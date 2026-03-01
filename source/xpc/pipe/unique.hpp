#ifndef _XPC_PIPE_UNIQUE_HPP
#define _XPC_PIPE_UNIQUE_HPP

/// XPC Modules
#include "xpc/pipe/handle.hpp"

namespace XPC::Pipe {

    /// @brief Unique Pipe View.
    class $_ABSTRACT Unique {
        //  PROPERTIES  //

        /// @brief Internal handle reference.
        const Handle* m_handle = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        constexpr Unique() = default;

        /**
         * @brief Construct from a given handle.
         * @param handle                    Handle to bind.
         */
        constexpr Unique(const Handle* handle) : m_handle(handle) {}

        /// @brief Allow copy-construction.
        constexpr Unique(const Unique& other) : m_handle(other.m_handle) {}

        /// @brief Allow move-construction.
        constexpr Unique(Unique&& other) : m_handle(other.m_handle) { other.m_handle = nullptr; }

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying reference.
        inline constexpr const Handle* handle() const noexcept { return m_handle; }

        /// @brief Gets the validity of the handle.
        inline constexpr bool invalid() const noexcept { return m_handle == nullptr || *m_handle == Invalid(); }
    };

}  // namespace XPC::Pipe

#endif
