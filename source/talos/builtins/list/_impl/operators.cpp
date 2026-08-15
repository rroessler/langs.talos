/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Apply, static Value::Any iterator(Isolate *, const Iterable::List &))

//  PROPERTIES  //

/// @brief All available operators.
static auto s_operators = Talos::Operator::Storage<Talos::Iterable::List>({
    {Talos::Operator::Kind::ITER, Talos::Builtins::Apply::iterator},
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Apply::iterator(Isolate *isolate, const Iterable::List &self) {
  // prepare the iterator callback to be used
  Iterable::Callback<Iterable::List> callback = [](auto *, const Iterable::List &self, size_t index) -> Value::Any {
    return index < self.size() ? self.get(index) : Value::Sentinel();
  };

  // and construct the resulting iterator to be used now
  return isolate->create<Iterable::Iterator>(self, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Iterable::List>::m_operator(const Iterable::List &, Operator::Kind kind) {
  return s_operators.lookup(kind);
}
