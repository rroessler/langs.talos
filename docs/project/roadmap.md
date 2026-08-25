---
icon: Map
title: Roadmap
description: A brief outline of the current bug-fixes, goals and other milestones for Talos
---

### Legend

| Status | Description                    |
| :----: | ------------------------------ |
|   ❌   | Not yet implemented            |
|   🚀   | Currently being developed      |
|   💀   | Has bare-bones implementation  |
|   ⚪   | Finished but needs revising    |
|   ✅   | Finished and ready for release |

## Runtime

| Status | Feature | Description                          | Todo                    |
| :----: | ------- | ------------------------------------ | ----------------------- |
|   💀   | `@...`  | Implement runtime decorators.        | Needs better typing     |
|   💀   | `#...`  | Implement compile-time attributes.   | Overloads not yet done  |
|   ✅   | `use`   | Implement explicit resources.        | -                       |
|   ✅   | `enum`  | Implement enumeration declarations.  | -                       |
|   ⚪   | `class` | Implement class-based inheritance.   | Needs a testing suite   |
|   ⚪   | `match` | Implement `match` statements.        | Needs better typing     |
|   ❌   | `Debug` | Implement debug `breakpoint` method. | Implement a DAP manager |

## Testing

| Status | Suite              | Description                 | Todo       |
| :----: | ------------------ | --------------------------- | ---------- |
|   🚀   | `builtins/list`    | Testing of `List` builtin   | Stubs only |
|   🚀   | `builtins/number`  | Testing of `Number` builtin | Stubs only |
|   🚀   | `builtins/result`  | Testing of `Result` builtin | Stubs only |
|   🚀   | `builtins/string`  | Testing of `String` builtin | Stubs only |
|   🚀   | `syntax/class`     | Testing of `class` syntax   | -          |
|   🚀   | `syntax/enum`      | Testing of `enum` syntax    | -          |
|   🚀   | `syntax/match`     | Testing of `match` syntax   | -          |
|   🚀   | `syntax/use`       | Testing of `use` syntax     | -          |
|   🚀   | `syntax/attribute` | Testing of `#...` syntax    | -          |
|   🚀   | `syntax/decorator` | Testing of `@...` syntax    | -          |

## Libraries

| Status | Library        | Description                     | Todo                           |
| :----: | -------------- | ------------------------------- | ------------------------------ |
|   ✅   | `talos:assert` | Assertion library methods.      | Additional methods?            |
|   ❌   | `talos:async`  | Asynchronous utilities.         | -                              |
|   ❌   | `talos:chrono` | Temporal utilities.             | -                              |
|   ❌   | `talos:codec`  | Encoding/decoding function.     | -                              |
|   ❌   | `talos:ffi`    | Native library utilities.       | -                              |
|   ❌   | `talos:fsys`   | Filesystem utilities.           | -                              |
|   ✅   | `talos:gc`     | Garbage collection hooks.       | Additional statistics?         |
|   🚀   | `talos:json`   | JSON/JSONC parsing/serializing. | -                              |
|   ❌   | `talos:lint`   | Linting plugin bindings.        | -                              |
|   ❌   | `talos:math`   | Mathematics utilities.          | -                              |
|   ⚪   | `talos:mem`    | Virtual memory utilities.       | Buffers, allocators, ...       |
|   ❌   | `talos:path`   | Filesystem path utilities.      | -                              |
|   ❌   | `talos:rng`    | Random number generators.       | -                              |
|   ⚪   | `talos:test`   | Testing suite framework.        | Skipping, lifecycle hooks, ... |
|   🚀   | `talos:toml`   | TOML parsing/serializing.       | -                              |
|   ✅   | `talos:uuid`   | UUID generators/validators.     | Should there be a validator?   |
|   🚀   | `talos:yaml`   | YAML parsing/serializing.       | -                              |

## Tooling

| Status | Label     | Description                               | Todo                          |
| :----: | --------- | ----------------------------------------- | ----------------------------- |
|   ✅   | `run`     | Handles starting runtimes.                | See: [Runtime](#runtime)      |
|   ✅   | `test`    | Handles running unit-tests.               | See: [Libraries](#libraries)  |
|   ✅   | `task`    | Executes pre-defined crate tasks.         | Parallel workspaces?          |
|   💀   | `lint`    | Runs extra analysis of scripts/projects.  | Recommended rules, plugins?   |
|   ⚪   | `bundle`  | Packages scripts/projects in executables. | Requires codesigning (Win32)  |
|   ✅   | `format`  | Formats scripts with a builtin styler.    | More configurable options     |
|   ✅   | `serve`   | Starts a language-server instance.        | Code completion is missing    |
|   ✅   | `upgrade` | Upgrades to the latest version of Talos.  | Needs a release to fully test |

## Documentation

| Status | Section   | Description                          |
| :----: | --------- | ------------------------------------ |
|   ⚪   | Blog      | Still need to implement `feed.xml`   |
|   ⚪   | Crates    | Only stub pages have been made.      |
|   ⚪   | Builtins  | Only stub pages have been made.      |
|   ⚪   | Language  | Fundamentals, advanced concepts, ... |
|   ⚪   | Project   | Contribution points, dashboard, ...  |
|   💀   | Proposals | Only a baseline specification, ...   |
|   ⚪   | Tour      | Some steps are not yet finished.     |
