#ifndef _TALOS_DYLIB_REGISTRY_HPP
#define _TALOS_DYLIB_REGISTRY_HPP

/// Talos Modules
#include "talos/dylib/proxy.hpp"
#include "talos/globals/roots.hpp"
#include "talos/lifecycle/service.hpp"

//  MACROS  //

/// @brief Allows unwrapping dynamic library exports.
#define TALOS_MM_DYLIB_UNWRAP(N, ...) \
    exports.fields().emplace(#N, Member::Factory::native(isolate, m_##N, m_name(), #N));

/// @brief Exposes a dynamic library addon.
#define TALOS_MM_DYLIB_ADDON(P, L, ...)                                   \
    static $_AUTO = Talos::Dylib::Registry::install<Talos::Package::P>(); \
    Talos::Package::P::P(Runtime::Isolate* isolate, Dylib::Exports& exports) { L(TALOS_MM_DYLIB_UNWRAP) }

/// @brief Exposes a dynamic library method.
#define TALOS_MM_DYLIB_METHOD(P, N, I, A, ...)  \
    Talos::Value::Any Talos::Package::P::m_##N( \
        Runtime::Isolate* I, const Function::Arguments& A $_PP_VARGS(__VA_ARGS__))

//  NAMESPACES  //

namespace Talos::Dylib {

    /// @brief Library Registry.
    class Registry : public $::Singleton<Registry> {
        //  PROPERTIES  //

        /// @brief Storage mutex value.
        mutable $::Mutex::Auto m_mutex;

        /// @brief All available dynamic libraries.
        $::Record<$::Ptr::Unique<Addon>> m_addons = {};

       protected:
        //  CONSTRUCTORS  //

        /// @brief Defaulted constructor.
        explicit Registry() = default;

       public:
        //  PUBLIC METHODS  //

        /**
         * @brief Denotes if a library has been bound.
         * @param name                      Name of library.
         */
        static inline constexpr bool bound(const $::String::View& name) {
            return s_instance()->m_addons.contains(name);
        }

        /**
         * @brief Allows iterating over the addon roots.
         * @param yield                     Globals cache.
         */
        static inline constexpr void each(const Globals::Each& yield) noexcept {
            for (const auto& addon : s_instance()->m_addons | std::views::values) yield(addon->exports());
        }

        /**
         * @brief Handles installing a dynamic library.
         * @param addon                     Library addon.
         */
        static Addon* install($::Ptr::Unique<Addon>&& addon);

        /// @brief Handles installing a dynamic package.
        template <class T>
        static inline Addon* install() {
            return install($::Convert::lowercase(T::m_name()), [](Runtime::Isolate* isolate, Exports& exports) {
                auto* package = $::New().with<T>(isolate, exports);  // create
                m_lifecycle(isolate)->subscribe([package] { delete package; });
            });
        }

        /**
         * @brief Handles installing a dynamic library.
         * @param name                      Name of library.
         * @param loader                    Loader to bind.
         */
        static inline Addon* install(const $::String::View& name, Loader&& loader) {
            return install($::New().unique<Addon>(name, std::move(loader)));
        }

        /**
         * @brief Handles loading dynamic libraries.
         * @param isolate                   Thread isolate.
         * @param name                      Library name.
         */
        static Value::Any preload(Runtime::Isolate* isolate, const $::String::View& name);

        /**
         * @brief Forces a dynamic library to be unloaded.
         * @param isolate                   Thread isolate.
         * @param name                      Library name.
         */
        static void unload(Runtime::Isolate* isolate, const $::String::View& name);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles getting the underlying lifecycle.
         * @param isolate                   Thread isolate.
         */
        static Lifecycle::Service* m_lifecycle(Runtime::Isolate* isolate);
    };

}  // namespace Talos::Dylib

#endif
