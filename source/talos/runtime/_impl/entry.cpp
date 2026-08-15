/// Talos Includes
#include "talos/runtime/entry.hpp"
#include "talos/import/service.hpp"
#include "talos/lifecycle/service.hpp"

//  PRIVATE METHODS  //

$_NORETURN void Talos::Runtime::Entry::m_execute() {
  // prepare the incoming runtime
  $_UNUSED $_AUTO = service<Lifecycle::Service>()->scope(this);

  // get the incoming resource to be run now
  auto script = options()->script.entry;
  auto result = m_import(script).pointer().okay();

  // attempt importing the incoming script
  if (result) m_thread->shutdown(EXIT_SUCCESS);

  // pull out the incoming exception to be printed
  auto exception = m_exception.as<Object::Exception>();
  std::cerr << $::Dye::red("Unhandled ");
  exception.format(std::cerr) << std::endl;

  // declare as a failure since received an exception
  m_thread->shutdown(EXIT_FAILURE);
}

Talos::Value::Any Talos::Runtime::Entry::m_import(const $::String::View &script) {
  auto resource = resolve(script, $::System::cwd()); // resolve the resource
  return resource ? m_analyze(*resource) : panic(8000000, resource.error());
}

Talos::Value::Any Talos::Runtime::Entry::m_analyze(const $::URI::Buffer &resource) {
  // only attempt analyzing if not in typeless mode
  if (!options()->flags.typeless) {
    Import::Service *modules = *m_services;
    auto stats = modules->analyze(resource, true);
    if (stats.errors) m_thread->shutdown(EXIT_FAILURE);
    else if (stats.hints) $::Debug::eprintln(); // pad
  }

  // and finally attempt interpreting now
  return import(resource);
}
