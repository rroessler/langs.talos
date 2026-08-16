# --  PUBLIC FUNCTIONS  -- #

# Attempts reading a version from a given file.
function(mono_version_read _prefix _file)
    # parse the incoming arguments to be used
    cmake_parse_arguments(_ARGS "COMMIT" "SUFFIX" "" ${ARGN})

    # ensure the file-path is valid as well
    cmake_path(SET _file ${_file} NORMALIZE)

    # attempt reading the incoming file
    file(READ ${_file} _version)
    string(STRIP ${_version} _version)

    # finally attempt parsing the result now
    mono_version_parse(${_prefix} ${_version})

    # append a suffix if given one
    if (_ARGS_SUFFIX)
        string(APPEND _version "-${_ARGS_SUFFIX}")
        set("${_prefix}_SUFFIX" ${_ARGS_SUFFIX} PARENT_SCOPE)
    endif ()

    # attempt getting the version-commit if required
    if (_ARGS_COMMIT)
        mono_version_commit("${_prefix}_COMMIT") # resolve commit
        set("${_prefix}_COMMIT" ${${_prefix}_COMMIT} PARENT_SCOPE)
    endif ()

    # set some of the outputs required
    set("${_prefix}_FILE" ${_file} PARENT_SCOPE)
    set("${_prefix}_LONG" ${_version} PARENT_SCOPE)

    # and return some additional items that the version-parse returned
    return(PROPAGATE "${_prefix}_MAJOR" "${_prefix}_MINOR" "${_prefix}_PATCH" "${_prefix}_LABEL" "${_prefix}_SHORT")
endfunction()

# Attempts parsing a version string.
function(mono_version_parse _prefix _version)
    set(_regex "([0-9]+)\\.([0-9]+)\\.([0-9]+)(-([a-zA-Z0-9]+))?")
    string(REGEX MATCH ${_regex} _ ${_version}) # parse the version

    # prepare all the base variables to be output
    set("${_prefix}_MAJOR" ${CMAKE_MATCH_1} PARENT_SCOPE)
    set("${_prefix}_MINOR" ${CMAKE_MATCH_2} PARENT_SCOPE)
    set("${_prefix}_PATCH" ${CMAKE_MATCH_3} PARENT_SCOPE)
    set("${_prefix}_LABEL" ${CMAKE_MATCH_5} PARENT_SCOPE)

    # also bind the shorthand version as well
    set("${_prefix}_SHORT" "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}" PARENT_SCOPE)
endfunction()

macro(mono_version_commit _output)
    # ensure we find Git so we can use it
    find_package(Git QUIET)

    # attempt getting the current hash
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE ${_output}
        OUTPUT_STRIP_TRAILING_WHITESPACE)
endmacro()

# Handles getting the current "Git" branch safely.
macro(mono_version_branch _output)
    # ensure we find Git so we can use it
    find_package(Git QUIET)

    # attempt finding the necessary branch to be shown
    execute_process(
        COMMAND ${GIT_EXECUTABLE} branch --show-current
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE ${_output}
        OUTPUT_STRIP_TRAILING_WHITESPACE)
endmacro()
