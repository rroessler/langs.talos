/// Forge Modules
#include "forge/engine/frame.hpp"
#include "forge/async/service.hpp"
#include "forge/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Forge::Engine::Frame::Frame(Runtime::Isolate* isolate) :
    m_interrupt(false), m_parent(isolate->m_frame), m_isolate(isolate) {
    m_depth = m_parent ? m_parent->m_depth + 1 : 0, m_isolate->m_frame = this;
}

Forge::Engine::Frame::~Frame() {
    if (m_isolate->thread()->task() == nullptr) return;  // forced exit
    $_ASSERT(m_isolate->m_frame == this), m_isolate->m_frame = m_parent;
}
