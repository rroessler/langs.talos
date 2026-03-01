#ifndef _FORGE_TESTING_MAIN_HPP
#define _FORGE_TESTING_MAIN_HPP

/// Forge Modules
#include "forge/async/main.hpp"
#include "forge/async/thenable.hpp"
#include "forge/diagnostic/reporter.hpp"

namespace Forge::Testing {

    /// @brief Runtime Main Thread.
    class Main : public Async::Main {
        //  PROPERTIES  //

        /// @brief Verbose spinner details.
        $::Spinner::Shared m_spinner = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Async::Main::Main;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles launching the testing runtime.
        $_NORETURN void m_execute() final;

        /// @brief Declares that there are no tests available.
        void m_empty();

        /**
         * @brief Handles reporting type-errors.
         * @param reporter              Diagnostic reporter.
         * @param sources               Total testing sources.
         */
        bool m_report(Diagnostic::Reporter* reporter, size_t sources);

        /**
         * @brief Handles analyzing imports.
         * @param resource              Resource to analyze.
         * @param reporter              Diagnostic reporter.
         */
        bool m_analyze(const $::URI::Buffer& resource, Diagnostic::Reporter* reporter);

        /**
         * @brief Declares an unhandled runtime error.
         * @param resource              Resource that failed.
         * @param reason                The reason to throw.
         */
        void m_unhandled($::Map<$::URI::View, Value::Any>&& errors);
        void m_unhandled(const $::URI::View& resource, Value::Any reason);

        /**
         * @brief Handles importing tests.
         * @param resource              Resource to import.
         * @param reporter              Global reporter instance.
         */
        Async::Thenable* m_import(const $::URI::Buffer& resource, Diagnostic::Reporter* reporter);
    };

}  // namespace Forge::Testing

#endif
