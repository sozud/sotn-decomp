#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>

#include <assert.h>

void SpuSetVoiceAttr(SpuVoiceAttr* arg) { 
    assert(0);
    DEBUGF("SpuSetVoiceAttr"); }

extern s32 _spu_AllocBlockNum;
extern s32 D_80033560;
extern s32 _spu_mem_mode_plus;
extern u32 _spu_mem_mode_unitM;
extern s32 _spu_rev_offsetaddr;
extern s32 _spu_rev_reserve_wa;

typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;
extern SPU_MALLOC* _spu_memList;

// long SpuMallocWithStartAddr(unsigned long addr, long size) {
//     assert(0);
//     NOT_IMPLEMENTED;
//     return -1;
// }

 long SpuMallocWithStartAddr(unsigned long addr, long size) {
#if 0
    s32 temp_a1;
    s32 temp_a3_2;
    s32 list_pos;
    s32 var_a2;
    s32 addr_temp;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    u32 size_temp;
    u32 sep_size;
    u32 var_a1;
    u32 sep_addr;
    u32 fmask;
    u32 fourmask;
    if (_spu_rev_reserve_wa == 0) {
        var_s2 = 0;
    } else {
        var_s2 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }
    var_a2 = size;
    if (size &  ~_spu_mem_mode_unitM) {
        var_a2 = size + _spu_mem_mode_unitM;
    }
    var_a1 = addr;
    sep_size = (var_a2 >> _spu_mem_mode_plus) << _spu_mem_mode_plus;
    if (addr &  ~_spu_mem_mode_unitM) {
        var_a1 = addr + _spu_mem_mode_unitM;
    }
    addr_temp = ((s32) var_a1 >> _spu_mem_mode_plus) << _spu_mem_mode_plus;
    var_v0 = -1;
    if (addr_temp >= 0x1010) {
        temp_a3_2 = addr_temp + sep_size;
        var_v0 = -1;
        if (((0x10000 << _spu_mem_mode_plus) - var_s2) >= temp_a3_2) {
            temp_a1 = addr_temp - 0x1010;
            if (_spu_memList->addr & 0x40000000) {
                size_temp = ((_spu_memList->size + 0x1010) - addr_temp) - sep_size;
                if (temp_a1 > 0) {
                    var_v0 = -1;
                    if ((D_8003355C - 2) >= D_80033560) {
                        _spu_memList->addr = 0x80001010;
                        _spu_memList[2].addr = (s32) (temp_a3_2 | 0x40000000);
                        var_v0_2 = 2;
                        _spu_memList->size = (u32) temp_a1;
                        _spu_memList[1].addr = addr_temp;
                        _spu_memList[1].size = sep_size;
                        _spu_memList[2].size = size_temp;

                        // _spu_memList->unkC = sep_size;
                        // _spu_memList->unk14 = size_temp;
                        goto block_15;
                    } else {
                        return -1;
                    }
                } else {
                    var_v0 = -1;
                    if ((D_8003355C - 1) >= D_80033560) {
                        _spu_memList[1].addr = (s32) (temp_a3_2 | 0x40000000);
                        // _spu_memList->unk8 = (s32) (temp_a3_2 | 0x40000000);
                        var_v0_2 = 1;
                        _spu_memList->addr = (u32) addr_temp;
                        _spu_memList->size = sep_size;
                        _spu_memList[1].size = size_temp;
                        // _spu_memList->unkC = size_temp;
block_15:
                        D_80033560 = var_v0_2;
                        goto block_30;
                    }
                }
                /* Duplicate return node #31. Try simplifying control flow for better match */
                return var_v0;
            }
            func_800286E0();
            list_pos = 0;
loop_18:
            fmask = 0x0FFFFFFF;
            fourmask = 0x40000000;
            // temp_a1_2 = _spu_memList[list_pos].addr;
            if ((s32) _spu_memList[list_pos].addr < 0) {
                sep_addr = _spu_memList[list_pos].addr & fmask;
                if ((u32) addr_temp >= sep_addr) {
                    if (((u32) addr_temp < (u32) (sep_addr +_spu_memList[list_pos].size)) || (_spu_memList[list_pos+1].addr & fourmask)) {
                        sep_addr = (u32) addr_temp;
                        if ((_spu_memList[list_pos].size - (addr_temp - (_spu_memList[list_pos].addr & fmask))) >= (s32) sep_size) {
                            goto block_29;
                        }
                    }
                    goto block_27;
                }
                if ((s32) _spu_memList[list_pos].size < (s32) sep_size) {
                    list_pos += 1;
                    goto loop_18;
                }
                goto block_29;
            }
            if (!(_spu_memList[list_pos].addr & fourmask)) {
block_27:
                list_pos += 1;
                goto loop_18;
            }
            sep_addr = _spu_memList[list_pos].addr & fmask;
            if ((_spu_memList[list_pos].size - var_s2) >= (s32) sep_size) {
block_29:
                addr_temp = _SpuMallocSeparateTo3(list_pos, sep_addr, sep_size, fmask);
block_30:
                func_800286E0();
                var_v0 = addr_temp;
                /* Duplicate return node #31. Try simplifying control flow for better match */
                return var_v0;
            }
            return -1;
        }
    } else {
        return -1;
    }

    return var_v0;
    #endif
    return 0;
}
