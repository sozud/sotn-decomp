// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage16SpriteBank20Images[];
extern u16 g_RStage16SpriteBank20Palette[];

SaturnSpriteResource g_RStage16SpriteBank20 = {
    g_RStage16SpriteBank20Images,
    g_RStage16SpriteBank20Palette,
    -1,
    0xFFFF,
};
