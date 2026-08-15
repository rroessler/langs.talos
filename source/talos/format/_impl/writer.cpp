/// Talos Include
#include "talos/format/writer.hpp"

//  CONSTRUCTORS  //

Talos::Format::Writer::Writer() : Writer($::Global::get<Format::Options>()) {}
Talos::Format::Writer::Writer(const Options *options) : m_options(options) {}
