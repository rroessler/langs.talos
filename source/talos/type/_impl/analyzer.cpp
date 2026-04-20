/// Talos Modules
#include "talos/relint/analyzer.hpp"
#include "talos/builtins/service.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/container.hpp"

/// Type Modules
#include "talos/type/_inline/type.ipp"

//  PROPERTIES  //

/// @brief Failure context to be used.
static auto g_failure = Talos::Type::Context(Talos::Type::Builder::fail());

//  CONSTRUCTORS  //

Talos::Type::Analyzer::Analyzer() : Analyzer($::Global::get<Runtime::Container>()) {}
Talos::Type::Analyzer::Analyzer(XI::Container* services) : m_services(services) {
    m_world = m_globals = m_services->get<Builtins::Service>()->types();
}

//  PUBLIC METHODS  //

$::Ptr::Unique<Talos::Type::Scope> Talos::Type::Analyzer::scope(const Syntax::Constructor* constructor,
    const $::Ptr::Shared<Callable>& callable, const $::Ptr::Shared<Generic>& generic) noexcept {
    // scope a new world to be used now
    auto world = scope();
    auto& captures = m_context->captures();

    auto parameters = callable->parameters();  // get the base details now
    auto spread = callable->packed() ? Type::Builder::list(parameters.back().value()) : nullptr;

    // pre-define any generic type parameters now
    for (const auto& constraint : generic ? generic->parameters() : Template()) {
        auto entity = world->types().declare(constraint->name(), constraint);
        if (entity == nullptr) report(4000400, constraint->name());  // dupe
    }

    // resolve all the necessary arguments now
    for (const auto& [ii, parameter] : $::Each(constructor->parameters()->list())) {
        // attempt getting the current details to be used
        auto optional = parameter->optional();
        auto packed = parameter == constructor->spread();

        // prepare the incoming type to be used now
        auto type = packed ? spread : parameters.at(ii).value();

        // stop on invalid parameter types
        if (type == nullptr) break;

        // if we are in spread-mode, then change to an array
        if (optional) type = Builder::maybe(type);

        // and attempt declaring the incoming entity now
        auto* entity = world->values().declare(parameter, type, captures);
        if (entity == nullptr) report(parameter, 4000401, parameter->name());
    }

    // return the current scoping
    return world;
}

$::Ptr::Unique<Talos::Type::Context> Talos::Type::Analyzer::audit(
    const Syntax::Tree* tree, Diagnostic::Reporter* reporter) {
    auto failed = reporter && reporter->failed();  // pre-validate
    if (failed) return $::New().unique<Type::Context>(Builder::fail());

    // attempt running our auditing now as needed
    m_world->m_deferred.clear(), m_reporter = reporter;
    m_context = $::New().unique<Type::Context>();
    check(tree), m_reporter = nullptr;  // check

    // attempt building all the linting details if necessary
    if (m_services->get<Runtime::Options>()->flags.lint) {
        auto linter = m_services->get<Relint::Analyzer>();
        m_context->mirrors() = linter->audit(tree, reporter);
    }

    // and finally return the resulting now
    return std::move(m_context);
}

Talos::Type::Deduction Talos::Type::Analyzer::check(const Syntax::Node* node) { return check(node, Builder::unset()); }
Talos::Type::Deduction Talos::Type::Analyzer::check(const Syntax::Node* node, const Erased& fallback) {
    // stop early if the underlying node is invalid
    if ($_UNLIKELY(node == nullptr)) return fallback;

    // and resolve the final deduction to be used
    auto deduction = Visitor::visit(node, this);

    // update the current typing now
    node->traits()->type() = deduction.type;

    // and return the resulting deduction
    return deduction;
}

Talos::Type::Deduction Talos::Type::Analyzer::check(const std::vector<Syntax::Node*>& nodes) {
    Flow::Degree degree = -1, minimum = depth();  // get the current degree details
    auto propagate = [minimum](Flow::Degree _) { return _ > -1 && _ <= minimum; };

    // attempt checking all the incoming statements now
    for (const auto& node : nodes) {
        if (propagate(degree)) redundant(node), check(node);
        else degree = check(node).flow->degree();  // update
    }

    // ensure that the instance is passable or not
    return propagate(degree) ? unreachable(degree) : passable();
}

std::vector<$::Ptr::Shared<Talos::Type::Parameter>> Talos::Type::Analyzer::check(const Syntax::Template& parameters) {
    static constexpr auto cast = [](Erased&& node) { return std::static_pointer_cast<Parameter>(node); };
    auto predicate = [&](const Syntax::Placeholder* parameter) { return cast(check(parameter).type); };
    return $::Ranges::To(parameters | std::views::transform(predicate));  // can safely transform here
}

Talos::Type::Deduction Talos::Type::Analyzer::preamble(const Syntax::Preamble* preamble, Entity* entity) {
    // set the entity as the preamble target
    m_world->m_preamble = entity;

    // iterate over the available attributes and decorators
    for (const auto* attribute : preamble->attributes()) check(attribute);
    for (const auto* decorator : preamble->decorators()) check(decorator);

    // unset the current preamble target now
    m_world->m_preamble = nullptr;

    // and return the resulting type deduction
    return passable(entity->value());
}

