// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DF8AC(Entity* self);
void func_060DFA14(Entity* self);
void func_060DFB7C(Entity* self);
void func_060DFC68(Entity* self);
void func_060DFDD4(Entity* self);

EntityEntry g_RStage16EntityEntry01 = {
    &g_SaturnSharedSpriteBank1Resource, func_060DF8AC};
EntityEntry g_RStage16EntityEntry05 = {
    &g_SaturnSharedSpriteBank5Resource, func_060DFA14};
EntityEntry g_RStage16EntityEntry18 = {NULL, func_060DFB7C};
EntityEntry g_RStage16EntityEntry19 = {
    &g_SaturnSharedSpriteBank1Resource, func_060DFC68};
EntityEntry g_RStage16GreyPuffEntityEntry = {
    &g_SaturnSharedSpriteBank5Resource, func_060DFDD4};

s32 g_RStage16ExplosionVariantYVelocities[6] = {
    0x800, 0x2800, 0x4800, 0x7000, 0xE000, 0x12000,
};

u8 g_RStage16ExplosionVariantStartFrames[4] = {1, 9, 21, 43};

u16 g_RStage16ExplosionVariantLifetimes[4] = {16, 24, 42, 47};

s32 g_RStage16GreyPuffYVelocities[6] = {
    0x400, 0x2400, 0x3C00, 0x6000, 0x7800, 0xC000,
};

s16 g_RStage16GreyPuffRotations[7] = {
    0x0C, 0x14, 0x20, 0x2C, 0x34, 0x40, 0x40,
};

s16 g_RStage16ExplosionVariantSizes[7] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
};
