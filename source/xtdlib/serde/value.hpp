#ifndef _XTDLIB_SERDE_VALUE_HPP
#define _XTDLIB_SERDE_VALUE_HPP

/// Library Includes
#include "xtdlib/lambda/visitor.hpp"
#include "xtdlib/string/buffer.hpp"

/// Forward Declarations
$_FWD($::Serde, class Value)

/// Forward Definitions
$_FWD($::Serde, using Boolean = bool)
$_FWD($::Serde, using Number = double)
$_FWD($::Serde, using Text = String::Buffer)
$_FWD($::Serde, using Null = std::nullptr_t)
$_FWD($::Serde, using Array = std::vector<Value>)
$_FWD($::Serde, using Object = std::map<Text, Value>)

namespace $::Serde {

/// @brief Denotes expected results from encoding/decoding.
template <class T> using Result = std::expected<T, Text>;

/// @brief Generic Serde Value.
class Value {
  //  TYPEDEFS  //

  /// @brief Allow the inspection proxy access.
  template <class> friend class Inspect;

  /// @brief Internal storage for values.
  using Storage = std::variant<Boolean, Number, Text, Null, Array, Object>;

  /// @brief Initializer List Typing.
  template <class T> using Initializer = std::initializer_list<typename T::value_type>;

  /// @brief Checks if a value is constructible.
  template <class T> static inline constexpr bool Constructible = std::is_constructible_v<Value, T>;

  /// @brief Checks for an arithemtic value.
  template <class T>
  static inline constexpr bool Arithmetic = !std::is_same_v<T, bool> && (std::is_arithmetic_v<T> || std::is_enum_v<T>);

  /// @brief Checks if an incoming typing is trivial.
  template <class T>
  static inline constexpr bool Trivial = std::same_as<T, Boolean> || std::same_as<T, Number> || std::same_as<T, Text> ||
                                         std::same_as<T, Null> || std::same_as<T, Array> || std::same_as<T, Object>;

protected:
  //  PROPERTIES  //

  /// @brief The value storage.
  Storage m_storage = Null();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs defaulted values.
  constexpr Value() = default;
  constexpr Value(Value &&) = default;
  constexpr Value(const Value &) = default;

  /// @brief Allow construction from "nullish" values.
  constexpr Value(Null) : Value() {}

  /**
   * @brief Constructs a boolean value.
   * @param state                   Boolean value
   */
  constexpr Value(Boolean state) : m_storage(state) {}

  /**
   * @brief Constructs a value from a string.
   * @param buffer                  Text buffer.
   */
  constexpr Value(const Text &text) : m_storage(text) {}
  constexpr Value(const String::View &text) : m_storage(Text(text)) {}

  /**
   * @brief Constructs a value from a numeric.
   * @param numeric                 Numeric value.
   */
  template <class T>
    requires Arithmetic<T>
  constexpr Value(T value) : m_storage(static_cast<Number>(value)) {}

  /**
   * @brief Constructs a value from the given elements.
   * @param elements                Array/Object values.
   */
  constexpr Value(const Array &elements) : m_storage(elements) {}
  constexpr Value(const Object &elements) : m_storage(elements) {}
  constexpr Value(Array &&elements) : m_storage(std::move(elements)) {}
  constexpr Value(Object &&elements) : m_storage(std::move(elements)) {}

  /**
   * @brief Constructs a value from given elements.
   * @param elements                Object initializer.
   */
  constexpr Value(Initializer<Object> &&elements) {
    // attempt emplacing the object instance now
    auto &object = m_storage.emplace<Object>();

    // and update the internal elements to be used now
    for (auto &&pair : elements) object.emplace(pair.first, pair.second);
  }

  /**
   * @brief Constructs a value from given elements.
   * @param elements                Array initializer.
   */
  template <bool = true> constexpr Value(Initializer<Array> &&elements) {
    m_storage.emplace<Array>(std::move(elements));
  }

  //  OPERATOR METHODS  //

  /// @brief Allow the default assignment operators.
  Value &operator=(Value &&) = default;
  Value &operator=(const Value &) = default;

