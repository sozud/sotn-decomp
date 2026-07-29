// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage16SpriteBank18;

void func_060E2578(Entity* self);
void func_060E3244(Entity* self);
void func_060E3438(Entity* self);

EntityEntry g_RStage16EntityEntry20 = {
    &g_RStage16SpriteBank18, func_060E2578};
EntityEntry g_RStage16EntityEntry21 = {NULL, func_060E3244};
EntityEntry g_RStage16EntityEntry22 = {NULL, func_060E3438};

u8 g_RStage16Entity21EffectSizes[4] = {16, 18, 32, 48};

s8 g_RStage16Entity21PositionOffsets[24][2] = {
    {15, -18},  {19, -16}, {21, -16}, {22, -8},  {27, 0},   {25, 1},
    {23, 1},    {21, 11},  {13, 20},  {2, 26},   {-7, 29},  {-20, 28},
    {-32, 20},  {-48, 14}, {-64, 0},  {-52, -8}, {-40, -20}, {-32, -22},
    {-28, -24}, {-26, -26}, {-24, -24}, {-22, -24}, {-16, -25}, {-16, -24},
};

u8 g_RStage16Entity21HitboxSizes[24][2] = {
    {2, 10},  {2, 10},  {3, 10},  {4, 9},   {5, 8},   {5, 7},
    {6, 6},   {7, 6},   {8, 6},   {9, 8},   {10, 11}, {10, 15},
    {20, 18}, {24, 18}, {48, 16}, {28, 12}, {20, 10}, {16, 8},
    {12, 6},  {10, 5},  {8, 4},   {6, 6},   {4, 6},   {3, 7},
};
