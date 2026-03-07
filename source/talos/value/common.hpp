#ifndef _TALOS_VALUE_ANY_HPP
#define _TALOS_VALUE_ANY_HPP

/// Talos Includes
#include "talos/operator/kind.hpp"
#include "talos/value/proxy.hpp"

namespace Talos::Value {

    /// @brief Base Runtime Value.
    class Any : public $::Printable {
        //  TYPEDEFS  //

        /// @brief Allow locals internal access.
        template <std::derived_from<Any> T>
        friend class Handle::Local;

       protected:
        //  PROPERTIES  //

        /// @brief The underlying pointer instance.
        Pointer::Underlying m_pointer = Pointer::Traits();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted value.
        explicit constexpr Any() = default;

        /**
         * @brief Allow explicit construction of values.
         * @param pointer               Pointer to assign.
         */
        explicit constexpr Any(const Pointer::Traits& traits) : m_pointer(traits) {}

        //  OPERATOR METHODS  //

        inline constexpr bool operator==(const Any& other) const noexcept { return m_pointer == other.m_pointer; }
        inline constexpr bool operator!=(const Any& other) const noexcept { return m_pointer != other.m_pointer; }

        //  PUBLIC METHODS  //

        /// @brief Gets the associated truthiness of the value
        bool truthiness() const noexcept;

        /// @brief Gets a values underlying shape.
        Shape::Underlying shape() const noexcept;

        /// @brief Gets the underlying type-name of a value.
        $::String::View type_name() const noexcept;

        /// @brief Gets the underlying tagged pointer.
        inline constexpr Pointer::Traits traits() const noexcept { return m_pointer; }
        inline constexpr Pointer::Underlying pointer() const noexcept { return m_pointer; }

        /// @brief Handles validating value types.
        template <std::derived_from<Any> T>
        inline constexpr bool is() const noexcept {
            return Proxy<T>::is(traits());
        }

        /// @brief Casts value to the desired typing.
        template <std::derived_from<Any> T>
        inline constexpr T as() const noexcept {
            $_UNUSED static constexpr auto to = $::RTTI::Name::of<T>();  // prepare the compiled name
            return $_ASSERT(is<T>(), "Failed cast from '{0}' to '{1}'", type_name(), to), m_as<T>();
        }

        /**
         * @brief Handles looking up a member attribute.
         * @param symbol            Field symbol.
         */
        Member::View attribute(const Symbol& symbol) const noexcept;

        /**
         * @brief Handles looking up an operator attribute.
         * @param symbol            Field symbol.
         */
        Member::View attribute(Operator::Kind kind) const noexcept;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles coordinating an unsafe cast.
        template <std::derived_from<Any> T>
        $_INLINE_PERF constexpr T m_as() const noexcept {
            if constexpr (std::same_as<T, Value::Any>) return *this;
            else return *reinterpret_cast<const T*>(this);  // cast
        }

        /// @brief Fallback validation check.
        static inline bool m_is(const Pointer::Traits&) { return true; }

        /**
         * @brief Handles printing values.
         * @param os                        Output stream.
         * @param self                      Value to print.
         */
        static void m_print($::Stream::Output& os, const Any& self);
        static void m_stringify($::Stream::Output& os, const Any& self);
    };

    //  PUBLIC METHODS  //

    /// @brief Allows unsafely casting to other values.
    template <std::derived_from<Any> T, class V>
    inline constexpr T Cast(const V& value) noexcept {
        if constexpr (std::same_as<T, V>) return value;  // same type
        else if constexpr (std::same_as<T, Value::Any>) return value;
        else return *reinterpret_cast<const T*>(&value);  // cast now
    }

}  // namespace Talos::Value

#endif
