// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage16SpriteBank18Images[];
extern u16 g_RStage16SpriteBank18Palette[];

SaturnSpriteResource g_RStage16SpriteBank18 = {
    g_RStage16SpriteBank18Images,
    g_RStage16SpriteBank18Palette,
    -1,
    0xFFFF,
};
