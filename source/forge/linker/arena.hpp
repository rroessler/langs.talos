#ifndef _FORGE_LINKER_ARENA_HPP
#define _FORGE_LINKER_ARENA_HPP

/// Forge Modules
#include "forge/bytecode/routine.hpp"
#include "forge/forward/function.hpp"
#include "forge/linker/buffer.hpp"
#include "forge/linker/records.hpp"

namespace Forge::Linker {

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

}  // namespace Forge::Linker

#endif
