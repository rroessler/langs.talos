/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Iterable::List) {
    TALOS_XX_STATICS_LIST(X)
};
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Iterable::List, from, isolate, args) {
    // ensure we have an incoming value
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);

    // pull out the incoming iterable value now
    auto value = args[0];

    // fast-path construction here if given an iterable straight away
    if (value.is<Iterable::Iterator>()) return isolate->create<Iterable::List>(value.as<Iterable::Iterator>());

    // prepare the incoming descriptor to be used
    auto* descriptor = value.attribute(Operator::Kind::ITER);

    // attempt getting the iterable to be used
    auto attribute = descriptor ? descriptor->getter(isolate, value) : Value::Missing();
    if (!attribute.traits().okay()) return isolate->panic(6000502, attribute.type_name());

    // should be able to cast and convert to a suitable array now
    return isolate->create<Iterable::List>(attribute.as<Iterable::Iterator>());
}

TALOS_MM_BUILTIN_STATIC(Iterable::List, empty, isolate, ) { return isolate->create<Iterable::List>(); }

TALOS_MM_BUILTIN_STATIC(Iterable::List, range, isolate, args) {
    // attempt pulling out necessary range values now as prescribed
    Value::Any start = Number::Tagged(0), end = Number::Tagged(0), step = Number::Tagged(1);

    // handle the incoming number of arguments available
    switch (args.size()) {
        case 0: break;
        case 1: end = args.at(0); break;
        default: step = args.at(2); $_FALLTHROUGH;
        case 2: start = args.at(0), end = args.at(1); break;
    }

    // ensure each of out items are valid now as well
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, start);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, end);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, step);

    // attempt preparing the list containing iterable values now
    std::vector<Value::Any> passthrough = { start, end, step };

    // construct a suitable range iterator now
    Iterable::Callback<Iterable::List> callback = [](auto*, Iterable::List self, size_t) -> Value::Any {
        // pull out the context values being used now
        Number::Underlying current = self.get(0).as<Number::Tagged>();
        Number::Underlying condition = self.get(1).as<Number::Tagged>();
        Number::Underlying step = self.get(2).as<Number::Tagged>();

        // we handle our condition based on the step
        if (step > 0 ? current >= condition : current <= condition) return Value::Sentinel();

        // update the current initial value being used
        return self.set(0, Number::Tagged(current + step)), Number::Tagged(current);
    };

    // and construct the resulting iterator now
    return isolate->create<Iterable::Iterator>(isolate->create<Iterable::List>(passthrough), std::move(callback));
}

TALOS_MM_BUILTIN_STATIC(Iterable::List, filled, isolate, args) {
    // ensure we have an incoming value
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);

    // prepare the incoming arguments now
    auto size = args.at<Number::Tagged>(0).value();
    TALOS_MM_ASSERT_LOWER(isolate, size, 0);
    TALOS_MM_ASSERT_INTEGRAL(isolate, size);

    // prepare the list and set all values as needed
    auto list = isolate->create<Iterable::List>(size);
    std::memset(list.data(), args[0].traits(), size);

    // return the resulting list now
    return list;
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Iterable::List)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    TALOS_XX_STATICS_LIST(X)
#undef X

    // and return the resulting instance
    return self;
}
