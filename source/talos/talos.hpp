#ifndef _TALOS_HPP
#define _TALOS_HPP

/// Async Modules
#include "talos/async/future.hpp"
#include "talos/async/service.hpp"
#include "talos/async/thenable.hpp"
#include "talos/async/worker.hpp"

/// Builtin Modules
#include "talos/builtins/adapter.hpp"
#include "talos/builtins/proxy.hpp"
#include "talos/builtins/service.hpp"

/// Bundle Modules
#include "talos/bundle/archive.hpp"
#include "talos/bundle/fuse.hpp"
#include "talos/bundle/service.hpp"
#include "talos/bundle/worker.hpp"

/// Bytecode Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/assembler.hpp"
#include "talos/bytecode/binder.hpp"
#include "talos/bytecode/block.hpp"
#include "talos/bytecode/compiler.hpp"
#include "talos/bytecode/instruction.hpp"
#include "talos/bytecode/invoker.hpp"
#include "talos/bytecode/label.hpp"
#include "talos/bytecode/metadata.hpp"
#include "talos/bytecode/operands.hpp"
#include "talos/bytecode/request.hpp"
#include "talos/bytecode/routine.hpp"
#include "talos/bytecode/syllable.hpp"
#include "talos/bytecode/visitor.hpp"

/// Crate Modules
#include "talos/crate/constants.hpp"
#include "talos/crate/manifest.hpp"
#include "talos/crate/service.hpp"

/// Debugger Modules
#include "talos/debugger/breakpoint.hpp"

/// Diagnostic Modules
#include "talos/diagnostic/options.hpp"
#include "talos/diagnostic/reporter.hpp"
#include "talos/diagnostic/traits.hpp"
#include "talos/diagnostic/view.hpp"

/// Document Modules
#include "talos/document/buffer.hpp"
#include "talos/document/publisher.hpp"
#include "talos/document/service.hpp"

/// Dylib Modules
#include "talos/dylib/addon.hpp"
#include "talos/dylib/proxy.hpp"
#include "talos/dylib/registry.hpp"

/// Engine Modules
#include "talos/engine/dispatch.hpp"
#include "talos/engine/exports.hpp"
#include "talos/engine/frame.hpp"
#include "talos/engine/metadata.hpp"
#include "talos/engine/register.hpp"

/// Format Modules
#include "talos/format/abstract.hpp"
#include "talos/format/comments.hpp"
#include "talos/format/dispatch.hpp"
#include "talos/format/grammar.hpp"
#include "talos/format/options.hpp"
#include "talos/format/pipeline.hpp"
#include "talos/format/reader.hpp"
#include "talos/format/storage.hpp"
#include "talos/format/wrap.hpp"
#include "talos/format/writer.hpp"

/// Garbage Modules
#include "talos/garbage/mode.hpp"
#include "talos/garbage/options.hpp"
#include "talos/garbage/service.hpp"

/// Globals Modules
#include "talos/globals/roots.hpp"
#include "talos/globals/service.hpp"

/// Handle Modules
#include "talos/handle/list.hpp"
#include "talos/handle/local.hpp"
#include "talos/handle/scope.hpp"

/// Heap Modules
#include "talos/heap/buffer.hpp"
#include "talos/heap/options.hpp"
#include "talos/heap/region.hpp"
#include "talos/heap/service.hpp"
#include "talos/heap/spaces.hpp"

/// Lifecycle Modules
#include "talos/lifecycle/service.hpp"

/// Linker Modules
#include "talos/linker/arena.hpp"
#include "talos/linker/buffer.hpp"
#include "talos/linker/records.hpp"
#include "talos/linker/view.hpp"

/// Locale Modules
#include "talos/locale/options.hpp"
#include "talos/locale/service.hpp"

/// Machine Modules
#include "talos/machine/builder.hpp"
#include "talos/machine/emitter.hpp"
#include "talos/machine/frame.hpp"
#include "talos/machine/info.hpp"
#include "talos/machine/service.hpp"
#include "talos/machine/signature.hpp"

/// Member Modules
#include "talos/member/descriptor.hpp"
#include "talos/member/property.hpp"
#include "talos/member/reference.hpp"

/// Import Modules
#include "talos/module/drafts.hpp"
#include "talos/module/dynamic.hpp"
#include "talos/module/graph.hpp"
#include "talos/module/interface.hpp"
#include "talos/module/loader.hpp"
#include "talos/module/metadata.hpp"
#include "talos/module/phase.hpp"
#include "talos/module/script.hpp"
#include "talos/module/service.hpp"

/// Lexer Modules
#include "talos/lexer/buffer.hpp"
#include "talos/lexer/dispatch.hpp"
#include "talos/lexer/generator.hpp"
#include "talos/lexer/kind.hpp"
#include "talos/lexer/scanner.hpp"
#include "talos/lexer/token.hpp"
#include "talos/lexer/traits.hpp"

/// Operator Modules
#include "talos/operator/kind.hpp"

/// Parser Modules
#include "talos/parser/delimited.hpp"
#include "talos/parser/dispatch.hpp"
#include "talos/parser/grammar.hpp"
#include "talos/parser/snapshot.hpp"
#include "talos/parser/stream.hpp"

/// Product Modules
#include "talos/product/details.hpp"
#include "talos/product/version.hpp"

/// Reflection Modules
#include "talos/reflect/category.hpp"

/// Relint Modules
#include "talos/relint/analyzer.hpp"
#include "talos/relint/context.hpp"
#include "talos/relint/hooks.hpp"
#include "talos/relint/metadata.hpp"
#include "talos/relint/options.hpp"
#include "talos/relint/rule.hpp"
#include "talos/relint/service.hpp"
#include "talos/relint/visitor.hpp"

/// Resource Modules
#include "talos/resource/frame.hpp"
#include "talos/resource/location.hpp"
#include "talos/resource/path.hpp"
#include "talos/resource/scheme.hpp"
#include "talos/resource/trace.hpp"

/// Runtime Modules
#include "talos/runtime/allocator.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/executor.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/runtime/main.hpp"
#include "talos/runtime/options.hpp"
#include "talos/runtime/service.hpp"

/// Server Modules
#include "talos/server/connection.hpp"
#include "talos/server/events.hpp"
#include "talos/server/options.hpp"
#include "talos/server/transport.hpp"

/// Shape Modules
#include "talos/shape/limits.hpp"
#include "talos/shape/lookup.hpp"
#include "talos/shape/service.hpp"

/// Signal Modules
#include "talos/signal/service.hpp"

/// Syntax Modules
#include "talos/syntax/comparator.hpp"
#include "talos/syntax/grammar.hpp"
#include "talos/syntax/metadata.hpp"
#include "talos/syntax/node.hpp"
#include "talos/syntax/precedence.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/syntax/visitor.hpp"

/// Testing Modules
#include "talos/testing/main.hpp"
#include "talos/testing/options.hpp"
#include "talos/testing/registry.hpp"
#include "talos/testing/service.hpp"
#include "talos/testing/traits.hpp"

/// Toolchain Modules
#include "talos/toolchain/audit.hpp"
#include "talos/toolchain/bundle.hpp"
#include "talos/toolchain/compile.hpp"
#include "talos/toolchain/format.hpp"
#include "talos/toolchain/launch.hpp"
#include "talos/toolchain/parse.hpp"
#include "talos/toolchain/serve.hpp"
#include "talos/toolchain/test.hpp"

/// Type Modules
#include "talos/type/_inline/type.ipp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

/// Variable Modules
#include "talos/variable/captures.hpp"
#include "talos/variable/modifiers.hpp"

#endif
