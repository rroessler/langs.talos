---
icon: Hash
title: Attributes
description: Compile-time annotations to empower type-analysis and runtime capabilities
---

Talos provides support for a selection of compile-time attributes. These allow annotating target declarations with metadata and functionality to empower development and runtime capabilities.

## Deprecations

Variable declarations can now be noted as ~~deprecated~~ and any usage of these variables will be hinted as such (see the [linting command](/docs/language/toolkit/linting/) for restricting deprecation usage).

```talos
// Annotating a variable as being deprecated.
#[Deprecated "This value is deprecated and will be removed in a future release"]
let value = ...;

// In a code-editor with a compatible Talos language-server, any usage of `value` will now be noted as deprecated.
Debug.println(value); // [!code word:value]
```

## Operator Hooks

Although limited, some operators can be added/altered to provide custom functionality. The operators that currently allow being defined include:

- `dispose` &nbsp;&mdash;&nbsp; Utilized by [explicit resource management](/docs/language/advanced/resources).
- `iterator` &nbsp;&mdash;&nbsp; Allows defining [custom object iterators](#).

## Additional Support

As language features are updated and improved, there may be additional attributes that are implemented for Talos.
