# this file sets some common properties

# set the current compilers now
find_program(CMAKE_C_COMPILER "clang")
find_program(CMAKE_CXX_COMPILER "clang++")

# ensure the compilers we set validly
if(NOT CMAKE_C_COMPILER OR NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "Mono: Could not find 'clang' compiler")
endif()
