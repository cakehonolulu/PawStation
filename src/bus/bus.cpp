#include <bus/bus.h>
#include <pawstation.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>

Bus::Bus(BusMode mode)
{
	// BIOS (512KB)
	bios.resize(1024 * 512);

	// RAM (2MB)
	ram.resize(1024 * 1024 * 2);

	std::fill(bios.begin(), bios.end(), 0);

	std::fill(ram.begin(), ram.end(), 0);

	bios_loaded = false;

	switch (mode)
	{
		case BusMode::SoftwareFastMem:
			fmem_init();
			read32 = std::bind(&Bus::fmem_read32, this, std::placeholders::_1);
			std::cout << CYAN << "[BUS] Running Bus w/Software FastMem mode..." << RESET "\n";
			break;
		case BusMode::Ranged:
			std::cerr << BOLDRED << "[BUS] Ranged Bus mode is unimplemented" << RESET "\n";
			exit(1);
			break;
		default:
			std::cerr << BOLDRED << "[BUS] Invalid Bus mode" << RESET "\n";
			exit(1);
			break;
	}
}

void Bus::load_bios(const std::string &bios_path)
{
	std::ifstream bios_file(bios_path, std::ios::binary);

	if (!bios_file.is_open())
	{
		std::cerr << BOLDRED << "Failed to open the BIOS file: " << bios_path << RESET << "\n";
		return;
	}

	bios_file.read(reinterpret_cast<char *>(bios.data()), bios.size());

	assert(bios_file.good() && bios_file.gcount() == static_cast<std::streamsize>(bios.size()));

	bios_file.close();

	bios_loaded = true;
}

bool Bus::is_bios_loaded() const
{
	return bios_loaded;
}