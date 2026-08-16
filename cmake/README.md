## CMake System

To both simplify the build-system, and expose Talos frameworks for external use, Talos comes with some additional CMake modules.

### Getting Started

Start by adding the following to your top-level `CMakeLists.txt`:

```cmake
# This include is required to get "talos"
include(FetchContent)

# To include "mono" only, then turn this option to "ON"
set(MONO_OPTION_ONLY OFF)

# Fetch the necessary content
FetchContent_Declare(
    talos
    GIT_SHALLOW ON
    GIT_TAG "latest"
    GIT_REPOSITORY "https://github.com/rroessler/langs.talos.git"
)

# Make the content available
FetchContent_MakeAvailable(talos)

# Or when using "OVERRIDE_FIND_PACKAGE"
find_package(talos)
```

### Module - `mono`

This is the CMake utility framework to configure cross-platform C++ monorepos. It can be included as a standalone by setting the `MONO_OPTION_ONLY` variable to `ON`. It features utilities to perform the following core functionality:

- [Dependency Management](./mono/MonoVendors)
- [Defining Monorepo Packages](./mono/MonoPackage)
- [Toggling Compiler Features](./mono/MonoFeatures)

### Module - `talos`

This module includes Talos specific CMake files for defining common variables and vendors.
