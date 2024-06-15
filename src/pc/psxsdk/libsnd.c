#include <common.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include <log.h>
#include <assert.h>
// #include "../../main/psxsdk/libsnd/libsnd_i.h"

#define NUM_SPU_CHANNELS 24

struct SpuVoice {
    s16 unk0;
    s16 unk2;
    s16 unk04;
    u16 unk6;
    s16 unk8;
    char unka;
    char unkb;
    s16 note; /* 0xC */
    s16 unke;
    s16 unk10;
    s16 prog;  /* 0x12 */
    s16 tone;  /* 0x14*/
    s16 vabId; /* 0x16 */
    s16 unk18;
    u8 pad4[1];
    u8 unk1b;
    s16 auto_vol; /* 0x1c */
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 start_vol; /* 0x24 */
    s16 end_vol;   /* 0x26 */
    s16 auto_pan;  /* 0x28 */
    s16 unk2a;
    s16 unk2c;
    s16 unk2e;
    s16 start_pan; /* 0x30 */
    s16 end_pan;   /* 0x32 */
};

u16* D_80032F10;

struct SpuVoice _svm_voice[NUM_SPU_CHANNELS];

void WaitEvent(s32)
{

}

struct RegBufStruct {
    short field_0_vol_left;
    short field_2_vol_right;
    short field_4_pitch;
    unsigned short field_6_vagAddr;
    unsigned short field_8_adsr1;
    unsigned short field_A_adsr2;
    short field_0xc;
    short field_0xe;
};

union RegBuf {
    struct RegBufStruct buf[NUM_SPU_CHANNELS];
    s16 raw[192];
};

union RegBuf _svm_sreg_buf;

unsigned char _svm_sreg_dirty[NUM_SPU_CHANNELS];

unsigned short _svm_okon1;
unsigned short _svm_okon2;
unsigned short _svm_okof1;
unsigned short _svm_okof2;

typedef struct VabHdr {         /* VAB Bank Headdings */

	s32           form;          /* always 'VABp' */
	s32           ver;           /* VAB file version number */
	s32           id;            /* VAB id */
	u32  fsize;         /* VAB file size */
	unsigned short reserved0;     /* system reserved */
	unsigned short ps;            /* # of the programs in this bank */
	unsigned short ts;            /* # of the tones in this bank */
	unsigned short vs;            /* # of the vags in this bank */
	unsigned char  mvol;          /* master volume for this bank */
	unsigned char  pan;           /* master panning for this bank */
	unsigned char  attr1;         /* bank attributes1 */
	unsigned char  attr2;         /* bank attributes2 */
	u32  reserved1;     /* system reserved */

} VabHdr;			/* 32 byte */


typedef struct ProgAtr {        /* Program Headdings */

	unsigned char tones;          /* # of tones */
	unsigned char mvol;           /* program volume */
	unsigned char prior;          /* program priority */
	unsigned char mode;           /* program mode */
	unsigned char mpan;           /* program pan */
	char          reserved0;      /* system reserved */
	short         attr;           /* program attribute */
	u32 reserved1;      /* system reserved */
        u16 reserved2;      // even vag spu ptr
        u16 reserved3;      // odd vag spu ptr
} ProgAtr;			/* 16 byte */



typedef struct VagAtr {         /* VAG Tone Headdings */

	unsigned char  prior;         /* tone priority */
	unsigned char  mode;          /* play mode */
	unsigned char  vol;           /* tone volume*/
	unsigned char  pan;           /* tone panning */
	unsigned char  center;        /* center note */
	unsigned char  shift;         /* center note fine tune */
	unsigned char  min;           /* minimam note limit */
	unsigned char  max;           /* maximam note limit */
	unsigned char  vibW;          /* vibrate depth */
	unsigned char  vibT;          /* vibrate duration */
	unsigned char  porW;          /* portamento depth */
	unsigned char  porT;          /* portamento duration */
	unsigned char  pbmin;         /* under pitch bend max */
	unsigned char  pbmax;         /* upper pitch bend max */
	unsigned char  reserved1;     /* system reserved */
	unsigned char  reserved2;     /* system reserved */
	unsigned short adsr1;         /* adsr1 */
	unsigned short adsr2;         /* adsr2 */
	short          prog;          /* parent program*/
	short          vag;           /* vag reference */
	short          reserved[4];   /* system reserved */

} VagAtr;			/* 32 byte */


struct struct_svm {
    char field_0_sep_sep_no_tonecount;
    char field_1_vabId;
    char field_2_note;
    char field_0x3;
    char field_4_voll;
    char field_0x5;
    char field_6_program;
    char field_7_fake_program;
    char field_8_unknown;
    char field_0x9;
    char field_A_mvol;
    char field_B_mpan;
    char field_C_vag_idx;
    char field_D_vol;
    char field_E_pan;
    char field_F_prior;
    char field_10_centre;
    unsigned char field_11_shift;
    char field_12_mode;
    char field_0x13;
    short field_14_seq_sep_no;
    short field_16_vag_idx;
    short field_18_voice_idx;
    short field_0x1a;
    char pad_0x1c[0x4];
};


s32 _svm_brr_start_addr[16]; /* number: 10 */
s16 _svm_stereo_mono;        /* number: 11 */
SpuReverbAttr _svm_rattr;    /* number: 12 */
u8 _svm_vab_used[16] = {0};        /* number: 13 */
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

