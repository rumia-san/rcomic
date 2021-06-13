cmake_minimum_required (VERSION 3.8)

project ("rcomic")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable (rcomic "main.cpp" "window.h" "image.h" "image.cpp" "window.cpp" "imageList.h" "imageList.cpp")
target_compile_features(rcomic PUBLIC cxx_std_17)
target_link_libraries(rcomic ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
