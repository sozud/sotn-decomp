// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage16SpriteBank20;

void func_060E4EDC(Entity* self);
void func_060E56DC(Entity* self);
void func_060E5CB0(Entity* self);
void func_060E5E70(Entity* self);

EntityEntry g_RStage16EntityWight = {&g_RStage16SpriteBank20, func_060E4EDC};
s16 g_RStage16WightInitOffset[2] = {0, 23};
EntityEntry g_RStage16EntityEntry28 = {&g_RStage16SpriteBank20, func_060E56DC};
EntityEntry g_RStage16EntityEntry29 = {&g_RStage16SpriteBank20, func_060E5CB0};

s16 g_RStage16WightBoneInitOffset[2] = {0, 0};
s16 g_RStage16WightBoneCollisionSensors[2][2] = {
    {0, 0},
    {255, 0},
};
u8 g_RStage16WightBoneSpinAnim[36] = {
    4, 0x14, 4, 0x15, 4, 0x14, 4, 0x15, 4,    0x16, 4, 0x17,
    4, 0x18, 4, 0x19, 4, 0x18, 4, 0x17, 4,    0x16, 4, 0x17,
    4, 0x16, 4, 0x15, 4, 0x14, 4, 0x15, 0xFF, 0,    0, 0,
};

EntityEntry g_RStage16EntityEntry30 = {&g_RStage16SpriteBank20, func_060E5E70};
s16 g_RStage16WightEffectInitOffset[2] = {0, 0};

u8 g_RStage16WightAnimation0[10] = {
    0x18, 1, 0x18, 2, 0x18, 3, 0x18, 2, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation1[10] = {
    0x18, 4, 0x18, 5, 0x18, 6, 0x18, 5, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation2[10] = {
    0x18, 7, 0x18, 8, 0x18, 9, 0x18, 8, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation3[6] = {
    0x20, 7, 0x20, 0xA, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation4[14] = {
    0x80, 1, 8, 0xB, 8, 0xC, 8, 0xD, 8, 0xE, 8, 0xF, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation5[6] = {
    1, 0x10, 1, 0x11, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation6[6] = {
    1, 0x12, 1, 0x13, 0xFF, 0xFF,
};
u8 g_RStage16WightAnimation7[14] = {
    2, 0x14, 2, 0x15, 2, 0x16, 2, 0x17, 2, 0x18, 2, 0x19, 0xFF, 0xFF,
};
u8* g_RStage16WightAnimations[] = {
    g_RStage16WightAnimation0, g_RStage16WightAnimation1,
    g_RStage16WightAnimation2, g_RStage16WightAnimation3,
    g_RStage16WightAnimation4, g_RStage16WightAnimation5,
    g_RStage16WightAnimation6, g_RStage16WightAnimation7,
};
