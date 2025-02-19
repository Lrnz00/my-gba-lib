// core.c
//
// Implementations of core.h


#include "core.h"
#include <string.h>


// For reference:
//   void *memset(void *ptr, int ch, size_t num)
//   void *memcpy(void *destination, const void *source, size_t num)


// memset() for 16 bits
// dest must be halfword-aligned
// hw is passed as u32 because standard memset() works that way
void memset16(void *dest, u32 hw, u32 hwcount)
{
	while (hwcount--) {
		memset(dest, hw, 1);
		memset(dest + 1, hw >> 8, 1);
		dest += 2;
	}
}


// memcpy() for 16 bits
// dest and src must be halfword-aligned
void memcpy16(void *dest, const void *src, u32 hwcount)
{

}

// memset() for 32 bits
// dest must be word-aligned
void memset32(void *dest, u32 wd, u32 wdcount)
{
	while (wdcount--) {
		memset(dest, wd, 1);
		memset(dest + 1, wd >> 8, 1);
		memset(dest + 2, wd >> 16, 1);
		memset(dest + 3, wd >> 24, 1);
		dest += 4;
	}
}


// memcpy() for 32 bits
// dest and src must be word-aligned
void memcpy32(void *dest, const void *src, u32 wdcount)
{

}


// Creates a filled u16 from a u8
u16 dup8(u8 ch)
{
	return ch | (ch << 8);
}


// Creates a filled u32 from a u8
u32 quad8(u8 ch)
{
	return ch | (ch << 8) | (ch << 16) | (ch << 24);
}


// Creates a filled u32 from a u16
u32 dup16(u16 hw)
{
	return hw | (hw << 16);
}