int ResetCallback(void) { return 0; }

typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);

SndSsMarkCallbackProc _SsMarkCallback[32][16]; /* #11 */
struct SeqStruct* _ss_score[32];               /* #12 */
s32 VBLANK_MINUS;                              /* #13 */
s32 _snd_openflag;                             /* #14 */
s16 _snd_seq_s_max;                            /* #15 */
s16 _snd_seq_t_max;                            /* #16 */
s32 _snd_ev_flag;                              /* #17 */


long _spu_transMode;

void* DMACallback(int dma, void (*func)()) {
    return NULL;
}

s32 _spu_rev_startaddr[4];
s32 D_80033098;

// s_ini.c
s32 _spu_fd = 0;
long _spu_trans_mode = 0;
s32 _spu_rev_flag = 0;
s32 _spu_rev_reserve_wa = 0;
s32 _spu_rev_offsetaddr = 0;
// struct SpuRevAttr {
//     s32 unk0;
//     s32 unk18;
//     s16 unk1c;
//     s16 unk1e;
//     s32 unk20;
//     s32 unk24;
// };

// typedef struct {
//     unsigned long	mask;	  /* �ݒ�}�X�N		  */
    
//     long		mode;	  /* ���o�[�u���[�h       */
//     SpuVolume		depth;	  /* ���o�[�u�̐[��	  */
//     long                delay;	  /* Delay Time (ECHO, DELAY �̂�)  */
//     long                feedback; /* Feedback   (ECHO �̂�)         */
// } SpuReverbAttr;


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

u16 D_80032F14[];
s32 _spu_AllocBlockNum;
s32 D_80033560;
s8* D_80033564;
s32 _spu_mem_mode_plus;
// s8* _spu_memList;


typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

// SPU_MALLOC ** _spu_memList;
SPU_MALLOC *_spu_memList=NULL;

s32 _spu_inTransfer;
struct _ss_spu_vm_rec_struct {
    u32 pad[2];
    SPU_MALLOC D_8003BD50[364];
};


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

typedef struct tagSpuVoiceRegister {
    SpuVolume volume; // 0-2
    u16 pitch;        // 4
    u16 addr;         // 6
    u16 adsr[2];      // 8-A
    u16 volumex;      // C
    u16 loop_addr;    // E
} SPU_VOICE_REG;      // 16 bytes

typedef struct tagSpuControl {
    SPU_VOICE_REG voice[24];
    SpuVolume main_vol; // 180
    SpuVolume rev_vol;  // 184
    // bit flags
    u16 key_on[2];       // 188
    u16 key_off[2];      // 18C
    u16 chan_fm[2];      // 190
    u16 noise_mode[2];   // 194
    u16 rev_mode[2];     // 198
    u32 chan_on;         // 19C
    u16 unk;             // 1A0
    u16 rev_work_addr;   // 1A2
    u16 irq_addr;        // 1A4
    u16 trans_addr;      // 1A6
    u16 trans_fifo;      // 1A8
    u16 spucnt;          // 1AA SPUCNT
    u16 data_trans;      // 1AC
    u16 spustat;         // 1AE SPUSTAT
    SpuVolume cd_vol;    // 1B0
    SpuVolume ex_vol;    // 1B4
    SpuVolume main_volx; // 1B8
    SpuVolume unk_vol;   // 1BC

    u16 dAPF1; // Starting at 0x1F801DC0
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
} SPU_RXX;

union SpuUnion {
    SPU_RXX rxxnv;
    volatile SPU_RXX rxx;
    volatile u16 raw[0x100];
};
short D_80032EC0[] = {0x0000, 0x0000,0x1000,0x3000, 0x00BF, 0x0000,0x0000, 0x0000};
union SpuUnion* _spu_RXX;

u16 D_80032ED0[] = {
    0x3FFF,
    0x3FFF,
    0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000 
};

struct _ss_spu_vm_rec_struct _ss_spu_vm_rec;

// short SsUtSetVVol(short vc, short voll, short volr) {
//     assert(0);
//     return 0;
// }

 s16 _svm_orev1;
 s16 _svm_orev2;

 void SpuVmKeyOn(s16, s16, u8, s32, s32, s32) {
    assert(0);
 }

// void SpuVmFlush()
// {
// assert(0);
// }

s32 _svm_envx_hist[32];
s32 D_8003BD08 = 0;



void SpuVmFlush(void) {
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
            D_80032F10[i2 * 8 + 0] = _svm_sreg_buf.raw[i2 * 8 + 0];
            D_80032F10[i2 * 8 + 1] = _svm_sreg_buf.raw[i2 * 8 + 1];

        }
        if (*sreg & 4) {
            D_80032F10[i2 * 8 + 2] = _svm_sreg_buf.raw[i2 * 8 + 2];
        }
        if (*sreg & 8) {
            D_80032F10[i2 * 8 + 3] =   _svm_sreg_buf.raw[i2 * 8 + 3];
        }
        if (*sreg & 0x10) {
            D_80032F10[i2 * 8 + 4] = _svm_sreg_buf.raw[i2 * 8 + 4];
            D_80032F10[i2 * 8 + 5] = _svm_sreg_buf.raw[i2 * 8 + 5];
        }
        *sreg = 0;
        sreg++;
        i2++;
    } while (sreg < &_svm_sreg_dirty[24]);

    reg_ptr = D_80032F10;
    _svm_okof1_temp = _svm_okof1;
    _svm_okof2_temp = _svm_okof2;
    _svm_okon1_temp = _svm_okon1;
    _svm_okon2_temp = _svm_okon2;
    _svm_okof1 = 0;
    _svm_okof2 = 0;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
