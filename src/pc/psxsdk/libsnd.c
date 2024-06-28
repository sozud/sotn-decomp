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

// u16 D_80032F14[1];
unsigned short D_80032F14[] = {
    0x1000, 0x100E, 0x101D, 0x102C, 0x103B, 0x104A, 0x1059, 0x1068,
    0x1078, 0x1087, 0x1096, 0x10A5, 0x10B5, 0x10C4, 0x10D4, 0x10E3,
    0x10F3, 0x1103, 0x1113, 0x1122, 0x1132, 0x1142, 0x1152, 0x1162,
    0x1172, 0x1182, 0x1193, 0x11A3, 0x11B3, 0x11C4, 0x11D4, 0x11E5,
    0x11F5, 0x1206, 0x1216, 0x1227, 0x1238, 0x1249, 0x125A, 0x126B,
    0x127C, 0x128D, 0x129E, 0x12AF, 0x12C1, 0x12D2, 0x12E3, 0x12F5,
    0x1306, 0x1318, 0x132A, 0x133C, 0x134D, 0x135F, 0x1371, 0x1383,
    0x1395, 0x13A7, 0x13BA, 0x13CC, 0x13DE, 0x13F1, 0x1403, 0x1416,
    0x1428, 0x143B, 0x144E, 0x1460, 0x1473, 0x1486, 0x1499, 0x14AC,
    0x14BF, 0x14D3, 0x14E6, 0x14F9, 0x150D, 0x1520, 0x1534, 0x1547,
    0x155B, 0x156F, 0x1583, 0x1597, 0x15AB, 0x15BF, 0x15D3, 0x15E7,
    0x15FB, 0x1610, 0x1624, 0x1638, 0x164D, 0x1662, 0x1676, 0x168B,
    0x16A0, 0x16B5, 0x16CA, 0x16DF, 0x16F4, 0x170A, 0x171F, 0x1734,
    0x174A, 0x175F, 0x1775, 0x178B, 0x17A1, 0x17B6, 0x17CC, 0x17E2,
    0x17F9, 0x180F, 0x1825, 0x183B, 0x1852, 0x1868, 0x187F, 0x1896};
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

// void SpuVmKeyOn(s16 a , s16 b , u8 c , s32 d , s32 e , s32 f) { 


