# --  PUBLIC FUNCTIONS  -- #

# Allows enabling "sccache" for projects.
macro(mono_sccache_setup)
    # attempt finding the underlying program (start with "sscache")
    find_program(MONO_CCACHE_PROGRAM sccache)

    # finally attempt setting our necessary properties now
    if (MONO_CCACHE_PROGRAM)
        mono_message_status("Enabling 'sccache': ${MONO_CCACHE_PROGRAM}")

        set(CMAKE_C_COMPILER_LAUNCHER ${MONO_CCACHE_PROGRAM})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${MONO_CCACHE_PROGRAM})

        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
        cmake_policy(SET CMP0141 NEW) # required for use with "MSVC" to work
    else ()
        mono_message_warn("Could not enable 'sccache': could not find program")
    endif ()
endmacro()
