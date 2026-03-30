/// Talos Modules
#include "talos/heap/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Heap::Buffer::Buffer(Stage stage) : Buffer($::Global::get<Runtime::Container>()->get<Heap::Service>(), stage) {}
Talos::Heap::Buffer::Buffer(Heap::Service* heap, Stage stage) : m_stage(stage), m_heap(heap) {}

//  PRIVATE METHODS  //

void Talos::Heap::Buffer::m_release($_UNUSED Address address, size_t size) {
    // validate some details about the current region
    $_ASSERT(m_region, "Cannot release buffer allocation from empty region");
    $_ASSERT(size <= m_region->used(), "Release size larger than region size");
    $_ASSERT(address == m_region->head() - size, "Mismatched heap-buffer release");

    // if the size was the same as the used, then pop the region
    if (m_region->release(size) == 0) m_region = m_heap->release(m_region);
}

Talos::Heap::Address Talos::Heap::Buffer::m_allocate(Runtime::Isolate* isolate, size_t size) {
    // check if the current region is valid
    bool exceeds = m_region == nullptr || !m_region->fits(size);

    // re-acquire a region now if necessary
    if (auto* thread = isolate->thread(); exceeds) thread->native([&] { m_acquire(); }), thread->checkpoint();

    // ensure we have some suitable results before continuing
    $_ASSERT(m_region, "Thread allocation region not acquired");
    $_ASSERT(m_region->fits(size), "Allocation does not fit region");
    $_ASSERT(m_region->stage() == m_stage, "Region stage mismatch");

    // return the allocation that occured now
    return m_region->allocate(size);
}

void Talos::Heap::Buffer::m_acquire() {
    auto* parent = m_stage == Stage::STACK ? m_region : nullptr;
    m_region = m_heap->acquire(m_stage, parent);  // acquire now
}
