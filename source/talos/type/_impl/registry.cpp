/// Builtins Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

//  PROPERTIES  //

static Talos::Type::Erased g_any = $::Shared::New<Talos::Type::Any>();
static Talos::Type::Erased g_none = $::Shared::New<Talos::Type::None>();
static Talos::Type::Erased g_fail = $::Shared::New<Talos::Type::Poison>();
static Talos::Type::Erased g_unset = $::Shared::New<Talos::Type::Unset>();
static Talos::Type::Erased g_never = $::Shared::New<Talos::Type::Union>();

static auto g_object = $::Shared::New<Talos::Type::Structure>();
static auto g_exception = Talos::Builtins::Inspect<Talos::Object::Exception>::typeclass()->instantiate();

static Talos::Type::Erased g_number = Talos::Builtins::Inspect<Talos::Number::Tagged>::typeclass()->instantiate();
static Talos::Type::Erased g_string = Talos::Builtins::Inspect<Talos::String::Any>::typeclass()->instantiate();
static Talos::Type::Erased g_symbol = Talos::Builtins::Inspect<Talos::Value::Symbol>::typeclass()->instantiate();
static Talos::Type::Erased g_boolean = Talos::Builtins::Inspect<Talos::Value::Boolean>::typeclass()->instantiate();

//  PUBLIC METHODS  //

const Talos::Type::Erased &Talos::Type::New::any() { return g_any; }
const Talos::Type::Erased &Talos::Type::New::none() { return g_none; }
const Talos::Type::Erased &Talos::Type::New::fail() { return g_fail; }
const Talos::Type::Erased &Talos::Type::New::unset() { return g_unset; }
const Talos::Type::Erased &Talos::Type::New::never() { return g_never; }

const Talos::Type::Erased &Talos::Type::New::number() { return g_number; }
const Talos::Type::Erased &Talos::Type::New::string() { return g_string; }
const Talos::Type::Erased &Talos::Type::New::symbol() { return g_symbol; }
const Talos::Type::Erased &Talos::Type::New::boolean() { return g_boolean; }

const $::Shared::Pointer<Talos::Type::Structure> &Talos::Type::New::object() { return g_object; }
const $::Shared::Pointer<Talos::Type::Instance> &Talos::Type::New::exception() { return g_exception; }

$::Shared::Pointer<Talos::Type::Structure> Talos::Type::New::record(const Erased &value) {
  return $::Shared::New<Structure>(value);
}

$::Shared::Pointer<Talos::Type::Structure> Talos::Type::New::interface() { return interface($::Map::Record<Entity>()); }
$::Shared::Pointer<Talos::Type::Structure> Talos::Type::New::interface(const $::Map::Record<Entity> &fields) {
  return $::Shared::New<Structure>(fields);
}

$::Shared::Pointer<Talos::Type::Structure> Talos::Type::New::interface(const $::String::View &name) {
  return interface(name, {});
}

$::Shared::Pointer<Talos::Type::Structure>
Talos::Type::New::interface(const $::String::View &name, const $::Map::Record<Entity> &fields) {
  return $::Shared::New<Structure>(name, fields);
}

Talos::Type::Erased Talos::Type::New::list(const Erased &target) {
  return Builtins::Inspect<Iterable::List>::generic()->instantiate({target});
}

Talos::Type::Erased Talos::Type::New::future(const Erased &target) {
  return Builtins::Inspect<Async::Future>::generic()->instantiate({target});
}

Talos::Type::Erased Talos::Type::New::iterator(const Erased &target) {
  return Builtins::Inspect<Iterable::Iterator>::generic()->instantiate({target});
}

Talos::Type::Erased Talos::Type::New::result(const Erased &target, const Erased &error) {
  return Builtins::Inspect<Monad::Result>::generic()->instantiate({target, error});
}

Talos::Type::Erased Talos::Type::New::enumeration(const $::String::View &name, Shape::Underlying shape) {
  auto prototype = $::Shared::New<Prototype>(name, shape);
  static auto s_super = Builtins::Inspect<Object::Enum>::typeclass();
  return prototype->super() = s_super, prototype->instantiate();
}

Talos::Type::Entity Talos::Type::New::optional(const Erased &target) {
  return Entity(target, Variable::Flag::OPTIONAL);
}

Talos::Type::Erased Talos::Type::New::maybe(const Erased &target) {
  return target->is<None>() ? target : merge(none(), target);
}

$::Shared::Pointer<Talos::Type::Prototype>
Talos::Type::New::prototype(const $::String::View &name, Shape::Underlying shape) {
  return $::Shared::New<Prototype>(name, shape);
}

$::Shared::Pointer<Talos::Type::Parameter>
Talos::Type::New::constraint(const $::String::View &name, const Erased &extends, const Erased &fallback) {
  return $::Shared::New<Parameter>(name, extends, fallback);
}

$::Shared::Pointer<Talos::Type::Generic> Talos::Type::New::generic(const Erased &target, const Template &parameters) {
  return $::Shared::New<Generic>(target, parameters);
}

