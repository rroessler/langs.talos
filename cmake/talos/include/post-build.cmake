# --  MODULE INSTALLATION  -- #

# Ignore if in cross-compilation mode
if (NOT TALOS_OPTION_POSTBUILD)
    return()
endif ()

# Set a suitable shell extension now
if (WIN32)
    set(TALOS_EXTENSION_SCRIPT ".ps1")
else ()
    set(TALOS_EXTENSION_SCRIPT ".sh")
endif ()

# Remove the original files available in the output
file(REMOVE_RECURSE "${TALOS_DIRENT_OUTPUT}/crates")

# Get all the available ".tal" and "_crate.jsonc" files
file(GLOB_RECURSE TALOS_SOURCES_SCRIPT "${TALOS_DIRENT_SCRIPT}/*${TALOS_EXTENSION_SCRIPT}")
file(GLOB_RECURSE TALOS_SOURCES_CRATES "${TALOS_DIRENT_CRATES}/*.tal" "${TALOS_DIRENT_CRATES}/*.jsonc")

# Copy across the sources to the output directory necessary
foreach (_fp IN LISTS TALOS_SOURCES_SCRIPT)
    # ensure we ignore certain directories
    if (_fp MATCHES "compile")
        continue ()
    endif ()

    cmake_path(RELATIVE_PATH _fp BASE_DIRECTORY ${TALOS_DIRENT_SCRIPT})
    cmake_path(GET _fp PARENT_PATH _parent) # get the parent path to be used

    file(MAKE_DIRECTORY "${TALOS_DIRENT_OUTPUT}/scripts/${_parent}")
    file(COPY_FILE "${TALOS_DIRENT_SCRIPT}/${_fp}" "${TALOS_DIRENT_OUTPUT}/scripts/${_fp}" ONLY_IF_DIFFERENT)
endforeach ()

# Copy across the sources to the output directory necessary
foreach (_fp IN LISTS TALOS_SOURCES_CRATES)
    # ensure we ignore all testing files from the output
    if (_fp MATCHES ".test.tal$")
        continue ()
    endif ()

    cmake_path(RELATIVE_PATH _fp BASE_DIRECTORY ${TALOS_DIRENT_CRATES})
    cmake_path(GET _fp PARENT_PATH _parent) # get the parent path to be used

    file(MAKE_DIRECTORY "${TALOS_DIRENT_OUTPUT}/crates/${_parent}")
    file(COPY_FILE "${TALOS_DIRENT_CRATES}/${_fp}" "${TALOS_DIRENT_OUTPUT}/crates/${_fp}" ONLY_IF_DIFFERENT)
endforeach ()
