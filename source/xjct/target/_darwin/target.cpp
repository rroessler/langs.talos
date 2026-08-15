/// Platform Modules
#include "xjct/target/darwin.hpp"

#if $_PLATFORM_DARWIN && defined(__MACH__)

/// Darwin Modules
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <mach-o/ldsyms.h>

/// Vendor Modules
#include <xpc/xpc.hpp>

//  PRIVATE METHODS  //

bool XJCT::Target::Darwin::m_codesign(const $::FS::Path &binary) const noexcept {
  // attempt constructing our necessary options for codesigning
  auto builder = XPC::Shell::Builder("codesign")
                     .cout(XPC::Pipe::Direct::PIPED)
                     .cerr(XPC::Pipe::Direct::PIPED)
                     .argv({"--sign", "-", binary.string()});

  // execute the incoming task now before continuing
  return XPC::Process::Child(builder).wait() == EXIT_SUCCESS;
}

XJCT::Blob::View XJCT::Target::Darwin::m_resource(const $::String::View &name) const noexcept {
  unsigned long size = 0; // prepare size to resolve the instance
  auto *ptr = ::getsectiondata(&_mh_execute_header, "__TEXT", name.data(), &size); // get now
  return ptr == nullptr ? Blob::View() : Blob::View(reinterpret_cast<const char *>(ptr), size);
}

#endif
