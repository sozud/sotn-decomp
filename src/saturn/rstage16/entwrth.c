// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_RStage16SpriteBank19;

void func_060E3608(Entity* self);
void func_060E4664(Entity* self);
void func_060E4804(Entity* self);
void func_060E4AFC(Entity* self);

EntityEntry g_RStage16EntityWraith = {&g_RStage16SpriteBank19, func_060E3608};
EntityEntry g_RStage16EntityEntry24 = {NULL, func_060E4664};
EntityEntry g_RStage16EntityEntry25 = {NULL, func_060E4804};
EntityEntry g_RStage16EntityEntry26 = {NULL, func_060E4AFC};
