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

    cpu->opcodes[0x00] = &interpreter_extended;
    cpu->opcodes[0x10] = &interpreter_cop0;

    cpu->cop0_opcodes[0x04] = &interpreter_mtc0;

    cpu->extended_opcodes[0x00] = &interpreter_sll;
    cpu->extended_opcodes[0x25] = &interpreter_or;

    cpu->opcodes[0x02] = &interpreter_j;
    cpu->opcodes[0x05] = &interpreter_bne;
    cpu->opcodes[0x08] = &interpreter_addi;
    cpu->opcodes[0x09] = &interpreter_addiu;
    cpu->opcodes[0x0D] = &interpreter_ori;
    cpu->opcodes[0x0F] = &interpreter_lui;
    cpu->opcodes[0x23] = &interpreter_lw;
    cpu->opcodes[0x2B] = &interpreter_sw;
}

void step_interpreter(Cpu *cpu)
{
    std::uint32_t opcode = cpu->next_opcode;
    cpu->next_opcode = cpu->fetch_opcode();

    cpu->pc += 4;
    cpu->parse_opcode(opcode);
    cpu->registers[0] = 0;
}

void interpreter_extended(Cpu *cpu, std::uint32_t opcode)
{
    cpu->extended_opcodes[subfunc](cpu, opcode);
}

void interpreter_cop0(Cpu *cpu, std::uint32_t opcode)
{
    cpu->cop0_opcodes[rs](cpu, opcode);
}

// COP0 Opcodes
void interpreter_mtc0(Cpu *cpu, std::uint32_t opcode)
{
    cpu->cop0_registers[rd] = cpu->registers[rt];
}

// Extended Opcodes
void interpreter_sll(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rd] = cpu->registers[rt] << shift;
}

void interpreter_or(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rd] = cpu->registers[rs] | cpu->registers[rt];
}

// Regular Opcodes
void interpreter_j(Cpu *cpu, std::uint32_t opcode)
{
    cpu->pc = (cpu->pc & 0xF0000000) | (jimm << 2);
}

void interpreter_bne(Cpu *cpu, std::uint32_t opcode)
{
    if (cpu->registers[rs] != cpu->registers[rt])
    {
        cpu->pc += simm << 2;
    }
}

void interpreter_addi(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->registers[rs] + simm;
}

void interpreter_addiu(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->registers[rs] + simm;
}

void interpreter_lui(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = imm << 16;
}

void interpreter_ori(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->registers[rs] | imm;
}

void interpreter_lw(Cpu *cpu, std::uint32_t opcode)
{
    cpu->registers[rt] = cpu->bus->read32(cpu->registers[rs] + simm);
}

void interpreter_sw(Cpu *cpu, std::uint32_t opcode)
{
  cpu->bus->write32(cpu->registers[rs] + simm, cpu->registers[rt]);
}