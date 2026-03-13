#ifndef _TALOS_FORMAT_STORAGE_HPP
#define _TALOS_FORMAT_STORAGE_HPP

/// Format Modules
#include "talos/format/_inline/nodes.ipp"

namespace Talos::Format {

    /// @brief Dispatching Callback Typing.
    using Callback = $::Functor::Shared<Node*(Reader*)>;

    /// @brief Node Collection Available.
    class Collection {
        //  TYPEDEFS  //

        /// @brief Allow storage internal access.
        friend class Storage;

        /// @brief Prepare the whitespace typing now.
        using Whitespace = $::Map<size_t, Buffer>;

        //  PROPERTIES  //

        /// @brief Separator to be used.
        Node* m_separator = nullptr;

        /// @brief The current segments available.
        Buffer m_buffer = {};

        /// @brief Currently available leading comments.
        Whitespace m_leading = {};

        /// @brief Currently available trailing comments.
        $::Map<size_t, Node*> m_trailing = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a delimited collection.
         * @param separator             Separator to bind.
         */
        explicit Collection(Node* separator = nullptr) : m_separator(separator) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if collections are trimmable at all.
        inline constexpr bool trimmable() const noexcept { return m_separator != nullptr; }

        /// @brief Optional collection separator.
        inline constexpr Node*& separator() noexcept { return m_separator; }
        inline constexpr Node* separator() const noexcept { return m_separator; }

        /**
         * @brief Handles appending whitespace.
         * @param node                  Node instance.
         */
        void whitespace(Node* node) noexcept;

        /**
         * @brief Handles appending a collection item.
         * @param item                  Item instance.
         * @param trailing              Trailing comment.
         */
        bool append(Node* item, Node* trailing = nullptr) noexcept;

        /**
         * @brief Handles merging the collection together.
         * @param storage               Storage instance.
         * @param trailing              Allow trailing separators.
         */
        Node::List* merge(Storage* storage, bool trailing = false) const noexcept;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles trimming leading whitespace.
         * @param whitespace            Whitespace to trim.
         */
        Whitespace m_trim(Whitespace whitespace) const noexcept;

        /**
         * @brief Handles flushing delimiters.
         * @param storage               Storage instance.
         * @param index                 Index of node.
         * @param trailing              Allow trailing separators.
         */
        Node* m_flush(Storage* storage, size_t index, bool trailing = true) const noexcept;

        /**
         * @brief Handles constructing suffixes.
         * @param storage               Storage instance.
         * @param index                 Index of node.
         * @param trailing              Allow trailing separators.
         */
        Node* m_suffix(Storage* storage, size_t index, bool trailing = true) const noexcept;
    };

    /// @brief Format Storage Container.
    class Storage {
        //  PROPERTIES  //

        /// @brief The current group sigil.
        Sigil m_group = 0;

        /// @brief The internal storage container.
        std::vector<$::Ptr::Unique<Node>> m_nodes = {};

        static inline auto s_space_hard = Node::Space(Break::HARD);
        static inline auto s_space_soft = Node::Space(Break::SOFT);

        static inline auto s_line_hard = Node::Line(Break::HARD);
        static inline auto s_line_soft = Node::Line(Break::SOFT);
        static inline auto s_line_literal = Node::Line(Break::LITERAL);
        static inline auto s_line_dynamic = Node::Line(Break::DYNAMIC);

        static inline auto s_expand = Node::Expand();

        static inline auto s_arrow_thin = Node::Unicode("->");
        static inline auto s_arrow_bold = Node::Unicode("=>");

        static inline auto s_paren_left = Node::Unicode("(");
        static inline auto s_paren_right = Node::Unicode(")");

        static inline auto s_brace_left = Node::Unicode("{");
        static inline auto s_brace_right = Node::Unicode("}");

        static inline auto s_brack_left = Node::Unicode("[");
        static inline auto s_brack_right = Node::Unicode("]");

        static inline auto s_attr = Node::Unicode("#[");
        static inline auto s_decor = Node::Unicode("@");

