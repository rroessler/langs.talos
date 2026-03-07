/// Talos Modules
#include "talos/operator/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

struct TALOS_BUILTIN_OPERATORS(Iterable::List) {
    static Value::Any iterator(Runtime::Isolate* isolate, Iterable::List self);
};

//  PROPERTIES  //

Talos::Operator::Storage<Talos::Iterable::List> TALOS_BUILTIN_TRAITS(
    Iterable::List)::m_operators = Operator::Storage<Iterable::List>({ { Operator::Kind::ITER, Apply::iterator } });

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_OPERATOR(Iterable::List, iterator, isolate, Iterable::List self) {
    // prepare the iterator callback to be used
    Iterable::Callback<Iterable::List> callback = [](auto*, Iterable::List self, size_t index) -> Value::Any {
        return index < self.size() ? self.get(index) : Value::Sentinel();
    };

    // and construct the resulting iterator to be used now
    return isolate->create<Iterable::Iterator>(self, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Iterable::List)::m_attributes(const Iterable::List&, Operator::Kind kind) {
    return m_operators.lookup(kind);
}
