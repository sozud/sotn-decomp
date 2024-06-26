#ifndef WANT_LIBSND_LLE
#include <common.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include <log.h>

short SsUtSetVVol(short vc, short voll, short volr) {
    DEBUGF("not implemented\n");
    return 0;
}

void SsSetSerialAttr(char s_num, char attr, char mode) { NOT_IMPLEMENTED; }

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    NOT_IMPLEMENTED;
}

void SsSetMVol(short voll, short volr) { NOT_IMPLEMENTED; }

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { NOT_IMPLEMENTED; }

short SsSeqOpen(u_long* addr, short vab_id) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsSeqClose(short seq_access_num) { NOT_IMPLEMENTED; }

void SsSeqStop(short seq_access_num) { NOT_IMPLEMENTED; }

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note,
                 short fine, short voll, short volr) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsUtReverbOn(void) { NOT_IMPLEMENTED; }

void SsUtSetReverbType(short type) { NOT_IMPLEMENTED; }

void SsSetTableSize(char* table, short s_max, short t_max) { NOT_IMPLEMENTED; }

void SsStart(void) { NOT_IMPLEMENTED; }

char SsSetReservedVoice(char voices) {
    DEBUGF("%d", voices);
    return 0;
}

void SsSetTickMode(long tick_mode) { DEBUGF("%d", tick_mode); }

void MySsInitHot();
void SsInitHot(void) { MySsInitHot(); }

void SsSetStereo(void) { NOT_IMPLEMENTED; }

void SsSetMono(void) { NOT_IMPLEMENTED; }

void SsSetSerialVol(short s_num, short voll, short volr) {
    DEBUGF("s_num %d voll %d volr %d", s_num, voll, volr);
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    DEBUGF("ldepth %d rdepth %d", ldepth, rdepth);
}

s32 SsVabTransCompleted(short immediateFlag) {
    NOT_IMPLEMENTED;
    return 1;
}

s32 SsVabOpenHeadSticky(u_char* addr, u_long vabid, u_long sbaddr) {
    NOT_IMPLEMENTED;
    return 0;
}

s32 SsVabTransBodyPartly(u_char* addr, u_long bufsize, u_long vabid) {
    NOT_IMPLEMENTED;
    return 0;
}

void SsVabClose(short vab_id) { NOT_IMPLEMENTED; }

#else
#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>
#include <assert.h>
#include "../../main/psxsdk/libsnd/libsnd_i.h"
#include <stdarg.h>

u16* D_80032F10;

struct SpuVoice _svm_voice[NUM_SPU_CHANNELS];

void WaitEvent(s32 a ) {}

union RegBuf _svm_sreg_buf;

unsigned char _svm_sreg_dirty[NUM_SPU_CHANNELS];

unsigned short _svm_okon1;
unsigned short _svm_okon2;
unsigned short _svm_okof1;
unsigned short _svm_okof2;

s32 _svm_brr_start_addr[16]; /* number: 10 */
s16 _svm_stereo_mono;        /* number: 11 */
SpuReverbAttr _svm_rattr;    /* number: 12 */
u8 _svm_vab_used[16] = {0};  /* number: 13 */
u8 spuVmMaxVoice;            /* number: 14 */
u16 _svm_vab_count;          /* number: 15 */
s16 kMaxPrograms;            /* number: 16 */
struct struct_svm _svm_cur;  /* number: 17 */
s16 _svm_damper;             /* number: 18 */
s16 _svm_vcf;                /* number: 19 */
u8 _svm_auto_kof_mode;       /* number: 20 */
VabHdr* _svm_vab_vh[16];     /* number: 21 */
ProgAtr* _svm_vab_pg[16];    /* number: 22 */
VagAtr* _svm_vab_tn[16];     /* number: 23 */
s32 _svm_vab_start[16];      /* number: 24 */
s32 _svm_vab_total[16];      /* number: 25 */
VabHdr* _svm_vh;             /* number: 26 */
ProgAtr* _svm_pg;            /* number: 27 */
VagAtr* _svm_tn;             /* number: 28 */
void* _svm_vg;               /* number: 29 */

void ResetCallback() {}

typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);

