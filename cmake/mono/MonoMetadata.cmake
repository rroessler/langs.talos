# --  PROPERTIES  -- #

# Prepare a super-module target to be used
set(MONO_TARGET_SUPER "mono" CACHE INTERNAL "")
set(MONO_TOOLCHAIN_TITLE "Mono" CACHE INTERNAL "")

# Prepare some utility properties to be used
cmake_path(SET MONO_PATH_SEP NORMALIZE "/")

# Prepare all the common directories to be used
set(MONO_DIRENT_CMAKE "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")
set(MONO_DIRENT_BINARY "${CMAKE_BINARY_DIR}/_mono" CACHE INTERNAL "")
set(MONO_DIRENT_PACKAGES "${MONO_DIRENT_BINARY}/packages" CACHE INTERNAL "")

# --  OPTIONS  -- #

# Prepare some user options that are available
option(MONO_OPTION_ONLY "Only enable 'mono' for development" OFF)
