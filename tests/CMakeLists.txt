cmake_minimum_required(VERSION 3.8)


include_directories(${PROJECT_SOURCE_DIR}/src)
find_package(Catch2 REQUIRED)

set(TEST_LIBRARIES Catch2::Catch2 ${PROJECT_NAME})

# Add source to this project's executable.
add_executable(test_quote "test_quote.cpp")
target_link_libraries(test_quote ${TEST_LIBRARIES})

add_executable(test_authority "test_authority.cpp")
target_link_libraries(test_authority ${TEST_LIBRARIES})

add_executable(test_url "test_url.h" "test_url.cpp")
target_link_libraries(test_url ${TEST_LIBRARIES})


include(Catch)
catch_discover_tests(test_quote)
catch_discover_tests(test_authority)
catch_discover_tests(test_url)
