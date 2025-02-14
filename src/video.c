// video.c
//
// Implementations of video.h


#include "video.h"


// Vertical synchronization using REG_VCOUNT (0-227)
INLINE void vid_vsync()
{
	while (REG_VCOUNT >= 160);	// wait untill VDraw
	while (REG_VCOUNT < 160);	// wait untill VBlank
}


// Create a COLOR based on RGB values
INLINE COLOR RGB15(u32 red, u32 greeb, u32 blue)
{
	return red | (green << 5) | (blue << 10);
}


// BMP16 pixel plotting
INLINE void bmp16_plot(u32 x, u32 y, u32 clr, void *baseAddr, u32 pitch)
{
	// baseAddr[x + y * pitch/8] = clr;
}
// TODO: implement other generics


// Mode 3 pixel plotting
INLINE void m3_plot(u32 x, u32 y, COLOR clr)
{
	// vid_mem[x + y * M3_WIDTH * 2] = clr;
}
// TODO: implement other m3 functions
