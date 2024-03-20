#include <cpu/interpreter.h>
#include <log/log.h>
#include <pawstation.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

void interpreter_setup(Cpu *cpu)
{
    Logger::Instance().Log("[CPU] Populating opcode table...");
    std::fill(std::begin(cpu->opcodes), std::end(cpu->opcodes), &Cpu::unknown_opcode);
    std::fill(std::begin(cpu->extended_opcodes), std::end(cpu->extended_opcodes), &Cpu::unknown_extended_opcode);
    std::fill(std::begin(cpu->cop0_opcodes), std::end(cpu->cop0_opcodes), &Cpu::unknown_cop0_opcode);

    cpu->opcodes[0x0D] = &interpreter_ori;
    cpu->opcodes[0x0F] = &interpreter_lui;
    cpu->opcodes[0x2B] = &interpreter_sw;
}

void step_interpreter(Cpu *cpu)
{
	std::uint32_t opcode = cpu->fetch_opcode();
    cpu->parse_opcode(opcode);
}

void interpreter_lui(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = imm << 16;
    cpu->pc = cpu->next_pc;
    cpu->next_pc += 4;
}

void interpreter_ori(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->registers[rs] | imm;
    cpu->pc = cpu->next_pc;
    cpu->next_pc += 4;
}

void interpreter_sw(Cpu *cpu, std::uint32_t opcode)
{
  cpu->bus->write32(cpu->registers[rs] + simm, cpu->registers[rt]);
  cpu->pc = cpu->next_pc;
  cpu->next_pc += 4;
}