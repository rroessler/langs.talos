/// Vendor Modules
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(is_file, runner) {
    runner->asserts()->okay($::Terminal::is(stdout));
    runner->asserts()->okay($::Terminal::is(stderr));
    runner->asserts()->okay(!$::Terminal::is(nullptr));
};

TEST_CASE(is_os, runner) {
    runner->asserts()->okay($::Terminal::is($::IO::cout()));
    runner->asserts()->okay($::Terminal::is($::IO::cerr()));
    runner->asserts()->okay(!$::Terminal::is($::String::Stream()));
};

TEST_CASE(as_file, runner) {
    runner->asserts()->equal($::Terminal::as($::IO::cout()), stdout);
    runner->asserts()->equal($::Terminal::as($::IO::cerr()), stderr);
    runner->asserts()->equal($::Terminal::as($::String::Stream()), nullptr);
};

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("Terminal/Core",
        {
            TEST_BIND(is_file, "Stream::Handle"),
            TEST_BIND(is_os, "Stream::Output"),
            TEST_BIND(as_file, "Stream::Output"),
        }),
});
