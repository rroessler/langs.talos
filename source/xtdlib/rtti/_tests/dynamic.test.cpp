/// Vendor Modules
#include <testing/testing.hpp>

/// Forward Declarations
$_FWD(Mock, struct A : public $::RTTI::Dynamic{})
$_FWD(Mock, struct B : public $::RTTI::Extends<B, A>{})
$_FWD(Mock, struct C : public $::RTTI::Extends<C, A>{})
$_FWD(Mock, struct D{})  // should not be accessible

//  TEST CASES  //

TEST_CASE(dynamic, runner) {
    // prepare our mocked values
    auto b = Mock::B{};
    auto c = Mock::C{};

    runner->asserts()->okay(b.is<Mock::B>());
    runner->asserts()->okay(c.is<Mock::C>());
    runner->asserts()->okay(!b.is<Mock::D>());
    runner->asserts()->okay(!c.is<Mock::D>());
};

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("RTTI/Dynamic", { TEST_BIND(dynamic, "T") }),
});
