#ifndef _TALOS_ENGINE_FRAME_HPP
#define _TALOS_ENGINE_FRAME_HPP

/// Talos Modules
#include "talos/forward/engine.hpp"
#include "talos/forward/linker.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/resource/trace.hpp"

namespace Talos::Engine {

    /// @brief Abstract Engine Frame.
    struct $_ABSTRACT Frame : public $::RTTI::Dynamic {
        //  TYPEDEFS  //

        /// @brief Frame Abstraction Typing.
        template <class T>
        using Abstract = $::RTTI::Extends<T, Frame>;

       protected:
        //  PROPERTIES  //

        bool m_interrupt;    // Interrupt flag.
        uint32_t m_depth;    // Current depth.
        Frame* m_parent;     // Parent frame.
        Isolate* m_isolate;  // Runtime isolate.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an engine frame.
         * @param isolate           Runtime isolate.
         */
        explicit Frame(Isolate* isolate);

        /// @brief Handles destructing frames.
        virtual ~Frame();

        //  PUBLIC METHODS  //

        /// @brief Attempts forcing the frame into an interrupt state.
        inline constexpr bool& interrupted() noexcept { return m_interrupt; }
        inline constexpr bool interrupted() const noexcept { return m_interrupt; }

        /// @brief Gets the depth of the frame.
        inline constexpr size_t depth() const noexcept { return m_depth; }

        /// @brief Gets the parent of the frame.
        inline constexpr Frame* parent() const noexcept { return m_parent; }

        /// @brief The underlying frame resource.
        virtual inline $::URI::View resource() const noexcept { return $::URI::Anonymous(); }

        /// @brief Gets the associated arena for a frame.
        virtual inline const Linker::Arena* arena() const noexcept { return nullptr; }

        /// @brief Handles getting a frames backtrace.
        virtual inline Resource::Trace backtrace() const noexcept { return Resource::Trace(resource()); }

        /// @brief Allows casting to derived values.
        template <std::derived_from<Frame> T>
        inline constexpr T* as() noexcept {
            return $::RTTI::Assert<T>(this), static_cast<T*>(this);
        }

        /// @brief Allows casting to derived values.
        template <std::derived_from<Frame> T>
        inline constexpr const T* as() const noexcept {
            return $::RTTI::Assert<T>(this), static_cast<const T*>(this);
        }
    };

}  // namespace Talos::Engine

#endif
