#ifndef _XTDLIB_URI_BUFFER_HPP
#define _XTDLIB_URI_BUFFER_HPP

/// C++ Modules
#include <optional>

/// Library Modules
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/serde/codec.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/system/platform.hpp"
#include "xtdlib/uri/codec.hpp"
#include "xtdlib/uri/scheme.hpp"

namespace $::URI {

    /// @brief URI parts of the form "<scheme>:[//<authority>]<body>".
    class Buffer : public Printable {
        //  TYPEDEFS  //

        /// @brief Allow parsing internal access.
        friend Buffer Codec::parse(const String::View&);

        //  PROPERTIES  //

        /// @brief Starting path index.
        size_t m_body = 0;

        /// @brief Underlying URI buffer.
        String::Buffer m_buffer = "";

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a URI from a file-path.
         * @param body                      Body to encapsulate.
         */
        explicit constexpr Buffer(const String::View& body) : Buffer(Scheme::FILE, body) {}

        /**
         * @brief Constructs a URI.
         * @param scheme                    Scheme to bind.
         * @param body                      Body to encapsulate.
         */
        explicit constexpr Buffer(const String::View& scheme, const String::View& body) : Buffer(scheme, "", body) {}

        /**
         * @brief Constructs a URI.
         * @param scheme                    Scheme to bind.
         * @param authority                 Authority buffer.
         * @param body                      Body to encapsulate.
         */
        explicit constexpr Buffer(const String::View& scheme, const String::View& authority, const String::View& body) {
            // determine the leading slashes to be used (based on the scheme)
            String::Buffer slashes = (authority.size() || scheme == Scheme::FILE ? "//" : "");
            m_body = 1 + scheme.size() + slashes.size() + authority.size();  // set the body

            // construct the underlying URI value now
            m_buffer = String::Buffer(scheme) + ':' + slashes + String::Buffer(authority) + m_normalize(body);
        }

        //  OPERATOR METHODS  //

        /// @brief Checks if a URI is equal to another.
        inline constexpr bool operator==(const Buffer& other) const noexcept { return m_buffer == other.m_buffer; }

        //  PUBLIC METHODS  //

        /// @brief Gets the base buffer value.
        inline constexpr String::View view() const noexcept { return m_buffer; }

        /// @brief Gets the underlying scheme value.
        inline constexpr String::View scheme() const noexcept { return view().substr(0, m_delimiter()); }

        /// @brief Gets the underlying authority value.
        inline constexpr String::View authority() const noexcept {
            auto value = view().substr(0, m_body);
            value = value.substr(m_delimiter() + 1);
            return value.starts_with("//") ? value.substr(2) : value;
        }

        /// @brief Gets the underlying body value.
        inline constexpr String::View body() const noexcept {
            auto value = m_trailing();

#if $_PLATFORM_WINDOWS
            if (scheme() != Scheme::FILE || !value.starts_with('/') || value.size() < 2) return value;
            return value.at(2) == ':' && std::isalpha(view().at(1)) ? value.substr(1) : value;
#else
            return value;
#endif
        }

        /**
         * @brief Gets a relative path from the given body.
         * @param hint                      Directory hint to use.
         */
        inline constexpr String::Buffer relative(const Filesystem::Path& hint = Path::current()) const {
            if (scheme() != Scheme::FILE) return m_buffer;
            return Path::relative(body(), hint).string();
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the ":" delimiter index.
        inline constexpr size_t m_delimiter() const noexcept {
            auto index = m_buffer.find_first_of(':');  // find now
            return $_ASSERT(index != String::View::npos), index;
        }

        /// @brief Gets the unmodified trailing path.
        inline constexpr String::View m_trailing() const noexcept {
            return { m_buffer.data() + m_body, m_buffer.size() - m_body };
        }

        /**
         * @brief Handles normalizing URI paths.
         * @param body                      Body to normalize.
         */
        static inline String::Buffer m_normalize(const String::View& body) { return m_normalize(String::Buffer(body)); }
        static inline String::Buffer m_normalize(String::Buffer buffer) {
#if $_PLATFORM_WINDOWS
            std::replace(buffer.begin(), buffer.end(), '\\', '/');
            if (buffer.size() > 1 && buffer.at(1) == ':') buffer = '/' + buffer;
#endif

            // should be suitably valid now
            return buffer;
        }

        /**
         * @brief Handles parsing URI values.
         * @param view                      View to parse.
         */
        static inline Buffer m_parse(const String::View& view) {
            // prepare some details about the details
            auto offset = view.find(':');
            auto buffer = m_normalize(view);

            // attempt checking for file paths now
            if (offset == String::View::npos || ($_PLATFORM_WINDOWS && offset == 1)) {
                if (Filesystem::Path(view).is_absolute()) return Buffer(Path::canonical(buffer).string());
                return Buffer(Scheme::HREF, buffer.starts_with("./") ? buffer.substr(2) : buffer);
            }

            // pull out the current scheme value now
            auto scheme = buffer.substr(0, offset);
            auto remaining = buffer.substr(offset + 1);

            // ignore parsing an authority if there is none
            if (!remaining.starts_with("//")) return Buffer(scheme, remaining);

            // attempt finding the necessary authority now
            remaining = remaining.substr(2);
            offset = remaining.find('/');

            auto authority = remaining.substr(0, offset);  // resolve our values now
            auto body = offset == String::Buffer::npos ? "" : remaining.substr(offset);

            // and reconstruct the resulting URI again
            return Buffer(scheme, authority, body);
        }

        /**
         * @brief Dumps the current resource value.
         * @param os                        Output stream.
         * @param self                      URI instance.
         */
        static void m_print(Stream::Output& os, const Buffer& self) { os << self.m_buffer; }

        /**
         * @brief Handles encoding a resource value.
         * @param self                      Resource to be encoded.
         */
        static Serde::Value m_encode(const Buffer& self) { return Serde::Value(Codec::encode(self)); }

        /**
         * @brief Handles decoding a resource value.
         * @param value                     Value to decode.
         */
        static Buffer m_decode(const Serde::Value& value) { return Buffer(Codec::decode(*value.as<Serde::Text>())); }
    };

}  // namespace $::URI

#endif
