#ifndef _FORGE_CRATES_MANIFEST_HPP
#define _FORGE_CRATES_MANIFEST_HPP

/// Forge Modules
#include "forge/format/options.hpp"
#include "forge/forward/crate.hpp"
#include "forge/relint/options.hpp"

//  X-MACROS  //

#define XX_CRATE_OPTIONALS(X)        \
    X(title, $::String::Buffer)      \
    X(describe, $::String::Buffer)   \
                                     \
    X(issues, $::String::Buffer)     \
    X(homepage, $::String::Buffer)   \
    X(repository, $::String::Buffer) \
    X(documentation, $::String::Buffer)

#define XX_CRATE_DICTIONARIES(X)      \
    X(tasks, $::String::Buffer)       \
    X(constraints, $::String::Buffer) \
    X(dependencies, $::String::Buffer)

namespace Forge::Crate {

    //  TYPEDEFS  //

    /// @brief Crate File Manifest.
    class Manifest {
        //  PROPERTIES  //

        $::String::Buffer m_name = "@forge/unknown";   // Associated crate-name.
        $::String::Buffer m_version = "0.0.0";         // Specification version.
        $::String::Buffer m_path = $::System::root();  // Prepare the base-path.

        /// @brief Explicit main script.
        std::optional<$::String::Buffer> m_main = std::nullopt;

#define X(N, T, ...) std::optional<T> m_##N = std::nullopt;
        XX_CRATE_OPTIONALS(X)
#undef X

#define X(N, T, ...) $::Dict<T> m_##N = {};
        XX_CRATE_DICTIONARIES(X)
#undef X

        /// @brief Incoming linting options.
        Relint::Options m_lint = {};

        /// @brief Incoming formatter options.
        Format::Options m_format = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of default options.
        constexpr Manifest() = default;

        /**
         * @brief Constructs options with a path.
         * @param path                  Crate options path.
         */
        constexpr Manifest(const $::String::Buffer& path) : m_path(path) {}

        //  PUBLIC METHODS  //

        inline constexpr $::String::Buffer& path() { return m_path; }
        inline constexpr $::String::View path() const { return m_path; }

        inline constexpr $::String::View name() const { return m_name; }
        inline constexpr $::String::View version() const { return m_version; }

        inline constexpr const Relint::Options& lint() const noexcept { return m_lint; }
        inline constexpr const Format::Options& format() const noexcept { return m_format; }
        inline constexpr std::optional<$::URI::Buffer> main() const { return m_resolve(m_main); }

#define X(N, T, ...) \
    inline constexpr $::String::View N() const noexcept { return m_##N.has_value() ? $::String::View(*m_##N) : ""; }
        XX_CRATE_OPTIONALS(X)
#undef X

#define X(N, T, ...) \
    inline constexpr const $::Dict<T>& N() const noexcept { return m_##N; }
        XX_CRATE_DICTIONARIES(X)
#undef X

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Resolves crate-paths against the root.
         * @param relative                  Relative path.
         */
        std::optional<$::URI::Buffer> m_resolve(const std::optional<$::String::Buffer>& relative) const;

        /**
         * @brief Handles decoding crate options.
         * @param value                     Value to decode.
         */
        static Manifest m_decode(const $::Serde::Value& value, const $::String::Buffer& path = $::System::root()) {
            // get the underlying options to be output
            auto options = Manifest(path);

            // stop-fast if there is no valid value
            if (!value.is<$::Serde::Object>()) return options;

            // otherwise attempt destructing now
            if (auto* name = value.at<$::Serde::Text>("name")) options.m_name = *name;
            if (auto* version = value.at<$::Serde::Text>("version")) options.m_version = *version;
            if (auto* main = value.at<$::Serde::Text>("main")) options.m_main = *main;

#define X(N, T, ...) \
    if (auto* N = value.at<T>(#N)) options.m_##N = *N;
            XX_CRATE_OPTIONALS(X)  // set the optional values as necessary now
#undef X

#define X(N, T, ...) \
    if (auto* N = value.at<$::Serde::Object>(#N)) options.m_##N = $::Reflect::decode<T>(*N);
            XX_CRATE_DICTIONARIES(X)  // attempt reading all the dictionary values now
#undef X

            // destructure the more complex items now
            options.m_lint = $::Reflect::decode<Relint::Options>(value.at("lint"));
            options.m_format = $::Reflect::decode<Format::Options>(value.at("format"));

            // resolve the final crate value now
            return options;
        }
    };

}  // namespace Forge::Crate

//  UNDEFINES  //

#undef XX_CRATE_OPTIONALS
#undef XX_CRATE_DICTIONARIES

#endif
