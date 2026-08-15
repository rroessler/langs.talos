#ifndef _TESTS_HPP
#define _TESTS_HPP

/// Vendor Includes
#include <xtest/xtest.hpp>

/// Forward Declarations
$_FWD(XT::Global, Session::Storage *registry())

//  MACROS  //

#define TEST_CASE(FN, ...) XT::Global::registry()->test(#FN "()", _test_##FN)
#define TEST_BENCH(FN, ...) XT::Global::registry()->bench(#FN "()", _test_##FN)
#define TEST_GROUP(N, ...) XT::Global::registry()->group(N)->bind(__VA_ARGS__)

#define TEST_SUITE(...) static $_AUTO = XT::Global::registry()->suite($::Source::Location())
#define TEST_CALLBACK(FN, R, ...) $_UNUSED static auto _test_##FN = [](XT::Session::Runner * R)

#endif
