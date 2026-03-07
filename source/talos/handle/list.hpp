#ifndef _TALOS_HANDLE_LIST_HPP
#define _TALOS_HANDLE_LIST_HPP

/// Talos Modules
#include "talos/forward/handle.hpp"
#include "talos/forward/value.hpp"

namespace Talos::Handle {

    /// @brief Linked List of Handles.
    class List {
        //  PROPERTIES  //

        /// @brief Top-most value.
        Handle::Local<Value::Any>* m_head = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit List() = default;

        //  PUBLIC METHODS  //

        /// @brief Current head of list.
        inline Handle::Local<Value::Any>* head() const { return m_head; }

        /**
         * @brief Pops the top-most value.
         * @param previous          Previous local value.
         */
        inline void pop(Handle::Local<Value::Any>* previous = nullptr) { m_head = previous; }

        /**
         * @brief Pushes a handle onto the list.
         * @param next              Next local value.
         */
        inline Handle::Local<Value::Any>* push(Handle::Local<Value::Any>* next) {
            auto* previous = m_head;
            m_head = next;
            return previous;
        }
    };

}  // namespace Talos::Handle

#endif
