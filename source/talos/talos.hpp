#ifndef _TALOS_HPP
#define _TALOS_HPP

/// Talos Modules
#include "talos/bundle/forward.hpp"
#include "talos/crate/forward.hpp"
#include "talos/diagnostic/forward.hpp"
#include "talos/document/forward.hpp"
#include "talos/engine/forward.hpp"
#include "talos/format/forward.hpp"
#include "talos/fuse/forward.hpp"
#include "talos/lexer/forward.hpp"
#include "talos/product/forward.hpp"
#include "talos/runtime/forward.hpp"
#include "talos/server/forward.hpp"
#include "talos/syntax/forward.hpp"
#include "talos/toolchain/forward.hpp"
#include "talos/type/forward.hpp"
#include "talos/value/forward.hpp"

//  MACROS  //

#define TALOS_MM_TITLE FORGE_MM_TITLE
#define TALOS_MM_COMMIT FORGE_MM_COMMIT
#define TALOS_MM_VERSION FORGE_MM_VERSION
#define TALOS_MM_REVISION TALOS_MM_VERSION "+" TALOS_MM_COMMIT
#define TALOS_MM_IDENTIFIER FORGE_MM_IDENTIFIER
#define TALOS_XX_VENDORS FORGE_XX_VENDOR_VERSIONS

#endif
