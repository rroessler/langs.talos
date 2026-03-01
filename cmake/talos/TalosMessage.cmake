# --  PUBLIC FUNCTIONS  -- #

# Handles printing messages with a prefix.
function(talos_message_status)
    __mono_message_impl(STATUS ${TALOS_TOOLCHAIN_TITLE} ${ARGN})
endfunction()
