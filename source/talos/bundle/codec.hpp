#ifndef _TALOS_BUNDLE_CODEC_HPP
#define _TALOS_BUNDLE_CODEC_HPP

/// Talos Modules
#include "talos/forward/bundle.hpp"
#include "talos/function/info.hpp"
#include "talos/linker/arena.hpp"
#include "talos/runtime/options.hpp"

namespace Talos::Bundle {

    /// @brief Encapsulates a bundled filesystem.
    struct Filesystem {
        //  PROPERTIES  //

        /// @brief The script resources.
        std::vector<$::URI::Buffer> resources = {};

        /// @brief All the available scripts.
        std::vector<$::Ptr::Unique<Linker::Arena>> scripts = {};

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a filesystem.
         * @param arenas                Arenas to bind.
         * @param runtime               Runtime options.
         */
        explicit Filesystem(const std::vector<Linker::Arena*>& arenas = {});
    };

    /// @brief Handles encoding bundles.
    struct Encoder : public $::Blob::Encoder<Filesystem> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base encoder.
        using $::Blob::Encoder<Filesystem>::Encoder;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding an archive.
         * @param fs                    Filesystem to encode.
         * @param sink                  Blob sink to use.
         */
        void m_encode(const Filesystem& fs, Sink& sink) const noexcept final;

        /**
         * @brief Handles encoding an arena.
         * @param arena                 Arena to encode.
         * @param sink                  Blob sink to use.
         */
        void m_encode(const Linker::Arena& arena, Sink& sink) const noexcept;

        /**
         * @brief Handles encoding a resource.
         * @param resource              Resource to encode.
         * @param sink                  Blob sink to use.
         */
        void m_encode(const $::URI::View& resource, Sink& sink) const noexcept;

        /**
         * @brief Handles encoding a function.
         * @param info                  Info to encode.
         * @param sink                  Blob sink to use.
         */
        void m_encode(const Function::Info& info, Sink& sink) const noexcept;

        /**
         * @brief Handles encoding a value.
         * @param value                 Value to encode.
         * @param sink                  Blob sink to use.
         */
        void m_encode(const Value::Any& value, Sink& sink) const noexcept;
    };

    /// @brief Handles decoding bundles.
    struct Decoder : public $::Blob::Decoder<Filesystem> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base encoder.
        using $::Blob::Decoder<Filesystem>::Decoder;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles reading the file-system.
         * @param source                Blob source state.
         */
        Filesystem m_decode(Source source) const noexcept final;

        /**
         * @brief Handles decoding an arena.
         * @param arena                 Arena to decode.
         * @param source                Blob source state.
         */
        void m_decode($::Ptr::Unique<Linker::Arena>& arena, Source& source) const noexcept;

        /**
         * @brief Handles decoding a function.
         * @param info                  Function information.
         * @param source                Blob source state.
         */
        void m_decode($::Ptr::Unique<Function::Info>& info, Source& source) const noexcept;
    };

}  // namespace Talos::Bundle

#endif
