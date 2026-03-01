# --  PACKAGE SETUP  -- #

# Prepare all the vendors to be required
talos_vendors_require(LIEF)

# Prepare all the packages to be required
talos_package_require(${TALOS_TARGET_XPC} ${TALOS_TARGET_XTDLIB})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XJCT)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XJCT} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XJCT} PCH SOURCES ${TALOS_SOURCES_XJCT} LIBRARIES
    LIEF::LIEF
    talos::xpc
    talos::xtdlib
    mono::warnings
)
