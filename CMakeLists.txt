# --  INCLUDE GUARDS  -- #

cmake_minimum_required(VERSION 3.28.3)

# --  INCLUDE MODULES  -- #

# Include some common preloaders
include("cmake/mono/MonoPreload.cmake")

if(MONO_OPTION_ONLY)
    # stop loading if not required to (eg: dependency)
    return()
else()
    # otherwise we want to try enable "ccache"
    mono_ccache_setup()

    # setup handling for "ninja" generators
    mono_feature_ninja()
endif()

# And load the "talos" preload now
include("cmake/talos/TalosPreload.cmake")

# --  MODULE DEFINITION  -- #

# Prepare the super-project instance
project(${TALOS_TARGET_SUPER} VERSION "${TALOS_VERSION_SHORT}" LANGUAGES CXX)

# --  MODULE INSTALLATION  -- #

# Check if running in the root-project
if(${TALOS_TOOLCHAIN_MAIN})
    # Ensure we enable some features at the top-level
    mono_feature_responses()
    mono_feature_visibility()
    mono_feature_deprecation(OFF)

    talos_message_status("Configuring Project '${TALOS_VERSION_LONG}'")
    add_subdirectory("${TALOS_DIRECTORY_SOURCE}/shell") # shell entry
endif()

# Enable all testing when desired
if(${TALOS_OPTION_TESTING})
    talos_message_status("Enabled Testing '${TALOS_VERSION_LONG}'")
    add_subdirectory("${TALOS_DIRECTORY_SOURCE}/testing") # test entry
endif()
