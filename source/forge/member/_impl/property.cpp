/// Forge Modules
#include "forge/member/property.hpp"
#include "forge/object/guard.hpp"

//  PUBLIC METHODS  //

Forge::Value::Any Forge::Member::Property::getter(Runtime::Isolate* isolate, Value::Any self) const {
    $_UNUSED $_AUTO = Object::Guard(self);  // lock the parent
    return m_getter ? m_getter(isolate, self) : Value::Missing();
}

Forge::Value::Any Forge::Member::Property::setter(Runtime::Isolate* isolate, Value::Any self, Value::Any value) {
    $_UNUSED $_AUTO = Object::Guard(self);  // lock the parent now
    return m_setter ? m_setter(isolate, self, value) : Value::Missing();
}