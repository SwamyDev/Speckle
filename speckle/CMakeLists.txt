cmake_minimum_required(VERSION 3.13)
project(speckle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories ("${PROJECT_SOURCE_DIR}/speckle/include")
add_subdirectory(speckle)

include(FetchContent)

set(WINDOW_EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/window/external)
set(GLAD_DIR ${WINDOW_EXTERNAL_DIR}/glad)

FetchContent_Declare(glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw.git
        GIT_TAG         origin/master)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR})
endif()

include_directories(${GLAD_DIR}/include)
add_executable(Speckle window/main.cpp window/external/glad/src/glad.c)
target_link_libraries(Speckle speckle ${OPENGL_gl_LIBRARY} glfw)