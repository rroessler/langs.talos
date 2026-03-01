#ifndef _FORGE_MODULE_INTERFACE_HPP
#define _FORGE_MODULE_INTERFACE_HPP

/// Forge Modules
#include "forge/async/thenable.hpp"
#include "forge/diagnostic/reporter.hpp"
#include "forge/document/buffer.hpp"
#include "forge/forward/linker.hpp"
#include "forge/forward/runtime.hpp"
#include "forge/forward/syntax.hpp"
#include "forge/module/metadata.hpp"
#include "forge/resource/trace.hpp"
#include "forge/value/common.hpp"

namespace Forge::Module {

    /// @brief Baseline Module Interface.
    class $_ABSTRACT Interface : public XI::Define<Interface, XI::Unique, $::RTTI::Dynamic> {
        //  PROPERTIES  //

        /// @brief Module mutex instance.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Current interface phase.
        $::Atomic<Phase> m_phase = Phase::CLEANED;

        /// @brief Associated resource buffer.
        $::URI::Buffer m_resource = $::URI::Anonymous().buffer();

        /// @brief Bound diagnostic reporter.
        $::Ptr::Unique<Diagnostic::Reporter> m_reporter = $::New().unique<Diagnostic::Reporter>();

        /// @brief Available module metadata.
        std::array<$::Ptr::Unique<Metadata>, FORGE_XX_MODULE_PHASES($_XX_ENUM_COUNT) - 1> m_metadata = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an anonymous resource (not recommended).
        explicit Interface() = default;

        /**
         * @brief Constructs a module interface.
         * @param resource                  Document resource.
         */
        explicit Interface(const $::URI::Buffer& resource) :
            m_resource(resource), m_reporter($::New().unique<Diagnostic::Reporter>(m_resource)) {}

        /**
         * @brief Constructs a module interface.
         * @param resource                  Document resource.
         */
        explicit Interface(const $::URI::View& resource) : Interface(resource.buffer()) {}

        /**
         * @brief Constructs a module interface.
         * @param services                  Services container.
         * @param resource                  Document resource.
         */
        explicit Interface(XI::Container* services, const $::URI::Buffer& resource) :
            m_resource(resource), m_reporter(services->get<Diagnostic::Reporter>(services, m_resource)) {}

        /**
         * @brief Constructs a module interface.
         * @param services                  Services container.
         * @param resource                  Document resource.
         */
        explicit Interface(XI::Container* services, const $::URI::View& resource) :
            Interface(services, resource.buffer()) {}

        //  PUBLIC METHODS  //

        inline constexpr Phase phase() const noexcept { return m_phase; }
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }
        inline constexpr bool ready() const noexcept { return phase() >= Phase::COMPILED; }
        inline constexpr Syntax::Dependencies dependencies() const noexcept { return m_dependencies(); }

        inline constexpr Diagnostic::Reporter* reporter() noexcept { return m_reporter.get(); }
        inline constexpr const Diagnostic::Reporter* reporter() const noexcept { return m_reporter.get(); }

        /// @brief Handles dumping module metadata.
        template <Dump D>
        void dump() const noexcept;

        /// @brief Safely constructs metadata values.
        template <Phase P>
        inline constexpr Metadata::Attributes<P>* metadata() requires(P > Phase::CLEANED) {
            static constexpr auto index = static_cast<uint8_t>(P) - 1;
            if (m_metadata[index] == nullptr) m_metadata[index] = $::New().unique<Metadata::Attributes<P>>();
            return reinterpret_cast<Metadata::Attributes<P>*>(m_metadata[index].get());  // resolve
        }

        /// @brief Allows getting currently made metadata.
        template <Phase P>
        inline constexpr const Metadata::Attributes<P>* metadata() const requires(P > Phase::CLEANED) {
            static constexpr auto index = static_cast<uint8_t>(P) - 1;
            $_ASSERT(m_metadata[index] != nullptr, "Metadata for interface not yet created");
            return reinterpret_cast<const Metadata::Attributes<P>*>(m_metadata[index].get());
        }

        /**
         * @brief Handles parsing a module.
         * @param services                  Service container.
         */
        void parse(XI::Container* services);

        /**
         * @brief Handles analyzing a module.
         * @param services                  Service container.
         */
        void analyze(XI::Container* services);

        /**
         * @brief Handles compiling a module.
         * @param services                  Service container.
         */
        Linker::Arena* compile(XI::Container* services);

        /**
         * @brief Handles interpreting a module.
         * @param isolate                   Runtime isolate.
         */
        Async::Thenable* interpret(Runtime::Isolate* isolate, const Resource::Trace& trace = {});

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying available dependencies.
        Syntax::Dependencies m_dependencies() const noexcept;

        /**
         * @brief Gets the document buffer for a module.
         * @param services                  Service container.
         */
        $::Ptr::Shared<Document::Buffer> m_document(XI::Container* services) const noexcept;

        /**
         * @brief Handles parsing a module.
         * @param services                  Service container.
         * @param syntax                    Syntax metadata.
         */
        virtual void m_parse(XI::Container* services, Metadata::Attributes<Phase::PARSED>* syntax);

        /**
         * @brief Handles analyzing a module.
         * @param services                  Service container.
         * @param types                     Type analysis metadata.
         */
        virtual void m_analyze(XI::Container* services, Metadata::Attributes<Phase::TYPED>* types);

        /**
         * @brief Handles compiling a module.
         * @param services                  Service container.
         * @param metadata                  Compilation metadata.
         */
        virtual void m_compile(XI::Container* services, Metadata::Attributes<Phase::COMPILED>* metadata);

        /**
         * @brief Handles interpreting a module.
         * @param isolate                   Runtime isolate.
         * @param exports                   Exports metadata.
         */
        virtual Async::Thenable* m_interpret(Runtime::Isolate* isolate, Metadata::Attributes<Phase::EXPORTED>* exports);
    };

    /// @brief Module Interface Abstraction.
    template <class T>
    using Abstract = $::RTTI::Extends<T, Interface>;

}  // namespace Forge::Module

#endif
