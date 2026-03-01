#ifndef _FORGE_TYPE_WORLD_HPP
#define _FORGE_TYPE_WORLD_HPP

/// Forge Modules
#include "forge/forward/syntax.hpp"
#include "forge/type/entity.hpp"
#include "xtdlib/utility/never.hpp"

namespace Forge::Type {

    /// @brief World Depth Typing.
    using Depth = int32_t;

    /// @brief Type World Container.
    class World {
        //  TYPEDEFS  //

        /// @brief Allow scope internal access.
        friend class Scope;

        /// @brief Allow the analyzer internal access.
        friend class Analyzer;

        /// @brief Encapsulates property access.
        template <class T, auto G, auto S>
        class Property {
            //  PROPERTIES  //

            /// @brief Parent world instance.
            World* m_world;

           public:
            //  CONSTRUCTORS  //

            /// @brief Handle constructing properties.
            constexpr Property() = delete;
            constexpr Property(World* world) : m_world(world) {}

            //  PUBLIC METHODS  //

            /// @brief Conversion operator to underlying typing.
            inline constexpr operator T() const noexcept { return G(m_world); }

            /// @brief Assignment operator for the value.
            template <std::convertible_to<T> U>
            inline constexpr Property& operator=(const U& value) {
                return S(m_world, value), *this;
            }
        };

        /// @brief Allows viewing type-slices.
        template <auto E, auto A>
        class View {
            //  PROPERTIES  //

            /// @brief Encapsulated world instance.
            World* m_world;

           public:
            //  CONSTRUCTORS  //

            /// @brief Handles constructing views.
            constexpr View() = delete;
            constexpr View(World* world) : m_world(world) {}

            //  PUBLIC METHODS  //

            /**
             * @brief Checks if a world contains an entity.
             * @param name                  Entity name.
             * @param local                 Locality check.
             */
            inline bool contains(const $::String::View& name, bool local = true) const {
                auto iter = m_world->m_entities.find(name);
                if (iter != m_world->m_entities.cend()) return E(iter->second);
                if (local || !m_world->m_parent) return false;
                return View(m_world->m_parent).contains(name, local);
            }

            /**
             * @brief Handles declaring entity instances.
             * @param name                  Name to bind.
             * @param type                  Type to bind.
             * @param args                  Entity arguments.
             */
            template <class... As>
            inline Entity* declare(const $::String::View& name, const Erased& type, As&&... args) {
                auto& entity = m_declare(name, std::forward<As>(args)...);
                return E(entity) ? nullptr : (A(entity, type), &entity);
            }

            /**
             * @brief Handles declaring entity instances.
             * @param declaration           Variable declaration.
             * @param type                  Associated type to bind.
             * @param captures              Context captures.
             */
            template <std::derived_from<Syntax::Declaration> T>
            inline Entity* declare(const T* declaration, const Erased& type, Variable::Captures& captures) {
                auto* entity = declare(declaration->name(), type, declaration->traits()->location());
                if ($_UNLIKELY(entity == nullptr)) return nullptr;  // failed to declare an entity

                // update the entity details now
                entity->modifiers() = declaration->modifiers();
                entity->context() = captures.declare(declaration);

                // update the used state if necessary to do so
                if (entity->exported()) entity->unused(false);

                // return the resulting entity value now
                return entity;
            }

           private:
            //  PRIVATE METHODS  //

            /**
             * @brief Handles declaring an entity instance.
             * @param name                  Entity name.
             * @param location              Location to bind.
             */
            inline Entity& m_declare(const $::String::View& name, const Resource::Location& location = {}) {
                auto& entity = m_world->m_entities.try_emplace(name).first->second;
                return m_world->m_locations.try_emplace(name, location), entity;
            }
        };

        /// @brief All available getters.
        struct Getter : public $::Never {
            //  PROPERTIES  //

            /// @brief Sets a depth property.
            template <Depth World::* D>
            static constexpr auto extent = [](this const auto& self, const auto* world) -> Depth {
                if (world == nullptr) return -1;
                if ((*world).*D > -1) return (*world).*D;
                $_MUSTTAIL return self(world->m_parent);
            };

            /// @brief Callee getter.
            static constexpr auto callee = [](this const auto& self, const auto* world) -> Erased {
                if (world == nullptr) return nullptr;
                if (world->m_callee) return world->m_callee;
                return self(world->m_parent);  // get now
            };
        };

        /// @brief All available setters.
        struct Setter : public $::Never {
            //  PROPERTIES  //

            /// @brief Sets a depth property.
            template <Depth World::* D>
            static constexpr auto extent = [](auto* world, const Depth& value) { (*world).*D = value; };

