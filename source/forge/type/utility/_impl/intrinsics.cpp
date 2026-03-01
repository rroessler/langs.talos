/// Forge Modules
#include "forge/type/builder.hpp"

//  PUBLIC METHODS  //

Forge::Type::Entity Forge::Type::Any::lookup(const $::String::View&) const { return m_clone(); }
Forge::Type::Entity Forge::Type::Unset::lookup(const $::String::View&) const { return m_clone(); }

Forge::Type::Erased Forge::Type::Any::apply(Operator::Kind kind) const {
    switch (kind) {
        case Operator::Kind::NOT: return Builder::boolean();
        default: return m_clone();  // default to "Any" type
    }
}

Forge::Type::Erased Forge::Type::Any::apply(Operator::Kind kind, const Erased&) const {
    switch (kind) {
        case Operator::Kind::EQ: $_FALLTHROUGH;
        case Operator::Kind::NE: $_FALLTHROUGH;
        case Operator::Kind::LOR: $_FALLTHROUGH;
        case Operator::Kind::LAND: return Builder::boolean();
        default: return m_clone();  // default to "Any" type
    }
}

void Forge::Type::None::m_print($::Stream::Output& os) const { os << Builtins::Proxy<Value::Void>::name(); }