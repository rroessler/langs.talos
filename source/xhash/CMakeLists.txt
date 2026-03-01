# --  PACKAGE PROPERTIES  -- #

# Prepare all the vendors to be required
talos_vendors_require(ankerl muuid)

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XHASH)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XHASH} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XHASH} PCH SOURCES ${TALOS_SOURCES_XHASH} LIBRARIES
    mono::warnings
    modern-uuid-static
    unordered_dense::unordered_dense
)
