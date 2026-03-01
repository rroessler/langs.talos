#ifndef _XINV_CORE_UTILITIES_HPP
#define _XINV_CORE_UTILITIES_HPP

/// XINV Includes
#include "xinv/core/shared.hpp"
#include "xinv/core/traits.hpp"
#include "xinv/core/unique.hpp"

namespace XI {

    /// @brief Immediate Instantiation Tag.
    class $_ABSTRACT Immediate {};

    /// @brief Service Abstraction Definition.
    template <class T, Traits::Abstract B, class... As>
    class $_ABSTRACT Define : public B, public As... {
        //  TYPEDEFS  //

        /// @brief Allow transient access.
        template <std::derived_from<Service> U>
        friend struct Traits::Transient;

        /// @brief Denotes the current base.
        using Base = T;

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using As::As...;

        /// @brief Virtual abstract destructor.
        virtual ~Define() = default;
    };

    /// @brief Mocked Service Abstraction.
    template <std::derived_from<Unique> T>
    struct $_ABSTRACT Mocks : public T {
        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Mocks() = default;
    };

    /// @brief Implements Service Abstraction.
    template <std::derived_from<Shared> T>
    struct $_ABSTRACT Implements : public T {
        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Implements() = default;
    };

}  // namespace XI

#endif
