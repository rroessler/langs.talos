#ifndef _XLSP_MESSAGE_PUBLISH_HPP
#define _XLSP_MESSAGE_PUBLISH_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/diagnostic.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP {

    /// @brief Publish Diagnostics Parameters.
    template <>
    struct Notification::Params<Message::Type::PUBLISH_DIAGNOSTICS> {
        //  PROPERTIES  //

        /// @brief Underlying text-document.
        Document::Identifier identifier;

        /// @brief The associated array of diagnostics.
        std::vector<Diagnostic> diagnostics;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs document open parameters.
         * @param resource                      Document resource.
         * @param diagnostics                   Diagnostics to bind.
         */
        explicit Params(const $::URI::View& resource, const std::vector<Diagnostic>& diagnostics = {}) :
            identifier(resource.buffer()), diagnostics(diagnostics) {}

        /**
         * @brief Constructs document open parameters.
         * @param identifier                    Document to bind.
         * @param diagnostics                   Diagnostics to bind.
         */
        explicit Params(const Document::Identifier& identifier, const std::vector<Diagnostic>& diagnostics = {}) :
            identifier(identifier), diagnostics(diagnostics) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Encodes the parameters.
         * @param self                          Diagnostics parameters.
         */
        static $::Serde::Value m_encode(const Params& self) {
            // ensure we cast the instance to a suitable output
            auto params = *$::Reflect::encode(self.identifier).as<$::Serde::Object>();
            params.emplace("diagnostics", $::Reflect::encode(self.diagnostics));
            return params;  // and return the final diagnostics constructed
        }
    };

}  // namespace XLSP

#endif
