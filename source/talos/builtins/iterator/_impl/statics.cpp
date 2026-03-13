/// Talos Modules
#include "talos/async/service.hpp"
#include "talos/engine/dispatch.hpp"
#include "talos/globals/service.hpp"
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

struct TALOS_BUILTIN_FIELDS(Iterable::Iterator) {
    static Value::Any yield(Runtime::Isolate*, const Function::Arguments&);
};

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Iterable::Iterator) {
    TALOS_XX_STATICS_ITERATOR(X)
};
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Iterable::Iterator, yield, isolate, args) {
    // ensure some valid conditions firstly
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Object::Instance, args.self());

    auto self = args.self();  // get details
    auto* descriptor = self.attribute("value");
    $_ASSERT(descriptor != nullptr);  // check

    // attempt updating the incoming value now
    auto value = descriptor->setter(isolate, self, args[0]);
    return $_ASSERT(value.traits().okay()), value;
}

TALOS_MM_BUILTIN_STATIC(Iterable::Iterator, empty, isolate, ) { return isolate->create<Iterable::Iterator>(); }

TALOS_MM_BUILTIN_STATIC(Iterable::Iterator, from, isolate, args) {
    // ensure we have been given a suitable set of arguments
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);

    auto* descriptor = args[0].attribute(Operator::Kind::ITER);  // pull out the iterable
    if (descriptor == nullptr) descriptor = args[0].attribute(Operator::Attribute::ITER);
    auto attribute = descriptor ? descriptor->getter(isolate, args[0]) : Value::Missing();
    return attribute.traits().okay() ? attribute : isolate->panic(6000502, attribute.type_name());
}

TALOS_MM_BUILTIN_STATIC(Iterable::Iterator, dynamic, isolate, args) {
    // ensure we have been given a suitable set of arguments
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // pull out the incoming function now
    auto generator = args.at<Function::Dynamic>(0);

    // create at context to be used for our iterator callback (helps bind all GC references together)
    auto context = isolate->create<Object::Instance>();

    // prepare the incoming yield handler so it is cached only once
    auto yield = TALOS_MM_GLOBALS_NATIVE(isolate, "Iterator.dynamic:yield", Field::yield);

    // we bind the context with the necessary properties for iteration
    context.fields().emplace("next", Member::Factory::reference(generator));
    context.fields().emplace("value", Member::Factory::reference(Value::Void()));
    context.fields().emplace("yield", Member::Factory::reference(isolate->bind(yield, context)));

    // prepare the callback to be used for the iterator
    Iterable::Callback<Object::Instance> callback = [](auto* isolate, Object::Instance self, size_t idx) -> Value::Any {
        // prepare the available properties contained
        auto next = self.attribute("next")->getter(isolate, self);
        auto yield = self.attribute("yield")->getter(isolate, self);

        // prepare the arguments to be used now
        std::vector<Value::Any> args = { Number::Tagged(idx), yield };

        // attempt getting the next handler now
        auto done = isolate->invoke(next, Function::Arguments(args));

        // check whether or not the operation has now ended
        if (!done.traits().okay()) return Value::Failure();
        else if (done.truthiness()) return Value::Sentinel();
        else return self.attribute("value")->getter(isolate, self);
    };

    // and now we want to rebuild the iterator as necessary
    return isolate->create<Iterable::Iterator>(context, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Iterable::Iterator)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    TALOS_XX_STATICS_ITERATOR(X)
#undef X

    // and return the resulting instance
    return self;
}
