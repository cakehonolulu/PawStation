#include <cpu/cpu_interpreter.h>
#include <log/log.h>
#include <pawstation.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

void cpu_interpreter_setup(Cpu *cpu)
{
    Logger::Instance().Log("[CPU] Populating opcode table...");
    std::fill(std::begin(cpu->opcodes), std::end(cpu->opcodes), &Cpu::cpu_unknown_opcode);
    std::fill(std::begin(cpu->extended_opcodes), std::end(cpu->extended_opcodes), &Cpu::cpu_unknown_extended_opcode);
    std::fill(std::begin(cpu->cop0_opcodes), std::end(cpu->cop0_opcodes), &Cpu::cpu_unknown_cop0_opcode);

    cpu->opcodes[0x0F] = &cpu_interpreter_lui;
    cpu->opcodes[0x0D] = &cpu_interpreter_ori;
}

void cpu_step_interpreter(Cpu *cpu)
{
	std::uint32_t opcode = cpu->cpu_fetch_opcode();
	cpu->pc = cpu->next_pc;
	cpu->next_pc += 4;
	cpu->cpu_parse_opcode(opcode);
}

void cpu_interpreter_lui(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = imm << 16;
}

void cpu_interpreter_ori(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->registers[rs] | imm;
}