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

            // get the baseline identifier value
            auto identifier = value.at("id");

            // attempt getting a suitable identifier now
            if (auto* _ = value.as<$::Serde::Text>()) params.identifier = *_;
            if (auto* _ = value.as<$::Serde::Number>()) params.identifier = fmt::to_string(*_);

            // return the resulting parameters
            return params;
        }
    };

}  // namespace XLSP

#endif
