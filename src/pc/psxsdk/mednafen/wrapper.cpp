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

extern "C" void write_16(u32 addr, u16 data, char* file, int line)
{
    printf("write16 %08X %04X %s:%d\n", addr, data, file, line);
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    SPU->Write(0, addr, data, file, line);
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
    SPU->Write(0, addr, data >> 16, __FILE__, __LINE__);
    SPU->Write(0, addr + 2, data & 0xFFFF, __FILE__, __LINE__);
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
#include <random>
extern "C"
void SoundRevCallback(void *userdata, u8 *stream, int len)
{
    if(!ready)
    {
        printf("not ready\n");
        return;
    }

    printf("SoundRev\n");
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
#include <string>
struct WriteEntry {
   uint32 A;
   uint16 V;
   std::string file;
   int line;
};

#include <vector>

extern std::vector<WriteEntry> writes;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


void CheckWrites(char* filename)
{
    std::ifstream infile(filename);
    std::string line;

    if (!infile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::vector<WriteEntry> expected;

    while (std::getline(infile, line)) {
        std::string addressStr, valueStr;

        // Find the position of "Write: "
        size_t pos = line.find("Write: ");
        if (pos != std::string::npos) {
            // Extract the substrings after "Write: "
            std::istringstream iss(line.substr(pos + 7));
            iss >> addressStr >> valueStr;

            // Convert the extracted strings to integers
            u32 address = std::stoul(addressStr, nullptr, 16);
            u16 value = std::stoul(valueStr, nullptr, 16);

            // Output the values
            // std::cout << "Address: " << std::hex << address << " Value: " << std::hex << value << std::endl;

            expected.push_back({address, value});
        }
    }

    for(int i = 0; i < expected.size(); i++)
    {
        if(
            expected[i].A != writes[i].A ||
            expected[i].V != writes[i].V
            )
        {
            printf("mismatch: %d expected %0X %04X != actual %0X %04X %s:%d\n", i, expected[i].A, expected[i].V,
            
             writes[i].A, writes[i].V, writes[i].file, writes[i].line);

            exit(0);
        }
        else {
            printf("match: %d %0X %04X\n", i, expected[i].A, expected[i].V);
        }
    }
    infile.close();

    writes.clear();
}

extern "C" void SpuVmInit(u8 arg0);
extern "C" void _SsInit(void);

extern "C" void SpuSetKey(long on_off, unsigned long voice_bit);

extern "C" s32 SpuSetReverb(s32);
extern "C" void _spu_init(s32 arg0);
extern "C" void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2);


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

extern "C" void SpuSetCommonAttr(SpuCommonAttr* attr);

s8 space[0x1000] = {0};

 extern "C" s32 SpuInitMalloc(s32 num, s8* top);
 extern "C" long SpuMallocWithStartAddr(unsigned long addr, long size);

 
typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

extern SPU_MALLOC *_spu_memList;

#define ASSERT_EQ(value1, value2)                                                           \
    if ((value1) != (value2))                                                               \
    {                                                                                       \
        printf("%d != %d in %s %s:%d\n", value1, value2, __FUNCTION__, __FILE__, __LINE__); \
        exit(1);                                                                   \
    }

#define ASSERT_EQ_HEX(value1, value2)                                                           \
    if ((value1) != (value2))                                                               \
    {                                                                                       \
        printf("%08X != %08X in %s %s:%d\n", value1, value2, __FUNCTION__, __FILE__, __LINE__); \
        exit(1);                                                                   \
    }
    extern "C" long SpuMalloc(long size);

void test_spu_malloc()
{
    SPU_MALLOC* temp;
    long result;
    int i;

    result = SpuInitMalloc(32, space);

    printf("SpuInitMalloc result %d\n", result);

    for(i = 0; i < 32; i++)
    {
        printf("temp[%d] addr %08X size %d\n", i, _spu_memList[i].addr, _spu_memList[i].size);
    }
    

    ASSERT_EQ_HEX(_spu_memList[0].addr, 0x40001010);
    ASSERT_EQ_HEX(_spu_memList[0].size, 520176)
    ASSERT_EQ_HEX(_spu_memList[1].addr, 0);
    ASSERT_EQ_HEX(_spu_memList[1].size, 0)
    ASSERT_EQ_HEX(result, 32)


    result = SpuMalloc(0x200);
#if 1
    for(i = 0; i < 32; i++)
    {
        printf("temp[%d] addr %08X size %d\n", i, _spu_memList[i].addr, _spu_memList[i].size);
    }

    ASSERT_EQ_HEX(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ_HEX(_spu_memList[0].size, 512);
    ASSERT_EQ_HEX(_spu_memList[1].addr, 0x40001210);
    ASSERT_EQ_HEX(_spu_memList[1].size, 519664);
    ASSERT_EQ_HEX(_spu_memList[2].addr, 0);
    ASSERT_EQ_HEX(_spu_memList[2].size, 0);
    ASSERT_EQ_HEX(result, 0x1010);

#endif
    printf("result %d\n", result);
}

extern "C" void med_run_tests()
{
    #if 0
    SpuVmInit(24);
    CheckWrites("./src/pc/psxsdk/expected/SpuVmInit.txt");

    _SsInit();
    CheckWrites("./src/pc/psxsdk/expected/_SsInit.txt");

    SpuSetKey(1, 0xffffff);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetKey1.txt");

    SpuSetKey(0, 0xffffff);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetKey0.txt");

    SpuSetReverb(0);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetReverb0.txt");

    // spuallocatearea stuff
    // SpuSetReverb(1);
    // CheckWrites("./src/pc/psxsdk/expected/SpuSetReverb1.txt");

    _spu_init(0);
    CheckWrites("./src/pc/psxsdk/expected/_spu_init.txt");

    _spu_FsetRXX(0, 0, 0);
    CheckWrites("./src/pc/psxsdk/expected/_spu_FsetRXX.txt");

    SpuCommonAttr attr;

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

    write_16(0x1F801DAA, 0, __FILE__, __LINE__);
    SpuSetCommonAttr(&attr); 

    CheckWrites("./src/pc/psxsdk/expected/SpuSetCommonAttr0.txt");

    attr.cd.reverb = 1;
    attr.cd.mix = 1;
    attr.ext.reverb = 1;
    attr.ext.mix = 1;

    write_16(0x1F801DAA, 0, __FILE__, __LINE__);
    SpuSetCommonAttr(&attr);

    CheckWrites("./src/pc/psxsdk/expected/SpuSetCommonAttr1.txt");
#endif
    test_spu_malloc();

    // exit(0);
}