//  }
s32 SpuVmKeyOn(s16 arg0, s16 vab_id, s16 program, s16 midi_key, u16 vol1, u16 vol2) {
    // ? sp10;
    // ? sp90;
    VagAtr* temp_a0;
    VagAtr* svm_tn;
    s16 alloc_voice;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a2;
    u8 var_s1;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    s8 var_a1;
    struct SeqStruct* temp_s0;
    u32 temp_v0_3;
    ProgAtr* temp_v0;
    u8 pad[0x100-0x8];

    var_s2 = 0;
    temp_s0 = &_ss_score[arg0 & 0xFF][(arg0 >> 8) & 0xff];
    var_v0 = -1;
    if (SpuVmVSetUp(vab_id, program) == 0) {
        _svm_cur.field_16_vag_idx = arg0;
        _svm_cur.field_2_note = midi_key;
        _svm_cur.field_0x3 = 0;
        var_v0_2 = program;
        if (arg0 == 0x21) {
            _svm_cur.field_4_voll = (s8) vol1;
        } else {
            _svm_cur.field_4_voll = (vol1 * temp_s0->vol[temp_s0->channel]) / 127;
            var_v0_2 = program ;
        }
        temp_a2 = var_v0_2;
        _svm_cur.field_0x5 = (s8) vol2;
        temp_v0 = &_svm_pg[temp_a2];//(temp_a2 * 0x10) + _svm_pg;
        _svm_cur.field_A_mvol = temp_v0->mvol;
        _svm_cur.field_B_mpan = temp_v0->mpan;
        _svm_cur.field_0_sep_sep_no_tonecount = temp_v0->tones;
        var_v0 = -1;
        if (_svm_cur.field_7_fake_program < _svm_vh->ps) {
            var_a1 = 0;
            if (vol1 == 0) {
                var_s2 = SpuVmKeyOff(arg0, vab_id, temp_a2, midi_key & 0xFFFF);
            } else {
                var_a2 = 0;
                if (_svm_cur.field_0_sep_sep_no_tonecount != 0) {
                    do {
                        // temp_a0 = &_svm_tn[(_svm_cur.field_7_fake_program * 0x10) + (var_a1 & 0xFF)];
                        // if ((u8) _svm_cur.field_2_note >= (u8) temp_a0->min) {
                        //     temp_v0_2 = var_a2 & 0xFF;
                        //     if ((u8) temp_a0->max >= (u8) _svm_cur.field_2_note) {
                        //         temp_v1 = var_a2;
                        //         var_a2 += 1;
                        //         // *(&sp10 + temp_v0_2) = temp_a0->unk16;
                        //         // *(&sp90 + (temp_v1 & 0xFF)) = var_a1;
                        //     }
                        // }
                        var_a1 += 1;
                    } while ((u32) (var_a1 & 0xFF) < (u8) _svm_cur.field_0_sep_sep_no_tonecount);
                }
                #if 0
                temp_v0_3 = var_a2 & 0xFF;
                var_s1 = 0;
                if (temp_v0_3 != 0) {
                    do {
                        _svm_cur.vag = temp_s0->unk10;
                        _svm_cur.field_C_vag_idx = temp_s0->unk90;
                        svm_tn = &_svm_tn[_svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10)];
                        _svm_cur.field_F_prior = (u8) svm_tn->prior;
                        _svm_cur.vol = svm_tn->vol;
                        _svm_cur.pan = svm_tn->pan;
                        _svm_cur.center = svm_tn->center;
                        _svm_cur.shift = svm_tn->shift;
                        _svm_cur.mode =  svm_tn->mode;
                        _svm_cur.min =  svm_tn->min;
                        _svm_cur.max = svm_tn->max;
                        alloc_voice = SpuVmAlloc(0U) & 0xFF;
                        _svm_cur.field_18_voice_idx = alloc_voice;
                        if (alloc_voice < (s32) spuVmMaxVoice) {
                            _svm_voice[alloc_voice].unk1b = 1;
                            _svm_voice[_svm_cur.field_18_voice_idx].unk2 = 0;
                            _svm_voice[_svm_cur.field_18_voice_idx].unke = arg0;                            
                            _svm_voice[_svm_cur.field_18_voice_idx].vabId = _svm_cur.field_1_vabId;                                                        
                            _svm_voice[_svm_cur.field_18_voice_idx].unk10 = _svm_cur.field_7_fake_program;                                                        
                            _svm_voice[_svm_cur.field_18_voice_idx].prog = program;                                                                                    

                            if (arg0 != 0x21) {
                                _svm_voice[_svm_cur.field_18_voice_idx].unk8 = vol1;                                                                                    
                            }

                            _svm_voice[_svm_cur.field_18_voice_idx].unka = vol2;                                                                                    
                            _svm_voice[_svm_cur.field_18_voice_idx].tone = _svm_cur.field_C_vag_idx;                                                                                    
                            _svm_voice[_svm_cur.field_18_voice_idx].note = midi_key;       
                            _svm_voice[_svm_cur.field_18_voice_idx].unk18 = _svm_cur.field_F_prior;                                                                                    
                            _svm_voice[_svm_cur.field_18_voice_idx].unk0 =  _svm_cur.vag;
                            SpuVmDoAllocate(alloc_voice);
                            if (_svm_cur.vag == 0xFF) {
                                vmNoiseOn(_svm_cur.field_0x1a);
                            } else {
                                SpuVmKeyOnNow(temp_v0_3 & 0xFF, note2pitch() & 0xFFFF);
                            }
                            var_s2 |= 1 << (s16) _svm_cur.field_18_voice_idx;
                        } else {
                            var_s2 = -1;
                        }
                        var_s1 += 1;
                    } while ((u32) (var_s1 & 0xFF) < temp_v0_3);
                }
                #else
                temp_v0_3 = var_a2;
                for(var_s1 = 0; var_s1 < temp_v0_3; var_s1++)
                {
                    // _svm_cur.vag = temp_s0->unk10;
                    _svm_cur.field_C_vag_idx = temp_s0->unk90;
                    svm_tn = &_svm_tn[_svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10)];
                    _svm_cur.field_F_prior = (u8) svm_tn->prior;
                    // _svm_cur.vol = svm_tn->vol;
                    // _svm_cur.pan = svm_tn->pan;
                    // _svm_cur.center = svm_tn->center;
                    // _svm_cur.shift = svm_tn->shift;
                    // _svm_cur.mode =  svm_tn->mode;
                    // _svm_cur.min =  svm_tn->min;
                    // _svm_cur.max = svm_tn->max;
                    alloc_voice = SpuVmAlloc(0U) & 0xFF;
                    _svm_cur.field_18_voice_idx = alloc_voice;
                    if (alloc_voice < (s32) spuVmMaxVoice) {
                        _svm_voice[alloc_voice].unk1b = 1;
                        _svm_voice[_svm_cur.field_18_voice_idx].unk2 = 0;
                        _svm_voice[_svm_cur.field_18_voice_idx].unke = arg0;                            
                        _svm_voice[_svm_cur.field_18_voice_idx].vabId = _svm_cur.field_1_vabId;                                                        
                        _svm_voice[_svm_cur.field_18_voice_idx].unk10 = _svm_cur.field_7_fake_program;                                                        
                        _svm_voice[_svm_cur.field_18_voice_idx].prog = program;                                                                                    

                        if (arg0 != 0x21) {
                            _svm_voice[_svm_cur.field_18_voice_idx].unk8 = vol1;                                                                                    
                        }

                        _svm_voice[_svm_cur.field_18_voice_idx].unka = vol2;                                                                                    
                        _svm_voice[_svm_cur.field_18_voice_idx].tone = _svm_cur.field_C_vag_idx;                                                                                    
                        _svm_voice[_svm_cur.field_18_voice_idx].note = midi_key;       
                        _svm_voice[_svm_cur.field_18_voice_idx].unk18 = _svm_cur.field_F_prior;                                                                                    
                        // _svm_voice[_svm_cur.field_18_voice_idx].unk0 =  _svm_cur.vag;
                        SpuVmDoAllocate(alloc_voice);
                        // if (_svm_cur.vag == 0xFF) {
                        //     vmNoiseOn(_svm_cur.field_0x1a);
                        // } else {
                            SpuVmKeyOnNow(temp_v0_3 & 0xFF, note2pitch() & 0xFFFF);
                        // }
                        var_s2 |= 1 << (s16) _svm_cur.field_18_voice_idx;
                    } else {
                        var_s2 = -1;
                    }
                }
                #endif
            }
            var_v0 = var_s2;
        }
    }
    return var_v0;
}

