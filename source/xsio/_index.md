## Concurrency Framework - `xsio`

This is the asynchronous library for Talos. It is implemented using the custom [`makecontext`](https://man7.org/linux/man-pages/man3/makecontext.3.html) functions provided by [`boost::context`](https://github.com/boostorg/context), which enables the functionality of lightweight context switching.
