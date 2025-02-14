// memmap.h
//
// Useful naming of memory sections.


#ifndef MEMMAP_H
#define MEMMAP_H

#include "types.h"


// Main sections
#define MEM_EWRAM	0x02000000	// External work RAM
#define MEM_IWRAM	0x03000000	// Internal work RAM
#define MEM_IO		0x04000000	// I/O registers
#define MEM_PAL		0x05000000	// Palette (No 8bit-write)
#define MEM_VRAM	0x06000000	// Video RAM (No 8bit-write)
#define MEM_OAM		0x07000000	// Object Attribute Memory (No 8bit-write)
#define MEM_ROM		0x08000000	// ROM
#define MEM_SRAM	0x0E000000	// Static RAM (8bit-write only)


// Main sections' sizes
#define EWRAM_SIZE	0x00040000
#define IWRAM_SIZE	0x00008000
#define PAL_SIZE	0x00000400
#define VRAM_SIZE	0x00018000
#define OAM_SIZE	0x00000400
#define SRAM_SIZE	0x00010000


// Subsections' sizes
#define PAL_BG_SIZE		0x00200		// BG palette size
#define PAL_OBJ_SIZE	0x00200		// Object palette size
#define CB_SIZE			0x04000		// Charblock size
#define SB_SIZE			0x00800		// Screenblock size
#define VRAM_BG_SIZE	0x10000		// BG VRAM size
#define VRAM_OBJ_SIZE	0x08000		// Object VRAM size
#define VRAM_PAGE_SIZE	0x0A000		// Bitmap page size
#define M3_SIZE			0x12C00		// Mode 3 buffer size
#define M4_SIZE			0x09600		// Mode 4 buffer size
#define M5_SIZE			0x0A000		// Mode 5 buffer size


// Display registers (used as variables)
#define REG_DISPCNT		*(vu32*)(MEM_IO + 0x0000)	// Display control
#define REG_DISPSTAT	*(vu16*)(MEM_IO + 0x0004)	// Display status
#define REG_VCOUNT		*(vu16*)(MEM_IO + 0x0006)	// Scanline count


#endif // MEMMAP_H
