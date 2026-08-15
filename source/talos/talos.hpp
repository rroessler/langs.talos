#ifndef _TALOS_HPP
#define _TALOS_HPP

/// Async Includes
#include "talos/async/_inline/async.ipp"

/// Bundle Includes
#include "talos/bundle/archive.hpp"
#include "talos/bundle/codec.hpp"
#include "talos/bundle/fuse.hpp"
#include "talos/bundle/options.hpp"
#include "talos/bundle/service.hpp"
#include "talos/bundle/worker.hpp"

/// Builtin Includes
#include "talos/builtins/adapter.hpp"
#include "talos/builtins/inspect.hpp"
#include "talos/builtins/storage.hpp"
#include "talos/builtins/wrapper.hpp"

/// Bytecode Includes
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/assembler.hpp"
#include "talos/bytecode/binder.hpp"
#include "talos/bytecode/block.hpp"
#include "talos/bytecode/compiler.hpp"
#include "talos/bytecode/disposable.hpp"
#include "talos/bytecode/glyph.hpp"
#include "talos/bytecode/instruction.hpp"
#include "talos/bytecode/invoker.hpp"
#include "talos/bytecode/iterator.hpp"
#include "talos/bytecode/label.hpp"
#include "talos/bytecode/loop.hpp"
#include "talos/bytecode/metadata.hpp"
#include "talos/bytecode/operands.hpp"
#include "talos/bytecode/optimizer.hpp"
#include "talos/bytecode/request.hpp"
#include "talos/bytecode/routine.hpp"
#include "talos/bytecode/trace.hpp"
#include "talos/bytecode/visitor.hpp"

/// Crate Includes
#include "talos/crate/constants.hpp"
#include "talos/crate/manifest.hpp"
#include "talos/crate/registry.hpp"

/// Diagnostic Includes
#include "talos/diagnostic/inspect.hpp"
#include "talos/diagnostic/options.hpp"
#include "talos/diagnostic/reporter.hpp"
#include "talos/diagnostic/scope.hpp"
#include "talos/diagnostic/view.hpp"

/// Document Includes
#include "talos/document/buffer.hpp"
#include "talos/document/publisher.hpp"
#include "talos/document/service.hpp"

/// Engine Includes
#include "talos/engine/dispatch.hpp"
#include "talos/engine/exports.hpp"
#include "talos/engine/frame.hpp"
#include "talos/engine/interrupt.hpp"
#include "talos/engine/invoke.hpp"
#include "talos/engine/metadata.hpp"
#include "talos/engine/operand.hpp"

/// Flow Includes
#include "talos/flow/control.hpp"
#include "talos/flow/effect.hpp"
#include "talos/flow/passable.hpp"
#include "talos/flow/unreachable.hpp"

/// Format Includes
#include "talos/format/collection.hpp"
#include "talos/format/comments.hpp"
#include "talos/format/delimited.hpp"
#include "talos/format/dispatch.hpp"
#include "talos/format/mixin.hpp"
#include "talos/format/options.hpp"
#include "talos/format/pipeline.hpp"
#include "talos/format/reader.hpp"
#include "talos/format/storage.hpp"
#include "talos/format/wrap.hpp"
#include "talos/format/writer.hpp"

/// Garbage Includes
#include "talos/garbage/lifetimes.hpp"
#include "talos/garbage/marker.hpp"
#include "talos/garbage/mode.hpp"
#include "talos/garbage/options.hpp"
#include "talos/garbage/service.hpp"

/// Globals Includes
#include "talos/globals/roots.hpp"
#include "talos/globals/service.hpp"

/// Handle Includes
#include "talos/handle/local.hpp"
#include "talos/handle/scope.hpp"
#include "talos/handle/stack.hpp"

/// Heap Includes
#include "talos/heap/buffer.hpp"
#include "talos/heap/limits.hpp"
#include "talos/heap/options.hpp"
#include "talos/heap/region.hpp"
#include "talos/heap/service.hpp"
#include "talos/heap/storage.hpp"

/// Image Includes
#include "talos/image/arena.hpp"
#include "talos/image/binary.hpp"
#include "talos/image/records.hpp"
#include "talos/image/slice.hpp"

/// Import Includes
#include "talos/import/graph.hpp"
#include "talos/import/loader.hpp"
#include "talos/import/service.hpp"
#include "talos/import/storage.hpp"
#include "talos/import/worker.hpp"

/// Lexer Includes
#include "talos/lexer/buffer.hpp"
#include "talos/lexer/dispatch.hpp"
#include "talos/lexer/inspect.hpp"
#include "talos/lexer/kind.hpp"
#include "talos/lexer/options.hpp"
#include "talos/lexer/scanner.hpp"
#include "talos/lexer/token.hpp"
#include "talos/lexer/visitor.hpp"

