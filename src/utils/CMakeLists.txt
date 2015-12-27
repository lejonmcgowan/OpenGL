set(utils_src LightHelper.cpp TweakBarHelper.cpp WindowContexts.cpp)
set(utils_head DebugGL.h LightHelper.h PathFind.h TweakBarHelper.h WindowContexts.h)

add_library(utils ${utils_src} ${utils_head})