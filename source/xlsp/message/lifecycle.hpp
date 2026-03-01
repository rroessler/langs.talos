#ifndef _XLSP_MESSAGE_LIFECYCLE_HPP
#define _XLSP_MESSAGE_LIFECYCLE_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/process.hpp"
#include "xlsp/workspace/folder.hpp"

namespace XLSP {

    /// @brief Initialize Request Parameters.
    template <>
    struct Request::Params<Message::Type::LIFECYCLE_INITIALIZE> {
        //  PROPERTIES  //

        /// @brief Process ID of the parent process that started the server.
        int64_t ppid = -1;

        /// @brief The locale the client is currently showing the user-interface in.
        $::String::Buffer locale = "";

        /// @brief Available workspace folders.
        std::vector<Workspace::Folder> workspaces = {};

        /// @brief Client capabilities.
        $::Serde::Object capabilities = $::Serde::Object();

        /// @brief Client information.
        std::optional<Process::Information> client = std::nullopt;

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted initialize request.
        explicit Params() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the initialize request parameters.
         * @param json                          JSON to request.
         */
        static Params m_decode(const $::Serde::Value& value) {
            // prepare the base parameters structure
            auto params = Params();

            // ensure we have the base information now
            auto info = value.at("clientInfo");
            auto capabilities = value.at("capabilities");

            // attempt assigning each of our details
            if (auto* locale = value.at<$::Serde::Text>("locale")) params.locale = *locale;
            if (auto* ppid = value.at<$::Serde::Number>("processId")) params.ppid = static_cast<int64_t>(*ppid);

            // some items require larger details to be parsed now
            if (auto* result = capabilities.as<$::Serde::Object>()) params.capabilities = *result;
            if (info.is<$::Serde::Object>()) params.client = $::Reflect::decode<Process::Information>(info);

            // return the resulting parameters
            return params;
        }
    };

    /// @brief Denotes the initialize response.
    template <>
    struct Response::Value<Message::Type::LIFECYCLE_INITIALIZE> {
        //  PROPERTIES  //

        /// @brief Server capabilities.
        $::Serde::Object capabilities = $::Serde::Object();

        /// @brief Server Information.
        std::optional<Process::Information> server = std::nullopt;

        //  CONSTRUCTORS  //

        /// @brief Constructs the defaulted initialize response.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the initialize response JSON.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value& response) {
            $::Serde::Object structure = { { "capabilities", response.capabilities } };
            if (response.server.has_value()) structure["serverInfo"] = $::Reflect::encode(*response.server);
            return structure;  // return the final structure to be used now
        }
    };

    /// @brief Denotes the initialized notification.
    XLSP_MESSAGE_EMPTY(Notification::Params, LIFECYCLE_INITIALIZED){};

    /// @brief Denotes the initialized notification.
    XLSP_MESSAGE_EMPTY(Request::Params, LIFECYCLE_SHUTDOWN){};

    /// @brief Denotes the initialized notification.
    XLSP_MESSAGE_NULLISH(Response::Value, LIFECYCLE_SHUTDOWN){};

    /// @brief Denotes the initialized notification.
    XLSP_MESSAGE_EMPTY(Notification::Params, LIFECYCLE_EXIT){};

}  // namespace XLSP

#endif
