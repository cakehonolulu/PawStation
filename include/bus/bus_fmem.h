#pragma once

#include <cstdint>

class Bus;

void fmem_init(Bus &bus);
std::uint32_t fmem_read32(Bus &bus, std::uint32_t address);