SndSsMarkCallbackProc _SsMarkCallback[32][16]; /* #11 */
struct SeqStruct* _ss_score[32];               /* #12 */
s32 VBLANK_MINUS;                              /* #13 */
s32 _snd_openflag;                             /* #14 */
s16 _snd_seq_s_max;                            /* #15 */
s16 _snd_seq_t_max;                            /* #16 */
s32 _snd_ev_flag;                              /* #17 */

long _spu_transMode;

void* DMACallback(int dma, void (*func)()) { return NULL; }

s32 _spu_rev_startaddr[16] = {
    0x0000FFFE, 0x0000FB28, 0x0000FC18, 0x0000F6F8, 0x0000F204, 0x0000EA44,
    0x0000E128, 0x0000CFF8, 0x0000CFF8, 0x0000F880, 0x00000002, 0x000004D8,
    0x000003D8, 0x00000908, 0x00000DFC, 0x000015BC};
s32 D_80033098;

// s_ini.c
s32 _spu_fd = 0;
long _spu_trans_mode = 0;
s32 _spu_rev_flag = 0;
s32 _spu_rev_reserve_wa = 0;
s32 _spu_rev_offsetaddr = 0;

SpuReverbAttr _spu_rev_attr = {0, 0, 0, 0, 0, 0};

u16 _spu_voice_centerNote[24] = {
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
    0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000};

s32 _spu_EVdma = 0;

s32 _spu_keystat = 0;

s8 _spu_zerobuf[1024] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
s32 _spu_isCalled = 0;

u16 D_80032F14[1];
s32 _spu_AllocBlockNum;
s32 D_80033560;
s8* D_80033564;
s32 _spu_mem_mode_plus = 3;

typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

SPU_MALLOC* _spu_memList = NULL;

s32 _spu_inTransfer;
struct _ss_spu_vm_rec_struct {
    u32 pad[2];
    SPU_MALLOC D_8003BD50[364];
};

short D_80032EC0[] = {0x0000, 0x0000, 0x1000, 0x3000,
                      0x00BF, 0x0000, 0x0000, 0x0000};
union SpuUnion* _spu_RXX;

u16 D_80032ED0[] = {0x3FFF, 0x3FFF, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000};

struct _ss_spu_vm_rec_struct _ss_spu_vm_rec;

s16 _svm_orev1;
s16 _svm_orev2;

void SpuVmKeyOn(s16 a , s16 b , u8 c , s32 d , s32 e , s32 f) { assert(0); }

s32 _svm_envx_hist[32];
s32 D_8003BD08 = 0;

void SpuVmFlush(void) {}

void SpuVmKeyOnNow(short vagCount, short pitch) { assert(0); }

void vmNoiseOn(s32 arg0) { assert(0); }

void SpuVmDoAllocate(void) { assert(0); }

struct rev_param_entry {
    u32 flags;
    u16 dAPF1;
    u16 dAPF2;
    u16 vIIR;
    u16 vCOMB1;
    u16 vCOMB2;
    u16 vCOMB3;
    u16 vCOMB4;
    u16 vWALL;
    u16 vAPF1;
    u16 vAPF2;
    u16 mLSAME;
    u16 mRSAME;
    u16 mLCOMB1;
    u16 mRCOMB1;
    u16 mLCOMB2;
    u16 mRCOMB2;
    u16 dLSAME;
    u16 dRSAME;
    u16 mLDIFF;
    u16 mRDIFF;
    u16 mLCOMB3;
    u16 mRCOMB3;
    u16 mLCOMB4;
    u16 mRCOMB4;
    u16 dLDIFF;
    u16 dRDIFF;
    u16 mLAPF1;
    u16 mRAPF1;
    u16 mLAPF2;
    u16 mRAPF2;
    u16 vLIN;
    u16 vRIN;
};

struct rev_param_entry _spu_rev_param[1];

long SpuSetReverbModeParam(SpuReverbAttr* attr) {
    // skipping this for now
    return 0;
}

long ResetRCnt(long spec) { return 1; }

void* InterruptCallback(u8 a, void (*b)() ) { return 0; }

long GetVideoMode(void) { return 0; }

struct SndSeqTickEnv _snd_seq_tick_env;

s32 D_8003355C;

typedef union {
    struct {
        s16 rest : 15;
        s16 msb : 1;
    } part;
    s16 all;
} Bits;