        static inline auto s_empty = Node::Empty();
        static inline auto s_query = Node::Unicode("?");
        static inline auto s_colon = Node::Unicode(":");
        static inline auto s_comma = Node::Unicode(",");
        static inline auto s_assign = Node::Unicode("=");
        static inline auto s_period = Node::Unicode(".");
        static inline auto s_policy = Node::Unicode("::");
        static inline auto s_spread = Node::Unicode("...");
        static inline auto s_terminator = Node::Unicode(";");

        static inline struct {
            inline constexpr Node* hard() const noexcept { return &s_space_hard; }
            inline constexpr Node* soft() const noexcept { return &s_space_soft; }
        } s_space_getter;

        static inline struct {
            inline constexpr Node* hard() const noexcept { return &s_line_hard; }
            inline constexpr Node* soft() const noexcept { return &s_line_soft; }
            inline constexpr Node* literal() const noexcept { return &s_line_literal; }
            inline constexpr Node* dynamic() const noexcept { return &s_line_dynamic; }
        } s_line_getter;

        static inline struct {
            inline constexpr Node* thin() const noexcept { return &s_arrow_thin; }
            inline constexpr Node* bold() const noexcept { return &s_arrow_bold; }
        } s_arrow_getter;

        static inline struct {
            inline constexpr Node* left() const noexcept { return &s_paren_left; }
            inline constexpr Node* right() const noexcept { return &s_paren_right; }
        } s_paren_getter;

        static inline struct {
            inline constexpr Node* left() const noexcept { return &s_brace_left; }
            inline constexpr Node* right() const noexcept { return &s_brace_right; }
        } s_brace_getter;

        static inline struct {
            inline constexpr Node* left() const noexcept { return &s_brack_left; }
            inline constexpr Node* right() const noexcept { return &s_brack_right; }
        } s_brack_getter;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of storage.
        explicit Storage() = default;

        //  PUBLIC METHODS  //

        inline constexpr const auto& line() const noexcept { return s_line_getter; }
        inline constexpr const auto& arrow() const noexcept { return s_arrow_getter; }
        inline constexpr const auto& space() const noexcept { return s_space_getter; }
        inline constexpr const auto& paren() const noexcept { return s_paren_getter; }
        inline constexpr const auto& brace() const noexcept { return s_brace_getter; }
        inline constexpr const auto& brack() const noexcept { return s_brack_getter; }

        inline constexpr Node* attr() const noexcept { return &s_attr; }
        inline constexpr Node* decor() const noexcept { return &s_decor; }

        inline constexpr Node* empty() const noexcept { return &s_empty; }
        inline constexpr Node* colon() const noexcept { return &s_colon; }
        inline constexpr Node* comma() const noexcept { return &s_comma; }
        inline constexpr Node* query() const noexcept { return &s_query; }
        inline constexpr Node* assign() const noexcept { return &s_assign; }
        inline constexpr Node* expand() const noexcept { return &s_expand; }
        inline constexpr Node* period() const noexcept { return &s_period; }
        inline constexpr Node* policy() const noexcept { return &s_policy; }
        inline constexpr Node* spread() const noexcept { return &s_spread; }
        inline constexpr Node* terminator() const noexcept { return &s_terminator; }

        /// @brief Gets the next avialable group-sigil.
        inline constexpr Sigil sigil() noexcept { return m_group++; }

        /**
         * @brief Constructs a comment node.
         * @param text                      Comment text.
         */
        inline constexpr Node* comment(const $::String::View& text) { return allocate<Node::Comment>(text); }

        /**
         * @brief Constructs a text node.
         * @param args                      Text arguments.
         */
        template <class... As>
        inline constexpr Node::Unicode* unicode(As&&... args) {
            return allocate<Node::Unicode>(std::forward<As>(args)...);
        }

        /**
         * @brief Handles minimizing targets.
         * @param target                    Target to compress.
         */
        inline constexpr Node::Minimize* minimize(Node* target) { return allocate<Node::Minimize>(target); }

