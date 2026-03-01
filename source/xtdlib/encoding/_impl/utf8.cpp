/// XTD Modules
#include "xtdlib/encoding/utf8.hpp"
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/io/print.hpp"
#include "xtdlib/macros/forward.hpp"

/// Forward Declarations
$_FWD(char* append(uint32_t, char*), $::Encoding::UTF8)

//  PUBLIC METHODS  //

/**
 * @brief Helper method to append to a buffer.
 * @param cp                    Unicode codepoint.
 * @param buffer                Buffer to append.
 */
inline char* $::Encoding::UTF8::append(uint32_t cp, char* buffer) {
    // declare as currently invalid now
    if (!$::Encoding::UTF8::validate(cp)) return nullptr;

    // emplace onto the buffer as needed
    if (cp < 0x80) *(buffer++) = static_cast<char>(cp);
    else if (cp < 0x800) {
        *(buffer++) = static_cast<char>((cp >> 6) | 0xc0);
        *(buffer++) = static_cast<char>((cp & 0x3f) | 0x80);
    } else if (cp < 0x10000) {
        *(buffer++) = static_cast<char>((cp >> 12) | 0xe0);
        *(buffer++) = static_cast<char>(((cp >> 6) & 0x3f) | 0x80);
        *(buffer++) = static_cast<char>((cp & 0x3f) | 0x80);
    } else {
        *(buffer++) = static_cast<char>((cp >> 18) | 0xf0);
        *(buffer++) = static_cast<char>(((cp >> 12) & 0x3f) | 0x80);
        *(buffer++) = static_cast<char>(((cp >> 6) & 0x3f) | 0x80);
        *(buffer++) = static_cast<char>((cp & 0x3f) | 0x80);
    }

    // return the final buffer value
    return buffer;
}

$::String::Buffer $::Encoding::UTF8::from(uint32_t cp) {
    char buffer[4];  // only expect maximum 4-bytes
    char* end = append(cp, buffer);
    return { buffer, static_cast<size_t>(end - buffer) };
}

uint32_t $::Encoding::UTF8::rune(const $::String::View& view, size_t unit) {
    return rune(view.data(), view.size(), unit);
}

uint32_t $::Encoding::UTF8::rune(const char* buffer, size_t size, size_t unit) {
    return rune(buffer, buffer + size, unit);
}

uint32_t $::Encoding::UTF8::rune(const char* buffer, const char* end, size_t unit) {
    // prepare the code-point to be used now
    uint32_t cp;

    // attempt peeking until the necessary unit now
    for (size_t ii = 0; ii < unit; ++ii) $_ASSERT(buffer < end), buffer += length(buffer);

    // attempt running our necessary peek handler now
    return $_EXPECT(peek(buffer, end, cp), "Failed to read UTF-8 rune at {0}", unit), cp;
}

size_t $::Encoding::UTF8::offset(const $::String::View& view, size_t unit) {
    return offset(view.data(), view.size(), unit);
}

size_t $::Encoding::UTF8::offset(const char* buffer, size_t size, size_t unit) {
    return offset(buffer, buffer + size, unit);
}

size_t $::Encoding::UTF8::offset(const char* buffer, $_UNUSED const char* end, size_t unit) {
    // prepare a resulting position now
    auto head = buffer;

    // attempt peeking until the necessary unit now
    for (size_t ii = 0; ii < unit; ++ii) $_ASSERT(buffer < end), buffer += length(buffer);

    // attempt running our necessary peek handler now
    return static_cast<size_t>(buffer - head);
}
