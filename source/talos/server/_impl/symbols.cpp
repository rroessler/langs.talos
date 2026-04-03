/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_symbols(XLSP_REQUEST(DOCUMENT_SYMBOLS) request) { request.cancel(); }
