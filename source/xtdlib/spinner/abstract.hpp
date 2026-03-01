#ifndef _XTDLIB_SPINNER_ABSTRACT_HPP
#define _XTDLIB_SPINNER_ABSTRACT_HPP

/// Library Modules
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/mutex/light.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/pointer/shared.hpp"
#include "xtdlib/pointer/unique.hpp"
#include "xtdlib/spinner/options.hpp"
#include "xtdlib/string/convert.hpp"
#include "xtdlib/terminal/ansi.hpp"
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/thread/handle.hpp"

namespace $::Spinner {

    /// @brief Spinner Abstraction.
    class $_ABSTRACT Abstract : public Ptr::Castable<Abstract> {
        //  PROPERTIES  //

        /// @brief Forces a display reset.
        bool m_reset = false;

        /// @brief Denotes if currently completed.
        bool m_complete = false;

        /// @brief Current frame to be shown.
        uint32_t m_frame = 0;

        /// @brief Current spinner options.
        Options m_options = {};

        /// @brief Assigned mutex thread.
        mutable Mutex::Light m_mutex;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted spinner instance.
        constexpr Abstract() = default;

        /**
         * @brief Constructs a spinner.
         * @param options           Options to inherit.
         */
        constexpr Abstract(const Options& options) : m_options(options) {}

        /**
         * @brief Constructs a spinner.
         * @param text              Initial text value.
         */
        constexpr Abstract(const String::Buffer& text) : Abstract({ .suffix = text }) {}

        /// @brief Handles dismissing the spinner.
        virtual ~Abstract() { dismiss(); }

        //  PUBLIC METHODS  //

        /// @brief Gets the associated options.
        inline constexpr const Options& options() const { return m_options; }

        /// @brief Allows updating the underlying tick-value.
        inline constexpr const Chrono::Duration& tick() const { return m_options.tick; }
        inline Abstract& tick(const Chrono::Duration& duration) { return m_override(m_options.tick, duration); }

        /// @brief Allows updating current prefix text.
        inline constexpr String::View prefix() const { return m_options.prefix; }
        inline Abstract& prefix(const ANSI& text) { return prefix(Convert::stringify(text)); }
        inline Abstract& prefix(const String::Buffer& text) { return m_override(m_options.prefix, text); }

        /// @brief Allows updating current suffix text.
        inline constexpr String::View suffix() const { return m_options.suffix; }
        inline Abstract& suffix(const ANSI& text) { return suffix(Convert::stringify(text)); }
        inline Abstract& suffix(const String::Buffer& text) { return m_override(m_options.suffix, text); }

        /**
         * @brief Handles dismissing the spinner.
         * @param text                      Dismissal text.
         */
        inline void dismiss(const String::Buffer& text = "") {
            $_AUTO $_UNUSED = Lock::guard(m_mutex);
            if (m_complete) return;  // latch now
            m_complete = true, m_dismiss();

            // ensure the cursor is available before writing the next message
            m_cursor(true);

            // show the completion message now as necessary
            m_clear(), m_options.os << '\r' << text << (text.empty() ? "" : "\n");

            // and re-show the cursor state now as necessary
            m_options.os.flush();
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles clearing lines as necessary.
        inline void m_clear() {
            if (auto* fd = Terminal::as(m_options.os)) std::fputs("\033[K", fd);
            m_reset = false;  // always ensure we have our reset toggled
        }

        /// @brief Handles dismissing the spinner instance.
        virtual inline void m_dismiss() {}

        /// @brief Handles checking quit conditions.
        virtual inline bool m_running() const { return !m_complete; }

        /// @brief Handles incoming sleep handling.
        virtual inline void m_sleep() const noexcept { Thread::This::sleep_for(m_options.tick.underlying()); }

        /**
         * @brief Handles overriding properties.
         * @param property                  Property to write.
         * @param next                      Next value to update.
         */
        template <class T, std::convertible_to<T> U = T>
        inline Abstract& m_override(T& property, const U& next) {
            $_UNUSED $_AUTO = Lock::guard(m_mutex);
            return m_reset = true, property = next, *this;
        }

        /**
         * @brief Toggles the current cursor state.
         * @param state                     Cursor state.
         */
        inline void m_cursor(bool state) {
            if (auto* fd = Terminal::as(m_options.os)) std::fputs(state ? "\033[?25h" : "\033[?25l", fd);
        }

        /// @brief Handles writing the current progress details.
        inline void m_writer() {
            // ensure the cursor state is hidden
            m_cursor(false);

            // handle dumping the spinner whilst running
            while (m_running()) m_print(), m_sleep();
        }

        /// @brief Handles dumping the current details.
        inline void m_print() {
            // ensure we lock whenever we write
            $_UNUSED $_AUTO = Lock::guard(m_mutex);

            // when a reset is called for, clear the line
            if (m_reset) m_clear();

            // determine the padding to be used
            auto padding = m_options.prefix.empty() || m_options.prefix.ends_with(' ') ? "" : " ";

            // show the leading prefix text now
            m_options.os << m_options.prefix << padding;

            // show the current frame value now
            if (const auto& frames = m_options.frames; frames.size()) m_options.os << frames[m_frame % frames.size()];

            // show the trailing suffix text now
            m_options.os << (m_options.suffix.starts_with(' ') ? "" : " ") << m_options.suffix << '\r';

            // fix up the incoming details for frame
            m_options.os.flush(), m_frame += 1;
        }
    };

    /// @brief Basic Spinner Implementation.
    class Basic : public Abstract {
        //  PROPERTIES  //

        /// @brief Underlying joinable thread.
        Thread::Handle m_thread;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs the thread instance.
         * @param args              Spinner options.
         */
        template <class... As>
        constexpr Basic(As&&... args) : Abstract(std::forward<As>(args)...), m_thread(&Basic::m_writer, this) {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles dismissing the internal thread.
        inline void m_dismiss() final { m_thread.join(); }
    };

    /// @brief Common Spinner Reference.
    using Shared = Ptr::Shared<Abstract>;

}  // namespace $::Spinner

#endif
