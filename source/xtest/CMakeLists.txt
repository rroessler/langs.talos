# --  PACKAGE SETUP  -- #

# Prepare all the packages to be required
talos_package_require(${TALOS_TARGET_XINV} ${TALOS_TARGET_XTDLIB})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XTEST)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XTEST} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XTEST} PCH SOURCES ${TALOS_SOURCES_XTEST} LIBRARIES
    talos::xinv
    talos::xtdlib
    mono::warnings
)
