// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdio.h>
#include <stdlib.h>
#include "sattypes.h"
#include "zero.h"
#include "zero/sound.h"

void PlaySfx(s32 sfxId);
extern s32 DAT_060642F8;

#define SOUND_LOG_VALUES 9

void sotn_satz_sound_log(unsigned long long frame) {
    static FILE* log;
    static int opened, fired;
    static u32 last[SOUND_LOG_VALUES];
    static unsigned long long sfxFrame;
    static int sfxId;
    const char* env;
    SndPcmPlayAdr pcm;
    u32 now[SOUND_LOG_VALUES];
    int i, changed = 0;

    if (!opened) {
        opened = 1;
        if ((env = getenv("SOTN_SATZ_SOUND_LOG"))) {
            log = fopen(env, "w");
        }
        if ((env = getenv("SOTN_SATZ_TEST_SFX"))) {
            sscanf(env, "%llu %i", &sfxFrame, &sfxId);
        }
    }
    if (sfxId && !fired && frame >= sfxFrame) {
        fired = 1;
        PlaySfx(sfxId);
    }
    if (!log) {
        return;
    }
    SND_GetPcmPlayAdr(&pcm, 5);
    now[0] = (u32)DAT_06064300;
    now[1] = DAT_06064360;
    now[2] = DAT_0606434C;
    now[3] = (u32)DAT_06064408;
    now[4] = (u32)DAT_06064394;
    now[5] = (u32)DAT_060642F8;
    now[6] = pcm.radr;
    now[7] = DAT_06064214;
    now[8] = (u32)DAT_0606433C;
    for (i = 0; i < SOUND_LOG_VALUES; i++) {
        if (i != 6) {
            changed |= now[i] != last[i];
        }
        last[i] = now[i];
    }
    if (changed) {
        fprintf(log,
                "frame %llu: clip=%x left=%x wr=%x copied=%x mode=%x cmd=%x "
                "radr=%x vox=%x start=%x\n",
                frame, now[0], now[1], now[2], now[3], now[4], now[5], now[6],
                now[7], now[8]);
        fflush(log);
    }
}
