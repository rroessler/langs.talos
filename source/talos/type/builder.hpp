#ifndef _TALOS_TYPE_BUILDER_HPP
#define _TALOS_TYPE_BUILDER_HPP

/// Talos Modules
#include "talos/builtins/proxy.hpp"
#include "talos/type/analyzer.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

/// Type Modules
#include "talos/type/compound/callable.hpp"
#include "talos/type/compound/instance.hpp"
#include "talos/type/compound/protocol.hpp"
#include "talos/type/compound/prototype.hpp"
#include "talos/type/resolver/asyncify.hpp"
#include "talos/type/resolver/awaited.hpp"
#include "talos/type/resolver/invoker.hpp"
#include "talos/type/resolver/iterable.hpp"
#include "talos/type/utility/generic.hpp"
#include "talos/type/utility/intrinsics.hpp"
#include "talos/type/utility/parameter.hpp"
#include "talos/type/utility/transform.hpp"
#include "talos/type/utility/union.hpp"

//  X-MACROS  //

#define TALOS_XX_TYPES_LIST(X) \
    X(Any, any)                \
    X(None, none)              \
    X(Maybe, maybe)            \
    X(Never, never)            \
    X(Unset, unset)            \
    X(Failure, fail)           \
                               \
    X(Parameter, constraint)   \
    X(Transform, transform)    \
                               \
    X(Callable, function)      \
    X(Variadic, variadic)      \
    X(Prototype, prototype)

//  NAMESPACES  //

namespace Talos::Type::Builder {

#define X(T, N, ...)                                            \
    template <typename... As>                                   \
    static inline constexpr $::Ptr::Shared<T> N(As&&... args) { \
        return $::New().shared<T>(std::forward<As>(args)...);   \
    }

    TALOS_XX_TYPES_LIST(X)
#undef X

    /// @brief Gets a symbol instance.
    static inline constexpr Erased symbol() { return Builtins::Proxy<Value::Symbol>::typing(); }

    /// @brief Gets a number instance.
    static inline constexpr Erased number() { return Builtins::Proxy<Number::Tagged>::typing(); }

    /// @brief Gets a string instance.
    static inline constexpr Erased string() { return Builtins::Proxy<String::Dynamic>::typing(); }

    /// @brief Gets a boolean instance.
    static inline constexpr Erased boolean() { return Builtins::Proxy<Value::Boolean>::typing(); }

    /// @brief Handles constructing generics.
    static inline constexpr Erased generic(const Erased& target, const Template& parameters = {}) {
        return parameters.empty() ? target : $::New().shared<Generic>(target, parameters);
    }

    /// @brief Gets a list instance.
    static inline constexpr Erased list() { return Builtins::Proxy<Iterable::List>::typing(); }
    static inline constexpr Erased list(const Erased& T) { return list()->as<Type::Generic>()->instantiate({ T }); }

    /// @brief Gets an exception typing.
    static inline constexpr Erased exception() { return Builtins::Proxy<Object::Exception>::typing(); }

    /// @brief Gets an iterator instance.
    static inline constexpr Erased iterator() { return Builtins::Proxy<Iterable::Iterator>::typing(); }
    static inline constexpr Erased iterator(const Erased& T) {
        return iterator()->as<Type::Generic>()->instantiate({ T });
    }

    /// @brief Gets a result instance.
    static inline constexpr Erased result() { return Builtins::Proxy<Monad::Result>::typing(); }
    static inline constexpr Erased result(const Erased& T, const Erased& E = any()) {
        return result()->as<Type::Generic>()->instantiate({ T, E });
    }

    /// @brief Gets a future instance.
    static inline constexpr Erased future() { return Builtins::Proxy<Async::Future>::typing(); }
    static inline constexpr Erased future(const Erased& T) { return future()->as<Type::Generic>()->instantiate({ T }); }

    /// @brief Gets an object instance.
    static inline constexpr Erased object() { return $::New().shared<Protocol>(any()); }
    static inline constexpr Erased record(const Erased& T) { return $::New().shared<Protocol>(T); }
    static inline constexpr Erased interface(const $::Record<Entity>& fields = {}) {
        return $::New().shared<Protocol>(fields);
    }

    /// @brief Gets a named interface.
    static inline constexpr Erased interface(const $::String::View& name, const $::Record<Entity>& fields = {}) {
        return $::New().shared<Protocol>(name, fields);
    }

    /// @brief Gets the base enumeration prototype.
    static inline constexpr $::Ptr::Shared<Prototype> enumeration() {
        return Builtins::Proxy<Object::Enum>::prototype();
    }

    /// @brief Creates a new enumeration instance.
    static inline constexpr Type::Erased enumeration(const $::String::View& name, Shape::Underlying shape) {
        auto prototype = $::New().shared<Prototype>(name, shape);
        return prototype->super() = enumeration(), prototype->instantiate();
    }

