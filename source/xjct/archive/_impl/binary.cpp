/// XJCT Modules
#include "xjct/archive/binary.hpp"
#include "xjct/forward/vendors.hpp"

//  PRIVATE METHODS  //

XJCT::Archive::Format XJCT::Archive::Binary::m_deduce(const Blob::Bytes &buffer) noexcept {
  if (LIEF::ELF::is_elf(buffer)) return Format::LINUX;
  else if (LIEF::MachO::is_macho(buffer)) return Format::DARWIN;
  return LIEF::PE::is_pe(buffer) ? Format::WINDOWS : Format::UNKNOWN;
}
