#ifndef _FORGE_TESTING_TRAITS_HPP
#define _FORGE_TESTING_TRAITS_HPP

/// Forge Modules
#include "forge/forward/testing.hpp"
#include "forge/object/exception.hpp"
#include "forge/resource/trace.hpp"

namespace Forge::Testing::Traits {

    /**
     * @brief Resolves a location from a resource trace.
     * @param trace                 Trace to resolve.
     */
    inline constexpr XT::Location location(const Resource::Trace& trace) {
        auto* position = trace.position();  // resolve baseline
        if (position == nullptr) return { 0, 0, trace.resource() };
        return { position->line, position->column, trace.resource() };
    }

    /**
     * @brief Derives a location from an exception.
     * @param exception             Exception to derive.
     * @param filter                Filters evaluation schemes.
     */
    inline constexpr XT::Location location(const Object::Exception& exception, bool filter = true) {
        // prepare a suitably filter predicate
        auto predicate = [filter](const Resource::Trace& trace) {
            if (trace.anonymous()) return false;  // always fail anonymous items
            return !filter || trace.resource().scheme() != $::URI::Scheme::EVAL;
        };

        // iterate through the exception to find a suitable location
        for (const auto& trace : $::Filter(exception.trace(), predicate)) return location(trace);

        // otherwise we need to an empty trace
        return {};
    }

}  // namespace Forge::Testing::Traits

#endif
