// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

static volatile u16* D_8003B68C;

static volatile s32* DEV5_DELAY = (s32*)0x1F801018;
static volatile s32* COMMON_DELAY = (s32*)0x1F801020;
static volatile s32* Dma_PCR = (s32*)0x1F8010F0;
static volatile s32* Dma_ICR = (s32*)0x1F8010F4;
static volatile s32* Dma_CHCR1 = (s32*)0x1F801098;
static volatile s32* Dma_MADR1 = (s32*)0x1F801090;
static volatile s32* Dma_CHCR2 = (s32*)0x1F8010A8;
static volatile s32* Dma_MADR2 = (s32*)0x1F8010A0;
static volatile s32* Dma_CHCR3 = (s32*)0x1F8010B8;
static volatile s32* Dma_MADR3 = (s32*)0x1F8010B0;
static volatile s32* Dma_CHCR5 = (s32*)0x1F8010D8;
static volatile s32* Dma_MADR5 = (s32*)0x1F8010D0;
static volatile s32* i_reg = (s32*)0x1F801070;
static volatile s32* i_mask = (s32*)0x1F801074;
s32 debug_cause[2] = {0, 0};
extern s32 Stframe_no;
extern s16 Stsector_offset;
extern s32 StRgb24;
extern s32 StMode;
extern void (*StFunc2)(void);
extern bool StCdIntrFlag;
extern s32 StCHANNEL;
extern s32 StStartFrame;
extern s32 CChannel;
extern s32 StFinalSector;
extern s32 StEmu_Idx;
extern s32 StRingIdx1;
extern s32 StRingIdx2;
extern s32 StEmu_Addr;
extern u32 StEndFrame;
extern s32 StSTART_FLAG;
extern u16* StRingBase;
extern StHEADER* StRingAddr;
extern s32 StRingSize;

