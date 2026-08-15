/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Apply, static Value::Any iterator(Isolate *, const String::Any &))

//  PROPERTIES  //

/// @brief All available operators.
static auto s_operators = Talos::Operator::Storage<Talos::String::Any>({
    {Talos::Operator::Kind::ITER, Talos::Builtins::Apply::iterator},
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Apply::iterator(Isolate *isolate, const String::Any &self) {
  // prepare the iterator callback to be used
  Iterable::Callback<String::Any> callback = [](auto *, const String::Any &self, size_t index) -> Value::Any {
    return index < self.size() ? String::Small(self.rune(index)) : Value::Sentinel();
  };

  // and construct the resulting iterator to be used now
  return isolate->create<Iterable::Iterator>(self, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Member::View Talos::Builtins::Wrapper<Talos::String::Any>::m_operator(const String::Any &, Operator::Kind kind) {
  return s_operators.lookup(kind);
}
