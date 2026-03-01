/// XLSP Modules
#include "xlsp/protocol/encoding.hpp"

/// Forward Declarations
$_FWD(template <class F> bool iterate(const $::String::View &, const F &), XLSP::Encoding);

//  PUBLIC METHODS  //

template <class F>
bool XLSP::Encoding::iterate(const $::String::View &view, const F &callback) {
    for (size_t ii = 0; ii < view.size();) {
        uint8_t ch = static_cast<uint8_t>(view.at(ii));
        if ($_LIKELY(!(ch & 0x80))) {
            if (callback(1, 1)) return true;
            ++ii;
            continue;
        }

        // check the UTF-8 length of the codepoint
        size_t length = $::Encoding::UTF8::length(ch);

        // we may have some invalid UTF-8 (eg: length is outside expected ranges)
        if ($_UNLIKELY(length < 2 || length > 4)) {
            if (callback(1, 1)) return true;
            ++ii;  // skip passed the invalid instance
            continue;
        }

        // skip over the trailing bytes now
        ii += length;

        // and update our details now
        if (callback(length, length == 4 ? 2 : 1)) return true;
    }

    // invalid UTF-8 strings will reach here
    return false;
}

size_t XLSP::Encoding::measure(const $::String::View &view, int32_t uu, const Type &encoding) {
    // stop early if necessary to do so
    if (uu <= 0) return 0;

    // prepare the output result now
    size_t out = 0;

    // attempt handling various encodings
    switch (encoding) {
        case Type::UTF8: return view.size();  // should be already valid now
        case Type::UTF16: iterate(view, [&](int32_t u8, int32_t u16) { return out += u8, uu -= u16, uu <= 0; }); break;
        case Type::UTF32: iterate(view, [&](int32_t u8, int32_t) { return out += u8, --uu <= 0; }); break;
        default: $_ABORT("Unsupported encoding: {0}", static_cast<uint8_t>(encoding));  // denote as invalid
    }

    // return the resulting encoding details
    return out;
}
