/// Talos Includes
#include "talos/function/args.hpp"
#include "talos/runtime/isolate.hpp"

/// Value Includes
#include "talos/value/_inline/value.ipp"

//  MACROS  //

/// @brief Prepare a macro for testing our values
#define MM_ASSERT_NUMERIC(I, V, ...)                                                                                 \
  if (!(V).is<Number::Tagged>()) return I->panic(6000253, #V, Value::Inspect<Number::Tagged>::name()), std::nullopt;

//  PUBLIC METHODS  //

std::optional<Talos::Iterable::Interval>
Talos::Iterable::Stepper(Runtime::Isolate *isolate, const Function::Args &args) {
  // prepare a suitable selection of values to be used
  Number::Floating start = 0, stop = 0, step = 1;

  switch (auto size = args.size(); size) {
  // leave all values as the same here
  case 0: break;

  case 1: {
    MM_ASSERT_NUMERIC(isolate, args[0]);
    stop = args.at<Number::Tagged>(0).value();
    if (start > stop) step = -1; // invert step
  } break;

  default: MM_ASSERT_NUMERIC(isolate, args[2]); $_FALLTHROUGH;
  case 2: {
    MM_ASSERT_NUMERIC(isolate, args[0]);
    MM_ASSERT_NUMERIC(isolate, args[1]);
    start = args.at<Number::Tagged>(0).value();
    stop = args.at<Number::Tagged>(1).value();
    if (size == 2) step = start < stop ? 1 : -1;
    else step = args.at<Number::Tagged>(2).value();
  } break;
  }

  // construct the resulting interval now
  return Interval(start, stop, step);
}
