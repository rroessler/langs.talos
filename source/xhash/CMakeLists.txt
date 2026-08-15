# --  PACKAGE SETUP  -- #

# Prepare all the vendors to be required
talos_vendors_require(ankerl muuid)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_XHASH "xhash" CACHE INTERNAL "")

# Get all the sources for the runtime
talos_sources_glob(TALOS_SOURCES_XHASH)

# --  PACKAGE DEFINITIONS  -- #

# Define the standard library project now
project(${TALOS_TARGET_XHASH} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the runtime library now
talos_library_declare(${TALOS_TARGET_XHASH} PCH SOURCES ${TALOS_SOURCES_XHASH} LIBRARIES
    mono::common
    modern-uuid-static
    unordered_dense::unordered_dense
)
