/// Talos Modules
#include "talos/object/exception.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Object::Attributes<Talos::Object::Exception>::Attributes(Runtime::Isolate* isolate) :
    Attributes(isolate, String::Dynamic()) {}

Talos::Object::Attributes<Talos::Object::Exception>::Attributes(
    Runtime::Isolate* isolate, const $::String::View& message) :
    Attributes(isolate, String::Dynamic(isolate, message)) {}

Talos::Object::Attributes<Talos::Object::Exception>::Attributes(Runtime::Isolate* isolate, String::Dynamic message) :
    Attributes(isolate, String::Dynamic(isolate, "Runtime"), message) {}

Talos::Object::Attributes<Talos::Object::Exception>::Attributes(
    Runtime::Isolate* isolate, const $::String::View& name, const $::String::View& message) :
    Attributes(isolate, String::Dynamic(isolate, name), String::Dynamic(isolate, message)) {}

Talos::Object::Attributes<Talos::Object::Exception>::Attributes(
    Runtime::Isolate* isolate, String::Dynamic arg_name, String::Dynamic arg_message) {
    // prepare the local scoping
    auto local_scope = isolate->scope();

    // prepare the locals to be used
    auto local_name = local_scope(arg_name);
    auto local_message = local_scope(arg_message);

    // set the values to be used now
    name = *local_name, message = *local_message, trace = isolate->backtrace();
}

//  PRIVATE METHODS  //

$::Stream::Output& Talos::Object::Exception::m_format($::Stream::Output& os) const noexcept {
    os << $::Dye::red("{0}.{1}", type_name(), name()).bold() << ": " << message();
    for (const auto& trace : trace()) os << $::Dye::dim("\n --> {0}", trace);
    return os;  // and return the initial output-stream for more printing now
}

void Talos::Object::Exception::m_yield(const Exception& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->name);
    yield(attributes->message);
}

void Talos::Object::Exception::m_print($::Stream::Output& os, const Exception& self) {
    os << $::Dye::cyan("<{0}.{1}: stack({2})>", self.type_name(), self.name(), self.trace().size());
}
