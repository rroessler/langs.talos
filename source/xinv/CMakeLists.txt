# --  PACKAGE SETUP  -- #

# Attempt requiring the desired dependencies
talos_package_require(${TALOS_TARGET_XTDLIB})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XINV)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XINV} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XINV} PCH SOURCES ${TALOS_SOURCES_XINV} LIBRARIES
    talos::xtdlib
    mono::warnings
)