$::Shared::Pointer<Talos::Type::Generic>
Talos::Type::New::generic(const Erased &target, const $::Shared::Pointer<Parameter> &initial) {
  return generic(target, Template({initial}));
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::lazy(const Erased &target) {
  return $::Shared::New<Transform>(target);
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::transform(const Erased &target) { return lazy(target); }
$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::transform(const Erased &target, Resolver &&resolver) {
  return $::Shared::New<Transform>(target, std::move(resolver));
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::awaited(const Erased &target) {
  return transform(target, Utility::Awaited());
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::asyncify(const Erased &target) {
  return transform(target, Utility::Asyncify());
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::iterable(const Erased &target) {
  return transform(target, Utility::Loopable());
}

$::Shared::Pointer<Talos::Type::Transform> Talos::Type::New::invocation(const Erased &target, bool async) {
  return transform(target, Utility::Invoker(async));
}

$::Shared::Pointer<Talos::Type::Callable> Talos::Type::New::function(const Erased &returns) {
  return function(returns, std::vector<Entity>());
}

$::Shared::Pointer<Talos::Type::Callable> Talos::Type::New::function(const Erased &returns, const Entity &initial) {
  return function(returns, std::vector<Entity>({initial}));
}

$::Shared::Pointer<Talos::Type::Callable>
Talos::Type::New::function(const Erased &returns, const Entity &first, const Entity &second) {
  return function(returns, std::vector<Entity>({first, second}));
}

$::Shared::Pointer<Talos::Type::Callable>
Talos::Type::New::function(const Erased &returns, const std::vector<Entity> &parameters) {
  return $::Shared::New<Callable>(returns, parameters);
}

$::Shared::Pointer<Talos::Type::Callable> Talos::Type::New::variadic(const Erased &returns) {
  return $::Shared::New<Variadic>(returns);
}

$::Shared::Pointer<Talos::Type::Callable> Talos::Type::New::variadic(const Erased &returns, const Entity &initial) {
  return variadic(returns, std::vector<Entity>({initial}));
}

$::Shared::Pointer<Talos::Type::Callable>
Talos::Type::New::variadic(const Erased &returns, const Entity &first, const Entity &second) {
  return variadic(returns, std::vector<Entity>({first, second}));
}

$::Shared::Pointer<Talos::Type::Callable>
Talos::Type::New::variadic(const Erased &returns, const std::vector<Entity> &parameters) {
  return $::Shared::New<Variadic>(returns, parameters);
}

Talos::Type::Erased Talos::Type::New::merge(const Erased &left, const Erased &right) {
  // stop if the types are fundamentally equal
  if (left->unify(right)) return left;

  // stop if either are "Any" types
  if (left->is<Any>() || right->is<Any>()) return any();

  // prepare the left and right children now
  auto elements = left->is<Union>() ? left->as<Union>()->elements() : std::vector({left});
  auto incoming = right->is<Union>() ? right->as<Union>()->elements() : std::vector({right});

  // attempt emplacing all new types as necessary
  for (const auto &element : incoming) {
    auto predicate = [element](const Erased &other) { return other->unify(element); };
    if (std::ranges::none_of(elements, predicate)) elements.emplace_back(element);
  }

  // construct the result based on the size of the elements
  switch (elements.size()) {
  case 0: return never();        // resolve as empty now
  case 1: return elements.at(0); // return base element
  default: return $::Shared::New<Union>(elements);
  }
}

Talos::Type::Erased Talos::Type::New::coalesce(const Erased &left, const Erased &right) {
  // if left is explicitly nullish, then return right
  if (left->is<None>()) return right;

  // if left is not a union, then return left
  if (!left->is<Union>()) return left;

  // get the left-most elements now
  auto elements = left->as<Union>()->elements();

  // prepare the nullish handler now
  static constexpr auto nullish = [](const Erased &type) { return type->is<None>(); };

  // attempt finding the nullish elements
  auto iter = std::ranges::find_if(elements, nullish);
  if (iter == elements.end()) return left; // missing

  // remove the nullish element now
  elements.erase(iter);

  // rebuild the left-most type now
  switch (elements.size()) {
  case 0: return right;
  case 1: return merge(elements.at(0), right);
  default: return merge($::Shared::New<Union>(elements), right);
  }
}

template <>
$::Shared::Pointer<Talos::Type::Callable> Talos::Type::New::cast<Talos::Type::Callable>(const Erased &type, bool) {
  // should be able to resolve simply here
  if (type->is<Generic>()) return cast<Callable>(type->as<Generic>()->target());
  if (type->is<Transform>()) return cast<Callable>(type->as<Transform>()->reduce());

  // otherwise attempt resolving prototype constructors
  if (type->is<Prototype>()) return cast<Callable>(type->as<Prototype>()->callable());

  // finally should expect a valid callable instance
  return type->is<Callable>() ? type->as<Callable>() : nullptr;
}

template <>
$::Shared::Pointer<Talos::Type::Prototype>
Talos::Type::New::cast<Talos::Type::Prototype>(const Erased &type, bool strict) {
  // only check for instances when not in strict checking mode
  if (!strict && type->is<Instance>()) return type->as<Instance>()->prototype();

  // should be able to resolve simply here
  if (type->is<Generic>()) return cast<Prototype>(type->as<Generic>()->target(), strict);
  if (type->is<Transform>()) return cast<Prototype>(type->as<Transform>()->reduce(), strict);

  // finally attempt finding a valid prototype instance
  return type->is<Prototype>() ? type->as<Prototype>() : nullptr;
}
