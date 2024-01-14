


include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)


# Make GoogleTest available to the project
FetchContent_MakeAvailable(googletest)

# Now GoogleTest can be used in your project
include(GoogleTest)

add_executable(
    user_test
    user_test.cpp
    state_test.cpp
    testclasses.cpp
)

target_link_libraries(
    user_test
    gtest_main
    taggsystem
)

target_include_directories(
    user_test
    PRIVATE
    ../src
)

add_test(user_test user_test)
