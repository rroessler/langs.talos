#ifndef _XLSP_MESSAGE_TRACE_HPP
#define _XLSP_MESSAGE_TRACE_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/trace.hpp"

namespace XLSP {

    /// @brief Incoming Trace-set values.
    template <>
    struct Notification::Params<Message::Type::TRACE_SET> {
        //  PROPERTIES  //

        /// @brief Underlying trace-value.
        Trace::Value value = Trace::Value::OFF;

        //  CONSTRUCTORS  //

        /// @brief Constructs the defaulted trace parameters.
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
            params.value = Trace::resolve(*value.at<$::Serde::Text>("value"));

            // return the resulting parameters
            return params;
        }
    };

    /// @brief Handles incoming trace-logs.
    template <>
    struct Notification::Params<Message::Type::TRACE_LOG> {
        //  PROPERTIES  //

        /// @brief Message to be logged.
        $::String::Buffer message = "";

        /// @brief Additional tracing details.
        std::optional<$::String::Buffer> verbose = std::nullopt;

        //  CONSTRUCTORS  //

        /// @brief Constructs the defaulted trace parameters.
        explicit Params() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding trace logs.
         * @param trace                     Trace details.
         */
        static $::Serde::Value m_encode(const Params& trace) {
            $::Serde::Object value = { { "message", trace.message } };
            if (trace.verbose.has_value()) value.emplace("verbose", *trace.verbose);
            return value;  // and return the resulting trace log parameters
        }
    };

}  // namespace XLSP

#endif
