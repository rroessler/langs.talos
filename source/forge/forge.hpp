#ifndef _FORGE_HPP
#define _FORGE_HPP

/// Async Modules
#include "forge/async/future.hpp"
#include "forge/async/service.hpp"
#include "forge/async/thenable.hpp"
#include "forge/async/worker.hpp"

/// Builtin Modules
#include "forge/builtins/adapter.hpp"
#include "forge/builtins/proxy.hpp"
#include "forge/builtins/service.hpp"

/// Bundle Modules
#include "forge/bundle/archive.hpp"
#include "forge/bundle/fuse.hpp"
#include "forge/bundle/service.hpp"
#include "forge/bundle/worker.hpp"

/// Bytecode Modules
#include "forge/bytecode/allocator.hpp"
#include "forge/bytecode/assembler.hpp"
#include "forge/bytecode/binder.hpp"
#include "forge/bytecode/block.hpp"
#include "forge/bytecode/compiler.hpp"
#include "forge/bytecode/instruction.hpp"
#include "forge/bytecode/invoker.hpp"
#include "forge/bytecode/label.hpp"
#include "forge/bytecode/metadata.hpp"
#include "forge/bytecode/operands.hpp"
#include "forge/bytecode/request.hpp"
#include "forge/bytecode/routine.hpp"
#include "forge/bytecode/syllable.hpp"
#include "forge/bytecode/visitor.hpp"

/// Crate Modules
#include "forge/crate/constants.hpp"
#include "forge/crate/manifest.hpp"
#include "forge/crate/service.hpp"

/// Diagnostic Modules
#include "forge/diagnostic/options.hpp"
#include "forge/diagnostic/reporter.hpp"
#include "forge/diagnostic/traits.hpp"
#include "forge/diagnostic/view.hpp"

/// Document Modules
#include "forge/document/buffer.hpp"
#include "forge/document/publisher.hpp"
#include "forge/document/service.hpp"

/// Dylib Modules
#include "forge/dylib/addon.hpp"
#include "forge/dylib/proxy.hpp"
#include "forge/dylib/registry.hpp"

/// Engine Modules
#include "forge/engine/dispatch.hpp"
#include "forge/engine/exports.hpp"
#include "forge/engine/frame.hpp"
#include "forge/engine/metadata.hpp"
#include "forge/engine/register.hpp"

/// Format Modules
#include "forge/format/abstract.hpp"
#include "forge/format/comments.hpp"
#include "forge/format/dispatch.hpp"
#include "forge/format/grammar.hpp"
#include "forge/format/options.hpp"
#include "forge/format/pipeline.hpp"
#include "forge/format/reader.hpp"
#include "forge/format/storage.hpp"
#include "forge/format/wrap.hpp"
#include "forge/format/writer.hpp"

/// Garbage Modules
#include "forge/garbage/mode.hpp"
#include "forge/garbage/options.hpp"
#include "forge/garbage/service.hpp"

/// Globals Modules
#include "forge/globals/roots.hpp"
#include "forge/globals/service.hpp"

/// Handle Modules
#include "forge/handle/list.hpp"
#include "forge/handle/local.hpp"
#include "forge/handle/scope.hpp"

/// Heap Modules
#include "forge/heap/buffer.hpp"
#include "forge/heap/options.hpp"
#include "forge/heap/region.hpp"
#include "forge/heap/service.hpp"
#include "forge/heap/spaces.hpp"

/// Lifecycle Modules
#include "forge/lifecycle/service.hpp"

/// Linker Modules
#include "forge/linker/arena.hpp"
#include "forge/linker/buffer.hpp"
#include "forge/linker/records.hpp"
#include "forge/linker/view.hpp"

/// Locale Modules
#include "forge/locale/options.hpp"
#include "forge/locale/service.hpp"

