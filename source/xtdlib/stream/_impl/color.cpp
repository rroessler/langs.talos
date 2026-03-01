/// Library Includes
#include "xtdlib/stream/color.hpp"
#include "xtdlib/terminal/dye.hpp"

//  PROPERTIES  //

std::locale::id $::Facet::Color::id = std::locale::id();

//  CONSTRUCTORS  //

$::Facet::Color::Color(Stream::Output& stream) : Color(Dye::enabled(stream)) {}
$::Facet::Color::Color(Stream::Handle* stream) : Color(Dye::enabled(stream)) {}
