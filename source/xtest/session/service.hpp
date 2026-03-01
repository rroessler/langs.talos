#ifndef _XTEST_SESSION_SERVICE_HPP
#define _XTEST_SESSION_SERVICE_HPP

/// XT Modules
#include "xtest/forward/handle.hpp"
#include "xtest/forward/session.hpp"

namespace XT::Session {

    /// @brief Testing Session Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief The bound services container.
        XI::Container* m_services;

        /// @brief Current runner instance.
        Runner* m_runner = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a session instance.
         * @param services                  Services to bind.
         */
        explicit Service(XI::Container* services) : m_services(services) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Launches a testing session.
         * @param sections                  Sections to run.
         */
        int32_t launch(const $::Dict<Group*>& sections = {});

        /// @brief Gets the current runner instance.
        inline constexpr Runner* runner() const noexcept { return m_runner; }
    };

}  // namespace XT::Session

#endif
