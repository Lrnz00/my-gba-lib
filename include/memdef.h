// memdef.h
//
// Memory map defines.


#ifndef MEMDEF_H
#define MEMDEF_H


// REG_DISPCNT defines
#define DCNT_MODE0		0x0000
#define DCNT_MODE1		0x0001
#define DCNT_MODE2		0x0002
#define DCNT_MODE3		0x0003
#define DCNT_MODE4		0x0004
#define DCNT_MODE5		0x0005
#define DCNT_GB			0x0008
#define DCNT_PAGE		0x0010
#define DCNT_OAM_HBL	0x0020
#define DCNT_OBJ_2D		0x0000
#define DCNT_OBJ_1D		0x0040
#define DCNT_BLANK		0x0080
#define DCNT_BG0		0x0100
#define DCNT_BG1		0x0200
#define DCNT_BG2		0x0400
#define DCNT_BG3		0x0800
#define DCNT_OBJ		0x1000
#define DCNT_WIN0		0x2000
#define DCNT_WIN1		0x4000
#define DCNT_WINOBJ		0x8000

// REG_DISPCNT masks
#define DCNT_MODE_MASK		0x0007
#define DCNT_LAYER_MASK		0x1F00
#define DCNT_WIN_MASK		0xE000


#endif // MEMDEF_H
