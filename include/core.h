// core.h
//
// General-use functions


#ifndef CORE_H
#define CORE_H

#include "types.h"


// memset/cpy() for 16 bits
// dest and src must be halfword-aligned
// hw is passed as u32 because standard memset() works that way
void memset16(void *dest, u32 hw, u32 hwcount);
void memcpy16(void *dest, const void *src, u32 hwcount);

// memset/cpy() for 32 bits
// dest and src must be word-aligned
void memset32(void *dest, u32 wd, u32 wdcount);
void memcpy32(void *dest, const void *src, u32 wdcount);


// Helpers for creating filled integers
u16 dup8(u8 ch);
u32 quad8(u8 ch);
u32 dup16(u16 hw);


#endif // CORE_H
