#ifndef _FORGE_BUILTINS_TRAITS_HPP
#define _FORGE_BUILTINS_TRAITS_HPP

/// Forge Modules
#include "forge/builtins/adapter.hpp"
#include "forge/forward/type.hpp"
#include "forge/member/descriptor.hpp"
#include "forge/shape/lookup.hpp"

//  MACROS  //

#define FORGE_BUILTIN_TRAITS(N) Forge::Builtins::Traits<Forge::N>
#define FORGE_BUILTIN_CUSTOM(N) $_FWD(struct N, Forge::Builtins::Custom)

#define FORGE_BUILTIN_FIELDS(N) FORGE_BUILTIN_TRAITS(N)::Field
#define FORGE_BUILTIN_STATICS(N) FORGE_BUILTIN_TRAITS(N)::Static
#define FORGE_BUILTIN_OPERATORS(N) FORGE_BUILTIN_TRAITS(N)::Apply
#define FORGE_BUILTIN_STORAGE(N) Forge::Member::Storage FORGE_BUILTIN_TRAITS(N)::m_members

#define FORGE_MM_BUILTIN_FTYPE(T, N, ...) Forge::Type::Entity FORGE_BUILTIN_FIELDS(T)::N(__VA_ARGS__)
#define FORGE_MM_BUILTIN_STYPE(T, N, ...) Forge::Type::Entity FORGE_BUILTIN_STATICS(T)::N(__VA_ARGS__)
#define FORGE_MM_BUILTIN_OTYPE(T, N, ...) Forge::Type::Erased FORGE_BUILTIN_OPERATORS(T)::N(__VA_ARGS__)

#define FORGE_MM_BUILTIN_ODECL(N, L, R, ...)                                                          \
    FORGE_BUILTIN_OPERATORS(N) {                                                                      \
        static Type::Erased L(const Self* self, Operator::Kind kind);                                 \
        static Type::Erased R(const Self* self, Operator::Kind kind, const Type::Erased& type);       \
        static Type::Erased decide(const Self* self, Operator::Kind kind, const Type::Erased& type) { \
            return type == nullptr ? L(self, kind) : R(self, kind, type);                             \
        }                                                                                             \
    }

#define FORGE_MM_BUILTIN_FIELD(T, N, I, A, ...)   \
    Forge::Value::Any FORGE_BUILTIN_FIELDS(T)::N( \
        Runtime::Isolate* I, const Function::Arguments& A $_PP_VARGS(__VA_ARGS__))

#define FORGE_MM_BUILTIN_STATIC(T, N, I, A, ...)   \
    Forge::Value::Any FORGE_BUILTIN_STATICS(T)::N( \
        Runtime::Isolate* I, const Function::Arguments& A $_PP_VARGS(__VA_ARGS__))

#define FORGE_MM_BUILTIN_OPERATOR(T, N, I, ...) \
    Forge::Value::Any FORGE_BUILTIN_OPERATORS(T)::N(Runtime::Isolate* I $_PP_VARGS(__VA_ARGS__))

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Builtin Adapter Traits.
    template <class T>
    struct Traits;

    /// @brief Literal String Value.
    template <size_t N>
    using Name = $::String::Literal<N>;

    /// @brief Common Builtin Details.
    template <class T, Name N>
    struct $_ABSTRACT Define {
        //  PUBLIC METHODS  //

        /// @brief Gets the name of a builtin.
        static inline constexpr $::String::View name() { return N.view(); }

        /// @brief Gets the hash of a builtin.
        static inline constexpr $::RTTI::Tag hash() { return $::RTTI::Hash<T>(); }

        /// @brief Gets the shape of a builtin.
        static inline constexpr Shape::Underlying shape() { return Shape::Lookup<T>(); }

        /// @brief Allows access to available type-lookups.
        static inline constexpr $::Ptr::Shared<Type::Prototype> prototype() {
            static auto s_prototype = $::New().shared<Type::Prototype>(name(), Shape::Lookup<T>());
            return s_prototype;  // and resolve the incoming type now as necessary now
        }
    };

    /// @brief Available Builtin Features.
    template <Adapter... As>
    struct $_ABSTRACT Features {
        //  PUBLIC METHODS  //

        /// @brief Checks adapter enablement.
        template <Adapter A>
        static inline constexpr bool uses() {
            return ((A == As) || ...);
        }
    };

}  // namespace Forge::Builtins

#endif
