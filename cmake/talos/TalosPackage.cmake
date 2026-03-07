# --  PUBLIC FUNCTIONS  -- #

# Handles declaring "talos" packages
function(talos_package_declare _package)
    set(_hint "${TALOS_DIRECTORY_SOURCE}/${_package}")
    mono_package_declare(${_package} HINT ${_hint})
endfunction()

# Handles requiring "talos" packages
function(talos_package_require)
    foreach(_package IN LISTS ARGN)
        mono_package_require(${_package})
    endforeach()
endfunction()

# Allows declaring libraries
function(talos_library_declare _target)
    # parse the incoming arguments now
    cmake_parse_arguments(_ARGS "PCH" "" "SOURCES;LIBRARIES" ${ARGN})

    # prepare the available sources
    if(NOT DEFINED _ARGS_SOURCES)
        set(_ARGS_SOURCES)
    endif()

    # handle based on the sources available
    if(_ARGS_SOURCES)
        set(_type PRIVATE) # declare as private now
        set(_include PUBLIC) # allow includes to be exposed
        add_library(${_target} STATIC) # static library
        target_sources(${_target} ${_type} ${_ARGS_SOURCES})
    else()
        set(_type INTERFACE) # hidden
        set(_include ${_type}) # hidden
        add_library(${_target} ${_type})
    endif()

    # prepare the autogen folder as well
    set(_autogen "${CMAKE_CURRENT_BINARY_DIR}/autogen/include")

    # and add the exposed library instance
    add_library(${TALOS_TARGET_SUPER}::${_target} ALIAS ${_target})
    set_property(TARGET ${_target} PROPERTY CXX_STANDARD ${TALOS_OPTION_CXXSTD})
    target_compile_features(${_target} ${_type} "cxx_std_${TALOS_OPTION_CXXSTD}")
    set_property(TARGET ${_target} PROPERTY CXX_EXTENSIONS OFF) # remove C++ extension
    target_include_directories(${_target} ${_include} ${TALOS_DIRECTORY_SOURCE} ${_autogen})

    # handling incoming pre-compilation libraries as well
    if(_ARGS_PCH)
        target_precompile_headers(${_target} ${_include} "${_target}.hpp")
    endif()

    # handle adding link-libraries
    if(DEFINED _ARGS_LIBRARIES)
        target_link_libraries(${_target} ${_include} ${_ARGS_LIBRARIES})
    endif()
endfunction()

# --  PACKAGE DECLARATIONS  -- #

# Declare all the packages for "talos"
talos_package_declare(${TALOS_TARGET_XPC})
talos_package_declare(${TALOS_TARGET_XASM})
talos_package_declare(${TALOS_TARGET_XINV})
talos_package_declare(${TALOS_TARGET_XJCT})
talos_package_declare(${TALOS_TARGET_XLSP})
talos_package_declare(${TALOS_TARGET_XSIO})
talos_package_declare(${TALOS_TARGET_XHASH})
talos_package_declare(${TALOS_TARGET_XTEST})
talos_package_declare(${TALOS_TARGET_XTDLIB})

# Declare the core package for "talos"
talos_package_declare(${TALOS_TARGET_SUPER})
