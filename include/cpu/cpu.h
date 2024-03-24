#pragma once

#include <bus/bus.h>
#include <cstdint>
#include <cpu/interpreter.h>
#include <cpu/registers.h>
#include <functional>

#define rs ((opcode >> 21) & 0x1F)
#define rt ((opcode >> 16) & 0x1F)
#define rd ((opcode >> 11) & 0x1F)

#define imm (opcode & 0xFFFF)
#define simm (std::uint32_t ((std::int16_t) imm))
#define subfunc (opcode & 0x3F)
#define shft ((std::uint32_t) ((opcode >> 6) & 0x1F))

#define jimm ((std::uint32_t) (opcode & 0x3FFFFFF))

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

	std::function<void()> step;
	void run();
    void reset();

	std::uint32_t fetch_opcode();
	void parse_opcode(std::uint32_t opcode);
	void unknown_opcode(std::uint32_t opcode);
	void unknown_extended_opcode(std::uint32_t opcode);
	void unknown_cop0_opcode(std::uint32_t opcode);

	std::function<void(Cpu *, std::uint32_t)> opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> extended_opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> cop0_opcodes[0x11] = {nullptr};

	std::uint32_t registers[32];
	std::uint32_t cop0_registers[32];

	std::uint32_t pc;

    std::uint32_t next_opcode;
};