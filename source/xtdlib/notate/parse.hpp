#ifndef _XTDLIB_NOTATE_PARSE_HPP
#define _XTDLIB_NOTATE_PARSE_HPP

/// Library Includes
#include "xtdlib/notate/section.hpp"

namespace $::Notate {

/**
 * @brief Handles parsing annotated documentation.
 * @param block                     Content to parse.
 * @param options                   Parsing options.
 */
Block Parse(const String::View &block, const Options &options = {});

/**
 * @brief Handles parsing annotated documentation.
 * @param segments                  Content to parse.
 * @param options                   Parsing options.
 */
Block Parse(const Segments &segments, const Options &options = {});
Block Parse(const std::vector<String::Buffer> &segments, const Options &options = {});

} // namespace $::Notate

#endif
