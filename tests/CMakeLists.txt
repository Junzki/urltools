cmake_minimum_required(VERSION 3.8)


include_directories(${PROJECT_SOURCE_DIR}/src)
find_package(Catch2 REQUIRED)

set(TEST_LIBRARIES Catch2::Catch2 ${PROJECT_NAME})

# Add source to this project's executable.
add_executable(urlcode_test "urlcode.cpp")
target_link_libraries(urlcode_test ${TEST_LIBRARIES})


include(Catch)
catch_discover_tests(urlcode_test)
