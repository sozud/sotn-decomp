#include "common.h"
#include "libsnd_i.h"

static s32 D_80032F08 = 0;
static s16 D_80032F0C = 0xffff;

short SsVabTransBodyPartly(
    unsigned char* addr, unsigned long bufsize, short vabid) {
    s16 new_vabid;
    s32 buff_diff;
    u32 new_bufsize;
    if (vabid < 0 || vabid > 16 || _svm_vab_used[vabid] != 2) {
        _spu_setInTransfer(0);
        printf("fail %d\n", __LINE__);
        return -1;
    }
    if (D_80032F08 == 0) {
        D_80032F0C = vabid;
        D_80032F08 = _svm_vab_total[vabid];
        printf("set D_80032F08 %d\n", D_80032F08);
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(_svm_vab_start[vabid]);
    }
    new_vabid = D_80032F0C;
    if (new_vabid != vabid) {
        _spu_setInTransfer(0);
                printf("fail %d\n", __LINE__);

        return -1;
    }
    new_bufsize = bufsize;
    if (D_80032F08 < new_bufsize) {
        new_bufsize = D_80032F08;
    }
    _spu_setInTransfer(1);
    SpuWritePartly(addr, new_bufsize);
    buff_diff = D_80032F08 - new_bufsize;
    printf("D_80032F08 %d new_bufsize %d\n", D_80032F08, new_bufsize);
    D_80032F08 = buff_diff;
    if (buff_diff == 0) {
        D_80032F0C = -1;
        D_80032F08 = 0;
        _svm_vab_used[new_vabid] = 1;
        return new_vabid;
    }
            printf("fail %d\n", __LINE__);

    return -2;
}