        /**
         * @brief Constructs a decision node.
         * @param args                      Decision arguments.
         */
        template <class... As>
        inline constexpr Node::Decide* decide(As&&... args) {
            return allocate<Node::Decide>(std::forward<As>(args)...);
        }

        /**
         * @brief Constructs a decision node.
         * @param group                     Group to bind.
         * @param args                      Decision arguments.
         */
        template <class... As>
        inline constexpr Node::Decide* decide(Node::Group* group, As&&... args) {
            return decide(group->sigil(), std::forward<As>(args)...);
        }

        /**
         * @brief Constructs a negation node.
         * @param alternative               Alternative node.
         */
        inline constexpr Node::Decide* negate(Node* alternative) { return decide(empty(), alternative); }

        /**
         * @brief Constructs a negation node.
         * @param alternative               Alternative node.
         */
        inline constexpr Node::Decide* negate(Sigil sigil, Node* alternative) {
            return decide(sigil, empty(), alternative);
        }

        /**
         * @brief Constructs a negation node.
         * @param group                     Group to bind.
         * @param alternative               Alternative node.
         */
        inline constexpr Node::Decide* negate(Node::Group* group, Node* alternative) {
            return decide(group, empty(), alternative);
        }

        /**
         * @brief Constructs a list node.
         * @param args                      List arguments.
         */
        template <class... As>
        inline constexpr Node::List* list(As&&... args) {
            auto* view = allocate<Node::List>(sizeof...(args));
            if constexpr (sizeof...(As)) append(view, std::forward<As>(args)...);
            return view;  // and return the resulting view now as needed
        }

        /**
         * @brief Constructs an indentation node.
         * @param args                      List arguments.
         */
        template <class... As>
        inline constexpr Node::Indent* indent(As&&... args) {
            auto* view = allocate<Node::Indent>(sizeof...(args));
            if constexpr (sizeof...(As)) append(view, std::forward<As>(args)...);
            return view;  // and return the resulting view now as needed
        }

        /**
         * @brief Constructs a grouped node.
         * @param args                      List arguments.
         */
        template <class... As>
        inline constexpr Node::Group* group(As&&... args) {
            return group(sigil(), std::forward<As>(args)...);
        }

        /**
         * @brief Constructs a grouped node.
         * @param args                      List arguments.
         */
        template <class... As>
        inline constexpr Node::Group* group(Sigil sigil, As&&... args) {
            auto* view = allocate<Node::Group>(sigil, sizeof...(As));
            if constexpr (sizeof...(As)) append(view, std::forward<As>(args)...);
            return view;  // and return the resulting view now as needed
        }

        /**
         * @brief Concatenates items onto a list.
         * @param node                      Potential list node.
         * @param args                      Arguments to append.
         */
        template <class... As>
        inline constexpr Node::List* append(Node* node, As&&... args) {
            auto* view = node->is<Node::List>() ? node->as<Node::List>() : list(node);
            return m_append(view, std::forward<As>(args)...);  // and append as needed
        }

        /**
         * @brief Handles allocating a format node.
         * @param args                      Node arguments.
         */
        template <std::derived_from<Node> T, class... As>
        inline constexpr T* allocate(As&&... args) {
            return static_cast<T*>(m_nodes.emplace_back($::New().unique<T>(std::forward<As>(args)...)).get());
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Concatenates items onto a list.
         * @param view                      Potential list view.
         * @param node                      Node to be appended.
         * @param rest                      Additional arguments.
         */
        template <std::derived_from<Node::List> T, class N, class... As>
        inline constexpr T* m_append(T* view, N&& node, As&&... args) {
            if (node == nullptr || node->tag() == $::RTTI::Hash<Node::Empty>()) $_PP_NOOP();
            else if (node->tag() != $::RTTI::Hash<Node::List>()) view->nodes().emplace_back(node);
            else $::Ranges::Append(view->nodes(), node->template as<Node::List>()->nodes());

            if constexpr (sizeof...(As) == 0) return view;  // no more parsing
            else return m_append<T, As...>(view, std::forward<As>(args)...);
        }
    };

}  // namespace Talos::Format

#endif
