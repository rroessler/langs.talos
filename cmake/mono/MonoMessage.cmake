# --  PUBLIC FUNCTIONS  -- #

# Handles printing status messages.
function(mono_message_debug)
    __mono_message_impl(DEBUG ${MONO_TOOLCHAIN_TITLE} ${ARGN})
endfunction()

# Handles printing status messages.
function(mono_message_status)
    __mono_message_impl(STATUS ${MONO_TOOLCHAIN_TITLE} ${ARGN})
endfunction()

# Handles printing warning messages.
function(mono_message_warn)
    __mono_message_impl(WARNING ${MONO_TOOLCHAIN_TITLE} ${ARGN})
endfunction()

# Handles printing fatal messages.
function(mono_message_fatal)
    __mono_message_impl(FATAL_ERROR ${MONO_TOOLCHAIN_TITLE} ${ARGN})
endfunction()

# --  PRIVATE FUNCTIONS  -- #

# Handles printing messages with a prefix.
function(__mono_message_impl _type _prefix)
    set(_message "${_prefix}: ")
    math(EXPR _argc "${ARGC} - 1")

    if (_argc GREATER 1)
        foreach (_ii RANGE 2 ${_argc})
            string(APPEND _message "${ARGV${_ii}}")
        endforeach ()
    endif ()

    message(${_type} "${_message}")
endfunction()
