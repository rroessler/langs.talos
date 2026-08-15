/// Talos Include
#include "talos/format/pipeline.hpp"
#include "talos/format/dispatch.hpp"

//  CONSTRUCTORS  //

Talos::Format::Pipeline::Pipeline() : Pipeline($::Global::get<Format::Options>()) {}
Talos::Format::Pipeline::Pipeline(const Options *options) : m_options(options) {}

//  PUBLIC METHODS  //

const Talos::Format::Options *Talos::Format::Pipeline::options() const noexcept { return m_options; }
Talos::Format::Result Talos::Format::Pipeline::process(const Lexer::Buffer *tokens) {
  // construct the reader and writer to be used
  auto writer = $::Unique::New<Writer>(m_options);
  auto reader = $::Unique::New<Reader>(tokens, m_options);

  // attempt reading the program as a collection of nodes
  auto *program = Dispatch::program(reader.get());
  if (program == nullptr) return std::nullopt;

  // finally attempt writing our output program now
  return program->render(writer.get()), writer->merge();
}
