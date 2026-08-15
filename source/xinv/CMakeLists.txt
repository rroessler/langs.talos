# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(xtdlib)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_XINV "xinv" CACHE INTERNAL "")

# Get all the sources for the runtime
talos_sources_glob(TALOS_SOURCES_XINV)

# --  PACKAGE DEFINITIONS  -- #

# Define the standard library project now
project(${TALOS_TARGET_XINV} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the runtime library now
talos_library_declare(${TALOS_TARGET_XINV} PCH SOURCES ${TALOS_SOURCES_XINV} LIBRARIES
    mono::common
    talos::xtdlib
)
