#ifndef _XSIO_ASYNC_STORAGE_HPP
#define _XSIO_ASYNC_STORAGE_HPP

/// C++ Modules
#include <stack>

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/forward/memory.hpp"
#include "xsio/forward/virtual.hpp"
#include "xsio/task/queue.hpp"

namespace XSIO::Async {

    /// @brief Asynchronous Runtime Storage.
    struct Storage {
        //  PROPERTIES  //

        /// @brief Underlying task queue.
        $::Ptr::Unique<Task::Queue> tasks = $::New().unique<Task::Queue>();

        /// @brief Available runtime mutexes.
        struct {
            $::Mutex::Auto stacks;      // Stack creation mutex.
            $::Mutex::Auto threads;     // Thread operation mutex.
            $::Mutex::Auto processors;  // Processor operation mutex.
        } mutex;

        /// @brief Instantiated items.
        struct {
            std::vector<$::Ptr::Unique<Memory::Stack>> stacks;
            std::vector<$::Ptr::Unique<Virtual::Thread>> threads;
            std::vector<$::Ptr::Unique<Virtual::Worker>> workers;
            std::vector<$::Ptr::Unique<Virtual::Processor>> processors;
        } instances;

        /// @brief All items that are free/idling.
        struct {
            std::stack<Memory::Stack*> stacks;
            std::stack<Virtual::Thread*> threads;
            std::stack<Virtual::Processor*> processors;
        } free;

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted cache.
        explicit Storage() = default;
    };

}  // namespace XSIO::Async

#endif
