---
title: 21. Crates
---

Alongside modules, Talos exposes internal and external libraries as crates. Crates are declared by constructing a `_crate.jsonc` at the root of a project directory.

Crates should declare a `main` entry-point for their library module, in which this exposes the directory as the `import` target.

Talos itself hosts two types of crates:

| Type     | URI Example    | Description                |
| -------- | -------------- | -------------------------- |
| Internal | `talos:<name>` | Taloss exposed libraries.  |
| External | `crate:<name>` | Installed crate libraries. |
