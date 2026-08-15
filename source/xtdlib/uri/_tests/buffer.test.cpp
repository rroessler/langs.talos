/// Vendor Includes
#include <tests/tests.hpp>

/// Forward Declarations
$_FWD(Mock, void parse(XT::Session::Runner *, const std::vector<$::String::View> &))

//  X-MACROS  //

#define XX_PARSING_TESTS(X)                                                  \
  X("https://github.com", "https", "github.com", "")                         \
  X("https://timothygu.me/urltester", "https", "timothygu.me", "/urltester") \
  X("file://" __FILE__, "file", "", __FILE__)

//  MOCK METHODS  //

void Mock::parse(XT::Session::Runner *runner, const std::vector<$::String::View> &argv) {
  auto uri = argv[0], scheme = argv[1], authority = argv[2], body = argv[3];
  auto parts = $::URI::Parse(uri); // attempt parsing the URI now to be used

  runner->asserts()->equal(scheme, parts.scheme());
  runner->asserts()->equal(authority, parts.authority());
  runner->asserts()->equal(body, parts.body());
  runner->asserts()->equal(uri, parts.view());
}

//  TEST CASES  //

TEST_CALLBACK(parse, runner) {
#define X(N, S, A, B, ...) Mock::parse(runner, {N, S, A, B});
  XX_PARSING_TESTS(X)
#undef X
};

//  TEST SECTIONS  //

TEST_SUITE("xtdlib")->emplace({
    TEST_GROUP("URI/Parse", {TEST_CASE(parse)}),
});
