/// Forge Modules
#include "forge/bundle/codec.hpp"

//  CONSTRUCTORS  //

Forge::Bundle::Filesystem::Filesystem(const std::vector<Linker::Arena*>& arenas) {
    // reserve the size of the scripts
    scripts.reserve(arenas.size());

    // iterate over the arenas and clone them
    for (const auto* arena : arenas) {
        // pre-emplace the URI resource but do not use
        resources.emplace_back(arena->resource.buffer());

        // construct a new arena instance now
        auto* script = scripts.emplace_back($::New().unique<Linker::Arena>()).get();

        // update all the non-copyable components
        script->strings = arena->strings;
        script->bytecode = arena->bytecode;
        script->resource = arena->resource;
        script->constants = arena->constants;

        // ensure we reserve the functions sizing
        script->functions.reserve(arena->functions.size());

        // copy across the functions now
        for (const auto& function : arena->functions) {
            auto buffer = function->buffer();  // prepare the buffer to be copied now
            auto info = $::New().unique<Function::Info>(script, *function->shared());
            info->buffer() = script->bytecode.view(buffer.offset(), buffer.size());
            script->functions.emplace_back(std::move(info));  // and emplace the function
        }
    }
}