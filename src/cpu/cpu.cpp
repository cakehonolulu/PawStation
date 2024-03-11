#include <cpu/cpu.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <log/log.h>
#include <pawstation.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

Cpu::Cpu(Bus *bus_, EmulationMode mode)
{
	bus = bus_;

	switch (mode)
	{
		case EmulationMode::Interpreter:
            Logger::Instance().Log("[CPU] Running in Interpreter mode...");
			interpreter_setup(this);
			step = std::bind(&step_interpreter, this);
			break;
		case EmulationMode::CachedInterpreter:
            Logger::Instance().Error("[CPU] Cached interpreter mode is unavailable...");
			exit(1);
			break;
		default:
            Logger::Instance().Error("[CPU] Invalid emulation mode!");
			exit(1);
			break;
	}

	std::memset(registers, 0, sizeof(registers));
    std::memset(cop0_registers, 0, sizeof(cop0_registers));
	pc = 0xBFC00000;
	next_pc = pc + 4;
}

Cpu::~Cpu()
{
}

void Cpu::run()
{
	while (!Pawstation::requestedExit())
	{
		step();
	}
}

std::uint32_t Cpu::fetch_opcode()
{
	return bus->read32(pc);
}

void Cpu::parse_opcode(std::uint32_t opcode)
{
	std::uint8_t function = (opcode >> 26) & 0x3F;
	opcodes[function](this, opcode);
}

void Cpu::unknown_opcode(std::uint32_t opcode)
{
    std::ostringstream logMessage;
    logMessage << "[CPU] Unimplemented opcode: 0x" << format("{:04X}", opcode)
               << " (Function bits: 0x" << format("{:02X}", (opcode >> 26) & 0x3F) << ")";

    Logger::Instance().Error(logMessage.str());
    Pawstation::exit_();
}

void Cpu::unknown_extended_opcode(std::uint32_t opcode)
{
    std::ostringstream logMessage;
    logMessage << "[CPU] Unimplemented extended opcode: 0x" << format("{:04X}", opcode) << " (Function bits: 0x"
	          << format("{:02X}", (opcode >> 26) & 0x3F) << ")";
    Logger::Instance().Error(logMessage.str());
    Pawstation::exit_();
}

void Cpu::unknown_cop0_opcode(std::uint32_t opcode)
{
    std::ostringstream logMessage;
    logMessage << "[CPU] Unimplemented COP0 opcode: 0x" << format("{:04X}", opcode) << " (Function bits: 0x"
	          << format("{:02X}", (opcode >> 26) & 0x3F) << ")";
    Logger::Instance().Error(logMessage.str());
    Pawstation::exit_();
}