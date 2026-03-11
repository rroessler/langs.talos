# --  PACKAGE SETUP  -- #

# Attempt requiring the desired dependencies
talos_package_require(${TALOS_TARGET_XTEST} ${TALOS_TARGET_SUPER})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the testing executable
talos_sources_tests(TALOS_SOURCES_TESTING)

# --  PACKAGE DEFINITION  -- #

# Define the shell project now
project(${TALOS_TARGET_TESTING} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base executable now
add_executable(${TALOS_TARGET_TESTING} ${TALOS_SOURCES_TESTING})

# Define all the libraries to be used now
target_link_libraries(${TALOS_TARGET_TESTING} PUBLIC
    talos::xtest
    talos::crates
    mono::warnings
)
