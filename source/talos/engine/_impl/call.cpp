/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/garbage/service.hpp"
#include "talos/machine/frame.hpp"
#include "talos/machine/signature.hpp"
#include "talos/object/class.hpp"
#include "talos/object/instance.hpp"
#include "talos/resource/frame.hpp"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Engine::Call::any(Isolate* isolate, Value::Any target, const Arguments& args) {
    // handle the incoming object types available
    switch (target.shape()) {
        case Shape::Lookup<Function::Native>(): return native(isolate, target.as<Function::Native>(), args);
        case Shape::Lookup<Function::Jitted>(): return jitted(isolate, target.as<Function::Jitted>(), args);
        case Shape::Lookup<Function::Closure>(): return closure(isolate, target.as<Function::Closure>(), args);
        case Shape::Lookup<Object::Class>(): return construct(isolate, target.as<Object::Class>(), args);

        // type is not callable here at all so we fail
        default: return isolate->panic(6000200, target.type_name());
    }
}

Talos::Value::Any Talos::Engine::Call::native(Isolate* isolate, Function::Native native, const Arguments& args) {
    // ensure the incoming native is validated here
    if ($_UNLIKELY(!m_validate(isolate, native, args))) return Value::Failure();

    // prepare the trace to be used
    static constexpr auto group = Resource::Group::NATIVE;
    auto trace = Resource::Trace(native.resource(), group);

    // build the resource frame to be used now
    $_UNUSED $_AUTO = Resource::Frame(isolate, trace);

    // and call the underlying native now
    return isolate->thread()->checkpoint(), native.callback()(isolate, args);
}

Talos::Value::Any Talos::Engine::Call::closure(Isolate* isolate, Function::Closure closure, const Arguments& args) {
    return m_closure(isolate, closure.info(), closure.context(), args);
}

Talos::Value::Any Talos::Engine::Call::inlined(Isolate* isolate, Function::Frame* frame, const Arguments& args) {
    return m_closure(isolate, frame->info(), frame->context(), args);
}

Talos::Value::Any Talos::Engine::Call::jitted(Isolate* isolate, Function::Jitted jitted, const Arguments& args) {
    return m_jitted(isolate, jitted.info(), jitted.context(), args);
}

Talos::Value::Any Talos::Engine::Call::inlined(Isolate* isolate, const Machine::Info* info, const Arguments& args) {
    const auto* frame = isolate->frame()->as<Machine::Frame>();
    return m_jitted(isolate, info, frame->context(), args);
}

Talos::Value::Any Talos::Engine::Call::construct(Isolate* isolate, Object::Class prototype, const Arguments& args) {
    // prepare the baseline statics here
    auto symbol = Operator::Attribute::CALL;
    const auto& statics = prototype.statics();

    // if the constructor is missing, the panic
    if (!statics.contains(symbol)) return isolate->panic(6000202, prototype.name());

    // pre-build the instance to be constructed
    auto instance = isolate->create<Object::Instance>(prototype);

    // should safely be able to get the constructor now
    auto constructor = statics.at(symbol)->getter(isolate, instance);

    // attempt calling the baseline constructor now
    auto result = any(isolate, constructor, { instance, args.span() });
    return result.traits().okay() ? instance : result;  // resolve now
}

//  PRIVATE METHODS  //

bool Talos::Engine::Call::m_validate(Isolate* isolate, Function::Dynamic target, const Arguments& args) {
    return m_validate(isolate, target.arity(), args);
}

bool Talos::Engine::Call::m_validate(Isolate* isolate, const Function::Info* info, const Arguments& args) {
    return m_validate(isolate, info->arity(), args);
}

bool Talos::Engine::Call::m_validate(Isolate* isolate, size_t arity, const Arguments& args) {
    // ensure that the incoming details are all valid
    auto total = args.size();

    // ensure the arguments have a suitable sizing now
    if ($_UNLIKELY(total < arity)) return isolate->panic(6000251, arity), false;

    // ensure that the instance has not overflowed now as well
    if ($_LIKELY(!isolate->thread()->stack()->overflowed())) return true;

    // otherwise we declare that the maximum recursion depth occuerd
    return isolate->panic("Maximum recursion depth exceeded"), false;
}

Talos::Function::Context Talos::Engine::Call::m_initialize(Isolate* isolate, size_t leaked, Function::Context parent) {
    // check if there are any leaked items
    if (!leaked) return parent;

    // construct a new context instance
    auto context = Function::Context(isolate, leaked);
    if (parent.valid()) context.parent(parent);
    return context;  // should be valid to bind
}

Talos::Value::Any Talos::Engine::Call::m_closure(
    Isolate* isolate, const Function::Info* info, Function::Context context, const Arguments& args) {
    // ensure the frame is valid before continuing
    if ($_UNLIKELY(!m_validate(isolate, info, args))) return Value::Failure();

    // attempt resolving our necessary sizes to be used now
    size_t locals = info->locals() + 1;
    if (locals > UINT32_MAX) locals = args.size() + 1;

    // build the frame to be used for calling
    auto frame = Function::Frame(isolate, info, args.self());

    // allocate the frame based on the stack now
    auto stack = isolate->allocator()->stack(locals);

    // bind the stack pointer to the frame
    frame.stack() = stack.data();

    // pull out the variadic arguments index
    size_t vargs = info->shared()->vargs;

    // prepare the argument count to be bound now
    auto argc = frame.argc() = std::min(args.size(), vargs);

    // fill the arguments as necessary now
    if (argc) std::memcpy(stack.data() + 1, args.data(), sizeof(Value::Any) * argc);

    // we also want to emit the spread parameter as well as a list
    if (vargs != UINT64_MAX) stack[frame.argc() = vargs + 1] = isolate->create<Iterable::List>(args.slice(vargs));

    // update the current leaked information to be used
    frame.context() = m_initialize(isolate, info->leaked(), context);

    // enforce a checkpoint before running our handler
    isolate->thread()->checkpoint();

    // get the incoming result
    auto result = Dispatch::m_execute(isolate, &frame);

    // execute our necessary handler
    return m_finalize(isolate, result);
}

Talos::Value::Any Talos::Engine::Call::m_jitted(
    Isolate* isolate, const Machine::Info* info, Function::Context context, const Arguments& args) {
    // construct a suitable machine frame now
    auto frame = Machine::Frame(isolate, info);

    // get the incoming maximum locals count to be used
    auto locals = info->locals() + Function::Offset::ARGS_DATA;

    // construct the potential passthrough stack now
    auto passthrough = isolate->allocator()->stack(locals);

    // clean the incoming passthrough arguments now
    passthrough[Function::Offset::ARGS_SIZE] = Number::Tagged(0);

    // construct the underlying stack to be used
    Value::Any stack[Machine::Offset::STK_SIZE] = {
        m_initialize(isolate, info->leaked(), context),
        std::bit_cast<Value::Any>(passthrough.data()),
        std::bit_cast<Value::Any>(&args),
    };

    // finally reinterpret the stack as our outgoing arguments
    const auto& outgoing = *reinterpret_cast<const Function::Arguments*>(&(frame.stack() = stack));

    // enforce a checkpoint before running our handler
    isolate->thread()->checkpoint();

    // get the incoming result
    auto result = info->callback(isolate, outgoing);

    // execute our necessary handler
    return m_finalize(isolate, result);
}

Talos::Value::Any Talos::Engine::Call::m_finalize(Isolate* isolate, Value::Any result) {
    return isolate->lifetimes()->close(isolate) ? result : Value::Failure();
}
