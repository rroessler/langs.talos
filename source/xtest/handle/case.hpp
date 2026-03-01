#ifndef _XTEST_HANDLE_CASE_HPP
#define _XTEST_HANDLE_CASE_HPP

/// XT Modules
#include "xtest/handle/abstract.hpp"

namespace XT {

    /// @brief Testing Case Container.
    class Case : public Handle::Abstract<Case> {
        //  PROPERTIES  //

        /// @brief Handles running a test-callback.
        Handle::Callback m_callback;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a test-case.
         * @param title                 Case title.
         * @param location              Source location.
         * @param callback              Test callback.
         */
        explicit Case(const $::String::Buffer& title, const Location& location, Handle::Callback&& callback) :
            Abstract(title, location), m_callback(std::move(callback)) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Handles running the callback.
         * @param runner                Test runner.
         */
        void execute(Session::Runner* runner) const final;
    };

}  // namespace XT

#endif
