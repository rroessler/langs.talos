#ifndef _TALOS_BUNDLE_WORKER_HPP
#define _TALOS_BUNDLE_WORKER_HPP

/// Talos Modules
#include "talos/async/main.hpp"
#include "talos/bundle/archive.hpp"
#include "talos/bundle/fuse.hpp"
#include "talos/bundle/options.hpp"
#include "talos/module/drafts.hpp"

namespace Talos::Bundle {

    /// @brief Bundler Worker Thread.
    class Worker : public Async::Main {
        //  PROPERTIES  //

        /// @brief Archive provider.
        Archive m_archive = {};

        /// @brief Bundler options.
        Options m_options = {};

        /// @brief Verbose spinner details.
        $::Spinner::Shared m_spinner = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a bundle worker.
         * @param options           Bundler options.
         */
        explicit Worker(const Options& options = {});
        explicit Worker(XI::Container* services, const Options& options = {});

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles launching the bundler.
        $_NORETURN void m_execute() final;

        /**
         * @brief Handles resolving the script.
         * @param script                Entry script.
         */
        $::URI::Buffer m_resolve(const $::String::View& script);

        /**
         * @brief Handles codesigning the output.
         * @param output                Output path.
         */
        bool m_codesign(const $::Filesystem::Path& output) const noexcept;

        /**
         * @brief Handles imbuing a binary with data.
         * @param binary                Binary to imbue.
         * @param blob                  Resource blob.
         */
        bool m_imbue(Executable& binary, const Blob& blob) const noexcept;
        bool m_imbue(Executable& binary, const Buffer& buffer) const noexcept;

        /**
         * @brief Handles resolving outputs.
         * @param script                Script resource.
         * @param extension             Extension to inherit.
         */
        $::Filesystem::Path m_output(const $::URI::View& script);
        $::Filesystem::Path m_output(const $::URI::View& script, const $::String::View& extension);

        /**
         * @brief Shows bundle failures.
         * @param code                  Diagnostic code.
         * @param args                  Message arguments.
         */
        template <class... As>
        inline constexpr bool m_failure(Diagnostic::Code code, As&&... args) const noexcept {
            auto category = Diagnostic::Traits::category(code);
            auto title = $::Dye::red("Exception.{0}", category).bold();
            auto message = Diagnostic::Traits::format(code, std::forward<As>(args)...);
            if (m_spinner) m_spinner->dismiss();  // ensure we finalize now
            return $::IO::cerr() << title << ": " << message << '\n', false;
        }
    };

}  // namespace Talos::Bundle

#endif
