#ifndef _TALOS_BUNDLE_OPTIONS_HPP
#define _TALOS_BUNDLE_OPTIONS_HPP

/// Talos Modules
#include "talos/forward/bundle.hpp"

namespace Talos::Bundle {

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

}  // namespace Talos::Bundle

#endif
