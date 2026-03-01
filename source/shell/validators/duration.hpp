#ifndef _SHELL_VALIDATORS_DURATION_HPP
#define _SHELL_VALIDATORS_DURATION_HPP

/// Vendor Modules
#include <CLI/CLI.hpp>
#include <xtdlib/xtdlib.hpp>

namespace Shell::Validator {

    /// @brief Helper Duration Validator.
    struct Duration : public CLI::Validator {
        //  CONSTRUCTORS  //

        /// @brief Constructs a duration validator.
        explicit Duration() : Validator(m_transform, "TIME [UNIT]") {}

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles transforming durations.
         * @param input                     Input to transform.
         */
        static inline $::String::Buffer m_transform($::String::Buffer& input) {
            CLI::detail::rtrim(input);  // ensure we trim the input beforehand
            if (input.empty()) throw CLI::ValidationError("Input is empty");

            auto start = input.end();  // attempt finding the starting point of the unit
            while (start > input.begin() && std::isalpha(*(start - 1), std::locale())) --start;

            $::String::Buffer unit = $::Convert::lowercase({ start, input.end() });
            input.resize(std::distance(input.begin(), start));  // resize the input

            // prepare the baseline duration to be used
            int64_t duration = {}, multiplier = m_multiplier(unit);

            // attempt casting to a suitably duration now
            auto success = CLI::detail::lexical_cast(input, duration);

            // if the unit is empty, then resolve in milliseconds
            if (!success) throw CLI::ValidationError("Value " + input + " could not be converted to TIME [UNIT]");
            if (multiplier < 0) throw CLI::ValidationError("Unit '" + unit + "' not recognized");  // invalid

            // since validly converted, then apply the multiplication and return as a stringified value
            input = CLI::detail::to_string(duration * multiplier);

            // and declare that no errors occured now
            return {};
        }

        /**
         * @brief Handles getting a suitable multiplier.
         * @param unit                  Unit to convert.
         */
        static inline int64_t m_multiplier(const $::String::View& unit) {
            // prepare the output multiplier to be used
            int64_t multiplier = 1;

            // and use a switch case to suitably multiply our values
            switch (XH::FNV::U64(unit)) {
                case XH::FNV::U64("h"): $_PP_NOOP(); $_FALLTHROUGH;
                case XH::FNV::U64("hh"): multiplier *= 60; $_FALLTHROUGH;

                case XH::FNV::U64("m"): $_PP_NOOP(); $_FALLTHROUGH;
                case XH::FNV::U64("mm"): multiplier *= 60; $_FALLTHROUGH;

                case XH::FNV::U64("s"): $_PP_NOOP(); $_FALLTHROUGH;
                case XH::FNV::U64("ss"): multiplier *= 1000; $_FALLTHROUGH;

                case XH::FNV::U64(""): $_PP_NOOP(); $_FALLTHROUGH;
                case XH::FNV::U64("ms"): multiplier *= 1000; $_FALLTHROUGH;
                case XH::FNV::U64("us"): multiplier *= 1000; $_FALLTHROUGH;
                case XH::FNV::U64("ns"): return multiplier;

                // declare an invalid multiplier
                default: return -1;
            }
        }
    };

}  // namespace Shell::Validator

#endif