void SpuSetCommonAttr(SpuCommonAttr* attr) {
    s16 mvol_right;
    s16 temp_a3;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 mvol_left_temp_2;
    s16 main_vol_right_temp;
    s32 attr_mask_zero;
    s32 mvol_mode_left;
    s32 mvol_mode_right;
    Bits main_vol_left;
    s16 main_vol_right;
    u16 mvol_left_temp;
    u16 mvol_right_temp;
    u32 attr_mask;

    mvol_left_temp = 0;
    attr_mask = attr->mask;
    attr_mask_zero = attr_mask == 0;
    mvol_right_temp = 0;

    if (attr_mask_zero != 0 || attr_mask & 1) {
        if (attr_mask_zero != 0 || attr_mask & 4) {
            temp_v1 = attr->mvolmode.left;
            switch (temp_v1) { /* switch 1 */
            case 1:            /* switch 1 */
                mvol_mode_left = 0x8000;
                break;
            case 2: /* switch 1 */
                mvol_mode_left = 0x9000;
                break;
            case 3: /* switch 1 */
                mvol_mode_left = 0xA000;
                break;
            case 4: /* switch 1 */
                mvol_mode_left = 0xB000;
                break;
            case 5: /* switch 1 */
                mvol_mode_left = 0xC000;
                break;
            case 6: /* switch 1 */
                mvol_mode_left = 0xD000;
                break;
            case 7: /* switch 1 */
                mvol_mode_left = 0xE000;
                break;
            case 0:
            default: /* switch 1 */
                mvol_left_temp = attr->mvol.left;
                mvol_mode_left = 0;
                break;
            }
        } else {
            mvol_left_temp = attr->mvol.left;
            mvol_mode_left = 0;
        }
        main_vol_left.part.rest = mvol_left_temp;
        if (mvol_mode_left != 0) {
            temp_a3 = attr->mvol.left;
            if (temp_a3 >= 0x80) {
                mvol_left_temp_2 = 0x7F;
            } else {
                mvol_left_temp_2 = temp_a3;
                if (temp_a3 < 0) {
                    mvol_left_temp_2 = 0;
                }
            }
            main_vol_left.part.rest = mvol_left_temp_2;
        }
#if 0
        _spu_RXX->rxx.main_vol.left = main_vol_left.all | mvol_mode_left;
#else
        write_16(0x1F801D80, main_vol_left.all | mvol_mode_left, __FILE__, __LINE__);
#endif
    }

    if (attr_mask_zero != 0 || attr_mask & 2) {
        if (attr_mask_zero != 0 || attr_mask & 8) {
            temp_v1_2 = attr->mvolmode.right;
            switch (temp_v1_2) { /* switch 2 */
            case 1:              /* switch 2 */
                mvol_mode_right = 0x8000;
                break;
            case 2: /* switch 2 */
                mvol_mode_right = 0x9000;
                break;
            case 3: /* switch 2 */
                mvol_mode_right = 0xA000;
                break;
            case 4: /* switch 2 */
                mvol_mode_right = 0xB000;
                break;
            case 5: /* switch 2 */
                mvol_mode_right = 0xC000;
                break;
            case 6: /* switch 2 */
                mvol_mode_right = 0xD000;
                break;
            case 7: /* switch 2 */
                mvol_mode_right = 0xE000;
                break;
            case 0:
            default: /* switch 2 */
                mvol_right_temp = attr->mvol.right;
                mvol_mode_right = 0;
                break;
            }
        } else {
            mvol_right_temp = attr->mvol.right;
            mvol_mode_right = 0;
        }
        main_vol_right = mvol_right_temp & 0x7FFF;
        if (mvol_mode_right != 0) {
            mvol_right = attr->mvol.right;
            if (mvol_right >= 0x80) {
                main_vol_right_temp = 0x7F;
            } else {
                main_vol_right_temp = mvol_right;
                if (mvol_right < 0) {
                    main_vol_right_temp = 0;
                }
            }
            main_vol_right = main_vol_right_temp & 0x7FFF;
        }
#if 0
        _spu_RXX->rxx.main_vol.right = main_vol_right | mvol_mode_right;
#else
        write_16(0x1F801D82,  main_vol_right | mvol_mode_right, __FILE__, __LINE__);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x40)) {
#if 0
        _spu_RXX->rxx.cd_vol.left = attr->cd.volume.left;
#else
        write_16(0x1F801DB0, attr->cd.volume.left, __FILE__, __LINE__);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x80)) {
#if 0
        _spu_RXX->rxx.cd_vol.right = attr->cd.volume.right;
#else
        write_16(0x1F801DB2, attr->cd.volume.right, __FILE__, __LINE__);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            // _spu_RXX->rxx.spucnt &= 0xFFFB;
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) & 0xFFFB, __FILE__, __LINE__);
        } else {
            #if 0
            _spu_RXX->rxx.spucnt = _spu_RXX->rxx.spucnt | 4;
            #else
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) | 4, __FILE__, __LINE__);
            #endif
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x200)) {
        if (attr->cd.mix == 0) {
            #if 0
            _spu_RXX->rxx.spucnt &= 0xFFFE;
            #else
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) & 0xFFFE, __FILE__, __LINE__);
            #endif
        } else {
#if 0
            _spu_RXX->rxx.spucnt |= 1;
#else
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) | 1, __FILE__, __LINE__);

