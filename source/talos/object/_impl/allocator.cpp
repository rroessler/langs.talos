/// Talos Modules
#include "talos/object/allocator.hpp"
#include "talos/heap/service.hpp"
#include "talos/runtime/isolate.hpp"

//  PRIVATE METHODS  //

Talos::Heap::Address Talos::Object::Allocator::m_allocate(
    Runtime::Isolate* isolate, size_t size, Shape::Underlying shape) {
    auto* heap = isolate->service<Heap::Service>();
    auto* buffer = heap->allocator(isolate);

    // prepare some constexpr values to be used
    constexpr auto s_padding = sizeof(Object::Header);

    // ensure we fix the incoming size to be used
    size = Heap::Align(size + s_padding);

    // attempt actually allocating now
    auto address = buffer->allocate(isolate, size);
    auto* header = std::bit_cast<Header*>(address);

    // and initialize the header instance as well
    return new (header) Header(shape, size), address + s_padding;
}
