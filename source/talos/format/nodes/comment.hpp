#ifndef _TALOS_FORMAT_COMMENT_HPP
#define _TALOS_FORMAT_COMMENT_HPP

/// Format Modules
#include "talos/format/nodes/unicode.hpp"

namespace Talos::Format {

    /// @brief Explicit Comment Node.
    class Node::Comment : public Node::Abstract<Comment, Unicode> {
        //  PROPERTIES  //

        /// @brief Leading comment values.
        static inline $::String::View s_introducer = "//";

        /// @brief Denotes document comments.
        static inline $::String::View s_documents = "!";

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a comment.
         * @param comment               Comment to bind.
         */
        explicit Comment(const $::String::View& comment = "") : Abstract(m_prefix(comment)) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Trims an incoming comment and returns the docstring state.
         * @param comment               Comment to trim.
         */
        static inline constexpr bool m_trim($::String::View& comment) noexcept {
            // if we do not have a comment introducer, then stop
            if (!comment.starts_with(s_introducer)) return false;

            // update the current comment details now
            comment = comment.substr(s_introducer.size());

            // and handle if we find a doctstring or not
            if (!comment.starts_with(s_documents)) return false;

            // we had a valid docstring to be now returned
            return comment = comment.substr(s_documents.size()), true;
        }

        /**
         * @brief Resolves a suitable comment.
         * @param comment               Comment to resolve.
         */
        static inline constexpr $::String::Buffer m_prefix($::String::View comment) noexcept {
            // prepare the incoming buffer to be used now
            auto buffer = $::String::Buffer(s_introducer);
            if (m_trim(comment)) buffer += s_documents;
            if (comment.empty()) return buffer;  // empty

            // ensure we trim the trailing comment now before adding
            return fmt::format("{0} {1}", buffer, $::Trim::both(comment));
        }
    };

}  // namespace Talos::Format

#endif
