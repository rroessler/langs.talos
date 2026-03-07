#ifndef _TALOS_MEMBER_STORAGE_HPP
#define _TALOS_MEMBER_STORAGE_HPP

/// Talos Modules
#include "talos/function/native.hpp"
#include "talos/member/property.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/value/symbol.hpp"

namespace Talos::Member {

    /// @brief Property Storage Container.
    class Storage {
        //  TYPEDEFS  //

        /// @brief Entry typing to cccept.
        using Entry = std::pair<$::String::View, Function::Callback>;

        /// @brief Initializer fields typing.
        using Initializer = std::vector<Entry>;

        //  PROPERTIES  //

        /// @brief Cached member values.
        $::Map<Value::Symbol, Value::Any> m_cache = {};

        /// @brief All available properties that have been constructed.
        $::Map<Value::Symbol, Member::Property> m_members = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty storage instance.
        explicit constexpr Storage() = default;

        /**
         * @brief Constructs a storage instance.
         * @param name                  Base storage name.
         * @param fields                Fields to be bound.
         */
        explicit constexpr Storage(const $::String::View& name, const Initializer& fields) : m_members(fields.size()) {
            for (const auto& [field, callback] : fields) m_members.emplace(m_factory(name, field, callback));
        }

        //  PUBLIC METHODS  //

        /**
         * @brief Checks if a symbol exists.
         * @param symbol                Field symbol.
         */
        inline constexpr bool contains(Value::Symbol symbol) const noexcept { return m_members.contains(symbol); }

        /**
         * @brief Handles looking up a storage field.
         * @param symbol                Symbol to resolve.
         */
        inline constexpr View retrieve(Value::Symbol symbol) noexcept {
            auto iter = m_members.find(symbol);  // attempt resolving
            return iter == m_members.cend() ? nullptr : &iter->second;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles constructing properties.
         * @param name                  Storage name.
         * @param field                 Field to bind.
         * @param callback              Native callback.
         */
        inline constexpr std::pair<Value::Symbol, Property> m_factory(
            const $::String::View& name, const $::String::View& field, Function::Callback callback) noexcept {
            // prepare an initial value in the cache
            auto& [symbol, value] = *m_cache.emplace(field, Value::Failure()).first;

            // prepare the property getter to be used now
            auto getter = Getter([=](Runtime::Isolate* isolate, auto) mutable -> Value::Any {
                if ($_LIKELY(value != Value::Failure())) return value;  // return now
                return value = isolate->create<Function::Native>(callback, name, field);
            });

            // and construct the resulting entry now
            return { symbol, Property(std::move(getter)) };
        };
    };

}  // namespace Talos::Member

#endif
