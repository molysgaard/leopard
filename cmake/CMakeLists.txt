cmake_minimum_required(VERSION 3.16)
project(leopard_cmake)

set(CMAKE_CXX_STANDARD 17)

# NOTE: Adding this line to your project will give you a library `leopard` which you can link to to get the correct include and linker directories and compile and linker flags.
include(leopard.cmake)

# Your own CMake code
add_executable(leopard_example
        src/example.cpp
        )

add_executable(leopard_tests
        src/tests.cpp
)

# NOTE: Here we are linking our application to the `leopard` library defined by the include above.
#       This will automatically give your application the correct include and linker directories,
#       as well as correct compile and linker flags.
target_link_libraries(leopard_example PRIVATE leopard)
target_link_libraries(leopard_tests PRIVATE leopard)
