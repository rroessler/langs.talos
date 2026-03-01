#ifndef _XTEST_REPORTER_TEXT_HPP
#define _XTEST_REPORTER_TEXT_HPP

/// XT Modules
#include "xtdlib/system/platform.hpp"
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

    /// @brief Text Reporter.
    template <>
    class Proxy<Tag::TEXT> : public Stream {
        //  TYPEDEFS  //

        /// @brief Benchmark record.
        using Record = std::pair<const Bench*, Bench::Result>;

        //  PROPERTIES  //

        /// @brief Current flushing index.
        size_t m_fidx = 0;

        /// @brief Indentation size.
        size_t m_indent = 2;

        /// @brief All recorded benchmark results.
        std::vector<Record> m_records = {};

        /// @brief Current spinner implementation.
        $::Spinner::Shared m_spinner = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base stream.
        using Stream::Stream;

        //  PUBLIC METHODS  //

        /**
         * @brief After running hook.
         * @param sections          Total sections.
         * @param elapsed           Elapsed duration.
         */
        void after_running(size_t sections, const $::Chrono::Duration& elapsed) final {
            for (const auto& [test, benchmark] : m_records) {  // show all the benchmark results now
                m_stream() << $::Dye::bold(test->meta()->title) << ": " << $::Dye::dim("{0} runs", benchmark.runs);
                m_stream() << '\n', m_time(benchmark), m_stream() << '\n', m_range(benchmark), m_stream() << "\n\n";
            }

            // destructure some items
            const auto& stats = m_stats();

            // get the final totals to be used
            auto total = stats.total();
            auto real = $::Chrono::Duration(stats.elapsed());

            // show the immediate results now if there was a total
            if (total) {
                m_stream() << ' ' << stats.passed() << " passed\n";
                m_stream() << ' ' << stats.failed() << " failed\n";
                m_stream() << ' ' << stats.skipped() << " skipped\n\n";
            }

            // show the final result as necessary now
            m_stream() << "Ran " << total << " test" << (total == 1 ? "" : "s");
            m_stream() << " across " << sections << " section" << (sections == 1 ? "" : "s");
            m_stream() << ' ' << $::Dye::dim("[R: {0}, T: {1}]", real, elapsed) << std::endl;
        }

        /**
         * @brief Group opening hook.
         * @param group             Group starting.
         */
        void group_opened(const Group* group) final {
            auto* meta = group->meta();  // get the traits
            m_stream() << m_before();    // show the padding

            // handle based on the current group state
            if (meta->skip) m_stream() << $::Dye::yellow("Skipping");
            else if (meta->todo) m_stream() << $::Dye::magenta("Unimplemented");
            else m_stream() << $::Dye::cyan("Testing");  // otherwise valid

            m_stream() << ": " << $::Dye::italic(meta->title);  // and show the final details now
            if (!meta->location.anonymous()) m_stream() << $::Dye::dim(" -> {0}", meta->location);
            m_stream() << std::endl;  // and close the location now
        }

        /**
         * @brief Group closing hook.
         * @param group             Group ending.
         */
        void group_closed(const Group*) final {
            if (m_depth() > 1) return;  // ignore flushing
            if (m_pending().size()) m_stream() << '\n', m_flush();
            m_stream() << '\n';  // and show some final depth
        }

        /**
         * @brief Group failure hook.
         * @param group             Group failed.
         * @param reason            Failure reason.
         */
        void group_failure(const Group*, $_UNUSED const $::String::Buffer&) final {}

        /**
         * @brief Test starting hook.
         * @param test              Test started.
         */
        void test_starting(const Handle* test) final {
            // ensure that there are no active tests
            $_ASSERT(m_spinner == nullptr, "Expected no active tests");

            // construct the current spinner instance
            m_spinner = m_loader();

            m_spinner->prefix(m_before());  // bind the options now
            m_spinner->suffix($::Dye::dim(test->meta()->title));
        }

        /**
         * @brief Test teardown hook.
         * @param test              Test finished.
         */
        void test_teardown(const Handle*) final { m_spinner = nullptr; }

        /**
         * @brief Test successful hook.
         * @param test              Test finished.
         * @param duration          Test duration.
         */
        void test_success(const Handle* test, const $::Chrono::Duration& duration) final {
            m_finalize(test, $::Dye::green("✓"), fmt::to_string(duration));
        }

        /**
         * @brief Test failed hook.
         * @param test              Test finished.
         * @param reason            Failure reason.
         */
        void test_failure(const Handle* test, const $::String::Buffer& reason) final {
            m_finalize(test, $::Dye::red("✗"), reason);
        }

        /**
         * @brief Test timeout hook.
         * @param test              Test finished.
         * @param timeout           Timeout duration.
         */
        void test_timeout(const Handle* test, const $::Chrono::Duration& timeout) final {
            m_finalize(test, $::Dye::red("!"), fmt::format("Exceeded timeout - {0}", timeout));
        }

        /**
         * @brief Test skipped result.
         * @param test              Test skipped.
         */
        void test_skipped(const Handle* test) final { m_finalize(test, $::Dye::yellow("»")); }

        /**
         * @brief Test partial result.
         * @param test              Test unimplemented.
         */
        void test_unimplemented(const Handle* test) final { m_finalize(test, $::Dye::magenta("-")); }

        /**
         * @brief Test progress hook.
         * @param test              Test progressing.
         * @param progress          Progress update.
         */
        void test_progress(const Handle* test, const Session::Progress& progress) final {
            $_ASSERT(m_spinner, "Expected an active test");  // ensure existence
            auto percentage = 100 * progress.iter / static_cast<double>(progress.total);
            m_spinner->suffix($::Dye::dim("{0} ({1}) - {2:.2}%", test->meta()->title, progress.label, percentage));
        }

        /**
         * @brief Benchmark finished hook.
         * @param bench             Benchmark finished.
         * @param result            Result of benchmark.
         */
        void bench_finished(const Bench* bench, const Bench::Result& result) final {
            auto details = fmt::format("{0} over {1} runs", $::Chrono::Duration(result.mean), result.runs);
            m_finalize(bench, $::Dye::blue("⏺"), details), m_records.emplace_back(bench, result);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying stream details.
        $::Stream::Output& m_stream() const noexcept { return $::IO::cout(); }

        /// @brief Constructs the current padding.
        inline $::String::Buffer m_before() const { return $::String::Buffer(m_depth() * m_indent, ' '); }

        /// @brief Handles flushing all pending failures.
        void m_flush() {
            const auto& pending = m_pending();  // get the underlying pending failures
            for (size_t ii = m_fidx; ii < pending.size(); ii++) m_flush(pending.at(ii));
            m_fidx = pending.size();  // update the flush index to be used
        }

        /**
         * @brief Handles flushing all pending failures.
         * @param failure           Failure to flush.
         */
        void m_flush(const Assert::Failure& failure) const {
            m_stream() << $::Dye::red("Failed Test") << ' ';  // prepare details now
            m_stream() << $::Dye::italic(failure.title) << ": " << failure.reason << '\n';
            for (const auto& location : std::views::reverse(failure.trace)) {
                if (location.size()) m_stream() << $::Dye::dim("| {0}", location) << '\n';
            }
        }

        /**
         * @brief Handles showing completion items.
         * @param test              Test instance.
         * @param status            Status text.
         * @param suffix            Additional suffix text.
         */
        void m_finalize(const Handle* test, const $::ANSI& status, const $::String::View& suffix = "") {
            $_ASSERT(m_spinner, "Expected an active test"), m_spinner->dismiss();  // ensure dismissed
            m_stream() << m_before() << status << ' ' << $::Dye::dim(test->meta()->title);
            if (suffix.size()) m_stream() << ' ' << $::Dye::dim("[{0}]", suffix);
            m_stream() << std::endl;  // and show the suffix as well
        }

        /**
         * @brief Formats benchmark times.
         * @param record            Record to format.
         */
        void m_time(const Bench::Result& record) {
            m_stream() << "  Time (" << $::Dye::green("mean").bold();
            m_stream() << " ± " << $::Dye::green("σ").dim() << ")";

            m_stream() << " - " << $::Dye::green($::Chrono::Duration(record.mean)).bold();
            m_stream() << " ± " << $::Dye::green($::Chrono::Duration(record.stddev)).dim();
        }

        /**
         * @brief Formats benchmark ranges.
         * @param record            Record to format.
         */
        void m_range(const Bench::Result& record) {
            m_stream() << "  Range (" << $::Dye::cyan("min").bold();
            m_stream() << " … " << $::Dye::magenta("max") << ")";

            m_stream() << " - " << $::Dye::cyan($::Chrono::Duration(record.minimum)).bold();
            m_stream() << " … " << $::Dye::magenta($::Chrono::Duration(record.maximum));
        }
    };

}  // namespace XT::Reporter

#endif
