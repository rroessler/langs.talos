/// Talos Modules
#include "talos/runtime/isolate.hpp"
#include "talos/async/future.hpp"
#include "talos/builtins/proxy.hpp"
#include "talos/engine/dispatch.hpp"
#include "talos/engine/frame.hpp"
#include "talos/globals/service.hpp"
#include "talos/heap/service.hpp"
#include "talos/machine/frame.hpp"
#include "talos/module/service.hpp"
#include "talos/resource/frame.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/service.hpp"

/// Metadata Modules
#include "talos/engine/metadata.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Runtime::Isolate::Isolate() : Isolate($::Global::get<Container>()) {}
Talos::Runtime::Isolate::Isolate(XI::Container* services) : Isolate(services, Value::Void()) {}
Talos::Runtime::Isolate::Isolate(XI::Container* services, const Value::Any& data) :
    m_services(services), m_data(data), m_allocator(this) {}

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Runtime::Isolate::interrupt() {
    if (m_frame) m_frame->interrupted() = true;
    return Value::Failure();  // declare failed
}

void Talos::Runtime::Isolate::roots(const Globals::Each& yield) {
    // yield the baseline details
    yield(m_data), yield(m_exception);

    // and then yield all the handles
    for (auto* handle = m_handles.head(); handle; handle = handle->next()) yield(handle->value());

    // finally start going through the frame roots now
    for (auto* frame = m_frame; frame; frame = frame->parent()) {
        // ensure we have a valid frame to be used
        if (!frame->is<Function::Frame>()) continue;

        // get the underlying closure frame now
        auto* closure = frame->as<Function::Frame>();

        // yield context environment and locals
        yield(closure->context().environment());
        yield(closure->span(0, closure->info()->locals()));
    }
}

std::vector<Talos::Resource::Trace> Talos::Runtime::Isolate::backtrace() {
    // get the initial frame value to be used
    auto* frame = m_frame;

    // prepare the resulting stack to be used
    auto stack = std::vector<Resource::Trace>();

    // if no frame exists, then construct an empty trace
    if (frame == nullptr) return stack;

    // determine the current frame size to be used
    auto size = std::min(m_frame->depth() + 1, options()->limits.backtraces);

    // attempt appending each of our available frames
    for (size_t ii = (stack.reserve(size), 0); frame != nullptr && ii < size; frame = frame->parent()) {
        stack.emplace_back(frame->backtrace());
    }

    // and return the resulting backtrace as a list
    return stack;
}

Talos::Engine::Exports* Talos::Runtime::Isolate::exports(const $::String::View& script) {
    return exports(script, $::System::cwd());
}

Talos::Engine::Exports* Talos::Runtime::Isolate::exports(
    const $::String::View& script, const $::Filesystem::Path& hint) {
    auto resource = resolve(script, hint);  // resolve the resource
    return resource.has_value() ? exports(resource.value()) : nullptr;
}

Talos::Engine::Exports* Talos::Runtime::Isolate::exports(const $::URI::View& resource) {
    auto* module = service<Import::Service>()->fetch(resource);
    if (module == nullptr) return panic(8000102, resource.relative()), nullptr;
    return module->metadata<Module::Phase::EXPORTED>();  // can validly return
}

Talos::Value::Any Talos::Runtime::Isolate::global(Value::Symbol symbol) {
    return m_services->get<Globals::Service>()->get(this, symbol);
}

const Talos::String::Intern* Talos::Runtime::Isolate::intern(Value::Symbol symbol) {
    // ensure the underlying frame is valid
    if (m_frame == nullptr) return nullptr;

    // attempt finding the arena reference
    const auto* arena = m_frame->arena();
    if (arena == nullptr) return nullptr;

    auto predicate = [symbol](const String::Intern& intern) { return intern.symbol() == symbol; };
    auto iter = std::ranges::find_if(arena->strings, predicate);  // attempt finding now ...
    return iter == arena->strings.cend() ? nullptr : &*iter;      // ... resolve as necessary
}

Talos::Async::Result Talos::Runtime::Isolate::spawn(Value::Any target) { return spawn(target, {}, {}); }
Talos::Async::Result Talos::Runtime::Isolate::spawn(Value::Any target, const Resource::Trace& trace) {
    return spawn(target, {}, trace);
}

Talos::Async::Result Talos::Runtime::Isolate::spawn(Value::Any target, Function::Arguments&& args) {
    return spawn(target, std::move(args), {});
}

Talos::Async::Result Talos::Runtime::Isolate::spawn(
    Value::Any target, Function::Arguments&& args, const Resource::Trace& trace) {
    // prepare the incoming frame to be used for the execution of the target
    auto frame = trace.anonymous() ? nullptr : $::New().unique<Resource::Frame>(this, trace);

    // ensure we have a valid target to be awaited on
    if (target.is<Async::Future>()) return target.as<Async::Future>().await(thread());
    else if (!target.is<Function::Dynamic>()) return panic(6000201, target.type_name());
    return create<Async::Future>(target.as<Function::Dynamic>(), args).await(thread());
}

Talos::Value::Any Talos::Runtime::Isolate::invoke(Value::Any target) { return invoke(target, {}); }
Talos::Value::Any Talos::Runtime::Isolate::invoke(Value::Any target, const Function::Arguments& args) {
    return Engine::Call::any(this, target, args);
}

Talos::Function::Dynamic Talos::Runtime::Isolate::bind(const Function::Dynamic& callback, Value::Any receiver) {
    // prepare the incoming passthrough callback information
    auto* info = Builtins::Proxy<Function::Dynamic>::binder();

    auto context = Function::Context(this, 1);  // bind
    context.store(0, callback), context.self(receiver);

    // and construct the resulting passthrough handler
    return create<Function::Closure>(info, context);
}

Talos::Resource::Result Talos::Runtime::Isolate::resolve(const $::String::View& script) const {
    return resolve(script, $::System::cwd());
}

Talos::Resource::Result Talos::Runtime::Isolate::resolve(
    const $::String::View& script, const $::Filesystem::Path& hint) const {
    return service<Import::Service>()->resolve(script, hint);
}

Talos::Value::Any Talos::Runtime::Isolate::import(const $::String::View& script, const Resource::Trace& trace) {
    return import(script, $::System::cwd(), trace);
}

Talos::Value::Any Talos::Runtime::Isolate::import(const $::String::View& script, const $::Filesystem::Path& hint) {
    return import(script, hint, {});
}

Talos::Value::Any Talos::Runtime::Isolate::import(
    const $::String::View& script, const $::Filesystem::Path& hint, const Resource::Trace& trace) {
    auto resource = resolve(script, hint);
    if (resource) return import(*resource, trace);
    return panic(8000000, resource.error());
}

Talos::Value::Any Talos::Runtime::Isolate::import(const $::URI::View& resource) { return import(resource, {}); }
Talos::Value::Any Talos::Runtime::Isolate::import(const $::URI::View& resource, const Resource::Trace& trace) {
    auto* result = service<Import::Service>()->import(this, resource, trace);
    return result ? result->await(this) : Value::Failure();  // failed here
}
