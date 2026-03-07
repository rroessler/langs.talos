#ifndef _TALOS_SERVER_WORKER_HPP
#define _TALOS_SERVER_WORKER_HPP

/// Talos Modules
#include "talos/crate/registry.hpp"
#include "talos/forward/async.hpp"
#include "talos/forward/server.hpp"

namespace Talos::Server {

    /// @brief Server Worker Callback.
    using Callback = $::Functor::Unique<void(Worker*)>;

    /// @brief Isolate Executor Abstraction.
    class Worker {
        //  TYPEDEFS  //

        /// @brief Allow the delegate internal access.
        friend struct Delegate;

        //  PROPERTIES  //

        /// @brief The underlying worker callback.
        Callback m_callback;

        /// @brief Bound server connection.
        Connection* m_connection;

        /// @brief Underlying resource instance.
        $::URI::Buffer m_resource;

        /// @brief The associated crate descriptor.
        $::Ptr::Unique<Crate::Manifest> m_crate;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a anonymous server worker.
         * @param connection                Server connection.
         * @param callback                  Worker callback.
         */
        explicit Worker(Connection* connection, Callback&& callback) :
            Worker(connection, $::URI::Anonymous(), std::move(callback)) {}

        /**
         * @brief Constructs a server worker.
         * @param connection                Server connection.
         * @param resource                  Document resource.
         * @param callback                  Worker callback.
         */
        explicit Worker(Connection* connection, const $::URI::View& resource, Callback&& callback) :
            m_callback(std::move(callback)),
            m_connection(connection),
            m_resource(resource.buffer()),
            m_crate(Crate::Registry::scan(m_resource)) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying resource value.
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }

        /**
         * @brief Forces the worker to analyze all the cached documents.
         * @param fresh                     Forcibly clear all drafts.
         */
        void analyze(bool fresh = false) const noexcept;

        /**
         * @brief Handles formatting a file.
         * @param options                   Format options.
         */
        std::vector<XLSP::Document::Edit> format() const noexcept;
        std::vector<XLSP::Document::Edit> format(const Format::Options& options) const noexcept;
    };

    /// @brief Handles executing a worker.
    struct Delegate : public Async::Task<Delegate>, public Worker {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a server task.
         * @param args                      Worker arguments.
         */
        template <class... As>
        explicit Delegate(As&&... args) : Worker(std::forward<As>(args)...) {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the underlying task.
        void m_execute() final { m_callback(this); }
    };

}  // namespace Talos::Server

#endif
