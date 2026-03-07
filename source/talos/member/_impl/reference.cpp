/// Talos Modules
#include "talos/member/reference.hpp"
#include "talos/object/guard.hpp"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Member::Reference::getter(Runtime::Isolate*, Value::Any self) const {
    $_UNUSED $_AUTO = Object::Guard(self);
    return m_reference;  // return result
}

Talos::Value::Any Talos::Member::Reference::setter(Runtime::Isolate*, Value::Any self, Value::Any value) {
    $_UNUSED $_AUTO = Object::Guard(self);
    if (!readonly()) return m_reference = value;
    return Value::Void(Value::Feedback::FIELD_IMMUTABLE);
}