
cmake_minimum_required(VERSION 3.15)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------
# Platform-aware Native File Dialog
# -----------------------------------
set(NFD_SOURCE external/src/nfd/nfd_portal.cpp)
if(WIN32)
    set(NFD_SOURCE external/src/nfd/nfd_win.cpp)
endif()

# -----------------------------------
# Source files
# -----------------------------------
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    external/src/rlImGui/rlImGui.cpp
    ${NFD_SOURCE}
    external/src/imgui/*.cpp
)

add_executable(project ${SRC_FILES})

# -----------------------------------
# Include directories
# -----------------------------------
target_include_directories(project PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/include/imgui
    ${CMAKE_SOURCE_DIR}/external/include/extras
)

# -----------------------------------
# Platform-specific libraries
# -----------------------------------
if(WIN32)
    # Windows: link raylib + winmm (urutan penting!)
    target_link_libraries(project PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/libraylib.a
        winmm
    )
else()
    # Non-Windows: link dbus (portal backend) + raylib
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(DBUS REQUIRED dbus-1)

    target_include_directories(project PRIVATE ${DBUS_INCLUDE_DIRS})
    target_link_libraries(project PRIVATE
        ${DBUS_LIBRARIES}
        ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    )
endif()