#if 0
    reg_ptr[0x18c/2] = _svm_okof1_temp;
    reg_ptr[0x18e/2] = _svm_okof2_temp;
    reg_ptr[0x188/2] = _svm_okon1_temp;
    reg_ptr[0x18a/2] = _svm_okon2_temp;
    reg_ptr[0x198/2] = _svm_orev1;
    reg_ptr[0x19a/2] = _svm_orev2;
#else
    write_16(0x1F801C00 + 0x18c, _svm_okof1_temp);
    write_16(0x1F801C00 + 0x18e, _svm_okof2_temp);
    write_16(0x1F801C00 + 0x188, _svm_okon1_temp);
    write_16(0x1F801C00 + 0x18a, _svm_okon2_temp);
    write_16(0x1F801C00 + 0x198, _svm_orev1);
    write_16(0x1F801C00 + 0x19a, _svm_orev2);
#endif
}

void SpuVmKeyOnNow(short vagCount, short pitch)
{
assert(0);
}

void vmNoiseOn(s32 arg0) {
assert(0);
}

void SpuVmDoAllocate(void) {
    assert(0);
}

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    assert(0);
    NOT_IMPLEMENTED;
}

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { 
    assert(0);
    NOT_IMPLEMENTED; }

short SsSeqOpen(u_long* addr, short vab_id) {
    assert(0);
    NOT_IMPLEMENTED;
    return 0;
}

void SsSeqClose(short seq_access_num) { 
    assert(0);
    NOT_IMPLEMENTED; }

// long SpuSetReverbModeParam(SpuReverbAttr* attr)
// {
// assert(0);
// }

// struct rev_param_entry {
//     u32 flags;
//     u16 dAPF1;
//     u16 dAPF2;
//     u16 vIIR;
//     u16 vCOMB1;
//     u16 vCOMB2;
//     u16 vCOMB3;
//     u16 vCOMB4;
//     u16 vWALL;
//     u16 vAPF1;
//     u16 vAPF2;
//     u16 mLSAME;
//     u16 mRSAME;
//     u16 mLCOMB1;
//     u16 mRCOMB1;
//     u16 mLCOMB2;
//     u16 mRCOMB2;
//     u16 dLSAME;
//     u16 dRSAME;
//     u16 mLDIFF;
//     u16 mRDIFF;
//     u16 mLCOMB3;
//     u16 mRCOMB3;
//     u16 mLCOMB4;
//     u16 mRCOMB4;
//     u16 dLDIFF;
//     u16 dRDIFF;
//     u16 mLAPF1;
//     u16 mRAPF1;
//     u16 mLAPF2;
//     u16 mRAPF2;
//     u16 vLIN;
//     u16 vRIN;
// };

struct rev_param_entry _spu_rev_param[1];


