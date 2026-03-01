#ifndef _FORGE_DIAGNOSTIC_REPORTER_HPP
#define _FORGE_DIAGNOSTIC_REPORTER_HPP

/// Forge Modules
#include "forge/diagnostic/options.hpp"
#include "forge/diagnostic/view.hpp"

namespace Forge::Diagnostic {

    /// @brief Source Reporter Options.
    class Reporter : public XI::Define<Reporter, XI::Unique, $::Printable> {
        //  TYPEDEFS  //

        /// @brief Scoping internal access.
        friend class Scope;

        //  PROPERTIES  //

        /// @brief Associated reporter resource.
        $::URI::View m_resource;

        /// @brief Current diagnostic scoping.
        Resource::Stack m_scoping = {};

        /// @brief Bound diagnostic values.
        std::vector<View> m_diagnostics = {};

        /// @brief Diagnostic reporter options.
        $::Ptr::Unique<Options> m_options = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a reporter instance.
         * @param options                   Reporter options.
         * @param resource                  Resource to bind.
         */
        explicit Reporter(const $::URI::View& resource = $::URI::Anonymous());
        explicit Reporter(const Options& options, const $::URI::View& resource = $::URI::Anonymous());
        explicit Reporter(XI::Container* services, const $::URI::View& resource = $::URI::Anonymous());

        //  PUBLIC METHODS  //

        /// @brief Whether or not the reporter is empty.
        inline constexpr bool empty() const noexcept { return m_diagnostics.empty(); }

        /// @brief The total diagnostics count.
        inline constexpr size_t size() const noexcept { return m_diagnostics.size(); }

        /// @brief Gets the available reporter instance.
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }

        /// @brief The underlying diagnostics limit.
        inline constexpr size_t limit() const noexcept { return m_options ? m_options->limit : SIZE_MAX; }

        /// @brief Gets the current severity assigned.
        inline constexpr Severity severity() const noexcept { return m_options ? m_options->severity : Severity::WARN; }

        /// @brief Gets a view of the available diagnostics.
        inline constexpr std::vector<XLSP::Diagnostic> view() const noexcept {
            auto predicate = [](const View& diagnostic) { return diagnostic.underlying(); };
            return $::Ranges::To(m_diagnostics | std::views::transform(predicate));
        }

        /// @brief Denotes if the reporter has any error diagnostic.
        inline bool failed() const {
            auto predicate = [](const View& d) { return d.severity() == Severity::ERROR; };
            return std::ranges::any_of(m_diagnostics, predicate);  // check for any errors
        }

        /// @brief Gets the total error count.
        inline size_t errors() const { return count(Severity::ERROR); }

        /**
         * @brief Counts diagnostics.
         * @param code                          Code to filter.
         */
        inline size_t count(Code code) const {
            auto predicate = [code](const View& d) { return d.code() == code; };
            return std::ranges::count_if(m_diagnostics, predicate);  // count now
        }

        /**
         * @brief Counts diagnostics.
         * @param severity                      Severity to filter.
         */
        inline size_t count(Severity severity) const {
            auto predicate = [severity](const View& d) { return d.severity() == severity; };
            return std::ranges::count_if(m_diagnostics, predicate);  // attempt counting now
        }

        /// @brief Clears all the available diagnostics.
        inline void clear() { m_diagnostics.clear(); }

        /**
         * @brief Collects a set of diagnostics.
         * @param diagnostics                   Diagnostics to collect.
         */
        inline void collect(const Reporter& reporter) { collect(reporter.m_diagnostics); }
        inline void collect(const std::vector<View>& diagnostics) {
            for (const auto& diagnostic : diagnostics) {
                if (m_ignore(diagnostic)) continue;
                if (m_exists(diagnostic)) continue;
                m_diagnostics.emplace_back(diagnostic);
            }
        }

        /**
         * @brief Handles constructing diagnostics.
         * @tparam As                           Argument types.
         * @param location                      Diagnostic location.
         * @param code                          Code of diagnostic.
         * @param args                          Message arguments.
         */
        template <class... As>
        inline bool emit(const XLSP::Range& range, Code code, As&&... args) {
            if (range == XLSP::Range()) return emit(Resource::Stack(), code, std::forward<As>(args)...);
            return emit(Resource::Location(m_resource, range), code, std::forward<As>(args)...);
        }

