#ifndef _TALOS_OBJECT_ENUM_HPP
#define _TALOS_OBJECT_ENUM_HPP

/// Talos Modules
#include "talos/member/reference.hpp"
#include "talos/number/tagged.hpp"
#include "talos/string/dynamic.hpp"

namespace Talos {

    /// @brief Enumeration Variant.
    struct Object::Variant {
        /// @brief Underlying variant name.
        String::Dynamic name;

        /// @brief Aliased variant label.
        String::Dynamic label;

        /// @brief The bound member reference.
        $::Ptr::Unique<Member::Reference> value;
    };

    /// @brief Enumeration Attributes.
    template <>
    struct Object::Attributes<Object::Enum> {
        //  PROPERTIES  //

        /// @brief Available enumeration variants.
        $::Map<Value::Symbol, Variant> variants = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty enumeration.
        explicit Attributes() = default;

        /**
         * @brief Constructs an enumeration.
         * @param variants              Variants initializer.
         */
        explicit Attributes(std::vector<Variant>&& variants) : Attributes(m_initialize(std::move(variants))) {}

        /**
         * @brief Constructs an enumeration.
         * @param variants              Enumeration variants.
         */
        explicit Attributes($::Map<Value::Symbol, Variant>&& variants) : variants(std::move(variants)) {}

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles initializing variants.
         * @param initializer           Initializer list.
         */
        static inline $::Map<Value::Symbol, Variant> m_initialize(std::vector<Variant>&& initializer) {
            auto predicate = [](Variant&& variant) { return std::pair(variant.name.symbol(), std::move(variant)); };
            auto range = std::views::as_rvalue(initializer) | std::views::transform(predicate);
            return $::Map<Value::Symbol, Variant>(range.begin(), range.end());  // and re-cast
        }
    };

    /// @brief Enumeration Interface.
    struct Object::Enum : public Object::Abstract<Object::Enum> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        /// @brief Gets the total variants available.
        inline constexpr const auto& variants() const noexcept { return m_attrs()->variants; }

        /**
         * @brief Allows looking up an enumeration variant.
         * @param symbol                Symbol to resolve.
         */
        inline constexpr const Variant* resolve(Value::Symbol symbol) const noexcept {
            auto& view = variants();  // prepare the view now to be used
            return view.contains(symbol) ? &view.at(symbol) : nullptr;
        }

        /**
         * @brief Allows looking up an enumeration variant.
         * @param ordinal               Ordinal to resolve.
         */
        inline constexpr const Variant* resolve(Number::Tagged ordinal) const noexcept {
            for (const auto& variant : variants() | std::views::values) {
                if (variant.value->reference() == ordinal) return &variant;
            }

            // failed to find a suitably variant
            return nullptr;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding enumerations safely.
         * @param self                          Enum instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Enum& self, const Globals::Each& yield);
    };

}  // namespace Talos

#endif
