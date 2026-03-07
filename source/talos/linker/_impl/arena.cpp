/// Talos Modules
#include "talos/linker/arena.hpp"
#include "talos/function/info.hpp"

//  PRIVATE METHODS  //

void Talos::Linker::Arena::m_print($::Stream::Output& os, const Arena& self) {
    // print all the available functions and their instructions
    for (const auto& function : self.functions) os << *function << "\n\n";

    // print the incoming constants pool now
    os << "<Constant Pool (size: " << self.constants.size() << ")>";
    for (const auto& [ii, constant] : $::Each(self.constants)) {
        $_UNUSED $_AUTO = $::Manip::Indent(os);
        os << "\n[" << ii << "]: " << constant;
    }

    if (self.constants.size()) os << '\n';  // print the intern pool
    os << "\n<Interns Pool (size: " << self.strings.size() << ")>";
    for (const auto& [ii, intern] : $::Each(self.strings)) {
        $_UNUSED $_AUTO = $::Manip::Indent(os);  // prepare indentation
        os << "\n[" << ii << "]: " << $::Dye::green("\"{0}\"", intern);
    }
}
