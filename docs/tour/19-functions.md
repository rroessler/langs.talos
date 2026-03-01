---
title: 19. Functions
---

Functions are basic self-contained chunks of code that can perform specific tasks when called. They are declared as first-class citizens and as such, are only named when specifically attached to a variable.

When defining a function, you can optionally declare parameters and a return-type, followed by the functions body.

```talos
let greet = fn (person: String): String {
    return "Hello, {0}!".fmt(person);
};
```

To then call a function, we use the `()` operator to invoke a function with the given arguments.

```talos
Debug.println(greet("Talos"));
```

Functions can be shortened further by using arrow punctuation.

```talos
let greet = fn (person: String) => "Hello, {0}".fmt(person);
```

Parameters can also be defined optionally, have a default value, or spread themselves into an array of values.

```talos
fn (a?) { ... }; // Declares an optional parameter
fn (a = 5) { ... }; // Declares a defaulted parameter
fn (...a) { ... }; // Declares a spread-parameter
```

Functions that have no arguments can also be defined without a parameter list.

```talos
fn { ... };
```
