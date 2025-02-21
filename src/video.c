// video.c
//
// Implementations of video.h


#include "video.h"
#include "memmap.h"
#include "memdef.h"
#include "core.h"


// Vertical synchronization using REG_VCOUNT (0-227)
void vid_vsync(void)
{
	while (REG_VCOUNT >= 160);	// wait untill VDraw
	while (REG_VCOUNT < 160);	// wait untill VBlank
}


// Page flipping for modes 4 and 5
// Changes display page in REG_DISPCNT and sets
//   vid_page to point to the back buffer
u16 *vid_flip(void)
{
	vid_page = (u16*)((u32)vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= DCNT_PAGE;
	return vid_page;
}


// Fetch color value from palette
COLOR get_color(u8 clrid)
{
	return pal_mem[clrid];
}


// Create a COLOR based on RGB values
COLOR RGB15(u32 red, u32 green, u32 blue)
{
	return red | (green << 5) | (blue << 10);
}


// BMP16 pixel plotting
void bmp16_plot(u32 x, u32 y, COLOR clr, void *baseAddr, u32 pitch)
{
	// This casts the byte offset to a 2-bytes pointer
	// x is multiplied by 2 to get the horizontal offset
	// Similar to the pattern (x, y) = buffer[x + y * screen_width]
	u16 *dest = (u16*)((u8*)baseAddr + x*2 + y*pitch);
	dest[0] = clr;
}


// BMP16 line drawing (specfically horizontal)
void bmp16_hline(u32 x1, u32 y, u32 x2, COLOR clr, void *baseAddr, u32 pitch)
{
	// Normalize
	if (x1 > x2) {
		u32 tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	u16 *dest = (u16*)((u8*)baseAddr + x1*2 + y*pitch);

	// Draw
	memset16(dest, (u32)clr, x2 - x1 + 1);
}


// BMP16 line drawing (specifically vertical)
void bmp16_vline(u32 x, u32 y1, u32 y2, COLOR clr, void *baseAddr, u32 pitch)
{
	// Normalize
	if (y1 > y2) {
		u32 tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	u16 *dest = (u16*)((u8*)baseAddr + x*2 + y1*pitch);
	pitch /= 2;    // The pitch is byte-based, but the pointer is halfword-based

	// Draw
	for (u32 height = y2 - y1 + 1; height > 0; height--) {
		dest[x] = clr;
		dest += pitch;
	}
}


// BMP16 general line drawing (Bresenham's line algorithm)
void bmp16_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch)
{
	u32 ii, dx, dy, xstep, ystep, dd;
	u16 *dest = (u16*)((u8*)baseAddr + y1*pitch + x1*2);
	pitch /= 2;    // The pitch is byte-based, but the pointer is halfword-based

	// --- Normalization ---
	if (x1 > x2) {
		xstep = -1;
		dx = x1 - x2;
	}
	else {
		xstep = +1;
		dx = x2 - x1;
	}
	if (y1 > y2) {
		ystep = -pitch;
		dy = y1 - y2;
	}
	else {
		ystep = +pitch;
		dy = y2 - y1;
	}


	// --- Drawing ---
	// Horizontal
	if (dy == 0) {
		for (ii = 0; ii <= dx; ii++)
			dest[ii * xstep] = clr;
	}
	// Vertical
	else if (dx == 0) {
		for (ii = 0; ii <= dy; ii++)
			dest[ii * ystep] = clr;
	}
	// Diagonal, slope <= 1
	else if (dx >= dy) {
		dd = 2*dy - dx;

		for (ii = 0; ii <= dx; ii++) {
			*dest = clr;
			if (dd >= 0) {
				dd -= 2*dx;
				dest += ystep;
			}

			dd += 2*dy;
			dest += xstep;
		}
	}
	// Diagonal, slope > 1
	else {
		dd = 2*dx - dy;

		for (ii = 0; ii <= dy; ii++) {
			*dest = clr;
			if (dd >= 0) {
				dd -= 2*dy;
				dest += xstep;
			}

			dd += 2*dx;
			dest += ystep;
		}
	}
}


// BMP16 rectangle drawing
void bmp16_rect(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch)
{
	u32 tmp;

	// --- Normalization ---
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	u32 width = x2 - x1;
	u32 height = y2 - y1;
	u16 *dest = (u16*)((u8*)baseAddr + y1*pitch + x1*2);
	pitch /= 2;    // The pitch is byte-based, but the pointer is halfword-based

	// --- Draw ---
	while (height--) {
		memset16(dest, (u32)clr, width);
		dest += pitch;
	}
}


// BMP16 frame drawing
void bmp16_frame(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr, void *baseAddr, u32 pitch)
{
	u32 tmp;

	// --- Normalization ---
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	u32 width = x2 - x1;
	u32 height = y2 - y1;
	u16 *dest = (u16*)((u8*)baseAddr + y1*pitch + x1*2);
	pitch /= 2;    // The pitch is byte-based, but the pointer is halfword-based

	// --- Top line ---
	memset16(dest, (u32)clr, width);
	if (height < 2)
		return;
	dest += pitch;
	height -= 2;

	// --- Left/x2 lines ---
	while (height--) {
		dest[0] = clr;
		dest[width - 1] = clr;
		dest += pitch;
	}

	// --- Bottom line ---
	memset16(dest, (u32)clr, width);
}


// BMP8 pixel plotting
void bmp8_plot(u32 x, u32 y, u8 clrid, void *baseAddr, u32 pitch)
{
	// Division by 2 because the bmp8 buffer is 8-bit, and the array is 16-bit
	u16 *dest = (u16*)((u8*)baseAddr + ((x + y*pitch) >> 1));

	// Decide whether to write on upper or on lower bits
	if (x & 1)
		// Odd (upper)
		*dest = (*dest & 0xFF) | (clrid << 8);
	else
		// Even (lower)
		*dest = (*dest & ~0xFF) | clrid;
}


// BMP8 line drawing (specifically horizontal)
void bmp8_hline(u32 x1, u32 y, u32 x2, u8 clrid, void *baseAddr, u32 pitch)
{
	// Normalize
	if (x1 > x2) {
		u32 tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	u32 width = x2 - x1 + 1;
	u16 *dest = (u16*)((u8*)baseAddr + ((x1 + y*pitch) >> 1));

	// Left unaligned pixel
	if (x1 & 1) {
		*dest = (*dest & 0xFF) + (clrid << 8);
		width--;
		dest++;
	}

	// Right unaligned pixel
	if (width & 1)
		dest[width >> 1] = (dest[width >> 1] & ~0xFF) + clrid;

	// Aligned line
	width >>= 1;
	if (width)
		memset16(dest, (u32)dup8(clrid), width);
}


// BMP8 line drawing (specifically vertical)
void bmp8_vline(u32 x, u32 y1, u32 y2, u8 clrid, void *baseAddr, u32 pitch)
{
	// Normalize
	if (y1 > y2) {
		u32 tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	u32 height = y2 - y1 + 1;
	u16 *dest = (u16*)((u8*)baseAddr + ((x + y1*pitch) >> 1));
	pitch /= 2;

	if (x & 1) {
		while (height--) {
			*dest = (*dest & 0xFF) + (clrid << 8);
			dest += pitch;
		}
	}
	else {
		while (height--) {
			*dest = (*dest & ~0xFF) + clrid;
			dest += pitch;
		}
	}
}


// BMP8 general line drawing (Bresenham's line algorithm)
void bmp8_line(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid, void *baseAddr, u32 pitch)
{
	// Trivial lines: horizontal and vertical

	// Horizontal
	if (y1 == y2) {
		// Adjust for inclusive ends
		if (x1 == x2) {
			bmp8_plot(x1, y1, clrid, baseAddr, pitch);
			return;
		}
		bmp8_hline(x1, y1, x2, clrid, baseAddr, pitch);
		return;
	}
	// Vertical
	else if (x1 == x2) {
		bmp8_vline(x1, y1, y2, clrid, baseAddr, pitch);
		return;
	}

	// Slogging through the diagonal
	u32 ii, dx, dy, xstep, ystep, dd;
	u32 addr = (u32)((u8*)baseAddr + x1 + y1*pitch);
	u32 mask = 255;
	u16 *dest;

	clrid &= mask;
	u16 new_clrid = clrid | (clrid << 8);
	if (x1 & 1)
		mask = ~mask;

	// Normalization
	if (x1 > x2) {
		xstep = -1;
		dx = x1-x2;
	}
	else {
		xstep = +1;
		dx = x2 - x1;
	}
	if (y1 > y2) {
		ystep = -pitch;
		dy = y1 - y2;
	}
	else {
		ystep = +pitch;
		dy = y2 - y1;
	}


	// Drawing

	// NOTE: because xstep is alternating, you can do marvels
	//	with mask-flips
	// NOTE: (mask >> 31) is equivalent to (x & 1) ? 0 : 1

	// Diagonal, slope <= 1
	if (dx >= dy) {
		dd = 2*dy - dx;

		for (ii = dx; ii >= 0; ii--) {
			dest = (u16*)(addr - (mask >> 31));
			*dest = (*dest & ~mask) | (new_clrid & mask);

			if (dd >= 0) {
				dd -= 2*dx;
				addr += ystep;
			}

			dd += 2*dy;
			addr += xstep;
			mask = ~mask;
		}
	}
	// Diagonal, slope > 1
	else {
		dd = 2*dx - dy;

		for (ii = dy; ii >= 0; ii--) {
			dest = (u16*)(addr - (mask >> 31));
			*dest = (*dest & ~mask) | (new_clrid & mask);

			if (dd >= 0) {
				dd -= 2*dy;
				addr += xstep;
				mask = ~mask;
			}

			dd += 2*dx;
			addr += ystep;
		}
	}
}


// BMP8 rectangle drawing
void bmp8_rect(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid, void *baseAddr, u32 pitch)
{
	u32 tmp, iy;

	// Normalization
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	u32 width = x2 - x1;
	u32 height = y2 - y1;
	u16 *dest = (u16*)((u8*)baseAddr + ((x1 + y1*pitch) >> 1));
	u16 *dstL;
	pitch /= 2;

	// Unaligned x1
	if (x1 & 1) {
		dstL = dest;
		for (iy = 0; iy < height; iy++) {
			*dstL = (*dstL & 0xFF) | clrid << 8;
			dstL += pitch;
		}

		width -= 1;
		dest += 1;
	}

	// Unaligned x2
	if (width & 1) {
		dstL = dest + width / 2;
		for (iy = 0; iy < height; iy++) {
			*dstL = (*dstL & ~0xFF) | clrid;
			dstL += pitch;
		}
		width -= 1;
	}

	if (width == 0)
		return;

	// Center
	dstL = dest;
	for (iy = 0; iy < height; iy++) {
		memset16(dstL, (u32)dup8(clrid), width/2);
		dstL += pitch;
	}
}


// BMP8 frame drawing
void bmp8_frame(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid, void *baseAddr, u32 pitch)
{
	u32 tmp;

	// Normalization
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	x2--;
	y2--;

	bmp8_hline(x1, y1, x2, clrid, baseAddr, pitch);
	bmp8_hline(x1, y2, x2, clrid, baseAddr, pitch);

	bmp8_vline(x1, y1, y2, clrid, baseAddr, pitch);
	bmp8_vline(x2, y1, y2, clrid, baseAddr, pitch);
}


// Mode 3 pixel plotting
void m3_plot(u32 x, u32 y, COLOR clr)
{
	vid_mem[x + y * M3_WIDTH] = clr;
}


// Mode 3 line drawing (specifically horizontal)
void m3_hline(u32 x1, u32 y, u32 x2, COLOR clr)
{
	bmp16_hline(x1, y, x2, clr, vid_mem, M3_WIDTH*2);
}


// Mode 3 line drawing (specifically vertical)
void m3_vline(u32 x, u32 y1, u32 y2, COLOR clr)
{
	bmp16_vline(x, y1, y2, clr, vid_mem, M3_WIDTH*2);
}


// Mode 3 general line drawing
void m3_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_line(x1, x2, y1, y2, clr, vid_mem, M3_WIDTH*2);
}


// Mode 3 rectangle drawing
void m3_rect(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_rect(x1, x2, y1, y2, clr, vid_mem, M3_WIDTH*2);
}


// Mode 3 frame drawing
void m3_frame(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_frame(x1, x2, y1, y2, clr, vid_mem, M3_WIDTH*2);
}


// Mode 3 screen filling
void m3_fill(COLOR clr)
{
	memset32(vid_mem, dup16(clr), M3_SIZE/4);
}


// Mode 4 pixel plotting
void m4_plot(u32 x, u32 y, u8 clrid)
{
	// Division by 2 because the m4 buffer is 8-bit, and the array is 16-bit
	u16 *dest = &vid_page[(x + y*M4_WIDTH) >> 1];

	// Decide whether to write on upper or on lower bits
	if (x & 1)
		// Odd (upper)
		*dest = (*dest & 0xFF) | (clrid << 8);
	else
		// Even (lower)
		*dest = (*dest & ~0xFF) | clrid;
}


// Mode 4 line drawing (specifically horizontal)
void m4_hline(u32 x1, u32 y, u32 x2, u8 clrid)
{
	bmp8_hline(x1, y, x2, clrid, vid_page, M4_WIDTH);
}


// Mode 4 line drawing (specifically vertical)
void m4_vline(u32 x, u32 y1, u32 y2, u8 clrid)
{
	bmp8_vline(x, y1, y2, clrid, vid_page, M4_WIDTH);
}


// Mode 4 general line drawing
void m4_line(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid)
{
	bmp8_line(x1, x2, y1, y2, clrid, vid_page, M4_WIDTH);
}


// Mode 4 rectangle drawing
void m4_rect(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid)
{
	bmp8_rect(x1, x2, y1, y2, clrid, vid_page, M4_WIDTH);
}


// Mode 4 frame drawing
void m4_frame(u32 x1, u32 y1, u32 x2, u32 y2, u8 clrid)
{
	bmp8_frame(x1, x2, y1, y2, clrid, vid_page, M4_WIDTH);
}


// Mode 4 screen filling
void m4_fill(u8 clrid)
{
	memset32(vid_page, quad8(clrid), M4_SIZE/4);
}


// Mode 5 pixel plotting
void m5_plot(u32 x, u32 y, COLOR clr)
{
	vid_page[x + y * M5_WIDTH] = clr;
}


// Mode 5 line drawing (specifically horizontal)
void m5_hline(u32 x1, u32 y, u32 x2, COLOR clr)
{
	bmp16_hline(x1, y, x2, clr, vid_page, M5_WIDTH*2);
}


// Mode 5 line drawing (specifically vertical)
void m5_vline(u32 x, u32 y1, u32 y2, COLOR clr)
{
	bmp16_vline(x, y1, y2, clr, vid_page, M5_WIDTH*2);
}


// Mode 5 general line drawing
void m5_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_line(x1, x2, y1, y2, clr, vid_page, M5_WIDTH*2);
}


// Mode 5 rectangle drawing
void m5_rect(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_rect(x1, x2, y1, y2, clr, vid_page, M5_WIDTH*2);
}


// Mode 5 frame drawing
void m5_frame(u32 x1, u32 y1, u32 x2, u32 y2, COLOR clr)
{
	bmp16_frame(x1, x2, y1, y2, clr, vid_page, M5_WIDTH*2);
}


// Mode 5 screen filling
void m5_fill(COLOR clr)
{
	memset32(vid_page, dup16(clr), M5_SIZE/4);
}
