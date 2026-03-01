/// Forge Modules
#include "forge/relint/context.hpp"
#include "forge/runtime/container.hpp"

//  CONSTRUCTORS  //

Forge::Relint::Context::Context() : Context($::Global::get<Runtime::Container>()) {}
Forge::Relint::Context::Context(XI::Container* services) : m_services(services) {}
