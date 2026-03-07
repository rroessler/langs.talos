/// Talos Modules
#include "talos/format/reader.hpp"

//  CONSTRUCTORS  //

Talos::Format::Reader::Reader(const Lexer::Buffer* tokens) : Reader(tokens, $::Global::get<Options>()) {}
Talos::Format::Reader::Reader(const Lexer::Buffer* tokens, const Options* options) :
    Lexer::Visitor(tokens), m_options(options), m_storage($::New().unique<Storage>()) {}
