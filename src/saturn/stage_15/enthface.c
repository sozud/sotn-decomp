// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank26;

void func_060E9E44(Entity* self);
void func_060EAAA8(Entity* self);
void func_060EACDC(Entity* self);
void func_060EB2B8(Entity* self);
void func_060EB824(Entity* self);
void func_060EBA00(Entity* self);

EntityEntry g_Stage15EntityHumanFaceTree = {
    &g_Stage15SpriteBank26, func_060E9E44};
EntityEntry g_Stage15EntityEntry46 = {&g_Stage15SpriteBank26, func_060EAAA8};
EntityEntry g_Stage15EntityEntry47 = {&g_Stage15SpriteBank26, func_060EACDC};
EntityEntry g_Stage15EntityEntry48 = {&g_Stage15SpriteBank26, func_060EB2B8};

s16 g_Stage15HumanFaceTreeBranchOffsets[8][2] = {
    {47, 4}, {47, 4}, {47, 4}, {47, 4}, {47, 4}, {35, 7}, {35, 7}, {35, 7},
};

EntityEntry g_Stage15EntityEntry49 = {&g_Stage15SpriteBank26, func_060EB824};
s16 g_Stage15Entity49PartOffsets[13][2] = {
    {8, 0}, {14, 0}, {6, 0}, {9, 0},  {12, 0}, {15, 0}, {5, 0},
    {9, 0}, {8, 0},  {9, 0}, {10, 0}, {11, 0}, {12, 0},
};
EntityEntry g_Stage15EntityEntry50 = {&g_Stage15SpriteBank26, func_060EBA00};

u8 g_Stage15HumanFaceTreeAnimation0[42] = {
    0x60, 1, 8,   2, 8, 3, 8, 4, 8, 5, 8, 6, 8, 7, 8, 8, 8, 9, 8, 0xA,  8,
    0xB,  8, 0xA, 8, 9, 8, 8, 8, 7, 8, 6, 8, 5, 8, 4, 8, 3, 8, 2, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation1[10] = {
    0x60, 2, 2, 3, 3, 0xC, 0x40, 0xD, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation2[28] = {
    0x60, 2,    2, 3,    3, 0xC,  4, 0xD,  4, 0xE,  5,    0xF,  0xC,  0x14,
    1,    0x15, 2, 0x14, 1, 0x15, 1, 0x16, 1, 0x15, 0x40, 0x16, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation3[10] = {
    0x60, 0xA, 2, 9, 3, 0x10, 0x40, 0x11, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation4[28] = {
    0x60, 0xA,  2, 9,    3, 0x10, 4, 0x11, 4, 0x12, 5,    0x13, 0xC,  0x17,
    1,    0x18, 2, 0x17, 1, 0x18, 1, 0x19, 1, 0x18, 0x40, 0x19, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation5[18] = {
    0xF,  0x22, 0x30, 0x23, 5,    0x24, 4,    0x25, 3,
    0x26, 3,    0x27, 3,    0x28, 0x3F, 0x29, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation6[16] = {
    0x60, 0x2F, 5, 0x30, 4,    0x31, 4,    0x32,
    4,    0x33, 4, 0x34, 0x40, 0x35, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation7[10] = {
    0xB, 0x36, 0xB, 0x37, 0xB, 0x38, 0xB, 0x39, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation8[10] = {
    0xB, 0x3A, 0xB, 0x3B, 0xB, 0x3C, 0xB, 0x3D, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation9[20] = {
    0x14, 0x3E, 0xC, 0x3F, 0xC, 0x40, 0xC, 0x41, 0x10, 0x42,
    0xC,  0x42, 0xC, 0x41, 0xC, 0x40, 0xC, 0x3F, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation10[4] = {0x80, 0x43, 0xFF, 0xFF};
u8 g_Stage15HumanFaceTreeAnimation11[18] = {
    0x60, 0x1A, 0x60, 0x1B, 0x60, 0x1C, 0x60, 0x1D, 0x60,
    0x1E, 0x60, 0x1F, 0x60, 0x20, 0x60, 0x21, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation12[18] = {
    0xF,  0x22, 0x30, 0x23, 4,    0x24, 3,    0x25, 2,
    0x45, 2,    0x46, 2,    0x47, 0xF,  0x29, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation13[14] = {
    0x30, 0x2F, 3, 0x30, 2, 0x31, 2, 0x48, 2, 0x49, 0x40, 0x35, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation14[8] = {
    5, 0x4F, 5, 0x50, 5, 0x51, 0xFF, 0xFF,
};
u8 g_Stage15HumanFaceTreeAnimation15[8] = {
    5, 0x4C, 5, 0x4D, 5, 0x4E, 0xFF, 0xFF,
};
u16 g_Stage15HumanFaceTreeAnimationPadding = 0;

u8* g_Stage15HumanFaceTreeAnimations[] = {
    g_Stage15HumanFaceTreeAnimation0,  g_Stage15HumanFaceTreeAnimation1,
    g_Stage15HumanFaceTreeAnimation2,  g_Stage15HumanFaceTreeAnimation3,
    g_Stage15HumanFaceTreeAnimation4,  g_Stage15HumanFaceTreeAnimation5,
    g_Stage15HumanFaceTreeAnimation6,  g_Stage15HumanFaceTreeAnimation7,
    g_Stage15HumanFaceTreeAnimation8,  g_Stage15HumanFaceTreeAnimation9,
    g_Stage15HumanFaceTreeAnimation10, g_Stage15HumanFaceTreeAnimation11,
    g_Stage15HumanFaceTreeAnimation12, g_Stage15HumanFaceTreeAnimation13,
    g_Stage15HumanFaceTreeAnimation14, g_Stage15HumanFaceTreeAnimation15,
};
