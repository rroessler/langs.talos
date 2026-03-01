#ifndef _FORGE_RELINT_OPTIONS_HPP
#define _FORGE_RELINT_OPTIONS_HPP

/// Forge Modules
#include "forge/diagnostic/traits.hpp"
#include "forge/forward/relint.hpp"

namespace Forge::Relint {

    /// @brief Linter Options.
    struct Options {
        //  PROPERTIES  //

        /// @brief Enables all the recommended options.
        bool recommended = true;

        /// @brief The rules override severities to be enabled.
        $::Dict<Severity> rules = {};

        /// @brief The available rules to be enabled.
        std::vector<$::String::Buffer> plugins = {};

        /// @brief Available rule overrides ignores reporters.
        $::Map<Diagnostic::Code, Severity> overrides = {};

        //  CONSTRUCTORS  //

        /// @brief Linting options to use.
        constexpr Options() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding linting options.
         * @param value                     Value to decode.
         */
        static Options m_decode(const $::Serde::Value& value) {
            // prepare the default options now
            auto options = Options();

            // stop-fast if there is no valid object
            if (!value.is<$::Serde::Object>()) return options;

            // pull out the details we could be using
            auto* rules = value.at<$::Serde::Object>("rules");
            auto* plugins = value.at<$::Serde::Array>("plugins");
            auto* overrides = value.at<$::Serde::Object>("overrides");
            auto* recommended = value.at<$::Serde::Boolean>("recommended");

            // and assign the values if possible to do so
            if (recommended) options.recommended = *recommended;
            if (rules) options.rules = m_decode<$::Serde::Text>(*rules);
            if (overrides) options.overrides = m_decode<Diagnostic::Code>(*overrides);
            if (plugins) options.plugins = $::Reflect::decode<$::Serde::Text>(*plugins);

            // and return the resulting options now
            return m_overrides(options), options;
        }

        /**
         * @brief Handles decoding severity maps.
         * @param object                    Object to decode.
         */
        template <class K>
        static $::Map<K, Severity> m_decode(const $::Serde::Object& object) {
            // prepare the output mapping to be used
            auto output = $::Map<K, Severity>();

            // iterate over the current mapping now
            for (const auto& [key, value] : object) {
                // attempt getting the current severity
                auto severity = m_severity(value);
                if (!severity.has_value()) continue;

                if (!value.is<$::Serde::Text>()) continue;  // ignore non-string values
                if constexpr (std::same_as<K, $::Serde::Text>) output[key] = *severity;
                else if (auto code = m_diagnostic(key)) output[*code] = *severity;  // coded
            }

            // return the resulting mapping now
            return output;
        }

        /**
         * @brief Handles defining override aliases.
         * @param options                   Options to update.
         */
        static void m_overrides(Options& options);

        /**
         * @brief Handles decoding diagnostic codes.
         * @param buffer                    Buffer to decode.
         * @param index                     Helper index value.
         */
        static std::optional<Diagnostic::Code> m_diagnostic(const $::String::Buffer& buffer, size_t index = 0) {
            std::optional<Diagnostic::Code> result = std::stoi(buffer, &index);
            if (index != buffer.size()) return std::nullopt;  // failed to parse
            return Diagnostic::Traits::overridable(*result) ? result : std::nullopt;
        }

        /**
         * @brief Handles decoding severities.
         * @param value                     Value to decode.
         */
        static std::optional<Severity> m_severity(const $::Serde::Value& value) {
            // get the underlying text-value to be used
            auto text = value.as<$::Serde::Text>();

            // ignore if the incoming value is not text at all
            if (text == nullptr) return std::nullopt;

#define X(N, ...) \
    case XH::FNV::U64(#N): return Severity::N;
            switch (XH::FNV::U64($::Convert::uppercase(*text))) {
                XLSP_XX_DIAGNOSTIC_SEVERITIES(X) default : return std::nullopt;
            }
#undef X
        }
    };  // namespace Forge::Relint

}  // namespace Forge::Relint

#endif
