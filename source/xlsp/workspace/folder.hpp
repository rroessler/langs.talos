#ifndef _XLSP_WORKSPACE_FOLDER_HPP
#define _XLSP_WORKSPACE_FOLDER_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

namespace XLSP::Workspace {

    /// @brief Workspace Folders Structure.
    struct Folder {
        //  PROPERTIES  //

        /// @brief Associated URI of the workspace folder.
        $::URI::Buffer resource;

        /// @brief Name of the workspace folder.
        $::String::Buffer name;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a workspace folder.
         * @param uri                           URI value.
         * @param identifier                    Workspace name.
         */
        explicit constexpr Folder(const $::URI::Buffer& uri, const $::String::Buffer& identifier) :
            resource(uri), name(identifier) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding workspace folders.
         * @param value                         Value to decode.
         */
        static Folder m_decode(const $::Serde::Value& value) {
            return Folder($::Reflect::decode<$::URI::Buffer>(value.at("uri")), *value.at<$::Serde::Text>("name"));
        }
    };

}  // namespace XLSP::Workspace

#endif