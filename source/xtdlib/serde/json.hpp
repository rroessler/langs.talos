#ifndef _XTDLIB_SERDE_JSON_HPP
#define _XTDLIB_SERDE_JSON_HPP

/// Library Includes
#include "xtdlib/serde/reflect.hpp"
#include "xtdlib/serde/value.hpp"

namespace $::JSON {

    /**
     * @brief Handles parsing JSON values.
     * @param json                      JSON to parse.
     * @param comments                  Comments flag.
     */
    Serde::Expected<Serde::Value> parse(const String::View& json, bool comments = false);

    /**
     * @brief Handles parsing JSON values.
     * @param json                      JSON to parse.
     * @param comments                  Comments flag.
     */
    template <class T>
    static inline Serde::Expected<T> parse(const String::View& json, bool comments = false) {
        return parse(json, comments).transform([](const Serde::Value& value) { return Reflect::decode<T>(value); });
    }

    /**
     * @brief Handles stringifying JSON values.
     * @param value                     Value to stringify.
     */
    Serde::Expected<Serde::Text> stringify(const Serde::Value& value);

    /**
     * @brief Handles stringifying JSON values.
     * @param value                     Value to stringify.
     */
    template <class T>
    static inline Serde::Expected<Serde::Text> stringify(const T& value) {
        if constexpr (std::convertible_to<T, Serde::Value>) return stringify(Serde::Value(value));
        else return stringify(Reflect::encode(value));  // otherwise must encode the value now
    }

}  // namespace $::JSON

#endif
