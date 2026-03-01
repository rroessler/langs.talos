#ifndef _TALOS_VALUE_FORWARD_HPP
#define _TALOS_VALUE_FORWARD_HPP

/// Forge Modules
#include <forge/value/_inline/value.ipp>

/// Forward Definitions
$_FWD(using Any = Forge::Value::Any, Talos::Value)
$_FWD(using Void = Forge::Value::Void, Talos::Value)
$_FWD(using Object = Forge::Object::Any, Talos::Value)
$_FWD(using List = Forge::Iterable::List, Talos::Value)
$_FWD(using Future = Forge::Async::Future, Talos::Value)
$_FWD(using Symbol = Forge::Value::Symbol, Talos::Value)
$_FWD(using Number = Forge::Number::Tagged, Talos::Value)
$_FWD(using String = Forge::String::Dynamic, Talos::Value)
$_FWD(using Boolean = Forge::Value::Boolean, Talos::Value)
$_FWD(using Function = Forge::Function::Dynamic, Talos::Value)
$_FWD(using Iterator = Forge::Iterable::Iterator, Talos::Value)
$_FWD(using Exception = Forge::Object::Exception, Talos::Value)

#endif
