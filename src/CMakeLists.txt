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

find_package(ANTTWEAKBAR REQUIRED)
if (ANTTWEAKBAR_FOUND)
    include_directories( ${ANT_TWEAK_BAR_INCLUDE_DIR})
    set(LIBRARIES ${ANT_TWEAK_BAR_LIBRARY})
else (ANTTWEAKBAR_FOUND)
    message(STATUS "AntTweakBar not found.")
endif(ANTTWEAKBAR_FOUND)

set(LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARIES})

if (ANTTWEAKBAR_FOUND)
    include_directories( ${ANT_TWEAK_BAR_INCLUDE_DIR})
    set(LIBRARIES ${ANT_TWEAK_BAR_LIBRARY} ${LIBRARIES})
else (ANTTWEAKBAR_FOUND)
    message(STATUS "AntTweakBar not found.")
endif(ANTTWEAKBAR_FOUND)


add_library(src  graphics/shader.cpp  graphics/drawables/BufferObject.cpp graphics/Buffer.cpp
                 graphics/Texture.cpp graphics/IndexBuffer.cpp
                 graphics/drawables/PlaneBuffer.cpp
                 graphics/drawables/PlaneBuffer.h
                 graphics/drawables/Drawable.h
                 graphics/drawables/BufferSphere.cpp
                 graphics/drawables/BufferSphere.h
                 graphics/drawables/BufferCube.cpp
                 graphics/drawables/BufferCube.h
                 graphics/TextureManager.cpp
                 graphics/TextureManager.h graphics/PhongMaterial.cpp graphics/PhongMaterial.h graphics/Light.cpp graphics/Light.h)

add_library(utils utils/WindowContexts.cpp utils/WindowContexts.h)
add_library(scenes  scenes/window.cpp scenes/window.h
                    scenes/BasicBillboardScene.cpp scenes/BasicBillboardScene.h
                    scenes/LineScene.cpp scenes/LineScene.h
                    scenes/LightingBasicScene.cpp scenes/LightingBasicScene.h
                    scenes/BasicTriangleScene.cpp scenes/BasicTriangleScene.h
                    scenes/SceneIncludes.h)

add_library(input input/Keyboard.cpp input/Keyboard.h input/Keyboard.h input/Mouse.cpp input/Mouse.h)

add_library(math math/Transform.h math/Camera.h math/mathNothing.cpp math/mathNothing.cpp)

#set(GRAHICS_SRC "graphics/shader.cpp" "graphics/Buffer.cpp" "graphics/Texture.cpp" "graphics/IndexBuffer.cpp")
#set(GRAPHICS_HEADERS "graphics/shader.h" "graphics/Buffer.h"  "graphics/Texture.h" "graphics/IndexBuffer.h")
#
#set(INPUT_SRC "input/Keyboard.cpp" "input/Mouse.cpp")
#set(INPUT_HEADERS "input/Keyboard.hpp" "input/Mouse.h")
#
#set(MATH_HEADERS "math/Camera.h" "math/Transform.h")
#
#set(SCENE_SRC "scenes/BasicBillboardScene.cpp" "scenes/BasicTriangleScene.cpp" "scenes/LineScene.cpp" "scenes/window.cpp")
#set(SCENE_HEADERS "scenes/BasicBillboardScene.h" "scenes/BasicTriangleScene.h" "scenes/LineScene.h" "scenes/window.h")
#
#set(UTILS_SRC "utils/WindowContexts.cpp")
#set(UTILS_HEADERS "utils/debugGL.h" "utils/PathFind.h" "utils/WindowContexts.h")
#
#add_library(graphics ${GRAPHICS_SRC} ${GRAPHICS_HEADERS})
#add_library(input ${INPUT_SRC} ${INPUT_HEADERS})
#add_library(math ${MATH_HEADERS})
#add_library(scenes ${SCENE_SRC} ${SCENE_HEADERS})
#add_library(utils ${UTILS_SRC} ${UTILS_HEADERS})

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ext ${CMAKE_SOURCE_DIR}/ext/include)

target_link_libraries(src ${LIBRARIES} ${GLFW_LIBRARY_FLAGS} ${GLEW_LIBRARIES})

add_executable(${PROJECT_NAME} _main.cpp)
target_link_libraries(${PROJECT_NAME}  utils scenes input src)