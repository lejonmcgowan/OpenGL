include_directories(${TESTPROJECT2_SOURCE_DIR})
link_directories(${TESTPROJECT2_BINARY_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
set(GLFW_LIBRARY_FLAGS -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread)

find_package(GLEW REQUIRED)
include_directories(GLEW_INCLDUE_DIRS)

find_package(SOIL REQUIRED)
include_directories(SOIL_INCLDUE_DIRS)

set(LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARIES})

add_library(src window.cpp graphics/shader.cpp scenes/BasicBillboardScene.cpp graphics/BufferObject.cpp graphics/Buffer.cpp graphics/Texture.cpp graphics/IndexBuffer.cpp input/Keyboard.cpp utils/WindowContexts.cpp utils/WindowContexts.h utils/WindowContexts.cpp utils/WindowContexts.h input/Mouse.cpp input/Mouse.h scenes/BasicTriangleScene.cpp scenes/BasicTriangleScene.h)
target_link_libraries(src ${LIBRARIES} ${GLFW_LIBRARY_FLAGS} ${GLEW_LIBRARIES})

add_executable(${PROJECT_NAME} _main.cpp)
target_link_libraries(${PROJECT_NAME} src)