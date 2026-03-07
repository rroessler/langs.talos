/// Talos Modules
#include "talos/heap/service.hpp"
#include "talos/garbage/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Heap::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Heap::Service::Service(XI::Container* services) :
    m_options(&services->get<Runtime::Options>()->heap), m_services(services) {
    // calculate the incoming details to be used now
    auto protection = $::Memory::Prot::READ | $::Memory::Prot::WRITE;
    m_data = $::Memory::Map::alloc(Limits::ADDRESS_SPACE, protection);

    // get some details about the heap before continuing
    auto address = std::bit_cast<Address>(m_data);
    m_spaces->unmapped.reserve(Limits::REGIONS_TOTAL);

    // fill all the unmapped regions
    for (size_t ii = 0; ii < Limits::REGIONS_TOTAL; ++ii) {
        auto offset = address + (ii * Limits::REGIONS_SIZE);
        m_spaces->unmapped.emplace(std::bit_cast<Region*>(offset));
    }

    // fill all the initial regions now
    for (size_t ii = 0; ii < Limits::REGIONS_INITIAL; ++ii) m_spaces->free.emplace(m_remap());
}

Talos::Heap::Service::~Service() { $::Memory::Map::free(m_data, Limits::ADDRESS_SPACE), m_data = nullptr; }

//  PUBLIC METHODS  //

size_t Talos::Heap::Service::usage() const noexcept {
    // prepare the predicate to be used
    auto predicate = [](size_t acc, const Region* region) { return acc + region->used(); };

    // get all the used memory sizes now
    auto eden = std::ranges::fold_left(m_spaces->eden, 0, predicate);
    auto junior = std::ranges::fold_left(m_spaces->junior, 0, predicate);
    auto senior = std::ranges::fold_left(m_spaces->senior, 0, predicate);

    // and return the result now
    return eden + junior + senior;
}

void Talos::Heap::Service::grow() {
    auto factor = m_options->growth_factor;
    size_t unmapped_regions_count = m_spaces->unmapped.size();
    float free_regions_count = static_cast<float>(m_spaces->free.size());
    size_t regions_to_add = std::min(static_cast<size_t>(free_regions_count * (factor - 1)), unmapped_regions_count);
    for (size_t ii = 0; ii < regions_to_add; ++ii) m_spaces->free.emplace(m_remap());
}

void Talos::Heap::Service::shrink() {
    auto factor = m_options->shrink_factor;
    float free_regions_count = static_cast<float>(m_spaces->free.size());
    size_t regions_to_remove = static_cast<size_t>(free_regions_count * (1 - factor));
    for (size_t ii = 0; ii < regions_to_remove; ++ii) m_unmap();
}

Talos::Heap::Region* Talos::Heap::Service::release(Region* region) {
    // validate some details about the region to be released
    $_ASSERT(region->used() == 0, "Cannot release non-empty region");
    $_ASSERT(region->stage() == Stage::STACK, "Non-stack regions cannot be released");

    // get a reference to the original parent now
    auto* parent = region->parent();

    // should safely be able to release the region now
    return region->reset(), m_spaces->free.emplace(region), parent;
}

Talos::Heap::Region* Talos::Heap::Service::acquire(Stage stage, Region* parent) {
    auto lock = $::Lock::scope(m_mutex);
    Region* region = m_pop();  // pop now

    // handle garbage collection when necessary
    if (stage == Stage::EDEN && region == nullptr) {
        for (size_t attempt = 0; attempt < m_options->garbage_attempts; ++attempt) {
            auto* garbage = m_services->get<Garbage::Service>();
            lock.unlock(), garbage->collect(), lock.lock();
            if ((region = m_pop())) break;  // got next now
        }
    }

    // attempt re-mapping if necessary to do so (eg: no valid region)
    if (region == nullptr) region = m_remap();

    // ensure we have a valid region now
    $_ASSERT(region, "Could not acquire map heap-region");
    $_ASSERT(region->stage() == Stage::UNUSED, "Region already in use");

    // and update our internal maps now
    switch (region->promote(stage, parent)) {
        case Stage::EDEN: m_spaces->eden.emplace(region); break;
        case Stage::JUNIOR: m_spaces->junior.emplace(region); break;
        case Stage::SENIOR: m_spaces->senior.emplace(region); break;
        case Stage::STACK: m_spaces->stacks.emplace(region); break;

        // fail on all other cases now
        default: $_ABORT("Cannot acquire unknown heap-region");
    }

    // return the resulting region now
    return region;
}

//  PRIVATE METHODS  //

void Talos::Heap::Service::m_unmap() {
    // ensure we have free regions to map
    $_ASSERT(m_spaces->free.size() > 0, "No free regions to unmap");

    auto* region = *m_spaces->free.begin();         // get the first region now
    region->reset(), m_spaces->free.erase(region);  // erase the incoming region

    // and re-inserted as being unmapped
    m_spaces->mapped.erase(region);
    m_spaces->unmapped.emplace(region);
}

Talos::Heap::Region* Talos::Heap::Service::m_pop() {
    if (m_spaces->free.empty()) return nullptr;
    auto* region = *m_spaces->free.begin();
    return m_spaces->free.erase(region), region;
}

Talos::Heap::Region* Talos::Heap::Service::m_remap() {
    // ensure we have not run out of usable memory
    $_EXPECT(m_spaces->unmapped.size(), "Out of virtual memory");

    // get our new region to be used
    auto* region = *m_spaces->unmapped.begin();

    m_spaces->unmapped.erase(region);  // update maps
    m_spaces->mapped.emplace(new (region) Region());

    // get details about the region
    $_UNUSED auto region_address = std::bit_cast<Address>(region);

    // ensure the region is the correct size and within a valid space now
    $_ASSERT((region_address & Limits::REGIONS_MASK) == region_address);
    $_ASSERT(region->buffer() - region_address == sizeof(Region));

    // and return the resulting mapped memory
    return region;
}
