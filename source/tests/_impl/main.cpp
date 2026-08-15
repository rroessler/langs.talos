/// Testing Includes
#include "tests/tests.hpp"

/**
 * @brief Testing runtime entry-point.
 * @param argc                  Argument count.
 * @param argv                  Variadic arguments.
 */
int32_t main(int32_t, char **) {
  // prepare the storage for tests now
  auto *storage = XT::Global::registry();

  // prepare some options to be inherited
  XT::Session::Options options = {
      .bench = {.enabled = true},
  };

  // and attempt executing the result now
  return XT::Bootstrap::launch(storage, options);
}

//  PUBLIC METHODS  //

XT::Session::Storage *XT::Global::registry() {
  /// @brief Overriden Storage Registry.
  class Registry : public Session::Storage {
  protected:
    //  PRIVATE METHODS  //

    /// @brief Ensure our resolution always fails.
    inline Handle::Group *m_resolve(const $::URI::View &) final { return nullptr; }
  };

  // and get the resulting registry instance
  return $::Global::get<Registry>();
}
