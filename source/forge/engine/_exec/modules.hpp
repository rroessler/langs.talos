/// Forge Modules
#include "forge/engine/exports.hpp"
#include "forge/object/instance.hpp"

/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_EXECUTE(MODULE_OPEN, isolate, frame, instruction) {
    auto module = isolate->exports(frame->resource())->open(isolate);
    return frame->store(instruction->get<0>(), module), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(MODULE_CLOSE, isolate, frame, instruction) {
    auto module = isolate->exports(frame->resource())->close();
    return frame->store(instruction->get<0>(), module), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(MODULE_IMPORT, isolate, frame, instruction) {
    // prepare the import details to be used
    auto path = frame->intern(instruction->get<1>()).view();
    auto trace = frame->backtrace(Resource::Group::IMPORT);
    auto value = isolate->import(path, frame->resource().body(), trace);

    if (!value.traits().okay()) return Mode::PANIC;  // failed import
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(MODULE_EXPORT, isolate, frame, instruction) {
    // ensure we get the underlying exports available
    auto* exports = isolate->exports(frame->resource());
    if (exports == nullptr) return Mode::PANIC;  // failed

    // get the details that we should use for updating
    auto value = frame->load(instruction->get<0>());
    auto name = frame->intern(instruction->get<1>());

    // get the underlying fields to be updated now
    auto& fields = exports->current().as<Object::Instance>().fields();
    auto exists = $_UNLIKELY(fields.contains(name.symbol()));  // check
    if (exists) return isolate->panic(8000301, name.view()), Mode::NEXT;

    // construct and emplace the field to be used now
    auto reference = $::New().unique<Member::Reference>(value);
    return fields.emplace(name.symbol(), std::move(reference)), Mode::NEXT;
}
