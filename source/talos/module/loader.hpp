#ifndef _TALOS_MODULE_LOADER_HPP
#define _TALOS_MODULE_LOADER_HPP

/// Talos Modules
#include "talos/module/interface.hpp"
#include "talos/resource/scheme.hpp"

namespace Talos::Import {

    /// @brief Abstract Module Loader.
    struct $_ABSTRACT Loader {
        //  TYPEDEFS  //

        /// @brief Exposes available loaders.
        template <std::derived_from<Module::Interface> T>
        struct Proxy;

        /// @brief Loader Abstraction CRTP.
        template <Resource::Scheme S, std::derived_from<Loader> B = Loader>
        requires Resource::Loadable<S> struct $_ABSTRACT Abstract : public B {
            //  CONSTRUCTORS  //

            /// @brief Inherit the base constructor.
            using B::B;

            /// @brief Virtual abstract destructor.
            virtual ~Abstract() = default;

            //  PUBLIC METHODS  //

            /// @brief Gets the scheme of a loader.
            inline constexpr $::String::View scheme() const noexcept final {
#define X(N, S, ...) \
    case Resource::Scheme::N: return S;
                switch (S) { TALOS_XX_RESOURCE_SCHEMES(X) default : $_ABORT("Unknown resource scheme"); }
#undef X
            }
        };

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Loader() = default;

        /// @brief Virtual abstract destructor.
        virtual ~Loader() = default;

        //  PUBLIC METHODS  //

        /// @brief The underlying loader scheme.
        virtual $::String::View scheme() const noexcept = 0;

        /**
         * @brief Handles fetching a module.
         * @param resource                  Resource to fetch.
         * @param services                  Services container.
         */
        virtual $::Ptr::Unique<Module::Interface> fetch(
            const $::URI::View& resource, XI::Container* services) const = 0;
    };

}  // namespace Talos::Import

#endif
