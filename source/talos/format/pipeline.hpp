#ifndef _TALOS_FORMAT_PIPELINE_HPP
#define _TALOS_FORMAT_PIPELINE_HPP

/// Talos Modules
#include "talos/format/reader.hpp"
#include "talos/format/writer.hpp"

namespace Talos::Format {

    /// @brief Formatting Pipeline.
    class Pipeline : public XI::Define<Pipeline, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Formatting options to inherit.
        const Options* m_options = nullptr;

        /// @brief Pipeline syntax reader.
        $::Ptr::Unique<Reader> m_reader = nullptr;

        /// @brief Pipeline format writer.
        $::Ptr::Unique<Writer> m_writer = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty pipeline.
        explicit Pipeline() = default;

        //  PUBLIC METHODS  //

        inline constexpr Reader* reader() const noexcept { return m_assert(m_reader.get()); }
        inline constexpr Writer* writer() const noexcept { return m_assert(m_writer.get()); }

        inline constexpr Storage* storage() const noexcept { return reader()->storage(); }
        inline constexpr const Options* options() const noexcept { return m_assert(m_options); }

        /**
         * @brief Handles processing tokens.
         * @param tokens                Lexer tokens.
         * @param options               Format options.
         */
        Result process(const Lexer::Buffer* tokens, const Options* options);
        inline Result process(const Lexer::Buffer* tokens) { return process(tokens, $::Global::get<Options>()); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles initializing the pipeline.
         * @param tokens                Lexer tokens.
         * @param options               Format options.
         */
        inline constexpr auto m_initialize(const Lexer::Buffer* tokens, const Options* options) {
            // ensure a current sequence has ended already
            $_ASSERT(m_options == nullptr, "Format::Pipeline active");

            // construct the reader and the writer to be used
            m_writer = $::New().unique<Writer>(m_options = options);
            m_reader = $::New().unique<Reader>(tokens, m_options);

            // prepare the conclusive finalization handler
            return $::Functor::Defer([&] { m_finalize(); });
        }

        /// @brief Handles cleaning a pipeline up.
        inline constexpr void m_finalize() { m_options = nullptr, m_reader = nullptr, m_writer = nullptr; }

        /**
         * @brief Asserts that the pipeline is running.
         * @param value                 Value to assert.
         */
        template <class T>
        inline constexpr T* m_assert(T* value) const noexcept {
            return $_ASSERT(value != nullptr, "Format::Pipeline not active"), value;
        }
    };

}  // namespace Talos::Format

#endif
