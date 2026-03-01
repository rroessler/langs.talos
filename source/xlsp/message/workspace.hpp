#ifndef _XLSP_MESSAGE_WORKSPACE_HPP
#define _XLSP_MESSAGE_WORKSPACE_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"
#include "xlsp/workspace/file.hpp"

namespace XLSP {

    /// @brief Workspace Watched Files Changed Notification.
    template <>
    struct Notification::Params<Message::Type::WORKSPACE_FILE_CHANGED> {
        //  PROPERTIES  //

        /// @brief The current workspace changes that occured.
        std::vector<Workspace::File> changes = {};

        // CONSTRUCTORS  //

        /**
         * @brief Constructs a workspace changed event.
         * @param changes               Changes that occured.
         */
        explicit Params(const std::vector<Workspace::File>& changes) : changes(changes) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding workspace changes.
         * @param value                 JSON to decode.
         */
        static Params m_decode(const $::Serde::Value& value) {
            return Params($::Reflect::decode<Workspace::File>(*value.at<$::Serde::Array>("changes")));
        }
    };

}  // namespace XLSP

#endif
