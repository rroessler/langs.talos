#ifndef _XTEST_HANDLE_GROUP_HPP
#define _XTEST_HANDLE_GROUP_HPP

/// XT Modules
#include "xtest/handle/abstract.hpp"

namespace XT {

    /// @brief Testing Group Container.
    class Group : public Handle::Abstract<Group> {
        //  PROPERTIES  //

        /// @brief The setup handler.
        Handle::Callback m_setup = nullptr;

        /// @brief Bound Group Tests.
        std::vector<const Handle*> m_tests = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a group.
         * @param title             Group title.
         * @param location          Source location.
         */
        explicit Group(const $::String::Buffer& title, const Location& location) : Abstract(title, location) {}

        //  PUBLIC METHODS  //

        /// @brief Gets all the associated group tests.
        inline constexpr const std::vector<const Handle*>& tests() const noexcept { return m_tests; }

        /// @brief Returns the base test count.
        inline size_t count() const final {
            auto predicate = [](size_t acc, const Handle* handle) { return acc + handle->count(); };
            return std::ranges::fold_left(m_tests, 0, predicate);  // reduce now as necessary
        }

        /**
         * @brief Handles binding unit tests.
         * @param list                      Initializer list.
         */
        inline constexpr Group* bind(const Handle* test) { return m_tests = { test }, this; }
        inline constexpr Group* bind(const Handle::Initializer& list) { return m_tests = list, this; }
        inline constexpr Group* bind(Handle::Callback&& setup) { return m_setup = std::move(setup), this; }

        /**
         * @brief Handles emplacing unit tests.
         * @param list                      Initializer list.
         */
        inline constexpr Group* emplace(const Handle* test) { return m_tests.emplace_back(test), this; }
        inline constexpr Group* emplace(const Handle::Initializer& list) {
            return $::Ranges::Append(m_tests, list), this;
        }

        /**
         * @brief Handles executing all group tests.
         * @param runner                    Test runner.
         */
        void execute(Session::Runner* runner) const final;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles initializing groups.
         * @param runner                    Test runner.
         */
        bool m_initialize(Session::Runner* runner) const;
    };

}  // namespace XT

#endif
