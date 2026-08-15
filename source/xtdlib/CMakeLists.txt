# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(xhash)

# Prepare all the vendors to be required
talos_vendors_require(aster boost fmt function2 glaze spdlog)

# --  PACKAGE PROPERTIES  -- #

# Define the target to be used
set(TALOS_TARGET_XTDLIB "xtdlib" CACHE INTERNAL "")

# Get all the sources for the runtime
talos_sources_glob(TALOS_SOURCES_XTDLIB)

# --  PACKAGE DEFINITIONS  -- #

# Define the standard library project now
project(${TALOS_TARGET_XTDLIB} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the runtime library now
talos_library_declare(${TALOS_TARGET_XTDLIB} PCH SOURCES ${TALOS_SOURCES_XTDLIB} LIBRARIES
    fmt::fmt
    aster::aster
    glaze::glaze
    mono::common
    talos::xhash
    spdlog::spdlog
    Boost::interprocess
    function2::function2
)
