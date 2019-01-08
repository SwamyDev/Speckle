if (NOT MSVC)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")
endif ()

find_package(OpenGL REQUIRED)

include_directories(external/glad/include)
add_library(speckle_static STATIC external/glad/src/glad.c include/rendering.hpp src/rendering.cpp src/Renderer.cpp src/Renderer.hpp)
target_link_libraries(speckle_static ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})
add_library(speckle SHARED external/glad/src/glad.c include/rendering.hpp src/rendering.cpp src/Renderer.cpp src/Renderer.hpp)
target_link_libraries(speckle ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})

if(CMAKE_BUILD_TYPE STREQUAL Release)
    if (MSVC)
        set(SPECKLE_PATH bin/)
        set(SPECKLE_NAME speckle.dll)
    else ()
        set(SPECKLE_PATH lib/)
        set(SPECKLE_NAME libspeckle.so)
    endif ()

    add_custom_command(TARGET speckle POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/${SPECKLE_PATH}/${SPECKLE_NAME}"
            "${CMAKE_SOURCE_DIR}/fleck/fleck/lib/${SPECKLE_NAME}")
endif()