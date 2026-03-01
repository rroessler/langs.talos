# --  MODULE PROPERTIES  -- #

set_property(GLOBAL PROPERTY __MONO_BOOST_TARGET "boost")
set_property(GLOBAL PROPERTY __MONO_BOOST_VERSION "1.88.0")

# --  PUBLIC METHODS  -- #

# Handles declaring a global boost instance.
function(mono_boost_declare)
    # prepare parsing some boost options
    cmake_parse_arguments(_ARGS "" "NAMED;VERSION" "COMPONENTS" ${ARGN})

    # update the underlying name now
    if(DEFINED _ARGS_NAMED)
        set_property(GLOBAL PROPERTY __MONO_BOOST_TARGET ${_ARGS_NAMED})
    else()
        get_property(_ARGS_NAMED GLOBAL PROPERTY __MONO_BOOST_TARGET)
    endif()

    # update the underlying version now
    if(DEFINED _ARGS_VERSION)
        set_property(GLOBAL PROPERTY __MONO_BOOST_VERSION ${_ARGS_VERSION})
    else()
        get_property(_ARGS_VERSION GLOBAL PROPERTY __MONO_BOOST_VERSION)
    endif()

    # stop handling if the target is available
    if(TARGET _ARGS_NAMED)
        return()
    endif()

    # set some global boost-properties now
    set(BOOST_USE_STATIC_LIBS ${_ARGS_STATIC} PARENT_SCOPE)

    # attempt installing now as necessary
    __mono_boost_declare(${_ARGS_NAMED} ${_ARGS_VERSION})
endfunction()

function(mono_boost_require)
    # get the underlying boost target now
    get_property(_target GLOBAL PROPERTY __MONO_BOOST_TARGET)

    if(NOT TARGET ${_target})
        get_property(_version GLOBAL PROPERTY __MONO_BOOST_VERSION)
        FetchContent_MakeAvailable(${_target}) # ensure before-hand
        find_package(${_target} ${_version} EXACT REQUIRED QUIET)
    endif()
endfunction()

macro(mono_boost_static _state)
    set(BOOST_USE_STATIC_LIBS ${_state})
endmacro()

macro(mono_boost_multithreaded _state)
    set(BOOST_USE_MULTITHREADED ${_state})
endmacro()

macro(mono_boost_libraries)
    set(BOOST_ENABLE_CMAKE ON)
    set(BOOST_INCLUDE_LIBRARIES ${ARGN})
endmacro()

# --  PRIVATE METHODS  -- #

# Handles fetching boost.
function(__mono_boost_declare _target _version)
    # include the fetch-content handler
    include(FetchContent)

    # prepare the URL to be used now
    set(_url "https://github.com/boostorg/boost/releases/download/boost-${_version}/boost-${_version}-cmake.tar.xz")

    # attempt fetching through the fast-source
    FetchContent_Declare(${_target} URL ${_url}
        OVERRIDE_FIND_PACKAGE
        DOWNLOAD_NO_EXTRACT OFF
        USES_TERMINAL_DOWNLOAD OFF)
endfunction()
