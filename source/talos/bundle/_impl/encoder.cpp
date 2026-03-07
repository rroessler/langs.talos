/// Talos Modules
#include "talos/bundle/codec.hpp"

//  PRIVATE METHODS  //

void Talos::Bundle::Encoder::m_encode(const Filesystem& fs, Sink& sink) const noexcept {
    // write the size of the incoming scripts vector
    m_write<size_t>(fs.scripts.size(), sink);

    // and write each of the script values now
    for (const auto& script : fs.scripts) m_encode(*script, sink);
}

void Talos::Bundle::Encoder::m_encode(const Linker::Arena& arena, Sink& sink) const noexcept {
    // encode the leading resource now
    m_encode(arena.resource, sink);

    // write the bytecode out to be encapsulated now
    m_write(arena.bytecode.buffer(), sink);

    m_write(arena.constants.size(), sink);  // write out the constants now
    for (const auto& constant : arena.constants) m_encode(constant, sink);

    m_write(arena.strings.size(), sink);  // write the strings now
    for (const auto& intern : arena.strings) m_write(intern.view(), sink), m_encode(intern.symbol(), sink);

    m_write(arena.functions.size(), sink);  // finally write the function information
    for (const auto& function : arena.functions) m_encode(*function, sink);
}

void Talos::Bundle::Encoder::m_encode(const $::URI::View& resource, Sink& sink) const noexcept {
    m_write($::URI::Buffer("arch", resource.relative()).view(), sink);
}

void Talos::Bundle::Encoder::m_encode(const Function::Info& info, Sink& sink) const noexcept {
    // write the current buffer details
    auto buffer = info.buffer();
    m_write(buffer.size(), sink);
    m_write(buffer.offset(), sink);

    // write the shared information now
    auto* shared = info.shared();
    m_write(shared->arity, sink);
    m_write(shared->adicity, sink);
    m_write(shared->locals, sink);
    m_write(shared->leaked, sink);
    m_write(shared->vargs, sink);
}

void Talos::Bundle::Encoder::m_encode(const Value::Any& value, Sink& sink) const noexcept {
    m_write(Pointer::Underlying(value.traits()), sink);
}