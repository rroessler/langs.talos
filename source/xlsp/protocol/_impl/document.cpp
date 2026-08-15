/// XLSP Includes
#include "xlsp/protocol/document.hpp"

//  PUBLIC METHODS  //

void XLSP::Document::Change::apply($::String::Buffer &content, const Encoding::Type &encoding) const {
  // update the content if no range given
  if (range == std::nullopt) return $_PP_IGN(content = text);

  // attempt inferring a starting offset now
  auto start = range->start.offset(content, encoding);
  auto end = range->end.offset(content, encoding);

  // stop if our offsets are invalid or bad arrangement
  if (start < 0 || end < 0 || end < start) return;

  // and replace the contents as necessary now
  content.replace(start, end - start, text);
}
