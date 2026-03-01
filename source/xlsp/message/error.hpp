#ifndef _XLSP_MESSAGE_ERROR_HPP
#define _XLSP_MESSAGE_ERROR_HPP

/// XLSP Includes
#include "xlsp/message/traits.hpp"

/// Forward Definitions
$_FWD(template <class T> using Result = std::variant<T $_PP_COMMA Error>, XLSP::Message)

//  X-MACROS  //

#define XX_ERROR_CODES(X)                                                                                         \
    X(PARSE_ERROR, -32700)                                                                                        \
    X(INVALID_REQUEST, -32600)                                                                                    \
    X(METHOD_MISSING, -32601)                                                                                     \
    X(INVALID_PARAMS, -32602)                                                                                     \
    X(INTERNAL_ERROR, -32603)                                                                                     \
                                                                                                                  \
    X(JRPC_RESERVED_ERROR_RANGE_BEG, -32099)                                                                      \
    X(SERVER_UNINITIALIZED, -32002)                                                                               \
    X(UNKNOWN_ERROR_CODE, -32001)                                                                                 \
    X(JRPC_RESERVED_ERROR_RANGE_END, -32000)                                                                      \
                                                                                                                  \
    X(SERVER_ERROR_BEG $_DEPRECATED("Use: JRPC_RESERVED_ERROR_RANGE_BEG instead"), JRPC_RESERVED_ERROR_RANGE_BEG) \
    X(SERVER_ERROR_END $_DEPRECATED("Use: JRPC_RESERVED_ERROR_RANGE_END instead"), JRPC_RESERVED_ERROR_RANGE_END) \
                                                                                                                  \
    X(LSP_RESERVED_ERROR_RANGE_BEG, -32899)                                                                       \
    X(REQUEST_FAILED, -32803)                                                                                     \
    X(SERVER_CANCELLED, -32802)                                                                                   \
    X(CONTENT_MODIFIED, -32801)                                                                                   \
    X(REQUEST_CANCELLED, -32800)                                                                                  \
    X(LSP_RESERVED_ERROR_RANGE_END, -32800)

//  MACROS  //

/// @brief Allows constructing quick errors.
#define XLSP_ERROR(C, ...) ::XLSP::Message::Error(::XLSP::Message::Error::Code::C $_PP_VARGS(__VA_ARGS__))

//  NAMESPACES  //

namespace XLSP::Message {

    /// @brief Response Error Structure.
    struct Error : public $::Printable {
        //  TYPEDEFS  //

        /// @brief Available error codes.
        enum class Code : int64_t { XX_ERROR_CODES($_XX_ENUM_VALUE) };

       private:
        //  PROPERTIES  //

        /// @brief Bound error code.
        Code m_code = Code::UNKNOWN_ERROR_CODE;

        /// @brief Detailed error message.
        $::String::Buffer m_message = "An unknown error occured.";

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        constexpr Error() = default;

        /**
         * @brief Constructs an error response.
         * @param code                  Code to bind.
         */
        constexpr Error(Code code) : m_code(code), m_message() {}

        /**
         * @brief Constructs an error response.
         * @param code                  Code to bind.
         * @param message               Error message.
         */
        constexpr Error(Code code, const $::String::Buffer& message) : m_code(code), m_message(message) {}

        //  PUBLIC METHODS  //

        inline constexpr Code code() const noexcept { return m_code; }
        inline constexpr $::String::View message() const noexcept { return m_message; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles constructing error JSON.
         * @param self                  Error to encode.
         */
        static $::Serde::Value m_encode(const Error& self) {
            $::Serde::Object error = { { "code", self.m_code } };
            if (self.m_message.size()) error["message"] = self.m_message;
            return error;  // return the resulting error value now
        }

        /**
         * @brief Handles decoding response-errors.
         * @param jvalue                JSON value to decode.
         */
        static Error m_decode(const $::Serde::Value& value) {
            auto code = value.at<Code>("code");  // force code
            auto* message = value.at<$::Serde::Text>("message");
            return Error(code, message ? *message : "");
        }

        /**
         * @brief Handles printing errors.
         * @param os                    Output stream.
         * @param self                  Error instance.
         */
        static inline void m_print($::Stream::Output& os, const Error& self) { os << "Error: " << self.m_message; }
    };

}  // namespace XLSP::Message

//  UNDEFINES  //

#undef XX_ERROR_CODES

#endif
