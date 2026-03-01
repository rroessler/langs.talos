#ifndef _XINV_CORE_CONTAINER_HPP
#define _XINV_CORE_CONTAINER_HPP

/// XINV Includes
#include "xinv/core/shared.hpp"
#include "xinv/core/traits.hpp"
#include "xinv/core/unique.hpp"
#include "xinv/core/utilities.hpp"

namespace XI {

    /// @brief Underlying service factory.
    template <std::derived_from<Service> T>
    using Factory = $::Functor::Unique<T*()>;

    /// @brief Services Container.
    class Container {
        //  PROPERTIES  //

        /// @brief Handles locks for service construction.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Bound shared services available.
        $::Map<$::RTTI::Tag, Factory<Shared>> m_services = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted container.
        explicit Container() = default;

        //  PUBLIC METHODS  //

        /// @brief Checks if a service exists.
        template <std::derived_from<Shared> T>
        inline constexpr bool exists() const noexcept {
            return m_services.contains($::RTTI::Hash<Traits::Infer<T>>());
        }

        /// @brief Attempts getting a service instance.
        template <std::derived_from<Shared> T>
        inline constexpr Traits::Infer<T>* get() {
            return static_cast<Traits::Infer<T>*>(m_services.at(m_resolve<T>(true))());
        }

        /// @brief Allows getting conditional services safely.
        template <std::derived_from<Shared> T>
        inline constexpr Traits::Infer<T>* when() {
            return exists<T>() ? get<T>() : nullptr;
        }

        /**
         * @brief Inplace constructs unique services.
         * @param args                          Arguments to bind.
         */
        template <std::derived_from<Unique> T, class... As>
        inline constexpr $::Ptr::Unique<T> get(As&&... args) {
            return m_reify<T>(std::forward<As>(args)...);
        }

        /**
         * @brief Handles binding and getting an immediate service.
         * @param args                          Arguments to bind.
         * @return Traits::Infer<T>*
         */
        template <std::derived_from<Shared> T, class... As>
        inline constexpr Traits::Infer<T>* emplace(As&&... args) {
            if (!exists<T>()) bind<T>(std::forward<As>(args)...);
            return get<T>();  // should be able to safely get now
        }

        /**
         * @brief Binds a factory for a shared service.
         * @param args                          Arguments to bind.
         */
        template <std::derived_from<Shared> T, class... As>
        inline void bind(As&&... args) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // ensure locked now
            auto factory = m_factory<T, Shared>(std::forward<As>(args)...);
            if constexpr (std::derived_from<T, Immediate>) factory();
            m_services.emplace(m_resolve<T>(false), std::move(factory));
        }

        /**
         * @brief Prepares a factory for unique services.
         * @param args                          Arguments to bind.
         */
        template <std::derived_from<Unique> T, class... As>
        inline Factory<T> bind(As&&... args) {
            return m_factory<T>(std::forward<As>(args)...);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets a validated hash-value.
        template <class T>
        inline constexpr $::RTTI::Tag m_resolve(bool exists) const {
            $_UNUSED static auto state = exists ? "not" : "already";
            $_UNUSED static constexpr auto name = $::RTTI::Name::of<T>();
            $_UNUSED static constexpr auto message = "XI::Container service {0} bound '{1}'";
            static constexpr auto hash = $::RTTI::Hash<Traits::Infer<T>>();  // hash the value
            return $_ASSERT(m_services.contains(hash) == exists, message, state, name), hash;
        }

        /**
         * @brief Handles instantiating a service.
         * @param args                          Service to build.
         */
        template <std::derived_from<Service> T, class... As>
        inline $::Ptr::Unique<T> m_reify(As&&... args) {
            if constexpr (Traits::Injectable<T, As...>) return $::New().unique<T>(this, std::forward<As>(args)...);
            else return $::New().unique<T>(std::forward<As>(args)...);  // should be non-injected if here
        }

        /**
         * @brief Handles binding a service factory.
         * @param args                          Service to build.
         */
        template <std::derived_from<Service> T, std::derived_from<Service> R = T, class... As>
        inline Factory<R> m_factory(As&&... args) {
            return [this, ... args = std::forward<As>(args)]() mutable {
                // prepare the base service instance here
                static auto s_service = m_reify<T>(std::forward<As>(args)...);

                // and return based on the incoming details
                if constexpr (std::same_as<T, R>) return s_service.get();
                else return static_cast<R*>(s_service.get());  // prepare
            };
        }
    };

}  // namespace XI

#endif
