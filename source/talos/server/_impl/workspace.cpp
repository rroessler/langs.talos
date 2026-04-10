/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_workspace_watcher(const XLSP_NOTIFICATION(WORKSPACE_FILE_CHANGED) & params) {
    if (params.changes.size()) m_connection->analyze();  // only force a re-analysis to occur if changes
}
