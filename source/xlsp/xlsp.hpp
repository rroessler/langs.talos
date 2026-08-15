#ifndef _XLSP_HPP
#define _XLSP_HPP

/// Event Includes
#include "xlsp/event/binder.hpp"
#include "xlsp/event/emitter.hpp"
#include "xlsp/event/storage.hpp"

/// Message Includes
#include "xlsp/message/channel.hpp"
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"

/// Parameters Includes
#include "xlsp/params/_inline/params.ipp"

/// Protocol Includes
#include "xlsp/protocol/anchor.hpp"
#include "xlsp/protocol/completion.hpp"
#include "xlsp/protocol/diagnostic.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/encoding.hpp"
#include "xlsp/protocol/error.hpp"
#include "xlsp/protocol/format.hpp"
#include "xlsp/protocol/markup.hpp"
#include "xlsp/protocol/position.hpp"
#include "xlsp/protocol/process.hpp"
#include "xlsp/protocol/range.hpp"
#include "xlsp/protocol/reference.hpp"
#include "xlsp/protocol/symbol.hpp"
#include "xlsp/protocol/trace.hpp"
#include "xlsp/protocol/workspace.hpp"

/// Server Includes
#include "xlsp/server/connection.hpp"
#include "xlsp/server/options.hpp"

/// Transport Includes
#include "xlsp/transport/abstract.hpp"
#include "xlsp/transport/console.hpp"
#include "xlsp/transport/stream.hpp"

#endif
