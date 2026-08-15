/// Testing Includes
#include "xtest/reporter/options.hpp"
#include "xtest/session/runner.hpp"

/// Reporter Includes
#include "xtest/reporter/_inline/json.ipp"
#include "xtest/reporter/_inline/junit.ipp"
#include "xtest/reporter/_inline/tap.ipp"
#include "xtest/reporter/_inline/text.ipp"
#include "xtest/reporter/_inline/xml.ipp"

//  PUBLIC METHODS  //

bool XT::Reporter::Ensure(const $::String::View &label) {
#define X(T, ...)                           \
  case XH::FNV::U32(Label::T): return true;
  switch (XH::FNV::U32(label)) { XTEST_XX_REPORTER_LABELS(X) default : return false; }
#undef X
}

$::Unique::Pointer<XT::Reporter::Stream> XT::Reporter::Resolve(Session::Runner *runner) {
#define X(T, ...)                                                                              \
  case XH::FNV::U32(Label::T): return $::Unique::New<Proxy<Label::T>>(runner, options.output);
  switch (auto &options = runner->options()->reporter; XH::FNV::U32(options.label)) {
    XTEST_XX_REPORTER_LABELS(X) default : return nullptr; // fallback to empty if invalid
  }
#undef X
}