/// Forge Modules
#include "forge/format/writer.hpp"

//  CONSTRUCTORS  //

Forge::Format::Writer::Writer() : Writer($::Global::get<Options>()) {}
Forge::Format::Writer::Writer(const Options* options) : m_options(options) {}
