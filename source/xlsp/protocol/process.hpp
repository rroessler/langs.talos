#ifndef _XLSP_PROTOCOL_PROCESS_HPP
#define _XLSP_PROTOCOL_PROCESS_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

namespace XLSP::Process {

    /// @brief Client/Server Process Information.
    struct Information {
        //  PROPERTIES  //

        /// @brief Name of client.
        $::String::Buffer name = "";

        /// @brief Client version.
        std::optional<$::String::Buffer> version = std::nullopt;

        //  CONSTRUCTORS  //

        /// @brief Default constructs the information.
        explicit Information() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Encodes the server information JSON.
         * @param info                          Information to encode.
         */
        static $::Serde::Value m_encode(const Information& info) {
            $::Serde::Object structure = { { "name", info.name } };
            if (info.version.has_value()) structure["version"] = *info.version;
            return structure;  // return the finally encoded value
        }

        /**
         * @brief Decodes the client information JSON.
         * @param value                         Information to decode.
         */
        static Information m_decode(const $::Serde::Value& value) {
            // get the base object instance now
            auto info = Information();

            // set the current name to be used
            info.name = *value.at<$::Serde::Text>("name");

            // attempt parsing some additional items now
            if (auto* version = value.at<$::Serde::Text>("version")) info.version = *version;

            // and return the resulting information
            return info;
        }
    };

}  // namespace XLSP::Process

#endif