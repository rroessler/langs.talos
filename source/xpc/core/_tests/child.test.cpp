/// Vendor Modules
#include <testing/testing.hpp>

/// XPC Modules
#include "xpc/core/child.hpp"

//  TEST CASES  //

TEST_CASE(echo, runner) {
    // attempt joining all the arguments for the output
    static std::vector<$::String::Buffer> s_argv = { "Hello,", "World!" };
    static auto s_expected = $::Convert::join(std::vector(s_argv), " ");

    // prepare the process options so we can pipe our output
    XPC::Shell::Options options = {
        .cout = XPC::Pipe::Direct::PIPED,

#if $_PLATFORM_WINDOWS
        .argv = { "/c", "echo" },
#endif
    };

    // ensure we append the necessary arguments now
    $::Ranges::Append(options.argv, s_argv);

    // prepare the command to be used (this is because we need to run in a command-prompt shell)
    auto command = $_PLATFORM_WINDOWS ? *XPC::Shell::Path::binary() : "echo";

    // attempt constructing the process to be executed now
    auto process = XPC::Core::Child(command, std::move(options));

    // attempt waiting for the process to complete succesfully
    runner->asserts()->equal(process.wait(), $_EXIT_SUCCESS);

    auto incoming = process.cout().string();  // get incoming now
    if ($_PLATFORM_WINDOWS) incoming = $::Trim::trailing(incoming);

    // flush the standard output from it's pipe and check it's valid
    runner->asserts()->equal(incoming, s_expected);
};

//  TEST SECTIONS  //

TEST_SECTION(XPC)->emplace({
    TEST_GROUP("Core/Child",
        {
            TEST_BIND(echo, "$::String::View"),
        }),
});
