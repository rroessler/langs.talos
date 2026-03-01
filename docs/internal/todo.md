---
title: Todo
---

## Todo Items

- [x] Test Macho Loop Performance (eg: to see if internally the generated machine code is faster than bytecode)
    - Conclusion: Significant improvement in performance using (around 10x gains)
- [-] Small String Constants (eg: add flag from bytecode compiler to instead place into constants over strings arena storage)
    - Conclusion: Not enough of a performance gain to implement (since small strings are immediately constructed without heap allocation)
- [-] Compress Comparison Jumps (eg: TEST_LTI into JUMP_FALSEY, could be elided into a JUMP_GEI instruction. Would improve bytecode/machine code outputs)
    - Conclusion: Could only elide certain jumps as the operands exceed 64-bits (above example exceeds), so ignored implementing
- [ ] Constant Load Propagation (eg: add a constant variable extent for local variables with constant values, so they can propogate instead of moving registers)
- [x] Frame Allocation (eg: use heap allocated regions for frame stacks instead of using the builtin `::alloca` allocator)
    - Conclusion: This removed numerous `Function::Argument` copies and moves, as well as improved memory usage (eg: not relying on thread-stack memory)
