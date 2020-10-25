cmake_minimum_required(VERSION 3.17)
project(CGame C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_ttf
        REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(CGame main.c MapRenderer.c InputEvents.c Rendering.c LinkedList.c FileIO.c Room.c CollisionDetection.c GameCore.h CollisionEvents.c CollisionEvents.h net_utils.c config.h)
IF (WIN32)
    find_library(WS2_32_LIBRARY ws2_32)
    target_link_libraries(CGame ws2_32)
endif()
target_link_libraries(CGame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})