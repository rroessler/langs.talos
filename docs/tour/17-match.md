---
title: 17. Match
---

A `match` statement considers a value and compares against several possible matching patterns. After which and appropriate block of code can be executed if matched successfully.

In the simplest form, a `match` statement compares against values of the same type.

```talos
match ("a") {
    "a": Debug.println("First latin character"),
    "z": Debug.println("Last latin character"),
    *: Debug.println("Some other character"),
}
```

Unlike other languages, cases do not fall-through to one-another. Each `case` expects a following statement. To instead match more than one case for a code-block, we can combine the cases.

```talos
match ("a") {
    "a", "A": Debug.println("Found letter 'a'"),
    *: Debug.println("Was not the letter 'a'"),
}
```

Or for more specific matching, we can use a function guard.

```talos
// Prepare a guard for our values
let guard = fn (ch: String) => ch.to_lower() == "a";

match ("a") {
    guard: Debug.println("Found letter 'a'"),
    *: Debug.println("Was not the letter 'a'"),
}
```

Additionally, we can use classes and builtin types as our guards as well.

```talos
match ("a") {
    String: Debug.println("Value was a string"),
    Number: Debug.println("Value was a number"),
    *: Debug.println("Did not match a valid type"),
}
```