long SpuSetReverbModeParam(SpuReverbAttr* attr) {
    struct rev_param_entry entry;
    s32 do_clear;
    s32 temp_a0;
    s32 temp_s5;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_fp;
    s32 var_s0;
    s32 var_s4;
    s32 var_s6;
    s32 reverb_master_enable;
    s32 var_v0;
    u8* var_a1_2;
    u8* var_a1_3;
    u8* var_a2;
    u32 temp_s3;
    u8* var_v1;
    u8* var_v1_2;
    u8* var_v1_3;
    u8 pad[2];

    printf("skipping SpuSetReverbModeParam\n");
    return;

    entry.flags = 0;

    reverb_master_enable = 0;
    var_s4 = 0;
    var_s6 = 0;
    do_clear = 0;
    temp_s3 = attr->mask;
    var_fp = 0;
    temp_s5 = temp_s3 == 0;
    // sp10 = 0;
    if ((temp_s5 != 0) || (temp_s3 & 1)) {
        var_s0 = attr->mode;
        if (var_s0 & 0x100) {
            var_s0 &= ~0x100;
            do_clear = 1;
        }
        if (((u32) var_s0 >= 0xAU) || ( (_SpuIsInAllocateArea_(_spu_rev_startaddr[var_s0]) != 0))) {
            return -1;
        }
        var_s4 = 1,
        var_a2 = &entry;
        var_a1 = 0x43;
        _spu_rev_attr.mode = (u32) var_s0;
        var_v1 = &_spu_rev_param[_spu_rev_attr.mode];
        _spu_rev_offsetaddr = _spu_rev_startaddr[_spu_rev_attr.mode];
        do {
            *var_a2++ = *var_v1++;
            var_a1--;
        } while (var_a1 != -1);
        switch (_spu_rev_attr.mode) {                       /* irregular */
        case 7:
            _spu_rev_attr.feedback = 0x7F;
            _spu_rev_attr.delay  = 0x7F;
            break;
        case 8:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 0x7F;
            break;
        default:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 0;
            break;
        }
        goto block_15;
    }
block_15:
    if ((temp_s5 != 0) || (temp_s3 & 8)) {
        if (((s32) _spu_rev_attr.mode < 9) && ((s32) _spu_rev_attr.mode >= 7)) {
            var_s6 = 1;
            if (var_s4 == 0) {
                var_a1_2 = &entry;
                var_a0 = 0x43;
                var_v1_2 = &_spu_rev_param[_spu_rev_attr.mode];
                do {
                    *var_a1_2++ =  *var_v1_2++;
                    var_a0 -= 1;
                } while (var_a0 != -1);
                entry.flags = 0x0C011C00;
            }
            temp_a0 = attr->delay;
            _spu_rev_attr.delay = temp_a0;

            entry.mLSAME = (temp_a0 << 0xd) / 127 - entry.dAPF1;
            temp_v1 = (temp_a0 << 0xC) / 127;
            entry.mRSAME = temp_v1 - entry.dAPF2;
            entry.dLSAME = entry.dRSAME + temp_v1;
            entry.mLCOMB1 = entry.mRCOMB1 + temp_v1;
            entry.mRAPF1 = entry.mRAPF2 + temp_v1;
            entry.mLAPF1 = entry.mLAPF2 + temp_v1;
        } else {
            _spu_rev_attr.delay = 0;
        }
    }
    if ((temp_s5 != 0) || (temp_s3 & 0x10)) {
        if (((s32)   _spu_rev_attr.mode < 9) && (_spu_rev_attr.mode >= 7)) {
            var_fp = 1;
            if (var_s4 == 0) {
                var_a1_3 = &entry;
                if (var_s6 == 0) {
                    var_a0_2 = 0x43;
                    var_v1_3 =  &_spu_rev_param[_spu_rev_attr.mode];
                    do {
                        *var_a1_3++ = *var_v1_3++;
                        var_a0_2 -= 1;
                    } while (var_a0_2 != -1);
                    var_v0 = 0x80;
                } else {
                    var_v0 = entry.flags | 0x80;
                }
                entry.flags = var_v0;
            }
            temp_v0_4 = attr->feedback;
              _spu_rev_attr.feedback = temp_v0_4;
            entry.vWALL = (temp_v0_4 * 0x8100) / 127;
        } else {
            _spu_rev_attr.feedback = 0;
        }
    }
    if (var_s4 != 0) {
        //   7     Reverb Master Enable    (0=Disabled, 1=Enabled)
        reverb_master_enable = ((u16) _spu_RXX->rxx.spucnt >> 7) & 1;
        if (reverb_master_enable != 0) {
            _spu_RXX->rxx.spucnt &= 0xFF7F;
        }
        // _spu_RXX->rxx.rev_vol.left = 0;
        // _spu_RXX->rxx.rev_vol.right = 0;
        // D_800330B4 = 0;
        // D_800330B6 = 0;
    } else {
        if ((temp_s5 != 0) || (temp_s3 & 2)) {
            _spu_RXX->rxx.rev_vol.left = (s16) (u16) attr->depth.left;
            _spu_rev_attr.depth.left = (u16) attr->depth.left;
        }
        if ((temp_s5 != 0) || (temp_s3 & 4)) {
            _spu_RXX->rxx.rev_vol.right = (s16) (u16) attr->depth.right;
            _spu_rev_attr.depth.right  = (u16) attr->depth.right;
        } else {
            _spu_RXX->rxx.rev_vol.left = 0;
            _spu_RXX->rxx.rev_vol.right = 0;
            _spu_rev_attr.depth.left = 0;
            _spu_rev_attr.depth.right = 0;
        }
    }

    if ((var_s4 != 0) || (var_s6 != 0) || (var_fp != 0)) {
        _spu_setReverbAttr(&entry);
    }
    if (do_clear != 0) {
        SpuClearReverbWorkArea((s32) _spu_rev_attr.mode);
    }
    if (var_s4 != 0) {
        _spu_FsetRXX(0xD1, _spu_rev_offsetaddr, 0);
        if (reverb_master_enable != 0) {
            _spu_RXX->rxx.spucnt |= 0x80;
        }
    }
    return 0;
}

struct SndSeqTickEnv {
    s32 unk0;
    s32 unk4;
    void (*unk8)();
    void (*unk12)();
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u32 unk20;
};

long ResetRCnt(long spec) {
    return 1;
}

void InterruptCallback(int irq, void (*f)()) {
}

long GetVideoMode(void) { return 0; }

struct SndSeqTickEnv _snd_seq_tick_env;

typedef struct {
    SpuVolume volume; /* volume       */
    long reverb;      /* reverb on/off */
    long mix;         /* mixing on/off */
} SpuExtAttr;

typedef struct {
    unsigned long mask; /* settings mask */

    SpuVolume mvol;     /* master volume */
    SpuVolume mvolmode; /* master volume mode */
    SpuVolume mvolx;    /* current master volume */
    SpuExtAttr cd;      /* CD input attributes */
    SpuExtAttr ext;     /* external digital input attributes */
} SpuCommonAttr;


// #include "../main/psxsdk/libsnd/libsnd_i.h"

