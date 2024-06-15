#include "common.h"
#include "libspu_internal.h"

s32 SpuInitMalloc(s32 num, s8* top) {
    SPU_MALLOC* temp = top;
    printf("top %p\n", top);
    printf("temp %p\n", temp);
    printf("%d %d\n", temp->addr, temp->size);
    if (num > 0) {
        temp->addr = 0x40001010;
        _spu_memList = temp;
        D_80033560 = 0;
        _spu_AllocBlockNum = num;
        temp->size = (s32)((0x10000 << _spu_mem_mode_plus) - 0x1010);
        return num;
    }
    return 0;
}
