#include <cpu/disassembler.h>
#include <cpu/registers.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

Disassembler::Disassembler() {
  // Set default disassembly functions
  SetDisassembleFunction(0x20, [](const Disassembler& disasm) {
    return format("add ${}, ${}, ${}", cpu_register_names[disasm.rd], cpu_register_names[disasm.rs], disasm.rt);
  });

  SetDisassembleFunction(0x0F, [](const Disassembler& disasm) {
    return format("lui ${}, 0x{:04X}", cpu_register_names[disasm.rt], disasm.imm);
  });

  SetDisassembleFunction(0x0D, [](const Disassembler& disasm) {
    return format("ori ${}, ${}, 0x{:04X}", cpu_register_names[disasm.rt], cpu_register_names[disasm.rs], disasm.imm);
  });
}

void Disassembler::SetDisassembleFunction(std::uint8_t opcode, DisassembleFunction func) {
  opcodeFunctions[opcode] = func;
}

std::string Disassembler::Disassemble(std::uint32_t opcode) {
  std::uint8_t opcodeKey = (opcode >> 26) & 0x3F; // Extract opcode key from the opcode
  auto it = opcodeFunctions.find(opcodeKey);

  if (it != opcodeFunctions.end()) {
    // Extract relevant fields from the opcode
    Disassembler disasm;
    disasm.rs = (opcode >> 21) & 0x1F;
    disasm.rt = (opcode >> 16) & 0x1F;
    disasm.rd = (opcode >> 11) & 0x1F;
    disasm.imm = opcode & 0xFFFF;

    // Call the registered disassembly function
    return it->second(disasm);
  } else {
    // Handle unknown opcode
    return format("UNKNOWN_OPCODE 0x{:08X}", opcode);
  }
}