Talos::Type::Erased Talos::Type::Analyzer::instantiate(const Erased& type, const Syntax::Specialization& arguments) {
    // we need to resolve a suitable generic target
    auto target = type->is<Transform>() ? type->as<Transform>()->reduce() : type;

    // ensure the type is actually generic before continuing with instantiating
    if (!target->is<Generic>()) return arguments.empty() ? target : report(3000350, *target).type;

    // cast to the generic we want to instantiate
    auto generic = target->as<Generic>();

    // pre-check the arity and adicity of the generic
    auto total = arguments.size();
    auto arity = generic->arity();
    auto adicity = generic->adicity();

    // ensure the totals are suitably valid before continuing
    if (total < arity) return report(3000401, arity).type;
    else if (total > adicity) return report(3000402, adicity).type;

    // and attempt mapping the types into the desired format
    auto predicate = [&](const Syntax::Annotation* argument) { return check(argument).type; };
    return generic->instantiate($::Ranges::To(arguments | std::views::transform(predicate)));
}

Talos::Type::Deduction Talos::Type::Analyzer::branch(Deduction&& deduction, Branch&& left, Branch&& right) {
    // execute our seperate branches now
    auto lf = m_using(std::move(left)), rf = m_using(std::move(right));

    // stop our deductions if the given one never succeeded
    if (deduction.flow->unreachable()) return std::move(deduction);

    // finally construct our resulting deduction to be used
    return Deduction(Builder::any(), m_merge(std::move(lf), std::move(rf)));
}

const Talos::Type::Context* Talos::Type::Analyzer::import(
    const $::String::View& path, const Resource::Location& location) {
    Import::Service* modules = *m_services;  // resolve now
    auto result = modules->resolve(path, resource().body());
    if (result.has_value()) return import(*result, location);
    return report(location, 8000000, result.error()), &g_failure;
}

const Talos::Type::Context* Talos::Type::Analyzer::import(const $::URI::View& resource, const Resource::Location&) {
    // prepare the importer service to be used
    Import::Service* modules = *m_services;

    // ignore if we could not validly fetch our module
    auto* found = modules->fetch(resource);
    if (found == nullptr) return &g_failure;

    // should be able to analyze the module now
    found->analyze(m_services);

    // and return the underlying type-context
    return found->metadata<Module::Phase::TYPED>()->context().get();
}

Talos::Type::Deduction Talos::Type::Analyzer::passable() const { return { Builder::none() }; }
Talos::Type::Deduction Talos::Type::Analyzer::passable(const Erased& type) const { return type; }

Talos::Type::Deduction Talos::Type::Analyzer::unreachable(Flow::Effect effect) const {
    return unreachable(depth(), effect);
}

Talos::Type::Deduction Talos::Type::Analyzer::unreachable(Flow::Degree degree, Flow::Effect effect) const {
    return Deduction(Builder::never(), $::New().unique<Flow::Unreachable>(degree, effect));
}

Talos::Type::Deduction Talos::Type::Analyzer::redundant(const Syntax::Node* node) {
    return report(node->traits()->bounds(), 4000900);
}

void Talos::Type::Analyzer::deprecated(const Entity* entity, const Syntax::Node*) {
    if (auto message = entity->deprecated()) report(9000100, *message);
}

void Talos::Type::Analyzer::mark(const Syntax::Identifier* identifier, Entity* entity, Depth depth) {
    // mark the entity as unused
    entity->unused(false);

    // check if the entity is deprecated at all
    deprecated(entity, identifier);

    // resolve the available captures
    auto& captures = m_context->captures();

    if (depth < 0) captures.global(identifier);  // expecting a global value
    else if (depth >= m_world->outer()) captures.mark(identifier, entity->context());
    else captures.leak(identifier, entity->context());  // otherwise a leaked upvalue
}

Talos::Type::Erased Talos::Type::Analyzer::declare(const Syntax::Variable* variable) {
    // prepare the expected type based on the given annotation
    auto expected = check(variable->hint()).type;

    // prepare the initializer type based on what we have currently
    auto initializer = check(variable->initializer()).type;

    if (expected->is<Unset>()) expected = initializer;
    if (expected->is<Unset>()) expected = Builder::any();

    // attempt unifying the value now if the expected value is not "any"
    while (!expected->is<Any>() && variable->initializer()) {
        if (variable->optional() && initializer->is<None>()) break;
        else if (expected->unify(initializer)) break;  // valid typing
        return report(variable, 3000300, *initializer, *expected).type;
    }

    // modify the expecting typing based on the optionality
    if (variable->optional()) expected = Builder::maybe(expected);

    // return the resulting type reference now
    return expected;
}

//  PRIVATE METHODS  //

$::Ptr::Unique<Talos::Flow::Control> Talos::Type::Analyzer::m_using(Branch&& branch) {
    auto* previous = m_world;
    auto current = World(*previous);
    m_world = &current;  // alias now

    // attempt running our branch now
    auto flow = branch(this);

    // update the current branch
    m_world = previous;

    // and return the final flow
    return flow;
}

$::Ptr::Unique<Talos::Flow::Control> Talos::Type::Analyzer::m_merge(
    $::Ptr::Unique<Flow::Control>&& left, $::Ptr::Unique<Flow::Control>&& right) const noexcept {
    // get the current degree values to be used
    auto ld = left->degree(), rd = right->degree();
    auto lu = left->unreachable(), ru = right->unreachable();

    // if both are unreachable, then fail
    if (lu && ru) return std::max(ld, rd) == rd ? std::move(left) : std::move(right);

    // otherwise declare as suitably passable now
    return $::New().unique<Flow::Passable>();
}
