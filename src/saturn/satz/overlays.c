// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"
#include "../zero/overlay.h"
#include "../game.h"
#include <saturn_player.h>
#include <string.h>

extern SaturnGameApi g_ApiInit;
extern SaturnPlayerOvl MARIA_player;
extern SaturnStageDataTables SATZ_STAGE_DATA;

SaturnGameApi g_GameOvl;
SaturnPlayerOvl g_PlayerOvl;
SaturnStageDataTables g_StageOverlayData;

static const struct {
    const char* name;
    void* area;
    const void* header;
    u32 size;
} s_Overlays[] = {
    {"GAME.PRG", &g_GameOvl, &g_ApiInit, sizeof(SaturnGameApi)},
    {"MARIA.PRG", &g_PlayerOvl, &MARIA_player, sizeof(SaturnPlayerOvl)},
    {SATZ_STAGE_PRG, &g_StageOverlayData, &SATZ_STAGE_DATA,
     sizeof(SaturnStageDataTables)},
};

static int is_prg(const char* name) {
    size_t n = strlen(name);
    return n > 4 && !strcmp(name + n - 4, ".PRG");
}

void* sotn_satz_low_work_ram(u32 address);

void* sotn_satz_load_target(void* dst) {
    unsigned long address = (unsigned long)dst;
    void* low;

    if (address >= 0x30000000ul || (address & ~0x20000000ul) >= 0x08000000ul) {
        return dst;
    }
    if ((address & 0x07F00000) >= 0x05A00000 &&
        (address & 0x07F00000) < 0x06000000) {
        return satz_bus_pointer(address);
    }
    if ((low = sotn_satz_low_work_ram(address))) {
        return low;
    }
    if ((address & 0x07F00000) == 0x06000000 ||
        (address & 0x07F00000) == 0x00200000) {
        satz_die(
            "load into work RAM address %08lX: give it a C label", address);
    }
    return dst;
}

s32 (*sotn_satz_movie_entry(void))(void);

int sotn_satz_install_overlay(const char* name, void* dst, s32* size) {
    u32 i;

    if (!is_prg(name)) {
        return 0;
    }
    if (!strcmp(name, "MOVIE.PRG")) {
        g_GameOvl.equipDefs = (void*)sotn_satz_movie_entry();
        *size = 0;
        return 1;
    }
    for (i = 0; i < sizeof(s_Overlays) / sizeof(s_Overlays[0]); i++) {
        if (!strcmp(name, s_Overlays[i].name)) {
            if (dst != s_Overlays[i].area) {
                satz_die("%s loaded to %p, not its header area", name, dst);
            }
            memcpy(
                s_Overlays[i].area, s_Overlays[i].header, s_Overlays[i].size);
            *size = s_Overlays[i].size;
            return 1;
        }
    }
    satz_die("overlay %s is not in the native build", name);
}
