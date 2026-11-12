// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 _spu_AllocBlockNum = 0;
s32 _spu_AllocLastNum = 0;
SPU_MALLOC* _spu_memList = NULL;
