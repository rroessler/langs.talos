/// Forge Modules
#include "forge/resource/frame.hpp"
#include "forge/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Forge::Resource::Frame::Frame(Runtime::Isolate* isolate, const Resource::Trace& trace) :
    Abstract<Frame>(isolate), m_trace(trace) {}

Forge::Resource::Frame::Frame(Runtime::Isolate* isolate) : Abstract<Frame>(isolate) {
    if (auto* frame = isolate->frame()) m_trace = frame->backtrace();
}
