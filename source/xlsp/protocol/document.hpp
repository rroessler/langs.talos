#ifndef _XLSP_PROTOCOL_DOCUMENT_HPP
#define _XLSP_PROTOCOL_DOCUMENT_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"
#include "xlsp/protocol/reference.hpp"

namespace XLSP {

/// @brief Text Document Item.
struct Document {
  //  TYPEDEFS  //

  /// @brief Document Synchronization Kinds.
  enum class Sync : uint8_t { NONE = 0, FULL = 1, INCR = 2 };

  /// @brief Document Edit Structure.
  struct Edit {
    //  PROPERTIES  //

    /// @brief Range to edit.
    Range range = {};

    /// @brief Replacement text to use.
    $::String::Buffer text = "";

    //  CONSTRUCTORS  //

    /// @brief Constructs an empty edit.
    explicit Edit() = default;

    /**
     * @brief Constructs a document edit.
     * @param text              Text replacement.
     * @param range             Range of replacement.
     */
    explicit Edit(const $::String::Buffer &text, const Range &range) : range(range), text(text) {}

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Handles encoding a document edit.
     * @param self                      Edit to encode.
     */
    static $::Serde::Value m_encode(const Edit &self) {
      return {{"range", $::Serde::Encode(self.range)}, {"newText", self.text}};
    }
  };

  /// @brief Content Change Event.
  struct Change {
    //  PROPERTIES  //

    /// @brief Text being replaced.
    $::String::Buffer text = "";

    /// @brief Range the document modifies.
    std::optional<Range> range = std::nullopt;

    //  CONSTRUCTORS  //

    /// @brief Constructs a default change value.
    explicit Change() = default;

    //  PUBLIC METHODS  //

    /**
     * @brief Applies a change to the given content.
     * @param content                   Content to update.
     * @param encoding                  Encoding to use.
     */
    void apply($::String::Buffer &content, const Encoding::Type &encoding) const;

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Handles decoding a document change
     * @param value                     Value to decode.
     */
    static Change m_decode(const $::Serde::Value &value) {
      // prepare the base change
      auto change = Change();

      // attempt updating our various items
      change.text = *value.at<$::Serde::Text>("text");

      // handle the optional values
      if (value.has("range")) change.range = $::Serde::Decode<Range>(value.at("range"));

      // and return the resulting change
      return change;
    }
  };

  /// @brief Text Document Identifier.
  struct Identifier {
    //  PROPERTIES  //

    /// @brief Document URI value.
    $::URI::Buffer resource = {};

    /// @brief Versioned identifier value.
    std::optional<int64_t> version = std::nullopt;

    //  CONSTRUCTORS  //

    /**
     * @brief Constructs an empty document.
     * @param resource                  Document resource.
     */
    constexpr Identifier(const $::URI::Buffer &resource = {}) : resource(resource) {}

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Handles encoding a document identifier.
     * @param self                      Identifier to encode.
     */
    static inline $::Serde::Value m_encode(const Identifier &self) {
      $::Serde::Object value = {{"uri", $::Serde::Encode(self.resource)}};
      if (self.version.has_value()) value["version"] = *self.version;
      return value; // return the resulting identifier value
    }

    /**
     * @brief Handles decoding a document identifier.
     * @param value                     Value to decode.
     */
    static inline Identifier m_decode(const $::Serde::Value &value) {
      auto identifier = Identifier($::Serde::Decode<$::URI::Buffer>(value.at("uri")));
      if (auto *v = value.at<$::Serde::Number>("version")) identifier.version = static_cast<int64_t>(*v);
      return identifier; // return the resulting identifier now
    }
  };

  /// @brief Document Layout Structure.
  struct Layout {
    //  PROPERTIES  //

    /// @brief Document identifier.
    Identifier identifier = {};

    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a document layout.
     * @param identifier              Identifier to bind.
     */
    constexpr Layout(const Identifier &identifier = {}) : identifier(identifier) {}

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Constructs the document position.
     * @param value                   Value to decode.
     */
    static Layout m_decode(const $::Serde::Value &value) {
      return Layout($::Serde::Decode<Identifier>(value.at("textDocument")));
    }
  };

  /// @brief Document Cursor Structure.
  struct Cursor : public Layout {
    //  PROPERTIES  //

    /// @brief Associated document position.
    Position position = {};

    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a document cursor.
     * @param identifier              Document identifier.
     * @param position                Document position.
     */
    constexpr Cursor(const Identifier &identifier = {}, const Position &position = {}) :
        Layout(identifier), position(position) {}

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Constructs the document position.
     * @param value                   Value to decode.
     */
    static Cursor m_decode(const $::Serde::Value &value) {
      auto position = $::Serde::Decode<Position>(value.at("position"));
      auto identifier = $::Serde::Decode<Identifier>(value.at("textDocument"));
      return Cursor(identifier, position); // and safely return the cursor now
    }
  };

  /// @brief Document Locations Structure.
  struct Locations {
    //  PROPERTIES  //

    /// @brief Reference locations.
    std::vector<Reference> locations = {};

    //  CONSTRUCTORS  //

    /**
     * @brief Constructs document locations.
     * @param locations               Locations to bind.
     */
    constexpr Locations(const std::vector<Reference> &locations = {}) : locations(locations) {}

  protected:
    //  PRIVATE METHODS  //

    /**
     * @brief Encodes document references.
     * @param value                   Value to encode..
     */
    static auto m_encode(const Locations &self) { return $::Serde::Encode(self.locations); }
  };

private:
  //  PROPERTIES  //

  /// @brief Document identifier value.
  Identifier m_identifier = {};

  /// @brief Current document text.
  $::String::Buffer m_text = {};

  /// @brief Language identifier.
  $::String::Buffer m_language = "plaintext";

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construct of empty documents.
  constexpr Document() = default;

  /**
   * @brief Constructs an empty document.
   * @param resource          Document resource.
   */
  constexpr Document(const $::URI::Buffer &resource) : m_identifier(resource) {}

  /**
   * @brief Constructs an empty document.
   * @param identifier        Document identifier.
   */
  constexpr Document(const Identifier &identifier) : m_identifier(identifier) {}

  //  PUBLIC METHODS  //

  inline constexpr $::String::Buffer &text() noexcept { return m_text; }
  inline constexpr const $::String::Buffer &text() const noexcept { return m_text; }
  inline constexpr $::URI::View resource() const noexcept { return m_identifier.resource; }
  inline constexpr $::String::View language() const noexcept { return m_language; }
  inline constexpr const Identifier &identifier() const noexcept { return m_identifier; }
  inline constexpr std::optional<int64_t> version() const noexcept { return m_identifier.version; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding a document value.
   * @param value                     Value to decode.
   */
  static Document m_decode(const $::Serde::Value &value) {
    // construct the document from the URI value
    auto document = Document($::Serde::Decode<Identifier>(value));

    // prepare the other fields to be set
    document.m_text = *value.at<$::Serde::Text>("text");
    document.m_language = *value.at<$::Serde::Text>("languageId");

    // return the resulting document now
    return document;
  }
};

} // namespace XLSP

#endif
