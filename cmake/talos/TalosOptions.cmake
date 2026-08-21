# --  OPTIONS  -- #

# Prepare some options to be used
option(TALOS_OPTION_CANARY "Enable canary builds" ON)
option(TALOS_OPTION_STRICT "Enable strict warnings" OFF)
option(TALOS_OPTION_TESTING "Enable building tests" OFF)
option(TALOS_OPTION_SANITIZE "Enable address sanitizer" OFF)
option(TALOS_OPTION_POSTBUILD "Enables post-build outputs" ON)

# Define the core compilation options to be used
set(TALOS_OPTION_CXXSTD "26" CACHE INTERNAL "The CXX standard library")
