// video.h
//
// Video-related definitions and functions.


#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"
#include "memmap.h"


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
#define CLR_RED     0x001F      // 0000_0000_0001_1111
#define CLR_LIME    0x03E0      // 0000_0011_1110_0000
#define CLR_BLUE    0x7C00      // 0111_1100_0000_0000
#define CLR_YELLOW  0x03FF      // 0000_0011_1111_1111
#define CLR_MAG     0x7C1F      // 0111_1100_0001_1111
#define CLR_CYAN    0x7FE0      // 0111_1111_1110_0000
#define CLR_WHITE   0x7FFF      // 0111_1111_1111_1111


// Useful COLOR-related values
#define RED_MASK	0x001F
#define RED_SHIFT	0
#define GREEN_MASK	0x03E0
#define GREEN_SHIFT	5
#define BLUE_MASK	0x7C00
#define BLUE_SHIFT	10


// General-use
void vid_vsync(void);


// Color-related
COLOR RGB15(u32 red, u32 green, u32 blue);


// Generic 16bpm drawing
void bmp16_plot(u32 x, u32 y, COLOR clr, void *baseAddr, u32 pitch);
void bmp16_hline(u32 x1, u32 y, u32 x2, COLOR clr, void *baseAddr, u32 pitch);
void bmp16_vline(u32 x, u32 y1, u32 y2, COLOR clr, void *baseAddr, u32 pitch);
void bmp16_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch);
void bmp16_rect(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch);
void bmp16_frame(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch);


// Mode 3 drawing (interface with generic bmp16 functions)
void m3_plot(u32 x, u32 y, COLOR clr);
void m3_hline(u32 x1, u32 y, u32 x2, COLOR clr);
void m3_vline(u32 x, u32 y1, u32 y2, COLOR clr);
void m3_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr);
void m3_rect(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr);
void m3_frame(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr);
void m3_fill(COLOR clr);


#endif // VIDEO_H
