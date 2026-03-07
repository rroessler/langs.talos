/// Talos Modules
#include "talos/runtime/main.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/module/service.hpp"

//  PRIVATE METHODS  //

$_NORETURN void Talos::Runtime::Main::m_execute() {
    // force our runtime to preload the lifecycle now
    $_UNUSED $_AUTO = service<Lifecycle::Service>()->scope(this);

    // get the incoming resource to be run now
    auto script = service<Runtime::Options>()->script.entry;

    // and attempt handling the incoming results now
    if (auto result = m_import(script); result.traits().okay()) m_thread->shutdown($_EXIT_SUCCESS);

    // pull out the incoming exception to be printed
    auto exception = m_exception.as<Object::Exception>();
    $::IO::cerr() << $::Dye::red("Unhandled ");
    exception.format($::IO::cerr()) << '\n';

    // and fail since we did not handle our exception
    m_thread->shutdown($_EXIT_FAILURE);
}

void Talos::Runtime::Main::m_analyze(const $::URI::Buffer& resource) {
    if (options()->flags.typeless) return;  // stop if ignoring types
    auto stats = service<Import::Service>()->analyze(resource, true);

    if (stats.errors) m_thread->shutdown($_EXIT_FAILURE);
    else if (stats.hints) $::IO::eprintln();  // padding
}

Talos::Value::Any Talos::Runtime::Main::m_import(const $::String::View& script) {
    auto resource = resolve(script, $::System::cwd());  // resolve now
    if (!resource.has_value()) return panic(8000000, resource.error());
    return m_analyze(resource.value()), import(resource.value());
}
