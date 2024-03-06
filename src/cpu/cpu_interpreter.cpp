#include <cpu/cpu_interpreter.h>
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
	std::cout << CYAN << "[CPU] Populating opcode table..." << RESET "\n";
}

void cpu_step_interpreter(Cpu *cpu)
{
	std::uint32_t opcode = cpu->cpu_fetch_opcode();
	cpu->pc = cpu->next_pc;
	cpu->next_pc += 4;
	cpu->cpu_parse_opcode(opcode);
}
