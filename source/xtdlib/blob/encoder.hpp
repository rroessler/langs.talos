#ifndef _XTDLIB_BLOB_ENCODER_HPP
#define _XTDLIB_BLOB_ENCODER_HPP

/// Library Modules
#include "xtdlib/blob/buffer.hpp"
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/traits/concepts.hpp"

namespace $::Blob {

    /// @brief Blob Encoder Abstraction.
    template <class T>
    struct $_ABSTRACT Encoder {
        //  TYPEDEFS  //

        /// @brief Encoder state to use.
        using Sink = Buffer;

        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Encoder() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Handles writing blobs.
         * @param data              Data to write.
         */
        inline constexpr Buffer write(const T& data) const noexcept {
            auto sink = Sink();  // prepare
            return m_encode(data, sink), sink;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles writing segments.
         * @param data              Data to write.
         * @param count             Count of data.
         * @param sink              Sink to use.
         */
        template <std::arithmetic U>
        inline constexpr void m_write(const U* data, size_t count, Sink& sink) const noexcept {
            const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data);
            sink.insert(sink.end(), ptr, ptr + sizeof(U) * count);
        }

        /**
         * @brief Handles writing arithmetic values.
         * @param value             Value to write.
         * @param sink              Sink to use.
         */
        template <std::arithmetic U>
        inline constexpr void m_write(U value, Sink& sink) const noexcept {
            m_write(&value, 1, sink);
        }

        /**
         * @brief Handles writing vectors.
         * @param data              Data to write.
         * @param sink              Sink to use.
         */
        template <std::arithmetic U>
        inline constexpr void m_write(const std::vector<U>& data, Sink& sink) const noexcept {
            m_write(data.size(), sink), m_write(data.data(), data.size(), sink);
        }

        /**
         * @brief Handles writing views.
         * @param view              Text to write.
         * @param sink              Sink to use.
         */
        inline constexpr void m_write(const String::View& view, Sink& sink) const noexcept {
            m_write(view.size(), sink), m_write(view.data(), view.size(), sink);
        }

        /**
         * @brief Handles writing blobs.
         * @param data              Data to write.
         * @param sink              Sink to use.
         */
        virtual void m_encode(const T& data, Sink& sink) const noexcept = 0;
    };

}  // namespace $::Blob

#endif
