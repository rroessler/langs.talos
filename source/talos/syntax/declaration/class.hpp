#ifndef _TALOS_DECLARATION_CLASS_HPP
#define _TALOS_DECLARATION_CLASS_HPP

/// Syntax Modules
#include "talos/syntax/annotation/constructor.hpp"
#include "talos/syntax/declaration/preamble.hpp"
#include "talos/syntax/statement/block.hpp"

namespace Talos::Syntax {

    /// @brief Object fields typing.
    using Fields = std::vector<Declaration*>;

    /// @brief Class Syntax Node.
    class Class : public Abstract<Class, Preamble> {
        //  PROPERTIES  //

        /// @brief Containing fields block.
        Block* m_block = nullptr;

        /// @brief Associated constructor value.
        Constructor* m_constructor = nullptr;

        /// @brief Passthrough constructor arguments.
        Expression* m_extends = nullptr;

        /// @brief Allowed interface implementations.
        Specialization m_implements = {};

        /// @brief Attached property values.
        Fields m_fields = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a class node.
         * @param token                 Target name.
         * @param location              Resource location.
         */
        explicit Class(const Lexer::Token* token) : Abstract(token) {}
        explicit Class(const $::String::View& name, const Bounds& location = {}) : Abstract(name, location) {}

        /**
         * @brief Constructs a class node.
         * @param name                  Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param fields                Declaration fields.
         * @param location              Resource location.
         */
        explicit Class(const $::String::View& name, Constructor* constructor, Expression* extends, const Fields& fields,
            const Bounds& location = {}) :
            Abstract(name, location), m_constructor(constructor), m_extends(extends), m_fields(fields) {}

        /**
         * @brief Constructs a class node.
         * @param token                 Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param fields                Declaration fields.
         */
        explicit Class(const Lexer::Token* token, Constructor* constructor, Expression* extends, const Fields& fields) :
            Abstract(token), m_constructor(constructor), m_extends(extends), m_fields(fields) {}

        /**
         * @brief Constructs a class node.
         * @param name                  Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param implements            Implementation interfaces.
         * @param fields                Declaration fields.
         * @param location              Resource location.
         */
        explicit Class(const $::String::View& name, Constructor* constructor, Expression* extends,
            const Specialization& implements, const Fields& fields, const Bounds& location = {}) :
            Abstract(name, location),
            m_constructor(constructor),
            m_extends(extends),
            m_implements(implements),
            m_fields(fields) {}

        /**
         * @brief Constructs a class node.
         * @param token                 Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param implements            Implementation interfaces.
         * @param fields                Declaration fields.
         */
        explicit Class(const Lexer::Token* token, Constructor* constructor, Expression* extends,
            const Specialization& implements, const Fields& fields) :
            Abstract(token),
            m_constructor(constructor),
            m_extends(extends),
            m_implements(implements),
            m_fields(fields) {}

        /**
         * @brief Constructs a class node.
         * @param name                  Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param implements            Implementation interfaces.
         * @param fields                Declaration fields.
         * @param location              Resource location.
         */
        explicit Class(const $::String::View& name, Constructor* constructor, Expression* extends,
            const Specialization& implements, const Fields& fields, Block* block, const Bounds& location = {}) :
            Abstract(name, location),
            m_block(block),
            m_constructor(constructor),
            m_extends(extends),
            m_implements(implements),
            m_fields(fields) {}

        /**
         * @brief Constructs a class node.
         * @param token                 Target name.
         * @param constructor           Class constructor.
         * @param extends               Superclass expression.
         * @param implements            Implementation interfaces.
         * @param fields                Declaration fields.
         */
        explicit Class(const Lexer::Token* token, Constructor* constructor, Expression* extends,
            const Specialization& implements, const Fields& fields, Block* block) :
            Abstract(token),
            m_block(block),
            m_constructor(constructor),
            m_extends(extends),
            m_implements(implements),
            m_fields(fields) {}

        //  PUBLIC METHODS  //

        inline constexpr const Block* block() const noexcept { return m_block; }
        inline constexpr const Fields& fields() const noexcept { return m_fields; }
        inline constexpr const Expression* extends() const noexcept { return m_extends; }
        inline constexpr const Constructor* constructor() const noexcept { return m_constructor; }
        inline constexpr const Specialization& implements() const noexcept { return m_implements; }
    };

}  // namespace Talos::Syntax

#endif
