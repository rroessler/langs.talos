/// Forge Modules
#include "forge/format/reader.hpp"

//  CONSTRUCTORS  //

Forge::Format::Reader::Reader(const Lexer::Buffer* tokens) : Reader(tokens, $::Global::get<Options>()) {}
Forge::Format::Reader::Reader(const Lexer::Buffer* tokens, const Options* options) :
    Lexer::Visitor(tokens), m_options(options), m_storage($::New().unique<Storage>()) {}