    /// @brief Resolves awaited typings.
    static inline constexpr Erased awaited(const Erased& target) { return transform(target, Utility::Awaited()); }
    static inline constexpr Erased asyncify(const Erased& target) { return transform(target, Utility::Asyncify()); }

    /// @brief Resolves iterable typings.
    static inline constexpr Erased iterable(const Erased& target) { return transform(target, Utility::Iterable()); }

    /// @brief Constructs an invocation transform.
    template <class... As>
    static inline constexpr Erased invocation(const Erased& target, As&&... args) {
        return transform(target, Utility::Invoker(std::forward<As>(args)...));
    }

    /**
     * @brief Allows the fast-construction of optional entities.
     * @param type                  Type to bind.
     */
    static inline constexpr Entity optional(const Erased& type) { return { type, Variable::Flag::OPTIONAL }; }

    /**
     * @brief Constructs a set of arguments.
     * @param types                 Types to bind.
     */
    template <class... As>
    static inline constexpr std::vector<Entity> arguments(As&&... types) {
        return { Entity(std::forward<As>(types))... };
    }

    /**
     * @brief Constructs a list of parameters.
     * @param items                 Parameters to bind.
     */
    template <class... As>
    static inline constexpr Template parameters(As&&... items) {
        return { std::forward<As>(items)... };
    }

    /**
     * @brief Handles merging types into a union.
     * @param left                  Left-most type.
     * @param right                 Right-most type.
     */
    static inline constexpr Erased merge(const Erased& left, const Erased& right) {
        // stop if the types are fundamentally equal
        if (left->unify(right)) return left;

        // stop if either are "Any" types
        if (left->is<Any>() || right->is<Any>()) return any();

        // prepare the left and right children now
        auto elements = left->is<Union>() ? left->as<Union>()->elements() : std::vector({ left });
        auto incoming = right->is<Union>() ? right->as<Union>()->elements() : std::vector({ right });

        // attempt emplacing all new types as necessary
        for (const auto& element : incoming) {
            auto predicate = [element](const Erased& other) { return other->unify(element); };
            if (std::ranges::none_of(elements, predicate)) elements.emplace_back(element);
        }

        // construct the result based on the size of the elements
        switch (elements.size()) {
            case 0: return never();         // resolve as empty now
            case 1: return elements.at(0);  // return base element
            default: return $::New().shared<Union>(elements);
        }
    }

    /**
     * @brief Handles coalescing nullish types.
     * @param left                  Maybe null typing.
     * @param right                 Coalescing typing.
     */
    static inline constexpr Erased coalesce(const Erased& left, const Erased& right) {
        // if left is explicitly nullish, then return right
        if (left->is<None>()) return right;

        // if left is not a union, then return left
        if (!left->is<Union>()) return left;

        // get the left-most elements now
        auto elements = left->as<Union>()->elements();

        // prepare the nullish handler now
        static constexpr auto nullish = [](const Erased& type) { return type->is<None>(); };

        // attempt finding the nullish elements
        auto iter = std::ranges::find_if(elements, nullish);
        if (iter == elements.end()) return left;  // missing

        // remove the nullish element now
        elements.erase(iter);

        // rebuild the left-most type now
        switch (elements.size()) {
            case 0: return right;
            case 1: return merge(elements.at(0), right);
            default: return merge($::New().shared<Union>(elements), right);
        }
    }

    /**
     * @brief Handles safe resolution of types.
     * @param type                  Type to resolve.
     */
    template <std::derived_from<Tagged> T>
    static inline constexpr $::Ptr::Shared<T> resolve(const Erased& type) {
        return type->is<T>() ? type->as<T>() : nullptr;
    }

    //  SPECIALIZATIONS  //

    template <>
    inline constexpr $::Ptr::Shared<Prototype> resolve(const Erased& type) {
        if (type->is<Instance>()) return type->as<Instance>()->prototype();
        if (type->is<Generic>()) return resolve<Prototype>(type->as<Generic>()->target());
        if (type->is<Transform>()) return resolve<Prototype>(type->as<Transform>()->reduce());
        return type->is<Prototype>() ? type->as<Prototype>() : nullptr;  // valid lookup here
    }

    template <>
    inline constexpr $::Ptr::Shared<Callable> resolve(const Erased& type) {
        // should be able to resolve simply here
        if (type->is<Generic>()) return resolve<Callable>(type->as<Generic>()->target());
        if (type->is<Transform>()) return resolve<Callable>(type->as<Transform>()->reduce());

        // otherwise attempt resolving prototype constructors
        if (type->is<Prototype>()) return resolve<Callable>(type->as<Prototype>()->callable());

        // finally should expect a valid constructor
        return type->is<Callable>() ? type->as<Callable>() : nullptr;
    }

}  // namespace Talos::Type::Builder

//  UNDEFINES  //

#undef MM_FACTORY_ALIAS

#endif
