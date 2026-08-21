# --  CONDITIONS  -- #

# Stop early if user only wants to use "mono"
if (MONO_OPTION_ONLY)
    return()
endif ()

# --  INCLUDES  -- #

# Include all the "talos" base modules
include("${CMAKE_CURRENT_LIST_DIR}/TalosOptions.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosMetadata.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosMessage.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosLibrary.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosPackage.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosSources.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TalosVendors.cmake")

# --  FEATURES  -- #

# Ensure some features are enabled
mono_sccache_setup()
mono_feature_ninja()

# Ensure all the "mono" libraries are enabled
mono_library_warnings(${TALOS_OPTION_STRICT})
mono_library_sanitize(${TALOS_OPTION_SANITIZE})
mono_library_common(${TALOS_OPTION_CXXSTD})
