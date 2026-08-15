/// Talos Includes
#include "talos/register/span.hpp"
#include "talos/bytecode/allocator.hpp"

//  CONSTRUCTORS  //

Talos::Register::List::List(Bytecode::Allocator *allocator) :
    Span(allocator ? allocator->m_index : 1, 0), m_allocator(allocator) {}

Talos::Register::List::~List() {
  if (m_allocator && count()) m_allocator->m_delist(first());
}

//  PUBLIC METHODS  //

Talos::Register::Slot Talos::Register::List::grow() {
  $_EXPECT(++m_count < UINT8_MAX, "Exceeded maximum span-count");
  if ($_UNLIKELY(m_allocator == nullptr)) return last();

  $_ASSERT(m_allocator->m_index == m_first + m_count - 1, "Register not freed between list-growth");
  return m_allocator->allocate(); // should be able to validly allocate a register now
}
