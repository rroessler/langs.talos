#ifndef _TALOS_FORMAT_PIPELINE_HPP
#define _TALOS_FORMAT_PIPELINE_HPP

/// Talos Includes
#include "talos/format/reader.hpp"
#include "talos/format/writer.hpp"

namespace Talos::Format {

/// @brief Formatting Pipeline.
class Pipeline {
  //  PROPERTIES  //

  /// @brief Formatter options to inherit.
  const Options *m_options = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a formatter pipeline.
   * @param options             Format options.
   */
  explicit Pipeline();
  explicit Pipeline(const Options *options);

  //  PUBLIC METHODS  //

  /// @brief Gets the available options.
  const Options *options() const noexcept;

  /**
   * @brief Handles formatting incoming lexical tokens.
   * @param tokens              Tokens buffer.
   */
  Result process(const Lexer::Buffer *tokens);
};

} // namespace Talos::Format

#endif