s32 _svm_envx_hist[32];
s32 D_8003BD08 = 0;

// void SpuVmFlush(void) {assert(false);}

void SpuVmFlush(void) {
    printf("SpuVmFlush\n");
    s32 var_s0;
    u32 env_mask;
    u16 _svm_okof2_temp;
    u16 _svm_okon1_temp;
    u16 _svm_okon2_temp;
    u16 _svm_okof1_temp;
    s32 i;
    s32 i2;

    s16 * temp;
    s32 * hist;
    s32 max;
    s16 temp2;
    s16* reg_ptr;
    char* sreg;
    max = spuVmMaxVoice;

    hist = &_svm_envx_hist;
    var_s0 = 0;
    D_8003BD08 = (D_8003BD08 + 1) & 0xF;
    hist[D_8003BD08] = 0;
    #if 0
    if ((s32) spuVmMaxVoice > 0) {
        var_a0 = &_svm_voice_06;
        var_a1 = D_80032F10;
        do {
            *var_a0 = var_a1[0xc/2];
            var_a0 += 0x34;
            if (*var_a0 == 0) {
                *temp_v0_2 |= 1 << var_s0;
            }
            var_s0 += 1;
            var_a1 += 0x10;
        } while (var_s0 < (s32) spuVmMaxVoice);
    }
    #else
    for(i = 0; i < max; i++)
    {
        temp = &_svm_voice[i].unk6;
#if 0
        temp2 = D_80032F10[i * 8 + 6];
#else
        temp2 = read_16(0x1F801C00 + i * 8 + 6, __FILE__, __LINE__);
#endif
        *temp = temp2;
        if(temp2 == 0)
        {
            hist[i] |= 1 << i;
        }
    }
    #endif
    i = 0;
    if (_svm_auto_kof_mode == 0) {
        env_mask = 0xFFFFFFFF;
        for(i = 0; i < 0xf; i++)
        {
            env_mask &= _svm_envx_hist[i];
        }

        for(i = 0; i < spuVmMaxVoice; i++)
        {
            if (env_mask & (1 << i)) {
                if (_svm_voice[i].unk1b == 2) {
                    SpuSetNoiseVoice(0, 0xFFFFFF);
                }
                _svm_voice[i].unk1b  = 0;
            }                
        }
    }
    
    _svm_okon1 &= ~_svm_okof1;
    _svm_okon2 &= ~_svm_okof2;
    for(i = 0; i < 24; i++)
    {
        // if (_svm_voice[i].auto_vol  != 0) {
        //     SetAutoVol(i);
        // }
        // if (_svm_voice[i].auto_pan != 0) {
        //     SetAutoPan(i);
        // }
    }
    
    i2 = 0;
    sreg = &_svm_sreg_dirty[0];
    do {        
        if (*sreg & 1) {
            write_16(0x1F801C00 + i2 * 0x10 + 0, _svm_sreg_buf.raw[i2 * 8 + 0], __FILE__, __LINE__);
            write_16(0x1F801C00 + i2 * 0x10 + 1, _svm_sreg_buf.raw[i2 * 8 + 1], __FILE__, __LINE__);

            // D_80032F10[i2 * 8 + 0] = _svm_sreg_buf.raw[i2 * 8 + 0];
            // D_80032F10[i2 * 8 + 1] = _svm_sreg_buf.raw[i2 * 8 + 1];

        }
        if (*sreg & 4) {
            // D_80032F10[i2 * 8 + 2] = _svm_sreg_buf.raw[i2 * 8 + 2];
            write_16(0x1F801C00 + i2 * 0x10 + 2, _svm_sreg_buf.raw[i2 * 8 + 2], __FILE__, __LINE__);
        }
        if (*sreg & 8) {
            // D_80032F10[i2 * 8 + 3] =   _svm_sreg_buf.raw[i2 * 8 + 3];
            write_16(0x1F801C00 + i2 * 0x10 + 3, _svm_sreg_buf.raw[i2 * 8 + 3], __FILE__, __LINE__);
        }
        if (*sreg & 0x10) {
            write_16(0x1F801C00 + i2 * 0x10 + 4, _svm_sreg_buf.raw[i2 * 8 + 4], __FILE__, __LINE__);
            write_16(0x1F801C00 + i2 * 0x10 + 5, _svm_sreg_buf.raw[i2 * 8 + 5], __FILE__, __LINE__);
            // D_80032F10[i2 * 8 + 4] = _svm_sreg_buf.raw[i2 * 8 + 4];
            // D_80032F10[i2 * 8 + 5] = _svm_sreg_buf.raw[i2 * 8 + 5];
        }
        *sreg = 0;
        sreg++;
        i2++;
    } while (sreg < &_svm_sreg_dirty[24]);

    reg_ptr = D_80032F10; // 0x1F801C00
    _svm_okof1_temp = _svm_okof1;
    _svm_okof2_temp = _svm_okof2;
    _svm_okon1_temp = _svm_okon1;
    _svm_okon2_temp = _svm_okon2;
    _svm_okof1 = 0;
    _svm_okof2 = 0;
    _svm_okon1 = 0;
    _svm_okon2 = 0;

    printf("hello\n");
#if 0
    reg_ptr[0x18c/2] = _svm_okof1_temp;
    reg_ptr[0x18e/2] = _svm_okof2_temp;
    reg_ptr[0x188/2] = _svm_okon1_temp;
    reg_ptr[0x18a/2] = _svm_okon2_temp;
    reg_ptr[0x198/2] = _svm_orev1;
    reg_ptr[0x19a/2] = _svm_orev2;
#else
    write_16(0x1F801C00 + 0x18c, _svm_okof1_temp, __FILE__, __LINE__);
    write_16(0x1F801C00 + 0x18e, _svm_okof2_temp, __FILE__, __LINE__);
    write_16(0x1F801C00 + 0x188, _svm_okon1_temp, __FILE__, __LINE__);
    write_16(0x1F801C00 + 0x18a, _svm_okon2_temp, __FILE__, __LINE__);
    write_16(0x1F801C00 + 0x198, _svm_orev1, __FILE__, __LINE__);
    write_16(0x1F801C00 + 0x19a, _svm_orev2, __FILE__, __LINE__);
#endif
}


