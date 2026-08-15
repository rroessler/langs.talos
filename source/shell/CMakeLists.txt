# --  PACKAGE SETUP  -- #

# Attempt requiring the desired packages
talos_package_require(talos)

# Prepare all the vendors to be required
talos_vendors_require(CLI11)

# --  PACKAGE PROPERTIES  -- #

# Define this packages target
set(TALOS_TARGET_SHELL "shell" CACHE INTERNAL "")

# Get all the sources for the shell
talos_sources_glob(TALOS_SOURCES_SHELL)

# --  PACKAGE DEFINITIONS  -- #

# Define the shell project now
project(${TALOS_TARGET_SHELL} VERSION ${TALOS_VERSION_SHORT} LANGUAGES CXX)

# Define the base executable details now
add_executable(${TALOS_TARGET_SHELL} ${TALOS_SOURCES_SHELL})

# Define all the libraries to be used
target_link_libraries(${TALOS_TARGET_SHELL} PUBLIC
    CLI11::CLI11
    mono::common
    talos::crates
)

# Rename and move the resulting executable to "dist"
set_property(TARGET ${TALOS_TARGET_SHELL} PROPERTY OUTPUT_NAME ${TALOS_TARGET_SUPER})

# Only allow moving if we allow post-building
if (TALOS_OPTION_POSTBUILD)
    set_target_properties(${TALOS_TARGET_SHELL} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TALOS_DIRENT_BINARY})
endif ()

# Prepare a custom target for preparing the output directory with items
add_custom_target(talos-output-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${TALOS_DIRENT_BINARY})
add_custom_command(TARGET talos-output-dir POST_BUILD COMMAND ${CMAKE_COMMAND}
    -DTALOS_OPTION_POSTBUILD=${TALOS_OPTION_POSTBUILD}
    -DTALOS_DIRENT_OUTPUT="${TALOS_DIRENT_OUTPUT}"
    -DTALOS_DIRENT_SCRIPT="${TALOS_DIRENT_SCRIPT}"
    -DTALOS_DIRENT_CRATES="${TALOS_DIRENT_SOURCE}/crates"
    -P "${TALOS_DIRENT_CMAKE}/include/post-build.cmake"
)
