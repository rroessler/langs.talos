/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Platform Modules
#include "xtdlib/portable/windows.hpp"
#include "xtdlib/system/executable.hpp"

//  PUBLIC METHODS  //

$::FS::Path $::Executable::resolve() {
  WCHAR file_path[MAX_PATH]; // prepare the buffer
  ::GetModuleFileNameW(NULL, file_path, MAX_PATH);
  return file_path; // and return the result now
}

#endif
