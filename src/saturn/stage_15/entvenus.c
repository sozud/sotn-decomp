// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank28;

void func_060ECE0C(Entity* self);
void func_060ED1C0(Entity* self);
void func_060ED848(Entity* self);
void func_060EDA88(Entity* self);
void func_060EDD10(Entity* self);

EntityEntry g_Stage15EntityVenusManTrap = {
    &g_Stage15SpriteBank28, func_060ECE0C};
s16 g_Stage15VenusManTrapInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry54 = {&g_Stage15SpriteBank28, func_060ED1C0};
s16 g_Stage15VenusManTrapFlowerInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry56 = {&g_Stage15SpriteBank28, func_060ED848};
s16 g_Stage15VenusManTrapTendrilInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry57 = {&g_Stage15SpriteBank28, func_060EDA88};
s16 g_Stage15VenusManTrapDartInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry55 = {&g_Stage15SpriteBank28, func_060EDD10};

u8 g_Stage15VenusManTrapAnimation0[10] = {
    2, 1, 6, 2, 6, 3, 6, 4, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation1[10] = {
    6, 5, 6, 6, 6, 7, 6, 8, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation2[10] = {
    2, 9, 6, 0xA, 6, 0xB, 6, 0xC, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation3[10] = {
    6, 0xD, 6, 0xE, 6, 0xF, 6, 0x10, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation4[6] = {
    2, 0x13, 2, 0x14, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation5[6] = {
    2, 0x16, 2, 0x17, 0xFF, 0xFF,
};
u8 g_Stage15VenusManTrapAnimation6[10] = {
    4, 0x18, 3, 0x19, 2, 0x1A, 2, 0x1B, 0xFF, 0xFF,
};
u16 g_Stage15VenusManTrapAnimationsPadding = 0;
u8* g_Stage15VenusManTrapAnimations[] = {
    g_Stage15VenusManTrapAnimation0, g_Stage15VenusManTrapAnimation1,
    g_Stage15VenusManTrapAnimation2, g_Stage15VenusManTrapAnimation3,
    g_Stage15VenusManTrapAnimation4, g_Stage15VenusManTrapAnimation5,
    g_Stage15VenusManTrapAnimation6,
};
