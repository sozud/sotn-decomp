// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

#if !defined(VERSION_PSP)
u32 D_801BEB04[24];
s32 D_801BEB64[83][2];
u32 D_801BEDFC;
u32 D_801BEE00;
u32 D_801BEE04;
u16 D_801BEE08[2];
u16 D_801BEE0C[66];
u16 D_801BEE90[2312];
#endif

// HACK move the header inclusion at the end to not scrable the BSS variables
#include "st0.h"
#include "../pfn_entity_update.h"
#include "../create_entity.h"
