#ifndef _XLSP_MESSAGE_SPECIAL_HPP
#define _XLSP_MESSAGE_SPECIAL_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"

namespace XLSP {

    /// @brief Cancellation parameters.
    template <>
    struct Notification::Params<Message::Type::$_CANCEL> {
        //  PROPERTIES  //

        /// @brief Underlying cancellation identifier.
        $::String::Buffer identifier = "";

        //  CONSTRUCTORS  //

        /// @brief Constructs the defaulted cancellation details.
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

            // attempt getting a suitable identifier now
            params.identifier = *value.at<$::Serde::Text>("id");

            // return the resulting parameters
            return params;
        }
    };

}  // namespace XLSP

#endif
