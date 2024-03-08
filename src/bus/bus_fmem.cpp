#include <bus/bus.h>
#include <bus/bus_fmem.h>
#include <sstream>
#include <log/log.h>
#include <cstring>
#include <pawstation.h>

#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

void Bus::fmem_init()
{
	// PS1's Address Space is 4GB, divide it in 64KB pages
	address_space_r = new uintptr_t[0x10000];
	address_space_w = new uintptr_t[0x10000];

	const uint32_t PAGE_SIZE = 64 * 1024; // Page size = 4KB

	memset(address_space_r, 0, sizeof(uintptr_t) * 0x10000);
	memset(address_space_w, 0, sizeof(uintptr_t) * 0x10000);

	// 512 KB's of BIOS memory fit in 8, 64KB pages
	for (auto pageIndex = 0; pageIndex < 128; pageIndex++)
	{
		const auto pointer = (uintptr_t)&bios[(pageIndex * PAGE_SIZE)]; // pointer to page #pageIndex of the BIOS
		address_space_r[pageIndex + 0x1FC0] = pointer;                 // map this page to KUSEG BIOS
		address_space_r[pageIndex + 0x9FC0] = pointer;                 // Same for KSEG0
		address_space_r[pageIndex + 0xBFC0] = pointer;                 // Same for KSEG1
	}

	for (auto pageIndex = 0; pageIndex < 128; pageIndex++)
	{
		const auto pointer = (uintptr_t) &ram [(pageIndex * PAGE_SIZE) & 0x1FFFFF];
		address_space_r[pageIndex + 0x0000] = pointer;
		address_space_r[pageIndex + 0x8000] = pointer;
		address_space_r[pageIndex + 0xA000] = pointer;
	}

	for (auto pageIndex = 0; pageIndex < 128; pageIndex++)
	{
		const auto pointer = (uintptr_t) &ram [(pageIndex * PAGE_SIZE) & 0x1FFFFF];
		address_space_w[pageIndex + 0x0000] = pointer;
		address_space_w[pageIndex + 0x8000] = pointer;
		address_space_w[pageIndex + 0xA000] = pointer;
	}
}

std::uint32_t Bus::fmem_read32(std::uint32_t address) {
	const auto page = address >> 16;           // Divide the address by 4KB to get the page number.
	const auto offset = address & 0xFFFF;       // The offset inside the 4KB page
	const auto pointer = address_space_r[page];// Get the pointer to this page

	if (pointer != 0)// Check if the pointer is not nullptr. If it is not, then this is a fast page
		return *(uint32_t *) (pointer +
		                      offset);// Actually read the value using the pointer from the page table + the offset.

	else {
		// Handle other cases or throw an exception if needed
        std::ostringstream logMessage;
        logMessage << "[BUS] 32-bit read from unknown address: 0x" << format("{:08X}", address);
        Logger::Instance().Error(logMessage.str());
        Pawstation::exit_();
	}
}