


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_executable(
#     sim
#     ../src/main.cpp
#     ../src/state.cpp
#     ../src/users.cpp
#     sim.cpp
#     )

# set_target_properties(
#     sim
#     PROPERTIES
#     LINK_FLAGS "--shell-file ${CMAKE_SOURCE_DIR}/sim.html")


# target_include_directories(
#     sim
#     PRIVATE
#     include
#     ../src/
# )


# set_target_properties(
#     sim PROPERTIES
#     SUFFIX ".html")



add_executable(
    sim
    ../src/main.cpp
    ../src/state.cpp
    ../src/users.cpp
    ../src/led.cpp
    ../src/archive.cpp
    ../src/cardreader.cpp
    nativesim.cpp
)

target_include_directories(
    sim
    PRIVATE
    include
    ../src/
)
