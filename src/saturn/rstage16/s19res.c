// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage16SpriteBank19Images[];
extern u16 g_RStage16SpriteBank19Palette[];

SaturnSpriteResource g_RStage16SpriteBank19 = {
    g_RStage16SpriteBank19Images,
    g_RStage16SpriteBank19Palette,
    -1,
    0xFFFF,
};
