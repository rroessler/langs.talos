# --  PUBLIC FUNCTIONS  -- #

# If you need to use response files due to some commands being too large
macro(mono_feature_responses)
    set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS ON)
    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS ON)
    set(CMAKE_C_RESPONSE_FILE_LINK_FLAG "@")
    set(CMAKE_CXX_RESPONSE_FILE_LINK_FLAG "@")
    set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON CACHE INTERNAL "")
endmacro()

# Allows hiding deprecation warnings
macro(mono_feature_deprecation _state)
    set(CMAKE_WARN_DEPRECATED ${_state} CACHE BOOL "" FORCE)
endmacro()

# Enables improved performance on MacOS (no weak-def symbol lookups)
macro(mono_feature_visibility)
    # prepare the available arguments now
    cmake_parse_arguments(_ARGS "" "TARGET;PRESET" "" ${ARGN})

    if (NOT DEFINED _ARGS_PRESET)
        set(_ARGS_PRESET "hidden")
    endif ()

    if (_ARGS_PRESET STREQUAL "hidden")
        set(_inlines ON)
    else ()
        set(_inlines OFF)
    endif ()

    if (DEFINED _ARGS_TARGET)
        mono_message_status("Setting Visibility '${_ARGS_PRESET}' for '${_ARGS_TARGET}'")
        set_target_properties(${_ARGS_TARGET} PROPERTIES CXX_VISIBILITY_PRESET ${_ARGS_PRESET})
        set_target_properties(${_ARGS_TARGET} PROPERTIES VISIBILITY_INLINES_HIDDEN ${_inlines})
    else ()
        mono_message_status("Setting Global Visibility '${_ARGS_PRESET}'")
        set(CMAKE_CXX_VISIBILITY_PRESET ${_ARGS_PRESET})
        set(CMAKE_VISIBILITY_INLINES_HIDDEN ${_inlines})
    endif ()
endmacro()

# Handles setting specific "ninja" properties
macro(mono_feature_ninja)
    if (APPLE AND CMAKE_GENERATOR STREQUAL Ninja)
        # for some reason, we cannot find "macosx"
        set(CMAKE_OSX_SYSROOT macosx)

        # attempt finding "llvm-ar" to be used now
        find_program(CMAKE_AR_TEMPORARY "llvm-ar")

        # also need to update the use of "llvm-ar"
        set(CMAKE_AR ${CMAKE_AR_TEMPORARY} CACHE FILEPATH "Archiver" FORCE)
        set(CMAKE_C_ARCHIVE_CREATE "${CMAKE_AR} qc <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_CXX_ARCHIVE_CREATE "${CMAKE_AR} qc <TARGET> <LINK_FLAGS> <OBJECTS>")

        # and clean up our temporary variables now
        unset(CMAKE_AR_TEMPORARY)
    endif ()
endmacro()
