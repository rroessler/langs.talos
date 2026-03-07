#ifndef _TALOS_TESTING_OPTIONS_HPP
#define _TALOS_TESTING_OPTIONS_HPP

/// Talos Modules
#include "talos/forward/testing.hpp"

namespace Talos::Testing {

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

}  // namespace Talos::Testing

#endif
