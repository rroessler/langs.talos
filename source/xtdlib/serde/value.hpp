#ifndef _XTDLIB_SERDE_VALUE_HPP
#define _XTDLIB_SERDE_VALUE_HPP

/// C++ Modules
#include <expected>
#include <map>
#include <variant>

/// Library Modules
#include "xtdlib/container/map.hpp"
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/rtti/name.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/traits/concepts.hpp"
#include "xtdlib/traits/sequence.hpp"
#include "xtdlib/traits/unqualified.hpp"

namespace $::Serde {

    //  TYPEDEFS  //

    /// @brief Any Serialization Value.
    class Value;

    using Boolean = bool;                               // Boolean primitive.
    using Number = double;                              // Numeric primitive.
    using Null = std::nullptr_t;                        // Nullish values.
    using Text = String::Buffer;                        // String values.
    using Array = std::vector<Value>;                   // Array of values.
    using Object = std::map<Text, Value, std::less<>>;  // Object of values.

    /// @brief Denotes expected results from parsing/stringifying.
    template <class T>
    using Expected = std::expected<T, Text>;

    /// @brief Validates a trivial typing.
    template <class T>
    concept Trivial = Traits::Disjunction<T, Null, Boolean, Number, Text, Array, Object>;

    /// @brief Validates a numeric typing.
    template <class T>
    concept Arithmetic = std::is_enum_v<T> || (!Traits::Disjunction<T, Boolean, Number> && std::arithmetic<T>);

    /// @brief Underlying Serialization Value.
    class Value : public Printable {
        //  TYPEDEFS  //

        /// @brief Encpasulates visitor overloads.
        template <class... Ts>
        struct Overloads : Ts... {
            using Ts::operator()...;
        };

        /// @brief Initializer List Typing.
        template <class T>
        using Initializer = std::initializer_list<typename T::value_type>;

        /// @brief Storage typing.
        using Storage = std::variant<Null, Boolean, Number, Text, Array, Object>;

       protected:
        //  PROPERTIES  //

        /// @brief Underlying value storage.
        Storage m_storage = Null();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted value.
        constexpr Value() = default;
        constexpr Value(Value&&) = default;
        constexpr Value(const Value&) = default;

        /// @brief Allows construction from nullish values.
        constexpr Value(Null) : m_storage(Null()) {}

        /**
         * @brief Constructs a value from a string.
         * @param buffer                Text buffer.
         */
        constexpr Value(const Text& text) { m_storage = text; }
        constexpr Value(const char* text) { m_storage = Text(text); }
        constexpr Value(const String::View& text) { m_storage = Text(text); }

        /**
         * @brief Constructs a boolean value.
         * @param state                 Boolean value
         */
        constexpr Value(bool state) { m_storage = state; }

        /**
         * @brief Constructs a numeric value.
         * @param numeric               Numeric value.
         */
        template <Arithmetic T>
        constexpr Value(T numeric) : m_storage(static_cast<Number>(numeric)) {}

        /**
         * @brief Constructs a value from the given elements.
         * @param elements              Array/Object values.
         */
        constexpr Value(const Array& elements) { m_storage = elements; }
        constexpr Value(const Object& elements) { m_storage = elements; }
        constexpr Value(Array&& elements) { m_storage = std::move(elements); }
        constexpr Value(Object&& elements) { m_storage = std::move(elements); }

        /**
         * @brief Constructs a value from given elements.
         * @param elements              Object initializer.
         */
        constexpr Value(Initializer<Object>&& elements) {
            m_storage.emplace<Object>();  // prepare
            auto& object = std::get<Object>(m_storage);

            // and update the internal elements to be used now
            for (auto&& pair : elements) object.emplace(pair.first, pair.second);
        }

        /**
         * @brief Constructs a value from given elements.
         * @param elements              Array initializer.
         */
        template <bool = true>
        constexpr Value(Initializer<Array>&& elements) {
            m_storage.emplace<Array>(std::move(elements));
        }

        //  OPERATOR METHODS  //

        Value& operator=(Value&&) = default;
        Value& operator=(const Value&) = default;

        inline constexpr bool operator==(const Value& other) const noexcept { return m_storage == other.m_storage; }
        inline constexpr bool operator!=(const Value& other) const noexcept { return m_storage != other.m_storage; }

