/// Forge Modules
#include "forge/heap/service.hpp"
#include "forge/runtime/isolate.hpp"

//  PRIVATE METHODS  //

Forge::Value::Any* Forge::Runtime::Stack::m_allocate() { return m_allocator->m_reserve(m_capacity); }
void Forge::Runtime::Stack::m_release() { m_allocator->m_release(m_data, m_capacity); }

Forge::Value::Any* Forge::Runtime::Allocator::m_reserve(size_t size) {
    // ensure we have an accompanying buffer now
    if (m_buffer == nullptr) {
        auto* heap = m_isolate->service<Heap::Service>();  // get the heap
        m_buffer = $::New().unique<Heap::Buffer>(heap, Heap::Stage::STACK);
    }

    // and attempt allocating the incoming values now and pre-fill
    auto* buffer = m_buffer->allocate<Value::Any>(m_isolate, size);
    return std::ranges::fill_n(buffer, size, Value::Void()), buffer;
}

void Forge::Runtime::Allocator::m_release(Value::Any* data, size_t size) {
    $_ASSERT(m_buffer, "Cannot release data without heap-buffer");
    m_buffer->release(data, size);  // and attempt releasing now
}
