#ifndef _XTEST_SESSION_RUNNER_HPP
#define _XTEST_SESSION_RUNNER_HPP

/// XT Modules
#include "xtest/assert/that.hpp"
#include "xtest/reporter/interface.hpp"
#include "xtest/session/options.hpp"
#include "xtest/session/service.hpp"
#include "xtest/session/statistics.hpp"

namespace XT::Session {

    /// @brief Transient Session Context.
    class Runner : public XI::Define<Runner, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Current runner depth.
        size_t m_depth = 0;

        /// @brief Underlying session options.
        Options* m_options = nullptr;

        /// @brief Bound session container.
        XI::Container* m_services = nullptr;

        /// @brief Reporter service.
        $::Ptr::Unique<Reporter::Interface> m_reporter = nullptr;

        /// @brief Statistics service.
        $::Ptr::Unique<Statistics> m_statistics = $::New().unique<Statistics>();

        /// @brief Assertion service.
        $::Ptr::Unique<Assert::That> m_asserts = $::New().unique<Assert::That>(this);

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an anonymous runner.
         * @param options               Session options.
         */
        explicit Runner(Options* options = $::Global::get<Options>());

        /**
         * @brief Constructs a service-runner.
         * @param services              Session services.
         */
        explicit Runner(XI::Container* services);

        //  PUBLIC METHODS  //

        inline constexpr size_t& depth() noexcept { return m_depth; }
        inline constexpr size_t depth() const noexcept { return m_depth; }

        inline constexpr Options* options() const noexcept { return m_options; }
        inline constexpr Assert::That* asserts() const noexcept { return m_asserts.get(); }
        inline constexpr Statistics* statistics() const noexcept { return m_statistics.get(); }
        inline constexpr Reporter::Interface* reporter() const noexcept { return m_reporter.get(); }

        /// @brief Gets a service from the runner.
        template <std::derived_from<XI::Shared> T>
        inline constexpr T* service() const noexcept {
            return $_ASSERT(m_services->exists<T>()), m_services->get<T>();
        }

        /// @brief Gets a unique service from the runner.
        template <std::derived_from<XI::Unique> T>
        inline constexpr $::Ptr::Unique<T> service() const noexcept {
            return m_services->get<T>();
        }

        /// @brief Handles getting the underlying services container.
        template <std::derived_from<XI::Container> T>
        inline constexpr XI::Container* service() const noexcept {
            return m_services;  // get the base container now
        }
    };

}  // namespace XT::Session

#endif
