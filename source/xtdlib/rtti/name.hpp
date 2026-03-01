#ifndef _XTDLIB_RTTI_NAME_HPP
#define _XTDLIB_RTTI_NAME_HPP

/// Library Includes
#include "xtdlib/string/view.hpp"
#include "xtdlib/traits/concepts.hpp"
#include "xtdlib/utility/never.hpp"

namespace $::RTTI {

    /// @brief Template Name Parser.
    class $_ABSTRACT Name : public Never {
        //  PROPERTIES  //

#if defined(__clang__)
#define $_FUNCSIG __PRETTY_FUNCTION__

        static constexpr auto m_prefix = String::View("[T = ");
        static constexpr auto m_suffix = String::View("]");
#elif defined(__GNUC__)
#define $_FUNCSIG __PRETTY_FUNCTION__

        static constexpr auto m_prefix = String::View("with T = ");
        static constexpr auto m_suffix = String::View("; ");
#elif defined(__FUNCSIG__)
#define $_FUNCSIG __FUNCSIG__

        static constexpr auto m_prefix = String::View("get_type_name<");
        static constexpr auto m_suffix = String::View(">(void)");
#else
#define $_FUNCSIG __func__

        static constexpr auto m_prefix = String::View();
        static constexpr auto m_suffix = String::View();
#endif

       public:
        //  PUBLIC METHODS  //

        /// @brief Handles deducing value-names.
        template <class T>
        $_INLINE_FORCE static consteval String::View of() noexcept {
            // ensure that function-signatures can be validly deduced
            static_assert(!!m_prefix.size() && !!m_suffix.size(), "Cannot deduce name-of value");

            static constexpr auto signature = String::View($_FUNCSIG);  // prepare
            static constexpr auto start = signature.find(m_prefix) + m_prefix.size();
            return signature.substr(start, signature.find(m_suffix) - start);  // trim
        }
    };

}  // namespace $::RTTI

#endif
