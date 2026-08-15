#ifndef _XTDLIB_MUTEX_LOCK_HPP
#define _XTDLIB_MUTEX_LOCK_HPP

/// Library Includes
#include "xtdlib/mutex/guard.hpp"
#include "xtdlib/mutex/types.hpp"

namespace $::Lock {

//  TYPEDEFS  //

/// @brief Multiple Locks Alias.
template <class... Ms> using Tuple = std::scoped_lock<Ms...>;

/// @brief Unique Lock Alias.
template <class M = Mutex::Auto> using Unique = std::unique_lock<M>;

//  FACTORY METHODS  //

/**
 * @brief Constructs a scoped mutex-lock.
 * @param mutex                 Mutex to lock.
 */
template <class M> static inline Unique<M> scope(M &mutex) { return Unique<M>(mutex); }

/**
 * @brief Constructs a tuple of mutex locks.
 * @param args                  Mutex arguments to lock.
 */
template <class... As> static inline Tuple<As...> join(As &&...args) { return Tuple<As...>(std::forward<As>(args)...); }

/**
 * @brief Constructs a mutex guard.
 * @param mutex                 Mutex to guard.
 */
template <class M> static inline Mutex::Guard<M> guard(M &mutex) { return Mutex::Guard(mutex); }

} // namespace $::Lock

#endif
