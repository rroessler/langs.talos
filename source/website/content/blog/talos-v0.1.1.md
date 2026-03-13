---
draft: true
date: 2026-12-31
title: Talos v0.1.1
author: Reuben Roessler
---

## Bug Fixes

#### Package / talos

- Moved: Some standard library crates have been renamed to simplify imports. This is primarly for performance (eg: smaller naming = faster parsing), but aimed not to remove readability.
- Moved: The core project structure around a little bit. Previously, the runtime was written under the naming convention `talos::forge`, and was exposed using a CMake interface library as `talos::talos`. Now the runtime has been moved solely into a standalone library as `talos::talos`. To then expose crate `dylib:*` module registrations with this standalone library, the identifier `talos::crates` is now used.

#### Package / vscode

- Fixed: Executable lookup now attempts to firstly find `talos` within the `$HOME/.talos` directory.

#### Toolkit / talos run

- Added: Implemented `class` statements. This includes: type-checking, instantiation, super-constructors, and interfaces.
- Added: Integrated the `NO_PROGRESS` environment variable. For more details see the [standards website](https://no-progress.org/).
- Added: Implemented the `Deprecated` attribute hook. This allows marking variables as deprecated (exposed via the type-system).
- Added: Implemented the `Operator` attribute hook foundations. This allows setting _limited_ custom operators to objects (eg: `call`, `dispose` and `iterator`).
- Added: Completed explicit resource management foundations. This includes: `use` statements, and disposal attributes.
- Began: Started the foundations for implementing a debugger. The core principle behind doing so is limited bytecode opcodes to a 7-bit value and using the most-significant to indicate that a breakpoint as been set.

#### Toolkit / talos upgrade

- Fixed: Simplified the uninstall process on Windows. Previously it used a scheduled-task, however this has been replaced with a delayed `rmdir` command invoked through a hidden separate process using the `start` command.

#### Crate / talos:ffi

- Added: Prepared stub typings for a future FFI implementation.

#### Crate / talos:gc

- Moved: Renamed the garbage collection module from `talos:garbage` to `talos:gc`.

#### Crate / talos:mem

- Moved: Renamed the virtual memory module from `talos:memory` to `talos:mem`.

#### Crate / talos:uuid

- Added: Exposed all UUID versions 1, 3, 4, 5, 6 and 7, alongside available namespace seeds.
