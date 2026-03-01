/// Forge Modules
#include "forge/bundle/archive.hpp"
#include "forge/bundle/codec.hpp"
#include "forge/module/service.hpp"

//  PRIVATE METHODS  //

Forge::Bundle::Buffer Forge::Bundle::Archive::m_encode(Import::Service* modules) const noexcept {
    // ensure we have a set of services as well
    $_ASSERT(!headless(), "Encoding modules archives requires a services container");

    // prepare a list of futures for compilation
    auto futures = std::vector<std::future<Linker::Arena*>>();

    // attempt compiling each of the incoming files now
    for (auto& module : modules->drafts()->each()) {
        if (!module->is<Module::Script>()) continue;
        futures.emplace_back(m_compile(module.get()));
    }

    // prepare the outgoing filesystem instance
    auto arenas = std::vector<Linker::Arena*>();
    arenas.reserve(futures.size());  // prebuild

    // wait for all the futures to be completed
    for (auto& future : futures) arenas.emplace_back(future.get());

    // finally encode the incoming filesystem now
    return encode(Filesystem(arenas));
}

std::future<Forge::Linker::Arena*> Forge::Bundle::Archive::m_compile(Module::Interface* module) const noexcept {
    return std::async(std::launch::async, &Module::Interface::compile, module, m_services);
}