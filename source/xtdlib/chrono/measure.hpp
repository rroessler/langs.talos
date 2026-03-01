#ifndef _XTDLIB_CHRONO_MEASURE_HPP
#define _XTDLIB_CHRONO_MEASURE_HPP

/// Library Modules
#include "xtdlib/chrono/point.hpp"

namespace $::Clock {

    /// @brief Handles taking runtime measurements.
    static inline constexpr struct {
        //  TYPEDEFS  //

        /// @brief Return based results.
        template <class R>
        using Result = std::conditional_t<std::is_void_v<R>, Chrono::Duration, std::pair<R, Chrono::Duration>>;

        /// @brief Timing Callback.
        template <class R>
        using Callback = Functor::Unique<R()>;

        //  OPERATOR METHODS  //

        /// @brief Gets the current performance time-point.
        inline constexpr Chrono::Point operator()() const { return m_now(); }

        /**
         * @brief Handles running a measurement.
         * @param callback                  Callback to measure.
         */
        inline constexpr Chrono::Duration operator()(Callback<void>&& callback) const {
            return apply<void>(std::move(callback));
        }

        //  PUBLIC METHODS  //

        /**
         * @brief Handles running a typed measurement.
         * @param callback                  Callback to measure.
         */
        template <class R>
        inline constexpr Result<R> apply(Callback<R>&& callback) const {
            auto start = m_now();  // prepare the starting value to be used
            if constexpr (std::same_as<void, R>) return callback(), m_now() - start;
            else return Result<R>{ callback(), m_now() - start };
        }

        /**
         * @brief Allows decomposing any typed measurement.
         * @param callback                  Callback to measure.
         */
        template <class F>
        inline constexpr Result<std::invoke_result_t<F>> apply(F&& callback) const {
            return apply(Callback<std::invoke_result_t<F>>(std::move(callback)));
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Ensures using the correct timing.
        inline constexpr Chrono::Point m_now() const noexcept { return Chrono::Point(Performance); }
    } Measure;

}  // namespace $::Clock

#endif
