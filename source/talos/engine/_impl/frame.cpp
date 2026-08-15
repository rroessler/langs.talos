/// Talos Includes
#include "talos/engine/frame.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Engine::Frame::Frame(Isolate *isolate) : m_encoded(reinterpret_cast<uintptr_t>(isolate)) {
  isolate->m_frames.push_back(this);
}

Talos::Engine::Frame::~Frame() {
  auto *isolate = m_isolate(); // decode the isolate
  if (isolate->thread()->task() == nullptr) return;
  $_ASSERT(isolate->m_frames.back() == this);
  isolate->m_frames.pop_back(); // remove frame
}