/// Machine Modules
#include "forge/machine/builder.hpp"
#include "forge/machine/emitter.hpp"
#include "forge/machine/frame.hpp"
#include "forge/machine/info.hpp"
#include "forge/machine/service.hpp"
#include "forge/machine/signature.hpp"

/// Member Modules
#include "forge/member/descriptor.hpp"
#include "forge/member/property.hpp"
#include "forge/member/reference.hpp"

/// Import Modules
#include "forge/module/drafts.hpp"
#include "forge/module/dynamic.hpp"
#include "forge/module/graph.hpp"
#include "forge/module/interface.hpp"
#include "forge/module/loader.hpp"
#include "forge/module/metadata.hpp"
#include "forge/module/phase.hpp"
#include "forge/module/script.hpp"
#include "forge/module/service.hpp"

/// Lexer Modules
#include "forge/lexer/buffer.hpp"
#include "forge/lexer/dispatch.hpp"
#include "forge/lexer/generator.hpp"
#include "forge/lexer/kind.hpp"
#include "forge/lexer/scanner.hpp"
#include "forge/lexer/token.hpp"
#include "forge/lexer/traits.hpp"

/// Operator Modules
#include "forge/operator/kind.hpp"

/// Parser Modules
#include "forge/parser/delimited.hpp"
#include "forge/parser/dispatch.hpp"
#include "forge/parser/grammar.hpp"
#include "forge/parser/snapshot.hpp"
#include "forge/parser/stream.hpp"

/// Reflection Modules
#include "forge/reflect/category.hpp"

/// Relint Modules
#include "forge/relint/analyzer.hpp"
#include "forge/relint/context.hpp"
#include "forge/relint/hooks.hpp"
#include "forge/relint/metadata.hpp"
#include "forge/relint/options.hpp"
#include "forge/relint/rule.hpp"
#include "forge/relint/service.hpp"
#include "forge/relint/visitor.hpp"

/// Resource Modules
#include "forge/resource/frame.hpp"
#include "forge/resource/location.hpp"
#include "forge/resource/path.hpp"
#include "forge/resource/scheme.hpp"
#include "forge/resource/trace.hpp"

/// Runtime Modules
#include "forge/runtime/allocator.hpp"
#include "forge/runtime/container.hpp"
#include "forge/runtime/executor.hpp"
#include "forge/runtime/isolate.hpp"
#include "forge/runtime/main.hpp"
#include "forge/runtime/options.hpp"
#include "forge/runtime/service.hpp"

/// Server Modules
#include "forge/server/connection.hpp"
#include "forge/server/events.hpp"
#include "forge/server/options.hpp"
#include "forge/server/transport.hpp"

/// Shape Modules
#include "forge/shape/limits.hpp"
#include "forge/shape/lookup.hpp"
#include "forge/shape/service.hpp"

/// Signal Modules
#include "forge/signal/service.hpp"

/// Syntax Modules
#include "forge/syntax/comparator.hpp"
#include "forge/syntax/grammar.hpp"
#include "forge/syntax/metadata.hpp"
#include "forge/syntax/node.hpp"
#include "forge/syntax/precedence.hpp"
#include "forge/syntax/tree.hpp"
#include "forge/syntax/visitor.hpp"

/// Testing Modules
#include "forge/testing/main.hpp"
#include "forge/testing/options.hpp"
#include "forge/testing/registry.hpp"
#include "forge/testing/service.hpp"
#include "forge/testing/traits.hpp"

/// Toolchain Modules
#include "forge/toolchain/audit.hpp"
#include "forge/toolchain/bundle.hpp"
#include "forge/toolchain/compile.hpp"
#include "forge/toolchain/format.hpp"
#include "forge/toolchain/launch.hpp"
#include "forge/toolchain/parse.hpp"
#include "forge/toolchain/serve.hpp"
#include "forge/toolchain/test.hpp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

/// Variable Modules
#include "forge/variable/captures.hpp"
#include "forge/variable/modifiers.hpp"

#endif
