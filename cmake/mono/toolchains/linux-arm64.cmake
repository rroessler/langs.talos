# define the baseline target-triple to be used
set(MONO_TOOLCHAIN_TRIPLE aarch64-linux-gnu)

# always setup the incoming architecture
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm64)

# ensure we also include the common items
include("${CMAKE_CURRENT_LIST_DIR}/common-vars.cmake")
