# --  MODULE PROPERTIES  -- #

set_property(GLOBAL PROPERTY __MONO_PACKAGES_LIST)
set_property(GLOBAL PROPERTY __MONO_PACKAGES_HINT)

# --  PUBLIC FUNCTIONS  -- #

# Handles requiring a package for use.
function(mono_package_require _package)
    # stop when the package has already been loaded
    if (TARGET ${_package})
        return()
    endif ()

    # attempt getting the package details
    __mono_package_hint(${_package} _hint)

    # once resolved then we can add the instance now
    add_subdirectory(${_hint} ${MONO_DIRENT_PACKAGES}/${_package})
endfunction()

# Handles declaring a package for use.
function(mono_package_declare _package)
    # parse the incoming arguments now
    cmake_parse_arguments(_ARGS "" "HINT" "" ${ARGN})

    # resolve the hint to be used for the package
    if (NOT DEFINED _ARGS_HINT)
        set(_ARGS_HINT ${CMAKE_SOURCE_DIR})
    endif ()

    # ensure that there is a valid "CMakeLists.txt" file
    if (NOT EXISTS "${_ARGS_HINT}/CMakeLists.txt")
        mono_message_fatal("Could not resolve package '${_package}'")
    endif ()

    # register the package now as necessary
    set_property(GLOBAL APPEND PROPERTY __MONO_PACKAGES_LIST ${_package})
    set_property(GLOBAL APPEND PROPERTY __MONO_PACKAGES_HINT ${_ARGS_HINT})
endfunction()

# --  PRIVATE FUNCTIONS  -- #

# Handles resolving hint values
function(__mono_package_hint _package _output)
    get_property(_list GLOBAL PROPERTY __MONO_PACKAGES_LIST)
    list(FIND _list ${_package} _index) # attempt finding

    # declare an error if we cannot find the package
    if (_index EQUAL -1)
        mono_message_fatal("Package '${_package}' not declared")
    endif ()

    # should be able to output our value now
    get_property(_hints GLOBAL PROPERTY __MONO_PACKAGES_HINT)
    list(GET _hints ${_index} _hint) # attempt getting the hint

    # set the resulting output for the hint
    set(${_output} ${_hint} PARENT_SCOPE)
endfunction()
