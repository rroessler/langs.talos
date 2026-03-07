#ifndef _TALOS_TESTING_REGISTRY_HPP
#define _TALOS_TESTING_REGISTRY_HPP

/// Talos Modules
#include "talos/function/dynamic.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/testing/traits.hpp"

namespace Talos::Testing {

    /// @brief Testing Registry.
    class Registry : public XI::Define<Registry, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Available testing mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Current registry target.
        Group* m_target = nullptr;

        /// @brief Available testing suite sections.
        $::Dict<Group*> m_sections = {};

        /// @brief Available tests storage.
        std::vector<Handle> m_storage = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Default registry constructor.
        explicit Registry() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the avialable testing sections.
        inline const $::Dict<Group*>& sections() const noexcept { return m_sections; }

        /// @brief Gets and sets the current group-target.
        inline constexpr Group* target() const noexcept { return m_target; }
        inline auto target(Group* group) {
            return m_target = group, $::Functor::Defer([&] { m_target = nullptr; });
        }

        /**
         * @brief Handles constructing a test-suite.
         * @param resource                  Section resource.
         */
        inline Group* suite(const $::URI::View& resource) { return suite(resource.relative()); }
        inline Group* suite(const $::String::Buffer& title) {
            if (m_sections.contains(title)) return m_sections.at(title);  // found
            auto* section = m_build($::New().unique<Group>(title, XT::Location()));
            return m_sections.emplace(title, section).first->second;  // and emplace
        }

        /**
         * @brief Handles constructing a test-group.
         * @param title                     Title of group.
         * @param location                  Source location.
         */
        inline Group* group(const $::String::Buffer& title, const XT::Location& location = $::Location()) {
            auto* group = m_build($::New().unique<Group>(title, location));
            return m_resolve(location)->emplace(group), group;  // emplace
        }

        /**
         * @brief Hanldes constructing a test-case.
         * @param title                     Title of case.
         * @param callback                  Handle callback.
         * @param location                  Source location.
         */
        inline Case* test(
            const $::String::Buffer& title, Callback&& callback, const XT::Location& location = $::Location()) {
            auto* test = m_with<Case>(title, std::move(callback), location);
            return m_resolve(location)->emplace(test), test;  // emplace
        }

        /**
         * @brief Constructs a test-case.
         * @param title                 Test title.
         * @param callback              Test callback.
         * @param location              Source location.
         */
        inline Bench* bench(
            const $::String::Buffer& title, Callback&& callback, const XT::Location& location = $::Location()) {
            auto* bench = m_with<Bench>(title, std::move(callback), location);
            return m_resolve(location)->emplace(bench), bench;  // emplace
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles emplacing storage values.
         * @param test                  Test to bind.
         */
        template <std::derived_from<XT::Handle> T>
        inline T* m_build($::Ptr::Unique<T>&& test) {
            auto* reference = test.get();  // prepare reference here
            return m_storage.emplace_back(std::move(test)), reference;
        }

        /**
         * @brief Constructs a test-case.
         * @param title                 Test title.
         * @param callback              Test callback.
         * @param location              Source location.
         */
        template <XT::Traits::Callable T>
        inline T* m_with(const $::String::Buffer& title, Callback&& callback, const XT::Location& location) {
            return m_build($::New().unique<T>(title, location, std::move(callback)));
        }

        /**
         * @brief Handles resolving the underlying target.
         * @param key                   Target key.
         */
        inline Group* m_resolve(const XT::Location& location) { return m_resolve(location.resource()); }
        inline Group* m_resolve(const $::URI::View& resource) { return m_target ? m_target : suite(resource); }
    };

}  // namespace Talos::Testing

#endif