// void SpuSetCommonAttr(SpuCommonAttr* attr)
// {
// assert(0);
// }
typedef union {
    struct {
        int16_t rest : 15;
        int16_t msb : 1;
    } part;
    int16_t all;
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
        write_16(0x180, main_vol_left.all | mvol_mode_left);
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
        write_16(0x182,  main_vol_right | mvol_mode_right);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x40)) {
#if 0
        _spu_RXX->rxx.cd_vol.left = attr->cd.volume.left;
#else
        write_16(0x1B0, attr->cd.volume.left);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x80)) {
#if 0
        _spu_RXX->rxx.cd_vol.right = attr->cd.volume.right;
#else
        write_16(0x1B2, attr->cd.volume.right);
#endif
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            _spu_RXX->rxx.spucnt &= 0xFFFB;
        } else {
            _spu_RXX->rxx.spucnt = _spu_RXX->rxx.spucnt | 4;
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x200)) {
        if (attr->cd.mix == 0) {
            _spu_RXX->rxx.spucnt &= 0xFFFE;
        } else {
#if 0
            _spu_RXX->rxx.spucnt |= 1;
#else
            u16 temp = read_16(0x1aa, __FILE__, __LINE__);
            temp |= 1;
            write_16(0x1aa, temp);
#endif
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x400)) {
        _spu_RXX->rxx.ex_vol.left = attr->ext.volume.left;
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x800)) {
        _spu_RXX->rxx.ex_vol.right = attr->ext.volume.right;
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            _spu_RXX->rxx.spucnt &= 0xFFF7;
        } else {
            _spu_RXX->rxx.spucnt |= 8;
        }
    }
    if ((attr_mask_zero != 0) || (attr_mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            _spu_RXX->rxx.spucnt &= 0xFFFD;
        } else {
            _spu_RXX->rxx.spucnt |= 2;
        }
    }
}

s32 _spu_AllocBlockNum;
s32 _spu_AllocLastNum;
s32 _spu_mem_mode_plus;
s32 _spu_mem_mode_unitM;
s32 _spu_rev_offsetaddr;
s32 _spu_rev_reserve_wa;

#define _spu_gcSPU func_800286E0

