# --  PUBLIC METHODS  -- #

# Factory for the "mono::warnings" library
macro(mono_library_warnings _strict)
    # define the base properties
    set(MONO_TARGET_WARNINGS "${MONO_TARGET_SUPER}_warnings")

    # define all the available warnings now
    set(MONO_WARNINGS_MSVC /W4)
    set(MONO_WARNINGS_UNIX
        -Wall
        -Wextra
        -Wshadow
    )

    # enable stricter library warnings
    if (${_strict})
    endif ()

    # define a set of recommended warnings to be attached
    add_library(${MONO_TARGET_WARNINGS} INTERFACE)
    add_library(${MONO_TARGET_SUPER}::warnings ALIAS ${MONO_TARGET_WARNINGS})

    # and allow the target to act as an interface for others
    target_compile_options(${MONO_TARGET_WARNINGS} INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:${MONO_WARNINGS_MSVC}>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:${MONO_WARNINGS_UNIX}>
    )
endmacro()