#endif
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x400)) {
        // _spu_RXX->rxx.ex_vol.left = attr->ext.volume.left;
        write_16(0x1F801DB4,  attr->ext.volume.left, __FILE__, __LINE__);
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x800)) {
        // _spu_RXX->rxx.ex_vol.right = attr->ext.volume.right;
        write_16(0x1F801DB6, attr->ext.volume.right, __FILE__, __LINE__);
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            // _spu_RXX->rxx.spucnt &= 0xFFF7;
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) & 0xFFF7, __FILE__, __LINE__);
        } else {
                        write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) | 8, __FILE__, __LINE__);

            // _spu_RXX->rxx.spucnt |= 8;
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            // _spu_RXX->rxx.spucnt &= 0xFFFD;
                        write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) & 0xFFFD, __FILE__, __LINE__);

        } else {
            // _spu_RXX->rxx.spucnt |= 2;
            write_16(0x1F801DAA, read_16(0x1F801DAA, __FILE__, __LINE__) | 2, __FILE__, __LINE__);
        }
    }
}

s32 _spu_AllocBlockNum;
s32 _spu_AllocLastNum;
s32 _spu_mem_mode_unitM;
s32 _spu_rev_offsetaddr;
s32 _spu_rev_reserve_wa;

// long SpuMalloc(long size) {
//     assert(false);
//     return 0;
// }

void func_800286E0(void);

#define _spu_AllocBlockNum D_8003355C

