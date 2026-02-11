cmake_minimum_required(VERSION 3.15)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE SRC_FILES
    src/*.cpp 
    external/src/rlImGui/rlImGui.cpp
    external/src/nfd/nfd_win.cpp
    external/src/imgui/*.cpp
)
add_executable(project ${SRC_FILES})

# include raylib headers
target_include_directories(project PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/include/imgui
    ${CMAKE_SOURCE_DIR}/external/include/extras
)

# link raylib (MinGW static)
target_link_libraries(project PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    winmm
)
