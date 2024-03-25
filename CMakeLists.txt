
cmake_minimum_required(VERSION 3.20)
project(taggsystem)

add_library(
    taggsystem
    src/users.cpp
    src/state.cpp
)

enable_testing()

add_subdirectory(test)
add_subdirectory(sim)

