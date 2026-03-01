#ifndef _XTEST_REPORTER_FACADE_HPP
#define _XTEST_REPORTER_FACADE_HPP

/// XT Modules
#include "xtest/handle/group.hpp"
#include "xtest/reporter/interface.hpp"

namespace XT::Reporter {

    /// @brief Facade Reporter.
    class Facade : public Interface {
        //  PROPERTIES  //

        /// @brief Verbose stack-trace.
        bool m_verbose = false;

        /// @brief Incoming failed assertions.
        Assert::Pending m_assertions = {};

        /// @brief The encapsulated reporter instance.
        $::Ptr::Unique<Interface> m_proxy = nullptr;

        /// @brief The associated streaming output.
        $::Ptr::Unique<$::Stream::Output> m_stream = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a facade based reporter.
         * @param tag               Tag of proxy.
         * @param runner            Session runner.
         */
        explicit Facade(Tag tag, Session::Runner* runner);

        //  PUBLIC METHODS  //

        /**
         * @brief Before running hook.
         * @param sections          Total sections.
         * @param options           Testing options.
         */
        void before_running(size_t sections, const Session::Options* options) final {
            m_proxy->before_running(sections, options);
        }

        /**
         * @brief After running hook.
         * @param sections          Total sections.
         * @param elapsed           Elapsed duration.
         */
        void after_running(size_t sections, const $::Chrono::Duration& elapsed) final {
            m_proxy->after_running(sections, elapsed);
        }

        /**
         * @brief Group opening hook.
         * @param group             Group starting.
         */
        void group_opened(const Group* group) final { m_proxy->group_opened(group), ++m_depth(), m_push(group); }

        /**
         * @brief Group closing hook.
         * @param group             Group ending.
         */
        void group_closed(const Group* group) final { m_proxy->group_closed(group), --m_depth(), m_pop(group); }

        /**
         * @brief Group failure hook.
         * @param group             Group failed.
         * @param reason            Failure reason.
         */
        void group_failure(const Group* group, const $::String::Buffer& reason) final {
            m_pending().emplace_back(m_trace(), group->meta()->title, reason);
            m_proxy->group_failure(group, reason);  // and show here as necessary
        }

        /**
         * @brief Test starting hook.
         * @param test              Test started.
         */
        void test_starting(const Handle* test) final { m_proxy->test_starting(test), m_push(test); }

        /**
         * @brief Test teardown hook.
         * @param test              Test finished.
         */
        void test_teardown(const Handle* test) final { m_proxy->test_teardown(test), m_assertions = {}, m_pop(test); }

        /**
         * @brief Test successful hook.
         * @param test              Test finished.
         * @param duration          Test duration.
         */
        void test_success(const Handle* test, const $::Chrono::Duration& duration) final {
            // if no assertions failed (eg: are pending), then we can safely succeed
            if (m_assertions.empty()) return m_proxy->test_success(test, duration), m_pass(test, duration);

            // otherwise we need to post-fail here
            const auto& title = test->meta()->title;

            // append all the pending assertions that we collected
            for (const auto& failure : m_assertions) m_pending().emplace_back(failure.trace, title, failure.reason);

            auto plural = m_assertions.size() == 1 ? "" : "s";  // show how many assertions failed
            auto message = fmt::format("Failed {0} Assertion{1}", m_assertions.size(), plural);
            m_proxy->test_failure(test, message), m_fail(test);  // and declare the failure now
        }

        /**
         * @brief Test failed hook.
         * @param test              Test finished.
         * @param reason            Failure reason.
         */
        void test_failure(const Handle* test, const $::String::Buffer& reason) final {
            m_pending().emplace_back(m_trace(), test->meta()->title, reason);
            m_proxy->test_failure(test, reason), m_fail(test);  // and fail
        }

