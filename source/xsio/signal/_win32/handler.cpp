/// XSIO Modules
#include "xsio/signal/handler.hpp"
#include "xsio/async/manager.hpp"

#if $_PLATFORM_WINDOWS

/// POSIX Modules
#include <csignal>

/// Forward Declarations
$_FWD(XSIO::Signal, class Native)

//  X-MACROS  //

/// @brief Internal lookup values.
#define XX_SIGNALS_LOOKUP(X) \
    X(INT)                   \
    X(ILL)                   \
    X(FPE)                   \
    X(TERM)                  \
    X(SEGV)                  \
    X(ABRT)

//  TYPEDEFS  //

/// @brief Native Signal Handler.
class XSIO::Signal::Native : public $::Singleton<Native> {
    //  PROPERTIES  //

    /// @brief Bound mutex value.
    mutable $::Mutex::Auto m_mutex;

    /// @brief Currently bound native callbacks.
    $::Map<const Handler*, Callback> m_callbacks = {};

   public:
    //  CONSTRUCTORS  //

    /// @brief Constructs a native instance.
    explicit Native() {
        // prepare the baseline signal handlers
        std::signal(SIGINT, m_handler);

        // otherwise for harder exceptions, we also catch
        SetUnhandledExceptionFilter(m_filter);
    }

    //  PUBLIC METHODS  //

    /**
     * @brief Handles binding a callback instance.
     * @param handler                   Handler reference.
     * @param callback                  Callback to bind.
     */
    static inline void bind(const Handler* handler, Callback&& callback) {
        auto* self = s_instance();  // get the instance
        $_UNUSED $_AUTO = $::Lock::guard(self->m_mutex);
        self->m_callbacks.emplace(handler, std::move(callback));
    }

    /**
     * @brief Handles removing a callback instance.
     * @param handler                   Handler reference.
     */
    static inline void remove(const Handler* handler) {
        auto* self = s_instance();  // get the instance
        $_UNUSED $_AUTO = $::Lock::guard(self->m_mutex);
        self->m_callbacks.erase(handler);  // erase now
    }

   private:
    //  PRIVATE METHODS  //

    /**
     * @brief Handles incoming signals.
     * @param signal                    Signal to handle.
     */
    static inline void m_handler(int32_t signal) { m_handler(m_resolve(signal)); }
    static inline void m_handler(Symbolic signal) {
        for (const auto& callback : s_instance()->m_callbacks | std::views::values) callback(signal);
    }

    /**
     * Handles incoming exceptions.
     * @param ep                        Exception pointer.
     */
    static inline LONG WINAPI m_filter(EXCEPTION_POINTERS* ep) {
        DWORD code = ep->ExceptionRecord->ExceptionCode;  // allow ignoring the possible to do so now
        if (code == DBG_PRINTEXCEPTION_C || code == DBG_CONTROL_C) return EXCEPTION_CONTINUE_SEARCH;
        return m_handler(SIGSEGV), EXCEPTION_EXECUTE_HANDLER;
    }

    /**
     * @brief Handles resolving signals to a symbolic value.
     * @param signal                    Signal to resolve.
     */
    static inline Symbolic m_resolve(int32_t signal) {
#define X(N, ...) \
    case SIG##N: return Symbolic::N;
        switch (signal) { XX_SIGNALS_LOOKUP(X) default : return Symbolic::UNK; }
#undef X
    }
};

//  CONSTRUCTORS  //

XSIO::Signal::Handler::Handler() {
    Native::bind(this, [this](const Code& code) { m_callback(code); });
}

XSIO::Signal::Handler::~Handler() { Native::remove(this); }

#endif
