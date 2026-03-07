#ifndef _TALOS_MODULE_SERVICE_HPP
#define _TALOS_MODULE_SERVICE_HPP

/// Talos Modules
#include "talos/module/drafts.hpp"
#include "talos/module/graph.hpp"
#include "talos/module/loader.hpp"
#include "talos/resource/path.hpp"

namespace Talos::Import {

    /// @brief Outgoing Import Statistics.
    struct Statistics {
        size_t errors = 0;
        size_t hints = 0;
    };

    /// @brief Modules Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Services container available.
        XI::Container* m_services;

        /// @brief Available loaders to be used.
        $::Record<$::Ptr::Unique<Loader>> m_loaders = {};

        /// @brief Underlying module drafts.
        $::Ptr::Unique<Drafts> m_drafts = $::New().unique<Drafts>();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a module service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying drafts available.
        inline constexpr Drafts* drafts() const noexcept { return m_drafts.get(); }

        /**
         * @brief Handles fetching modules via their loader.
         * @param resource                  Document resource.
         */
        Module::Interface* fetch(const $::URI::View& resource);

        /**
         * @brief Handles preloading archived modules with arenas.
         * @param arenas                    Arenas to preload.
         */
        void preload(std::vector<$::Ptr::Unique<Linker::Arena>>&& arenas);

        /**
         * @brief Handles importing a module directly.
         * @param isolate                   Runtime isolate.
         * @param resource                  Document resource.
         * @param trace                     Resource trace.
         */
        Async::Thenable* import(Runtime::Isolate* isolate, const $::URI::View& resource);
        Async::Thenable* import(Runtime::Isolate* isolate, const $::URI::View& resource, const Resource::Trace& trace);

        /**
         * @brief Handles resolving resources.
         * @param script                    Script to be resolved.
         * @param hint                      Optional directory hint.
         */
        Resource::Result resolve(const $::String::View& script, const $::Filesystem::Path& hint = $::System::cwd());

        /**
         * @brief Constructs an import graph.
         * @param dependencies              Initial graphing dependencies.
         */
        inline $::Ptr::Unique<Graph> graph(const $::URI::Buffer& resource) { return graph(std::vector({ resource })); }
        inline $::Ptr::Unique<Graph> graph(const Dependencies& dependencies = {}) {
            return m_services->get<Graph>(dependencies);
        }

        /**
         * @brief Handles analyzing resources.
         * @param resource                  Resources to analyze.
         * @param report                    Should report results.
         */
        Statistics analyze(const $::URI::View& resource, bool report = false);
        Statistics analyze(const $::URI::Buffer& resource, bool report = false);
        Statistics analyze(const Dependencies& dependencies, bool report = false);

        /**
         * @brief Handles analyzing resources.
         * @param resource                  Resources to analyze.
         * @param reporter                  Collection reporter.
         * @param display                   Display the results.
         */
        Statistics analyze(const $::URI::View& resource, Diagnostic::Reporter* reporter, bool display = false);
        Statistics analyze(const $::URI::Buffer& resource, Diagnostic::Reporter* reporter, bool display = false);
        Statistics analyze(const Dependencies& dependencies, Diagnostic::Reporter* reporter, bool display = false);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Ensures that a module is parsed once fetched.
         * @param module                    Module to ensure.
         */
        Module::Interface* m_prepare(Module::Interface* module) const;
    };

}  // namespace Talos::Import

#endif
