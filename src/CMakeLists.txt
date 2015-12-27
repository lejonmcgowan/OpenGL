include_directories(${TESTPROJECT2_SOURCE_DIR})
link_directories(${TESTPROJECT2_BINARY_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(GLEW_INCLDUE_DIRS)

find_package(SOIL REQUIRED)
include_directories(SOIL_INCLDUE_DIRS)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ext ${CMAKE_SOURCE_DIR}/ext/include)

#setup all required libraries
set(ext_libraries ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARIES})

#setup optional libraries
if (ANTTWEAKBAR_FOUND)
    include_directories( ${ANT_TWEAK_BAR_INCLUDE_DIR})
    set(LIBRARIES ${ANT_TWEAK_BAR_LIBRARY} ${LIBRARIES})
else (ANTTWEAKBAR_FOUND)
    message(STATUS "AntTweakBar not found.")
endif(ANTTWEAKBAR_FOUND)

#macro to get all the subdirectory names. from:
#http://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
macro(MACRO_SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

MACRO_SUBDIRLIST(src_libraries ${CMAKE_CURRENT_SOURCE_DIR})

foreach(src_library ${src_libraries})
    add_subdirectory(${src_library})
endforeach()


add_executable(${PROJECT_NAME} _main.cpp)

#all libraries will be named based on their subdirectory name
target_link_libraries(${PROJECT_NAME} ${src_libraries} ${ext_libraries})