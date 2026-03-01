#ifndef _FORGE_RUNTIME_STACK_HPP
#define _FORGE_RUNTIME_STACK_HPP

/// Forge Modules
#include "forge/forward/runtime.hpp"
#include "forge/heap/buffer.hpp"
#include "forge/object/allocator.hpp"
#include "forge/value/common.hpp"

namespace Forge::Runtime {

    /// @brief Temporary Stack Container.
    class Stack {
        //  PROPERTIES  //

        /// @brief The capacity bound.
        size_t m_capacity = 0;

        /// @brief Associated isolate.
        Allocator* m_allocator = nullptr;

        /// @brief The leading stack pointer.
        Value::Any* m_data = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty stack.
        explicit constexpr Stack() = default;

        /**
         * @brief Constructs a runtime stack.
         * @param allocator             Runtime allocator.
         * @param capacity              Total capacity.
         */
        explicit constexpr Stack(Allocator* allocator, size_t capacity = 0) :
            m_capacity(m_align(capacity)), m_allocator(allocator), m_data(m_allocate()) {}

        /// @brief Handles destructing the incoming stack.
        constexpr ~Stack() { m_release(); }

        //  OPERATOR METHODS  //

        /// @brief Allows accessing and modifying stack values.
        inline constexpr Value::Any& operator[](size_t index) noexcept { return m_data[index]; }
        inline constexpr Value::Any operator[](size_t index) const noexcept { return m_data[index]; }

        //  PUBLIC METHODS  //

        inline constexpr size_t size() const noexcept { return m_capacity; }
        inline constexpr Value::Any* data() const noexcept { return m_data; }
        inline constexpr std::span<Value::Any> span() const noexcept { return { data(), size() }; }

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles allocating the stack.
        Value::Any* m_allocate();

        /// @brief Handles releasing the stack.
        void m_release();

        /**
         * @brief Resolves a suitable alignment.
         * @param size                      Size to align.
         */
        static inline constexpr size_t m_align(size_t size) {
            return Heap::Align<Pointer::Alignment::OBJECT / sizeof(Value::Any)>(size);
        }
    };

    /// @brief Runtime Memory Allocator.
    class Allocator {
        //  TYPEDEFS  //

        /// @brief Allow the stack internal access.
        friend class Stack;

        //  PROPERTIES  //

        /// @brief Parent runtime isolate.
        Isolate* m_isolate = nullptr;

        /// @brief The internal buffer.
        $::Ptr::Unique<Heap::Buffer> m_buffer = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a runtime allocator.
         * @param isolate               Runtime isolate.
         */
        explicit Allocator(Isolate* isolate = nullptr) : m_isolate(isolate) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Constructs a temporary stack.
         * @param capacity              Size of the stack.
         */
        inline constexpr Stack stack(size_t capacity) { return Stack(this, capacity); }

        /**
         * @brief Handles constructing objects.
         * @param args                  Attribute arguments.
         */
        template <std::derived_from<Value::Any> T, class... As>
        inline constexpr T create(As&&... args) {
            return Object::Allocator::create<T>(m_isolate, std::forward<As>(args)...);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles reserving data.
         * @param size                  Size of incoming data.
         */
        Value::Any* m_reserve(size_t size);

        /**
         * @brief Handles releasing data.
         * @param data                  Data to release.
         * @param size                  Size of data.
         */
        void m_release(Value::Any* data, size_t size);
    };

}  // namespace Forge::Runtime

#endif
