
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
#if 0


// short D_80032EC0[] = {0x0000, 0x0000,0x1000,0x3000, 0x00BF, 0x0000,0x0000, 0x0000};

// u16 D_80032ED0[] = {
//     0x3FFF,
//     0x3FFF,
//     0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000,0x0000, 0x0000 
// };


// typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);

// extern SndSsMarkCallbackProc _SsMarkCallback[32][16];

// extern s32 VBLANK_MINUS;                              /* #13 */
// extern s32 _snd_openflag;                             /* #14 */
// extern s16 _snd_seq_s_max;                            /* #15 */
// extern s16 _snd_seq_t_max;                            /* #16 */
// extern s32 _snd_ev_flag;                              /* #17 */

// #if 1
// void _SsInitMine(void) {
//     u16* var_a2;
//     int i, j;

// #ifdef VERSION_PC
// int pos = 0;
// #endif

//     var_a2 = (u16*)0x1F801C00;
//     for (i = 0; i < 24; i++) {
//         for (j = 0; j < 8; j++) {
// #ifdef VERSION_PC
//             write_16(0x1F801C00 + pos++, D_80032EC0[j]);
// #else
//             *var_a2++ = D_80032EC0[j];
// #endif
//         }
//     }

//     var_a2 = (u16*)0x1F801D80;
//     for (i = 0; i < 16; i++) {
// #ifdef VERSION_PC
//         write_16(0x1F801D80 + i, D_80032ED0[j]);
// #else
//         *var_a2++ = D_80032ED0[i];
// #endif
//     }

//     SpuVmInit(24);

//     for (j = 0; j < 32; j++) {
//         for (i = 0; i < 16; i++) {
//             _SsMarkCallback[j][i] = 0;
//         }
//     }

//     VBLANK_MINUS = 0x3C;
//     _snd_openflag = 0;
//     _snd_ev_flag = 0;
// }
// #endif
#endif
#define PSX
void PcsxReduxExit(short exitCode)
{
    printf("Exiting with code %d\n", exitCode);
    #ifdef PSX
    (*(volatile unsigned short *)0x1f802082) = exitCode;
    #else
    exit(exitCode);
    #endif
}

void SpuSetKey(long on_off, unsigned long voice_bit);
s32 SpuSetReverb(s32 on_off);
void _spu_init(s32 arg0);

void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2);

typedef struct {
    short left;
    short right;
} SpuVolume;

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


void SpuSetCommonAttr(SpuCommonAttr* attr);

    SpuCommonAttr attr;


#if 0
void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2) {
    if (arg2 == 0) {
#ifdef VERSION_PC
        write_16(arg0 * 2, arg1, __FILE__, __LINE__);
#else
        _spu_RXX->raw[arg0] = arg1;
#endif
        return;
    }

    _spu_RXX->raw[arg0] = (arg1 >> _spu_mem_mode_plus);
}
#endif 

enum
{
    SPU_T_SYNC0,
    SPU_T_SYNC,
    SPU_T_SET_TRANS,
    SPU_T_TRANSFER,
};
int _spu_t(int count, ...);

int main()
{
    printf("SpuVmInit\n");
    #if 0
    SpuVmInit(24);
    #endif
    #if 0
    extern unsigned char spuVmMaxVoice;
    spuVmMaxVoice = 24;
    SpuVmFlush();
    #endif
    #if 0
    printf("_SsInit\n");
    _SsInit();
#endif

#if 0
    SpuSetKey(0, 0xffffff);
#endif


#if 0
    SpuSetReverb(1);
#endif
#if 0
_spu_init(0);
#endif
#if 0
_spu_FsetRXX(0, 0, 0);
#endif


#if 0
    attr.mask = 0xffffffff;
    attr.mvol.left = 1;
    attr.mvol.right = 2;
    attr.mvolmode.left = 1;
    attr.mvolmode.right = 1;
    attr.mvolx.left = 3;
    attr.mvolx.right = 4;
    attr.cd.volume.left = 1;
    attr.cd.volume.right = 2;
    attr.cd.reverb = 0;
    attr.cd.mix = 0;
    attr.ext.volume.left = 2;
    attr.ext.volume.right = 3;
    attr.ext.reverb = 0;
    attr.ext.mix = 0;
#if 0
    /* reset spucnt*/
    *(u16*)0x1F801DAA = 0;
    SpuSetCommonAttr(&attr);
#endif
    attr.cd.reverb = 1;
    attr.cd.mix = 1;
    attr.ext.reverb = 1;
    attr.ext.mix = 1;

    *(u16*)0x1F801DAA = 0;
    SpuSetCommonAttr(&attr);
    
#endif

PcsxReduxExit(0);
    return 0;
}