/// Vendor Modules
#include <glaze/json.hpp>

/// Library Includes
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/serde/json.hpp"

/// Forward Declarations
$_FWD(struct Exposed, $::Serde)
$_FWD(template <bool = false> constexpr glz::opts options(), $::JSON)
$_FWD(template <bool> Serde::Expected<Serde::Value> read(const String::View&), $::JSON)

//  TYPEDEFS  //

/// @brief Allow exposing internal details.
struct $::Serde::Exposed : public Value {
    //  TYPEDEFS  //

    /// @brief Internal access.
    friend struct glz::meta<Value>;

    /// @brief Allow stringification internal access.
    friend Serde::Expected<Text> JSON::stringify(const Value&);

    //  CONSTRUCTORS  //

    /// @brief Allow default construction.
    using Value::Value;
};

//  SPECIALIZATIONS  //

template <>
struct glz::meta<$::Serde::Value> {
    //  TYPEDEFS  //

    /// @brief Underlying meta-typing.
    using T = $::Serde::Value;

    //  PROPERTIES  //

    /// @brief Underlying storage value.
    static constexpr auto value = &$::Serde::Exposed::m_storage;
};

//  PUBLIC METHODS  //

template <bool C>
constexpr glz::opts $::JSON::options() {
    return { .comments = C };
}

template <bool C>
$::Serde::Expected<$::Serde::Value> $::JSON::read(const String::View& buffer) {
    Serde::Value value = Serde::Null();  // prepare value
    auto ec = glz::read<options<C>()>(value, buffer);
    if (ec) return std::unexpected(glz::format_error(ec, buffer));
    return Serde::Expected<Serde::Value>(value);  // valid result
}

$::Serde::Expected<$::Serde::Value> $::JSON::parse(const String::View& json, bool comments) {
    return comments ? read<true>(json) : read<false>(json);
}

$::Serde::Expected<$::Serde::Text> $::JSON::stringify(const Serde::Value& value) {
    auto exposed = static_cast<const Serde::Exposed*>(&value);  // prepare the exposed value
    auto result = glz::write<options<>()>(exposed->m_storage);  // and attempt writing now
    return result.transform_error([](const glz::error_ctx& ec) { return glz::format_error(ec); });
}
