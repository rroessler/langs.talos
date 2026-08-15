# --  PACKAGE SETUP  -- #

# Prepare all the packages to be required
talos_package_require(xtdlib)

# Prepare all the vendors to be required
talos_vendors_require(asmjit)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_XASM "xasm" CACHE INTERNAL "")

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XASM)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XASM} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XASM} PCH SOURCES ${TALOS_SOURCES_XASM} LIBRARIES
    mono::common    
    asmjit::asmjit
    talos::xtdlib
)
