# --  PACKAGE SETUP  -- #

# Attempt requiring the desired dependencies
talos_package_require(${TALOS_TARGET_FORGE})

# --  PACKAGE PROPERTIES  -- #

# Get all the availble sources for the project
talos_sources_glob(TALOS_SOURCES_SUPER)

# --  PACKAGE DEFINITION  -- #

# Define the base library now
talos_library_declare(${TALOS_TARGET_SUPER} PCH SOURCES ${TALOS_SOURCES_SUPER} LIBRARIES
    $<LINK_LIBRARY:WHOLE_ARCHIVE,talos::forge>
    mono::warnings
)
