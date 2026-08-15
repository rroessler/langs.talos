# --  PUBLIC FUNCTIONS  -- #

# Allow searching for incoming sources.
function(mono_sources_glob)
    # parse the incoming arguments to be used
    cmake_parse_arguments(_ARGS "BUILTINS" "OUTPUT;HINT;EXT" "INCLUDE" ${ARGN})

    # ensure we have an output set
    if (NOT DEFINED _ARGS_OUTPUT)
        mono_message_fatal("Expected an output for globbing sources")
    endif ()

    # prepare the targets list to be used
    if (_ARGS_BUILTINS)
        __mono_sources_builtins(_targets)
    endif ()

    # allow setting a default extension value
    if (NOT DEFINED _ARGS_EXT)
        set(_ARGS_EXT ".cpp")
    endif ()

    # allow setting the hint to the sources
    if (NOT DEFINED _ARGS_HINT)
        set(_ARGS_HINT ${CMAKE_CURRENT_LIST_DIR})
    endif ()

    # append all the includes as well
    if (DEFINED _ARGS_INCLUDE)
        list(APPEND _targets ${_ARGS_INCLUDE})
    endif ()

    # attempt getting the available sources now
    file(GLOB_RECURSE _sources "${_ARGS_HINT}/*${_ARGS_EXT}")

    # filter as necessary of our targets if necessary
    if (_targets)
        list(JOIN _targets "|" _joined) # prepare the regex needed
        list(FILTER _sources INCLUDE REGEX ".*(${_joined})\/.*\\.cpp")
    endif ()

    # return the resulting sources now
    set(${_ARGS_OUTPUT} ${_sources} PARENT_SCOPE)
endfunction()

# --  PRIVATE FUNCTIONS  -- #

# Allow defining some common builtins
function(__mono_sources_builtins _output)
    # define the base implementation location
    set(_targets "_impl")

    # otherwise bind all the platform based items
    if (WIN32)
        list(APPEND _targets "_win32")
    endif ()

    if (APPLE)
        list(APPEND _targets "_darwin")
    endif ()

    if (LINUX)
        list(APPEND _targets "_linux")
    endif ()

    if (UNIX)
        list(APPEND _targets "_posix")
    endif ()

    # set the resulting output now
    set(${_output} ${_targets} PARENT_SCOPE)
endfunction()