// void SpuVmKeyOnNow(short vagCount, short pitch) { assert(0); }
void SpuVmKeyOnNow(short vagCount, short pitch)
{
  unsigned short bitsLower = 0;
  short new_var;
  unsigned short bitsUpper;
  struct SeqStruct *pSeq;
  u32 right;
  u32 uVar1;
  u32 left;
  u16 pos;
  s32 mvol;
  s32 temp1;
  s16 a1;
  short ptemp;
  a1 = _svm_cur.field_0x1a;
  ptemp = pitch;
  a1 *= 8;
  mvol = _svm_vh->mvol * 0x3fff;
  temp1 = (_svm_cur.field_4_voll * mvol) / 0x3f01;
  left = temp1;
  uVar1 = ((left * _svm_cur.field_A_mvol) * _svm_cur.field_D_vol) / 0x3f01;
  left = uVar1;
  right = uVar1;
  pSeq = &_ss_score[_svm_cur.field_16_vag_idx & 0xff][(_svm_cur.field_16_vag_idx & 0xff00) >> 8];
  if (_svm_cur.field_16_vag_idx != 0x21)
  {
    left = (uVar1 * pSeq->unk74) / 127;
    right = (uVar1 * pSeq->unk76) / 127;
  }
  if (_svm_cur.field_E_pan < 64)
  {
    right = (right * _svm_cur.field_E_pan) / 63;
  }
  else
  {
    left = (left * (127 - _svm_cur.field_E_pan)) / 63;
  }
  if (_svm_cur.field_B_mpan < 64)
  {
    right = (right * _svm_cur.field_B_mpan) / 63;
  }
  else
  {
    left = (left * (127 - _svm_cur.field_B_mpan)) / 63;
  }
  if (_svm_cur.field_0x5 < 64)
  {
    right = (right * _svm_cur.field_0x5) / 63;
  }
  else
  {
    left = (left * (127 - _svm_cur.field_0x5)) / 63;
  }
  new_var = ptemp;
  if (_svm_stereo_mono == 1)
  {
    if (left < right)
    {
      left = right;
    }
    else
    {
      right = left;
    }
  }
  {
    left = (left * left) / 0x3fff;
    right = (right * right) / 0x3fff;
  }
  pos = a1;
  _svm_sreg_buf.raw[pos + 2] = new_var;
  _svm_sreg_buf.raw[pos + 0] = left;

#if 0
  // real version
  _svm_sreg_buf.raw[pos + 1] = right;
#else
  // wrong but slightly more matching (permuter)
  bitsUpper = right;
  _svm_sreg_buf.raw[pos + 1] = right;
#endif
  _svm_sreg_dirty[_svm_cur.field_0x1a] |= 7;
  _svm_voice[_svm_cur.field_0x1a].unk04 = new_var;
  _svm_voice[_svm_cur.field_0x1a].unk1b = 1;
  if (_svm_cur.field_0x1a < 0x10)
  {
    bitsLower = 1 << _svm_cur.field_0x1a;
    bitsUpper = 0;
  }
  else
  {
    bitsLower = 0;
    bitsUpper = 1 << (_svm_cur.field_0x1a - 0x10);
  }
  if (_svm_cur.field_14_seq_sep_no & 4)
  {
    _svm_orev1 |= bitsLower;
    _svm_orev2 |= bitsUpper;
  }
  else
  {
    _svm_orev1 &= ~bitsLower;
    _svm_orev2 &= ~bitsUpper;
  }
  _svm_okon1 = bitsLower | _svm_okon1;
  _svm_okon2 = bitsUpper | _svm_okon2;
  _svm_okof1 = _svm_okof1 & (~_svm_okon1);
  _svm_okof2 = _svm_okof2 & (~_svm_okon2);
}


