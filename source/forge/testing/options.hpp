#ifndef _FORGE_TESTING_OPTIONS_HPP
#define _FORGE_TESTING_OPTIONS_HPP

/// Forge Modules
#include "forge/forward/testing.hpp"

namespace Forge::Testing {

    /// @brief Testing Options Available.
    struct Options {
        //  PROPERTIES  //

        /// @brief Denotes if randomizing testing.
        bool randomize = false;

        /// @brief Bailout total for testing.
        size_t bailout = 0;

        /// @brief Benchmarking options available.
        XT::Bench::Options bench = {};

        /// @brief The baseline pattern to use.
        $::String::Buffer pattern = "**/*.test.tal";

        /// @brief Available filters to apply to files.
        std::vector<$::String::Buffer> filters = {};

        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        constexpr Options() = default;
    };

}  // namespace Forge::Testing

#endif
