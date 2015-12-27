set(scene_src BasicBillboardScene.cpp BasicTriangleScene.cpp LightingBasicScene.cpp LineScene.cpp
        MultipleLightsScene.cpp Window.cpp)
set(scene_head BasicBillboardScene.h BasicTriangleScene.h LightingBasicScene.h LineScene.h MultipleLightsScene.h
        Scene.h SceneIncludes.h Window.h)

add_library(scenes ${scene_src} ${scene_head})