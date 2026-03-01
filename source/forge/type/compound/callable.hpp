#ifndef _FORGE_TYPE_CALLABLE_HPP
#define _FORGE_TYPE_CALLABLE_HPP

/// Forge Modules
#include "forge/type/entity.hpp"

/// Type Modules
#include "forge/type/utility/intrinsics.hpp"

namespace Forge::Type {

    /// @brief Callable Function Typing.
    class Callable : public Abstract<Callable> {
        //  TYPEDEFS  //

        /// @brief Allow prototypes internal access.
        friend class Prototype;

        //  PROPERTIES  //

        /// @brief Attach parameter values.
        std::vector<Entity> m_parameters = {};

        /// @brief Expected return typing.
        Erased m_returns = $::New().shared<None>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted callable instance.
        explicit Callable() = default;

        /**
         * @brief Constructs a function hint.
         * @param returns               Return typing.
         */
        explicit Callable(const Erased& returns) : m_returns(returns) {}

        /**
         * @brief Constructs a function hint.
         * @param returns               Return typing.
         * @param parameters            Parameter types.
         */
        explicit Callable(const Erased& returns, const std::vector<Entity>& parameters) :
            m_parameters(parameters), m_returns(returns) {}

        /**
         * @brief Constructs a function hint.
         * @param returns               Return typing.
         * @param parameters            Parameter types.
         */
        explicit Callable(const Erased& returns, const std::vector<Erased>& parameters) : m_returns(returns) {
            static constexpr auto predicate = [](const Erased& type) { return Entity(type); };
            m_parameters = $::Ranges::To(parameters | std::views::transform(predicate));
        }

        //  PROPERTIES  //

        /// @brief Denotes if the instance is packed.
        virtual inline constexpr bool packed() const noexcept { return false; }

        inline constexpr std::vector<Entity>& parameters() noexcept { return m_parameters; }
        inline constexpr const std::vector<Entity>& parameters() const noexcept { return m_parameters; }

        inline constexpr Erased& returns() noexcept { return m_returns; }
        inline constexpr const Erased& returns() const noexcept { return m_returns; }

        inline constexpr Lattice lattice() const noexcept final { return Fact::FUN_ANY; }
        inline constexpr $::Ternary truthiness() const noexcept final { return true; }

        /// @brief Gets the minimum parameters available.
        inline constexpr size_t arity() const noexcept {
            for (const auto& [ii, entity] : $::Each(m_parameters)) {
                if (packed() && &entity == &m_parameters.back()) break;
                if (entity.optional()) return ii;  // check optionality
            }

            // return the resulting distance to be used now
            return m_parameters.size() - packed();
        }

        /// @brief Gets the maximum parameters available.
        inline constexpr size_t adicity() const noexcept { return packed() ? SIZE_MAX : m_parameters.size(); }

        /**
         * @brief Handles looking up callable fields.
         * @param field                 Field to lookup.
         */
        Entity lookup(const $::String::View& field) const final;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating "Function" shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return shape == Shape::Lookup<Function::Dynamic>();
        }

        /**
         * @brief Handles inferring a function.
         * @param constraints               Generic constraints.
         */
        Erased m_infer(const Constraints& constraints) const final;

        /**
         * @brief Handles running a unification pass.
         * @param candidate                 Candidate to unify.
         * @param constraints               Generic constraints.
         */
        bool m_unify(const Erased& candidate, const Constraints& constraints) const final;

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        void m_print($::Stream::Output& os) const final;
    };

    /// @brief Variadic Function Typing.
    struct Variadic : public Abstract<Variadic, Callable> {
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted variadic function.
        explicit Variadic() : Variadic($::New().shared<Any>()) {}
        explicit Variadic(const Erased& returns) : Variadic(returns, std::vector<Erased>({ $::New().shared<Any>() })) {}

        /**
         * @brief Constructs a variadic function.
         * @param returns                   Return typing.
         * @param parameters                Parameters to bind.
         */
        template <class... As>
        explicit Variadic(const Erased& returns, const std::vector<Erased>& parameters) :
            Abstract(returns, parameters) {}

        /**
         * @brief Constructs a variadic function.
         * @param returns                   Return typing.
         * @param parameters                Parameters to bind.
         */
        template <class... As>
        explicit Variadic(const Erased& returns, const std::vector<Entity>& parameters) :
            Abstract(returns, parameters) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if the instance is packed.
        inline constexpr bool packed() const noexcept final { return true; }
    };

}  // namespace Forge::Type

#endif
