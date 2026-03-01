#ifndef _XLSP_HPP
#define _XLSP_HPP

/// Event Modules
#include "xlsp/event/binder.hpp"
#include "xlsp/event/dispatcher.hpp"
#include "xlsp/event/responder.hpp"
#include "xlsp/event/storage.hpp"

/// Message Modules
#include "xlsp/message/document.hpp"
#include "xlsp/message/error.hpp"
#include "xlsp/message/json.hpp"
#include "xlsp/message/lifecycle.hpp"
#include "xlsp/message/notification.hpp"
#include "xlsp/message/publish.hpp"
#include "xlsp/message/request.hpp"
#include "xlsp/message/special.hpp"
#include "xlsp/message/trace.hpp"
#include "xlsp/message/traits.hpp"
#include "xlsp/message/workspace.hpp"

/// Protocol Modules
#include "xlsp/protocol/diagnostic.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/encoding.hpp"
#include "xlsp/protocol/format.hpp"
#include "xlsp/protocol/location.hpp"
#include "xlsp/protocol/markup.hpp"
#include "xlsp/protocol/position.hpp"
#include "xlsp/protocol/process.hpp"
#include "xlsp/protocol/range.hpp"
#include "xlsp/protocol/trace.hpp"

/// Server Modules
#include "xlsp/server/connection.hpp"
#include "xlsp/server/options.hpp"

/// Transport Modules
#include "xlsp/transport/abstract.hpp"
#include "xlsp/transport/console.hpp"
#include "xlsp/transport/stream.hpp"

/// Workspace Modules
#include "xlsp/workspace/file.hpp"
#include "xlsp/workspace/folder.hpp"

#endif