  /// @brief Allow using baseline storage equality.
  inline constexpr bool operator==(const Value &other) const noexcept { return m_storage == other.m_storage; }
  inline constexpr bool operator!=(const Value &other) const noexcept { return m_storage != other.m_storage; }

  /// @brief Handles converting the instance to a boolean.
  inline constexpr operator bool() const noexcept {
    // prepare a visitor for suitable overloads now
    static constexpr auto s_overloads = $::Lambda::Visitor{
        [](Null) -> bool { return false; },
        [](Boolean value) -> bool { return value; },
        [](Number value) -> bool { return value != 0; },
        [](const auto &value) -> bool { return value.size(); },
    };

    // determine if suitably truthy
    return std::visit(s_overloads, m_storage);
  }

  //  PUBLIC METHODS  //

  /// @brief Checks if a value is a particular typing(s).
  template <class... Ts> inline constexpr bool is() const noexcept {
    return (std::holds_alternative<Ts>(m_storage) || ...);
  }

  /// @brief Allows safe access to typed values.
  template <class T> inline constexpr const T *as() const noexcept { return std::get_if<T>(&m_storage); }

  /// @brief Allows safe access to typed defaulted values.
  template <class T> inline constexpr const T &as(const T &alt) const noexcept {
    return is<T>() ? std::get<T>(m_storage) : alt;
  }

  /**
   * @brief Denotes if an index exists.
   * @param index                   Index to query.
   */
  inline constexpr bool has(size_t index) const { return is<Array>() ? index < as<Array>()->size() : false; }

  /**
   * @brief Denotes if a key exists.
   * @param key                     Key to query.
   */
  inline constexpr bool has(const String::View &key) const {
    return is<Object>() ? as<Object>()->contains(Text(key)) : false;
  }

  /**
   * @brief Gets a key-value by index.
   * @param index                   Key value.
   * @param alt                     Alternative.
   */
  inline constexpr Value at(size_t index) const { return m_at<Value>(index, Value()); }
  template <class T> inline constexpr const T *at(size_t index) const { return m_at<T>(index); }
  template <class T> inline constexpr T at(size_t index, const T &alt) const { return m_at<T>(index, alt); }

  /**
   * @brief Gets a key-value by text.
   * @param key                     Key value.
   * @param alt                     Alternative.
   */
  inline constexpr Value at(const String::View &key) const { return m_at(Text(key), Value()); }
  template <class T> inline constexpr const T *at(const String::View &key) const { return m_at<T>(Text(key)); }
  template <class T> inline constexpr T at(const String::View &key, const T &alt) const {
    return m_at<T>(Text(key), alt);
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Resolves generically typed, keyed values.
  inline constexpr const Value *m_at(size_t index) const { return has(index) ? &as<Array>()->at(index) : nullptr; }
  inline constexpr const Value *m_at(const Text &key) const { return has(key) ? &as<Object>()->at(key) : nullptr; }

  /**
   * @brief Gets a safe key reference.
   * @param key                 Key to use.
   */
  template <class T, class K> inline constexpr const T *m_at(const K &key) const {
    // resolve the keyed value to get
    if (auto *value = m_at(key)) {
      if constexpr (std::same_as<T, Value>) return value;
      else return value->template as<T>(); // cast here
    }

    // otherwise we have an invalid value
    return nullptr;
  }

  /**
   * @brief Allows forcing a default value.
   * @param key                 Key to use.
   * @param alt                 Alternative.
   */
  template <class T, class K> inline constexpr T m_at(const K &key, const T &alt) const {
    // resolved the keyed value to get
    if (auto *value = m_at(key)) {
      if constexpr (std::same_as<T, Value>) return *value; // resolve
      else if constexpr (Trivial<T>) return value->template as<T>(alt);
      else if constexpr (Arithmetic<T>) {
        auto *numeric = value->template as<Number>();
        if (numeric) return static_cast<T>(*numeric);
      }
    }

    // return the alternative immediately
    return alt;
  }
};

} // namespace $::Serde

#endif
