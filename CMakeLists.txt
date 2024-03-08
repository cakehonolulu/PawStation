cmake_minimum_required(VERSION 3.26)
project(pawstation)

set(CMAKE_CXX_STANDARD 23)

# Option to choose the frontend (default: ImGui)
option(USE_IMGUI_FRONTEND "Use ImGui frontend" OFF)
option(USE_HEADLESS_FRONTEND "Use headless frontend" OFF)
option(RUN_TESTS "Enable testing" ON)

# Both USE_IMGUI_FRONTEND and USE_HEADLESS_FRONTEND options can't be active at the same time, check against it
if(USE_IMGUI_FRONTEND AND USE_HEADLESS_FRONTEND)
    message(FATAL_ERROR "Can't enable ImGui and Headless frontends at the same time!")
endif()

# Check if there's one of the frontend options enabled
if(NOT USE_IMGUI_FRONTEND AND NOT USE_HEADLESS_FRONTEND AND NOT RUN_TESTS)
    message(FATAL_ERROR "No frontend selected, please enable ImGui, Headless frontend, or testing!")
endif()


# Specify the main executable
add_executable(pawstation)

add_subdirectory(src)
add_subdirectory(utils)

# Add frontend or testing based on options
if (!RUN_TESTS)
    if(NOT USE_IMGUI_FRONTEND AND NOT USE_HEADLESS_FRONTEND)
        message(FATAL_ERROR "No frontend selected, please enable ImGui or Headless frontend!")
    else()
        add_subdirectory(frontend)
    endif()
else()
    add_subdirectory(tests)
endif()

# Set include directories for the main executable
target_include_directories(pawstation PRIVATE ${PROJECT_SOURCE_DIR}/include)
