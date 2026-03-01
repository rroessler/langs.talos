/// Forge Modules
#include "forge/runtime/isolate.hpp"
#include "forge/async/future.hpp"
#include "forge/builtins/proxy.hpp"
#include "forge/engine/dispatch.hpp"
#include "forge/engine/frame.hpp"
#include "forge/globals/service.hpp"
#include "forge/heap/service.hpp"
#include "forge/machine/frame.hpp"
#include "forge/module/service.hpp"
#include "forge/resource/frame.hpp"
#include "forge/runtime/container.hpp"
#include "forge/runtime/service.hpp"

/// Metadata Modules
#include "forge/engine/metadata.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Forge::Runtime::Isolate::Isolate() : Isolate($::Global::get<Container>()) {}
Forge::Runtime::Isolate::Isolate(XI::Container* services) : Isolate(services, Value::Void()) {}
Forge::Runtime::Isolate::Isolate(XI::Container* services, const Value::Any& data) :
    m_services(services), m_data(data), m_allocator(this) {}

//  PUBLIC METHODS  //

Forge::Value::Any Forge::Runtime::Isolate::interrupt() {
    if (m_frame) m_frame->interrupted() = true;
    return Value::Failure();  // declare failed
}

void Forge::Runtime::Isolate::roots(const Globals::Each& yield) {
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

std::vector<Forge::Resource::Trace> Forge::Runtime::Isolate::backtrace() {
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

Forge::Engine::Exports* Forge::Runtime::Isolate::exports(const $::String::View& script) {
    return exports(script, $::System::cwd());
}

Forge::Engine::Exports* Forge::Runtime::Isolate::exports(
    const $::String::View& script, const $::Filesystem::Path& hint) {
    auto resource = resolve(script, hint);  // resolve the resource
    return resource.has_value() ? exports(resource.value()) : nullptr;
}

Forge::Engine::Exports* Forge::Runtime::Isolate::exports(const $::URI::View& resource) {
    auto* module = service<Import::Service>()->fetch(resource);
    if (module == nullptr) return panic(8000102, resource.relative()), nullptr;
    return module->metadata<Module::Phase::EXPORTED>();  // can validly return
}

Forge::Value::Any Forge::Runtime::Isolate::global(Value::Symbol symbol) {
    return m_services->get<Globals::Service>()->get(this, symbol);
}

const Forge::String::Intern* Forge::Runtime::Isolate::intern(Value::Symbol symbol) {
    // ensure the underlying frame is valid
    if (m_frame == nullptr) return nullptr;

    // attempt finding the arena reference
    const auto* arena = m_frame->arena();
    if (arena == nullptr) return nullptr;

    auto predicate = [symbol](const String::Intern& intern) { return intern.symbol() == symbol; };
    auto iter = std::ranges::find_if(arena->strings, predicate);  // attempt finding now ...
    return iter == arena->strings.cend() ? nullptr : &*iter;      // ... resolve as necessary
}

Forge::Async::Result Forge::Runtime::Isolate::spawn(Value::Any target) { return spawn(target, {}, {}); }
Forge::Async::Result Forge::Runtime::Isolate::spawn(Value::Any target, const Resource::Trace& trace) {
    return spawn(target, {}, trace);
}

Forge::Async::Result Forge::Runtime::Isolate::spawn(Value::Any target, Function::Arguments&& args) {
    return spawn(target, std::move(args), {});
}

Forge::Async::Result Forge::Runtime::Isolate::spawn(
    Value::Any target, Function::Arguments&& args, const Resource::Trace& trace) {
    // prepare the incoming frame to be used for the execution of the target
    auto frame = trace.anonymous() ? nullptr : $::New().unique<Resource::Frame>(this, trace);

    // ensure we have a valid target to be awaited on
    if (target.is<Async::Future>()) return target.as<Async::Future>().await(thread());
    else if (!target.is<Function::Dynamic>()) return panic(6000201, target.type_name());
    return create<Async::Future>(target.as<Function::Dynamic>(), args).await(thread());
}

Forge::Value::Any Forge::Runtime::Isolate::invoke(Value::Any target) { return invoke(target, {}); }
Forge::Value::Any Forge::Runtime::Isolate::invoke(Value::Any target, const Function::Arguments& args) {
    return Engine::Call::any(this, target, args);
}

Forge::Function::Dynamic Forge::Runtime::Isolate::bind(const Function::Dynamic& callback, Value::Any receiver) {
    // prepare the incoming passthrough callback information
    auto* info = Builtins::Proxy<Function::Dynamic>::binder();

    auto context = Function::Context(this, 1);  // bind
    context.store(0, callback), context.self(receiver);

    // and construct the resulting passthrough handler
    return create<Function::Closure>(info, context);
}

Forge::Resource::Result Forge::Runtime::Isolate::resolve(const $::String::View& script) const {
    return resolve(script, $::System::cwd());
}

Forge::Resource::Result Forge::Runtime::Isolate::resolve(
    const $::String::View& script, const $::Filesystem::Path& hint) const {
    return service<Import::Service>()->resolve(script, hint);
}

Forge::Value::Any Forge::Runtime::Isolate::import(const $::String::View& script, const Resource::Trace& trace) {
    return import(script, $::System::cwd(), trace);
}

Forge::Value::Any Forge::Runtime::Isolate::import(const $::String::View& script, const $::Filesystem::Path& hint) {
    return import(script, hint, {});
}

Forge::Value::Any Forge::Runtime::Isolate::import(
    const $::String::View& script, const $::Filesystem::Path& hint, const Resource::Trace& trace) {
    auto resource = resolve(script, hint);
    if (resource) return import(*resource, trace);
    return panic(8000000, resource.error());
}

Forge::Value::Any Forge::Runtime::Isolate::import(const $::URI::View& resource) { return import(resource, {}); }
Forge::Value::Any Forge::Runtime::Isolate::import(const $::URI::View& resource, const Resource::Trace& trace) {
    auto* result = service<Import::Service>()->import(this, resource, trace);
    return result ? result->await(this) : Value::Failure();  // failed here
}
