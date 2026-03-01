#ifndef _XTEST_REPORTER_INTERFACE_HPP
#define _XTEST_REPORTER_INTERFACE_HPP

/// XT Modules
#include "xtest/assert/failure.hpp"
#include "xtest/assert/info.hpp"
#include "xtest/forward/reporter.hpp"
#include "xtest/handle/bench.hpp"
#include "xtest/handle/group.hpp"
#include "xtest/session/options.hpp"
#include "xtest/session/progress.hpp"
#include "xtest/session/statistics.hpp"

namespace XT::Reporter {

    /// @brief Reporter Interface.
    class $_ABSTRACT Interface {
        //  PROPERTIES  //

        /// @brief Attached context.
        Session::Runner* m_runner;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default constructor.
        explicit Interface() = delete;

        /**
         * @brief Constructs a reporter interface.
         * @param runner            Session runner.
         */
        explicit Interface(Session::Runner* runner) : m_runner(runner) {}

        /// @brief Abstract destructor.
        virtual ~Interface() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Before running hook.
         * @param sections          Total sections.
         * @param options           Testing options.
         */
        virtual void before_running(size_t sections, const Session::Options* options) = 0;

        /**
         * @brief After running hook.
         * @param sections          Total sections.
         * @param elapsed           Elapsed duration.
         */
        virtual void after_running(size_t sections, const $::Chrono::Duration& elapsed) = 0;

        /**
         * @brief Group opening hook.
         * @param group             Group starting.
         */
        virtual void group_opened(const Group* group) = 0;

        /**
         * @brief Group closing hook.
         * @param group             Group ending.
         */
        virtual void group_closed(const Group* group) = 0;

        /**
         * @brief Group failure hook.
         * @param group             Group failed.
         * @param reason            Failure reason.
         */
        virtual void group_failure(const Group* group, const $::String::Buffer& reason) = 0;

        /**
         * @brief Test starting hook.
         * @param test              Test started.
         */
        virtual void test_starting(const Handle* test) = 0;

        /**
         * @brief Test teardown hook.
         * @param test              Test finished.
         */
        virtual void test_teardown(const Handle* test) = 0;

        /**
         * @brief Test successful hook.
         * @param test              Test finished.
         * @param duration          Test duration.
         */
        virtual void test_success(const Handle* test, const $::Chrono::Duration& duration) = 0;

        /**
         * @brief Test failed hook.
         * @param test              Test finished.
         * @param reason            Failure reason.
         */
        virtual void test_failure(const Handle* test, const $::String::Buffer& reason) = 0;

        /**
         * @brief Test timeout hook.
         * @param test              Test finished.
         * @param timeout           Timeout duration.
         */
        virtual void test_timeout(const Handle* test, const $::Chrono::Duration& timeout) = 0;

        /**
         * @brief Test skipped result.
         * @param test              Test skipped.
         */
        virtual void test_skipped(const Handle* test) = 0;

        /**
         * @brief Test partial result.
         * @param test              Test unimplemented.
         */
        virtual void test_unimplemented(const Handle* test) = 0;

        /**
         * @brief Test progress hook.
         * @param test              Test progressing.
         * @param progress          Progress update.
         */
        virtual void test_progress(const Handle* test, const Session::Progress& progress) = 0;

        /**
         * @brief Handles assertion startups.
         * @param assertion         Assertion information.
         */
        virtual void assertion_starting(const Assert::Info& assertion) = 0;

        /**
         * @brief Handles assertion teardowns.
         * @param assertion         Assertion information.
         * @param result            Assertion result flag.
         */
        virtual void assertion_teardown(const Assert::Info& assertion, bool result) = 0;

        /**
         * @brief Handles assertion failures.
         * @param assertion         Assertion information.
         */
        virtual void assertion_failure(const Assert::Info& assertion) = 0;

        /**
         * @brief Benchmark finished hook.
         * @param bench             Benchmark finished.
         * @param result            Result of benchmark.
         */
        virtual void bench_finished(const Bench* bench, const Bench::Result& result) = 0;

       protected:
        //  PRIVATE METHODS  //

        size_t& m_depth();
        size_t m_depth() const;

        /// @brief Gets a reference to the underlying stack-trace.
        Assert::Trace& m_trace();
        const Assert::Trace& m_trace() const;

        /// @brief Gets a reference to the statistics available.
        Session::Statistics& m_stats();
        const Session::Statistics& m_stats() const;

        /// @brief Gets a reference to the pending failures.
        Assert::Pending& m_pending();
        const Assert::Pending& m_pending() const;

        /// @brief Constructs a new loader instance.
        $::Spinner::Shared m_loader() const;
    };

}  // namespace XT::Reporter

#endif
