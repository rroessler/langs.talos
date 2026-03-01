#ifndef _XTDLIB_URI_ALIAS_HPP
#define _XTDLIB_URI_ALIAS_HPP

/// Library Modules
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/uri/view.hpp"

namespace $::URI {

    /**
     * @brief Constructs an evaluation buffer.
     * @param description           Description to bind.
     */
    static inline constexpr Buffer Evaluate(const $::String::View& description) {
        return Buffer(Scheme::EVAL, description);
    }

    /**
     * @brief Constructs an evaluation buffer.
     * @param msg                   Format message.
     * @param args                  Arguments to bind.
     */
    template <class... As>
    static inline constexpr Buffer Evaluate(const fmt::format_string<As...> msg, As&&... args) {
        return Evaluate(fmt::format(msg, std::forward<As>(args)...));
    }

    /// @brief Gets the anonymous view.
    static inline constexpr View Anonymous() {
        static auto resource = Evaluate("<anonymous>");
        return resource;  // and return the underlying view now
    }

    /**
     * @brief Constructs an immediate file resource.
     * @param file_path             File-path to bind.
     */
    static inline constexpr Buffer File(const Filesystem::Path& file_path) {
        auto underlying = file_path.string();  // get the underlying view now
        if (file_path.is_absolute()) return Buffer(Scheme::FILE, "localhost", underlying);
        return Buffer(Scheme::HREF, underlying.starts_with("./") ? underlying.substr(2) : underlying);
    }

}  // namespace $::URI

#endif
