#ifndef _XSIO_SIGNAL_HANDLER_HPP
#define _XSIO_SIGNAL_HANDLER_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/signal/code.hpp"

namespace XSIO::Signal {

    /// @brief Signal Callback Handler.
    using Callback = $::Functor::Unique<void(const Code&)>;

    /// @brief Handles incoming signals.
    class Handler {
        //  PROPERTIES  //

        /// @brief Associated mutex value.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Prepare an initially non-blocking acceptor.
        Callback m_callback = [&](const Code&) {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a signal handler.
        explicit Handler();

        /// @brief Allows removing signal handling.
        ~Handler();

        //  PUBLIC METHODS  //

        /**
         * @brief Binds a signal callback.
         * @param callback              Signal callback.
         */
        inline void bind(Callback&& callback) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_callback = std::move(callback);  // bind
        }

        /**
         * @brief Handles raising a signal instance.
         * @param args                  Arguments to bind.
         */
        template <class... As>
        inline void raise(As&&... args) {
            m_callback(Code(std::forward<As>(args)...));
        }
    };

}  // namespace XSIO::Signal

#endif
