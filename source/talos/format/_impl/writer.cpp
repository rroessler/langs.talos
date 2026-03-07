/// Talos Modules
#include "talos/format/writer.hpp"

//  CONSTRUCTORS  //

Talos::Format::Writer::Writer() : Writer($::Global::get<Options>()) {}
Talos::Format::Writer::Writer(const Options* options) : m_options(options) {}
