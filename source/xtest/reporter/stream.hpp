#ifndef _XTEST_REPORTER_STREAM_HPP
#define _XTEST_REPORTER_STREAM_HPP

/// XT Modules
#include "xtest/reporter/interface.hpp"

namespace XT::Reporter {

    /// @brief Stream Reporter.
    class $_ABSTRACT Stream : public Interface {
        //  PROPERTIES  //

        /// @brief The underlying stream output.
        $::Stream::Output& m_output = $::IO::cout();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a stream instance.
         * @param runner            Session runner.
         * @param output            Output stream.
         */
        explicit Stream(Session::Runner* runner) : Interface(runner) {}
        explicit Stream(Session::Runner* runner, $::Stream::Output& output) : Interface(runner), m_output(output) {}

        /// @brief Abstract destructor.
        virtual ~Stream() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Before running hook.
         * @param section           Total sections.
         * @param options           Testing options.
         */
        virtual void before_running($_UNUSED size_t section, $_UNUSED const Session::Options* options) override {}

        /**
         * @brief After running hook.
         * @param section           Total sections.
         * @param elapsed           Elapsed duration.
         */
        virtual void after_running($_UNUSED size_t section, $_UNUSED const $::Chrono::Duration& elapsed) override {}

        /**
         * @brief Group opening hook.
         * @param group             Group starting.
         */
        virtual void group_opened($_UNUSED const Group* group) override {}

        /**
         * @brief Group closing hook.
         * @param group             Group ending.
         */
        virtual void group_closed($_UNUSED const Group* group) override {}

        /**
         * @brief Group failure hook.
         * @param group             Group failed.
         * @param reason            Failure reason.
         */
        virtual void group_failure($_UNUSED const Group* group, $_UNUSED const $::String::Buffer& reason) override {}

        /**
         * @brief Test starting hook.
         * @param test              Test started.
         */
        virtual void test_starting($_UNUSED const Handle* test) override {}

        /**
         * @brief Test teardown hook.
         * @param test              Test finished.
         */
        virtual void test_teardown($_UNUSED const Handle* test) override {}

        /**
         * @brief Test successful hook.
         * @param test              Test finished.
         * @param duration          Test duration.
         */
        virtual void test_success($_UNUSED const Handle* test, $_UNUSED const $::Chrono::Duration& duration) override {}

        /**
         * @brief Test failed hook.
         * @param test              Test finished.
         * @param reason            Failure reason.
         */
        virtual void test_failure($_UNUSED const Handle* test, $_UNUSED const $::String::Buffer& reason) override {}

        /**
         * @brief Test timeout hook.
         * @param test              Test finished.
         * @param timeout           Timeout duration.
         */
        virtual void test_timeout($_UNUSED const Handle* test, $_UNUSED const $::Chrono::Duration& timeout) override {}

        /**
         * @brief Test skipped result.
         * @param test              Test skipped.
         */
        virtual void test_skipped($_UNUSED const Handle* test) override {}

        /**
         * @brief Test partial result.
         * @param test              Test unimplemented.
         */
        virtual void test_unimplemented($_UNUSED const Handle* test) override {}

        /**
         * @brief Test progress hook.
         * @param test              Test progressing.
         * @param progress          Progress update.
         */
        virtual void test_progress($_UNUSED const Handle* test, $_UNUSED const Session::Progress& progress) override {}

        /**
         * @brief Handles assertion startups.
         * @param assertion         Assertion information.
         */
        virtual void assertion_starting($_UNUSED const Assert::Info& assertion) override {}

        /**
         * @brief Handles assertion teardowns.
         * @param assertion         Assertion information.
         * @param result            Assertion result flag.
         */
        virtual void assertion_teardown($_UNUSED const Assert::Info& assertion, $_UNUSED bool result) override {}

        /**
         * @brief Handles assertion failures.
         * @param assertion         Assertion information.
         */
        virtual void assertion_failure($_UNUSED const Assert::Info& assertion) override {}

        /**
         * @brief Benchmark finished hook.
         * @param bench             Benchmark finished.
         * @param result            Result of benchmark.
         */
        virtual void bench_finished($_UNUSED const Bench* bench, $_UNUSED const Bench::Result& result) override {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying stream to output to.
        inline constexpr $::Stream::Output& m_stream() const noexcept { return m_output; }
    };

}  // namespace XT::Reporter

#endif
