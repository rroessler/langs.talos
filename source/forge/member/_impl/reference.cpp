/// Forge Modules
#include "forge/member/reference.hpp"
#include "forge/object/guard.hpp"

//  PUBLIC METHODS  //

Forge::Value::Any Forge::Member::Reference::getter(Runtime::Isolate*, Value::Any self) const {
    $_UNUSED $_AUTO = Object::Guard(self);
    return m_reference;  // return result
}

Forge::Value::Any Forge::Member::Reference::setter(Runtime::Isolate*, Value::Any self, Value::Any value) {
    $_UNUSED $_AUTO = Object::Guard(self);
    if (!readonly()) return m_reference = value;
    return Value::Void(Value::Feedback::FIELD_IMMUTABLE);
}