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
	// Pack two 16-bit values into a 32-bit word
    u32 hw32 = ((u32)hw << 16) | hw;
    u32 *ptr32 = (u32*)dest;

    // Fill in 32-bit chunks for better performance
    while (hwcount >= 2) {
        *ptr32++ = hw32;
        hwcount -= 2;
    }

    // Handle remaining 16-bit word if hwcount was odd
    if (hwcount) {
        *((u32*)ptr32) = hw;
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
	// Treat dest as 32-bit pointer
	u32 *ptr = (u32*)dest;

    while (wdcount--) {
        // Write the 32-bit value directly
		*ptr++ = wd;
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
