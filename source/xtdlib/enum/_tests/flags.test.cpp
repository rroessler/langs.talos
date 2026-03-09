/// Vendor Modules
#include <testing/testing.hpp>

/// Forward Declarations
$_FWD(Mock, enum class Enum)
$_FWD(Mock, using Flags = $::Enum::Flags<Enum>)

//  TYPEDEFS  //

enum class Mock::Enum { A, B, C, D };

//  TEST CASES  //

TEST_CASE(none, runner) { runner->asserts()->okay(Mock::Flags().none()); };

TEST_CASE(set, runner) {
    auto flags = Mock::Flags(Mock::Enum::A, Mock::Enum::C);
    runner->asserts()->okay(flags.test(Mock::Enum::A, Mock::Enum::C));
    runner->asserts()->okay(!flags.test(Mock::Enum::B, Mock::Enum::D));
};

TEST_CASE(any, runner) { runner->asserts()->okay(Mock::Flags(Mock::Enum::B).any()); };
TEST_CASE(all, runner) { runner->asserts()->okay(Mock::Flags().set().all()); };

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("Enum/Flags",
        {
            TEST_BIND(none, ),
            TEST_BIND(set, ),
            TEST_BIND(any, ),
            TEST_BIND(all, ),
        }),
});
