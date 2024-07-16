#include <game.h>
#include "dra.h"

AnimationFrame D_800B0798[] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {0, 0}};

// no known usages
AnimationFrame D_800B07BC[] = {{2, 9}, {1, 16}, {0, 0}};

AnimationFrame D_800B07C8[] = {
    {5, 13}, {2, 14}, {2, 14}, {2, 16}, {1, 17}, {1, 18}, {1, 19},
    {1, 20}, {1, 21}, {1, 22}, {1, 23}, {1, 24}, {1, 25}, {1, 26},
    {1, 27}, {1, 28}, {2, 9},  {1, 16}, {2, 10}, {1, 16}, {2, 11},
    {1, 16}, {2, 12}, {2, 9},  {1, 16}, {0, 23}};

s32 D_800B0830[] = {FIX(-2.5), FIX(-2.5), FIX(-2.5)};

s32 D_800B083C[] = {FIX(0), FIX(-0.75), FIX(0.75)};

// tetra spirit out of bounds problem, add a value at beginning and end
#ifdef VERSION_PC
u8 D_800B0848[] = {0x00, 0x80, 0x80, 0x80, 0x90, 0x80, 0xA0, 0x80, 0xB0,
                   0xA0, 0x80, 0xA0, 0x90, 0xA0, 0xA0, 0xA0, 0xB0, 0x03};
#else
u8 D_800B0848[] = {0x80, 0x80, 0x80, 0x90, 0x80, 0xA0, 0x80, 0xB0,
                   0xA0, 0x80, 0xA0, 0x90, 0xA0, 0xA0, 0xA0, 0xB0};
#endif

u16 D_800B0858[] = {0x03C0, 0x0440, 0x0340, 0x04C0};

// tetra spirit out of bounds problem, add another value at end
#ifdef VERSION_PC
s16 D_800B0860[] = {31, 0,   31, -32, 0,  -32, -32, -32, -32,
                    0,  -32, 31, 0,   31, 31,  31,  31,  0};
#else
s16 D_800B0860[] = {31, 0,   31, -32, 0,  -32, -32, -32, -32,
                    0,  -32, 31, 0,   31, 31,  31,  31};
#endif

s16 D_800B0884[] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005,
                    0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005,
                    0x0005, 0x0004, 0x0003, 0x0002, 0x0001};
s16 D_800B08A8[] = {0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00A0,
                    0x00AA, 0x00AA, 0x00AA, 0x00AA, 0x00AA, 0x00A0,
                    0x0080, 0x0060, 0x0040, 0x0020, 0x0000};

helper_8012F178 D_800B08CC[6] = {0};

s32 D_800B0914 = 0;
s32 D_800B0918 = 0;
s32 D_800B091C = 0;
s32 D_800B0920 = 0;
