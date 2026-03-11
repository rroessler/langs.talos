# --  PACKAGE SETUP  -- #

# Prepare all the vendors to be required
talos_vendors_require(CLI11)

# Attempt requiring the desired dependencies
talos_package_require(${TALOS_TARGET_SUPER})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the shell
talos_sources_glob(TALOS_SOURCES_SHELL)

# --  PACKAGE DEFINITION  -- #

# Define the shell project now
project(${TALOS_TARGET_SHELL} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base executable now
add_executable(${TALOS_TARGET_SHELL} ${TALOS_SOURCES_SHELL})

# Define all the libraries to be used now
target_link_libraries(${TALOS_TARGET_SHELL} PUBLIC
    CLI11::CLI11
    talos::crates
    mono::warnings
)

# Rename and move the resulting executable to "dist"
set_property(TARGET ${TALOS_TARGET_SHELL} PROPERTY OUTPUT_NAME ${TALOS_TARGET_SUPER})

# Only allow moving if we allow post-building
if(TALOS_OPTION_POSTBUILD)
    set_target_properties(${TALOS_TARGET_SHELL} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TALOS_DIRECTORY_BINARY})
endif()

# Prepare a custom target for preparing the output directory with items
add_custom_target(talos-output-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${TALOS_DIRECTORY_BINARY})
add_custom_command(TARGET talos-output-dir POST_BUILD COMMAND ${CMAKE_COMMAND}
    -DTALOS_OPTION_POSTBUILD=${TALOS_OPTION_POSTBUILD}
    -DTALOS_DIRECTORY_OUTPUT="${TALOS_DIRECTORY_OUTPUT}"
    -DTALOS_DIRECTORY_SCRIPT="${TALOS_DIRECTORY_SCRIPT}"
    -DTALOS_DIRECTORY_CRATES="${TALOS_DIRECTORY_SOURCE}/crates"
    -P "${TALOS_DIRECTORY_MODULES}/include/post-build.cmake"
)
