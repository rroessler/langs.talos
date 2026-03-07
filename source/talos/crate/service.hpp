#ifndef _TALOS_CRATE_SERVICE_HPP
#define _TALOS_CRATE_SERVICE_HPP

/// Talos Includes
#include "talos/crate/manifest.hpp"
#include "talos/value/common.hpp"

namespace Talos::Crate {

    /// @brief Crate Runtime Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Crates mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief All resolved crates.
        $::Dict<$::Ptr::Unique<Manifest>> m_crates = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        explicit Service() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Handles getting a cached crate resource package.
         * @param file_path                 File path.
         */
        const Manifest* resolve(const $::URI::View& resource);
        const Manifest* resolve(const $::Filesystem::Path& file_path);

        /**
         * @brief Handles getting dynamic crate values.
         * @param isolate                   Thread isolate.
         * @param name                      Library name.
         */
        Value::Any dylib(Runtime::Isolate* isolate, const $::String::View& name) const noexcept;
    };

}  // namespace Talos::Crate

#endif