#if 0
s32 SpuMalloc(s32 arg0) {
    s32 last_blocknum;
    s32 size_temp;
    s32 addr_temp;
    s32 cur_blocknum;
    s32 var_a0;
    s32 block_count;
    s32 var_s3;
    s32 var_v0;
    u32 temp_s1;
    u32 cur_size;
    SPU_MALLOC* temp_a2;
    SPU_MALLOC* last_block;
    SPU_MALLOC* temp_v1_3;
    SPU_MALLOC* temp_v1_4;
    SPU_MALLOC* cur_memlist;
    u32 mask4;
    u32 mask8;
    s32 d_temp;
    block_count = 0;
    cur_blocknum = -1;
    if (_spu_rev_reserve_wa == 0) {
        var_s3 = 0;
    } else {
        var_s3 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }
    // var_a0 = arg0;
    if (arg0 & ~_spu_mem_mode_unitM) {
        var_a0 = arg0 + _spu_mem_mode_unitM;
    }
    temp_s1 = (var_a0 >> _spu_mem_mode_plus) << _spu_mem_mode_plus;
    if (_spu_memList[0]->addr & 0x40000000) {
        cur_blocknum = 0;
    } else {
        _spu_gcSPU();
        d_temp = _spu_AllocBlockNum;
#if 1
        if (d_temp > 0) {
            mask4 = 0x40000000;
            mask8 = 0x80000000;
            cur_memlist = _spu_memList[0]->addr;

loop_9:
            if ((cur_memlist->addr & mask4) || ((cur_memlist->addr & mask8) && (cur_memlist->size >= temp_s1))) {
                cur_blocknum = block_count;
            } else {
                block_count += 1;
                cur_memlist += 1;
                if (block_count < d_temp) {
                    goto loop_9;
                }
            }
        }
#else
        for(block_count = 0; block_count < d_temp; block_count++)
        {
            mask4 = 0x40000000;
            mask8 = 0x80000000;
            cur_memlist = _spu_memList[0]->addr;
            if ((cur_memlist->addr & mask4) || ((cur_memlist->addr & mask8) && (cur_memlist->size >= temp_s1))) {
                cur_blocknum = block_count;
                break;
            } else {
                cur_memlist += 1;
                continue;
            }
        }
#endif
    }
    var_v0 = -1;
    if (cur_blocknum != -1) {
        temp_a2 = cur_blocknum + _spu_memList[0];
        if (temp_a2->addr & 0x40000000) {
            var_v0 = -1;
            if (cur_blocknum < _spu_AllocBlockNum) {
                var_v0 = -1;
                if ((temp_a2->size - var_s3) >= temp_s1) {
                    last_blocknum = cur_blocknum + 1;
                    temp_v1_3 = &_spu_memList[0][last_blocknum];
                    temp_v1_3->addr = (s32) (((temp_a2->addr & 0x0FFFFFFF) + temp_s1) | 0x40000000);
                    temp_v1_3->size = (s32) (temp_a2->size - temp_s1);
                    _spu_AllocLastNum = last_blocknum;
                    temp_a2->size = temp_s1;
                    temp_a2->addr = (s32) (temp_a2->addr & 0x0FFFFFFF);
                    _spu_gcSPU();
                    return _spu_memList[0][cur_blocknum].addr;
                } else {
                    return -1;
                }
            }
            /* Duplicate return node #23. Try simplifying control flow for better match */
            return var_v0;
        }
        cur_size = temp_a2->size;
        if ((temp_s1 < cur_size) && (_spu_AllocLastNum < _spu_AllocBlockNum)) {
            last_block = &_spu_memList[0][_spu_AllocLastNum];
            addr_temp = last_block->addr;
            size_temp = last_block->size;
            last_block->addr = ((temp_s1 + temp_a2->addr) | 0x80000000);
            last_block->size = (cur_size - temp_s1);
            _spu_AllocLastNum += 1;
            last_block[1].addr = addr_temp;
            last_block[1].size = size_temp;
        }
        temp_v1_4 = cur_blocknum + _spu_memList[0];
        temp_v1_4->size = temp_s1;
        temp_v1_4->addr = (temp_v1_4->addr & 0x0FFFFFFF);
        _spu_gcSPU();
        var_v0 = _spu_memList[0][cur_blocknum].addr;
    }
    return var_v0;
}
#else
    long SpuMalloc(long size)
    {
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
        
        int found_block_idx = -1;
        if ((_spu_memList->addr & 0x40000000) != 0)
        {
            found_block_idx = 0;
        }
        else
        {
            printf("! _spu_memList->addr & 0x40000000\n");
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
        long pAllocated = -1;

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

#endif

#if 0
s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr) {
    int vagLens[256]; 
    s32 sp410;
    s32 var_a1;
    s16 vabId_2;
    s16 max_programs;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a1_2;
    s32 vagIdx;
    s32 var_s0;
    s32 totalVagsSize;
    s32 totalVagSize;
    s32 var_v0_3;
    s32* temp_a3_2;
    s32* var_a0;
    s32* var_a1_3;
    u16 temp_v1;
    u16* ptr_vag_off_table;
    u32 magic;
    u32 spuAllocMem;
    u32 var_v1_2;
    u8 temp_s4;
    u8* temp_a2;
    ProgAtr* var_v1;
    void* temp_a2_2;
    VabHdr* ptr = addr;
    s32 *pVagOffTable;
    ProgAtr* pProgTable;

    
    s32 vabId;
    s32 i;

    vabId_2 = 0x10;
    // if (_spu_getInTransfer() == 1) {
    //     return -1;
    // }
    _spu_setInTransfer(1);
    
    if (!(vabid < 0x10)) {
        _spu_setInTransfer(0);
        return -1;    
    }

    printf("vabid %d\n", vabid);

    {
        var_a1 = 0;
        if (vabid == -1) {
            for(var_a1 = 0; var_a1 < 16; var_a1++)
            {
                if (_svm_vab_used[var_a1] != 0) {
                    _svm_vab_used[var_a1] = 1;
                    vabId_2 = var_a1;
                    _svm_vab_count += 1;
                    break;
                }
            }
        } else {
            if (_svm_vab_used[vabid] == 0) {
                _svm_vab_used[vabid] = 1;
                vabId_2 = vabid;
                _svm_vab_count += 1;
                printf("found vab %d\n", vabid);
            }
        }

        printf("vabId_2 %d\n", vabId_2);

        if (vabId_2 >= 0x10) {

            for(i = 0; i < 16; i++)
            {
                printf("vab %d\n", _svm_vab_used[i]);
            }
            _spu_setInTransfer(0);
            exit(0);
            return -1;
        }
        _svm_vab_vh[vabId_2] = addr;
        magic = ptr->form;
        printf("magic %08X\n", magic);
        temp_a2 = addr + 0x20;
        if ((magic >> 8) != 0x564142) {
            _svm_vab_used[vabId_2] = 0;
            _spu_setInTransfer(0);
            _svm_vab_count -= 1;
            printf("no magic\n");
                        exit(0);
            return -1;
        }
        max_programs = 0x40;
        if ((magic & 0xFF) == 0x70) {

            max_programs = 0x40;
            // max_programs = ptr->ver >= 5 ? 0x80 : 0x40;
            if (ptr->ver >= 5) {
                max_programs = 0x80;
            }
        }
        kMaxPrograms = max_programs;
        if (kMaxPrograms >= (s32) ptr->ps) 
        {
            _svm_vab_pg[vabId_2] = temp_a2;
            temp_a2_2 = temp_a2 + (kMaxPrograms * 0x10);

            #if 1
            var_a1_2 = 0;
            var_s0 = 0;
            if (kMaxPrograms > 0) {
                var_v1 = temp_a2;
                do {
                    var_v1->reserved1 = var_s0;
                    if (var_v1->tones != 0) {
                        var_s0 += 1;
                    }
                    var_a1_2 += 1;
                    var_v1 += 1;
                } while (var_a1_2 < kMaxPrograms);
            }
            #else
            var_v1 = temp_a2;
            if (kMaxPrograms > 0)
            {
                do
                {
                    var_v1[var_a1_2].reserved1 = var_s0;
                    if (var_v1[var_a1_2].tones != 0) {
                        var_s0 += 1;
                    }  
                     var_a1_2++;
                } while(var_a1_2 < kMaxPrograms);
            }
            #endif
            totalVagsSize = 0;
            var_a1_3 = &vagLens[0];
            _svm_vab_tn[vabId_2] = temp_a2_2;
            ptr_vag_off_table = temp_a2_2 + (ptr->vs << 9);
            temp_s4 = ptr->ps;
            temp_a3_2 = &var_a1_3[temp_s4];
            do {
                if ((s32) temp_a3_2 >= (s32) var_a1_3) {
                    temp_v1 = *ptr_vag_off_table;
                    var_v0_3 = temp_v1 * 4;
                    if (ptr->ver >= 5) {
                        var_v0_3 = temp_v1 * 8;
                    }
                    *var_a1_3 = var_v0_3;
                    totalVagsSize += *var_a1_3;
                }
                var_a1_3 += 1;
                ptr_vag_off_table += 1;
            } while ((s32) var_a1_3 < (s32) &sp410);


            _svm_brr_start_addr[vabId_2] = ptr_vag_off_table;
            spuAllocMem = sbaddr;
            if (arg2 == 0) {
                spuAllocMem = SpuMalloc(totalVagsSize);//, (s32) var_a1_3, ptr_vag_off_table, spuAllocMem);
                var_v1_2 = spuAllocMem + totalVagsSize;
                if (spuAllocMem == -1U) {
                    _svm_vab_used[vabId_2] = 0;
                    _spu_setInTransfer(0);
                    _svm_vab_count -= 1;
                    printf("SpuMalloc fail\n");
                                exit(0);
                    return -1;
                }
            } 
            else {
                var_v1_2 = spuAllocMem + totalVagsSize;
            }
            totalVagSize = 0;
            if (var_v1_2 > 0x80000U) {
                end:
                _svm_vab_used[vabId_2] = 0;
                _spu_setInTransfer(0);
                _svm_vab_count -= 1;
                printf("too big\n");
                            exit(0);
                return -1;
            }
            _svm_vab_start[vabId_2  ] = spuAllocMem;
            for(vagIdx = 0; vagIdx <= temp_s4; vagIdx++)
            {
                totalVagSize += vagLens[vagIdx];
                if (!(vagIdx & 1)) {
                    pProgTable[vagIdx / 2].reserved2 = (spuAllocMem + totalVagSize) >> 3;
                } else {
                    // pProgTable[vagIdx / 2].reserved3 = (spuAllocMem + totalVagSize) >> 3;
                }
            }
            printf("totalVagSize %d\n", totalVagSize);
            _svm_vab_total[vabId_2] = totalVagSize;
            _svm_vab_used[ vabId_2] = 2;
        } else {
            goto end;
        }
    }
    printf("oops\n");
    return 0;
}
#else
#define AddBytes(T, ptr, bytes) (unsigned char *)(ptr) + bytes

// s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr) {
    int SsVabOpenHeadWithMode(unsigned char *pAddr, int vabId, s32 pFn, long mode)
    {
        int vagLens[256]; // max vags
#if 0
        if (_spu_getInTransfer() == 1)
        {
            // Already uploading to SPU
            printf("Already xfter in progress\n");
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

                        _svm_vab_tn[vabId] = AddBytes(VagAtr, _svm_vab_pg[vabId], progCount * sizeof(struct ProgAtr)); // 128 program attributes

                        unsigned short *pVagOffTable = AddBytes(unsigned short, _svm_vab_tn[vabId], 16 * pHeader->ps * sizeof(struct VagAtr)); // 16 tones per program

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
                                }
                                else
                                {
                                    vagLens[i] = pVagOffTable[i] << 2; // TODO: Why is this bit needed?
                                }
                                totalVagsSize += vagLens[i]; // calc total vag size
                            }
                        }

                        const unsigned int roundedSize = totalVagsSize + 63 & ~63; // Round to multiple of 64
                        long spuAllocMem = //(*pFn)(roundedSize, mode, vabId);
                        spuAllocMem = SpuMalloc(totalVagsSize);

                        if (spuAllocMem == -1)
                        {
                            printf("Spu alloc failed size 0x%X id %d\n", roundedSize, vabId); // 0x1C5FC0
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
                return -1;
            }
        }
        _spu_setInTransfer(0);
        return -1;
    }
