#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

class Disassembler {
public:
  using DisassembleFunction = std::function<std::string(const Disassembler&)>;

  Disassembler(std::uint32_t pc = 0);

  // Set a custom disassembly function for a specific opcode
  void SetDisassembleFunction(std::uint8_t opcode, DisassembleFunction func);

  // Disassemble an opcode
  std::string Disassemble(std::uint32_t opcode, std::uint32_t pc);

private:
  std::uint8_t rs;
  std::uint8_t rt;
  std::uint8_t rd;
  std::uint16_t imm;
  std::uint32_t simm;
  std::uint16_t subfunc;
  std::uint32_t shift;
  std::uint32_t jimm;
  std::uint32_t pc_;

  std::unordered_map<std::uint8_t, DisassembleFunction> opcodeFunctions;
};
