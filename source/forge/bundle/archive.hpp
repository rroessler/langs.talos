#ifndef _FORGE_BUNDLE_ARCHIVE_HPP
#define _FORGE_BUNDLE_ARCHIVE_HPP

/// Forge Modules
#include "forge/bundle/codec.hpp"
#include "forge/forward/module.hpp"

namespace Forge::Bundle {

    /// @brief Internal provider.
    using Provider = XJCT::Archive::Provider;

    /// @brief Bundled Archive Service.
    class Archive : public XI::Define<Archive, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Internal provider for archives.
        Provider m_provider = {};

        /// @brief Services container (if nullptr then running headless).
        XI::Container* m_services = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a headless archive.
        constexpr Archive() = default;

        /**
         * @brief Constructs a serviced archive.
         * @param services              Services container.
         */
        constexpr Archive(XI::Container* services) : m_services(services) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if currently headless.
        inline constexpr bool headless() const noexcept { return m_services == nullptr; }

        /// @brief Encapsulated provider instance.
        inline constexpr const Provider* provider() const noexcept { return &m_provider; }

        /**
         * @brief Handles decoding an archive.
         * @param blob                  Blob to decode.
         */
        inline constexpr Filesystem decode(const Blob& blob) const noexcept { return Decoder().read(blob); }

        /**
         * @brief Handles encoding an archive.
         * @param fuse                  Archive fuse.
         */
        inline constexpr Filesystem decode(const XJCT::Sentinel::View& fuse) const noexcept {
            return decode(m_provider.resource(fuse));
        }

        /**
         * @brief Handles encoding an archive.
         * @param fs                    Filesystem to encode.
         */
        inline constexpr Buffer encode(const Filesystem& fs) const noexcept { return Encoder().write(fs); }

        /**
         * @brief Handles encoding an archive.
         * @param modules               Modules to encode.
         */
        inline constexpr Buffer encode(Import::Service* modules) const noexcept { return m_encode(modules); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles compiling modules.
         * @param modules               Modules service.
         */
        Buffer m_encode(Import::Service* modules) const noexcept;

        /**
         * @brief Handles compiling a module.
         * @param module                Module to compile.
         */
        std::future<Linker::Arena*> m_compile(Module::Interface* module) const noexcept;
    };

}  // namespace Forge::Bundle

#endif
