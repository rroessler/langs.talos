#ifndef _TALOS_OBJECT_ALLOCATOR_HPP
#define _TALOS_OBJECT_ALLOCATOR_HPP

/// Talos Modules
#include "talos/heap/options.hpp"
#include "talos/object/abstract.hpp"

namespace Talos::Object {

    /// @brief Object Allocator.
    struct Allocator {
        //  PUBLIC METHODS  //

        /**
         * @brief Handles constructing values.
         * @param isolate               Runtime isolate.
         * @param args                  Constructor arguments.
         */
        template <std::derived_from<Value::Any> T, class... As>
        static inline constexpr T create(Runtime::Isolate* isolate, As&&... args) {
            if constexpr (!m_validate<T>()) return m_inlined<T>(isolate, std::forward<As>(args)...);
            else return m_create<T>(isolate, std::forward<As>(args)...);  // should be built here
        }

        /**
         * @brief Handles moving values.
         * @param address               Address to move into.
         * @param value                 Value to be moved.
         */
        template <std::derived_from<Value::Any> T>
        static inline constexpr void move(Heap::Address address, Value::Any value) {
            if constexpr (m_validate<T>()) m_move<T>(address, value.as<Object::Any>());
        }

        /**
         * @brief Handles destructing values.
         * @param value                 Value to destruct.
         */
        template <std::derived_from<Value::Any> T>
        static inline constexpr void destroy(Value::Any value) {
            if constexpr (m_validate<T>()) m_destruct<T>(value.as<Object::Any>());
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Validates incoming value
        template <std::derived_from<Value::Any> T>
        static inline constexpr bool m_validate() {
            return std::derived_from<T, Abstract<T>>;
        }

        /**
         * @brief Handles creating an object.
         * @param isolate               Runtime isolate.
         * @param args                  Constructor arguments.
         */
        template <std::derived_from<Value::Any> T, class... As>
        static inline constexpr T m_create(Runtime::Isolate* isolate, As&&... args) {
            using Attributes = typename Object::Attributes<T>;  // resolve details
            using Underlying = std::conditional_t<std::same_as<T, Any>, Instance, T>;

            static constexpr auto size = sizeof(Attributes);  // get the base details
            $_UNUSED static constexpr auto name = $::RTTI::Name::of<Underlying>();

            // ensure that the desired object is actually valid to be constructed
            $_ASSERT(!!size, "Object '{0}' does not have any attributes", name);
            $_ASSERT(size <= UINT8_MAX, "Object '{0}' attributes exceed maximum size", name);

            // attempt allocating the underlying memory now
            auto shape = Shape::Lookup<Underlying>();
            auto address = m_allocate(isolate, size, shape);

            // construct the actual details now
            m_construct<Attributes>(isolate, address, std::forward<As>(args)...);

            // and return the resulting encoded object instance
            return T(Any::m_encode(address));
        }

        /**
         * @brief Constructs any valid value.
         * @param isolate               Runtime isolate.
         * @param args                  Constructor arguments.
         */
        template <std::derived_from<Value::Any> T, class... As>
        static inline constexpr T m_inlined(Runtime::Isolate* isolate, As&&... args) {
            static constexpr auto without = std::constructible_from<T, As...>;
            if constexpr (without) return T(std::forward<As>(args)...);
            else return T(isolate, std::forward<As>(args)...);
        }

        /**
         * @brief Handles constructing an object.
         * @param isolate               Runtime isolate.
         * @param address               Address to allocate.
         * @param args                  Constructor arguments.
         */
        template <class T, class... As>
        static inline constexpr void m_construct(Runtime::Isolate* isolate, Heap::Address address, As&&... args) {
            auto* attributes = std::bit_cast<T*>(address);  // get the attributes
            static constexpr auto without = std::constructible_from<T, As...>;
            if constexpr (without) new (attributes) T(std::forward<As>(args)...);
            else new (attributes) T(isolate, std::forward<As>(args)...);
        }

        /**
         * @brief Handles moving values.
         * @param address               Address to move into.
         * @param value                 Value to be moved.
         */
        template <std::derived_from<Value::Any> T>
        static inline constexpr void m_move(Heap::Address address, Object::Any object) {
            using Attributes = typename Object::Attributes<T>;
            auto* other = std::bit_cast<Attributes*>(object.address());
            auto* output = new (std::bit_cast<Attributes*>(address)) Attributes(std::move(*other));
            $_PP_IGNORE(output);
        }

        /**
         * @brief Handles destructing an object.
         * @param object                Value to destruct.
         */
        template <std::derived_from<Value::Any> T>
        static inline constexpr void m_destruct(Object::Any object) {
            using Attributes = typename Object::Attributes<T>;
            std::bit_cast<Attributes*>(object.address())->~Attributes();
        }

        /**
         * @brief Handles allocating an object.
         * @param isolate               Runtime isolate.
         * @param size                  Size to allocate.
         * @param shape                 Object shape value.
         */
        static Heap::Address m_allocate(Runtime::Isolate* isolate, size_t size, Shape::Underlying shape);
    };

}  // namespace Talos::Object

#endif
