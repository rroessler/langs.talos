# --  INCLUDE GUARDS  -- #

include_guard(GLOBAL)

cmake_minimum_required(VERSION 3.28.3)

# --  MODULE PROPERTIES  -- #

# Prepare all the super-module properties
set(MONO_TARGET_SUPER "mono")

# Prepare all the common directories to be used
set(MONO_DIRECTORY_MODULES ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")
set(MONO_DIRECTORY_BINARY ${CMAKE_BINARY_DIR}/_mono CACHE INTERNAL "")
set(MONO_DIRECTORY_PACKAGES ${MONO_DIRECTORY_BINARY}/packages CACHE INTERNAL "")

# Prepare some common options to be used
option(MONO_OPTION_ONLY "Only enable 'mono' for development" OFF)

# Prepare some common items now
cmake_path(SET MONO_PATH_SEPARATOR NORMALIZE "/")

# --  MODULE INCLUDES  -- #

# Include all the "mono" based modules
include("${MONO_DIRECTORY_MODULES}/MonoMessage.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoVersion.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoFeatures.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoSources.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoBoost.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoCache.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoVendors.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoWarnings.cmake")
include("${MONO_DIRECTORY_MODULES}/MonoPackage.cmake")
