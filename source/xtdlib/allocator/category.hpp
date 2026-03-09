#ifndef _XTDLIB_ALLOCATOR_CATEGORY_HPP
#define _XTDLIB_ALLOCATOR_CATEGORY_HPP

/// Library Includes
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/rtti/hash.hpp"

//  MACROS  //

#if $_ENABLE_MTRACE
#define $_ALLOCATOR_CATEGORY(C) $_FWD($::Allocator::Tag, struct C{})
#else
#define $_ALLOCATOR_CATEGORY(C)  // declare as unset now
#endif

// define a baseline category to use
$_ALLOCATOR_CATEGORY(XTDLIB_GENERAL)

//  NAMESPACES  //

namespace $::Allocator {

    /// @brief Helper for assertion of categories.
    class Category : public Printable {
        //  PROPERTIES  //

        /// @brief Underlying category name.
        String::View m_name = "UNKNOWN";

       public:
        //  CONSTRUCTORS  //

        /// @brief Ensure no default construction.
        explicit constexpr Category() = default;

        /// @brief Constructs a category value.
        explicit constexpr Category(const String::View& name) : m_name(name) {}

        //  OPERATOR METHODS  //

        inline constexpr bool operator==(const Category& other) const noexcept { return m_name == other.m_name; }
        inline constexpr bool operator!=(const Category& other) const noexcept { return m_name != other.m_name; }

        //  PUBLIC METHODS  //

        /// @brief Gets the name of the category.
        inline constexpr String::View name() const noexcept { return m_name; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing categories.
         * @param os                    Output stream.
         * @param self                  Category instance.
         */
        static inline void m_print(Stream::Output& os, const Category& self) {
            os << fmt::format("CATEGORY({0})", self.m_name);
        }
    };

}  // namespace $::Allocator

#endif
