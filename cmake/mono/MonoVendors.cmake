# --  PUBLIC METHODS  -- #

# Handles fetching vendor modules.
function(mono_vendor_declare _target _vtag)
    # parse the incoming arguments now
    __mono_vendor_repo(_repo ${ARGN})
    __mono_vendor_version(${_vtag} _version)

    # attempt parsing the hidden details now
    cmake_parse_arguments(_ARGS "NP" "TAG" "" ${ARGN})

    # update the tag to be used
    if (NOT DEFINED _ARGS_TAG)
        # prepare the arguments tag to be used
        set(_ARGS_TAG ${_vtag})
    endif ()

    # attempt fetching the incoming content now
    __mono_vendor_declare(${_target} ${_repo} ${_ARGS_TAG})
endfunction()

# Otherwise we actually require it from here
function(mono_vendor_require _target)
    if (NOT TARGET ${_target})
        FetchContent_MakeAvailable(${_target})
        find_package(${_target} REQUIRED QUIET)
        mono_message_status("Found Vendor '${_target}'")
    endif ()
endfunction()

# --  PRIVATE METHODS  -- #

# Handles stripping versions of their prefix
macro(__mono_vendor_version _vtag _version)
    string(REGEX REPLACE "^v" "" _version ${_vtag})
endmacro()

# Gets the incoming vendor version
function(__mono_vendor_repo _repo)
    # parse the incoming arguments
    cmake_parse_arguments(_ARGS "" "REPO" "" ${ARGN})

    # ensure the version was assigned
    if (NOT DEFINED _ARGS_REPO)
        mono_message_fatal("Expected a vendor repository")
    endif ()

    # define the necessary version now
    set(${_repo} "https://github.com/${_ARGS_REPO}" PARENT_SCOPE)
endfunction()

function(__mono_vendor_declare _target _repo _tag)
    # ignore if the target already exists
    if (NOT TARGET ${_target})
        # include the fetch-content handler
        include(FetchContent)

        # attempt fetching the incoming content now
        FetchContent_Declare(
            ${_target}
            GIT_TAG ${_tag}
            GIT_REPOSITORY ${_repo}
            GIT_SHALLOW ON
            OVERRIDE_FIND_PACKAGE)
    endif ()
endfunction()

# --  MODULE DEFINITION  -- #
