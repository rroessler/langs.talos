#ifndef _FORGE_ITERABLE_ITERATOR_HPP
#define _FORGE_ITERABLE_ITERATOR_HPP

/// Forge Modules
#include "forge/iterable/callback.hpp"

namespace Forge {

    /// @brief Iterator Attributes.
    template <>
    struct Object::Attributes<Iterable::Iterator> {
        //  TYPEDEFS  //

        /// @brief Allow the iterator internal access.
        friend struct Iterable::Iterator;

        //  PROPERTIES  //

        /// @brief Internal index value.
        size_t index = 0;

        /// @brief Current iterator value.
        Value::Any value = Value::Void();

        /// @brief Iterable state value (usually the iterator).
        Value::Any state = Value::Void();

        /// @brief Handles getting the subsequent value.
        Iterable::Callback<Value::Any> next = nullptr;

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty iterator.
        explicit Attributes() : value(Value::Sentinel()) {}

        /**
         * @brief Constructs a typed iterator.
         * @param iterable              Iterable state.
         * @param callback              Typed callback.
         */
        template <std::derived_from<Value::Any> T>
        explicit Attributes(T iterable, Iterable::Callback<T>&& callback) : state(iterable) {
            next = [cb = std::move(callback)](Runtime::Isolate* isolate, Value::Any self, size_t index) -> Value::Any {
                return cb(isolate, self.as<T>(), index);  // and convert into our suitable callback now
            };
        }

        /**
         * @brief Constructs an untyped iterator.
         * @param iterable              Iterable state.
         * @param callback              Untyped callback.
         */
        template <>
        explicit Attributes<Value::Any>(Value::Any iterable, Iterable::Callback<Value::Any>&& callback) :
            state(iterable), next(std::move(callback)) {
            if ($_UNLIKELY(callback == nullptr)) value = Value::Sentinel();
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Denotes if the result is alright or not.
        inline constexpr bool m_okay() const noexcept { return value.traits().okay(); }

        /// @brief Denotes if the iterator is done.
        inline constexpr bool m_done() const noexcept { return value.traits().sentinel(); }

        /**
         * @brief Handles advancing the iterable.
         * @param isolate               Thread isolate.
         */
        inline constexpr bool m_advance(Runtime::Isolate* isolate) {
            if ($_UNLIKELY(next == nullptr) || m_done()) return true;
            return value = next(isolate, state, index++), m_done();
        }
    };

    /// @brief Iterator Interface.
    struct Iterable::Iterator : public Object::Abstract<Iterable::Iterator> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr bool done() const noexcept { return m_attrs()->m_done(); }
        inline constexpr bool okay() const noexcept { return m_attrs()->m_okay(); }

        inline constexpr size_t index() const noexcept { return m_attrs()->index; }
        inline constexpr Value::Any value() const noexcept { return m_attrs()->value; }

        /**
         * @brief Handles advancing the iterator.
         * @param isolate               Thread isolate.
         */
        inline constexpr bool next(Runtime::Isolate* isolate) const noexcept { return m_attrs()->m_advance(isolate); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding iterators safely.
         * @param self                          Iterator instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Iterator& self, const Globals::Each& yield);
    };

}  // namespace Forge

#endif
