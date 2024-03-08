option(TEST_CPU "Enable CPU tests" ON)
option(TEST_BUS "Enable BUS tests" OFF)

if(NOT TEST_CPU AND NOT TEST_BUS)
    message(FATAL_ERROR "No testing option selected. Please enable at least one testing option.")
endif()

target_include_directories(pawstation PRIVATE ${CMAKE_SOURCE_DIR}/external/doctest)

if(TEST_CPU)
    add_subdirectory(cpu)
endif()
