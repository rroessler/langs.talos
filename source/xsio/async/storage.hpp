#ifndef _XSIO_ASYNC_STORAGE_HPP
#define _XSIO_ASYNC_STORAGE_HPP

/// XSIO Includes
#include "xsio/async/options.hpp"
#include "xsio/memory/stack.hpp"
#include "xsio/task/queue.hpp"
#include "xsio/virtual/processor.hpp"
#include "xsio/virtual/thread.hpp"
#include "xsio/virtual/worker.hpp"

namespace XSIO::Async {

/// @brief Asynchronous Runtime Storage.
class Storage {
  //  TYPEDEFS  //

  /// @brief Internal acquisition handler.
  class Acquire {
    //  PROPERTIES  //

    /// @brief Internal reference.
    Storage *m_self;

  public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs an acquirement handler.
     * @param self            Storage instance.
     */
    constexpr Acquire(Storage *self) : m_self(self) {}

    //  OPERATOR METHODS  //

    /// @brief Handles acquiring a thread stack.
    inline constexpr operator Memory::Stack *() {
      $_UNUSED $_AUTO = $::Lock::guard(m_self->mutex.stacks);
      auto &available = m_self->free.stacks; // get available

      // resolve when there are free stacks
      if (available.size()) {
        auto *stack = available.top();
        return available.pop(), stack;
      }

      auto &thread = m_self->options->thread; // construct the next thread stack
      auto stack = $::Unique::New<Memory::Stack>(thread.stack_size, thread.stack_limit);
      return m_self->instances.stacks.emplace_back(std::move(stack)).get();
    }

    /// @brief Handles acquiring a virtual thread.
    inline constexpr operator Virtual::Thread *() {
      $_UNUSED $_AUTO = $::Lock::guard(m_self->mutex.threads);
      auto &available = m_self->free.threads; // get the free instances

      // if we have available threads, then recycle
      if (available.size()) {
        auto *thread = available.top();
        return available.pop(), thread;
      }

      auto thread = $::Unique::New<Virtual::Thread>(); // otherwise create
      return m_self->instances.threads.emplace_back(std::move(thread)).get();
    }

    /// @brief Handles acquiring a virtual processor.
    inline constexpr operator Virtual::Processor *() {
      // prepare the processors mutex now
      $_UNUSED $_AUTO = $::Lock::guard(m_self->mutex.processors);

      // get the free instances firstly
      auto &available = m_self->free.processors;
      if (available.empty()) return nullptr;

      // otherwise we need to pop the top-most free processor
      auto *processor = available.top();
      return available.pop(), processor;
    }
  };

public:
  //  PROPERTIES  //

  /// @brief Bound runtime options.
  const Options *options = $::Global::get<Options>();

  /// @brief Underlying task queue.
  $::Unique::Pointer<Task::Queue> tasks = $::Unique::New<Task::Queue>();

  /// @brief Available runtime mutexes.
  struct {
    $::Mutex::Auto stacks;     // Stack creation mutex.
    $::Mutex::Auto threads;    // Thread operation mutex.
    $::Mutex::Auto processors; // Processor operation mutex.
  } mutex;

  /// @brief Instantiated items.
  struct {
    std::vector<$::Unique::Pointer<Memory::Stack>> stacks;
    std::vector<$::Unique::Pointer<Virtual::Thread>> threads;
    std::vector<$::Unique::Pointer<Virtual::Worker>> workers;
    std::vector<$::Unique::Pointer<Virtual::Processor>> processors;
  } instances;

  /// @brief All items that are free/idling.
  struct {
    std::stack<Memory::Stack *> stacks;
    std::stack<Virtual::Thread *> threads;
    std::stack<Virtual::Processor *> processors;
  } free;

  /// @brief Handles acquiring instances.
  Acquire acquire = {this};

  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted cache.
  explicit Storage() : Storage($::Global::get<Options>()) {}
  explicit Storage(const Options *options) : options(options) {}
};

} // namespace XSIO::Async

#endif
