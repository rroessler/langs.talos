/// Forge Modules
#include "forge/relint/analyzer.hpp"
#include "forge/builtins/service.hpp"
#include "forge/module/service.hpp"
#include "forge/runtime/container.hpp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

//  PROPERTIES  //

/// @brief Failure context to be used.
static auto g_failure = Forge::Type::Context(Forge::Type::Builder::fail());

//  CONSTRUCTORS  //

Forge::Type::Analyzer::Analyzer() : Analyzer($::Global::get<Runtime::Container>()) {}
Forge::Type::Analyzer::Analyzer(XI::Container* services) : m_services(services) {
    m_world = m_globals = m_services->get<Builtins::Service>()->types();
}

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Type::Context> Forge::Type::Analyzer::audit(
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

Forge::Type::Deduction Forge::Type::Analyzer::check(const Syntax::Node* node) { return check(node, Builder::unset()); }
Forge::Type::Deduction Forge::Type::Analyzer::check(const Syntax::Node* node, const Erased& fallback) {
    // stop early if the underlying node is invalid
    if ($_UNLIKELY(node == nullptr)) return fallback;

    // get the base typing we are working with
    auto& current = node->traits()->type();

    // and resolve the final deduction to be used
    auto deduction = Visitor::visit(node, this);
    return current = deduction.type, std::move(deduction);
}

Forge::Type::Deduction Forge::Type::Analyzer::check(const std::vector<Syntax::Node*>& nodes) {
    Flow::Degree degree = -1, minimum = depth();  // get the current degree details
    auto propagate = [minimum](Flow::Degree _) { return _ > -1 && _ <= minimum; };

    // attempt checking all the incoming statements now
    for (const auto& node : nodes) {
        if (propagate(degree)) redundant(node);
        else degree = check(node).flow->degree();
    }

    // ensure that the instance is passable or not
    return propagate(degree) ? unreachable(degree) : passable();
}

std::vector<$::Ptr::Shared<Forge::Type::Parameter>> Forge::Type::Analyzer::check(const Syntax::Template& parameters) {
    static constexpr auto cast = [](Erased&& node) { return std::static_pointer_cast<Parameter>(node); };
    auto predicate = [&](const Syntax::Placeholder* parameter) { return cast(check(parameter).type); };
    return $::Ranges::To(parameters | std::views::transform(predicate));  // can safely transform here
}

Forge::Type::Erased Forge::Type::Analyzer::instantiate(const Erased& type, const Syntax::Specialization& arguments) {
    // ensure the type is actually generic before continuing with instantiating
    if (!type->is<Generic>()) return arguments.empty() ? type : report(3000350, *type).type;

    // cast to the generic we want to instantiate
    auto generic = type->as<Generic>();

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

Forge::Type::Deduction Forge::Type::Analyzer::branch(Deduction&& deduction, Branch&& left, Branch&& right) {
    // execute our seperate branches now
    auto lf = m_using(std::move(left)), rf = m_using(std::move(right));

    // stop our deductions if the given one never succeeded
    if (deduction.flow->unreachable()) return std::move(deduction);

    // finally construct our resulting deduction to be used
    return Deduction(Builder::any(), m_merge(std::move(lf), std::move(rf)));
}

const Forge::Type::Context* Forge::Type::Analyzer::import(
    const $::String::View& path, const Resource::Location& location) {
    auto* modules = m_services->get<Import::Service>();
    auto result = modules->resolve(path, resource().body());
    if (result.has_value()) return import(*result, location);
    return report(location, 8000000, result.error()), &g_failure;
}

const Forge::Type::Context* Forge::Type::Analyzer::import(const $::URI::View& resource, const Resource::Location&) {
    // prepare the importer service to be used
    auto* importer = m_services->get<Import::Service>();

    // ignore if we could not validly fetch our module
    auto* module = importer->fetch(resource);
    if (module == nullptr) return &g_failure;

    // should be able to analyze the module now
    module->analyze(m_services);

    // and return the underlying type-context
    return module->metadata<Module::Phase::TYPED>()->context().get();
}

Forge::Type::Deduction Forge::Type::Analyzer::passable() const { return { Builder::none() }; }
Forge::Type::Deduction Forge::Type::Analyzer::passable(const Erased& type) const { return type; }

Forge::Type::Deduction Forge::Type::Analyzer::unreachable(Flow::Effect effect) const {
    return unreachable(depth(), effect);
}

Forge::Type::Deduction Forge::Type::Analyzer::unreachable(Flow::Degree degree, Flow::Effect effect) const {
    return Deduction(Builder::never(), $::New().unique<Flow::Unreachable>(degree, effect));
}

Forge::Type::Deduction Forge::Type::Analyzer::redundant(const Syntax::Node* node) {
    return report(node->traits()->bounds(), 4000900);
}

void Forge::Type::Analyzer::mark(const Syntax::Identifier* identifier, Entity* entity, Depth depth) const noexcept {
    entity->unused(false);  // mark unused
    auto& captures = m_context->captures();

    if (depth < 0) captures.global(identifier);  // expecting a global value
    else if (depth >= m_world->outer()) captures.mark(identifier, entity->context());
    else captures.leak(identifier, entity->context());  // otherwise a leaked upvalue
}

Forge::Type::Erased Forge::Type::Analyzer::declare(const Syntax::Variable* variable) {
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

$::Ptr::Unique<Forge::Flow::Control> Forge::Type::Analyzer::m_using(Branch&& branch) {
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

$::Ptr::Unique<Forge::Flow::Control> Forge::Type::Analyzer::m_merge(
    $::Ptr::Unique<Flow::Control>&& left, $::Ptr::Unique<Flow::Control>&& right) const noexcept {
    // get the current degree values to be used
    auto ld = left->degree(), rd = right->degree();
    auto lu = left->unreachable(), ru = right->unreachable();

    // if both are unreachable, then fail
    if (lu && ru) return std::max(ld, rd) == rd ? std::move(left) : std::move(right);

    // otherwise declare as suitably passable now
    return $::New().unique<Flow::Passable>();
}
