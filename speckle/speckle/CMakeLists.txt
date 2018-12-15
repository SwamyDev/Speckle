set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

find_package(OpenGL REQUIRED)

include_directories(external/include)
add_library(speckle ${OPENGL_gl_LIBRARY} external/src/glad/glad.c src/Renderer.cpp include/Renderer.h src/Shader.cpp src/Shader.hpp external/src/stb/stb_image.cpp src/Camera.cpp src/Camera.hpp)

add_custom_command(
        TARGET speckle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/speckle/src/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)