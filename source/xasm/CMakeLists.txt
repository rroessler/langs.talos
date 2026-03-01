# --  PACKAGE SETUP  -- #

# Prepare all the vendors to be required
talos_vendors_require(asmjit)

# Prepare all the packages to be required
talos_package_require(${TALOS_TARGET_XTDLIB})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XASM)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XASM} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XASM} PCH SOURCES ${TALOS_SOURCES_XASM} LIBRARIES
    asmjit::asmjit
    talos::xtdlib
    mono::warnings
)
