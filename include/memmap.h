// memmap.h
//
// Useful naming of memory sections.


#ifndef MEMMAP
#define MEMMAP

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


// Main sections' sizes
#define EWRAM_SIZE	0x0004_0000
#define IWRAM_SIZE	0x0000_8000
#define PAL_SIZE	0x0000_0400
#define VRAM_SIZE	0x0001_8000
#define OAM_SIZE	0x0000_0400
#define SRAM_SIZE	0x0001_0000


// Subsections' sizes
#define PAL_BG_SIZE		0x0_0200		// BG palette size
#define PAL_OBJ_SIZE	0x0_0200		// Object palette size
#define CB_SIZE			0x0_4000		// Charblock size
#define SB_SIZE			0x0_0800		// Screenblock size
#define VRAM_BG_SIZE	0x1_0000		// BG VRAM size
#define VRAM_OBJ_SIZE	0x0_8000		// Object VRAM size
#define VRAM_PAGE_SIZE	0x0_A000		// Bitmap page size
#define M3_SIZE			0x1_2C00		// Mode 3 buffer size
#define M4_SIZE			0x0_9600		// Mode 4 buffer size
#define M5_SIZE			0x0_A000		// Mode 5 buffer size


// Display registers (used as variables)
#define REG_DISPCNT		*(vu32*)(MEM_IO + 0x0000)	// Display control
#define REG_DISPSTAT	*(vu16*)(MEM_IO + 0x0004)	// Display status
#define REG_VCOUNT		*(vu16*)(MEM_IO + 0x0006)	// Scanline count


#endif
