#ifndef _XTDLIB_STRING_CONVERT_HPP
#define _XTDLIB_STRING_CONVERT_HPP

/// C++ Includes
#include <ranges>

/// Library Includes
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Convert {

    /**
     * @brief Handles stringifying values.
     * @param self                  Item to stringify.
     */
    template <class T, class... As>
    static inline String::Buffer stringify(const T& self, As&&... args) {
        if constexpr (!std::derived_from<T, Printable>) return fmt::to_string(self);
        else return Printable::Expose<T>::stringify(self, std::forward<As>(args)...);
    }

    /**
     * @brief Handles converting a string to lowercase.
     * @param buffer                Buffer to capitalize.
     */
    static inline int32_t lowercase(int32_t ch) { return std::tolower(ch); }
    static inline String::Buffer lowercase(const $::String::View& buffer) {
        String::Buffer output;  // prepare the output string
        for (const auto& ch : buffer) output += lowercase(ch);
        return output;  // and return the final output
    }

    /**
     * @brief Handles converting a string to uppercase.
     * @param buffer                Buffer to capitalize.
     */
    static inline int32_t uppercase(int32_t ch) { return std::toupper(ch); }
    static inline String::Buffer uppercase(const $::String::View& buffer) {
        String::Buffer output;  // prepare the output string
        for (const auto& ch : buffer) output += uppercase(ch);
        return output;  // and return the final output
    }

    /**
     * @brief Handles capitalizing a singular word.
     * @param buffer                Buffer to capitalize.
     */
    static inline String::Buffer capitalize(const String::View& buffer) {
        if (buffer.empty()) return String::Buffer(buffer);  // ignore if empty
        return uppercase(buffer.substr(0, 1)) + String::Buffer(buffer.substr(1));
    }

    /**
     * @brief Handles joining multiple arguments.
     * @param items                 Items to join.
     * @param delimiter             Delimiter to use.
     */
    template <class T>
    static inline String::Buffer join(const std::vector<T>& items, const $::String::View& delimiter = ", ") {
        if constexpr (!requires(T t) { *t; }) return fmt::format("{0}", fmt::join(items, delimiter));
        else {
            auto predicate = [](const T& item) -> const auto& { return *item; };  // prepare predicate
            return fmt::format("{0}", fmt::join(items | std::views::transform(predicate), delimiter));
        }
    }

    /**
     * @brief Handles joining multiple arguments.
     * @param items                 Items to join.
     * @param delimiter             Delimiter to use.
     */
    template <class... As>
    static inline String::Buffer join(As&&... items, const $::String::View& delimiter = ", ") {
        return join(std::vector({ std::forward<As>(items)... }), delimiter);
    }

}  // namespace $::Convert

#endif
