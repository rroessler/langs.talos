#ifndef _XTDLIB_CHRONO_DURATION_HPP
#define _XTDLIB_CHRONO_DURATION_HPP

/// C++ Modules
#include <chrono>

/// Library Includes
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/vendors/fmt.hpp"

/// Exposed Literals
using namespace std::chrono_literals;

//  X-MACROS  //

#define XX_CHRONO_UNITS(X)                     \
    X(Microseconds, std::chrono::microseconds) \
    X(Milliseconds, std::chrono::milliseconds) \
    X(Seconds, std::chrono::seconds)           \
    X(Minutes, std::chrono::minutes)           \
    X(Hours, std::chrono::hours)               \
    X(Days, std::chrono::days)                 \
    X(Years, std::chrono::years)

//  NAMESPACES  //

namespace $::Chrono {

    /// @brief Base Ticks Duration.
    using Ticks = std::chrono::nanoseconds;

    /// @brief Internal Duration Class.
    struct Duration {
        //  TYPEDEFS  //

        /// @brief Underlying Duration Representation.
        template <class R, class P>
        using Underlying = std::chrono::duration<R, P>;

       private:
        //  PROPERTIES  //

        /// @brief Underlying ticks encapsulated.
        Ticks m_ticks = Ticks::zero();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty duration.
        constexpr Duration() = default;

        /**
         * @brief Constructs a duration.
         * @param ticks                     Ticks to bind.
         */
        constexpr Duration(size_t ticks) : m_ticks(ticks) {}

        /**
         * @brief Constructs a duration.
         * @param ticks                     Ticks to bind.
         */
        template <class R, class P>
        constexpr Duration(const Underlying<R, P>& ticks) : m_ticks(std::chrono::duration_cast<Ticks>(ticks)) {}

        //  OPERATOR METHODS  //

        /// @brief Handles all comparison values.
        inline constexpr auto operator<=>(const Duration& other) const noexcept { return m_ticks <=> other.m_ticks; }
        inline constexpr auto operator==(const Duration& other) const noexcept { return m_ticks == other.m_ticks; }

        /// @brief Binary "+" operator.
        friend inline constexpr Duration operator+(const Duration& left, const Duration& right) {
            return { left.m_ticks + right.m_ticks };
        }

        /// @brief Binary "-" operator.
        friend inline constexpr Duration operator-(const Duration& left, const Duration& right) {
            return { left.m_ticks - right.m_ticks };
        }

        /// @brief Binary "*" operator.
        friend inline constexpr Duration operator*(const Duration& left, size_t right) {
            return { left.m_ticks * right };
        }

        /// @brief Binary "/" operator.
        friend inline constexpr Duration operator/(const Duration& left, const size_t right) {
            return { left.m_ticks / right };
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the count in ticks [ns].
        inline constexpr size_t count() const noexcept { return m_ticks.count(); }

        /// @brief Gets the underlying representation.
        inline constexpr Ticks underlying() const noexcept { return m_ticks; }
    };

#define X(N, U, ...)                                      \
    struct N : public Duration {                          \
        constexpr N() = default;                          \
        constexpr N(size_t ticks) : Duration(U(ticks)) {} \
    };

    XX_CHRONO_UNITS(X)
#undef X

}  // namespace $::Chrono

//  SPECIALIZATIONS  //

template <class R, class P>
struct fmt::formatter<$::Chrono::Duration::Underlying<R, P>, char> : fmt::formatter<$::String::View> {
    //  PROPERTIES  //

    /// @brief Internal format specifications.
    fmt::detail::dynamic_format_specs<char> m_specs;

    //  PUBLIC METHODS  //

    /// @brief Handles parsing values.
    constexpr auto parse(fmt::parse_context<char>& ctx) -> const char* {
        return parse_format_specs(ctx.begin(), ctx.end(), m_specs, ctx, fmt::detail::type::double_type);
    }

    /// @brief Handles printing durations.
    auto format(const $::Chrono::Duration::Underlying<R, P>& duration, fmt::format_context& ctx) const
        -> decltype(ctx.out()) {
        // get the baseline specs to be used now
        auto specs = fmt::format_specs(m_specs);
        if (specs.precision < 0) specs.precision = 3;

        // update the presentation type to be used
        specs.set_type(specs.precision >= 0 ? fmt::presentation_type::fixed : fmt::presentation_type::general);

        // prepare our writer to be used
        auto buffer = fmt::basic_memory_buffer<char>();
        auto out = fmt::basic_appender<char>(buffer);

        auto [count, suffix] = m_format(duration.count());
        out = fmt::detail::write<char>(out, count, specs);
        out = fmt::detail::write<char>(out, suffix);

        // and build the final result now
        return fmt::formatter<$::String::View, char>::format({ buffer.data(), buffer.size() }, ctx);
    }

    //  PRIVATE METHODS  //

    /**
     * @brief Handles formatting duration counts.
     * @param count                     Count to format.
     */
    inline constexpr std::pair<double, $::String::View> m_format(double count) const {
        if (std::isnan(count)) return { NAN, "?" };
        if (count < 1000) return { count, "ns" };
        if ((count /= 1000) < 1000) return { count, "us" };
        if ((count /= 1000) < 1000) return { count, "ms" };
        if ((count /= 1000) < 60) return { count, "ss" };
        if ((count /= 60) < 60) return { count, "mm" };
        return { count / 60, "hh" };  // otherwise hours
    }
};

template <>
struct fmt::formatter<$::Chrono::Duration, char> : fmt::formatter<$::Chrono::Ticks, char> {
    //  PUBLIC METHODS  //

    /// @brief Handles printing durations.
    auto format(const $::Chrono::Duration& duration, fmt::format_context& ctx) const -> decltype(ctx.out()) {
        return fmt::formatter<$::Chrono::Ticks, char>::format(duration.underlying(), ctx);
    }
};

//  UNDEFINES  //

#undef XX_CHRONO_UNITS

#endif
