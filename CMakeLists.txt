cmake_minimum_required(VERSION 3.26)
project(pawstation)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# Add ImGui source files
set(IMGUI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/imgui)

set(IMGUI_SOURCES
        "${IMGUI_SOURCE_DIR}/imgui.h"
        "${IMGUI_SOURCE_DIR}/imgui.cpp"
        "${IMGUI_SOURCE_DIR}/imgui_demo.cpp"
        "${IMGUI_SOURCE_DIR}/imgui_draw.cpp"
        "${IMGUI_SOURCE_DIR}/imgui_widgets.cpp"
        "${IMGUI_SOURCE_DIR}/imgui_tables.cpp"
        "${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp"
        "${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp"
        "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

add_executable(pawstation
        pawstation.cpp
        ${IMGUI_SOURCES})  # Include ImGui sources in the target


target_include_directories(pawstation
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${IMGUI_SOURCE_DIR}
        ${IMGUI_SOURCE_DIR}/backends)

target_link_libraries(pawstation PRIVATE ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
