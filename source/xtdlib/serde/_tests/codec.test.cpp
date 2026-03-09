/// Vendor Modules
#include <testing/testing.hpp>

/// Forward Declarations
$_FWD(Mock, struct Item)

//  X-MACROS  //

/// @brief Mock Values List.
#define XX_SERDE_VALUES(X)                                \
    X(Text, text, "abc", "def")                           \
    X(Number, number, 42, 3.14)                           \
    X(Boolean, boolean, true, false)                      \
    X(Array, array, $::Serde::Array(), $::Serde::Array()) \
    X(Object, object, $::Serde::Object(), $::Serde::Object())

//  TYPEDEFS  //

struct Mock::Item {
    //  PROPERTIES  //

#define X(T, N, V, ...) $::Serde::T N = V;
    XX_SERDE_VALUES(X)
#undef X

    //  CONSTRUCTORS  //

    /// @brief Allow default construction.
    explicit Item() = default;

   protected:
    //  PRIVATE METHODS  //

    // Implementation for a potential encoder.
    static $::Serde::Value m_encode(const Item& self) {
        auto output = $::Serde::Object();

#define X(_, N, V, ...) output[#N] = self.N;
        XX_SERDE_VALUES(X)
#undef X

        return output;
    }

    // Implementation for a potential decoder.
    static Item m_decode(const $::Serde::Value& value) {
        // prepare an initial item to be used now
        auto item = Item();

#define X(T, N, ...) \
    if (auto* _ = value.at<$::Serde::T>(#N)) item.N = *_;
        XX_SERDE_VALUES(X)
#undef X

        // return the resulting item now
        return item;
    }
};

//  TEST CASES  //

TEST_CASE(encode, runner) {
    // prepare a default value to be encoded
    auto result = $::Reflect::encode(Mock::Item());

    // and attempt checking against the default values now
#define X(_, N, V, ...) runner->asserts()->equal(result.at(#N), $::Serde::Value(V));
    XX_SERDE_VALUES(X)
#undef X
};

TEST_CASE(decode, runner) {
    // prepare an empty object to be compared against
    auto defaulted = $::Reflect::decode<Mock::Item>($::Serde::Value());

#define X(_, N, __, V, ...) { #N, V },
    // prepare an explicit set of overriden values now
    $::Serde::Value alternate = $::Serde::Object({ XX_SERDE_VALUES(X) });
    auto overriden = $::Reflect::decode<Mock::Item>(alternate);
#undef X

// check that the empty instance is valid now
#define X(_, N, V, ...) runner->asserts()->equal(defaulted.N, V);
    XX_SERDE_VALUES(X)
#undef X

// check all the override values are valid now
#define X(_, N, __, V, ...) runner->asserts()->equal(overriden.N, V);
    XX_SERDE_VALUES(X)
#undef X
};

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("RTTI/Dynamic",
        {
            TEST_BIND(encode, "Mock::Item"),
            TEST_BIND(decode, "Mock::Item"),
        }),
});
