/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_vardef(XLSP_REQUEST(DOCUMENT_VARIABLE_DEFINITION) request) { request.cancel(); }
void Talos::Server::Events::on_document_typedef(XLSP_REQUEST(DOCUMENT_TYPE_DEFINITION) request) { request.cancel(); }
