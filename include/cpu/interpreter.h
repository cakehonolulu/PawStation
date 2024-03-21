#pragma once

#include <cstdint>
#include <cpu/cpu.h>
#include <iostream>

class Cpu;

void step_interpreter(Cpu *cpu);
void interpreter_setup(Cpu *cpu);

void interpreter_extended(Cpu *cpu, std::uint32_t opcode);

void interpreter_sll(Cpu *cpu, std::uint32_t opcode);
void interpreter_or(Cpu *cpu, std::uint32_t opcode);

void interpreter_j(Cpu *cpu, std::uint32_t opcode);
void interpreter_addiu(Cpu *cpu, std::uint32_t opcode);
void interpreter_lui(Cpu *cpu, std::uint32_t opcode);
void interpreter_ori(Cpu *cpu, std::uint32_t opcode);
void interpreter_sw(Cpu *cpu, std::uint32_t opcode);
