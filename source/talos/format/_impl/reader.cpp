/// Talos Include
#include "talos/format/reader.hpp"

//  CONSTRUCTORS  //

Talos::Format::Reader::Reader(const Lexer::Buffer *tokens) : Reader(tokens, $::Global::get<Format::Options>()) {}
Talos::Format::Reader::Reader(const Lexer::Buffer *tokens, const Options *options) :
    Visitor(tokens), m_options(options) {}
