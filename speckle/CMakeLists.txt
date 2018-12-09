cmake_minimum_required(VERSION 3.13)
project(speckle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories ("${PROJECT_SOURCE_DIR}/speckle/include")
add_subdirectory(speckle)

include(FetchContent)

FetchContent_Declare(glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw.git
        GIT_TAG         origin/master)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR})
endif()

add_executable(Speckle window/main.cpp)
target_link_libraries(Speckle speckle glfw)