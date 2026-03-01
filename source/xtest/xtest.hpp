#ifndef _XTEST_HPP
#define _XTEST_HPP

/// Assert Modules
#include "xtest/assert/failure.hpp"
#include "xtest/assert/info.hpp"
#include "xtest/assert/reason.hpp"
#include "xtest/assert/that.hpp"

/// Handle Modules
#include "xtest/handle/abstract.hpp"
#include "xtest/handle/bench.hpp"
#include "xtest/handle/group.hpp"
#include "xtest/handle/traits.hpp"

/// Reporter Modules
#include "xtest/reporter/facade.hpp"
#include "xtest/reporter/interface.hpp"

/// Session Modules
#include "xtest/session/options.hpp"
#include "xtest/session/progress.hpp"
#include "xtest/session/registry.hpp"
#include "xtest/session/runner.hpp"
#include "xtest/session/service.hpp"
#include "xtest/session/statistics.hpp"

#endif
