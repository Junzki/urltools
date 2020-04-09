# CMakeList.txt : CMake project for urltools, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("urltools" CXX)

set(CMAKE_CXX_STANDARD 14)

set(${PROJECT_NAME}_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE ${PROJECT_NAME}_FILES "${${PROJECT_NAME}_SOURCE}/*")
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_FILES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "lib")

# Add tests
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    include(CTest)

    if (${BUILD_TESTING})
        add_subdirectory(tests)
    endif()
endif()
