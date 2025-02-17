// video.c
//
// Implementations of video.h


#include "video.h"
#include "memmap.h"


// Vertical synchronization using REG_VCOUNT (0-227)
void vid_vsync(void)
{
	while (REG_VCOUNT >= 160);	// wait untill VDraw
	while (REG_VCOUNT < 160);	// wait untill VBlank
}


// Create a COLOR based on RGB values
COLOR RGB15(u32 red, u32 green, u32 blue)
{
	return red | (green << 5) | (blue << 10);
}


// BMP16 pixel plotting
void bmp16_plot(u32 x, u32 y, u32 clr, void *baseAddr, u32 pitch)
{
	// This casts the byte offset to a 2-bytes pointer
	// x is multiplied by 2 to get the horizontal offset
	// Similar to the pattern (x, y) = buffer[x + y * screen_width]
	((u16*)(baseAddr + x*2 + y*pitch))[0] = clr;
}
// TODO: implement other bmp16


// Mode 3 pixel plotting
void m3_plot(u32 x, u32 y, COLOR clr)
{
	vid_mem[x + y * M3_WIDTH] = clr;
}
// TODO: implement other m3
