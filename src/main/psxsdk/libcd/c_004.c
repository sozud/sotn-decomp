// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern StHEADER* StRingAddr;
extern s32 StMode;
extern void (*StFunc1)(void);
extern s32 StFinalSector;
extern s32 StRingIdx1;
extern s32 StRingIdx2;

static CdlLOC fp_2;
static s32 D_8003B688;

void data_ready_callback(void) {
    StHEADER* ptr = &StRingAddr[StRingIdx2];
    do {
    } while (0);

    ptr->id = 2;
    fp_2 = ptr->loc;
    D_8003B688 = ptr->frameCount;
    StRingIdx2 = StRingIdx1;
    if (StFunc1 != NULL) {
        StFunc1();
    }
    StFinalSector = 0;
}

s32 StGetBackloc(CdlLOC* loc) {
    if (StMode) {
        return -1;
    }
    CdIntToPos(CdPosToInt(&fp_2) + 1, loc);
    return D_8003B688;
}
