/// Library Modules
#include "xtdlib/uri/codec.hpp"
#include "xtdlib/encoding/hex.hpp"
#include "xtdlib/io/print.hpp"
#include "xtdlib/uri/buffer.hpp"

/// Forward Declarations
$_FWD($::URI::Codec, String::Buffer encode(const String::View &))

//  PUBLIC METHODS  //

bool $::URI::Codec::escape(uint8_t ch) {
    // alphabetical and digits should be validly kept
    if (Encoding::ASCII::is_alpha(ch) || Encoding::ASCII::is_digit(ch)) return false;

    // otherwise we keep base on the characters
    switch (ch) {
        // these are the usual base cases
        case '-': $_FALLTHROUGH;
        case '_': $_FALLTHROUGH;
        case '.': $_FALLTHROUGH;
        case '/': return false;

        // since we normalize our values, we ignore windows separators
        case '\\': $_FALLTHROUGH;

        // otherwise fail here
        default: return true;
    }
}

$::URI::Buffer $::URI::Codec::parse(const String::View &buffer) { return Buffer::m_parse(buffer); }

$::URI::Buffer $::URI::Codec::decode(const String::View &buffer) {
    // prepare the decoded buffer to be used
    auto decoded = String::Buffer();

    // prepare the hex-check now as needed
    static constexpr auto is_hex = [](char a, char b) { return Encoding::HEX::is(a) && Encoding::HEX::is(b); };

    // iteratively decode the buffer now
    for (auto iter = buffer.begin(), end = buffer.end(); iter != end; ++iter) {
        auto encoded = *iter == '%' && iter + 2 < end && is_hex(*(iter + 1), *(iter + 2));
        if ($_LIKELY(!encoded)) decoded.push_back(*iter);  // regular conversion to be used
        else decoded.push_back(Encoding::HEX::from(*(iter + 1), *(iter + 2))), iter += 2;
    }

    // and finally attempt parsing now
    return parse(decoded);
}

$::String::Buffer $::URI::Codec::encode(const $::String::View &content) {
    // prepare the output buffer to encode into
    auto encoded = String::Buffer();

    // encode each character as necessary now
    for (uint8_t ch : content) {
        if ($_LIKELY(!escape(ch))) encoded.push_back(ch);
        else {
            encoded.push_back('%');  // prepare percent sign
            encoded.push_back(Encoding::HEX::encode(ch / 16));
            encoded.push_back(Encoding::HEX::encode(ch % 16));
        }
    }

    // return the resulting encoded buffer
    return encoded;
}

$::String::Buffer $::URI::Codec::encode(const Buffer &resource) {
    // prepare our content and encoded output
    auto encoded = String::Buffer();

    // get the details to be encoded now
    auto body = resource.body();
    auto authority = resource.authority();

    // start by encoding the scheme to be used
    encoded += encode(resource.scheme()) + ':';

    // stop if the body and authority are empty
    if (authority.empty() && body.empty()) return encoded;

    // then encode the authority if necessary to do so
    if (!authority.empty() || body.starts_with('/')) encoded += "//" + encode(authority);

    // and return the resulting encoded value
    return encoded + encode(body);
}
