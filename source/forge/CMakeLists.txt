# --  PACKAGE SETUP  -- #

# Attempt requiring the desired dependencies
talos_package_require(
    ${TALOS_TARGET_XPC}
    ${TALOS_TARGET_XASM}
    ${TALOS_TARGET_XINV}
    ${TALOS_TARGET_XJCT}
    ${TALOS_TARGET_XLSP}
    ${TALOS_TARGET_XSIO}
    ${TALOS_TARGET_XTEST}
    ${TALOS_TARGET_XTDLIB}
)

# --  PACKAGE PROPERTIES  -- #

# Get all the available sources for the forge
talos_sources_glob(TALOS_SOURCES_FORGE INCLUDE "_parse" "_check" "_relint" "_format" "_lower")
talos_sources_glob(TALOS_SOURCES_CRATES HINT "${TALOS_DIRECTORY_SOURCE}/crates")

# Merge all the source files together as necessary
list(APPEND TALOS_SOURCES_FORGE ${TALOS_SOURCES_CRATES})

# --  PACKAGE DEFINITION  -- #

# Define the forge library now
project(${TALOS_TARGET_FORGE} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)
talos_library_declare(${TALOS_TARGET_FORGE} SOURCES ${TALOS_SOURCES_FORGE} LIBRARIES
    talos::xpc
    talos::xasm
    talos::xinv
    talos::xjct
    talos::xlsp
    talos::xsio
    talos::xtest
    talos::xtdlib
)

# Ensure we allow injecting vendors as well
talos_vendors_inject(${TALOS_TARGET_FORGE})

# Define some common definitions now
target_compile_definitions(${TALOS_TARGET_FORGE} PUBLIC
    -DFORGE_MM_TITLE="${TALOS_TOOLCHAIN_TITLE}"
    -DFORGE_MM_IDENTIFIER="${TALOS_TARGET_SUPER}"
    -DFORGE_MM_VERSION="${TALOS_VERSION_LONG}"
    -DFORGE_MM_COMMIT="${TALOS_VERSION_COMMIT}"
)
