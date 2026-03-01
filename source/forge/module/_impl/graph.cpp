/// Forge Includes
#include "forge/module/graph.hpp"
#include "forge/module/interface.hpp"
#include "forge/module/service.hpp"
#include "forge/runtime/container.hpp"
#include "forge/runtime/options.hpp"

//  CONSTRUCTORS  //

Forge::Import::Graph::Graph() : Graph($::Global::get<Runtime::Container>()) {}
Forge::Import::Graph::Graph(XI::Container* services, const Dependencies& dependencies) :
    Graph(services->get<Import::Service>(), dependencies) {}

//  PUBLIC METHODS  //

std::vector<Forge::Module::Interface*> Forge::Import::Graph::roots() const noexcept {
    auto predicate = [](const Nodule* node) { return node->module; };
    return $::Ranges::To(m_roots | std::views::transform(predicate));
}

std::vector<Forge::Module::Interface*> Forge::Import::Graph::leaves() const noexcept {
    // prepare the resultant values to be used
    auto modules = std::vector<Module::Interface*>();
    auto visited = $::Set<const Module::Interface*>({ nullptr });

    // construct a queue filled with the underlying nodules
    auto queued = std::queue<const Nodule*>(m_roots.begin(), m_roots.end());

    // attempt a "breadth-first-search" now
    for (; queued.size(); queued.pop()) {
        // get the top-most node to work with now
        auto* head = queued.front();

        // emplace all the children whilst possible to do so
        for (const auto* child : head->children) {
            if (!visited.contains(child->module)) queued.push(child);
        }

        // emplace this node onto the visited stack and module list
        modules.emplace_back(head->module), visited.emplace(head->module);
    }

    // return the resulting leaves now
    return modules;
}

//  PRIVATE METHODS  //

Forge::Import::Nodule* Forge::Import::Graph::m_link(Module::Interface* module, Nodule* parent) {
    // ignore if the module does not actually exist
    if ($_UNLIKELY(module == nullptr)) return nullptr;

    // check if the module already exists
    auto iter = m_nodes.find(module);
    if (iter != m_nodes.cend()) return iter->second.get();

    // construct the new nodule instance now
    auto* node = m_nodes.emplace(module, $::New().unique<Nodule>(module)).first->second.get();

    // update the nodules parent details now
    if (parent != nullptr) node->parents.emplace_back(parent), parent->children.emplace_back(node);

    // attempt scanning across the available depedencies
    for (const auto& dependency : m_import(module)) m_link(dependency, node);

    // resolve whether or not the node should be a root
    node->parents.size() ? $_PP_IGNORE(m_roots.erase(node)) : $_PP_IGNORE(m_roots.emplace(node));

    // and return the resulting nodule instance as needed
    return node;
}

std::future<Forge::Module::Interface*> Forge::Import::Graph::m_import(const $::URI::View& resource) const {
    static constexpr auto s_launch = $_PP_NDEBUG ? std::launch::async : std::launch::deferred;
    return std::async(s_launch, [&, resource] -> Module::Interface* { return m_modules->fetch(resource); });
}

std::vector<Forge::Module::Interface*> Forge::Import::Graph::m_import(const Dependencies& resources) const {
    // stop early if there are no resources given
    if (resources.empty()) return {};

    // prepare some output containers to be used now
    auto dependencies = std::vector<Module::Interface*>();
    auto futures = std::vector<std::future<Module::Interface*>>();

    // pre-fill our capacities now
    dependencies.reserve(resources.size()), futures.reserve(resources.size());

    // bind all the futures and request them now
    for (const auto& resource : resources) futures.emplace_back(m_import(resource));
    for (auto& future : futures) dependencies.emplace_back(future.get());

    // return all found dependencies now
    return dependencies;
}

std::vector<Forge::Module::Interface*> Forge::Import::Graph::m_import(Forge::Module::Interface* parent) const {
    auto resources = Dependencies();
    auto hint = parent->resource().body();
    auto dependencies = parent->dependencies();

    // pre-fill the resources sizing as well
    resources.reserve(dependencies.size());

    // attempt iterating over the available module resources
    for (const auto& path : dependencies) {
        auto resource = m_modules->resolve(path, hint);
        if (resource) resources.emplace_back(*resource);
    }

    // and return the final result of dependencies
    return m_import(resources);
}
