// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DC840(Entity* self);
void func_060DD09C(Entity* self);
void func_060DD588(Entity* self);
void func_060DE0BC(Entity* self);
void func_060DE1BC(Entity* self);

extern char g_RStage16ObtainedText[];

typedef struct {
    s8 values[2];
    u8 padding[2];
} RStage16HeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} RStage16SubweaponIndices;

EntityEntry g_RStage16EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DC840};
EntityEntry g_RStage16EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DD09C};
EntityEntry g_RStage16EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DD588};
EntityEntry g_RStage16EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DE0BC};
EntityEntry g_RStage16EntityEntry13 = {NULL, func_060DE1BC};

RStage16HeartPrizeValues g_RStage16HeartPrizes = {{1, 5}, {0, 0}};

u32 g_RStage16GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

RStage16SubweaponIndices g_RStage16AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_RStage16RelicOrbTexts[] = {g_RStage16ObtainedText};

s16 g_RStage16RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_RStage16RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_RStage16RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_RStage16RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_RStage16RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_RStage16RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
