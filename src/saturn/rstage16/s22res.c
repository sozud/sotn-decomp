// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage16SpriteBank22Images[];
extern u16 g_RStage16SpriteBank22Palette[];

SaturnSpriteResource g_RStage16SpriteBank22 = {
    g_RStage16SpriteBank22Images,
    g_RStage16SpriteBank22Palette,
    -1,
    0xFFFF,
};