void _spu_gcSPU() {
     func_800286E0();
}

    long SpuMalloc(long size)
    {
        long pAllocated;

        printf("SpuMalloc size %d\n", size);
        unsigned int rev_size_zero = 0;
        if (_spu_rev_reserve_wa)
        {
            rev_size_zero = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
        }
        else
        {
            rev_size_zero = 0;
        }

        int size_adjusted = size;
        if ((size & ~_spu_mem_mode_unitM) != 0)
        {
            size_adjusted = size + _spu_mem_mode_unitM;
        }

        const u32 calc_alloc_size = size_adjusted >> _spu_mem_mode_plus << _spu_mem_mode_plus;

        printf("memlist is:\n");
        for(int i = 0; i < 32; i++)
        {
            printf("_spu_memList[%d].addr %08X size %08X\n", i, _spu_memList[i].addr, _spu_memList[i].size);
        }
        
        int found_block_idx = -1;
        if ((_spu_memList->addr & 0x40000000) != 0)
        {
            found_block_idx = 0;
        }
        else
        {
            printf("! _spu_memList->addr & 0x40000000 _spu_AllocBlockNum %d\n", _spu_AllocBlockNum);
            _spu_gcSPU();

            if (_spu_AllocBlockNum > 0)
            {
                s32 cur_idx = 0;
                SPU_MALLOC* pListIter = _spu_memList;
                while ((pListIter->addr & 0x40000000) == 0 && ((pListIter->addr & 0x80000000) == 0 || pListIter->size < calc_alloc_size))
                {
                    printf("next block\n");
                    ++cur_idx;
                    ++pListIter;
                    if (cur_idx >= _spu_AllocBlockNum)
                    {
                        goto out_of_blocks;
                    }
                }
                found_block_idx = cur_idx;
            }
        }

    out_of_blocks:
        pAllocated = -1;

        printf("found_block_idx %d\n", found_block_idx);

        if (found_block_idx != -1)
        {
            printf("SpuMalloc:%d\n", __LINE__);

            if ((_spu_memList[found_block_idx].addr & 0x40000000) != 0)
            {
                            printf("SpuMalloc:%d _spu_AllocBlockNum %d\n", __LINE__, _spu_AllocBlockNum);

                if (found_block_idx < (int)_spu_AllocBlockNum)
                {
                                printf("SpuMalloc:%d\n", __LINE__);

                    if (_spu_memList[found_block_idx].size - rev_size_zero >= calc_alloc_size)
                    {
                                    printf("SpuMalloc:%d\n", __LINE__);

                        _spu_AllocLastNum = found_block_idx + 1;

                        SPU_MALLOC* pLastBlock = &_spu_memList[_spu_AllocLastNum];
                        pLastBlock->addr = ((_spu_memList[found_block_idx].addr & 0xFFFFFFF) + calc_alloc_size) | 0x40000000;
                        pLastBlock->size = _spu_memList[found_block_idx].size - calc_alloc_size;

                        _spu_memList[found_block_idx].size = calc_alloc_size;
                        _spu_memList[found_block_idx].addr &= 0xFFFFFFF;

                        _spu_gcSPU();

                        pAllocated = _spu_memList[found_block_idx].addr;
                    }
                }
            }
            else
            {
                            printf("SpuMalloc:%d\n", __LINE__);

                if (calc_alloc_size < _spu_memList[found_block_idx].size)
                {
                                printf("SpuMalloc:%d\n", __LINE__);

                    const u32 pAllocEndAddr = _spu_memList[found_block_idx].addr + calc_alloc_size;
                    if (_spu_AllocLastNum < _spu_AllocBlockNum)
                    {
                                    printf("SpuMalloc:%d\n", __LINE__);

                        const u32 last_addr = _spu_memList[_spu_AllocLastNum].addr;
                        const u32 last_alloc_size = _spu_memList[_spu_AllocLastNum].size;

                        _spu_memList[_spu_AllocLastNum].addr = pAllocEndAddr | 0x80000000;
                        _spu_memList[_spu_AllocLastNum].size = _spu_memList[found_block_idx].size - calc_alloc_size;
                        
                        _spu_AllocLastNum++;
                        _spu_memList[_spu_AllocLastNum].addr = last_addr;
                        _spu_memList[_spu_AllocLastNum].size = last_alloc_size;
                    }
                }

                _spu_memList[found_block_idx].size = calc_alloc_size;
                _spu_memList[found_block_idx].addr &= 0xFFFFFFF;

                _spu_gcSPU();

                pAllocated = _spu_memList[found_block_idx].addr;
            }

        }
        return pAllocated;
    }

#define AddBytes(T, ptr, bytes) (unsigned char *)(ptr) + bytes

