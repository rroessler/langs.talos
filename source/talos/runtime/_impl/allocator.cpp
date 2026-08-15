/// Talos Includes
#include "talos/heap/service.hpp"
#include "talos/runtime/isolate.hpp"

//  PRIVATE METHODS  //

Talos::Value::Any *Talos::Runtime::Stack::m_allocate() { return Allocator::m_reserve(m_isolate, m_capacity); }
void Talos::Runtime::Stack::m_release() { Allocator::m_release(m_isolate, m_data, m_capacity); }

Talos::Value::Any *Talos::Runtime::Allocator::m_reserve(Isolate *isolate, size_t size) {
  // attempt getting the associated isolate buffer now
  auto *buffer = isolate->m_services->get<Heap::Service>()->stack(isolate);

  // and attempt allocating the incoming values now and pre-fill
  auto *output = buffer->allocate<Value::Any>(isolate, size);
  return std::ranges::fill_n(output, size, Value::Void()), output;
}

void Talos::Runtime::Allocator::m_release(Isolate *isolate, Value::Any *data, size_t size) {
  isolate->m_services->get<Heap::Service>()->stack(isolate)->release(data, size);
}
