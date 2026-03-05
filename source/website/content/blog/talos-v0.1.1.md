---
draft: true
date: 2026-12-31
title: Talos v0.1.1
author: Reuben Roessler
---

## Bug Fixes

#### talos upgrade

- Fixed: Simplified the uninstall process on Windows. Previously it used a scheduled-task, however this has been replaced with a delayed `rmdir` command invoked through a hidden separate process using the `start` command.
