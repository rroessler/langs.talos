/// C++ Includes
#include <ranges>

/// Library Includes
#include "xtdlib/allocator/tracker.hpp"
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/io/print.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/terminal/ansi.hpp"

//  PUBLIC METHODS  //

void *$::Allocator::Tracker::acquire(void *pointer, const Record &record) {
    // get the underlying instance now
    auto self = s_instance();

    // stop if not currently recording now
    if (!self->m_recording) return pointer;

    // lock the underlying instance being used now
    $_UNUSED $_AUTO = Lock::guard(self->m_mutex);

    // ensure we do not have duplicate items
    $_ASSERT(!self->m_allocations.contains(pointer), "Double allocation of address '{0}'", pointer);

    // emplace the base allocation instance
    self->m_allocations.emplace(pointer, record);
    auto pool = record.pool(), bytes = record.bytes();

    // update the allocations by pool as necessary now
    if (pool >= self->m_pooled.size()) self->m_pooled.resize(pool + 1, 0);

    // update the current bytes to be used
    self->m_accumulated += bytes;
    self->m_pooled[pool] += bytes;

    // return the resulting pointer now
    return pointer;
}

void $::Allocator::Tracker::release(void *pointer) {
    // get the underlying instance now
    auto self = s_instance();

    // stop if not currently recording now or we have a nullptr
    if (!self->m_recording || pointer == nullptr) return;

    // lock the underlying instance being used now
    $_UNUSED $_AUTO = Lock::guard(self->m_mutex);

    auto iter = self->m_allocations.find(pointer);  // attempt finding the record in question
    $_ASSERT(iter != self->m_allocations.end(), "Failed deallocation of address '{0}'", pointer);

    // destructure our allocation instance
    auto pool = iter->second.pool(), bytes = iter->second.bytes();

    // update our categories as necessary now
    self->m_accumulated -= bytes;
    self->m_pooled[pool] -= bytes;

    // and remove the instance
    self->m_allocations.erase(iter);
}

//  PRIVATE METHODS  //

void $::Allocator::Tracker::m_report() const {
    // get the underlying instance now
    auto self = s_instance();

    // stop if not currently recording now
    if (!self->m_recording || self->m_allocations.empty()) return;

    // show the initial warning display as necessary now
    $::IO::cerr() << '\n' << Dye::red("===== Memory Leaks Detected: {0} Bytes =====", self->m_accumulated) << "\n\n";

    // dump all the available memory leaks now
    for (const auto &record : self->m_allocations | std::views::values) $::IO::cerr() << record << '\n';

    // and ensure there is a final newline
    $::IO::cerr() << '\n';
}
