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

| Status | Feature | Description                             | Todo                     |
| :----: | ------- | --------------------------------------- | ------------------------ |
|   ❌   | `@...`  | Implement runtime decorators.           | -                        |
|   ❌   | `#...`  | Implement compile-time attributes.      | -                        |
|   🚀   | `use`   | Implement explicit resources.           | Requires attribute hooks |
|   ⚪   | `enum`  | Implement enumeration declarations.     | -                        |
|   💀   | `class` | Implement class-based inheritance.      | -                        |
|   💀   | `xasm`  | Implement jitted runtime functions.     | -                        |
|   💀   | `Debug` | Implement debugger `breakpoint` method. | Implement a DAP manager  |

## Libraries

| Status | Library        | Description                     | Todo                           |
| :----: | -------------- | ------------------------------- | ------------------------------ |
|   ✅   | `talos:assert` | Assertion library methods.      | Additional methods?            |
|   ❌   | `talos:async`  | Asynchronous utilities.         | -                              |
|   ❌   | `talos:chrono` | Temporal utilities.             | -                              |
|   ❌   | `talos:codec`  | Encoding/decoding function.     | -                              |
|   🚀   | `talos:ffi`    | Native library utilities.       | -                              |
|   ❌   | `talos:fsys`   | Filesystem utilities.           | -                              |
|   ✅   | `talos:gc`     | Garbage collection hooks.       | Additional statistics?         |
|   💀   | `talos:jit`    | Experimental JIT hooks.         | -                              |
|   🚀   | `talos:json`   | JSON/JSONC parsing/serializing. | -                              |
|   ❌   | `talos:math`   | Mathematics utilities.          | -                              |
|   ⚪   | `talos:mem`    | Virtual memory utilities.       | Buffers, allocators, ...       |
|   ❌   | `talos:path`   | Filesystem path utilities.      | -                              |
|   ❌   | `talos:rng`    | Random number generators.       | -                              |
|   ⚪   | `talos:test`   | Testing suite framework.        | Skipping, lifecycle hooks, ... |
|   🚀   | `talos:toml`   | TOML parsing/serializing.       | -                              |
|   ✅   | `talos:uuid`   | UUID generators/validators.     | Show there be a validator?     |
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
|   ⚪   | `serve`   | Starts a language-server instance.        | More code-editor features     |
|   ⚪   | `upgrade` | Upgrades to the latest version of Talos.  | Needs a release to fully test |

## Documentation

| Status | Section  | Description                       |
| :----: | -------- | --------------------------------- |
|   🚀   | Crates   | Only stub pages have been made.   |
|   ⚪   | Language | Toolkit, advanced concepts...     |
|   ⚪   | Project  | Contribution points, dashboard... |
|   ⚪   | Tour     | Some steps are not yet finished.  |
