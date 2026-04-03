/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_completes(XLSP_REQUEST(DOCUMENT_COMPLETIONS) request) { request.cancel(); }
