# Ensure that CMake is configured correctly
cmake_minimum_required(VERSION 3.28.3)

# --  INCLUDES  -- #

# Ensure that we can only preload this module once
include_guard(GLOBAL)

# Include all the "mono" based modules
include("${CMAKE_CURRENT_LIST_DIR}/MonoMetadata.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoMessage.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoCache.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoFeatures.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoVersion.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoPackage.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoSources.cmake")

# Include all the "mono" vendor modules
include("${CMAKE_CURRENT_LIST_DIR}/MonoBoost.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonoVendors.cmake")

# Include all the "mono" based libraries
include("${CMAKE_CURRENT_LIST_DIR}/libraries/common.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/libraries/sanitize.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/libraries/warnings.cmake")
