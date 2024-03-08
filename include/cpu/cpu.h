#pragma once

#include <bus/bus.h>
#include <cstdint>
#include <cpu/cpu_interpreter.h>
#include <functional>

#define rt ((opcode >> 16) & 0x1F)
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

	const std::vector<std::string> cpu_register_names = {
	        "zr",
	        "at",
	        "v0", "v1",
	        "a0", "a1", "a2", "a3",
	        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	        "t8", "t9",
	        "k0", "k1",
	        "gp",
	        "sp",
	        "fp",
	        "ra"
	};

	const std::vector<std::string> cop0_register_names = {
	        "Index", "Random", "EntryLo0", "EntryLo1",
	        "Context", "PageMask", "Wired", "Reserved",
	        "BadVAddr", "Count", "EntryHi", "Compare",
	        "Status", "Cause", "EPC", "PRId",
	        "Config", "LLAddr", "WatchLo", "WatchHi",
	        "XContext", "Reserved", "Reserved", "Reserved",
	        "Reserved", "Reserved", "Reserved", "Reserved",
	        "CacheErr", "TagLo", "TagHi", "ErrorEPC",
	        "Reserved"
	};

	std::function<void(Cpu *, std::uint32_t)> opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> extended_opcodes[0x3F] = {nullptr};
	std::function<void(Cpu *, std::uint32_t)> cop0_opcodes[0x11] = {nullptr};

	std::uint32_t registers[32];
	std::uint32_t cop0_registers[32];

	std::uint32_t pc;
	std::uint32_t next_pc;
};