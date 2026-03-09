#ifndef _TALOS_FUNCTION_CONTEXT_HPP
#define _TALOS_FUNCTION_CONTEXT_HPP

/// Talos Modules
#include "talos/forward/function.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/iterable/list.hpp"

namespace Talos::Function {

    /// @brief Function Context.
    class Context {
        //  TYPEDEFS  //

        /// @brief Available Context Offsets.
        struct Offset {
            static constexpr size_t PARENT = 0;
            static constexpr size_t VALUES = 1;
        };

        //  PROPERTIES  //

        /// @brief Underlying environment value.
        Value::Any m_environment;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a context.
         * @param environment           Environment to bind.
         */
        explicit Context(Value::Any environment = Value::Void()) : m_environment(environment) {}

        /**
         * @brief Constructs a closure context.
         * @param isolate               Runtime isolate.
         * @param size                  Size of context.
         */
        explicit Context(Runtime::Isolate* isolate, size_t size = 0);

        //  OPERATOR METHODS  //

        inline constexpr operator Value::Any() const noexcept { return m_environment; }
        inline constexpr operator Iterable::List() const noexcept { return underlying(); }

        //  PUBLIC METHODS  //

        inline constexpr bool valid() const noexcept { return m_environment.is<Iterable::List>(); }
        inline constexpr Value::Any& environment() noexcept { return m_environment; }
        inline constexpr Iterable::List underlying() const noexcept { return m_environment.as<Iterable::List>(); }

        /// @brief Gets the total size of the context.
        inline constexpr size_t size() const noexcept {
            return valid() ? underlying().size() - Offset::VALUES : SIZE_MAX;
        }

        /// @brief Gets/sets the parent context value.
        inline Context parent() const noexcept { return Context(m_get(Offset::PARENT)); }
        inline constexpr void parent(const Iterable::List& next) const noexcept { m_set(Offset::PARENT, next); }

        /**
         * @brief Loads a value from the context.
         * @param index                     Index of value.
         */
        inline constexpr Value::Any load(size_t index) const noexcept { return m_get(Offset::VALUES + index); }

        /**
         * @brief Stores a value on the context.
         * @param index                     Index of value.
         * @param value                     Value to assign.
         */
        inline constexpr void store(size_t index, Value::Any value) const noexcept {
            m_set(Offset::VALUES + index, value);
        }

        /**
         * @brief Handles getting a parent at a required depth.
         * @param depth                     Depth of parent.
         */
        inline constexpr Context resolve(size_t depth) const {
            switch (depth) {
                case 0: return *this;     // should be this instance
                case 1: return parent();  // fast-path the immediate parent
                default: {
                    auto context = *this;  // get the base reference for our depth
                    for (; depth && context.valid(); --depth) context = context.parent();
                    return context;  // return the resulting context as necessary now
                }
            }
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles getting index values.
         * @param index                     Index to retrieve.
         */
        inline constexpr Value::Any m_get(size_t index) const noexcept { return underlying().get(index); }

        /**
         * @brief Handles setting index values.
         * @param index                     Index of context.
         * @param value                     Value to assign.
         */
        inline constexpr void m_set(size_t index, Value::Any value) const noexcept { underlying().set(index, value); }
    };

}  // namespace Talos::Function

#endif
