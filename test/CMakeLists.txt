project(test)

include_directories(include)

include_directories("${CMAKE_SOURCE_DIR}/speckle/src")

add_executable(SpeckleUnitTests unit/main.cpp)
target_link_libraries(SpeckleUnitTests speckle_static)

add_executable(SpeckleIntegrationTests integration/main.cpp)
target_link_libraries(SpeckleIntegrationTests speckle_static)