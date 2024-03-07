#include <bus/bus.h>
#include <log/log.h>
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
            Logger::Instance().Log("[BUS] Running Bus w/Software FastMem mode...");
			break;
		case BusMode::Ranged:
            Logger::Instance().Error("[BUS] Ranged Bus mode is unimplemented!");
			exit(1);
			break;
		default:
            Logger::Instance().Error("[BUS] Invalid Bus mode!");
			exit(1);
			break;
	}
}

void Bus::load_bios(const std::string &bios_path)
{
	std::ifstream bios_file(bios_path, std::ios::binary);

	if (!bios_file.is_open())
	{
        Logger::Instance().Error("[BUS] Failed to open the BIOS file!");
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