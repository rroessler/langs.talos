# --  PACKAGE SETUP  -- #

# Prepare all the vendors to be required
talos_vendors_require(ankerl aster boost fmt glaze spdlog)

# Prepare all the packages to be required
talos_package_require(${TALOS_TARGET_XHASH})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_XTDLIB)

# --  PACKAGE DEFINITION  -- #

# Define the project now
project(${TALOS_TARGET_XTDLIB} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base library now
talos_library_declare(${TALOS_TARGET_XTDLIB} PCH SOURCES ${TALOS_SOURCES_XTDLIB} LIBRARIES
    ${TALOS_TARGET_XHASH}

    fmt::fmt
    aster::aster
    glaze::glaze
    mono::warnings
    Boost::interprocess
    spdlog::spdlog_header_only
    unordered_dense::unordered_dense
)

# Set the underlying options now
target_compile_definitions(${TALOS_TARGET_XTDLIB} PUBLIC
    -D_XTDLIB_ENABLE_MTRACE=$<BOOL:${TALOS_OPTION_MTRACE}>
)
