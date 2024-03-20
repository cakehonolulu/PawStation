#pragma once

#include <cstdint>
#include <cpu/cpu.h>
#include <iostream>

class Cpu;

void step_interpreter(Cpu *cpu);
void interpreter_setup(Cpu *cpu);

void interpreter_lui(Cpu *cpu, std::uint32_t opcode);
void interpreter_ori(Cpu *cpu, std::uint32_t opcode);
void interpreter_sw(Cpu *cpu, std::uint32_t opcode);
