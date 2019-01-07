set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

find_package(OpenGL REQUIRED)

include_directories(external/glad/include)
add_library(speckle STATIC external/glad/src/glad.c include/rendering.hpp src/rendering.cpp src/Renderer.cpp src/Renderer.hpp)
target_link_libraries(speckle ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})
add_library(Speckle SHARED external/glad/src/glad.c include/rendering.hpp src/rendering.cpp src/Renderer.cpp src/Renderer.hpp)
target_link_libraries(Speckle ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})

if(CMAKE_BUILD_TYPE STREQUAL Release)
    add_custom_command(TARGET Speckle POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/libSpeckle.so"
            "${CMAKE_SOURCE_DIR}/fleck/fleck/lib/libSpeckle.so")
endif()