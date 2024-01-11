#include <common.h>
#include <stdarg.h>
#include <stdio.h>
#include <log.h>
#include "psxsdk/cdc.h"

bool g_IsQuitRequested; // controls whenever MainGame should quit

FILE* cd_fp = NULL;
void OpenCd(char* filename) {
    cd_fp = fopen(filename, "rb");

    if (!cd_fp) {
        DEBUGF("Couldn't open CD.\n");
    }
}

void MyAudioCallback(void* data, u8* buffer, int length) {
    // printf("here!\n");
    int i = 0;
    void my_audio_callback(void *userdata, u8 *stream, int len);

    my_audio_callback(data, buffer, length);

    //  while (i * 4 < length) {
    //     buffer[i * 4 + 0] = rand();
    //     i++;
    //  }
    // while (i * 4 < length) {
    //     // printf("i read size %d %d %d\n", i, AudioBuffer.ReadPos, AudioBuffer.Size);
    //     if (AudioBuffer.ReadPos < AudioBuffer.Size) {
    //         printf("filling\n");
    //         // emit until we have to generate again
    //         int32_t samples[2];

    //         GetCDAudio(samples);

    //         buffer[i * 4 + 1] = samples[0] >> 8;
    //         buffer[i * 4 + 0] = samples[0];

    //         // right
    //         buffer[i * 4 + 3] = samples[1] >> 8;
    //         buffer[i * 4 + 2] = samples[1];
    //         i += 1;
    //     } else if (CdReading()) {
    //         // printf("exec cd\n");
    //         // generate more audio
    //         ExecCd();
    //     }
    // }
    // printf("end of callback\n");
}

int MyFntPrint(const char* fmt, va_list arg) {
    char buf[256];
    vsnprintf(buf, sizeof(buf), fmt, arg);
    INFOF(buf);
}

u_long* MyFntFlush(int id) {
    fflush(stderr);
    return 0;
}
