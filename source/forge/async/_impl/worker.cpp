/// Forge Modules
#include "forge/async/worker.hpp"
#include "forge/engine/dispatch.hpp"

//  PRIVATE METHODS  //

void Forge::Async::Worker::m_execute() {
    // prepare a local scoping to be used
    auto local_scope = scope();

    // get the details about the future instance
    auto local_future = local_scope(m_data.as<Async::Future>());
    if (local_future->m_attrs()->worker == nullptr) return;

    // destructure the callback and details to be used
    auto* local_thenable = local_future->thenable();
    const auto& local_arguments = local_future->arguments();
    auto local_callback = local_scope(local_future->callback());

    // attempt running the future callback now
    auto retval = invoke(*local_callback, local_arguments);

    // detach the underlying worker instance now
    local_future->m_attrs()->worker = nullptr;

    // declare the details about the instance now
    if (retval.traits().okay()) local_thenable->resolve(this, retval);
    else local_thenable->reject(this, m_exception);  // failure here
}
