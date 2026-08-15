/// XSIO Includes
#include "xsio/timer/token.hpp"
#include "xsio/async/scheduler.hpp"

//  PRIVATE METHODS  //

bool XSIO::Timer::Token::m_cancel() const noexcept {
  if (m_scheduler == nullptr) return false; // declare as invalid if no scheduler bound
  auto predicate = [this](const auto &processor) { return processor->timers()->cancel(m_id); };
  return std::ranges::any_of(m_scheduler->processors(), predicate); // attempts cancelling the timer
}
