#ifndef _XTEST_HANDLE_BENCH_HPP
#define _XTEST_HANDLE_BENCH_HPP

/// XT Modules
#include "xtest/handle/abstract.hpp"

namespace XT {

    /// @brief Benchmark Container.
    struct Bench : public Handle::Abstract<Bench> {
        //  TYPEDEFS  //

        /// @brief Measurements List.
        using Timings = std::vector<size_t>;

        /// @brief Samples Bounds.
        struct Samples {
            size_t minimum = 10;
            size_t maximum = 5000;
        };

        /// @brief Measurements Result.
        struct Result {
            size_t runs;     // Total runs taken.
            size_t sum;      // Total elapsed time.
            size_t mean;     // Mean time found.
            size_t minimum;  // Minimum time found.
            size_t maximum;  // Maximum time found.
            double stddev;   // Standard deviation.
        };

        /// @brief Benchmarking Options.
        struct Options {
            //  PROPERTIES  //

            /// @brief Denotes whether enabled or not.
            bool enabled = false;

            /// @brief Declare a warmup amount.
            size_t warmup = 0;

            /// @brief Minimum samples expected.
            Samples samples = {};

            /// @brief Prepare an expected timeout.
            $::Chrono::Duration timeout = 5s;

            //  CONSTRUCTORS  //

            /// @brief Default constructor.
            constexpr Options() = default;
        };

       private:
        //  PROPERTIES  //

        /// @brief Handles running a bench-mark.
        Handle::Callback m_callback;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a test-bench.
         * @param title                 Case title.
         * @param location              Source location.
         * @param callback              Test callback.
         */
        explicit Bench(const $::String::Buffer& title, const Location& location, Handle::Callback&& callback) :
            Abstract(title, location), m_callback(std::move(callback)) {}

        /**
         * @brief Handles running the callback.
         * @param runner                Test runner.
         */
        void execute(Session::Runner* runner) const final;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles analyzing results.
         * @param timings               Timings to analyze.
         */
        Result m_analyze(const Timings& timings) const;

        /**
         * @brief Handles running warmups.
         * @param runner                Test runner.
         * @param iterations            Warmup iterations.
         */
        void m_warmup(Session::Runner* runner, size_t iterations) const;

        /**
         * @brief Handles executing a run.
         * @param runner                Test runner.
         * @param timeout               Total timeout.
         * @param samples               Minimum samples.
         */
        Timings m_execute(Session::Runner* runner, size_t timeout, const Samples& samples) const;
    };

}  // namespace XT

#endif
