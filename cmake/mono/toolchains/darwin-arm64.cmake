# define the baseline target-triple to be used
set(MONO_TOOLCHAIN_TRIPLE arm64-apple-darwin)

# always setup the incoming architecture
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR arm64)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.8)

# ensure we also include the common items
include("${CMAKE_CURRENT_LIST_DIR}/common-vars.cmake")
