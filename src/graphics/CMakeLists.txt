set(graphics_src Buffer.cpp IndexBuffer.cpp Light.cpp Shader.cpp Texture.cpp TextureManager.cpp)
#not necessary, but it helps IDE identify files in project
set(graphics_head Buffer.h IndexBuffer.h Light.h Shader.h ShaderManager.h Texture.h TextureManager.h)

MACRO_SUBDIRLIST(graphics_libraries ${CMAKE_CURRENT_SOURCE_DIR})

foreach(graphics_subdir ${graphics_subdirs})
    add_subdirectory(${graphics_subdir})
endforeach()

message(WARNING "graphics_libraries: " ${graphics_libraries})

add_library(graphics ${graphics_src} ${graphics_head})
target_link_libraries(graphics ${graphics_libraries})