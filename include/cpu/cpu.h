#pragma once

#include <bus/bus.h>
#include <cstdint>
#include <cpu/cpu_interpreter.h>
#include <cpu/cpu_registers.h>
#include <functional>

#define rt ((opcode >> 16) & 0x1F)
#define rs ((opcode >> 21) & 0x1F)
#define imm (opcode & 0xFFFF)

enum class EmulationMode
{
	Interpreter,
	CachedInterpreter,
	DynamicRecompiler
};

class Cpu
{
private:
public:
	Cpu(Bus *bus_, EmulationMode mode = EmulationMode::Interpreter);
	~Cpu();

	Bus *bus;

	std::function<void()> cpu_step;
	void run();

	std::uint32_t cpu_fetch_opcode();
	void cpu_parse_opcode(std::uint32_t opcode);
	void cpu_unknown_opcode(std::uint32_t opcode);
	void cpu_unknown_extended_opcode(std::uint32_t opcode);
	void cpu_unknown_cop0_opcode(std::uint32_t opcode);

	std::function<void(Cpu *, std::uint32_t)> opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> extended_opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> cop0_opcodes[0x11] = {nullptr};

	std::uint32_t registers[32];
	std::uint32_t cop0_registers[32];

	std::uint32_t pc;
	std::uint32_t next_pc;
};