            /// @brief Callee setter.
            static constexpr auto callee = [](auto* world, const Erased& value) {
                world->m_callee = value;  // update the current callee
                world->m_loops = -1, world->m_outer = world->m_depth;
            };
        };

        /// @brief Lookup Entry Typing.
        using Entry = std::pair<Entity*, Depth>;

        /// @brief Callee Property Typing.
        using Callee = Property<Erased, Getter::callee, Setter::callee>;

        /// @brief Depth Property Typing.
        template <Depth World::* D>
        using Extent = Property<Depth, Getter::extent<D>, Setter::extent<D>>;

        //  PROPERTIES  //

        Depth m_depth = -1;  // Current depth value.
        Depth m_outer = -1;  // Maximum depth value.
        Depth m_loops = -1;  // Current loop depth.

        // Explicit function value.
        Erased m_callee = {};

        /// @brief Attached world parent.
        World* m_parent = nullptr;

        /// @brief Encapsulated entities.
        $::Record<Entity> m_entities = {};

        /// @brief Currently deferred values.
        std::vector<Deferrer> m_deferred = {};

        /// @brief Associated resource locations.
        $::Record<Resource::Location> m_locations = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a global world instance.
        explicit World() = default;

        /**
         * @brief Constructs a world instance.
         * @param parent                Parent world.
         */
        explicit World(World* parent) : m_depth(($_ASSERT(parent), parent->m_depth + 1)), m_parent(parent) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the current world depth.
        inline constexpr Depth depth() const noexcept { return m_depth; }

        /// @brief Gets the import/export state.
        inline constexpr bool importable() const noexcept { return m_depth < 1; }
        inline constexpr bool exportable() const noexcept { return m_callee == nullptr; }

        /// @brief Gets the underlying entities map.
        inline constexpr $::Record<Entity>& entities() noexcept { return m_entities; }
        inline constexpr const $::Record<Entity>& entities() const noexcept { return m_entities; }

        /// @brief Gets/sets the current callee value.
        inline constexpr Callee callee() noexcept { return Callee(this); }
        inline constexpr Erased callee() const noexcept { return Getter::callee(this); }

        /// @brief Gets/sets the current looping depth.
        inline constexpr auto loops() noexcept { return Extent<&World::m_loops>(this); }
        inline constexpr Depth loops() const noexcept { return Getter::extent<&World::m_loops>(this); }

        /// @brief Gets/sets the current outer depth.
        inline constexpr auto outer() noexcept { return Extent<&World::m_outer>(this); }
        inline constexpr Depth outer() const noexcept { return Getter::extent<&World::m_outer>(this); }

        /// @brief Gets the world-of-types view.
        inline constexpr auto types() {
            static constexpr auto s_exists = [](const Entity& entity) { return entity.transient(); };
            static constexpr auto s_assign = [](Entity& entity, const Erased& type) { entity.type() = type; };
            return View<s_exists, s_assign>(this);  // construct the outgoing view to be used now
        }

        /// @brief Gets the world-of-values view.
        inline constexpr auto values() {
            static constexpr auto s_exists = [](const Entity& entity) { return entity.opaque(); };
            static constexpr auto s_assign = [](Entity& entity, const Erased& type) { entity.value() = type; };
            return View<s_exists, s_assign>(this);  // construct the outgoing view to be used now
        }

        /**
         * @brief Handles declaring a raw entity.
         * @param name                          Name of entity.
         * @param entity                        Entity to bind.
         * @param location                      Location value.
         */
        inline constexpr bool declare(const $::String::View& name, Entity entity) { return declare(name, entity, {}); }
        inline constexpr bool declare(const $::String::View& name, Entity entity, const Resource::Location& location) {
            if (!m_entities.try_emplace(name, entity).second) return false;
            return m_locations.try_emplace(name, location), true;  // valid
        }

        /**
         * @brief Handles looking up internal values.
         * @param name                          Name of entry.
         */
        inline constexpr Entry lookup(const $::String::View& name) const {
            auto iter = m_entities.find(name);  // scan here first before continuing
            if (iter != m_entities.cend()) return { const_cast<Entity*>(&iter->second), m_depth };
            return m_parent ? m_parent->lookup(name) : Entry(nullptr, -1);  // failed to find value
        }
    };

    /// @brief Scoped World Container.
    class Scope : public World {
        //  PROPERTIES  //

        /// @brief Bound analyzer instance.
        Analyzer* m_analyzer;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a scoped world instance.
        explicit Scope() = delete;
        explicit Scope(Analyzer* analyzer);

        /// @brief Handles removing the scoping.
        ~Scope();
    };

}  // namespace Forge::Type

#endif