        /**
         * @brief Test timeout hook.
         * @param test              Test finished.
         * @param timeout           Timeout duration.
         */
        void test_timeout(const Handle* test, const $::Chrono::Duration& timeout) final {
            auto reason = fmt::format("Test timed out after {0}", timeout);
            m_pending().emplace_back(m_trace(), test->meta()->title, reason);
            m_proxy->test_timeout(test, timeout), m_fail(test);  // and fail
        }

        /**
         * @brief Test skipped result.
         * @param test              Test skipped.
         */
        void test_skipped(const Handle* test) final { m_proxy->test_skipped(test), m_skip(test); }

        /**
         * @brief Test partial result.
         * @param test              Test unimplemented.
         */
        void test_unimplemented(const Handle* test) final { m_proxy->test_unimplemented(test), m_skip(test); }

        /**
         * @brief Test progress hook.
         * @param test              Test progressing.
         * @param details           Progress update.
         */
        void test_progress(const Handle* test, const Session::Progress& details) final {
            m_proxy->test_progress(test, details);
        }

        /**
         * @brief Handles assertion startups.
         * @param assertion         Assertion information.
         */
        void assertion_starting(const Assert::Info& assertion) final {
            m_push(assertion.location), m_proxy->assertion_starting(assertion);
        }

        /**
         * @brief Handles assertion teardowns.
         * @param assertion         Assertion information.
         * @param result            Assertion result flag.
         */
        void assertion_teardown(const Assert::Info& assertion, bool result) final {
            m_pop(), m_proxy->assertion_teardown(assertion, result);
        }

        /**
         * @brief Handles assertion failures.
         * @param assertion         Assertion information.
         */
        void assertion_failure(const Assert::Info& assertion) final {
            auto reason = $::String::Buffer(assertion.message);  // attempt resolving the message
            if (reason.empty()) reason = fmt::format("Failed assertion '{0}'", assertion.label);
            m_assertions.emplace_back(m_trace(), "", reason), assertion_teardown(assertion, false);
        }

        /**
         * @brief Benchmark finished hook.
         * @param bench             Benchmark finished.
         * @param result            Result of benchmark.
         */
        void bench_finished(const Bench* bench, const Bench::Result& result) final {
            m_proxy->bench_finished(bench, result), m_pass(bench, result.sum);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles popping the stack.
         * @param test                  Test to pop.
         */
        inline void m_pop() { m_trace().pop_back(); }
        inline void m_pop(const Handle*) { m_assertions = {}, m_pop(); }

        /**
         * @brief Handles pushing a test onto the stack.
         * @param test                  Test to push.
         */
        inline void m_push(const Handle* test) { return m_push(test->meta()->location); }
        inline void m_push(const Location& location) {
            if (location.anonymous()) m_trace().emplace_back("");  // ignoreable
            else m_trace().emplace_back($::Convert::stringify(location));
        }

        /**
         * @brief Handles pushing a stack-trace.
         * @param stack                 Stack to push.
         */
        inline size_t m_push(const std::vector<Location>& stack) {
            for (const auto& location : stack) m_push(location);
            return stack.size();  // and emit the final size now
        }

        /**
         * @brief Handles skipping tests.
         * @param test                  Test to skip.
         */
        inline void m_skip(const Handle* test) { ++m_stats().skipped(), test_teardown(test); }

        /**
         * @brief Handles failing tests.
         * @param test                  Test to fail.
         */
        inline void m_fail(const Handle* test) { ++m_stats().failed(), test_teardown(test); }

        /**
         * @brief Handles passing tests.
         * @param test                  Test to pass.
         * @param duration              Elapsed time.
         */
        inline void m_pass(const Handle* test, const $::Chrono::Duration& duration) { m_pass(test, duration.count()); }
        inline void m_pass(const Handle* test, size_t duration) {
            auto& stats = m_stats();  // get statistics
            ++stats.passed(), stats.elapsed() += duration;
            test_teardown(test);  // and teardown now
        }
    };

}  // namespace XT::Reporter

#endif
