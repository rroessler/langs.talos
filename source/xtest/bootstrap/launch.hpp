#ifndef _XTEST_BOOTSTRAP_LAUNCH_HPP
#define _XTEST_BOOTSTRAP_LAUNCH_HPP

/// Testing Includes
#include "xtest/forward/handle.hpp"
#include "xtest/session/options.hpp"

namespace XT::Bootstrap {

/**
 * @brief Handles launching a bootstrapped runner.
 * @param storage                   Session storage.
 * @param options                   Testing options.
 */
int32_t launch(const Session::Storage *storage, const Session::Options &options = {});

/**
 * @brief Handles launching a bootstrapped runner.
 * @param sections                  Test sections.
 * @param options                   Testing options.
 */
int32_t launch(const $::Map::Dict<Handle::Group *> &sections = {}, const Session::Options &options = {});

/**
 * @brief Handles launching a bootstrapped runner.
 * @param runner                    Session runner.
 * @param sections                  Test sections.
 */
int32_t launch(Session::Runner *runner, const Session::Storage *storage);
int32_t launch(Session::Runner *runner, const $::Map::Dict<Handle::Group *> &sections = {});

} // namespace XT::Bootstrap

#endif
