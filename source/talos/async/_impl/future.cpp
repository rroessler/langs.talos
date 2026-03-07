/// Talos Modules
#include "talos/async/service.hpp"
#include "talos/async/worker.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Object::Attributes<Talos::Async::Future>::Attributes(Runtime::Isolate* callee, Function::Dynamic callback) :
    Attributes(callee, callback, {}) {}

Talos::Object::Attributes<Talos::Async::Future>::Attributes(
    Runtime::Isolate* isolate, Function::Dynamic callback, Function::Arguments&& passthrough) :
    callback(callback), arguments(std::move(passthrough)), thenable($::New().unique<Async::Thenable>()) {
    m_initialize(isolate);
}

Talos::Object::Attributes<Talos::Async::Future>::Attributes(
    Runtime::Isolate* isolate, Function::Dynamic callback, const Function::Arguments& passthrough) :
    callback(callback), arguments(passthrough), thenable($::New().unique<Async::Thenable>()) {
    m_initialize(isolate);
}

//  PUBLIC METHODS  //

Talos::Async::Result Talos::Async::Future::timeout(Thread* thread, const $::Chrono::Duration& duration) const noexcept {
    auto timer = m_timeout(duration);
    auto result = thenable()->await(thread);
    if (timer == nullptr) return result;
    if (timer->cancel(thread)) return result;
    return std::unexpected(Value::Timeout());
}

Talos::Value::Any Talos::Async::Future::timeout(
    Runtime::Isolate* isolate, const $::Chrono::Duration& duration) const noexcept {
    auto timer = m_timeout(duration);
    auto value = thenable()->await(isolate);
    if (timer == nullptr) return value;
    if (timer->cancel(isolate->thread())) return value;
    return isolate->panic(6000101);
}

Talos::Async::Result Talos::Async::Future::await(Thread* thread) const noexcept { return thenable()->await(thread); }
Talos::Value::Any Talos::Async::Future::await(Runtime::Isolate* isolate) const noexcept {
    return thenable()->await(isolate);
}

//  PRIVATE METHODS  //

void Talos::Object::Attributes<Talos::Async::Future>::m_initialize(Runtime::Isolate* isolate) {
    // prepare the services to be used now
    auto* services = isolate->service<XI::Container>();
    auto* async = isolate->service<Async::Service>();

    // get the associated address now
    auto pointer = std::bit_cast<Pointer::Underlying>(this);
    pointer |= static_cast<Pointer::Underlying>(Pointer::Kind::OBJ);

    auto local_scope = isolate->scope();  // prepare scoping
    auto local_future = local_scope(Async::Future(pointer));

    auto* frame = isolate->frame();  // prepare the resource trace
    auto anonymous = frame == nullptr || callback.resource() == $::URI::Anonymous();
    auto trace = anonymous ? Resource::Trace() : frame->backtrace();  // build trace

    // and attempt scheduling the future now
    auto* processor = isolate->thread()->worker()->processor();
    worker = async->spawn<Async::Worker>(processor, services, *local_future, trace);
}

void Talos::Async::Future::m_yield(const Future& self, const Globals::Each& yield) {
    // get the attributes now
    auto* attributes = self.m_attrs();

    // bind all the underlying values
    yield(attributes->arguments.self());
    yield(attributes->arguments.span());

    // thenables are conditional here
    if (attributes->thenable) yield(attributes->thenable->immediate());
}

Talos::Async::Timeout Talos::Async::Future::m_timeout(const $::Chrono::Duration& duration) const noexcept {
    // attempt getting the underlying worker
    auto* worker = m_attrs()->worker;
    if (worker == nullptr) return nullptr;

    // prepare the async handler now
    auto* async = worker->service<Async::Service>();

    // prepare the callback to be executed
    auto callback = [worker](Thread*, Processor*) { worker->interrupt(); };

    // finally attempt constructing the timeout now
    return async->timeout(duration, std::move(callback));
}
