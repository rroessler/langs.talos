# define the baseline target-triple to be used
set(MONO_TOOLCHAIN_TRIPLE arm64-pc-win32)

# always setup the incoming architecture
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR arm64)

# ensure we also include the common items
include("${CMAKE_CURRENT_LIST_DIR}/common-vars.cmake")

# ensure we are on a valid processor to compile this
if(NOT(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64"))
    message(FATAL_ERROR "Mono: Cannot currently cross-compile Windows ARM64 executables")
endif()
