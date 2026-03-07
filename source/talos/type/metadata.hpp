#ifndef _TALOS_TYPE_METADATA_HPP
#define _TALOS_TYPE_METADATA_HPP

/// Talos Modules
#include "talos/module/metadata.hpp"
#include "talos/type/context.hpp"

namespace Talos::Module {

    /// @brief Constructs a set of typed metadata.
    template <>
    class Metadata::Attributes<Phase::TYPED> : public Metadata {
        //  PROPERTIES  //

        /// @brief Construct the underlying type-context.
        $::Ptr::Unique<Type::Context> m_context = $::New().unique<Type::Context>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of exports.
        explicit Attributes() = default;

        //  PUBLIC METHODS  //

        inline constexpr $::Ptr::Unique<Type::Context>& context() noexcept { return m_context; }
        inline constexpr const Type::Context* context() const noexcept { return m_context.get(); }
    };

}  // namespace Talos::Module

#endif
