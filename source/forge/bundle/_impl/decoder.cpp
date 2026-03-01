/// Forge Modules
#include "forge/bundle/codec.hpp"

//  PRIVATE METHODS  //

Forge::Bundle::Filesystem Forge::Bundle::Decoder::m_decode(Source source) const noexcept {
    // construct the baseline filesystem instance now
    auto filesystem = Filesystem();

    // prepare the size of the incoming scripts now
    auto scripts = m_read<size_t>(source);

    // pre-fill the resources and scripts size
    filesystem.scripts.reserve(scripts);
    filesystem.resources.reserve(scripts);

    // and attempt decoding as necessary into the arenas
    for (size_t ii = 0; ii < scripts; ++ii) {
        auto buffer = $::URI::Codec::parse(m_view(source));
        $::URI::View resource = filesystem.resources.emplace_back(buffer);
        auto& arena = filesystem.scripts.emplace_back(nullptr);
        m_decode(arena, source), arena->resource = resource;
    }

    // return the resulting filesystem now
    return filesystem;
}

void Forge::Bundle::Decoder::m_decode($::Ptr::Unique<Linker::Arena>& arena, Source& source) const noexcept {
    // ensure we reconstruct the arena now
    arena = $::New().unique<Linker::Arena>();

    // update the bytecode block to be used
    arena->bytecode = { m_span<uint8_t>(source) };

    auto constants = m_span<Pointer::Underlying>(source);  // read the constants
    for (const auto& pointer : constants) arena->constants.emplace_back(pointer);

    // prepare the strings base to be read from
    auto strings = m_read<size_t>(source);
    arena->strings.reserve(strings);

    // prepare the strings to be read now
    for (size_t ii = 0; ii < strings; ++ii) {
        auto buffer = $::String::Buffer(m_view(source));
        auto value = Value::Any(m_read<Pointer::Underlying>(source));
        arena->strings.emplace_back(buffer, value.as<Value::Symbol>());
    }

    // prepare the functions size to be read from
    auto functions = m_read<size_t>(source);
    arena->functions.reserve(functions);

    // finally attempt writing all out all the functions now
    for (size_t ii = 0; ii < functions; ++ii) {
        auto info = $::New().unique<Function::Info>(arena.get());
        m_decode(arena->functions.emplace_back(std::move(info)), source);
    }
}

void Forge::Bundle::Decoder::m_decode($::Ptr::Unique<Function::Info>& info, Source& source) const noexcept {
    // get the underlying buffer details
    auto size = m_read<size_t>(source), offset = m_read<size_t>(source);
    info->buffer() = info->arena()->bytecode.view(offset, size);

    // read the shared information now
    auto* shared = info->shared();
    m_read(&shared->arity, 1, source);
    m_read(&shared->adicity, 1, source);
    m_read(&shared->locals, 1, source);
    m_read(&shared->leaked, 1, source);
    m_read(&shared->vargs, 1, source);
}
