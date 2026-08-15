# --  PUBLIC FUNCTIONS  -- #

# Handles declaring "talos" packages
function(talos_package_declare _package)
    set(_hint "${TALOS_DIRENT_SOURCE}/${_package}")
    mono_package_declare(${_package} HINT ${_hint})
endfunction()

# Handles requiring "talos" packages
function(talos_package_require)
    foreach (_package IN LISTS ARGN)
        if (TARGET ${_package})
            continue ()
        endif ()

        # can safely require the package now
        talos_package_declare(${_package})
        mono_package_require(${_package})
    endforeach ()
endfunction()
