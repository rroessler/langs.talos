/// Talos Includes
#include "talos/object/exception.hpp"
#include "talos/globals/roots.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Object::Wrapper<Talos::Object::Exception>::Wrapper(Runtime::Isolate *isolate) :
    Wrapper(isolate, String::Any()) {}

Talos::Object::Wrapper<Talos::Object::Exception>::Wrapper(Runtime::Isolate *isolate, const $::String::View &message) :
    Wrapper(isolate, String::Any(isolate, message)) {}

Talos::Object::Wrapper<Talos::Object::Exception>::Wrapper(Runtime::Isolate *isolate, String::Any message) :
    Wrapper(isolate, String::Any(isolate, "Runtime"), message) {}

Talos::Object::Wrapper<Talos::Object::Exception>::Wrapper(
    Runtime::Isolate *isolate, const $::String::View &name, const $::String::View &message
) : Wrapper(isolate, String::Any(isolate, name), String::Any(isolate, message)) {}

Talos::Object::Wrapper<Talos::Object::Exception>::Wrapper(
    Runtime::Isolate *isolate, String::Any arg_name, String::Any arg_message
) {
  // prepare the local scoping
  auto local_scope = isolate->scope();

  // prepare the locals to be used
  auto local_name = local_scope(arg_name);
  auto local_message = local_scope(arg_message);

  // set the values to be used now
  name = *local_name, message = *local_message, trace = isolate->backtrace();
}

//  PRIVATE METHODS  //

std::ostream &Talos::Object::Exception::m_format(std::ostream &os) const noexcept {
  os << $::Dye::red("{0}.{1}", brand(), name()).bold() << ": " << message();
  for (const auto &trace : trace()) os << $::Dye::dim("\n --> {0}", trace);
  return os; // and return the initial output-stream for more printing now
}

void Talos::Object::Exception::m_yield(const Exception &self, Globals::Each &yield) {
  auto *attributes = self.m_wrapper();
  yield(attributes->name);
  yield(attributes->message);
}

void Talos::Object::Exception::m_print(std::ostream &os, const Exception &self) {
  os << $::Dye::cyan("<{0}.{1}: stack({2})>", self.brand(), self.name(), self.trace().size());
}
