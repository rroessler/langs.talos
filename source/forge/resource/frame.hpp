#ifndef _FORGE_RESOURCE_FRAME_HPP
#define _FORGE_RESOURCE_FRAME_HPP

/// Forge Modules
#include "forge/engine/frame.hpp"

namespace Forge::Resource {

    /// @brief Abstract Engine Frame.
    class Frame : public Engine::Frame::Abstract<Frame> {
        //  PROPERTIES  //

        /// @brief Associated resource trace.
        Trace m_trace;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a resource frame.
         * @param isolate           Runtime isolate.
         * @param trace             Resource trace.
         */
        explicit Frame(Runtime::Isolate* isolate);
        explicit Frame(Runtime::Isolate* isolate, const Trace& trace);

        //  PUBLIC METHODS  //

        inline constexpr Resource::Trace backtrace() const noexcept final { return m_trace; }
        inline constexpr $::URI::View resource() const noexcept final { return m_trace.resource(); }
    };

}  // namespace Forge::Resource

#endif
