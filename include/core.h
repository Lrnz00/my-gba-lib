// core.h
//
// General-use functions


#ifndef CORE
#define CORE

#include "types.h"


// memset/cpy() for 16 bits
// dest and src must be halfword-aligned
void memset16(void *dest, u16 hw, u32 hwcount);
void memcpy16(void *dest, const void *src, u32 hwcount);

// memset/cpy() for 32 bits
// dest and src must be word-aligned
void memset32(void *dest, u32 wd, u32 hwcount);
void memcpy32(void *dest, const void *src, u32 wdcount);


#endif
