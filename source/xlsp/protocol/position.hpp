#ifndef _XLSP_PROTOCOL_POSITION_HPP
#define _XLSP_PROTOCOL_POSITION_HPP

/// XLSP Modules
#include "xlsp/protocol/encoding.hpp"

namespace XLSP {

    /// @brief Baseline Cursor Position (to reduce `Position` and `Range` sizes).
    struct Cursor {
        //  PROPERTIES  //

        uint32_t line = 0;    // Line-number (zero-offset).
        uint32_t column = 0;  // Character-number (zero-offset).

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty cursor (0, 0).
        constexpr Cursor() = default;

        /**
         * @brief Constructs a cursor.
         * @param ln                        Line of cursor.
         * @param col                       Column of cursor.
         */
        constexpr Cursor(uint32_t ln, uint32_t col) : line(ln), column(col) {}

        //  OPERATOR METHODS  //

        /// @brief Equality operator for positions.
        inline constexpr auto operator==(const Cursor& other) const -> bool {
            return line == other.line && column == other.column;
        }

        /// @brief Comparison operator for positions.
        inline constexpr auto operator<=>(const Cursor& other) const {
            return std::tie(line, column) <=> std::tie(other.line, other.column);
        }

        //  PUBLIC METHODS  //

        /// @brief Gets a client version of a cursor.
        inline constexpr Cursor client() const noexcept {
            return *this == Cursor() ? *this : Cursor(line - 1, column - 1);
        }

        /// @brief Gets a server version of a cursor.
        inline constexpr Cursor server() const noexcept {
            return *this == Cursor() ? *this : Cursor(line + 1, column + 1);
        }

        /**
         * @brief Gets a suitable offset of a view.
         * @param view                      Variable to get offset of.
         * @param encoding                  Encoding to determine offset.
         */
        inline constexpr int64_t offset(const $::String::View& view, const Encoding::Type& encoding) const {
            // prepare the placeholder for a start-of-line
            uint32_t som = 0;

            // attempt getting the start-of-line length
            for (uint32_t ii = 0; ii < line; ++ii) {
                auto nl = view.find('\n', som);
                if (nl == $::String::View::npos) return -1;
                som = nl + 1;  // and increment passed the line
            }

            // get the current line details now
            auto end = view.find('\n', som);
            auto ln = view.substr(som, end);

            // attempt measuring now
            auto total = som + Encoding::measure(ln, column, encoding);

            // return the final result now
            return total > view.size() ? -1 : total;
        }
    };

    /// @brief Position Structure.
    struct Position : public Cursor, public $::Printable {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Cursor::Cursor;

        /// @brief We allow direct conversions from cursor values.
        constexpr Position(const Cursor& cursor) : Cursor(cursor) {}

        //  PUBLIC METHODS  //

        /// @brief Gets a client version of a cursor.
        inline constexpr Position client() const noexcept {
            return *this == Position() ? *this : Position(line - 1, column - 1);
        }

        /// @brief Gets a server version of a cursor.
        inline constexpr Position server() const noexcept {
            return *this == Position() ? *this : Position(line + 1, column + 1);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding positions.
         * @param position                  Position instance.
         */
        static $::Serde::Object m_encode(const Position& position) {
            return { { "line", position.line }, { "character", position.column } };
        }

        /**
         * @brief Handles decoding positions.
         * @param value                     JSON value to decode.
         */
        static Position m_decode(const $::Serde::Value& value) {
            return { value.at<uint32_t>("line"), value.at<uint32_t>("character") };
        }

        /**
         * @brief Handles printing positions.
         * @param os                        Output stream.
         * @param self                      Position to print.
         */
        static void m_print($::Stream::Output& os, const Position& self) { os << self.line << ':' << self.column; }
    };

}  // namespace XLSP

#endif
