/// Talos Modules
#include "talos/engine/frame.hpp"
#include "talos/async/service.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Engine::Frame::Frame(Runtime::Isolate* isolate) :
    m_interrupt(false), m_parent(isolate->m_frame), m_isolate(isolate) {
    m_depth = m_parent ? m_parent->m_depth + 1 : 0, m_isolate->m_frame = this;
}

Talos::Engine::Frame::~Frame() {
    if (m_isolate->thread()->task() == nullptr) return;  // forced exit
    $_ASSERT(m_isolate->m_frame == this), m_isolate->m_frame = m_parent;
}
