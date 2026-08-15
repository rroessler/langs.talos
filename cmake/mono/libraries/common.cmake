# --  PUBLIC METHODS  -- #

# Factory for the "mono::common" library
macro(mono_library_common _cxxstd)
    # define the base properties
    set(MONO_TARGET_COMMON "${MONO_TARGET_SUPER}_common")

    # define a set of common compilation options
    add_library(${MONO_TARGET_COMMON} INTERFACE)
    add_library(${MONO_TARGET_SUPER}::common ALIAS ${MONO_TARGET_COMMON})

    # and allow the target to act as an interface for others
    set_property(TARGET ${MONO_TARGET_COMMON} PROPERTY CXX_EXTENSIONS OFF)
    set_property(TARGET ${MONO_TARGET_COMMON} PROPERTY CXX_STANDARD ${_cxxstd})
    target_compile_features(${MONO_TARGET_COMMON} INTERFACE "cxx_std_${_cxxstd}")

    # also reference the other libraries from "mono"
    target_link_libraries(${MONO_TARGET_COMMON} INTERFACE mono::sanitize mono::warnings)
endmacro()
