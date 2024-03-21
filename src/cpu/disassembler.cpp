#include <cpu/disassembler.h>
#include <cpu/registers.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

Disassembler::Disassembler(std::uint32_t pc) : pc_(pc) {
    SetDisassembleFunction(0x00, [](const Disassembler& disasm) {
        {
            switch (disasm.subfunc) {
                case 0x00:
                    return format("sll ${}, ${}, {}", cpu_register_names[disasm.rd], cpu_register_names[disasm.rt], disasm.imm);
                case 0x25:
                    return format("or ${}, ${}, ${}", cpu_register_names[disasm.rd], cpu_register_names[disasm.rs], cpu_register_names[disasm.rt]);
                default:
                    return format("UNKNOWN_SUBFUNCTION 0x{:02X}", disasm.subfunc);
            }
        }
    });

    SetDisassembleFunction(0x10, [](const Disassembler& disasm) {
        {
            switch (disasm.rs) {
                case 0x04:
                    return format("mtc0 ${}, ${}", cpu_register_names[disasm.rt], cop0_register_names[disasm.rd]);
                default:
                    return format("UNKNOWN_COP0_FUNCTION 0x{:02X}", disasm.rs);
            }
        }
    });

    SetDisassembleFunction(0x02, [](const Disassembler& disasm) {
        return format("j 0x{:08X}",  (disasm.pc_ & 0xF0000000) | (disasm.jimm << 2));
    });

    SetDisassembleFunction(0x09, [](const Disassembler& disasm) {
        return format("addiu ${}, ${}, 0x{:04X}", cpu_register_names[disasm.rt], cpu_register_names[disasm.rs], disasm.imm);
    });

    SetDisassembleFunction(0x0D, [](const Disassembler& disasm) {
        return format("ori ${}, ${}, 0x{:04X}", cpu_register_names[disasm.rt], cpu_register_names[disasm.rs], disasm.imm);
    });

    SetDisassembleFunction(0x0F, [](const Disassembler& disasm) {
        return format("lui ${}, 0x{:04X}", cpu_register_names[disasm.rt], disasm.imm);
    });

    SetDisassembleFunction(0x20, [](const Disassembler& disasm) {
        return format("add ${}, ${}, ${}", cpu_register_names[disasm.rd], cpu_register_names[disasm.rs], disasm.rt);
    });

    SetDisassembleFunction(0x2B, [](const Disassembler& disasm) {
        return format("sw ${}, 0x{:04X}(${})", cpu_register_names[disasm.rt], disasm.imm, cpu_register_names[disasm.rs]);
    });
}

void Disassembler::SetDisassembleFunction(std::uint8_t opcode, DisassembleFunction func) {
  opcodeFunctions[opcode] = func;
}

std::string Disassembler::Disassemble(std::uint32_t opcode, std::uint32_t pc) {
    std::uint8_t opcodeKey = (opcode >> 26) & 0x3F;
    auto it = opcodeFunctions.find(opcodeKey);

    if (it != opcodeFunctions.end()) {
        Disassembler disasm;
        disasm.pc_ = pc;
        disasm.rs = ((opcode >> 21) & 0x1F);
        disasm.rt = ((opcode >> 16) & 0x1F);
        disasm.rd = ((opcode >> 11) & 0x1F);
        disasm.imm = (opcode & 0xFFFF);
        disasm.simm = (std::uint32_t ((std::int16_t) imm));
        disasm.subfunc = (opcode & 0x3F);
        disasm.shift = ((std::uint32_t) ((opcode >> 6) & 0x1F));
        disasm.jimm = ((std::uint32_t) (opcode & 0x3FFFFFF));

        return it->second(disasm);
    } else {
        std::uint8_t extendedOpcodeKey = opcode & 0xFF;
        auto extendedIt = opcodeFunctions.find(extendedOpcodeKey);

        Disassembler disasm;
        disasm.pc_ = pc;
        disasm.rs = ((opcode >> 21) & 0x1F);
        disasm.rt = ((opcode >> 16) & 0x1F);
        disasm.rd = ((opcode >> 11) & 0x1F);
        disasm.imm = (opcode & 0xFFFF);
        disasm.simm = (std::uint32_t ((std::int16_t) imm));
        disasm.subfunc = (opcode & 0x3F);
        disasm.shift = ((std::uint32_t) ((opcode >> 6) & 0x1F));
        disasm.jimm = ((std::uint32_t) (opcode & 0x3FFFFFF));

        if (extendedIt != opcodeFunctions.end()) {
            return extendedIt->second(disasm);
        } else {
            return format("UNKNOWN_OPCODE 0x{:08X}", opcode);
        }
    }
}