void vmNoiseOn(s32 arg0) { assert(0); }

// void SpuVmDoAllocate(void) { assert(0); }

void SpuVmDoAllocate(void) {
    s32 hist_pos;
    u16 var_v0;
    s16 temp;
    struct thing * svm;
    
    _svm_cur.unk1c.a = _svm_cur.field_0x1a * 8;
    _svm_cur.unk1c.b =  _svm_cur.field_C_vag_idx + ( _svm_cur.field_7_fake_program * 0x10);
    _svm_voice[ _svm_cur.field_0x1a].unk6 = 0x7FFF;

    for(hist_pos = 0; hist_pos < 0x10; hist_pos++)
    {
        _svm_envx_hist[hist_pos]  &= ~(1 << _svm_cur.field_0x1a);
    }
    if (( _svm_cur.field_18_voice_idx & 1) > 0) {
        _svm_sreg_buf.raw[_svm_cur.unk1c.a + 3] = _svm_pg[ (_svm_cur.field_18_voice_idx - 1) / 2].reserved2;
    } else {
        _svm_sreg_buf.raw[_svm_cur.unk1c.a + 3] = _svm_pg[(_svm_cur.field_18_voice_idx - 1) / 2].reserved3;
    }
    svm = &_svm_cur.unk1c;
    _svm_sreg_dirty[_svm_cur.field_0x1a] |= 8;
    _svm_sreg_buf.raw[svm->a + 4] = _svm_tn[(_svm_cur.field_7_fake_program * 0x10) +  _svm_cur.field_C_vag_idx].adsr1;
    _svm_sreg_buf.raw[svm->a + 5] = _svm_tn[(_svm_cur.field_7_fake_program * 0x10) +  _svm_cur.field_C_vag_idx].adsr2 + _svm_damper;
    _svm_sreg_dirty[_svm_cur.field_0x1a] = _svm_sreg_dirty[_svm_cur.field_0x1a] | 0x30;
}

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

