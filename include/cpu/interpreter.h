#pragma once

#include <cstdint>
#include <cpu/cpu.h>
#include <iostream>

class Cpu;

void step_interpreter(Cpu *cpu);
void interpreter_setup(Cpu *cpu);

void interpreter_extended(Cpu *cpu, std::uint32_t opcode);
void interpreter_cop0(Cpu *cpu, std::uint32_t opcode);

// COP0 Opcodes
void interpreter_mtc0(Cpu *cpu, std::uint32_t opcode);

// Extended Opcodes
void interpreter_sll(Cpu *cpu, std::uint32_t opcode);
void interpreter_or(Cpu *cpu, std::uint32_t opcode);

// Regular Opcodes
void interpreter_j(Cpu *cpu, std::uint32_t opcode);
void interpreter_bne(Cpu *cpu, std::uint32_t opcode);
void interpreter_addi(Cpu *cpu, std::uint32_t opcode);
void interpreter_addiu(Cpu *cpu, std::uint32_t opcode);
void interpreter_lui(Cpu *cpu, std::uint32_t opcode);
void interpreter_ori(Cpu *cpu, std::uint32_t opcode);
void interpreter_lw(Cpu *cpu, std::uint32_t opcode);
void interpreter_sw(Cpu *cpu, std::uint32_t opcode);
