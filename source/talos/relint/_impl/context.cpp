/// Talos Includes
#include "talos/relint/context.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Relint::Context::Context() : Context($::Global::get<Runtime::Container>()) {}
Talos::Relint::Context::Context(XI::Container *services) : m_services(services) {}
