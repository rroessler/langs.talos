/// Talos Modules
#include "talos/member/property.hpp"
#include "talos/object/guard.hpp"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Member::Property::getter(Runtime::Isolate* isolate, Value::Any self) const {
    $_UNUSED $_AUTO = Object::Guard(self);  // lock the parent
    return m_getter ? m_getter(isolate, self) : Value::Missing();
}

Talos::Value::Any Talos::Member::Property::setter(Runtime::Isolate* isolate, Value::Any self, Value::Any value) {
    $_UNUSED $_AUTO = Object::Guard(self);  // lock the parent now
    return m_setter ? m_setter(isolate, self, value) : Value::Missing();
}