# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(xtdlib)

# Prepare all the vendors to be required
talos_vendors_require(boost)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_XSIO "xsio" CACHE INTERNAL "")

# Get all the sources for the runtime
talos_sources_glob(TALOS_SOURCES_XSIO)

# --  PACKAGE DEFINITIONS  -- #

# Define the standard library project now
project(${TALOS_TARGET_XSIO} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the runtime library now
talos_library_declare(${TALOS_TARGET_XSIO} PCH SOURCES ${TALOS_SOURCES_XSIO} LIBRARIES
    mono::common
    talos::xtdlib
    Boost::context
)
