option(CPU_INTERPR "Enable CPU Interpreter tests" ON)
option(CPU_JIT "Enable CPU JIT tests" OFF)

if(NOT CPU_INTERPR AND NOT CPU_JIT)
    message(FATAL_ERROR "No CPU testing option selected. Please enable at least one testing option.")
endif()

if(CPU_INTERPR AND CPU_JIT)
    message(FATAL_ERROR "Both CPU testing options selected. Please enable only one testing option.")
endif()

if(CPU_INTERPR)
    add_subdirectory(interpreter)
endif()

if(CPU_JIT)
    # add_subdirectory(jit)
    message(FATAL_ERROR "JIT testing is not yet implemented.")
endif()
