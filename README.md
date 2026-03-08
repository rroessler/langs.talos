# Talos Programming Language

<p align="center">
    <a href="#why-talos">Why Talos?</a> |
    <a href="#getting-started">Getting Started</a> |
    <a href="#faq">Contributing</a>
</p>

## Why Talos?

Many dynamic programming languages prioritize performance, syntax and paradigms over other important development needs such as analysis, testability, scalability, portability and readability. Talos aims to be the best of both worlds with a statically-typed language that targets a dynamic runtime, and has builtin linting, formating, testing, language-server, bundler and more.

Fundamentally Talos does not reinvent the wheel, but instead aims to excel at working with the user to improve development workflow. Alongside this, Talos is designed around the following core features:

- A familiar and readable modern syntax
- Performant static-analysis, with additional strict linting support
- A dynamic runtime for immediate execution, and multiple bundling options for distribution
- Rich standard library, focusing on out-of-the-box testability and development scalability
- A gentle learning curve, with reasonable familiarity to TypeScript, Dart, Rust, and Carbon

The language goals in mind to support these features include:

- [Modular C++ Backend](./docs/project/development.mdx)
    - [Monorepo Build System](./cmake/_index)
    - [LSP Framework](./source/xlsp/_index)
    - [Testing Framework](./source/xtest/_index)
    - [Dependency Injection](./source/xinv/_index)
    - [Concurrency Framework](./source/xsio/_index)

- [Language Design](./docs/language/index)
    - [Familiar Modern Syntax](./docs/language/fundamentals/syntax)
    - [Nominal/Structural Types](./docs/language/advanced/type-system)
    - [Monadic Error Handling](./docs/language/advanced/exceptions)
    - [Fatal Runtime Exceptions](./docs/language/advanced/exceptions)
    - [Colorless Function Design](./docs/language/advanced/colorless)

## Getting Started

Talos supports Windows (x64), Darwin (x64, Apple Silicon) and Linux (x64, arm64).

> **Note:**
>
> Currently Talos is not available for installation. Check out [how to build](./docs/project/development.mdx)

## FAQ

**Is there a roadmap for Talos' development?**

Yes, you can see the [full roadmap](./docs/project/roadmap) for more details.

**Can I contribute to this project?**

Not quite yet as Talos is still an experimental project. Once a version `1.0.0` language can be shipped, contribution will become available. Talos can be [built natively](./docs/project/development.mdx) for those that want to get their hands dirty.
