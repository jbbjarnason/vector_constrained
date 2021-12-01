cmake_minimum_required(VERSION 3.21)
project(vector_constrained)

# build used standard modules
add_custom_target(std_modules ALL
    COMMAND
        ${CMAKE_COMMAND} -E echo "Building standard library modules"
    COMMAND
        g++ -fmodules-ts -std=c++20 -c -x c++-system-header vector initializer_list utility algorithm stdexcept memory cstdio cstddef
    WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}
)

add_library(vector_constrained vector_constrained.cpp)
target_compile_features(vector_constrained
    PUBLIC
        cxx_std_20
)
target_compile_options(vector_constrained
    PUBLIC
        -fmodules-ts
)
add_dependencies(vector_constrained
    std_modules
)

add_executable(example example.cpp)
target_link_libraries(example
    PRIVATE
        vector_constrained
)

