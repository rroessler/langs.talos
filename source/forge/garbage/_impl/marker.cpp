/// Forge Modules
#include "forge/garbage/marker.hpp"
#include "forge/garbage/service.hpp"
#include "forge/globals/roots.hpp"
#include "forge/heap/service.hpp"
#include "forge/runtime/container.hpp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  CONSTRUCTORS  //

Forge::Garbage::Marker::Marker(Garbage::Service* garbage) : Marker($::Global::get<Runtime::Container>(), garbage) {}
Forge::Garbage::Marker::Marker(XI::Container* services, Garbage::Service* garbage) :
    m_heap(services->get<Heap::Service>()), m_garbage(garbage) {}

//  PUBLIC METHODS  //

void Forge::Garbage::Marker::mark(Mode mode, const Globals::Roots* roots) {
    roots->each([&](Value::Any& value) { mark(mode, value); });
}

void Forge::Garbage::Marker::mark(Mode mode, const Value::Any& value) {
    if (value.is<Object::Any>()) mark(mode, value.as<Object::Any>());
}

void Forge::Garbage::Marker::mark(Mode mode, const Object::Any& object) {
    if (mode != Mode::MINOR || !object.traits().is<Pointer::Kind::SEN>()) m_queue.push(object);
}

void Forge::Garbage::Marker::trace(Mode mode) {
    // prepare a suitable mark handler
    auto yield = Globals::Each([&](Value::Any& value) { mark(mode, value); });

    // attempt trace across all the available object queue
    for (; m_queue.size(); m_queue.pop()) {
        // get the underlying object and its header
        auto* header = m_queue.front().header();

        // attempt setting the current object as being blackened and compact it
        if (m_blacken(header, yield)) m_compact(mode, header);
    }
}

//  PRIVATE METHODS  //

bool Forge::Garbage::Marker::m_blacken(Object::Header* header, const Globals::Each& yield) {
    // if the object was already reachable, then we ignore blackening
    if (!header->toggle<Object::Flag::REACHABLE>(true)) return false;

#define X(T, ...) \
    case Shape::Lookup<T>(): Value::Proxy<T>::yield(header->encode<T>(), yield); break;
    switch (header->shape()) { FORGE_XX_VALUES_OBJECT(X) default : X(Object::Instance) }
#undef X

    // and declare that we successfully marked our items
    return true;
}

Forge::Heap::Region* Forge::Garbage::Marker::m_junior(Mode, size_t size) const noexcept {
    // prepare the predicate to be used
    auto predicate = [size](const Heap::Region* region) { return region->fits(size); };

    // otherwise find a current region that fits potentially
    if (auto* region = $::Filter.first(m_garbage->m_juniors, predicate)) return region;

    // otherwise construct a new one to be used instead
    return *m_garbage->m_juniors.emplace(m_heap->acquire(Heap::Stage::JUNIOR)).first;
}

Forge::Heap::Region* Forge::Garbage::Marker::m_senior(Mode mode, size_t size) const noexcept {
    // prepare the predicate to be used
    auto predicate = [size](const Heap::Region* region) { return region->fits(size); };

    // check if we can scan our current senior regions
    auto senior = mode == Mode::MINOR;

    // attempt a first get of a region here
    if (auto* region = senior ? $::Filter.first(m_heap->regions()->senior, predicate) : nullptr) return region;

    // otherwise find a current region that fits potentially
    if (auto* region = $::Filter.first(m_garbage->m_seniors, predicate)) return region;

    // otherwise construct a new one to be used instead
    return *m_garbage->m_seniors.emplace(m_heap->acquire(Heap::Stage::SENIOR)).first;
}

Forge::Heap::Region* Forge::Garbage::Marker::m_target(
    Mode mode, size_t size, size_t survivors, Heap::Stage stage) const noexcept {
    switch (stage) {
        case Heap::Stage::EDEN: return m_junior(mode, size);
        case Heap::Stage::SENIOR: return m_senior(mode, size);

        // for junior regions we want to base on the survivor count
        case Heap::Stage::JUNIOR: {
            auto senior = survivors >= m_heap->options()->garbage_survivors;
            return senior ? m_senior(mode, size) : m_junior(mode, size);  // get
        }

        // should not normally reach here at all
        default: $_ABORT("Unexpected heap-region stage");
    }
}

void Forge::Garbage::Marker::m_compact(Mode mode, Object::Header* header) const noexcept {
    // get the underlying region being used
    auto stage = header->region()->stage();

    // cannot collect senior regions in minor-collection
    if (mode == Mode::MINOR && stage == Heap::Stage::SENIOR) return;

    // attempt getting the associated target region now
    auto* region = m_target(mode, header->size(), header->survivors(), stage);
    $_ASSERT(region != nullptr, "Could not resolve a valid target region");

    // copy the header into the target region
    auto padding = sizeof(Object::Header);
    auto address = region->allocate(header->size());
    auto pointer = std::bit_cast<void*>(address);
    std::memcpy(pointer, std::bit_cast<void*>(header), padding);

#define X(T, ...) \
    case Shape::Lookup<T>(): Object::Allocator::move<T>(address + padding, header->encode()); break;
    switch (header->shape()) { FORGE_XX_VALUES_OBJECT(X) default : X(Object::Instance) }
#undef X

    // update all the flags for the newly constructed address now
    auto* target = reinterpret_cast<Object::Header*>(pointer);
    target->promote(region->stage() == Heap::Stage::SENIOR);

    // set the current forwarding target now as necessary
    header->forwarded(m_garbage->m_encode(target));

    // ensure reachability is valid now as well
    $_ASSERT(!target->reachable()), $_ASSERT(header->reachable());

    // prepare some validation just in case we messed up
    $_ASSERT(target->encode() == m_garbage->m_decode(header));
}
