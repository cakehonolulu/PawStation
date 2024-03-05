cmake_minimum_required(VERSION 3.26)
project(pawstation)

set(CMAKE_CXX_STANDARD 17)

add_executable(pawstation
        pawstation.cpp)

target_include_directories(pawstation PRIVATE ${PROJECT_SOURCE_DIR}/include)
