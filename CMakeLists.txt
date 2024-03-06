cmake_minimum_required(VERSION 3.26)
project(pawstation)

set(CMAKE_CXX_STANDARD 17)

# Option to choose the frontend (default: ImGui)
option(USE_IMGUI_FRONTEND "Use ImGui frontend" ON)
option(USE_HEADLESS_FRONTEND "Use headless frontend" OFF)

# Both USE_IMGUI_FRONTEND and USE_HEADLESS_FRONTEND options can't be active at the same time, check against it
if(USE_IMGUI_FRONTEND AND USE_HEADLESS_FRONTEND)
    message(FATAL_ERROR "Can't enable ImGui and Headless frontends at the same time!")
endif()

# Also check if there's one of the frontend options enabled, we can't compile without any frontend selected
if(NOT USE_IMGUI_FRONTEND AND NOT USE_HEADLESS_FRONTEND)
    message(FATAL_ERROR "No frontend selected, please enable ImGui or Headless frontend!")
endif()

add_executable(pawstation
        pawstation.cpp)

# Add all the required steps for ImGui frontend
if(USE_IMGUI_FRONTEND)
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

    # Add ImGui source files to the executable
    target_sources(pawstation PRIVATE ${IMGUI_SOURCES})

    # Add OpenGL, SDL2 and ImGui include files to compilation
    target_include_directories(pawstation PRIVATE
            ${OPENGL_INCLUDE_DIRS}
            ${SDL2_INCLUDE_DIRS}
            ${IMGUI_SOURCE_DIR}
            ${IMGUI_SOURCE_DIR}/backends)

    # Add OpenGL and SDL2 libraries to the executable
    target_link_libraries(pawstation PRIVATE ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
endif()

target_include_directories(pawstation PRIVATE ${PROJECT_SOURCE_DIR}/include)
