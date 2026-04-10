#ifndef _TALOS_SERVER_CONNECTION_HPP
#define _TALOS_SERVER_CONNECTION_HPP

/// Talos Includes
#include "talos/async/service.hpp"
#include "talos/document/service.hpp"
#include "talos/server/events.hpp"
#include "talos/server/options.hpp"
#include "talos/server/transport.hpp"
#include "talos/server/worker.hpp"

namespace Talos::Server {

    /// @brief LSP Connection Service.
    class Connection : public XI::Define<Connection, XI::Shared, XLSP::Server::Connection> {
        //  PROPERTIES  //

        /// @brief The mutex for analysis.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Available services container.
        XI::Container* m_services;

        /// @brief Asynchrononous runtime service.
        Async::Service* m_async;

        /// @brief Module documents service.
        Document::Service* m_documents;

        /// @brief Events dispatcher instance.
        $::Ptr::Unique<Events> m_events;

        /// @brief Helpert utilities to be used.
        $::Ptr::Unique<Utilities> m_utilities;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a server connection.
         * @param services              Services container.
         * @param options               Options to be bound.
         */
        explicit Connection(const Options* options = $::Global::get<Options>());
        explicit Connection(XI::Container* services, const Options* options = $::Global::get<Options>());

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying documents.
        inline constexpr Document::Service* documents() noexcept { return m_documents; }
        inline constexpr const Document::Service* documents() const noexcept { return m_documents; }

        /// @brief Gets the underlying utilities.
        inline constexpr const Utilities* utilities() const noexcept { return m_utilities.get(); }

        /// @brief Prepares a suitable scoped connection guard.
        $_NODISCARD inline constexpr auto guard() noexcept { return $::Lock::guard(m_mutex); }

        /// @brief Allows getting underlying services.
        template <std::derived_from<XI::Service> T>
        inline constexpr T* service() const noexcept {
            return $_ASSERT(m_services->exists<T>()), m_services->get<T>();
        }

        /**
         * @brief Handles scheduling a server-worker.
         * @param args                  Worker arguments.
         */
        template <class... As>
        inline constexpr void schedule(As&&... args) {
            m_async->spawn<Delegate>(this, std::forward<As>(args)...);
        }

        /**
         * @brief Handles coordinating analysis.
         * @param args                  Worker arguments.
         */
        template <class... As>
        inline constexpr void analyze(As&&... args) {
            analyze(Refresh::ENTIRE, std::forward<As>(args)...);
        }

        /**
         * @brief Handles coordinating analysis.
         * @param mode                  Refresh mode.
         * @param args                  Worker arguments.
         */
        template <class... As>
        inline constexpr void analyze(Refresh mode, As&&... args) {
            schedule(std::forward<As>(args)..., [mode](Worker* worker) { worker->analyze(mode); });
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles launching the connection instance.
        inline int32_t m_listen() final { return m_async->launch<Transport>(this); }
    };

}  // namespace Talos::Server

#endif
