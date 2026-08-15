#ifndef _XTDLIB_MUTEX_GUARD_HPP
#define _XTDLIB_MUTEX_GUARD_HPP

namespace $::Mutex {

/// @brief Unique Mutex Guard.
template <class T> class Guard {
  //  PROPERTIES  //

  /// @brief Attached mutex instance.
  T &m_mutex;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs the lock-guard.
   * @param mutex                 Mutex to be locked.
   */
  Guard(T &mutex) noexcept : m_mutex(mutex) { m_mutex.lock(); }

  /// @brief Removes the mutex-lock.
  ~Guard() noexcept { m_mutex.unlock(); }

  /// @brief Do not allow copy-construction.
  Guard(const Guard &) = delete;

  //  OPERATOR METHODS  //

  /// @brief Do not allow copy-assignment.
  Guard &operator=(const Guard &) = delete;
};

} // namespace $::Mutex

#endif
