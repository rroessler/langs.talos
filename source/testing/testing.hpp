#ifndef _TESTING_HPP
#define _TESTING_HPP

/// Vendor Modules
#include <xtest/xtest.hpp>

//  MACROS  //

#define TEST_GROUP(N, ...) XT::Bind::group(N)->bind(__VA_ARGS__)
#define TEST_BIND(V, N, ...) XT::Bind::test(#V "(" N ")", t_##V)
#define TEST_BENCH(V, N, ...) XT::Bind::bench(#V "(" N ")", t_##V)
#define TEST_SECTION(N, ...) static $_AUTO = XT::Bind::describe(Testing::Section::N)
#define TEST_CASE(V, R, ...) $_UNUSED static auto t_##V = [](XT::Session::Runner * R $_PP_VARGS(__VA_ARGS__))

//  NAMESPACES  //

namespace Testing::Section {

    static constexpr auto FORGE = "forge";

    static constexpr auto XPC = "xpc";
    static constexpr auto XTDLIB = "xtdlib";

}  // namespace Testing::Section

#endif
