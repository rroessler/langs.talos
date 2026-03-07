/// Talos Modules
#include "talos/string/dynamic.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::String::Dynamic::Dynamic(Runtime::Isolate* isolate, const Intern& intern) : Dynamic() {
    if (intern.bytes() <= Limits::SMALL) m_pointer = Small(intern.view()).m_pointer;
    else m_pointer = isolate->create<String::Large>(intern).m_pointer;
}

Talos::String::Dynamic::Dynamic(Runtime::Isolate* isolate, const $::String::View& value) : Dynamic() {
    if (value.size() <= Limits::SMALL) m_pointer = Small(value).m_pointer;
    else m_pointer = isolate->create<String::Large>(value).m_pointer;
}
