cmake_minimum_required(VERSION 3.8)


include_directories(${PROJECT_SOURCE_DIR}/src)
find_package(Catch2 REQUIRED)

set(TEST_LIBRARIES Catch2::Catch2 ${PROJECT_NAME})

# Add source to this project's executable.
add_executable(urlcode_test "urlcode.cpp")
target_link_libraries(urlcode_test ${TEST_LIBRARIES})

add_executable(user_info_test "user_info.cpp")
target_link_libraries(user_info_test ${TEST_LIBRARIES})

add_executable(url_test "url.cpp")
target_link_libraries(url_test ${TEST_LIBRARIES})


include(Catch)
catch_discover_tests(urlcode_test)
catch_discover_tests(user_info_test)
catch_discover_tests(url_test)
