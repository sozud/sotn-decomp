// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern s32 StRingIdx3;
extern StHEADER* StRingAddr;
extern s32 StRingSize;

u_long StFreeRing(u_long* base) {
    s32 temp_a1;
    s32 i;
    s16 nSectors;
    StHEADER* temp_v0;

    temp_a1 = (base - (u_long*)&StRingAddr[StRingSize]) / 504;
    temp_v0 = &StRingAddr[temp_a1];
    nSectors = StRingAddr[temp_a1].nSectors;
    if ((s16)temp_v0->id != 4) {
        return 1;
    }
    for (i = 0; i < nSectors; i++) {
        *((s16*)&StRingAddr[i + temp_a1]) = 0;
    }
    StRingIdx3 = i + temp_a1;
    return 0;
}
