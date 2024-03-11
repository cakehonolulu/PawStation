#include <doctest/doctest.h>
#include <cpu/interpreter.h>

TEST_CASE("[CPU/INTERPRETER] LUI")
{
    Bus *bus = new Bus();
    Cpu *cpu = new Cpu(bus);
    cpu_interpreter_setup(cpu);
    std::uint32_t opcode = 0x3C000000;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00000000);
    opcode = 0x3C000001;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00010000);
    opcode = 0x3C0000FF;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00FF0000);
    opcode = 0x3C0000AA;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00AA0000);
    opcode = 0x3C0000FF;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00FF0000);
    opcode = 0x3C0000FF;
    cpu_interpreter_lui(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00FF0000);
}
