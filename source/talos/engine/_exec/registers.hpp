/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(REG_MOVE, isolate, frame, unqualified) {
  auto *instruction = unqualified->cast<Glyph::REG_MOVE>();
  auto value = frame->load(instruction->get<1>());
  frame->store(instruction->get<0>(), value);
  $_MUSTTAIL return tailcall(isolate, frame, unqualified);
}

TALOS_MM_ENGINE_EXECUTE(REG_SWAP, isolate, frame, unqualified) {
  auto *instruction = unqualified->cast<Glyph::REG_MOVE>();
  frame->swap(instruction->get<0>(), instruction->get<1>());
  $_MUSTTAIL return tailcall(isolate, frame, unqualified);
}
