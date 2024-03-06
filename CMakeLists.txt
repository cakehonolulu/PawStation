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

# Specify the main executable
add_executable(pawstation)

add_subdirectory(src)
add_subdirectory(frontend)

# Set include directories for the main executable
target_include_directories(pawstation PRIVATE ${PROJECT_SOURCE_DIR}/include)
