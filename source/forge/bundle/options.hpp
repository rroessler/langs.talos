#ifndef _FORGE_BUNDLE_OPTIONS_HPP
#define _FORGE_BUNDLE_OPTIONS_HPP

/// Forge Modules
#include "forge/forward/bundle.hpp"

namespace Forge::Bundle {

    /// @brief Bundler Options.
    struct Options {
        //  PROPERTIES  //

        /// @brief Denotes output should be compiled.
        bool compile = true;

        /// @brief Expected output file to use.
        $::String::Buffer output = "";

        //  CONSTRUCTORS  //

        /// @brief Constructs defaulted options.
        constexpr Options() = default;

        /// @brief Constructs a set of bundle options.
        constexpr Options(std::false_type) : compile(false) {}

        /**
         * @brief Constructs a set of bundle options.
         * @param output            Output file.
         */
        constexpr Options(const $::String::View& output) : output(output) {}
    };

}  // namespace Forge::Bundle

#endif
