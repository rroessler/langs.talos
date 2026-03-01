#ifndef _XTDLIB_POINTER_AUTO_HPP
#define _XTDLIB_POINTER_AUTO_HPP

/// C++ Includes
#include <cstddef>

/// Library Includes
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/functor/unique.hpp"
#include "xtdlib/pointer/proxy.hpp"
#include "xtdlib/stream/types.hpp"
#include "xtdlib/traits/concepts.hpp"

namespace $::Ptr {

    /// @brief An unsafe "shared_ptr" implementation.
    template <class T>
    struct Auto {
        //  TYPEDEFS  //

        /// @brief Derived class declaration.
        class Derived;

        /// @brief Allow being friends with other types.
        template <class U>
        friend struct Auto;

        /// @brief Expose the underlying type.
        using Underlying = T;

        /// @brief Internal counter typing.
        using Counter = Functor::Unique<size_t(Derived*)>;

        /// @brief Explicit Traits Container.
        struct Traits {
            Counter increment = nullptr;
            Counter decrement = nullptr;
        };

        /// @brief Binds a reference count to a derived pointer.
        class Derived : public Underlying {
            //  TYPEDEFS  //

            /// @brief Allow exposing the reference count.
            friend struct Auto<Underlying>;

            //  PROPERTIES  //

            /// @brief Current reference count.
            size_t m_refc = 0;

            /// @brief Handles decrementing the instance.
            Traits m_counter = {};

           public:
            //  CONSTRUCTORS  //

            /// @brief Inherit the base constructor.
            using Underlying::Underlying;

            //  PUBLIC METHODS  //

            /// @brief Gets the current reference count.
            inline constexpr size_t refc() const noexcept { return m_refc; }

           private:
            //  PRIVATE METHODS  //

            inline size_t m_inc() { return m_refc = m_counter.increment ? m_counter.increment(this) : ++m_refc; }
            inline size_t m_dec() { return m_refc = m_counter.decrement ? m_counter.decrement(this) : --m_refc; }
        };

       private:
        //  PROPERTIES  //

        /// @brief The underlying reference.
        Derived* m_ptr = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty pointer.
        explicit constexpr Auto() = default;

        /**
         * @brief Constructs from an initial value.
         * @param ptr               Pointer to bind.
         */
        explicit constexpr Auto(Derived* ptr) : m_ptr(ptr) { m_increment(); }

        /**
         * @brief Constructs a custom auto-pointer.
         * @param ptr               Pointer to bind.
         * @param traits            Custom counter traits.
         */
        explicit constexpr Auto(Derived* ptr, Traits&& counter) : Auto(ptr) { m_ptr->m_counter = std::move(counter); }

        /// @brief Allow copy-construction.
        constexpr Auto(const Auto& other) : m_ptr(other.m_ptr) { m_increment(); }
        template <std::convertible_from<Underlying> U>
        constexpr Auto(const Auto<U>& other) : m_ptr(other.m_ptr) {
            m_increment();
        }

        /// @brief Allow move-construction.
        constexpr Auto(Auto&& other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
        template <std::convertible_from<Underlying> U>
        constexpr Auto(Auto<U>&& other) : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        /// @brief Handles releasing the encapsulated pointer.
        constexpr ~Auto() { m_decrement(); }

        //  OPERATOR METHODS  //

        /// @brief Allow valid dereferencing.
        inline constexpr Underlying& operator*() const noexcept { return m_assert(), *m_ptr; }

        /// @brief Allow valid member operators.
        inline constexpr Underlying* operator->() const noexcept { return m_assert(), m_ptr; }

        /// @brief Gets the truthiness of the pointer.
        inline constexpr operator bool() const noexcept { return m_ptr != nullptr; }

        /// @brief Handles direct comparisons.
        inline constexpr bool operator==(Underlying* other) const noexcept { return m_ptr == other; }
        inline constexpr bool operator==(std::nullptr_t) const noexcept { return m_ptr == nullptr; }
        inline constexpr bool operator==(const Auto& other) const noexcept { return m_ptr == other.m_ptr; }

        template <std::convertible_from<Underlying> U>
        inline constexpr bool operator==(U* other) const noexcept {
            return m_ptr == other->m_ptr;
        }

        template <std::convertible_from<Underlying> U>
        inline constexpr bool operator==(const Auto<U>& other) const noexcept {
            return m_ptr == other->m_ptr;
        }

        /// @brief Allow three-way comparisons directly.
        inline constexpr auto operator<=>(const Auto& other) const noexcept { return m_ptr <=> other->m_ptr; }

        /// @brief Allow printing to output streams.
        inline friend Stream::Output& operator<<(Stream::Output& os, const Auto& self) noexcept {
            return os << self.m_ptr, os;
        }

        /// @brief Allow copy-conversion.
        inline constexpr Auto& operator=(const Auto& other) { return Auto(other).swap(*this), *this; }
        template <std::convertible_from<Underlying> U>
        inline constexpr Auto& operator=(const Auto<U>& other) {
            return Auto(other).swap(*this), *this;
        }

        /// @brief Allow move-conversion.
        inline constexpr Auto& operator=(Auto&& other) { return Auto(std::move(other)).swap(*this), *this; }
        template <std::convertible_from<Underlying> U>
        inline constexpr Auto& operator=(Auto<U>&& other) {
            return Auto(std::move(other)).swap(*this), *this;
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying pointer.
        inline constexpr Underlying* get() const noexcept { return m_ptr; }

        /// @brief Gets the underlying reference count.
        inline constexpr size_t refc() const noexcept { return m_ptr ? m_ptr->m_refc : 0; }

        /// @brief Allow only resetting with itself.
        inline constexpr void reset() { Auto().swap(*this); }

        /// @brief Handles swapping pointers.
        inline constexpr void swap(Auto& other) noexcept { std::swap(m_ptr, other.m_ptr); }

       private:
        //  PRIVATE METHODS  //

        /// @brief Asserts that the pointer is valid.
        inline constexpr void m_assert() const noexcept { $_ASSERT(m_ptr != nullptr); }

        /// @brief Handles safely incrementing the encapsulated pointer.
        inline constexpr void m_increment() {
            if (m_ptr != nullptr) m_ptr->m_inc();
        }

        /// @brief Handles safely releasing the encapsulated pointer.
        inline constexpr void m_decrement() {
            if (m_ptr == nullptr || m_ptr->m_refc == 0) return;
            if (m_ptr->m_dec() == 0) delete m_ptr, m_ptr = nullptr;
        }
    };

}  // namespace $::Ptr

#endif
