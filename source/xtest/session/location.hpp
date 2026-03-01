#ifndef _XTEST_SESSION_LOCATION_HPP
#define _XTEST_SESSION_LOCATION_HPP

/// XT Includes
#include "xtest/forward/session.hpp"

namespace XT {

    /// @brief Bound Location Details.
    class Location : public $::Printable {
        //  PROPERTIES  //

        size_t m_line = 0;    // Line of location.
        size_t m_column = 0;  // Column of location.

        /// @brief Underlying location resource.
        $::URI::Buffer m_resource;

       public:
        //  CONSTRUCTORS  //

        /// @brief Defaulted location constructor.
        constexpr Location() : m_resource($::URI::Anonymous().buffer()) {}

        /**
         * @brief Constructs a testing location.
         * @param location          Compile-time location.
         */
        constexpr Location(const $::Location& location) :
            Location(location.line(), location.column(), $::URI::File(location.file())) {}

        /**
         * @brief Constructs a location.
         * @param line              Line of location.
         * @param column            Column of location.
         * @param resource          Resource of location.
         */
        constexpr Location(size_t line, size_t column, const $::URI::View& resource) :
            m_line(line), m_column(column), m_resource(resource.buffer()) {}

        //  PUBLIC METHODS  //

        inline constexpr size_t line() const noexcept { return m_line; }
        inline constexpr size_t column() const noexcept { return m_column; }
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }
        inline constexpr bool anonymous() const noexcept { return m_resource == $::URI::Anonymous(); }
        inline constexpr $::String::Buffer filename() const noexcept {
            return $::Path::filename(m_resource.body()).string();
        }

        /**
         * @brief Gets the relative resource.
         * @param hint                      Optional hint.
         */
        inline constexpr $::String::Buffer relative(const $::Filesystem::Path& hint = $::System::cwd()) const noexcept {
            return m_resource.relative(hint);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles dumping locations.
         * @param os                        Output stream.
         * @param self                      Location instance.
         */
        static inline void m_print($::Stream::Output& os, const Location& self) {
            os << self.relative();  // prepare the base details now before showing
            if (self.line() > 0) os << ':' << self.line() << ':' << self.column();
        }

        /**
         * @brief Handles stringifying locations.
         * @param oss                       Output stream.
         * @param self                      Location instance.
         */
        static inline void m_stringify($::String::Stream& oss, const Location& self) { m_print(oss, self); }
    };

}  // namespace XT

#endif
