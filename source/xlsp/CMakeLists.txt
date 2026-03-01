# --  PACKAGE SETUP  -- #

# Prepare all the packages to be required
talos_package_require(${TALOS_TARGET_XTDLIB})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XLSP)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XLSP} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XLSP} PCH SOURCES ${TALOS_SOURCES_XLSP} LIBRARIES
    talos::xtdlib
    mono::warnings
)