void StCdInterrupt(void) {
    volatile s16 subroutine_arg8[4];
    CdlLOC loc;
    u_char result[8];
    u32* var_a1;
    s32 var_t0;
    u32* var_a0;
    u32 var_v1_2;
    u32 var_v1_3;
    u8* var_v1;

    if (StFinalSector == 1) {
        return;
    }
    if ((StRgb24 != 0) && (*Dma_CHCR1 & 0x01000000)) {
        StCdIntrFlag = true;
        if (StEmu_Addr != 0) {
            StEmu_Idx++;
        }
        debug_cause[0] = 1;
        return;
    }
    if (CdReady(1, result) == CdlDiskError) {
        return;
    }
    subroutine_arg8[1] = result[0];
    subroutine_arg8[2] = result[1];
    if (subroutine_arg8[1] & 4) {
        debug_cause[0] = 3;
        return;
    }
    D_8003B68C = (u16*)&StRingAddr[StRingIdx1];
    if (D_8003B68C[0] != 0) {
        if (StEmu_Addr != 0) {
            StEmu_Idx++;
        }
        debug_cause[0] = 4;
        return;
    }
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0x80;
    *DEV5_DELAY = 0x20943;
    *COMMON_DELAY = 0x1323;
    if (StMode == 0) {
        var_v1 = (u8*)&subroutine_arg8[4];
        do {
            *var_v1++ = *libcd_CDRegister2;
        } while (var_v1 < &subroutine_arg8[6]);
        for (var_v1_2 = 0; var_v1_2 < 8; var_v1_2++) {
            *libcd_CDRegister2;
        }
    }
    var_t0 = 0x11000000;
    if (StEmu_Addr != 0) {
        mem2mem(D_8003B68C, (StEmu_Idx << 0xB) + StEmu_Addr, 8, 0);
    } else {
        dma_execute(3, D_8003B68C, 0, 8, var_t0, 0, 0);
    }
    while (*Dma_CHCR3 & 0x01000000) {
    }
    ((StHEADER*)D_8003B68C)->loc = loc;
    *DEV5_DELAY = 0x20843;
    *COMMON_DELAY = 0x1325;
    if ((StSTART_FLAG == 1) && (StStartFrame != 0)) {
        if (StStartFrame != D_8003B68C[4]) {
            D_8003B68C[0] = 0;
            if (StEmu_Addr != 0) {
                StEmu_Idx++;
            }
            return;
        }
        StSTART_FLAG = 0;
    }
    if ((D_8003B68C[0] != 0x160) ||
        (((D_8003B68C[1] >> 0xA) & 0x1F) != CChannel)) {
        if (StEmu_Addr != 0) {
            StEmu_Idx = 0;
        } else {
            D_8003B68C[0];
        }
        debug_cause[0] = 5;
        D_8003B68C[0] = 0;
        return;
    }
    if ((Stsector_offset != D_8003B68C[2]) ||
        ((Stframe_no != 0) && (Stframe_no != D_8003B68C[4]))) {
        Stframe_no = 0;
        Stsector_offset = 0;
        init_ring_status(StRingIdx2, StRingIdx1 - StRingIdx2);
        StRingIdx1 = StRingIdx2;
        D_8003B68C[0] = 0;
        if (StEmu_Addr != 0) {
            StEmu_Idx++;
        }
        debug_cause[0] = 6;
        return;
    }
    if (D_8003B68C[2] == 0) {
        Stsector_offset = 0;
        Stframe_no = D_8003B68C[4];
        if ((StEndFrame != 0) && (Stframe_no >= StEndFrame)) {
            Stframe_no = 0;
            Stsector_offset = 0;
            init_ring_status(StRingIdx2, StRingIdx1 - StRingIdx2);
            StRingIdx1 = StRingIdx2;
            D_8003B68C[0] = 0;
            StSTART_FLAG = 1;
            if (StFunc2 != NULL) {
                StFunc2();
            }
            if (StEmu_Addr != 0) {
                StEmu_Idx++;
            }
            debug_cause[0] = 7;
            return;
        }
        if ((u32)(StRingSize - StRingIdx1 - 1) < D_8003B68C[3]) {
            if (StEndFrame == 0) {
                D_8003B68C[0] = 1;
                StSTART_FLAG = 1;
                if (StFunc2 != NULL) {
                    StFunc2();
                }
                if (StEmu_Addr != 0) {
                    StEmu_Idx++;
                }
                debug_cause[0] = 8;
                return;
            }
            if ((s16)StRingAddr->id != 0) {
                D_8003B68C[0] = 0;
                if (StEmu_Addr != 0) {
                    StEmu_Idx++;
                }
                debug_cause[0] = 9;
                return;
            }
            D_8003B68C[0] = 1;
            var_a1 = StRingAddr;
            var_a0 = D_8003B68C;
            StRingIdx1 = 0;
            for (var_v1_3 = 0; var_v1_3 < 8; var_v1_3++) {
                *var_a1++ = *var_a0++;
            }
            D_8003B68C = StRingAddr;
        }
        StRingIdx2 = StRingIdx1;
    }
    debug_cause[0] = 10;
    Stsector_offset++;
    StRingBase = &StRingAddr[StRingSize] + (StRingIdx1 * 0x3F);

    if (StRgb24 != 0) {
        var_t0 = 0x11000000;
        *DEV5_DELAY = 0x20943;
        *COMMON_DELAY = 0x1323;
    } else {
        *DEV5_DELAY = 0x21020843;
        var_t0 = 0x11400100;
    }
    if ((D_8003B68C[3] - 1) == D_8003B68C[2]) {
        StFinalSector = 1;
        if (StEmu_Addr != 0) {
            mem2mem(
                StRingBase, (StEmu_Idx << 0xB) + StEmu_Addr + 0x20, 0x1F8, 1);
            StEmu_Idx++;
        } else {
            dma_execute(3, StRingBase, 0, 0x1F8, var_t0, 1, 0);
        }
        Stsector_offset = 0;
        Stframe_no = 0;
        CChannel = StCHANNEL;
    } else {
        if (StEmu_Addr != 0) {
            mem2mem(
                StRingBase, (StEmu_Idx << 0xB) + StEmu_Addr + 0x20, 0x1F8, 0);
            StEmu_Idx++;
        } else {
            dma_execute(3, StRingBase, 0, 0x1F8, var_t0, 0, 0);
        }
    }
    *COMMON_DELAY = 0x1325;
    D_8003B68C[0] = 3;
    StRingIdx1 += 1;
    if ((StEmu_Addr != 0) && (StFinalSector != 0)) {
        data_ready_callback();
    }
}

void mem2mem(s32* dst, s32* src, u32 num, u32 arg3) {
    u32 i;
    for (i = 0; i < num; i++) {
        *dst++ = *src++;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", dma_execute);
