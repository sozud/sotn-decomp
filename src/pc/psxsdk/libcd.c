#include <common.h>
#include <psxsdk/libcd.h>
#include "../log.h"
#include <assert.h>

CdlCB CdReadyCallback(CdlCB func) {
    DEBUGF("not implemented");
    return func;
}

// char* CdControlComToStr(u_char com)
// {
//     switch(mode)
//     {
//         case CdlNop:
//         return "CdlNop";
//         case CdlSetloc:	return "CdlSetloc";
//         case CdlPlay:		return "CdlPlay";
//         case CdlForward: return "CdlForward";
//         case CdlBackward: return "CdlBackward";
//         default:
//         assert(false);
//     }
// }

char* CdSyncModeToStr(int mode) {
    switch (mode) {
    case CdlNop:
        return "CdlNop";
    case CdlSetloc:
        return "CdlSetloc";
    case CdlPlay:
        return "CdlPlay";
    case CdlForward:
        return "CdlForward";
    case CdlBackward:
        return "CdlBackward";
    case CdlReadN:
        return "CdlReadN";
    case CdlSetfilter:
        return "CdlSetfilter";
    case CdlSetmode:
        return "CdlSetmode";
    case CdlGetTD:
        return "CdlGetTD"; //	0x14
    default:
        printf("missing mode %02x\n", mode);
        assert(false);
    }

    return "";

    // // case: CdlReadN	0x06
    // // case: CdlStandby	0x07
    // // case: CdlStop		0x08
    // // case: CdlPause	0x09
    // // case: CdlMute		0x0b
    // // case: CdlDemute	0x0c
    // // case: CdlSetfilter	0x0d
    // // case: CdlSetmode	0x0e
    // // case: CdlGetparam	0x0f
    // // case: CdlGetlocL	0x10
    // // case: CdlGetlocP	0x11
    // // case: CdlGetTN	0x13
    // // case: CdlGetTD	0x14
    // // case: CdlSeekL	0x15
    // // case: CdlSeekP	0x16
    // // case: CdlReadS	0x1B
}

#include <stdio.h>

#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

int CdPosToInt(CdlLOC* p) {
    return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) +
           DECODE_BCD(p->sector) - 150;
}

FILE* cd_fp = NULL;

bool reading = false;

int CdControl(u_char com, u_char* param, u_char* result) {
    DEBUGF("com %d %s", com, CdSyncModeToStr(com));

    if (!cd_fp) {
        cd_fp = fopen("/home/d/sotn-decomp/iso/"
                      "Castlevania\ -"
                      "\ Symphony\ of\ the\ Night\ \(USA\)\ \(Track\ 1\).bin",
                      "rb");

        if (!cd_fp) {
            assert(false);
        }
    }

    switch (com) {
    case CdlSetloc:
        CdlLOC* pos = (CdlLOC*)param;
        fseek(cd_fp, CdPosToInt(pos) * 2352, SEEK_SET);
        break;

    case CdlReadN:
    printf("starting to read\n");
        reading = true;
        break;
    }
    return 1;
}

int CdSync(int mode, u_char* result) {
    DEBUGF("mode %0d %s", mode, CdSyncModeToStr(mode));
    return CdlComplete;
}

int CdMix(CdlATV* vol) {
    DEBUGF("not implemented");
    return 0;
}

//
// output should be readable at -2 and -1
static void DecodeXAADPCM(const uint8_t* input, int16_t* output,
                          const unsigned shift, const unsigned weight) {
    // Weights copied over from SPU channel ADPCM playback code, may not be
    // entirely the same for CD-XA ADPCM, we need to run tests.
    static const int32_t Weights[16][2] = {
        // s-1    s-2
        {0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60},
    };

    for (int i = 0; i < 28; i++) {
        int32_t sample;

        sample = (int16_t)(input[i] << 8);
        sample >>= shift;

        sample += ((output[i - 1] * Weights[weight][0]) >> 6) +
                  ((output[i - 2] * Weights[weight][1]) >> 6);

        if (sample < -32768)
            sample = -32768;

        if (sample > 32767)
            sample = 32767;

        output[i] = sample;
    }
}

struct CD_Audio_Buffer
{
 int16_t Samples[2][0x1000];	// [0][...] = l, [1][...] = r
 uint32_t Size;
 uint32_t Freq;
 uint32_t ReadPos;
};

