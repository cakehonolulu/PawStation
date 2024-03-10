#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

class Disassembler {
public:
  using DisassembleFunction = std::function<std::string(const Disassembler&)>;

  Disassembler();

  // Set a custom disassembly function for a specific opcode
  void SetDisassembleFunction(std::uint8_t opcode, DisassembleFunction func);

  // Disassemble an opcode
  std::string Disassemble(std::uint32_t opcode);

private:
  std::uint8_t rs;
  std::uint8_t rt;
  std::uint8_t rd;
  std::uint16_t imm;

  std::unordered_map<std::uint8_t, DisassembleFunction> opcodeFunctions;
};
