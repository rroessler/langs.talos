/// XLSP Includes
#include "xlsp/server/connection.hpp"
#include "xlsp/transport/console.hpp"

//  CONSTRUCTORS  //

XLSP::Server::Connection::Connection(const Options &options) :
    Connection($::Unique::New<Transport::Console>(), options) {}

XLSP::Server::Connection::Connection($::Unique::Pointer<Transport::Abstract> &&transport, const Options &options) :
    m_options(options), m_transport(std::move(transport)) {}

//  PRIVATE METHODS  //

$::String::Buffer XLSP::Server::Connection::m_bind(Event::Answer &&reply) {
  // prepare the necessary identifier to be used
  auto identifier = fmt::to_string(++m_events->identifier);

  // get the maximum queue threshold
  const auto threshold = m_options.events.threshold;

  // prepare a response handler for missing replies
  std::optional<Event::Storage::Pending> pending = std::nullopt;

  // ensure no other calls can be made whilst we bind a response
  auto lock = $::Lock::scope(m_events->mutex.reply);

  // emplace the necessary callback to be used now
  m_events->responses.emplace_back(identifier, std::move(reply));

  // if the queue overflows, we assume the client did not reply
  if (m_events->responses.size() > threshold) {
    pending = std::move(m_events->responses.front()); // get the pending request now
    $_ERROR("More than {0} outstanding LSP requests, forgetting about {1}", threshold, pending->identifier);
    m_events->responses.pop_front(); // ensure the callback has now been ignored
  }

  // declare as finishing our lock region now
  lock.unlock();

  // declare an error if necessary
  if (pending.has_value()) {
    auto message = fmt::format("Failed to receive reply for request ({0})", identifier);
    pending->answer(Error(Error::Code::REQUEST_FAILED, message)); // emit the failure now
  }

  // return the resulting identifier
  return identifier;
}
