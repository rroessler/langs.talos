---
draft: true
date: 2026-12-31
title: Talos v0.1.2
author: Reuben Roessler
---

## Runtime Decorators

Todo...

---

## Bug Fixes

<h4>Toolkit / talos run</h4>

- Added: Exposed more underlying runtime options for setting stack size and overflow limits (eg: `TALOS_STACK_SIZE` and `TALOS_STACK_LIMIT` environment variables).
- Fixed: Updated the default thread stack-size from 1MB to 8MB. This now matches what (libuv)[https://github.com/libuv/libuv] uses for Node JS and other runtimes.
- Fixed: Can now safely barrel exports and imports. Previously this syntax crashed during compilation as a variable pattern was expected for these statements.
- Fixed: Backtraces now are limited to a fixed size that will in future be available for configuration through the command-line.
- Fixed: Previously generic functions would crash the type-checker due to their contextual type not being resolved properly. This has now been addressed.
- Added: Laid the foundations for runtime decorator annotations. This includes: basic type-checking, and instantiation alongside compile-time attributes.

<h4>Toolkit / talos serve</h4>

- Fixed: When type-checking accessors, fields now have their inferred types properly cached to enable linting tools.
- Fixed: There was an issue decoding `$/cancel` request identifiers. These are now properly decoded depending on whether they are a string or number value.

<h4>Toolkit / talos upgrade</h4>

- Fixed: Previously the wrong version branch (eg: `-main` instead of `-stable`) was used for determining the current Talos installation. This resulted in upgrades not properly identifying when the latest version was the same as the current one. This has now been resolved for this release of Talos.

<h4>Crate / talos:mem</h4>

- Added: Exposed thread-memory namespace with stack-usage details similar to heap-memory namespace.
