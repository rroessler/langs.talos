/// Talos Modules
#include "talos/signal/service.hpp"

//  CONSTRUCTORS  //

Talos::Signal::Service::Service(XI::Container* services) : m_async(services->get<Async::Service>()) {
    m_async->signals()->bind([&](const XSIO::Signal::Code& code) { return m_dispatch(code); });
}

//  PRIVATE METHODS  //

void Talos::Signal::Service::m_dispatch(const XSIO::Signal::Code& code) {
    /// TODO: check if we can catch the incoming code at all
    if (auto* isolate = m_async->isolate(); isolate && !m_handler.is<Value::Void>()) $_ABORT("UNIMPLEMENTED");

    // attempt stopping all the running threads
    for (const auto& thread : m_async->scheduler()->threads()) {
        if (!thread->is<Runtime::Executor>()) continue;  // should cast
        reinterpret_cast<Runtime::Executor*>(thread->task())->interrupt();
    }

    // and now we can safely exit the routine as necessary
    m_async->exit($_EXIT_CUSTOM(code.underlying()));
    if (!$_PLATFORM_WINDOWS) $::IO::eprintln();
}
