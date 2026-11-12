// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

extern s32 _spu_AllocBlockNum;

void SpuFree(unsigned long arg0) {
    s32 i;

    for (i = 0; i < _spu_AllocBlockNum; i++) {
        if (_spu_memList[i].addr & 0x40000000) {
            break;
        }
        if (_spu_memList[i].addr == arg0) {
            _spu_memList[i].addr |= 0x80000000;
            break;
        }
    }
    _spu_gcSPU();
}
