/// Forge Modules
#include "forge/format/pipeline.hpp"
#include "forge/format/dispatch.hpp"

//  PUBLIC METHODS  //

Forge::Format::Result Forge::Format::Pipeline::process(const Lexer::Buffer* tokens, const Options* options) {
    // ensure the process has been initialized
    $_UNUSED $_AUTO = m_initialize(tokens, options);

    // attempt reading the program as a body
    auto* program = Dispatch::m_collection(m_reader.get());
    if (program == nullptr) return std::nullopt;  // failed

    // write the program and return the result now
    return program->render(m_writer.get()), m_writer->merge();
}