/// Lifecycle Includes
#include "talos/lifecycle/scope.hpp"
#include "talos/lifecycle/service.hpp"

/// Locale Includes
#include "talos/locale/options.hpp"
#include "talos/locale/service.hpp"

/// Machine Includes
#include "talos/machine/allocator.hpp"
#include "talos/machine/builder.hpp"
#include "talos/machine/constants.hpp"
#include "talos/machine/emitter.hpp"
#include "talos/machine/facts.hpp"
#include "talos/machine/frame.hpp"
#include "talos/machine/info.hpp"
#include "talos/machine/logger.hpp"
#include "talos/machine/service.hpp"
#include "talos/machine/visitor.hpp"

/// Member Includes
#include "talos/member/descriptor.hpp"
#include "talos/member/factory.hpp"
#include "talos/member/property.hpp"
#include "talos/member/reference.hpp"
#include "talos/member/storage.hpp"

/// Module Includes
#include "talos/module/abstract.hpp"
#include "talos/module/archive.hpp"
#include "talos/module/dynamic.hpp"
#include "talos/module/metadata.hpp"
#include "talos/module/phase.hpp"
#include "talos/module/script.hpp"

/// Operator Includes
#include "talos/operator/attribute.hpp"
#include "talos/operator/inspect.hpp"
#include "talos/operator/kind.hpp"
#include "talos/operator/storage.hpp"

/// Parser Includes
#include "talos/parser/delimited.hpp"
#include "talos/parser/dispatch.hpp"
#include "talos/parser/snapshot.hpp"
#include "talos/parser/stream.hpp"

/// Product Includes
#include "talos/product/details.hpp"
#include "talos/product/semver.hpp"

/// Reflect Includes
#include "talos/reflect/category.hpp"
#include "talos/reflect/inspect.hpp"

/// Relint Includes
#include "talos/relint/context.hpp"
#include "talos/relint/exports.hpp"
#include "talos/relint/hooks.hpp"
#include "talos/relint/mirror.hpp"
#include "talos/relint/options.hpp"
#include "talos/relint/rule.hpp"
#include "talos/relint/scope.hpp"
#include "talos/relint/service.hpp"

/// Register Includes
#include "talos/register/scoped.hpp"
#include "talos/register/slot.hpp"
#include "talos/register/span.hpp"

/// Resource Includes
#include "talos/resource/frame.hpp"
#include "talos/resource/location.hpp"
#include "talos/resource/scheme.hpp"
#include "talos/resource/trace.hpp"

/// Runtime Includes
#include "talos/runtime/allocator.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/entry.hpp"
#include "talos/runtime/executor.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/runtime/options.hpp"

/// Server Includes
#include "talos/server/connection.hpp"
#include "talos/server/events.hpp"
#include "talos/server/options.hpp"
#include "talos/server/style.hpp"
#include "talos/server/transport.hpp"
#include "talos/server/utilities.hpp"
#include "talos/server/worker.hpp"

/// Shape Includes
#include "talos/shape/limits.hpp"
#include "talos/shape/lookup.hpp"
#include "talos/shape/service.hpp"

/// Signal Includes
#include "talos/signal/service.hpp"

/// Syntax Includes
#include "talos/syntax/bounds.hpp"
#include "talos/syntax/comparator.hpp"
#include "talos/syntax/grammar.hpp"
#include "talos/syntax/metadata.hpp"
#include "talos/syntax/node.hpp"
#include "talos/syntax/precedence.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/syntax/trivia.hpp"
#include "talos/syntax/visitor.hpp"

/// Testing Includes
#include "talos/testing/entry.hpp"
#include "talos/testing/inspect.hpp"
#include "talos/testing/options.hpp"
#include "talos/testing/service.hpp"
#include "talos/testing/storage.hpp"

/// Toolchain Includes
#include "talos/toolchain/bundle.hpp"
#include "talos/toolchain/format.hpp"
#include "talos/toolchain/launch.hpp"
#include "talos/toolchain/parse.hpp"
#include "talos/toolchain/serve.hpp"
#include "talos/toolchain/test.hpp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Value Includes
#include "talos/value/_inline/value.ipp"

/// Variable Includes
#include "talos/variable/analyzer.hpp"
#include "talos/variable/captures.hpp"
#include "talos/variable/modifiers.hpp"
#include "talos/variable/scope.hpp"
#include "talos/variable/upvalues.hpp"
#include "talos/variable/visitor.hpp"

#endif
