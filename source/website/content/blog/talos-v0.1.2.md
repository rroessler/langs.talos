---
draft: true
date: 2026-12-31
title: Talos v0.1.2
author: Reuben Roessler
---

---

## Bug Fixes

<h4>Toolkit / talos run</h4>

- Added: Exposed more underlying runtime options for setting stack size and overflow limits (eg: `TALOS_STACK_SIZE` and `TALOS_STACK_LIMIT` environment variables).
- Fixed: Updated the default thread stack-size from 1MB to 8MB. This now matches what (libuv)[https://github.com/libuv/libuv] uses for Node JS and other runtimes.
