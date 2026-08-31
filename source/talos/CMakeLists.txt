# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(xasm xinv xlsp xpc xjct xsio xtdlib xtest)

# Prepare all the vendors to be required
talos_vendors_require(boost)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_CRATES "crates" CACHE INTERNAL "")

# Get all the sources for the runtime
talos_sources_glob(TALOS_SOURCES_SUPER INCLUDE "_parse" "_format" "_check" "_lower" "_rules" "_relint")
talos_sources_glob(TALOS_SOURCES_CRATES HINT "${TALOS_DIRENT_SOURCE}/crates")

# Merge all the source files together as necessary
list(APPEND TALOS_SOURCES_SUPER ${TALOS_SOURCES_CRATES})

# --  PACKAGE DEFINITIONS  -- #

# Define the runtime library now
talos_library_declare(${TALOS_TARGET_SUPER} AUTOGEN SOURCES ${TALOS_SOURCES_SUPER} LIBRARIES
    mono::common
    talos::xasm
    talos::xinv
    talos::xpc
    talos::xlsp
    talos::xjct
    talos::xsio
    talos::xtest
    talos::xtdlib
    Boost::locale
)

# Ensure we allow injecting vendors as well
talos_vendors_inject(${TALOS_TARGET_SUPER})

# Define some common definitions now
target_compile_definitions(${TALOS_TARGET_SUPER} PUBLIC
    -DTALOS_MM_TITLE="${TALOS_TOOLCHAIN_TITLE}"
    -DTALOS_MM_IDENTIFIER="${TALOS_TARGET_SUPER}"
    -DTALOS_MM_VERSION="${TALOS_VERSION_LONG}"
    -DTALOS_MM_COMMIT="${TALOS_VERSION_COMMIT}"
    -DTALOS_MM_CANARY=$<BOOL:${TALOS_OPTION_CANARY}>
)

# Define a custom library for binding the crates to the runtime
add_library(${TALOS_TARGET_CRATES} INTERFACE)
add_library(${TALOS_TARGET_SUPER}::${TALOS_TARGET_CRATES} ALIAS ${TALOS_TARGET_CRATES})

# Define the additional "talos::crates" details
target_link_libraries(${TALOS_TARGET_CRATES} INTERFACE $<LINK_LIBRARY:WHOLE_ARCHIVE,talos::talos>)
