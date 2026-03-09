#ifndef _TALOS_FUNCTION_FRAME_HPP
#define _TALOS_FUNCTION_FRAME_HPP

/// Talos Modules
#include "talos/engine/frame.hpp"
#include "talos/function/context.hpp"
#include "talos/function/info.hpp"

namespace Talos::Function {

    /// @brief Derived Function Frame.
    class Frame : public Engine::Frame::Abstract<Frame> {
        //  PROPERTIES  //

        /// @brief Incoming argument count.
        size_t m_argc = 0;

        /// @brief Current instruction offset.
        uintptr_t m_offset = 0;

        /// @brief Shared function information.
        const Info* m_info = nullptr;

        /// @brief Associated environment context.
        Context m_context = Context();

        /// @brief Curently bound receiver.
        Value::Any m_self = Value::Void();

        /// @brief Register stack (eg: 0 = accumulator, ...A = arguments, ...N = registers).
        Value::Any* m_stack = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a function frame.
         * @param isolate               Runtime isolate.
         * @param info                  Function information.
         * @param self                  Bound receiver value.
         */
        constexpr Frame(Runtime::Isolate* isolate, const Info* info = nullptr, const Value::Any& self = Value::Void()) :
            Abstract<Frame>(isolate), m_offset(info->buffer().address()), m_info(info), m_self(self) {}

        //  PUBLIC METHODS  //

        /// @brief Current function information.
        inline constexpr const Info* info() const noexcept { return m_info; }
        inline constexpr const Linker::Arena* arena() const noexcept final { return m_info->arena(); }

        /// @brief Current instruction offset.
        inline constexpr uintptr_t& offset() noexcept { return m_offset; }
        inline constexpr uintptr_t offset() const noexcept { return m_offset; }

        /// @brief The incoming argument count to be used.
        inline constexpr size_t& argc() noexcept { return m_argc; }
        inline constexpr size_t argc() const noexcept { return m_argc; }

        /// @brief Gets the bound receiver value.
        inline constexpr Value::Any self() const noexcept { return m_self; }

        /// @brief Gets a span of the incoming arguments.
        inline constexpr std::span<Value::Any> argv() const noexcept { return span(1, m_argc); }

        /// @brief Current stack details.
        inline constexpr Value::Any*& stack() noexcept { return m_stack; }
        inline constexpr Value::Any* stack() const noexcept { return m_stack; }

        /// @brief Underlying accumulator reference.
        inline constexpr Value::Any& accumulator() noexcept { return m_stack[0]; }
        inline constexpr Value::Any accumulator() const noexcept { return m_stack[0]; }

        /// @brief Current environment context.
        inline constexpr Context& context() noexcept { return m_context; }
        inline constexpr const Context& context() const noexcept { return m_context; }
        inline constexpr Context context(Bytecode::Index depth) const noexcept { return m_context.resolve(depth); }

        /// @brief Gets the underlying frame resource.
        inline constexpr $::URI::View resource() const noexcept final { return m_info->resource(); }

        /// @brief Handles constructing suitable backtrace values.
        inline constexpr Resource::Trace backtrace() const noexcept final { return backtrace(m_group()); }
        inline constexpr Resource::Trace backtrace(Resource::Group group) const noexcept {
            auto offset = m_offset - arena()->bytecode.address();
            offset -= sizeof(Bytecode::Instruction::Encoded);
            auto* entry = arena()->bytecode.sources().before(offset);
            auto* position = entry ? &entry->position : nullptr;
            return Resource::Trace(resource(), group, position);
        }

        /**
         * @brief Handles getting registers from the frame.
         * @param index                 Register index.
         */
        $_INLINE_PERF constexpr Value::Any load(Engine::Register index) const {
            return m_assert(index), m_stack[index];
        }

        /**
         * @brief Handles getting registers from the frame.
         * @param index                 Register index.
         */
        template <std::derived_from<Value::Any> T>
        $_INLINE_PERF constexpr T load(Engine::Register index) const {
            return load(index).as<T>();
        }

        /**
         * @brief Handles setting registers from the frame.
         * @param index                 Register index.
         * @param value                 Value to assign.
         */
        $_INLINE_PERF constexpr Value::Any store(Engine::Register index, Value::Any value) {
            return m_assert(index), m_stack[index] = value;
        }

        /**
         * @brief Handles getting a frame span.
         * @param list                  Register list.
         */
        inline constexpr std::span<Value::Any> span(Engine::Register::Span list) const {
            return span(list.first(), list.count());
        }

        /**
         * @brief Handles getting a frame span.
         * @param index                 Frame index.
         * @param count                 Span count.
         */
        inline constexpr std::span<Value::Any> span(Engine::Register index, Bytecode::Index count) const {
            if (count == 0) return std::span<Value::Any>();  // resolve empty spans immediately
            return m_assert(index + count - 1), std::span<Value::Any>({ &m_stack[index], count });
        }

        /**
         * @brief Handles constructing call-arguments.
         * @param list                  List to split.
         */
        inline constexpr std::pair<Value::Any, std::span<Value::Any>> split(Engine::Register::Span list) const {
            auto argv = span(list);  // get base
            return { argv[0], argv.subspan(1) };
        }

        /**
         * @brief Retrieves a string intern.
         * @param index                 Index of intern.
         */
        inline constexpr const String::Intern& intern(Bytecode::Index index) const noexcept {
            return arena()->strings.at(index);
        }

        /**
         * @brief Retrieves a constant.
         * @tparam T                    Optional type.
         * @param index                 Index of constant.
         */
        template <std::derived_from<Value::Any> T = Value::Any>
        inline constexpr T constant(Bytecode::Index index) const noexcept {
            auto value = arena()->constants.at(index);  // getter
            if constexpr (std::same_as<T, Value::Any>) return value;
            else return value.as<T>();  // force a cast to occur
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the associated resource-group.
        inline constexpr Resource::Group m_group() const noexcept {
            return m_info->main() ? Resource::Group::SCRIPT : Resource::Group::METHOD;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Ensures indices are valid.
         * @param index                 Index to validate.
         */
        inline constexpr void m_assert($_UNUSED Engine::Register index) const {
            $_ASSERT(!index.nowhere(), "Invalid register value");  // validate now
            $_ASSERT(index.encode() < m_info->locals() + 1, "Exceeded stack index");
        }
    };

}  // namespace Talos::Function

#endif
