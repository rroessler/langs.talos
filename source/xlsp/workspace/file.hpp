#ifndef _XLSP_WORKSPACE_FILE_HPP
#define _XLSP_WORKSPACE_FILE_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

namespace XLSP::Workspace {

    /// @brief Designates a file, folder or any workspace operation.
    enum class Operation : uint8_t {
        UNUSED = 0,  // ignorable operation
        CREATE = 1,  // a creation event
        CHANGE = 2,  // a change event
        DELETE = 3,  // a deletion event
    };

    /// @brief Encapsulates a file-change event.
    struct File {
        //  PROPERTIES  //

        /// @brief The associated URI of a file.
        $::URI::Buffer resource;

        /// @brief The associated file-operation.
        Operation operation = Operation::UNUSED;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a workspace folder.
         * @param uri                       Resource URI.
         */
        explicit constexpr File(const $::URI::Buffer& uri) : resource(uri) {}
        explicit constexpr File(const $::URI::Buffer& uri, Operation type) : resource(uri), operation(type) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding workspace folders.
         * @param value                         Value to decode.
         */
        static File m_decode(const $::Serde::Value& value) {
            auto uri = $::Reflect::decode<$::URI::Buffer>(value.at("uri"));
            auto type = value.at<Operation>("type", Operation::UNUSED);
            return File(uri, type);  // and construct the resulting file
        }
    };

}  // namespace XLSP::Workspace

#endif
