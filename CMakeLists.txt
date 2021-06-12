cmake_minimum_required (VERSION 3.8)

project ("rcomic")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable (rcomic "main.cpp" "window.h" "image.h" "image.cpp" "window.cpp")
target_compile_features(rcomic PUBLIC cxx_std_17)
target_link_libraries(rcomic ${SDL2_LIBRARIES})

# TODO: 如有需要，请添加测试并安装目标。
