/// Talos Modules
#include "talos/operator/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

struct TALOS_BUILTIN_OPERATORS(String::Dynamic) {
    static Value::Any iterator(Runtime::Isolate* isolate, String::Dynamic self);
};

//  PROPERTIES  //

Talos::Operator::Storage<Talos::String::Dynamic> TALOS_BUILTIN_TRAITS(
    String::Dynamic)::m_operators = Operator::Storage<String::Dynamic>({ { Operator::Kind::ITER, Apply::iterator } });

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_OPERATOR(String::Dynamic, iterator, isolate, String::Dynamic self) {
    // prepare the iterator callback to be used
    Iterable::Callback<String::Dynamic> callback = [](auto*, String::Dynamic self, size_t index) -> Value::Any {
        return index < self.size() ? String::Small(self.rune(index)) : Value::Sentinel();
    };

    // and construct the resulting iterator to be used now
    return isolate->create<Iterable::Iterator>(self, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(String::Dynamic)::m_attributes(const String::Dynamic&, Operator::Kind kind) {
    return m_operators.lookup(kind);
}
