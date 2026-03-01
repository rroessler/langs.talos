#ifndef _XTDLIB_ASYNC_ATOMIC_HPP
#define _XTDLIB_ASYNC_ATOMIC_HPP

/// C++ Modules
#include <atomic>

/// Library Includes
#include "xtdlib/debug/assert.hpp"

namespace $ {

    /// @brief Atomic Container Class.
    template <class T>
    struct Atomic : public std::atomic<T> {
        //  TYPEDEFS  //

        using std::atomic<T>::atomic;
        using std::atomic<T>::operator=;

        //  PUBLIC METHODS  //

        /**
         * @brief Weak CAS handler.
         * @param expected              Current expected value.
         * @param desired               Desired exchange value.
         * @param order                 Memory ordering to use.
         */
        inline bool compare_exchange_weak(T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
            return std::atomic<T>::compare_exchange_weak(expected, desired, order);
        }

        /**
         * @brief Strong CAS handler.
         * @param expected              Current expected value.
         * @param desired               Desired exchange value.
         * @param order                 Memory ordering to use.
         */
        inline bool compare_exchange_strong(
            T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
            return std::atomic<T>::compare_exchange_strong(expected, desired, order);
        }

        /**
         * @brief Asserted CAS handler.
         * @param expected              Current expected value.
         * @param desired               Desired exchange value.
         * @param order                 Memory ordering to use.
         */
        inline void compare_exchange_assert(
            T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
            if (compare_exchange_strong(expected, desired, order)) return;
            T actual = *this;  // get the actual details to be used

            // builder the details about this swap
            auto builder = std::stringstream();

            // construct the details for the compare-and-swap
            builder << "Desired: '" << m_format(desired) << "', ";
            builder << "Expected: '" << m_format(expected) << "', ";
            builder << "Actual: '" << m_format(actual) << "'";

            // and show to developers where this failed
            $_ABORT("Failed compare-and-swap assertion! {0}", builder.str());
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles formatting values.
         * @param value                 Value to format.
         */
        static inline $::String::Buffer m_format(T value) {
            if constexpr (!std::is_scoped_enum_v<T>) return fmt::to_string(value);
            else return fmt::to_string(fmt::underlying(value));  // format out now
        }
    };

}  // namespace $

#endif