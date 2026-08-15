/// Talos Includes
#include "talos/register/scoped.hpp"
#include "talos/bytecode/allocator.hpp"

//  CONSTRUCTORS  //

Talos::Register::Scoped::Scoped(Bytecode::Allocator *allocator) : Slot(allocator->allocate()), m_allocator(allocator) {}
Talos::Register::Scoped::~Scoped() { m_allocator->m_release(*this); }
