/// Forge Modules
#include "forge/string/dynamic.hpp"
#include "forge/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Forge::String::Dynamic::Dynamic(Runtime::Isolate* isolate, const Intern& intern) : Dynamic() {
    if (intern.bytes() <= Limits::SMALL) m_pointer = Small(intern.view()).m_pointer;
    else m_pointer = isolate->create<String::Large>(intern).m_pointer;
}

Forge::String::Dynamic::Dynamic(Runtime::Isolate* isolate, const $::String::View& value) : Dynamic() {
    if (value.size() <= Limits::SMALL) m_pointer = Small(value).m_pointer;
    else m_pointer = isolate->create<String::Large>(value).m_pointer;
}
