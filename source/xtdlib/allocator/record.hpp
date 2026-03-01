#ifndef _XTDLIB_ALLOCATOR_RECORD_HPP
#define _XTDLIB_ALLOCATOR_RECORD_HPP

/// Library Includes
#include "xtdlib/allocator/category.hpp"
#include "xtdlib/debug/location.hpp"
#include "xtdlib/debug/printable.hpp"

namespace $::Allocator {

    /// @brief Allocation Record.
    class Record : public $::Printable {
        //  PROPERTIES  //

        /// @brief Associated allocation pool.
        size_t m_pool;

        /// @brief Total bytes allocated.
        size_t m_bytes;

        /// @brief Allocation category type.
        Category m_category;

        /// @brief Source Location Details.
        $::Location m_location;

       public:
        //  CONSTRUCTORS  //

        /// @brief Default allocation constructor.
        explicit constexpr Record() = default;

        /**
         * @brief Constructs a suitable record.
         * @param bytes                     Size of record.
         * @param category                  Memory category.
         * @param location                  Source location.
         */
        explicit constexpr Record(size_t bytes, const Category& category, const $::Location& location) :
            m_pool(0), m_bytes(bytes), m_category(category), m_location(location) {}

        /**
         * @brief Constructs a suitable record.
         * @param pool                      Pool identifier.
         * @param bytes                     Size of record.
         * @param category                  Memory category.
         * @param location                  Source location.
         */
        explicit constexpr Record(size_t pool, size_t bytes, const Category& category, const $::Location& location) :
            m_pool(pool), m_bytes(bytes), m_category(category), m_location(location) {}

        //  PUBLIC METHODS  //

        inline constexpr size_t bytes() const noexcept { return m_bytes; }
        inline constexpr size_t pool() const noexcept { return m_pool; }
        inline constexpr Category category() const noexcept { return m_category; }

        inline constexpr size_t line() const noexcept { return m_location.line(); }
        inline constexpr size_t column() const noexcept { return m_location.column(); }
        inline constexpr $::String::View file() const noexcept { return m_location.file(); }
        inline constexpr $::String::View callee() const noexcept { return m_location.callee(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing records.
         * @param os                        Output stream.
         * @param self                      Record instance.
         */
        static inline void m_print(Stream::Output& os, const Record& self) {
            os << fmt::format("{0} ({1}): {2} bytes", self.callee(), self.category(), self.bytes());
            os << fmt::format("\n --> '{0}'", self.m_location);  // format the location now
        }
    };

}  // namespace $::Allocator

#endif
