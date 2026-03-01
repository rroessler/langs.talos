#ifndef _XTDLIB_FUNCTOR_UNIQUE_HPP
#define _XTDLIB_FUNCTOR_UNIQUE_HPP

/// C++ Modules
#include <functional>

/// Library Modules
#include "xtdlib/debug/assert.hpp"

namespace $::Functor {

    /// @brief A move-only functor.
    template <class T, class B = std::function<T>>
    class Unique : public B {
        //  TYPEDEFS  //

        /// @brief Type-erasure container.
        template <class F, class E = void>
        struct Container;

        /// @brief Copyable functors.
        template <class F>
        struct Container<F, std::enable_if_t<std::is_copy_constructible_v<F>>> {
            //  PROPERTIES  //

            /// @brief Encapsulated functor.
            F functor;

            //  OPERATOR METHODS  //

            /// @brief Call-operator overload for 'functor'.
            template <class... As>
            $_INLINE_FORCE constexpr auto operator()(As&&... args) {
                return functor(std::forward<As>(args)...);
            }
        };

        /// @brief Movable functors.
        template <class F>
        struct Container<F, std::enable_if_t<!std::is_copy_constructible_v<F>>> {
            //  PROPERTIES  //

            /// @brief Encapsulate functor.
            F functor;

            //  CONSTRUCTORS  //

            constexpr Container(Container&&) = default;
            constexpr Container(F&& functor) : functor(std::forward<F>(functor)) {}
            constexpr Container(const Container& other) : functor(const_cast<F&&>(other.functor)) { m_abort(); }

            //  OPERATOR METHODS  /

            constexpr Container& operator=(Container&&) = delete;
            constexpr Container& operator=(const Container&) { m_abort(); }

            /// @brief Call-operator overload for calling the `functor`.
            template <typename... As>
            $_INLINE_FORCE constexpr auto operator()(As&&... args) {
                return functor(std::forward<As>(args)...);
            }

           private:
            //  PRIVATE METHODS  //

            /// @brief Declares that the container cannot be copied.
            $_NORETURN $_INLINE_FORCE constexpr void m_abort() noexcept(false) {
                $_ABORT("Cannot copy move-only function");
            }
        };

       public:
        //  CONSTRUCTORS  //

        constexpr Unique() noexcept = default;
        constexpr Unique(const Unique&) = delete;
        constexpr Unique(Unique&&) = default;

        /// @brief Constructs a nulled unique function.
        constexpr Unique(std::nullptr_t) noexcept : B(nullptr) {}

        /**
         * @brief Constructs a unique functor.
         * @tparam F                    Function typing.
         * @param functor               Lambda to inherit.
         */
        template <typename F>
        constexpr Unique(F&& functor) : B(Container<F>{ std::forward<F>(functor) }) {}

        //  OPERATOR METHODS  //

        /// @brief Inherit the base call-operator.
        using B::operator();

        constexpr Unique& operator=(Unique&&) = default;
        constexpr Unique& operator=(const Unique&) = delete;
        constexpr Unique& operator=(std::nullptr_t) { return B::operator=(nullptr), *this; }

        template <typename F>
        inline constexpr Unique& operator=(F&& functor) {
            return B::operator=(Container<F>{ std::forward<F>(functor) }), *this;
        }
    };

}  // namespace $::Functor

#endif
