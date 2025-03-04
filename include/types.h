// types.h
//
// A set of typedefs, #defines and inlines.


#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>


// Base types
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;


// Volatile types
typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;


// Colors are 16-bit in the 5.5.5 format
typedef u16 COLOR;


#endif // TYPES_H