// s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr) {
    int SsVabOpenHeadWithMode(unsigned char *pAddr, int vabId, s32 pFn, long mode)
    {
        int vagLens[256]; // max vags
#if 1
        if (_spu_getInTransfer() == 1)
        {
            // Already uploading to SPU
            printf("Already xfter in progress\n");
            assert(false);
            return -1;
        }
#endif
        _spu_setInTransfer(1);
        if (vabId < 16)
        {
            if (vabId == -1)
            {
                // Find a free vabId
                vabId = 16; // set to not found
                for (int i = 0; i < 16; i++)
                {
                    if (_svm_vab_used[i] == 0)
                    {
                        _svm_vab_used[i] = 1;
                        _svm_vab_count++;
                        vabId = i;
                        printf("alloc vabid %d\n", vabId);
                        break;
                    }
                }
            }
            else
            {
                // Use the given vabId
                if (_svm_vab_used[vabId] == 0)
                {
                    _svm_vab_used[vabId] = 1;
                    _svm_vab_count++;
                }
                else
                {
                    vabId = 0; // TODO: check
                }
            }

            if (vabId < 16)
            {
                VabHdr *pHeader = (VabHdr *)pAddr;

                _svm_vab_vh[vabId] = pHeader;
                // _svm_vab_not_send_size = 0;
                if ((pHeader->form >> 8) == 0x564142) // check for VAB magic marker
                {
                    int maxPrograms = 64; // old versions had 64 progs only?
                    if ((pHeader->form & 0xff) == 'p' && pHeader->ver >= 4)
                    {
                        printf(">= v4 VAB\n");
                        maxPrograms = 128;
                    }
                    else
                    {
                        printf("Old style VAB\n");
                    }

                    int progCount = maxPrograms;
                    if (pHeader->ps > progCount)
                    {
                        // too many progs in header
                        printf("VAB header program count too high\n");
                        _svm_vab_used[vabId] = 0;
                    }
                    else
                    {
                        _svm_vab_pg[vabId] = AddBytes(struct ProgAtr, pAddr, sizeof(VabHdr));

                        printf("adding sizeof(VabHdr) %d\n", sizeof(VabHdr));

                        _svm_vab_tn[vabId] = AddBytes(VagAtr, _svm_vab_pg[vabId], progCount * sizeof(struct ProgAtr)); // 128 program attributes

                        printf("adding  progCount * sizeof(struct ProgAtr) %d\n",  progCount * sizeof(struct ProgAtr));

                        printf("prior: %d\n", _svm_vab_tn[vabId]->prior);
                        printf("mode: %d\n", _svm_vab_tn[vabId]->mode);
                        printf("vol: %d\n", _svm_vab_tn[vabId]->vol);

                        printf("pHeader->ps %d\n", pHeader->ps );
                        assert(sizeof(VagAtr) == 32);

                        printf("adding vagoff %d\n", 16 * pHeader->ps * sizeof(struct VagAtr)); 

                        u32 off_progs = 0 + 0x20;
                        u32 off_tone_attrs = off_progs + (16 * 128);
                        u32 off_vag_offsets = off_tone_attrs + (32 * 16 * pHeader->ps);

                        unsigned short *pVagOffTable = pAddr + off_vag_offsets; //AddBytes(unsigned short, _svm_vab_tn[vabId], 16 * pHeader->ps * sizeof(struct VagAtr)); // 16 tones per program

                        printf("diff %d\n", (size_t)pVagOffTable - (size_t)pAddr);
                        unsigned int fakeProgIdx = 0;
                        ProgAtr *pProgTable = _svm_vab_pg[vabId];
                        for (int i = 0; i < progCount; i++)
                        {
                            pProgTable[i].reserved1 = fakeProgIdx;
                            if (pProgTable[i].tones != 0)
                            {
                                fakeProgIdx++;
                            }
                        }

                        unsigned int totalVagsSize = 0;
                        for (int i = 0; i < 256; i++)
                        {
                            if (i <= pHeader->vs) // vag count
                            {
                                if (pHeader->ver >= 4)
                                {
                                    vagLens[i] = pVagOffTable[i] << 3;
                                    printf("%d pVagOffTable[] %d vagLens[] = %d\n", i, pVagOffTable[i], vagLens[i]);
                                }
                                else
                                {
                                    vagLens[i] = pVagOffTable[i] << 2; // TODO: Why is this bit needed?
                                }
                                totalVagsSize += vagLens[i]; // calc total vag size
                            }
                        }

                        printf(" pHeader->vs %d\n",  pHeader->vs);

                        const unsigned int roundedSize = totalVagsSize + 63 & ~63; // Round to multiple of 64
                        long spuAllocMem  = SpuMalloc(totalVagsSize);

                        if (spuAllocMem == -1)
                        {
                            printf("Spu alloc failed size 0x%X id %d\n", roundedSize, vabId); // 0x1C5FC0
                            exit(1);
                            assert(false);
                            return -1;
                        }

                        if (spuAllocMem + roundedSize <= 0x80000) // less than spu ram size ??
                        {
                            _svm_vab_start[vabId] = spuAllocMem;
                            int vagIdx = 0;
                            int totalVagSize = 0;
                            pProgTable = _svm_vab_pg[vabId];

                            do
                            {
                                totalVagSize += vagLens[vagIdx]; // incremental total
                                // 256 vags, but 128 progs, so alternate the storage
                                if ((vagIdx & 1) == 0)
                                {
                                    pProgTable[vagIdx / 2].reserved2 = (spuAllocMem + totalVagSize) >> 3;
                                }
                                else
                                {
                                    pProgTable[vagIdx / 2].reserved3 = (spuAllocMem + totalVagSize) >> 3;
                                }

                                vagIdx++; // vag counter
                            } while (vagIdx <= pHeader->vs);

                            _svm_vab_total[vabId] = totalVagSize;
                            _svm_vab_used[vabId] = 2;
                            printf("OK!\n");
                            return vabId;
                        }

                        printf("Bigger than spu ram\n");
                        _svm_vab_used[vabId] = 0;
                    }
                }
                else
                {
                    // bad file magic
                    printf("Bad file magic\n");
                    _svm_vab_used[vabId] = 0;
                }

                _spu_setInTransfer(0);
                _svm_vab_count--;
                assert(false);
                return -1;
            }
        }
        _spu_setInTransfer(0);
        assert(false);
        return -1;
    }

