// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E08C8(Entity* self);
void func_060E09D4(Entity* self);

EntityEntry g_RStage16EntityEntry14 = {
    &g_SaturnSharedSpriteBank8Resource, func_060E08C8};
EntityEntry g_RStage16EntityEntry08 = {NULL, func_060E09D4};
