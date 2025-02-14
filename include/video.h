// video.h
//
// Video-related definitions and functions.


#include "types.h"


#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

// Pointer to the video RAM (used as an array)
#define vid_mem		((u16*)MEM_VRAM)


// Some predefined colors

#define CLR_BLACK	0x0000
#define CLR_RED		0x001F
#define CLR_LIME	0x03E0
#define CLR_YELLOW	0x03FF
#define CLR_BLUE	0x7C00
#define CLR_MAG		0x7C1F
#define CLR_CYAN	0x7FE0
#define CLR_WHITE	0x7FFF


// Mode 3 pixel plotting
INLINE void m3_plot(u32 x, u32 y, COLOR clr)
{
	vid_mem[x + y * SCREEN_WIDTH] = clr;
}


// Create a COLOR based on RGB values
INLINE COLOR RGB15(u32 red, u32 greeb, u32 blue)
{
	return red | (green << 5) | (blue << 10);
}