// void func_800286E0(void) {}

void func_800286E0(void)
{
    int last_alloc_idx;           // $v0
    int counter;                  // $t1
    SPU_MALLOC *pMemList;         // $t0
    int last_alloc_idx_;          // $t5
    SPU_MALLOC *pMemList_Iter;    // $a3
    int list_idx;                 // $a2
    SPU_MALLOC *pCurBlock;        // $v1
    bool bIsntMagicAddr;          // dc
    SPU_MALLOC *pCurBlock_;       // $a1
    int counter_;                 // $t1
    SPU_MALLOC *pMemList__;       // $v1
    int last_alloc_idx__;         // $v1
    int counter__;                // $t1
    SPU_MALLOC *pMemList___;      // $t5
    SPU_MALLOC *pMemListIter_;    // $t2
    int counter_next;             // $a2
    int last_alloc_idx___;        // $t3
    SPU_MALLOC *pNextBlock_;      // $a0
    int mem_addr;                 // $a3
    int mem_size;                 // $v1
    int last_alloc_idx____;       // $a1
    int idx;                      // $t1
    SPU_MALLOC *pMemListIter;     // $a0
    SPU_MALLOC *pCurBlock__;      // $v0
    SPU_MALLOC *pPrevBlock;       // $a0

    last_alloc_idx = _spu_AllocLastNum;
    counter = 0;
    if (_spu_AllocLastNum >= 0)
    {
        pMemList = _spu_memList;
        last_alloc_idx_ = _spu_AllocLastNum;
        pMemList_Iter = _spu_memList;
        do
        {
            list_idx = counter + 1;
            if ((pMemList_Iter->addr & 0x80000000) == 0)
            {
                goto next_item;
            }

            pCurBlock = &pMemList[list_idx];
            while (1)
            {
                bIsntMagicAddr = pCurBlock->addr != 0x2FFFFFFF;
                ++pCurBlock;
                if (bIsntMagicAddr)
                {
                    break;
                }
                ++list_idx;
            }
            pCurBlock_ = &pMemList[list_idx];
            if ((pCurBlock_->addr & 0x80000000) != 0 && (pCurBlock_->addr & 0xFFFFFFF) == (pMemList_Iter->addr & 0xFFFFFFF) + pMemList_Iter->size)
            {
                pCurBlock_->addr = 0x2FFFFFFF;
                pMemList_Iter->size += pCurBlock_->size;
            }
            else
            {
            next_item:
                ++pMemList_Iter;
                ++counter;
            }
        } while (last_alloc_idx_ >= counter);
        last_alloc_idx = _spu_AllocLastNum;
    }

    counter_ = 0;
    if (last_alloc_idx >= 0)
    {
        pMemList__ = _spu_memList;
        do
        {
            if (!pMemList__->size)
            {
                pMemList__->addr = 0x2FFFFFFF;
            }
            ++counter_;
            ++pMemList__;
        } while (last_alloc_idx >= counter_);
    }

    last_alloc_idx__ = _spu_AllocLastNum;
    counter__ = 0;
    if (_spu_AllocLastNum >= 0)
    {
        pMemList___ = _spu_memList;
        pMemListIter_ = _spu_memList;
        do
        {
            if ((pMemListIter_->addr & 0x40000000) != 0)
            {
                break;
            }
            counter_next = counter__ + 1;
            if (last_alloc_idx__ >= counter__ + 1)
            {
                last_alloc_idx___ = _spu_AllocLastNum;
                pNextBlock_ = &pMemList___[counter__ + 1];
                do
                {
                    if ((pNextBlock_->addr & 0x40000000) != 0)
                    {
                        break;
                    }

                    mem_addr = pMemListIter_->addr;
                    if ((pNextBlock_->addr & 0xFFFFFFFu) < (pMemListIter_->addr & 0xFFFFFFFu))
                    {
                        pMemListIter_->addr = pNextBlock_->addr;
                        mem_size = pMemListIter_->size;
                        pMemListIter_->size = pNextBlock_->size;
                        pNextBlock_->addr = mem_addr;
                        pNextBlock_->size = mem_size;
                    }
                    ++counter_next;
                    ++pNextBlock_;
                } while (last_alloc_idx___ >= counter_next);
            }
            last_alloc_idx__ = _spu_AllocLastNum;
            ++counter__;
            ++pMemListIter_;
        } while (_spu_AllocLastNum >= counter__);
    }

    last_alloc_idx____ = _spu_AllocLastNum;
    idx = 0;
    if (_spu_AllocLastNum >= 0)
    {
        pMemListIter = _spu_memList;
        while ((pMemListIter->addr & 0x40000000) == 0) // not last entry
        {
            if (pMemListIter->addr == 0x2FFFFFFF)
            {
                pCurBlock__ = &_spu_memList[last_alloc_idx____];
                pMemListIter->addr = pCurBlock__->addr;
                pMemListIter->size = pCurBlock__->size;
                _spu_AllocLastNum = idx;
                break;
            }
            last_alloc_idx____ = _spu_AllocLastNum;
            ++idx;
            ++pMemListIter;
            if (_spu_AllocLastNum < idx)
            {
                break;
            }
        }
    }

    // Merged tail unused blocks
    if (_spu_AllocLastNum - 1 >= 0)
    {
        pPrevBlock = &_spu_memList[_spu_AllocLastNum - 1];
        do
        {
            if ((pPrevBlock->addr & 0x80000000) == 0)
            {
                break;
            }
            // Found unused block, merge it and set as last entry
            pPrevBlock->addr = pPrevBlock->addr & 0xFFFFFFF | 0x40000000;
            pPrevBlock->size += _spu_memList[_spu_AllocLastNum].size;
            _spu_AllocLastNum--;
            pPrevBlock--;
        } while (_spu_AllocLastNum >= 0);
    }
}


