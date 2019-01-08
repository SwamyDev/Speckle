cmake_minimum_required(VERSION 3.12)
project(speckle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories ("${PROJECT_SOURCE_DIR}/speckle/include")
add_subdirectory(speckle)

add_subdirectory(test)

include(FetchContent)

FetchContent_Declare(glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw.git
        GIT_TAG         origin/master)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR})
endif()

include_directories(${glfw_SOURCE_DIR}/include)
include_directories("speckle/external/glad/include")
add_executable(SpeckleWindow speckle/external/glad/src/glad.c window/main.cpp)
target_link_libraries(SpeckleWindow speckle_static glfw)