/// Talos Modules
#include "talos/engine/exports.hpp"
#include "talos/member/factory.hpp"
#include "talos/object/instance.hpp"

/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Talos::Value::Any Talos::Engine::Dispatch::m_expose(
    Runtime::Isolate* isolate, Exports* exports, Value::Any value, const String::Intern* intern) {
    return exports ? m_expose(isolate, exports->current().as<Object::Instance>(), value, intern) : Value::Failure();
}

$_INLINE_FORCE Talos::Value::Any Talos::Engine::Dispatch::m_expose(
    Runtime::Isolate* isolate, Object::Instance exports, Value::Any value, const String::Intern* intern) {
    auto& fields = exports.fields();  // resolve the fields now
    auto exists = $_UNLIKELY(fields.contains(intern->symbol()));
    if (exists) return isolate->panic(8000301, intern->view());

    // construct and emplace the field to be used now
    auto reference = Member::Factory::reference(Value::Any(value));
    return fields.emplace(intern->symbol(), std::move(reference)), Value::Void();
}

TALOS_MM_ENGINE_EXECUTE(MODULE_OPEN, isolate, frame, instruction) {
    auto module = isolate->exports(frame->resource())->open(isolate);
    return frame->store(instruction->get<0>(), module), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(MODULE_CLOSE, isolate, frame, instruction) {
    auto module = isolate->exports(frame->resource())->close();
    return frame->store(instruction->get<0>(), module), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(MODULE_BARREL, isolate, frame, instruction) {
    // prepare the base output exports to be used
    auto* module = isolate->exports(frame->resource());
    if (module == nullptr) return Mode::PANIC;  // bad

    // get the underlying module instances to be barrel exported now
    auto& exports = module->current().as<Object::Instance>().fields();
    auto barrel = frame->load<Object::Instance>(instruction->get<0>());

    // iterate over the available barrel fields now
    for (const auto& [key, value] : barrel.fields()) {
        if (exports.contains(key)) return isolate->panic(8000302), Mode::PANIC;
        exports.emplace(key, Member::Factory::reference(value->reference()));
    }

    // once complete, declare as a success now
    return Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(MODULE_IMPORT, isolate, frame, instruction) {
    // prepare the import details to be used
    auto path = frame->intern(instruction->get<1>()).view();
    auto trace = frame->backtrace(Resource::Group::IMPORT);
    auto value = isolate->import(path, frame->resource().body(), trace);

    if (!value.traits().okay()) return Mode::PANIC;  // failed import
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(MODULE_EXPORT, isolate, frame, instruction) {
    // ensure we get the underlying exports available
    auto* exports = isolate->exports(frame->resource());
    if (exports == nullptr) return Mode::PANIC;  // failed

    // get the details that we should use for updating
    auto value = frame->load(instruction->get<0>());
    auto name = frame->intern(instruction->get<1>());

    // attempt exporting the current value now
    auto result = m_expose(isolate, exports, value, &name);
    return result.traits().okay() ? Mode::NEXT : Mode::PANIC;
}
