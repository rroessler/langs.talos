/// Machine Includes
#include "talos/machine/_inline/macros.ipp"

//  EMITTER METHODS  //

TALOS_MM_MACHINE_EMIT(ENUM_EMPTY, builder, instruction) {
  auto dx = __ee__ slot(instruction->get<0>()); // prepare destination
  __ee__ call(Glue::empty<Iterable::Iterator>, dx, builder->isolate);
}

TALOS_MM_MACHINE_EMIT(ENUM_MAKE, builder, instruction) {
  // prepare the destination register
  auto dx = __ee__ slot(instruction->get<0>());

  // ensure we preload the necessary parameters
  __ee__ params(instruction->get<1>());

  // and invoke the enumeration constructor
  __ee__ call(Glue::enumeration, dx, builder->isolate, builder->params);
}
