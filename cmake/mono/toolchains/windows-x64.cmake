# define the baseline target-triple to be used
set(MONO_TOOLCHAIN_TRIPLE x86_64-pc-win32)

# always setup the incoming architecture
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x64)

# ensure we also include the common items
include("${CMAKE_CURRENT_LIST_DIR}/common-vars.cmake")
