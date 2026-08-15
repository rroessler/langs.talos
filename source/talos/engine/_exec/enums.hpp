/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(ENUM_EMPTY, isolate, frame, unqualified) {
  auto *instruction = unqualified->cast<Glyph::ENUM_EMPTY>();
  auto enumeration = isolate->create<Object::Enum>();
  frame->store(instruction->get<0>(), enumeration);
  $_MUSTTAIL return tailcall(isolate, frame, unqualified);
}

TALOS_MM_ENGINE_EXECUTE(ENUM_MAKE, isolate, frame, unqualified) {
  auto *instruction = unqualified->cast<Glyph::ENUM_MAKE>();
  auto tuples = frame->span(instruction->get<1>());
  auto enumeration = m_enumeration(isolate, tuples);
  frame->store(instruction->get<0>(), enumeration);
  $_MUSTTAIL return tailcall(isolate, frame, unqualified);
}
