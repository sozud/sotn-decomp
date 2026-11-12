// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"

extern u32 StStartFrame;
extern u32 StEndFrame;
extern u32 StSTART_FLAG;

void StSetMask(u_long mask, u_long start, u_long end) {
    StSTART_FLAG = mask;
    StStartFrame = start;
    StEndFrame = end;
}
