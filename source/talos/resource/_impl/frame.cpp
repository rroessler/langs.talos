/// Talos Includes
#include "talos/resource/frame.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Resource::Frame::Frame(Runtime::Isolate *isolate, const Resource::Trace &trace) :
    Engine::Frame::Mixin<Frame>(isolate), m_trace(trace) {}

Talos::Resource::Frame::Frame(Runtime::Isolate *isolate) : Engine::Frame::Mixin<Frame>(isolate) {
  if (auto *frame = isolate->frame()) m_trace = frame->backtrace();
}
