cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -g)
endif()

# GLAD
add_library(glad libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# GLFW (локальная версия)
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

include_directories(
    glad/include
    src/include
    log
    gui
    gui/backends
    libs/glm
    libs/glm/gtc
    libs/nlohmann
)

# Исходники
add_executable(Sim 
    src/main.cpp
    src/render.cpp
    src/camera3d.cpp
    src/space_mesh.cpp

    gui/imgui.cpp
    gui/imgui_draw.cpp
    gui/imgui_widgets.cpp
    gui/imgui_tables.cpp
    gui/imgui_demo.cpp
    gui/backends/imgui_impl_glfw.cpp
    gui/backends/imgui_impl_opengl2.cpp
)

# Линковка
target_link_libraries(Sim
    glad
    glfw
)

# Windows
if (WIN32)
    target_link_libraries(Sim
        opengl32
        glu32
    )
endif()

# Linux
if (UNIX AND NOT APPLE)
    target_link_libraries(Sim
        X11 Xrandr Xi Xxf86vm Xcursor pthread dl GL GLU
    )
endif()
