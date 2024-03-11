target_sources(pawstation
            PRIVATE
            cpu/cpu.cpp
        cpu/interpreter.cpp
            cpu/disassembler.cpp
            bus/bus.cpp
            bus/bus_fmem.cpp)