u16 _spu_tsa;
void (* volatile _spu_transferCallback)();

s32 _spu_mem_mode;
s32 _spu_mem_mode_unit;
s32 _spu_mem_mode_unitM;

s32* D_80033508;
s32* D_8003350C;
s32* D_80033510;
s32* D_80033518;
s32 D_80033550;
s32 D_800334FC;
s32* D_80033514;
u16 D_80033540[] = {
    0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707, 0x0707,
};
s32 _spu_addrMode;

void (* volatile _spu_IRQCallback)();

void DeliverEvent(unsigned long a, unsigned long b) {}

s32 D_800330F8[256] = {0};
s32 D_80033558;
volatile u32* D_80033554;

void write_dma(u32 data, char* file, int line);

// dma function, reimplement to avoid pulling in dma controller
int _spu_t(int mode, ...) {
    va_list args;
    va_start(args, mode);
    s32 spu_ram_dest_addr;
    u32* source_address;
    s32 count;
    s32 i;

    switch (mode) {
    case 0:
    case 1:
        write_16(0x1F801DAA, (read_16(0x1F801DAA) & ~0x30) | 0x20, __FILE__,
                 __LINE__);
        return 0;

    case 2:
        // set destination address
        spu_ram_dest_addr = va_arg(args, u32) >> _spu_mem_mode_plus;
        _spu_tsa = spu_ram_dest_addr;

        // dma destination address in spu ram
        write_16(0x1f801da6, spu_ram_dest_addr, __FILE__, __LINE__);
        return 0;

    case 3:
        // transfer
        source_address = (u32*)va_arg(args, u32*);
        count = (s32)va_arg(args, s32);
        for (i = 0; i < count / 4; i++) {
            write_dma(source_address[i], __FILE__, __LINE__);
        }
        return 0;
        break;
    }

    assert(false);
    return 0;
}

void _SsSndCrescendo(s16 a , s16 b) { assert(false); }
void _SsSndDecrescendo(s16 a , s16 b) { assert(false); }

void SpuVmSetVol(
    short seq_sep_no, short vabId, short program, short voll, short volr) {
    assert(false);
}

void _SsContDataEntry(s16 a, s16 b, u8 c) { assert(false); }

#endif
