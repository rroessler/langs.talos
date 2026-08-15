# --  PUBLIC METHODS  -- #

# Factory for the "mono::sanitize" library
macro(mono_library_sanitize _enabled)
    # define the base properties
    set(MONO_TARGET_SANITIZE "${MONO_TARGET_SUPER}_sanitize")

    # define a set of recommended warnings to be attached
    add_library(${MONO_TARGET_SANITIZE} INTERFACE)
    add_library(${MONO_TARGET_SUPER}::sanitize ALIAS ${MONO_TARGET_SANITIZE})

    # and allow the target to act as an interface for others if enabled
    if (${_enabled})
        target_link_options(${MONO_TARGET_SANITIZE} INTERFACE -fsanitize=address)
        target_compile_options(${MONO_TARGET_SANITIZE} INTERFACE -fsanitize=address -fno-omit-frame-pointer)
    endif ()
endmacro()
