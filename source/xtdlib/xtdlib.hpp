#ifndef _XTDLIB_HPP
#define _XTDLIB_HPP

/// Allocator Modules
#include "xtdlib/allocator/category.hpp"
#include "xtdlib/allocator/object.hpp"
#include "xtdlib/allocator/policy.hpp"
#include "xtdlib/allocator/record.hpp"
#include "xtdlib/allocator/standard.hpp"
#include "xtdlib/allocator/tracker.hpp"

/// Async Modules
#include "xtdlib/async/atomic.hpp"
#include "xtdlib/async/latch.hpp"
#include "xtdlib/async/signaller.hpp"

/// Blob Modules
#include "xtdlib/blob/buffer.hpp"
#include "xtdlib/blob/decoder.hpp"
#include "xtdlib/blob/encoder.hpp"

/// Chrono Modules
#include "xtdlib/chrono/clock.hpp"
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/chrono/measure.hpp"
#include "xtdlib/chrono/point.hpp"

/// Container Modules
#include "xtdlib/container/each.hpp"
#include "xtdlib/container/filter.hpp"
#include "xtdlib/container/map.hpp"
#include "xtdlib/container/ranges.hpp"
#include "xtdlib/container/set.hpp"

/// Debug Modules
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/debug/location.hpp"
#include "xtdlib/debug/logger.hpp"
#include "xtdlib/debug/printable.hpp"

/// Encoding Modules
#include "xtdlib/encoding/ascii.hpp"
#include "xtdlib/encoding/hex.hpp"
#include "xtdlib/encoding/utf8.hpp"

/// Enum Modules
#include "xtdlib/enum/class.hpp"
#include "xtdlib/enum/flags.hpp"

/// Filesystem Modules
#include "xtdlib/filesystem/chmod.hpp"
#include "xtdlib/filesystem/compare.hpp"
#include "xtdlib/filesystem/iterator.hpp"
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/filesystem/read.hpp"
#include "xtdlib/filesystem/unique.hpp"
#include "xtdlib/filesystem/write.hpp"

/// Functor Modules
#include "xtdlib/functor/defer.hpp"
#include "xtdlib/functor/shared.hpp"
#include "xtdlib/functor/traits.hpp"
#include "xtdlib/functor/unique.hpp"

/// Glob Modules
#include "xtdlib/glob/match.hpp"
#include "xtdlib/glob/pattern.hpp"

/// IO Modules
#include "xtdlib/io/print.hpp"

/// Macro Modules
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/macros/processor.hpp"

/// Manipulator Modules
#include "xtdlib/manip/indent.hpp"

/// Math Modules
#include "xtdlib/math/saturation.hpp"

/// Memory Modules
#include "xtdlib/memory/constants.hpp"
#include "xtdlib/memory/mapping.hpp"

/// Mutex Modules
#include "xtdlib/mutex/guard.hpp"
#include "xtdlib/mutex/light.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"

/// Pointer Modules
#include "xtdlib/pointer/auto.hpp"
#include "xtdlib/pointer/new.hpp"
#include "xtdlib/pointer/proxy.hpp"
#include "xtdlib/pointer/shared.hpp"
#include "xtdlib/pointer/unique.hpp"

/// RNG Modules
#include "xtdlib/random/interface.hpp"
#include "xtdlib/random/simple.hpp"

/// RTTI Modules
#include "xtdlib/rtti/dynamic.hpp"
#include "xtdlib/rtti/hash.hpp"
#include "xtdlib/rtti/name.hpp"

/// Serde Modules
#include "xtdlib/serde/codec.hpp"
#include "xtdlib/serde/json.hpp"
#include "xtdlib/serde/reflect.hpp"
#include "xtdlib/serde/value.hpp"

/// Spinner Modules
#include "xtdlib/spinner/abstract.hpp"
#include "xtdlib/spinner/frames.hpp"
#include "xtdlib/spinner/options.hpp"

/// Stream Modules
#include "xtdlib/stream/color.hpp"
#include "xtdlib/stream/setup.hpp"
#include "xtdlib/stream/types.hpp"

/// String Modules
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/convert.hpp"
#include "xtdlib/string/literal.hpp"
#include "xtdlib/string/stream.hpp"
#include "xtdlib/string/trim.hpp"
#include "xtdlib/string/view.hpp"

/// Strong Modules
#include "xtdlib/strong/infer.hpp"
#include "xtdlib/strong/unit.hpp"

/// System Modules
#include "xtdlib/system/abort.hpp"
#include "xtdlib/system/architecture.hpp"
#include "xtdlib/system/constants.hpp"
#include "xtdlib/system/debugbreak.hpp"
#include "xtdlib/system/environment.hpp"
#include "xtdlib/system/executable.hpp"
#include "xtdlib/system/exit.hpp"
#include "xtdlib/system/information.hpp"
#include "xtdlib/system/platform.hpp"
#include "xtdlib/system/unreachable.hpp"

/// Terminal Modules
#include "xtdlib/terminal/ansi.hpp"
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/terminal/dye.hpp"

/// Thread Modules
#include "xtdlib/thread/handle.hpp"
#include "xtdlib/thread/limits.hpp"

/// Trait Modules
#include "xtdlib/traits/concepts.hpp"
#include "xtdlib/traits/copyable.hpp"
#include "xtdlib/traits/movable.hpp"
#include "xtdlib/traits/newable.hpp"
#include "xtdlib/traits/sequence.hpp"
#include "xtdlib/traits/unqualified.hpp"

/// URI Modules
#include "xtdlib/uri/alias.hpp"
#include "xtdlib/uri/buffer.hpp"
#include "xtdlib/uri/codec.hpp"
#include "xtdlib/uri/scheme.hpp"
#include "xtdlib/uri/view.hpp"

/// Utility Modules
#include "xtdlib/utility/global.hpp"
#include "xtdlib/utility/never.hpp"
#include "xtdlib/utility/singleton.hpp"
#include "xtdlib/utility/ternary.hpp"

/// Union Modules
#include "xtdlib/union/aligned.hpp"

#endif
