#ifndef _FORGE_TYPE_INVOKER_HPP
#define _FORGE_TYPE_INVOKER_HPP

/// Type Modules
#include "forge/type/compound/callable.hpp"
#include "forge/type/utility/transform.hpp"

namespace Forge::Type::Utility {

    /// @brief Invocation Type Resolver.
    class Invoker {
        //  PROPERTIES  //

        /// @brief Denotes if asynchronous.
        bool m_async = false;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a function invoker.
         * @param async                 Asynchronous flag.
         */
        explicit Invoker(bool async = false) : m_async(async) {}

        //  OPERATOR METHODS  //

        /**
         * @brief Handles instantiating the target.
         * @param target                Target to be instantiated.
         */
        Erased operator()(const Erased& target, const Constraints& constraints) const noexcept;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles binding function parameters.
         * @param target                Target to bind.
         */
        Erased m_bind(const Erased& target) const noexcept;

        /**
         * @brief Handles resolving return-values.
         * @param callable              Callable to resolve.
         */
        Erased m_returns(const $::Ptr::Shared<Callable>& callable) const noexcept;
    };

    /// @brief Ensure the resolution conversion is valid.
    static_assert(std::convertible_to<Invoker, Resolver>);

}  // namespace Forge::Type::Utility

#endif
