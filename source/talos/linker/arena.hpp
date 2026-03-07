#ifndef _TALOS_LINKER_ARENA_HPP
#define _TALOS_LINKER_ARENA_HPP

/// Talos Modules
#include "talos/bytecode/routine.hpp"
#include "talos/forward/function.hpp"
#include "talos/linker/buffer.hpp"
#include "talos/linker/records.hpp"

namespace Talos::Linker {

    /// @brief Linker Arena.
    struct Arena : public $::Printable {
        //  PROPERTIES  //

        /// @brief Associated bytecode buffer.
        Buffer bytecode = {};

        /// @brief Bound resource for shared routine information.
        $::URI::View resource = $::URI::Anonymous();

        /// @brief Bound constant values.
        std::vector<Value::Any> constants = {};

        /// @brief All interned string values.
        std::vector<String::Intern> strings = {};

        /// @brief Coinciding functions available.
        std::vector<$::Ptr::Unique<Function::Info>> functions = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted arena instance.
        constexpr Arena() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing arenas.
         * @param os                    Output stream.
         * @param self                  Arena to print.
         */
        static void m_print($::Stream::Output& os, const Arena& self);
    };

}  // namespace Talos::Linker

#endif
