#ifndef _TALOS_MACHINE_FRAME_HPP
#define _TALOS_MACHINE_FRAME_HPP

/// Talos Modules
#include "talos/engine/frame.hpp"
#include "talos/forward/machine.hpp"
#include "talos/function/arguments.hpp"
#include "talos/function/context.hpp"
#include "talos/machine/info.hpp"

/*
 *
 * The frame-stack for machine-code supports a similar layout to function arguments.
 *
 * |    LABEL    |  OFFSET  |         DESCRIPTION          |
 * | ----------- | -------- | ---------------------------- |
 * |  STK_ENVP   |    0     | The environment context.     |
 * |  STK_ARGV   |    1     | Pointer to stack arguments.  |
 * |  STK_DATA   |    2     | Pointer to local arguments.  |
 *
 */

namespace Talos::Machine::Offset {

    //  PROPERTIES  //

    static inline constexpr size_t STK_ENVP = Function::Offset::ARGS_SIZE;
    static inline constexpr size_t STK_PASS = Function::Offset::ARGS_SELF;
    static inline constexpr size_t STK_DATA = Function::Offset::ARGS_DATA;
    static inline constexpr size_t STK_SIZE = STK_DATA + 1;  // get sizing

}  // namespace Talos::Machine::Offset

namespace Talos::Machine {

    /// @brief Machine Frame.
    class Frame : public Engine::Frame::Abstract<Frame> {
        //  PROPERTIES  //

        /// @brief Shared function information.
        const Info* m_info;

        /// @brief The underlying constructed stack.
        Value::Any* m_stack = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a function frame.
         * @param isolate               Runtime isolate.
         * @param info                  Function information.
         */
        constexpr Frame(Runtime::Isolate* isolate, const Info* info = nullptr) :
            Abstract<Frame>(isolate), m_info(info) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying arena reference.
        inline constexpr const Linker::Arena* arena() const noexcept final { return m_info->arena(); }

        /// @brief Handles getting the current self value.
        inline constexpr Value::Any self() const noexcept { return argv()->self(); }

        /// @brief Casts underlying arguments pointer into an arguments structure.
        inline constexpr const Function::Arguments* argv() const noexcept {
            return reinterpret_cast<const Function::Arguments*>(m_stack + Offset::STK_DATA);
        }

        /// @brief Current stack details.
        inline constexpr Value::Any*& stack() noexcept { return m_stack; }
        inline constexpr Value::Any* stack() const noexcept { return m_stack; }

        /// @brief The bound context.
        inline constexpr Value::Any& context() noexcept { return m_stack[Offset::STK_ENVP]; }
        inline constexpr Function::Context context() const noexcept {
            return Function::Context(m_stack[Offset::STK_ENVP]);
        }

        /// @brief Gets the underlying frame resource.
        inline constexpr $::URI::View resource() const noexcept final { return m_info->resource(); }

        /// @brief Handles constructing suitable backtrace values.
        inline constexpr Resource::Trace backtrace() const noexcept final { return backtrace(m_group()); }
        inline constexpr Resource::Trace backtrace(Resource::Group group) const noexcept {
            return Resource::Trace(resource(), group);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the associated resource-group.
        inline constexpr Resource::Group m_group() const noexcept {
            return m_info->main() ? Resource::Group::SCRIPT : Resource::Group::METHOD;
        }
    };

}  // namespace Talos::Machine

#endif
