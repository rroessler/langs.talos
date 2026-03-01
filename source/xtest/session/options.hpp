#ifndef _XTEST_SESSION_OPTIONS_HPP
#define _XTEST_SESSION_OPTIONS_HPP

/// XT Includes
#include "xtest/forward/reporter.hpp"
#include "xtest/handle/bench.hpp"

namespace XT::Session {

    /// @brief Core Testing Options.
    struct Options : public XI::Define<Options, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Benchmarking options.
        Bench::Options bench = {};

        /// @brief Main testing title.
        $::String::View title = "xtest/anonymous";

        /// @brief Bound reporter typing.
        Reporter::Tag reporter = Reporter::Tag::DEFAULT;

        /// @brief Handles constructing reporter spinners.
        Reporter::Spinner spinner = [](XI::Container*) { return $::New().unique<$::Spinner::Basic>(); };

        //  CONSTRUCTORS  //

        /// @brief Default Options Constructor.
        constexpr Options() = default;
    };

}  // namespace XT::Session

#endif