        /// @brief Handles converting the instance to a boolean.
        inline constexpr operator bool() const noexcept {
            static constexpr auto s_overloads = Overloads{
                [](Null) -> bool { return false; },
                [](Boolean value) -> bool { return value; },
                [](Number value) -> bool { return value != 0; },
                [](const auto& value) -> bool { return value.size(); },
            };

            // determine if suitably truthy
            return m_storage.visit(s_overloads);
        }

        //  PUBLIC METHODS  //

        /// @brief Denotes if a particular typing.
        template <Trivial T>
        inline constexpr bool is() const noexcept {
            return std::holds_alternative<T>(m_storage);
        }

        /// @brief Gets a value representation.
        template <Trivial T>
        inline T* as() noexcept {
            if constexpr (std::same_as<T, Null>) return nullptr;
            else return std::get_if<T>(&m_storage);  // attempt
        }

        /// @brief Gets a value representation.
        template <Trivial T>
        inline const T* as() const noexcept {
            if constexpr (std::same_as<T, Null>) return nullptr;
            else return std::get_if<T>(&m_storage);  // attempt
        }

        /**
         * @brief Denotes if an index exists.
         * @param index                 Index to query.
         */
        inline constexpr bool has(size_t index) const { return is<Array>() ? !(index >= as<Array>()->size()) : false; }

        /**
         * @brief Denotes if a key exists.
         * @param key                   Key to query.
         */
        inline constexpr bool has(const String::View& key) const {
            return is<Object>() ? as<Object>()->contains(Text(key)) : false;
        }

        /**
         * @brief Attempts getting a value at an index.
         * @param index                 Index to get.
         */
        inline Value at(size_t index) const { return m_coalesce<Value>(m_at(index)); }

        /**
         * @brief Attempts getting a value at an index.
         * @param index                 Index to get.
         */
        template <Trivial T>
        inline const T* at(size_t index) const requires(!std::same_as<T, Null>) {
            return m_coalesce<const T*>(m_at(index));
        }

        /**
         * @brief Attempts getting a value at an index.
         * @param index                 Index to get.
         * @param alt                   Preset value.
         */
        template <Arithmetic T>
        inline const T at(size_t index, T alt = static_cast<T>(0)) const requires(!std::same_as<T, Number>) {
            auto* numeric = at<Number>(index);  // prepare
            return numeric ? static_cast<T>(*numeric) : alt;
        }

        /**
         * @brief Attempts getting a value at a key.
         * @param key                   Key to get.
         */
        inline Value at(const String::View& key) const { return m_coalesce<Value>(m_at(key)); }

        /**
         * @brief Attempts getting a value at a key.
         * @param key                   Key to get.
         */
        template <Trivial T>
        inline const T* at(const String::View& key) const requires(!std::same_as<T, Null>) {
            return m_coalesce<const T*>(m_at(key));
        }

        /**
         * @brief Attempts getting a numeric at a key.
         * @param key                   Key to get.
         * @param alt                   Preset value.
         */
        template <Arithmetic T>
        inline const T at(const String::View& key, T alt = static_cast<T>(0)) const requires(!std::same_as<T, Number>) {
            auto* numeric = at<Number>(key);  // prepare now
            return numeric ? static_cast<T>(*numeric) : alt;
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles underlying assertions.
        template <Trivial T>
        $_INLINE_PERF void m_assert() const noexcept {
            $_ASSERT(is<T>(), "JSON::Value is not of type '{0}'", RTTI::Name::of<T>());
        }

        /**
         * @brief Handles return values.
         * @param value                 Value to coalesce.
         */
        template <class T>
        inline T m_coalesce(const Value* value) const {
            if (value == nullptr) return nullptr;  // invalid
            if constexpr (std::same_as<Value, T>) return *value;
            else return value->as<Traits::Unqualified<T>>();
        }

        /**
         * @brief Attempts getting a value at an index.
         * @param index                 Index to get.
         */
        inline const Value* m_at(size_t index) const { return has(index) ? &as<Array>()->at(index) : Null(); }

        /**
         * @brief Gets an underlying value.
         * @param key                   Value to get.
         */
        inline const Value* m_at(const String::View& key) const {
            // ignore when we immediately have a bad value
            if (!is<Object>()) return nullptr;

            // attempt resolving as a suitable object value now
            const auto& object = std::get<Object>(m_storage);
            auto iter = object.find(Text(key));  // find now

            // should be able to resolve suitably now
            return iter == object.cend() ? nullptr : &iter->second;
        }
    };

}  // namespace $::Serde

#endif
