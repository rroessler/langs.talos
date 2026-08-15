# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(talos xtest)

# --  PACKAGE PROPERTIES  -- #

# Define this packages target
set(TALOS_TARGET_TESTS "tests" CACHE INTERNAL "")

# Get all the available sources for the testing executable
talos_sources_tests(TALOS_SOURCES_TESTS)

# --  PACKAGE DEFINITIONS  -- #

# Define the tests project now
project(${TALOS_TARGET_TESTS} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base executable now
add_executable(${TALOS_TARGET_TESTS} ${TALOS_SOURCES_TESTS})

# Define all the libraries to be used now
target_link_libraries(${TALOS_TARGET_TESTS} PUBLIC
    mono::common
    talos::xtest
    talos::crates
)

