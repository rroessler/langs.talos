# --  MODULE PROPERTIES  -- #

# Prepare all the post-init properties
set(TALOS_TOOLCHAIN_TITLE "Talos" CACHE INTERNAL "")
set(TALOS_TOOLCHAIN_STRING "${TALOS_TOOLCHAIN_TITLE} ${TALOS_VERSION_LONG}" CACHE INTERNAL "")
set(TALOS_TOOLCHAIN_TARNAME "${TALOS_TOOLCHAIN_TITLE}_${TALOS_VERSION_LONG}" CACHE INTERNAL "")

# Prepare all the targets available
set(TALOS_TARGET_SHELL "shell" CACHE INTERNAL "")
set(TALOS_TARGET_CRATES "crates" CACHE INTERNAL "")
set(TALOS_TARGET_TESTING "testing" CACHE INTERNAL "")

set(TALOS_TARGET_XPC "xpc" CACHE INTERNAL "")
set(TALOS_TARGET_XASM "xasm" CACHE INTERNAL "")
set(TALOS_TARGET_XINV "xinv" CACHE INTERNAL "")
set(TALOS_TARGET_XJCT "xjct" CACHE INTERNAL "")
set(TALOS_TARGET_XLSP "xlsp" CACHE INTERNAL "")
set(TALOS_TARGET_XSIO "xsio" CACHE INTERNAL "")
set(TALOS_TARGET_XHASH "xhash" CACHE INTERNAL "")
set(TALOS_TARGET_XTEST "xtest" CACHE INTERNAL "")
set(TALOS_TARGET_XTDLIB "xtdlib" CACHE INTERNAL "")

# Prepare the incoming options to be used
option(TALOS_OPTION_TESTING "Enable building tests" OFF)
option(TALOS_OPTION_MTRACE "Force enables memory tracing" OFF)
option(TALOS_OPTION_POSTBUILD "Enables post-build outputs" ON)

# Prepare the incoming arguments to be used
set(TALOS_OPTION_CXXSTD 26 CACHE INTERNAL "The CXX standard library")

# Determine if in the main-project
if(CMAKE_SOURCE_DIR STREQUAL TALOS_DIRECTORY_ROOT)
    set(TALOS_TOOLCHAIN_MAIN ON CACHE INTERNAL "")
else()
    set(TALOS_TOOLCHAIN_MAIN OFF CACHE INTERNAL "")
endif()