#endif

void func_800286E0() {
    // assert(0);
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
s32 D_80033540[] = {
     0x07070707,
     0x07070707,
     0x07070707,
     0x07070707
};
 s32 _spu_addrMode;

void (* volatile _spu_IRQCallback)();

void DeliverEvent(unsigned long, unsigned long)
{

}

#include <stdarg.h>
 s32 D_800330F8[128];


// s32 _spu_t(s32, ...)
// {
//     assert(0);
//     return 0;
// }
 s32 D_80033558;
 volatile u32 *D_80033554;

    enum
    {
        SPU_T_SYNC0,
        SPU_T_SYNC,
        SPU_T_SET_TRANS,
        SPU_T_TRANSFER,
    };
int _spu_t(int count, ...)
{
    s32 var_v0_2;
    s32 var_v1_3;
    s32 val;
    int i;
    u32 ck;
    u16 ck2;
    static u32 _spu_tmp = 0, _spu_bcr = 0;
    va_list args;
    s32 * D_80033518_ptr;
    u32 temp;
    u32 temp2;
    // volatile u32 *SPUDMA_MADR2 ;
    va_start(args, count);

    //DEBUGPRINT(("Tsa %d\n", count));

    switch (count)
    {
    case SPU_T_SET_TRANS:
        ck = va_arg(args, u32) >> _spu_mem_mode_plus;
        _spu_tsa = ck;
#if 0
        _spu_RXX->rxx.trans_addr = ck;
#else
        write_16(0x1a6, ck);
#endif
        return 0;

    case SPU_T_SYNC:
        D_80033550 = 0;
#if 0
        if (_spu_RXX->rxx.trans_addr != _spu_tsa)
#else
        if(read_16(0x1a6, __FILE__, __LINE__) != _spu_tsa)
#endif
        {
            i = 0;
            do
            {
                if (i + 1 > 3840) return -2;
                i++;
            } while (_spu_RXX->rxx.trans_addr != _spu_tsa);
        }
#if 0
        _spu_RXX->rxx.spucnt = (_spu_RXX->rxx.spucnt & ~0x30) | 0x20;
#else
        u16 temp = read_16(0x1AA, __FILE__, __LINE__);
        temp = (temp & ~0x30) | 0x20;
        write_16(0x1aa, temp);
#endif
        // SPU_RXX::Set(&_spu_RXX->spucnt, (SPU_RXX::GetU16(&_spu_RXX->spucnt) & ~0x30) | 0x20);
        break;
        return 0;

    case SPU_T_SYNC0:
        D_80033550 = 1;
        if (_spu_RXX->rxx.trans_addr != _spu_tsa)
        {
            i = 0;
            do
            {
                if (i + 1 > 3840) return -2;
                i++;
            } while (_spu_RXX->rxx.trans_addr != _spu_tsa);
        }
        _spu_RXX->rxx.spucnt = _spu_RXX->rxx.spucnt | 0x30;
        break;
        // SPU_RXX::Set(&_spu_RXX->spucnt, SPU_RXX::GetU16(&_spu_RXX->spucnt) | 0x30);
        return 0;

    case SPU_T_TRANSFER:
        // ck2 = D_80033550 ? 0x20 : 0x30;

        if(D_80033550 == 1)
        {
            ck2 = 0x30;
        }
        else {
            ck2 = 0x20;
        }
        // if(_spu_wck != ck)
        // {
        //     ck = 0x20;

        // } 
        // else {
        //     ck = 0x30;

        // }
        // ck = _spu_wck ? 0x30 : 0x20;
        i = 0;

#if 0
        if ((_spu_RXX->rxx.spucnt & 0x30u) != ck2)
#else
        if(read_16(0x1aa, __FILE__, __LINE__) & 0x30u != ck2)
#endif
        {
            do
            {
                if (i + 1 > 3840)
                {
                    //DEBUGPRINT(("T/O transfer %x==%x\n", s->spucnt, ck));
                    return -2;
                }
                i++;

#if 0
            } while ((_spu_RXX->rxx.spucnt & 0x30u) != ck2);
#else
            } while ((read_16(0x1aa, __FILE__, __LINE__) & 0x30u) != ck2);
#endif
        }

        if (D_80033550 == 1) {
#if 0
            var_v0_2 = *D_80033518;  0x1F801014 4    SPU_DELAY   Delay/Size (usually 200931E1h)
#else
            // var_v0_2 = 0x1F801014
#endif
            var_v0_2 &= 0xF0FFFFFF;
            var_v1_3 = 0x22000000;
        } else {
        #if 0
            var_v0_2 = *D_80033518;
        #else
        #endif
            var_v0_2 &= 0xF0FFFFFF;
            var_v1_3 = 0x20000000;
        }
        #if 0
        *D_80033518 = var_v0_2 | var_v1_3;
        #endif
        // *D_80033554 = SPUDMA_MADR;

        temp2 = (u32)va_arg(args, u32);
        #if 0
        *D_80033508 = temp2;   // 0x1F8010C0 "DMA4 MADR
        #endif
        ck = (u32)va_arg(args, u32);
        D_80033558 = (ck / 64) + ((ck % 64) ? 1 : 0);
#if 0
        *D_80033554 = temp2;
        #endif
        #if 0
        *D_8003350C =  (D_80033558 << 16) | 0x10; // 0x1F8010C4 DMA4 BCR 

        if(D_80033550 == 1)
        {
            val = 0x1000200;
        }
        else {
            val = 0x1000201;
        }
        *D_80033510 = val;
        #endif
        break;
    }

    return 0;
}

