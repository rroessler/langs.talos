/// Talos Includes
#include "talos/diagnostic/view.hpp"

//  PRIVATE METHODS  //

void Talos::Diagnostic::View::m_print(std::ostream &os, const View &self) {
  auto severity = Inspect::color(self.m_severity);
  auto code = $::Dye::dim("(TAL{0})", self.m_code);

  os << severity << ' ' << code << ": " << self.m_message << '\n'; // prepare details
  os << $::Dye::dim(" --> {0}", fmt::to_string(fmt::join(std::views::reverse(self.m_stack), "\n --> ")));
}
