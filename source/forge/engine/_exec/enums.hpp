/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Forge::Value::Any Forge::Engine::Dispatch::m_enumeration(
    Isolate* isolate, const std::span<Value::Any>& tuples) {
    $_ASSERT(tuples.size() % 3 == 0, "Expected tuples");

    // prepare the variants to be emplaced
    auto variants = std::vector<Object::Variant>();

    // prepare a resolution for incremental values
    static auto increment = [](const Object::Variant& variant) -> Number::Tagged {
        auto ordinal = variant.value->reference().as<Number::Tagged>();
        return Number::Tagged(ordinal.value() + 1);  // increment ordinal
    };

    // attempt assigning our values now
    for (size_t ii = 0; ii < tuples.size();) {
        auto name = tuples[ii++].as<String::Dynamic>();
        auto label = tuples[ii++].as<String::Dynamic>();
        auto value = tuples[ii++];  // value needs resolving

        // check if the incoming value is void (eg: unassigned)
        if (value.is<Value::Void>()) value = variants.empty() ? Number::Tagged(0) : increment(variants.back());

        auto reference = $::New().unique<Member::Reference>(value);  // construct the incoming reference
        variants.emplace_back(Object::Variant{ .name = name, .label = label, .value = std::move(reference) });
    }

    // and finally construct and load the enumeration now
    return isolate->create<Object::Enum>(std::move(variants));
}

FORGE_MM_ENGINE_EXECUTE(ENUM_EMPTY, isolate, frame, instruction) {
    auto enumeration = isolate->create<Object::Enum>();  // construct
    return frame->store(instruction->get<0>(), enumeration), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(ENUM_MAKE, isolate, frame, instruction) {
    auto enumeration = m_enumeration(isolate, frame->span(instruction->get<1>()));
    return frame->store(instruction->get<0>(), enumeration), Mode::NEXT;  // build
}
