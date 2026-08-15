/// Shell Includes
#include "shell/validators/duration.hpp"

//  PRIVATE METHODS  //

$::String::Buffer Shell::Validator::Duration::m_transform($::String::Buffer &input) {
  CLI::detail::rtrim(input); // ensure we trim the input beforehand
  if (input.empty()) throw CLI::ValidationError("Input is empty");

  auto start = input.end(); // attempt finding the starting point of the unit
  while (start > input.begin() && std::isalpha(*(start - 1), std::locale())) --start;

  $::String::Buffer unit = $::Convert::lowercase({start, input.end()});
  input.resize(std::distance(input.begin(), start)); // resize the input

  // prepare the baseline duration to be used
  int64_t duration = {}, multiplier = $::Chrono::Multiplier(unit);

  // attempt casting to a suitably duration now
  auto success = CLI::detail::lexical_cast(input, duration);

  // if the unit is empty, then resolve in milliseconds
  if (!success) throw CLI::ValidationError("Value " + input + " could not be converted to TIME [UNIT]");
  if (multiplier < 0) throw CLI::ValidationError("Unit '" + unit + "' not recognized"); // invalid

  // since validly converted, then apply the multiplication and return as a stringified value
  input = CLI::detail::to_string(duration * multiplier);

  // and declare that no errors occured now
  return {};
}
