// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern s32 StRingIdx3;
extern s32 StEndFrame;
extern StHEADER* StRingAddr;
extern volatile s32 StRingSize;

u_long StGetNext(u_long** addr, u_long** header) {
    volatile StHEADER* ptr = &StRingAddr[StRingIdx3];
    if (ptr->id == 1) {
        StRingIdx3 = 0;
        if (StEndFrame != 0) {
            ptr->id = 0;
        }
        ptr = &StRingAddr[StRingIdx3];
    }
    if (ptr->id == 2) {
        ptr->id = 4;
        *addr = &StRingAddr[StRingSize] + (StRingIdx3 * 0x3F);
        *header = ptr;
        return 0;
    } else {
        return 1;
    }
}
