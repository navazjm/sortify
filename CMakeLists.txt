cmake_minimum_required(VERSION 3.10)
project(sortify VERSION 0.1.0)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# === Paths ===
set(CIMGUI_DIR "${CMAKE_SOURCE_DIR}/libs/cimgui")
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/libs/raylib")  # Raylib submodule path
set(RAYLIB_CIMGUI_DIR "${CMAKE_SOURCE_DIR}/libs/raylib-cimgui")

# === Raylib (submodule) ===
add_subdirectory(${RAYLIB_DIR})

# === Build cimgui ===
add_library(cimgui STATIC
    ${CIMGUI_DIR}/cimgui.cpp
    ${CIMGUI_DIR}/imgui/imgui.cpp
    ${CIMGUI_DIR}/imgui/imgui_demo.cpp
    ${CIMGUI_DIR}/imgui/imgui_draw.cpp
    ${CIMGUI_DIR}/imgui/imgui_widgets.cpp
    ${CIMGUI_DIR}/imgui/imgui_tables.cpp
)

target_include_directories(cimgui PUBLIC
    ${CIMGUI_DIR}
    ${CIMGUI_DIR}/imgui
)

target_compile_options(cimgui PRIVATE -fno-exceptions -fno-rtti -std=c++11 -DIMGUI_DISABLE_OBSOLETE_KEYIO=1)

# === raylib-cimgui ===
add_library(raylib_cimgui STATIC ${RAYLIB_CIMGUI_DIR}/rlcimgui.c)

target_include_directories(raylib_cimgui PUBLIC
    ${CIMGUI_DIR}
    ${CIMGUI_DIR}/imgui
    ${RAYLIB_CIMGUI_DIR}
    ${RAYLIB_CIMGUI_DIR}/extras
    ${RAYLIB_DIR}/src  # Raylib submodule includes
)

target_link_libraries(raylib_cimgui PRIVATE cimgui)

# === sortify main app ===
file(GLOB SORTIFY_SOURCES "src/*.c")
add_library(sortify_lib STATIC ${SORTIFY_SOURCES})

target_include_directories(sortify_lib
    PUBLIC src
    PRIVATE ${RAYLIB_DIR}/src  # Raylib's src directory for raylib.h
    ${CIMGUI_DIR}
    ${RAYLIB_CIMGUI_DIR}
)

target_compile_options(sortify_lib PRIVATE -Wall -Wextra -Werror)

add_executable(sortify "src/sortify.c")

target_include_directories(sortify PRIVATE
    ${RAYLIB_DIR}/src  # Raylib's src directory for raylib.h
    ${CIMGUI_DIR}
    ${RAYLIB_CIMGUI_DIR}
)

target_compile_options(sortify PRIVATE ${RAYLIB_CFLAGS_OTHER})

# Link against Raylib and other necessary libraries
target_link_libraries(sortify
    PRIVATE
        sortify_lib
        raylib_cimgui
        raylib  # Link against Raylib
        stdc++  # Needed for linking C++ symbols from ImGui
)

# Set target properties
set_target_properties(sortify PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# === Install ===
install(TARGETS sortify DESTINATION /usr/local/bin)

