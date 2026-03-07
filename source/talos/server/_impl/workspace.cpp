/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_workspace_watcher(const XLSP_NOTIFICATION(WORKSPACE_FILE_CHANGED) & params) {
    // ignore if there are no changes that occured
    if (params.changes.empty()) return;

    // for now we just want to schedule a re-analysis of our project
    m_connection->schedule([](Worker* worker) { worker->analyze(true); });
}