        /**
         * @brief Handles constructing diagnostics.
         * @tparam As                           Argument types.
         * @param location                      Diagnostic location.
         * @param code                          Code of diagnostic.
         * @param args                          Message arguments.
         */
        template <class... As>
        inline bool emit(const Resource::Location& location, Code code, As&&... args) {
            auto stack = location.anonymous() ? Resource::Stack() : Resource::Stack({ location });
            return emit(stack, code, std::forward<As>(args)...);  // and further emit the instance now
        }

        /**
         * @brief Handles constructing diagnostics.
         * @tparam As                           Argument types.
         * @param stack                         Diagnostic locations.
         * @param code                          Code of diagnostic.
         * @param args                          Message arguments.
         */
        template <class... As>
        inline bool emit(const Resource::Stack& stack, Code code, As&&... args) {
            return m_emplace(m_create(code, stack), std::forward<As>(args)...);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles constructing diagnostics.
         * @param code                          Code of diagnostic.
         * @param stack                         Diagnostic stack.
         */
        inline View m_create(Code code, Resource::Stack stack) const {
            // construct the base diagnostic
            auto diagnostic = View();

            // prepare the underlying code to be used
            diagnostic.m_code = code;
            diagnostic.m_severity = m_resolve(code);

            // initialize the base stack to be used
            diagnostic.m_stack = $::Ranges::Prepend(stack, m_scoping);

            // and return as necessary now
            return diagnostic;
        }

        /**
         * @brief Handles resolving severities to be bound.
         * @param code                          Diagnostic code.
         */
        inline Severity m_resolve(Code code) const {
            if ($_UNLIKELY(m_options == nullptr)) return Traits::severity(code);  // ignore when no options
            return m_options->overrides.contains(code) ? m_options->overrides.at(code) : Traits::severity(code);
        }

        /**
         * @brief Handles emplacing diagnostics.
         * @tparam As                           Argument types.
         * @param diagnostic                    Diagnostic to populate.
         * @param args                          Message arguments.
         */
        template <class... As>
        bool m_emplace(View&& diagnostic, As&&... args) {
            // stop if we could not emplace the instance
            if (m_ignore(diagnostic)) return diagnostic.severity() == Severity::ERROR;

            // render the diagnostic now to be used (since not-ignorable)
            diagnostic.m_message = Traits::format(diagnostic.m_code, std::forward<As>(args)...);

            // only insert if the diagnostic is unique
            if (!m_exists(diagnostic)) m_diagnostics.emplace_back(std::move(diagnostic));

            // and denote the error status now
            return diagnostic.severity() == Severity::ERROR;
        }

        /**
         * @brief Checks if a diagnostic could be ignored.
         * @param diagnostic                    Diagnostic to query.
         */
        inline bool m_ignore(const View& diagnostic) const {
            if (m_diagnostics.size() > limit()) return true;  // should ignore since limit is reached
            if (diagnostic.m_stack.empty()) return true;      // ignore if the underlying stack is empty
            return diagnostic.m_severity == Severity::NONE || diagnostic.m_severity > severity();
        }

        /**
         * @brief Checks if a diagnostic exists.
         * @param diagnostic                Diagnostic to query.
         */
        inline bool m_exists(const View& diagnostic) const {
            auto predicate = [diagnostic](const View& other) { return diagnostic == other; };
            return std::ranges::any_of(m_diagnostics, predicate);  // check if the diagnostic exists
        }

        /**
         * @brief Handles printing reporter diagnostics.
         * @param os                            Output stream.
         * @param self                          Reporter instance.
         */
        static void m_print($::Stream::Output& os, const Reporter& self);
    };

    /// @brief Encapsulates a reporter scoping.
    class Scope {
        //  PROPERTIES  //

        /// @brief Enforce validation.
        bool m_valid = false;

        /// @brief Diagnostic reporter.
        Reporter* m_reporter = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Default construction.
        explicit Scope() = default;

        /**
         * @brief Constructs a reporter scoping.
         * @param reporter                  Reporter to scope.
         * @param location                  Location to enqueue.
         */
        explicit Scope(Reporter* reporter, const Resource::Location& location) :
            m_valid(!location.anonymous()), m_reporter(reporter) {
            if (m_valid && m_reporter) m_reporter->m_scoping.emplace_back(location);
        }

        /// @brief Handles removing the enqueued location.
        ~Scope() {
            if (m_valid && m_reporter) m_reporter->m_scoping.pop_back();
        }
    };

}  // namespace Forge::Diagnostic

#endif
