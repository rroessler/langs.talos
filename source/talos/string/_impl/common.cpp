/// Talos Includes
#include "talos/string/common.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::String::Any::Any(Runtime::Isolate *isolate, const Intern &intern) : Any() {
  if (intern.bytes() <= Limits::SMALL) m_pointer = Small(intern.view()).m_pointer;
  else m_pointer = isolate->create<String::Large>(intern).m_pointer;
}

Talos::String::Any::Any(Runtime::Isolate *isolate, const $::String::View &value) : Any() {
  if (value.size() <= Limits::SMALL) m_pointer = Small(value).m_pointer;
  else m_pointer = isolate->create<String::Large>(value).m_pointer;
}
