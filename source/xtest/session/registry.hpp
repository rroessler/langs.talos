#ifndef _XTEST_SESSION_REGISTRY_HPP
#define _XTEST_SESSION_REGISTRY_HPP

/// XT Modules
#include "xtest/handle/traits.hpp"
#include "xtest/session/runner.hpp"

namespace XT::Session {

    /// @brief Global Registry Instance.
    class Registry : public $::Singleton<Registry> {
        //  PROPERTIES  //

        /// @brief The bound module sections.
        $::Dict<Group*> m_sections = {};

        /// @brief Available tests storage.
        std::vector<$::Ptr::Unique<Handle>> m_storage = {};

       protected:
        //  CONSTRUCTORS  //

        /// @brief Defaulted Constructor.
        explicit Registry() = default;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the size of the underlying units.
        static inline constexpr size_t count() { return s_instance()->m_sections.size(); }

        /// @brief Gets the underlying registered units.
        static inline const $::Dict<Group*>& sections() { return s_instance()->m_sections; }

        /**
         * @brief Constructs a test-section.
         * @param title                 Group title.
         * @param location              Source location.
         */
        static inline Group* describe(const $::String::Buffer& title, const Location& location = $::Location()) {
            auto* self = s_instance();  // get the base instance here to begin with
            auto label = title + " / " + location.filename();
            if (self->m_sections.contains(label)) return self->m_sections.at(label);
            return self->m_sections.emplace(label, group(label, location)).first->second;
        }

        /**
         * @brief Constructs a test-group.
         * @param title                 Group title.
         * @param location              Source location.
         */
        static inline Group* group(const $::String::Buffer& title, const Location& location = $::Location()) {
            return s_instance()->m_build($::New().unique<Group>(title, location));
        }

        /**
         * @brief Constructs a test-case.
         * @param title                 Test title.
         * @param callback              Test callback.
         * @param location              Source location.
         */
        static inline Case* test(
            const $::String::Buffer& title, Handle::Callback&& callback, const Location& location = $::Location()) {
            return s_instance()->m_with<Case>(title, std::move(callback), location);
        }

        /**
         * @brief Constructs a test-case.
         * @param title                 Test title.
         * @param callback              Test callback.
         * @param location              Source location.
         */
        static inline Bench* bench(
            const $::String::Buffer& title, Handle::Callback&& callback, const Location& location = $::Location()) {
            return s_instance()->m_with<Bench>(title, std::move(callback), location);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles emplacing storage values.
         * @tparam T                    Value type.
         * @param test                  Test to bind.
         */
        template <std::derived_from<Handle> T>
        inline T* m_build($::Ptr::Unique<T>&& test) {
            auto* reference = test.get();  // prepare reference first
            return m_storage.emplace_back(std::move(test)), reference;
        }

        /**
         * @brief Constructs a test-case.
         * @param title                 Test title.
         * @param callback              Test callback.
         * @param location              Source location.
         */
        template <Traits::Callable T>
        inline T* m_with(const $::String::Buffer& title, Handle::Callback&& callback, const Location& location) {
            return m_build($::New().unique<T>(title, location, std::move(callback)));
        }
    };

}  // namespace XT::Session

#endif
