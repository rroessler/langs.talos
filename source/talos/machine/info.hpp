#ifndef _TALOS_MACHINE_INFO_HPP
#define _TALOS_MACHINE_INFO_HPP

/// Talos Modules
#include "talos/forward/machine.hpp"
#include "talos/function/callback.hpp"
#include "talos/function/info.hpp"

namespace Talos::Machine {

    /// @brief Prepare a native reference typing.
    using Callback = Reference (*)(Runtime::Isolate*, const Function::Arguments&);

    /// @brief Machine Code Information.
    class Info : public $::Printable {
        //  PROPERTIES  //

        /// @brief Maximum local stack count.
        size_t m_locals = 0;

        /// @brief Underlying jitted callback.
        Callback m_callback = nullptr;

        /// @brief Underlying function information.
        const Function::Info* m_info = nullptr;

        /// @brief The associated disassembly information.
        $::String::Buffer m_disassembly = "";

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs machine code callee details.
         * @param info              Function information.
         */
        explicit Info(const Function::Info* info = nullptr) : m_info(info) {}

        //  PUBLIC METHODS  //

        /// @brief Minimum/maximum argument counts.
        inline constexpr size_t arity() const noexcept { return m_info->arity(); }
        inline constexpr size_t adicity() const noexcept { return m_info->adicity(); }
        inline constexpr size_t argmax() const noexcept { return m_info->argmax(); }
        inline constexpr size_t leaked() const noexcept { return m_info->leaked(); }

        /// @brief Associated variable counts.
        inline constexpr size_t& locals() noexcept { return m_locals; }
        inline constexpr size_t locals() const noexcept { return m_locals; }

        /// @brief Denotes if this is the "main" module function information.
        inline constexpr bool main() const noexcept { return m_info->main(); }

        /// @brief Gets the underlying bytecode arena.
        inline constexpr const Linker::Arena* arena() const noexcept { return m_info->arena(); }

        /// @brief Gets the underlying native code callback.
        inline constexpr Callback& callback() noexcept { return m_callback; }
        inline constexpr Callback callback() const noexcept { return m_callback; }

        /// @brief Gets the bound resource value.
        inline constexpr $::URI::View resource() const noexcept { return m_info->resource(); }

        /// @brief Gets the incoming disassembly details.
        inline constexpr $::String::Buffer& disassembly() noexcept { return m_disassembly; }
        inline constexpr $::String::View disassembly() const noexcept { return m_disassembly; }

        /**
         * @brief Allows executing the callback directly.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to call.
         */
        inline constexpr Value::Any callback(
            Runtime::Isolate* isolate, const Function::Arguments& args) const noexcept {
            return Value::Any(m_callback(isolate, args));
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing machine callees.
         * @param os                    Output stream.
         * @param self                  Info to print.
         */
        static void m_print($::Stream::Output& os, const Info& self);
    };

}  // namespace Talos::Machine

#endif
