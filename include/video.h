// video.h
//
// Video-related definitions and functions.


#include "types.h"


// Sizes in pixels
#define SCREEN_WIDTH		240
#define SCREEN_HEIGHT		160


// Each mode's screen sizes
#define M3_WIDTH		SCREEN_WIDTH
#define M3_HEIGHT		SCREEN_HEIGHT
#define M4_WIDTH		SCREEN_WIDTH
#define M4_HEIGHT		SCREEN_HEIGHT
#define M5_WIDTH		160
#define M5_HEIGHT		128


// Sizes in tiles
#define SCREEN_WIDTH_T		(SCREEN_WIDTH / 8)
#define SCREEN_HEIGHT_T		(SCREEN_HEIGHT / 8)


// Total scanlines
#define SCREEN_LINES		228


// Shorter names
#define SCR_W		SCREEN_WIDTH
#define SCR_H		SCREEN_HEIGHT
#define SCR_WT		SCREEN_WIDTH_T
#define SCR_HT		SCREEN_HEIGHT_T


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


// Useful COLOR-related values
#define RED_MASK	0x001F
#define RED_SHIFT	0
#define GREEN_MASK	0x03E0
#define GREEN_SHIFT	5
#define BLUE_MASK	0x7C00
#define BLUE_SHIFT	10


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