struct SeqStruct {
    u8 unk0;
    u8 pad1[3];
    u8* read_pos;
    u8* next_sep_pos; /* 0x8 */
    u8* loop_pos;     /* 0xC */
    u8 unk10;
    u8 unk11;
    u8 channel;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 panpot[16];
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2a;
    u8 unk2b;
    u8 programs[16];
    u8 unk3C;
    u8 pad3D;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4a;
    s16 unk4c;
    s16 vol[16];
    s16 unk6E;
    s16 unk70;
    s16 unk72;
    u16 unk74;
    u16 unk76;
    s16 unk78;
    s16 unk7A;
    s32 unk7c;
    u32 unk80;
    s32 unk84;
    s32 delta_value;
    s32 unk8c;
    s32 unk90;
    u32 unk94;
    u32 unk98;
    s32 unk9C;
    s32 unkA0;
    u32 unkA4;
    s16 padA6;
    s16 padaa;
};
void _SsSndCrescendo(s16, s16) {}
void _SsSndDecrescendo(s16, s16) {}
// void _SsSndPause(s16, s16);
// void _SsSndPlay(s16, s16);
// void _SsSndReplay(s16, s16);
// void _SsSndTempo(s16, s16); 

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

void _SsContDataEntry(s16, s16, u8) {}