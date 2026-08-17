# --  PROPERTIES  -- #

# Resolve the root of the project
set(TALOS_DIRENT_CMAKE "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")
cmake_path(SET TALOS_DIRENT_ROOT "${TALOS_DIRENT_CMAKE}/../.." NORMALIZE)
string(REGEX REPLACE "${MONO_PATH_SEP}$" "" TALOS_DIRENT_ROOT ${TALOS_DIRENT_ROOT})

# Define all the additional directories to be used
set(TALOS_DIRENT_OUTPUT "${TALOS_DIRENT_ROOT}/dist" CACHE INTERNAL "")
set(TALOS_DIRENT_BINARY "${TALOS_DIRENT_OUTPUT}/bin" CACHE INTERNAL "")
set(TALOS_DIRENT_SOURCE "${TALOS_DIRENT_ROOT}/source" CACHE INTERNAL "")
set(TALOS_DIRENT_SCRIPT "${TALOS_DIRENT_ROOT}/scripts" CACHE INTERNAL "")
set(TALOS_DIRENT_CONFIG "${TALOS_DIRENT_ROOT}/configs" CACHE INTERNAL "")

# Resolve the versioning to be used
if (DEFINED CACHE{TALOS_OPTION_CANARY} AND NOT ${TALOS_OPTION_CANARY})
    # We have been requested to define a non-canary build
    mono_version_read(TALOS_VERSION "${TALOS_DIRENT_CONFIG}/version.txt" COMMIT SUFFIX "stable")
else ()
    # We define canary builds by default (since this declares custom configurations)
    mono_version_read(TALOS_VERSION "${TALOS_DIRENT_CONFIG}/version.txt" COMMIT SUFFIX "canary")
endif ()

# Prepare all the baseline properties
set(TALOS_TOOLCHAIN_TITLE "Talos" CACHE INTERNAL "")
set(TALOS_TOOLCHAIN_STRING "${TALOS_TOOLCHAIN_TITLE} ${TALOS_VERSION_LONG}" CACHE INTERNAL "")
set(TALOS_TOOLCHAIN_TARNAME "${TALOS_TOOLCHAIN_TITLE}_${TALOS_VERSION_LONG}" CACHE INTERNAL "")

# Determine if in the main-project or as a dependency
if (CMAKE_SOURCE_DIR STREQUAL TALOS_DIRENT_ROOT)
    # We set the toolchain as being the root
    set(TALOS_TOOLCHAIN_MAIN ON CACHE INTERNAL "")

    # And we should also enable some additional features
    mono_feature_responses()
    mono_feature_visibility()
    mono_feature_deprecation(OFF)
else ()
    set(TALOS_TOOLCHAIN_MAIN OFF CACHE INTERNAL "")
endif ()

# Define the primary targets to be available
set(TALOS_TARGET_SUPER "talos" CACHE INTERNAL "")

# --  OPTIONS  -- #

# Prepare some options to be used
option(TALOS_OPTION_CANARY "Enable canary builds" ON)
option(TALOS_OPTION_STRICT "Enable strict warnings" OFF)
option(TALOS_OPTION_TESTING "Enable building tests" OFF)
option(TALOS_OPTION_SANITIZE "Enable address sanitizer" OFF)
option(TALOS_OPTION_POSTBUILD "Enables post-build outputs" ON)

# Define the core compilation options to be used
set(TALOS_OPTION_CXXSTD "26" CACHE INTERNAL "The CXX standard library")
