/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Library Includes
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/macros/processor.hpp"
#include "xtdlib/portable/windows.hpp"
#include "xtdlib/system/environment.hpp"

//  PUBLIC METHODS  //

std::optional<$::String::Buffer> $::Environ::get(const String::Buffer &key) {
  size_t size = 0; // prepare
  auto buffer = String::Buffer();

  do {
    buffer.resize(buffer.size() + 4096); // attempt resizing out buffer as necessary
    size = ::GetEnvironmentVariableA(key.c_str(), &buffer.front(), static_cast<DWORD>(buffer.size()));
  } while (size == buffer.size());

  // do a final resize on the buffer
  buffer.resize(size);

  // and handle the outgoing result now
  return buffer.size() ? std::optional(buffer) : std::nullopt;
}

bool $::Environ::del(const String::Buffer &key) { return ::SetEnvironmentVariableA(key.c_str(), nullptr); }
bool $::Environ::set(const String::Buffer &key, const String::Buffer &value) {
  return ::SetEnvironmentVariableA(key.c_str(), value.c_str());
}

$::Map::Dict<$::String::Buffer> $::Environ::view() {
  // prepare the output to be used
  auto output = Map::Dict<String::Buffer>();

  // get all available environment strings
  auto block = ::GetEnvironmentStringsA();
  if (block == nullptr) return output;

  // attempt iterating over the available block now
  for (LPTCH ii = block; *ii != L'\0'; ++ii) {
    String::Buffer key, value; // prepare
    for (; *ii != L'='; ++ii) key += *ii;
    for ($_UNUSED $_AUTO = ii++; *ii != L'\0'; ++ii) value += *ii;
    output.emplace(key, value); // emplace
  }

  // and return the resulting output now
  return ::FreeEnvironmentStringsA(block), output;
}

#endif
