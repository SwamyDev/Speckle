set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

find_package(OpenGL REQUIRED)

file(COPY src/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories(external/glad/include)
add_library(speckle ${OPENGL_gl_LIBRARY} external/glad/src/glad.c src/Renderer.cpp include/Renderer.h src/Shader.cpp src/Shader.hpp)