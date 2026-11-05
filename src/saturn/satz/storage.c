// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <string.h>

typedef struct {
    const char* name;
    uint32_t address;
    uint8_t* data;
    uint32_t retail_size;
} SotnFixedSymbol;
extern const SotnFixedSymbol sotn_fixed_symbols[];
void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));

void sotn_satz_clear_range(uint32_t start, uint32_t size) {
    const SotnFixedSymbol* s;

    for (s = sotn_fixed_symbols; s->name; s++) {
        if (s->address >= start && s->address < start + size) {
            memset(s->data, 0, s->retail_size * 2);
        }
    }
}

uint8_t g_FileLoadBuffer[0x10000] __attribute__((aligned(16)));

uint8_t g_StageOvlArea[0x6000] __attribute__((aligned(16)));

uint8_t DAT_00232000[0x33380];
uint8_t DAT_00252000[0x96100];
int32_t DAT_00292000[0x20000 / 4];
uint8_t DAT_002B2000[0x15000];
int16_t DAT_002C7000[0x19000 / 2];
uint16_t DAT_002E0000[0x12000 / 2];
int32_t DAT_002F2000[0xE000 / 4];

static const struct {
    uint32_t address;
    void* data;
    uint32_t size;
} s_LowWorkRam[] = {
    {0x00232000, DAT_00232000, sizeof(DAT_00232000)},
    {0x00252000, DAT_00252000, sizeof(DAT_00252000)},
    {0x00292000, DAT_00292000, sizeof(DAT_00292000)},
    {0x002B2000, DAT_002B2000, sizeof(DAT_002B2000)},
    {0x002C7000, DAT_002C7000, sizeof(DAT_002C7000)},
    {0x002E0000, DAT_002E0000, sizeof(DAT_002E0000)},
    {0x002F2000, DAT_002F2000, sizeof(DAT_002F2000)},
};

void* sotn_satz_low_work_ram(uint32_t address) {
    uint32_t i, best = sizeof(s_LowWorkRam) / sizeof(s_LowWorkRam[0]);

    for (i = 0; i < sizeof(s_LowWorkRam) / sizeof(s_LowWorkRam[0]); i++) {
        if (address >= s_LowWorkRam[i].address &&
            address - s_LowWorkRam[i].address < s_LowWorkRam[i].size) {
            best = i;
        }
    }
    if (best == sizeof(s_LowWorkRam) / sizeof(s_LowWorkRam[0])) {
        return NULL;
    }
    return (uint8_t*)s_LowWorkRam[best].data +
           (address - s_LowWorkRam[best].address);
}

void* sotn_satz_retail_address(uint32_t address) {
    const SotnFixedSymbol* s;

    void* low = sotn_satz_low_work_ram(address);

    if (low) {
        return low;
    }
    if (address >= 0x060485E0 &&
        address < 0x060485E0 + sizeof(g_FileLoadBuffer)) {
        return g_FileLoadBuffer + (address - 0x060485E0);
    }
    for (s = sotn_fixed_symbols; s->name; s++) {
        if (address >= s->address && address < s->address + s->retail_size) {
            return s->data + (address - s->address);
        }
    }
    sotn_satz_unimplemented("sotn_satz_retail_address: no native object");
}

void* sotn_satz_be16_copy(const void* src, uint32_t bytes) {
    static uint16_t ring[0x2000];
    static uint32_t next;
    const uint16_t* in = src;
    uint16_t* out;
    uint32_t i, words = (bytes + 1) / 2;

    if (next + words > sizeof(ring) / 2) {
        next = 0;
    }
    out = &ring[next];
    next += words;
    for (i = 0; i < words; i++) {
        out[i] = (uint16_t)((in[i] >> 8) | (in[i] << 8));
    }
    return out;
}

void sotn_snd_ram_copy(uint8_t* dst, const void* src, uint32_t count) {
    satz_bus_store(satz_bus_address(dst), src, count);
}

void sotn_snd_ram_clear(uint8_t* dst, uint32_t count) {
    static const uint8_t zero[0x400];
    uint32_t done;

    for (done = 0; done < count; done += sizeof(zero)) {
        satz_bus_store(
            satz_bus_address(dst + done), zero,
            count - done < sizeof(zero) ? count - done : sizeof(zero));
    }
}
