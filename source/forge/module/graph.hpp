#ifndef _FORGE_MODULE_GRAPH_HPP
#define _FORGE_MODULE_GRAPH_HPP

/// C++ Includes
#include <future>
#include <queue>

/// Forge Includes
#include "forge/forward/module.hpp"
#include "forge/forward/syntax.hpp"

namespace Forge::Import {

    /// @brief Explicit Graph Dependencies.
    using Dependencies = std::vector<$::URI::Buffer>;

    /// @brief A graph nodule.
    struct Nodule {
        //  PROPERTIES  //

        /// @brief Associated module reference.
        Module::Interface* module = nullptr;

        /// @brief Parent module reference.
        std::vector<Nodule*> parents = {};

        /// @brief Dependencies bound to a nodule.
        std::vector<Nodule*> children = {};

        //  CONSTRUCTORS  //

        /// @brief Allow default construction (for root nodes).
        explicit Nodule() = default;

        /**
         * @brief Allow construction of nodules.
         * @param module            Module interface.
         */
        explicit Nodule(Module::Interface* module) : module(module) {}
    };

    /// @brief Module Dependency Graph.
    class Graph : public XI::Define<Graph, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Bound modules service.
        Import::Service* m_modules;

        /// @brief All independent graph roots.
        $::Set<Nodule*> m_roots = {};

        /// @brief Cache of nodes for quick lookup.
        $::Map<Module::Interface*, $::Ptr::Unique<Nodule>> m_nodes = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted graph instance.
        explicit Graph();

        /**
         * @brief Constructs a graph instance.
         * @param services                  Services container.
         * @param dependencies              Dependencies to bind.
         */
        explicit Graph(XI::Container* services, const Dependencies& dependencies = {});

        /**
         * @brief Constructs an import graph.
         * @param modules                   Modules service.
         * @param dependencies              Dependencies to bind.
         */
        explicit Graph(Import::Service* modules, const Dependencies& dependencies = {}) : m_modules(modules) {
            for (const auto& resource : dependencies) add(resource);  // bind the initial dependencies
        }

        //  PUBLIC METHODS  //

        /// @brief Gets all the available root nodes.
        std::vector<Module::Interface*> roots() const noexcept;

        /// @brief Gets all the avaialble trailing nodes.
        std::vector<Module::Interface*> leaves() const noexcept;

        /**
         * @brief Handles adding a module to the graph.
         * @param resource                  Module to add.
         */
        inline const Nodule* add(Module::Interface* module) { return m_link(module, nullptr); }
        inline const Nodule* add(const $::URI::View& resource) { return add(m_import(resource).get()); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles linking a depedency to a parent.
         * @param dependency                Depedency to link.
         * @param parent                    Parent nodule reference.
         */
        Nodule* m_link(Module::Interface* dependency, Nodule* parent);

        /**
         * @brief Handles importing a singular resource.
         * @param resource                  Resource to import.
         */
        std::future<Module::Interface*> m_import(const $::URI::View& resource) const;

        /**
         * @brief Handles importing a set of module resources.
         * @param module                    Imports a modules dependencies.
         */
        std::vector<Module::Interface*> m_import(Module::Interface* parent) const;

        /**
         * @brief Handles importing a set of resources.
         * @param resources                 Dependency resources.
         */
        std::vector<Module::Interface*> m_import(const Dependencies& resources) const;
    };

}  // namespace Forge::Import

#endif
