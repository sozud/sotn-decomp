#include "dra.h"
#include "objects.h"
#include "sfx.h"

void SetCdVolume(s8 s_num, s16 arg1, s16 arg2);

extern s16 g_CurrentXaSoundId;
extern s16 D_80138458;
extern s32 D_8013AE90;
extern u8 D_8013B640;
extern s32 D_8013AEF4;

u32 CdSoundCommand4(void) {
    u32 address;
    u8 var_v0;

    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        D_80138458 = g_CurrentXaSoundId;

#ifdef VERSION_HD
        if (g_CurrentXaSoundId < 0x3d) {
#else
        if (g_CurrentXaSoundId < 0x40) {
#endif
            g_CdSoundCommand16 = 0;
        }

        D_80139820 = g_XaMusicConfigs[D_80138458].volume;
        g_CdVolume = D_80139820;
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        g_CdMode[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;

    case 1:
        var_v0 = DoCdCommand(CdlSetmode, g_CdMode, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        } else {
            return var_v0;
        }

    case 2:
        g_CdMode[0] = g_XaMusicConfigs[D_80138458].filter_file;
        g_CdMode[1] = g_XaMusicConfigs[D_80138458].filter_channel_id % 16;
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;

    case 3:
        var_v0 = DoCdCommand(CdlSetfilter, g_CdMode, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        } else {
            return var_v0;
        }

    case 4:
        address = g_XaMusicConfigs[D_80138458].filter_channel_id +
                  g_XaMusicConfigs[D_80138458].cd_addr + 150;
        D_80139014 = g_XaMusicConfigs[D_80138458].unk230;

        if (D_80139014 == 2) {
            D_8013AE90 = g_XaMusicConfigs[D_80138458].unk228 + 20;
        } else {
            D_8013AE90 = g_XaMusicConfigs[D_80138458].unk228;
        }

        address += g_CurCdPos;
        MakeCdLoc(address, &D_8013B640);
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;

    case 5:
        var_v0 = DoCdCommand(CdlSetloc, &D_8013B640, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        } else {
            return var_v0;
        }

    case 6:
        var_v0 = DoCdCommand(CdlReadN, NULL, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        } else {
            return var_v0;
        }

    case 7:
        var_v0 = DoCdCommand(CdlNop, NULL, g_CdCommandResult);
        if (var_v0 == 0) {
            var_v0 = *g_CdCommandResult & 0x40;
            if (var_v0 == 0) {
                g_CdSoundCommandStep += 1;
                return g_CdSoundCommandStep;
            } else {
                return var_v0;
            }
        } else {
            return var_v0;
        }

    case 8:
        SsSetSerialAttr(0, 0, 1);
        D_8013AEF4 = VSync(-1);
        g_CdSoundCommandStep = 0;
        D_8013901C = D_80138458;
        D_801390A0 = g_CdSoundCommandStep;
        return AdvanceCdSoundCommandQueue();

    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        return AdvanceCdSoundCommandQueue();
    }
}

const u32 padding_CdSoundCommand4 = 0;
