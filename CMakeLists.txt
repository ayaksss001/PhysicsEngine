cmake_minimum_required(VERSION 3.10)
project(RelativitySimulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(glad libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

include_directories(
    glad/include
    src/include
    log
    gui
    gui/backends
    libs/glm
    libs/glm/ext
    libs/glm/detail
    libs/glm/gtc
    libs/glm/gtx
    libs/glm/simd
    libs/nlohmann
    libs/nlohmann/detail
    libs/nlohmann/thirdparty

)

add_executable(Sim 
    src/main.cpp
    src/render.cpp
    log/log.cpp
    gui/imgui.cpp
    gui/imgui_draw.cpp
    gui/imgui_widgets.cpp
    gui/imgui_tables.cpp
    gui/imgui_demo.cpp
    gui/backends/imgui_impl_glfw.cpp
    gui/backends/imgui_impl_opengl2.cpp
    src/camera3d.cpp
    src/space_mesh.cpp
)

target_link_libraries(Sim
    PRIVATE
    glad
    glfw
    X11
    Xrandr
    Xi
    Xxf86vm
    Xcursor
    pthread
    dl
    GL
    glm
    GLU
)
