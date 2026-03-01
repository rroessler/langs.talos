# --  INCLUDE GUARDS  -- #

include_guard(GLOBAL)

cmake_minimum_required(VERSION 3.28.3)

# --  MODULE PROPERTIES  -- #

# Define the primary target to be available
set(TALOS_TARGET_SUPER "talos" CACHE INTERNAL "")

# Define the initial directory paths
set(TALOS_DIRECTORY_MODULES ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")
cmake_path(SET TALOS_DIRECTORY_ROOT "${TALOS_DIRECTORY_MODULES}/../.." NORMALIZE)
string(REGEX REPLACE "${MONO_PATH_SEPARATOR}$" "" TALOS_DIRECTORY_ROOT ${TALOS_DIRECTORY_ROOT})

# And then define the additional directories for use
set(TALOS_DIRECTORY_OUTPUT "${TALOS_DIRECTORY_ROOT}/dist" CACHE INTERNAL "")
set(TALOS_DIRECTORY_BINARY "${TALOS_DIRECTORY_OUTPUT}/bin" CACHE INTERNAL "")
set(TALOS_DIRECTORY_SOURCE "${TALOS_DIRECTORY_ROOT}/source" CACHE INTERNAL "")
set(TALOS_DIRECTORY_SCRIPT "${TALOS_DIRECTORY_ROOT}/scripts" CACHE INTERNAL "")

# --  MODULE DEFINITION  -- #

# Pre-parse the incoming version value
mono_version_read(TALOS_VERSION "${TALOS_DIRECTORY_ROOT}/configs/version.txt" BRANCH_TRIM "main")

# Also parse the incoming commit details
mono_version_commit(TALOS_VERSION_COMMIT)

# --  MODULE INCLUDES  -- #

# Include all the "talos" based modules
include("${TALOS_DIRECTORY_MODULES}/TalosMetadata.cmake")
include("${TALOS_DIRECTORY_MODULES}/TalosMessage.cmake")
include("${TALOS_DIRECTORY_MODULES}/TalosPackage.cmake")
include("${TALOS_DIRECTORY_MODULES}/TalosSources.cmake")
include("${TALOS_DIRECTORY_MODULES}/TalosVendors.cmake")
