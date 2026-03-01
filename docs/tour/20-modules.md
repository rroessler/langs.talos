---
title: 20. Modules
---

Programs in Talos can be split into mutiple files called modules. A module is a collection of variables that have been exposed via an `export` declaration.

Local modules can be imported/exported using the following syntax:

```talos
// Local file "a.tal"
export let a = "A";
```

```talos
// Relative file "b.tal"
import "./a.tal" as { a };

// Showing the result of our imported module.
Debug.println(a);
```

Import targets are declared with a relative/absolute file-path, or for special imports as file URI's.