struct XA_Subheader
{
 uint8_t file;
 uint8_t channel;
 uint8_t submode;
 uint8_t coding;

 uint8_t file_dup;
 uint8_t channel_dup;
 uint8_t submode_dup;
 uint8_t coding_dup;
};

struct XA_SoundGroup
{
 uint8_t params[16];
 uint8_t samples[112];
};

#define XA_CODING_8BIT		0x10
#define XA_CODING_189		0x04
#define XA_CODING_STEREO	0x01

int16_t xa_previous[2][2];

void XA_ProcessSector(const uint8_t* sdata, struct CD_Audio_Buffer* ab) {
    const struct XA_Subheader* sh = (const struct XA_Subheader*)&sdata[12 + 4];
    const unsigned unit_index_shift = (sh->coding & XA_CODING_8BIT) ? 0 : 1;

    // printf("File: 0x%02x 0x%02x - Channel: 0x%02x 0x%02x - Submode: 0x%02x
    // 0x%02x - Coding: 0x%02x 0x%02x - \n", sh->file, sh->file_dup,
    // sh->channel, sh->channel_dup, sh->submode, sh->submode_dup, sh->coding,
    // sh->coding_dup);
    ab->ReadPos = 0;
    ab->Size = 18 * (4 << unit_index_shift) * 28;

    if (sh->coding & XA_CODING_STEREO)
        ab->Size >>= 1;

    ab->Freq = (sh->coding & XA_CODING_189) ? 3 : 6;

    // fprintf(stderr, "Coding: %02x %02x\n", sh->coding, sh->coding_dup);

    for (unsigned group = 0; group < 18; group++) {
        const struct XA_SoundGroup* sg =
            (const struct XA_SoundGroup*)&sdata[12 + 4 + 8 + group * 128];

        for (unsigned unit = 0; unit < (4U << unit_index_shift); unit++) {
            const uint8_t param = sg->params[(unit & 3) | ((unit & 4) << 1)];
            const uint8_t param_copy =
                sg->params[4 | (unit & 3) | ((unit & 4) << 1)];
            uint8_t ibuffer[28];
            int16_t obuffer[2 + 28];

            if (param != param_copy) {
                // PSX_WARNING(
                //     "[CDC] CD-XA param != param_copy --- %d %02x %02x\n", unit,
                //     param, param_copy);
            }

            for (unsigned i = 0; i < 28; i++) {
                uint8_t tmp = sg->samples[i * 4 + (unit >> unit_index_shift)];

                if (unit_index_shift) {
                    tmp <<= (unit & 1) ? 0 : 4;
                    tmp &= 0xf0;
                }

                ibuffer[i] = tmp;
            }

            const bool ocn =
                (bool)(unit & 1) && (sh->coding & XA_CODING_STEREO);

            obuffer[0] = xa_previous[ocn][0];
            obuffer[1] = xa_previous[ocn][1];

            DecodeXAADPCM(ibuffer, &obuffer[2], param & 0x0F, param >> 4);

            xa_previous[ocn][0] = obuffer[28];
            xa_previous[ocn][1] = obuffer[29];

            if (param != param_copy)
                memset(obuffer, 0, sizeof(obuffer));

            if (sh->coding & XA_CODING_STEREO) {
                for (unsigned s = 0; s < 28; s++) {
                    ab->Samples[ocn][group * (2 << unit_index_shift) * 28 +
                                     (unit >> 1) * 28 + s] = obuffer[2 + s];
                }
            } else {
                for (unsigned s = 0; s < 28; s++) {
                    ab->Samples[0][group * (4 << unit_index_shift) * 28 +
                                   unit * 28 + s] = obuffer[2 + s];
                    ab->Samples[1][group * (4 << unit_index_shift) * 28 +
                                   unit * 28 + s] = obuffer[2 + s];
                }
            }
        }
    }

#if 0
 // Test
 for(unsigned i = 0; i < ab->Size; i++)
 {
  static unsigned counter = 0;

  ab->Samples[0][i] = (counter & 2) ? -0x6000 : 0x6000;
  ab->Samples[1][i] = rand();
  counter++;
 }
#endif
}

 struct CD_Audio_Buffer ab;

void ExecCd() {
    if (reading) {
        uint8_t sector[2352];
        printf("read at %d\n", ftell(cd_fp));
        fread(sector, sizeof(uint8_t), 2352, cd_fp);
        XA_ProcessSector(sector, &ab);
    }
}
