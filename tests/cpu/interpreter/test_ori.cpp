#include <doctest/doctest.h>
#include <cpu/interpreter.h>
#include <cstring>

/*TEST_CASE("[CPU/INTERPRETER] ORI")
{
    Bus *bus = new Bus();
    Cpu *cpu = new Cpu(bus);
    cpu_interpreter_setup(cpu);
    std::uint32_t opcode = ...*/

// Add test cases for ORI using cpu_interpreter_ori
TEST_CASE("[CPU/INTERPRETER] ORI")
{
    Bus *bus = new Bus();
    Cpu *cpu = new Cpu(bus);
    cpu_interpreter_setup(cpu);
    std::uint32_t opcode = 0x34000000;
    cpu_interpreter_ori(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00000000);
    opcode = 0x34000001;
    cpu_interpreter_ori(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x00000001);
    opcode = 0x340000FF;
    cpu_interpreter_ori(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x000000FF);
    opcode = 0x340000FF;
    cpu_interpreter_ori(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x000000FF);
    opcode = 0x340000FF;
    cpu_interpreter_ori(cpu, opcode);
    CHECK(cpu->registers[rt] == 0x000000FF);
}




