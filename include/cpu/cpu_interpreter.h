#pragma once

#include <cstdint>
#include <cpu/cpu.h>
#include <iostream>

class Cpu;

void cpu_step_interpreter(Cpu *cpu);
void cpu_interpreter_setup(Cpu *cpu);
