#ifndef _TALOS_OBJECT_EXCEPTION_HPP
#define _TALOS_OBJECT_EXCEPTION_HPP

/// Talos Modules
#include "talos/diagnostic/traits.hpp"
#include "talos/iterable/list.hpp"
#include "talos/string/dynamic.hpp"

namespace Talos {

    /// @brief Exception Attributes.
    template <>
    struct Object::Attributes<Object::Exception> {
        //  PROPERTIES  //

        String::Dynamic name;     // Name of exception.
        String::Dynamic message;  // Exception message.

        /// @brief Backtrace list.
        std::vector<Resource::Trace> trace;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a defaulted exception.
         * @param isolate                   Runtime isolate.
         */
        explicit Attributes(Runtime::Isolate* isolate);

        /**
         * @brief Constructs an exception.
         * @param isolate                   Runtime isolate.
         * @param message                   Exception message.
         */
        explicit Attributes(Runtime::Isolate* isolate, String::Dynamic message);
        explicit Attributes(Runtime::Isolate* isolate, const $::String::View& message);

        /**
         * @brief Constructs an exception.
         * @param isolate                   Runtime isolate.
         * @param name                      Name of exception.
         * @param message                   Exception message.
         */
        explicit Attributes(Runtime::Isolate* isolate, String::Dynamic name, String::Dynamic message);
        explicit Attributes(Runtime::Isolate* isolate, const $::String::View& name, const $::String::View& message);
    };

    /// @brief Exception Interface.
    struct Object::Exception : public Object::Abstract<Object::Exception> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr String::Dynamic& name() const noexcept { return m_attrs()->name; }
        inline constexpr String::Dynamic& message() const noexcept { return m_attrs()->message; }
        inline constexpr std::vector<Resource::Trace>& trace() const noexcept { return m_attrs()->trace; }
        inline constexpr $::Stream::Output& format($::Stream::Output& os) const noexcept { return m_format(os); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles formatting exceptions.
         * @param os                     Output stream.
         */
        $::Stream::Output& m_format($::Stream::Output& os) const noexcept;

        /**
         * @brief Handlers yielding exceptions safely.
         * @param self                  Exception instance.
         * @param yield                 Yield callback.
         */
        static void m_yield(const Exception& self, const Globals::Each& yield);

        /**
         * @brief Handles printing values.
         * @param os                    Output stream.
         * @param self                  Exception instance.
         */
        static void m_print($::Stream::Output& os, const Exception& self);
    };

}  // namespace Talos

#endif
