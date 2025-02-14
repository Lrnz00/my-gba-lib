// memmap.h
//
// Useful naming of memory sections.


#include "types.h"


// Main sections
#define MEM_EWRAM	0x0200_0000	// External work RAM
#define MEM_IWRAM	0x0300_0000	// Internal work RAM
#define MEM_IO		0x0400_0000	// I/O registers
#define MEM_PAL		0x0500_0000	// Palette (No 8bit-write)
#define MEM_VRAM	0x0600_0000	// Video RAM (No 8bit-write)
#define MEM_OAM		0x0700_0000	// Object Attribute Memory (No 8bit-write)
#define MEM_ROM		0x0800_0000	// ROM
#define MEM_SRAM	0x0E00_0000	// Static RAM (8bit-write only)


// Main section sizes
#define EWRAM_SIZE	0x0004_0000
#define IWRAM_SIZE	0x0000_8000
#define PAL_SIZE	0x0000_0400
#define VRAM_SIZE	0x0001_8000
#define OAM_SIZE	0x0000_0400
#define SRAM_SIZE	0x0001_0000


// Display registers (used as variables)
#define REG_DISPCNT	*(vu32*)(MEM_IO + 0x0000)	// Display control
#define REG_DISPSTAT	*(vu16*)(MEM_IO + 0x0004)	// Display status
#define REG_VCOUNT	*(vu16*)(MEM_IO + 0x0006)	// Scanline count
