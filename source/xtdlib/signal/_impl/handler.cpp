/// Library Includes
#include "xtdlib/signal/handler.hpp"
#include "xtdlib/container/map.hpp"

/// Forward Declarations
$_FWD($::Signal, class Registry)

/// Forward Definitions
$_FWD($::Signal, using Bucket = $::Map::Set<const Handler *>)

//  TYPEDEFS  //

class $::Signal::Registry : public Ensure::Singleton<Registry> {
  //  PROPERTIES  //

  /// @brief Internal mutex for resolution.
  mutable Mutex::Auto m_mutex;

  /// @brief Denotes all the attached handlers.
  Map::Base<Symbolic, Bucket> m_buckets = {};

public:
  //  PUBLIC METHODS  //

  /**
   * @brief Handles listening for signals.
   * @param handler                 Signal handler.
   * @param code                    Code to use.
   */
  static inline void listen(const Handler *handler, const Code &code) {
    // get the underlying instance to be used
    auto *self = s_instance();

    // lock the instance before continuing
    $_UNUSED $_AUTO = Lock::guard(self->m_mutex);

    // get the associated bucket to be updated
    auto &bucket = self->m_buckets[code.symbolic()];

    // check if we need to bind a suitable signal for this code
    bool attach = bucket.empty() && bucket.emplace(handler).second;

    // and prepare our handler to be assigned for this code
    if (attach) std::signal(code.native(), m_dispatch);
  }

  /**
   * @brief Handles ignoring signals.
   * @param handler                 Signal handler.
   * @param code                    Code to use.
   */
  static inline bool ignore(const Handler *handler, const Code &code) {
    // get the underlying instance to be used
    auto *self = s_instance();

    // lock the instance before continuing
    $_UNUSED $_AUTO = Lock::guard(self->m_mutex);

    // get the associated bucket to be updated
    auto &bucket = self->m_buckets[code.symbolic()];

    // check if we now need to remove the signal handler
    auto empty = bucket.erase(handler) && bucket.empty();

    // and reassign the default handler to be used
    return empty ? std::signal(code.native(), SIG_DFL), true : false;
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles dispatching signals.
   * @param signal                Signal to dispatch.
   */
  static inline void m_dispatch(int32_t signal) { m_dispatch(Code(signal)); }
  static inline void m_dispatch(const Code &code) {
    const auto &bucket = s_instance()->m_buckets[code.symbolic()];
    for (const auto &handler : bucket) handler->raise(code);
  }
};

//  CONSTRUCTORS  //

$::Signal::Handler::~Handler() {}

//  PRIVATE METHODS  //

void $::Signal::Handler::m_listen(const Handler *self, const Code &code) { return Registry::listen(self, code); }
bool $::Signal::Handler::m_ignore(const Handler *self, const Code &code) { return Registry::ignore(self, code); }