// void SpuVmSetVol(
//     short seq_sep_no, short vabId, short program, short voll, short volr) {
//     // assert(false);
// }

    void SpuVmSetVol(short seq_sep_no, short vabId, short program, short voll, short volr)
    {
        struct VagAtr *vagAtr;
        struct SpuVoice *voice;
        struct SeqStruct *pSeq = &_ss_score[seq_sep_no & 0xff][(seq_sep_no & 0xff00) >> 8];
        SpuVmVSetUp(vabId, program);

        if (volr == 0)
        {
            volr = 1;
        }

        if (voll == 0)
        {
            voll = 1;
        }

        _svm_cur.field_14_seq_sep_no = seq_sep_no;

        for (int i = 0; i < spuVmMaxVoice; i++)
        {
            voice = &_svm_voice[i];
            if (//(_snd_vmask & 1 << (i & 31)) == 0 &&
                voice->unke == seq_sep_no &&
                voice->prog == program &&
                voice->vabId == vabId)
            {
                if ((pSeq->vol[pSeq->channel] != voll) && (pSeq->vol[pSeq->channel] == 0))
                {
                    pSeq->vol[pSeq->channel] = 1;
                }

                vagAtr = &_svm_tn[(voice->prog * 16) + voice->vabId];
                int v1 = ((voice->unk8 * voll / 127) * _svm_vh->mvol * 0x3fff) / 0x3f01;
                v1 = (v1 * _svm_pg[program].mvol * vagAtr->vol) / 0x3f01;

                const int vagPan = vagAtr->pan;

                assert(0);

                int left = 127;//(v1 * pSeq->voll) / 127;
                int right = 127;//(v1 * pSeq->volr) / 127;

                if (vagPan < 64)
                {
                    right = (right * vagPan) / 63;
                }
                else
                {
                    left = (left * (127 - vagPan)) / 63;
                }

                const int progPan = _svm_pg[_svm_voice[seq_sep_no].prog].mpan;
                if (progPan < 64)
                {
                    right = (right * progPan) / 63;
                }
                else
                {
                    left = (left * (127 - progPan)) / 63;
                }

                int tmp = volr & 0xff;
                if (tmp < 64)
                {
                    right = (right * tmp) / 63;
                }
                else
                {
                    left = (left * (127 - tmp)) / 63;
                }

                if (_svm_stereo_mono == 1)
                {
                    if (left < right)
                    {
                        left = right;
                    }
                    right = left;
                }

                _svm_sreg_buf.buf[i].field_0_vol_left = (short)((left * left) / 0x3fff);
                _svm_sreg_buf.buf[i].field_2_vol_right = (short)((right * right) / 0x3fff);
                _svm_sreg_dirty[i] |= 3;
            }
        }
    }
    
void _SsContDataEntry(s16 a, s16 b, u8 c) { 
    // assert(false); 
    }


#endif
