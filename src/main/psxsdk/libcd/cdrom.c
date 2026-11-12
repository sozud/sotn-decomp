// SPDX-License-Identifier: MIT
#include "common.h"
#include <psxsdk/libcd.h>
#include "registers.h"

extern StHEADER* StRingAddr;
extern u_long StRingSize;

void StSetRing(u_long* ring_addr, u_long ring_size) {
    StRingAddr = (StHEADER*)ring_addr;
    StRingSize = ring_size;
    StClearRing();
}
