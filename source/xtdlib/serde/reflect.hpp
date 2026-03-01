#ifndef _XTDLIB_SERDE_REFLECT_HPP
#define _XTDLIB_SERDE_REFLECT_HPP

/// Library Modules
#include "xtdlib/serde/codec.hpp"

namespace $::Reflect {

    //  PUBLIC METHODS  //

    /**
     * @brief Handles serializing values.
     * @param encodable                 Value to encode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF Serde::Value encode(const T& encodable, As&&... args) {
        if constexpr (Serde::Constructible<T>) return Serde::Value(encodable);
        else return Serde::Encoder<T, As...>::encode(encodable, std::forward<As>(args)...);
    }

    /**
     * @brief Handles serializing array structures.
     * @param encodable                 Array of values to encode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF Serde::Array encode(const std::vector<T>& encodable, As&&... args) {
        auto length = encodable.size();      // prepare the base size
        auto output = Serde::Array(length);  // prepare the base array
        for (size_t ii = 0; ii < length; ++ii) output[ii] = encode<T, As...>(encodable[ii], std::forward<As>(args)...);
        return output;  // return the final resulting array
    }

    /**
     * @brief Handles serializing object structures.
     * @param encodable                 Object of values to encode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF Serde::Object encode(const Dict<T>& encodable, As&&... args) {
        auto output = Serde::Object();  // prepare the base object
        for (const auto& [key, value] : encodable) output[key] = encode<T, As...>(value, std::forward<As>(args)...);
        return output;  // return the final resulting object
    }

    /**
     * @brief Handles deserializing values.
     * @param decodable                 Value to decode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF T decode(const Serde::Value& decodable, As&&... args) {
        if constexpr (Serde::Trivial<T>) return *decodable.as<T>();  // basic cast to value now
        else if constexpr (Serde::Arithmetic<T>) return static_cast<T>(*decodable.as<Serde::Number>());
        else return Serde::Decoder<T, As...>::decode(decodable, std::forward<As>(args)...);  // attempt now
    }

    /**
     * @brief Handles deserializing values.
     * @param decodable                 Value to decode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF std::vector<T> decode(const Serde::Array& decodable, As&&... args) {
        auto output = std::vector<T>();    // prepare the return typing
        output.reserve(decodable.size());  // ensure we pre-reserve size
        for (const auto& value : decodable) output.emplace_back(decode<T, As...>(value, std::forward<As>(args)...));
        return output;  // and return the resulting output now
    }

    /**
     * @brief Handles deserializing values.
     * @param decodable                 Value to decode.
     * @param args                      Additional arguments.
     */
    template <class T, class... As>
    $_INLINE_PERF Dict<T> decode(const Serde::Object& decodable, As&&... args) {
        auto output = Dict<T>();  // prepare the return typing
        for (const auto& [key, value] : decodable) output[key] = decode<T, As...>(value, std::forward<As>(args)...);
        return output;  // return the resulting output now
    }

}  // namespace $::Reflect

#endif
