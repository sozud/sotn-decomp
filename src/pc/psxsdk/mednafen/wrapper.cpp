#include "dma.h"
#include "spu.h"
#include <types.h>

#include <cstdio>
PS_SPU* SPU = nullptr;


bool init = false;

bool ready = false;

extern "C" void mednafen_init()
{
    ready = true;
    MDFN_IEN_PSX::DMA_Init();
    MDFN_IEN_PSX::DMA_Power();
    SPU = new PS_SPU();
    SPU->Power();
}

extern "C" void write_16(u32 addr, u16 data)
{
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    SPU->Write(0, addr, data);
    // printf("[SPU] Write: %08x %04x\n", addr, data);
}

extern "C" u16 read_16(u32 addr, char* file, int line)
{
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    // printf("read_16 from %08X %s:%d\n", addr, file, line);
    return SPU->Read(0, addr);
}

extern "C" void write_32(u32 addr, u32 data)
{
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    SPU->Write(0, addr, data >> 16);
    SPU->Write(0, addr + 2, data & 0xFFFF);
}

extern "C" u32 read_32(u32 addr)
{
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    u16 upper = SPU->Read(0, addr);
    u16 lower = SPU->Read(0, addr + 2);
    return upper << 16 | lower;
}


double accum = 0;
extern "C" void SsSeqCalledTbyT(void);
#include <string.h>
extern "C"
void SoundRevCallback(void *userdata, u8 *stream, int len)
{
    if(!ready)
    {
        return;
    }
    for(int i = 0; i < len / 4; i++)
    {
        // generate one sample
        SPU->UpdateFromCDC(768);
        if(accum >= 735.735)
        {
         SsSeqCalledTbyT();
         accum -= 735.735;
        }
        accum += 1;
    }

    memcpy(stream, IntermediateBuffer, len);

    if (IntermediateBufferPos >= 1024)
    {
        IntermediateBufferPos = 0;
    }
}