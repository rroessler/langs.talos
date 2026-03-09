/// XSIO Modules
#include "xsio/timer/cache.hpp"
#include "xsio/forward/context.hpp"
#include "xsio/timer/event.hpp"
#include "xsio/timer/token.hpp"

/// Forward Declarations
$_FWD(XSIO::Timer, class After)
$_FWD(XSIO::Timer, class Awaken)

//  TYPEDEFS  //

/// @brief Handles awakening sleeping threads.
class XSIO::Timer::Awaken : public Action::Abstract<Awaken> {
    //  PROPERTIES  //

    /// @brief The sleeping thread instance.
    Virtual::Thread* m_thread;

    /// @brief Underlying scheduler instance.
    Async::Scheduler* m_scheduler;

   public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs an awaken action.
     * @param thread                Thread to awaken.
     * @param scheduler             Scheduler instance.
     */
    explicit Awaken(Virtual::Thread* thread, Async::Scheduler* scheduler) : m_thread(thread), m_scheduler(scheduler) {}

    //  PUBLIC METHODS  //

    /**
     * @brief Handles awakening a sleeping thread.
     * @param thread                Context-switch thread.
     * @param processor             Processor to inherit.
     */
    inline void execute(Virtual::Thread*, Virtual::Processor* processor) const final {
        m_thread->awaken(), m_scheduler->schedule(m_thread, processor);
    }
};

/// @brief Handles executing callbacks.
class XSIO::Timer::After : public Action::Abstract<After> {
    //  PROPERTIES  //

    /// @brief Underlying callback handler.
    Callback m_callback;

   public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a callback action.
     * @param callback              Callback to run.
     */
    explicit After(Callback callback) : m_callback(callback) {}

    //  PUBLIC METHODS  //

    /**
     * @brief Handles running the bound callback.
     * @param thread                Context-switch thread.
     * @param processor             Processor to inherit.
     */
    inline void execute(Virtual::Thread* thread, Virtual::Processor* processor) const final {
        m_callback(thread, processor);
    }
};

//  PUBLIC METHODS  //

void XSIO::Timer::Cache::fire(Virtual::Thread* thread, Virtual::Processor* processor) {
    // prepare a mutex for firing events now
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);

    // get the current timestamp value to be used
    auto now = Point();

    // and fire events whilst possible to do so
    for (; !m_events.empty(); m_pop()) {
        auto& event = m_events.front();
        if (event.timestamp() > now) break;
        event.fire(thread, processor);
    }
}

bool XSIO::Timer::Cache::cancel(Identifier timer) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // prepare a mutex so we can erase an event
    auto predicate = [timer](const Timer::Event& event) { return event.identifier() == timer; };
    auto iterator = std::ranges::find_if(m_events, predicate);  // attempt finding the iterator
    return iterator == m_events.end() ? false : (m_events.erase(iterator), true);
}

void XSIO::Timer::Cache::suspend(Virtual::Thread* thread, const Ticks& duration) {
    return suspend(thread, Timer::Point() + duration);
}

void XSIO::Timer::Cache::suspend(Virtual::Thread* thread, const Point& timestamp) {
    // prepare a unique lock to be used
    auto lock = $::Lock::scope(m_mutex);

    // prepare a callback to be used for the callback
    Context::Callback callback = [timestamp, &lock](Virtual::Thread* sleeping, Virtual::Processor* processor) {
        auto* timers = processor->timers();  // get the current timers now
        auto awaken = $::New().unique<Awaken>(sleeping, timers->m_scheduler);
        timers->m_push(timestamp, std::move(awaken)), lock.unlock();
    };

    // and attempt suspending now
    Switch::yield_to_scheduler(thread, Virtual::State::WAITING, std::move(callback));
}

XSIO::Timer::Token XSIO::Timer::Cache::schedule(const Ticks& duration, Callback callback) {
    return schedule(Timer::Point() + duration, std::move(callback));
}

XSIO::Timer::Token XSIO::Timer::Cache::schedule(const Point& timestamp, Callback callback) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // lock before preparing
    return m_push(timestamp, $::New().unique<After>(std::move(callback)));
}

XSIO::Timer::Token XSIO::Timer::Cache::schedule(const Ticks& duration, $::Ptr::Unique<Action>&& action) {
    return schedule(Timer::Point() + duration, std::move(action));
}

XSIO::Timer::Token XSIO::Timer::Cache::schedule(const Point& timestamp, $::Ptr::Unique<Action>&& action) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    return m_push(timestamp, std::move(action));
}

//  PRIVATE METHODS  //

void XSIO::Timer::Cache::m_pop() { std::ranges::pop_heap(m_events, Comparator()), m_events.pop_back(); }
XSIO::Timer::Token XSIO::Timer::Cache::m_push(const Point& timestamp, $::Ptr::Unique<Action>&& action) {
    auto timer = m_events.emplace_back(Event(timestamp, std::move(action))).identifier();
    return std::ranges::push_heap(m_events, Comparator()), Token(timer, m_scheduler);
}
