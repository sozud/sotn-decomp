// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

void func_us_801C9538(void) {
    D_us_801DF788 = 2;
    D_us_801DF78A = 0;
    D_us_801DF78E = 0;
    D_us_801DF78F = 8;
}

INCLUDE_ASM("st/no4/nonmatchings/cutscene", func_us_801C9568);

INCLUDE_ASM("st/no4/nonmatchings/cutscene", CutsceneUnk3);

INCLUDE_ASM("st/no4/nonmatchings/cutscene", func_us_801C9764);

INCLUDE_ASM("st/no4/nonmatchings/cutscene", func_us_801C9800);

INCLUDE_ASM("st/no4/nonmatchings/cutscene", ScaleCutsceneAvatar);

INCLUDE_RODATA("st/no4/nonmatchings/cutscene", D_us_801C0A70);

INCLUDE_ASM("st/no4/nonmatchings/cutscene", func_us_801C9A54);
