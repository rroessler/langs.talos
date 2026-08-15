#ifndef _SHELL_COMMAND_USAGE_HPP
#define _SHELL_COMMAND_USAGE_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

namespace Shell::Command {

/// @brief Shell Command Usage
struct $_ABSTRACT Usage {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Usage() = default;

  //  PUBLIC METHODS  //

  /// @brief Handlers getting available help details.
  inline constexpr $::String::Buffer help() const noexcept {
    auto oss = std::stringstream(); // prepare
    $::Color::Enabled(oss, $::Color::Enabled());
    return m_help(oss), oss.str(); // construct
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles showing usage details.
   * @param os                        Output stream.
   */
  virtual void m_help(std::ostream &os) const = 0;
};

/// @brief Handles describing usage details.
class Descriptor : public Usage {
  //  TYPEDEFS  //

  /// @brief Core list entry value.
  using Entry = std::pair<$::Color::ANSI, $::String::View>;

  /// @brief Denotes a positional item.
  using Positional = std::pair<$::String::View, bool>;

  /// @brief Underlying descriptor list details.
  using List = std::vector<Entry>;

  /// @brief Initializer list value.
  using Initializer = std::initializer_list<Entry>;

  //  PROPERTIES  //

  /// @brief Explicit descriptor title.
  $::String::View m_title;

  List m_commands = {};    // Sub-commands available.
  List m_options = {};     // Explicit options available.
  List m_environment = {}; // Environment flags available.

  /// @brief Available positionals.
  std::vector<Positional> m_positionals = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a descriptor instance.
   * @param title                     Title to bind.
   */
  constexpr Descriptor(const $::String::View &title = "") : m_title(title) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying title value.
  inline constexpr $::String::View title() const { return m_title; }

  inline Descriptor &commands(const Initializer &list) { return m_commands = list, *this; }
  inline Descriptor &options(const Initializer &list) { return m_options = list, *this; }
  inline Descriptor &environment(const Initializer &list) { return m_environment = list, *this; }
  inline Descriptor &positionals(const std::initializer_list<Positional> &list) { return m_positionals = list, *this; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles showing usage details.
   * @param os                        Output stream.
   */
  void m_help(std::ostream &os) const final;

  /**
   * @brief Handles printing positional arguments.
   * @param os                        Output stream.
   * @param entry                     Positional entry.
   */
  void m_help(std::ostream &os, const Positional &entry) const;

  /**
   * @brief Handles showing details for a desired list.
   * @param os                        Output stream.
   * @param title                     Title to use.
   * @param list                      List of details.
   */
  void m_help(std::ostream &os, const $::String::View &title, const List &list) const;

  /**
   * @brief Gets the padding associated with a list.
   * @param list                      List to get padding of.
   */
  static inline constexpr size_t m_padding(const List &list) {
    // prepare some variables to define our padding now
    static constexpr size_t s_alignment = 8;

    // prepare our maximum to now be used
    auto maximum = m_maximum(list) + s_alignment / 2;

    // and construct the maximum padding to be used
    return maximum + s_alignment - maximum % s_alignment;
  }

  /**
   * @brief Handles comparing to entries.
   * @param a                         Entry alpha.
   * @param b                         Entry beta.
   */
  static inline bool m_compare(const Entry &a, const Entry &b) {
    return a.first.value().size() < b.first.value().size();
  }

  /**
   * @brief Gets a lists maximum entry.
   * @param list                      List to maximize.
   */
  static inline size_t m_maximum(const List &list) {
    return list.empty() ? 0 : std::max_element(list.cbegin(), list.cend(), m_compare)->first.value().size();
  }
};

} // namespace Shell::Command

#endif
