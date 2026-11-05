// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../zero.h"
#include "../game.h"
#include "../lib/spr/spr.h"

extern s32 g_GameDataEnd;
extern u32 g_randomNext;
unsigned int sotn_rand_state(void);

static s32 MovieSkipped(void) { return 0; }

s32 (*sotn_satz_movie_entry(void))(void) { return MovieSkipped; }

static void sotn_satz_dump_objects_to(FILE* file, uint64_t frame);

static void sotn_satz_dump_objects(uint64_t frame) {
    static FILE* file;
    static int opened;

    if (!opened) {
        const char* path = getenv("SOTN_SATZ_OBJECTS");
        opened = 1;
        file = path ? fopen(path, "w") : NULL;
        if (file) {
            fputs("frame\tslot\tid\tx\ty\tvx\tvy\tfacing\tstep\tstep_s\tanim\n",
                  file);
        }
    }
    if (file) {
        sotn_satz_dump_objects_to(file, frame);
    }
}

static void sotn_satz_dump_objects_to(FILE* file, uint64_t frame) {
    Entity* e;
    int i;

    fprintf(file, "%llu\t-1\t%u\t%d\t%d\t0\t0\t0\t%u\t%u\t0\n",
            (unsigned long long)frame, DAT_0605cea0.unk2,
            g_Tilemap.scrollX.i.hi, g_Tilemap.scrollY.i.hi, DAT_0605cea0.unk0,
            DAT_0605cea0.unk2);
    fprintf(file, "%llu\t-2\t0\t%d\t%d\t%d\t%d\t0\t0\t0\t0\n",
            (unsigned long long)frame, g_GameDataEnd, (s32)g_Timer,
            (s32)g_randomNext, (s32)sotn_rand_state());
    for (i = 0; i < 256; i++) {
        e = &g_Entities[i];
        if (e->entityId == 0 && i != 0) {
            continue;
        }
        fprintf(file, "%llu\t%d\t%u\t%d\t%d\t%d\t%d\t%u\t%u\t%u\t%d\n",
                (unsigned long long)frame, i, e->entityId, e->posX.i.hi,
                e->posY.i.hi, e->velocityX, e->velocityY, e->facingLeft,
                e->step, e->step_s, e->animCurFrame);
    }
    fflush(file);
}

void func_06032E88(unsigned int value);

static void sotn_satz_cram_init(void) {
    const char* path = getenv("SOTN_SATZ_CRAM_INIT");
    unsigned char cram[0x1000];
    FILE* f;
    unsigned i;

    if (!path || !(f = fopen(path, "rb"))) {
        return;
    }
    if (fread(cram, 1, sizeof(cram), f) == sizeof(cram)) {
        for (i = 0; i < sizeof(cram); i += 2) {
            satz_bus_write(0x25F00000 + i, (cram[i] << 8) | cram[i + 1], 2);
        }
    }
    fclose(f);
}

static void sotn_satz_warp(void) {
    const char* warp = getenv("SOTN_SATZ_WARP");
    unsigned x, y, room;

    if (!warp) {
        return;
    }
    if (sscanf(warp, "%i %i %i", &x, &y, &room) != 3) {
        satz_die("SOTN_SATZ_WARP: want \"X Y ROOM\"");
    }
    g_RoomTeleports[0x48].x = x;
    g_RoomTeleports[0x48].y = y;
    g_RoomTeleports[0x48].roomId = room;
}

void sotn_satz_boot_override(void) {
    sotn_satz_cram_init();
    g_CurrentRoom.stageID = SATZ_STAGE_ID;
    g_PlayableCharacter = 2;
    D_8006C374 = 0x48;
    g_RoomTeleports[0x48].stageId = SATZ_STAGE_ID;
    DAT_06061dd0 = 1;
    sotn_satz_warp();
}

extern const struct {
    const char* name;
    uint32_t address;
    uint8_t* data;
    uint32_t retail_size;
} sotn_fixed_symbols[];

void sotn_satz_arrival(void) {
    static int done;
    const char* arrival = getenv("SOTN_SATZ_ARRIVAL");

    if (arrival && !done) {
        done = 1;
        D_80097C98 = atoi(arrival);
    }
    {
        static int init_done;
        const char* list = getenv("SOTN_SATZ_INIT_POKES");
        if (list && !init_done) {
            char buf[1024], *item, *save;
            init_done = 1;
            snprintf(buf, sizeof(buf), "%s", list);
            for (item = strtok_r(buf, ";", &save); item;
                 item = strtok_r(NULL, ";", &save)) {
                char name[64];
                unsigned off = 0;
                long value;
                int j;
                char* plus;
                if (sscanf(item, "%63s %li", name, &value) != 2) {
                    satz_die("SOTN_SATZ_INIT_POKES: bad item %s", item);
                }
                plus = strchr(name, '+');
                if (plus) {
                    *plus = 0;
                    off = (unsigned)strtoul(plus + 1, NULL, 0);
                }
                for (j = 0; sotn_fixed_symbols[j].name &&
                            strcmp(sotn_fixed_symbols[j].name, name);
                     j++) {
                }
                if (!sotn_fixed_symbols[j].name) {
                    satz_die("SOTN_SATZ_INIT_POKES: %s is not a fixed-address "
                             "symbol",
                             name);
                }
                sotn_fixed_symbols[j].data[off] = (uint8_t)value;
            }
        }
    }
}

static uint64_t s_Frame;

int sotn_satz_extra_iteration(void) {
    static unsigned long long frames[64], used = ~0ull;
    static int count = -1;
    const char* list;
    char* end;
    int i;

    if (count < 0) {
        count = 0;
        for (list = getenv("SOTN_SATZ_EXTRA"); list && *list && count < 64;
             list = *end ? end + 1 : end) {
            frames[count++] = strtoull(list, &end, 10);
        }
    }
    for (i = 0; i < count; i++) {
        if (frames[i] == s_Frame && used != s_Frame) {
            used = s_Frame;
            return 1;
        }
    }
    return 0;
}

void __real_SCL_DisplayFrame(void);
void __wrap_SCL_DisplayFrame(void) {
    if (!sotn_satz_extra_iteration()) {
        __real_SCL_DisplayFrame();
    }
}

static void sotn_satz_lag(uint64_t frame) {
    static unsigned long long frames[64];
    static int count = -1;
    const char* list;
    char* end;
    int i;

    if (count < 0) {
        count = 0;
        for (list = getenv("SOTN_SATZ_LAG"); list && *list && count < 64;
             list = *end ? end + 1 : end) {
            frames[count++] = strtoull(list, &end, 10);
        }
    }
    for (i = 0; i < count; i++) {
        if (frames[i] == frame) {
            g_Timer++;
        }
    }
}

static void sotn_satz_sync_seeds(uint64_t frame) {
    static int count = -1;
    static unsigned long long at[8];
    static long long values[8][4];
    static int fields[8];
    const char* seeds;
    int i;

    if (count < 0) {
        count = 0;
        for (seeds = getenv("SOTN_SATZ_SEEDS"); seeds && *seeds && count < 8;
             seeds = strchr(seeds, ';')) {
            seeds += *seeds == ';';
            fields[count] =
                sscanf(seeds, "%llu %lld %lld %lld %lld", &at[count],
                       &values[count][0], &values[count][1], &values[count][2],
                       &values[count][3]) -
                1;
            count += fields[count] == 1 || fields[count] >= 3;
            if (!strchr(seeds, ';')) {
                break;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (frame != at[i]) {
            continue;
        }
        if (fields[i] == 1) {
            g_Timer = (u32)values[i][0];
            continue;
        }
        g_GameDataEnd = (s32)values[i][0];
        g_randomNext = (u32)values[i][1];
        func_06032E88((unsigned int)values[i][2]);
        if (fields[i] == 4) {
            g_Timer = (u32)values[i][3];
        }
    }
}

uint32_t satz_mem_read(uint32_t address, int size);

static void sotn_satz_watch(uint64_t frame) {
    static int loaded;
    static unsigned long long frames[64];
    static unsigned addresses[64], lengths[64];
    static char names[64][32];
    static int count;
    const char* path;
    const char* dir;
    char out[512];
    FILE* f;
    int i;
    unsigned j;

    if (!loaded) {
        loaded = 1;
        path = getenv("SOTN_SATZ_WATCH");
        if (path && (f = fopen(path, "r"))) {
            while (count < 64 && fscanf(f, "%llu %x %x %31s", &frames[count],
                                        &addresses[count], &lengths[count],
                                        names[count]) == 4) {
                count++;
            }
            fclose(f);
        }
    }
    dir = getenv("SOTN_SATZ_WATCH_DIR");
    for (i = 0; i < count; i++) {
        if (frames[i] != frame) {
            continue;
        }
        snprintf(out, sizeof(out), "%s/%s_%06llu.bin", dir ? dir : ".",
                 names[i], (unsigned long long)frame);
        if ((f = fopen(out, "wb"))) {
            for (j = 0; j < lengths[i]; j++) {
                fputc((int)(addresses[i] >= 0x25F80000
                                ? satz_bus_read(addresses[i] + j, 1)
                                : satz_mem_read(addresses[i] + j, 1)),
                      f);
            }
            fclose(f);
        }
    }
}

static unsigned s_Poll;
int sotn_satz_voice = -1;
unsigned sotn_satz_updates;

static void sotn_satz_poll_sync(void) {
    static int loaded;
    static long long* timers;
    static long long* libcs;
    static long long* voices;
    static long long seeds[3];
    static unsigned first, count;
    static long offset;
    static int seeded;
    char path[512];
    const char* sync;
    FILE* f;
    char line[256];
    long long poll, slot, id, x, y, vx, vy, voice, voiceRead;

    if (!loaded) {
        loaded = 1;
        sync = getenv("SOTN_SATZ_POLL_SYNC");
        if (!sync || sscanf(sync, "%511s %ld %u", path, &offset, &first) != 3 ||
            !(f = fopen(path, "r"))) {
            return;
        }
        while (fgets(line, sizeof(line), f)) {
            voice = 0;
            voiceRead = 0;
            if (sscanf(line,
                       "%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld",
                       &poll, &slot, &id, &x, &y, &vx, &vy, &voice,
                       &voiceRead) < 7 ||
                slot != -2 || poll < 0) {
                continue;
            }
            poll -= offset;
            if (poll < 0) {
                continue;
            }
            if (poll >= count) {
                timers = realloc(timers, (poll + 1) * sizeof(*timers));
                libcs = realloc(libcs, (poll + 1) * sizeof(*libcs));
                voices = realloc(voices, (poll + 1) * sizeof(*voices));
                while (count <= poll) {
                    libcs[count] = 0;
                    voices[count] = 0;
                    timers[count++] = -1;
                }
            }
            timers[poll] = y;
            libcs[poll] = vy;
            voices[poll] = voiceRead ? voiceRead - 1 : voice;
            if (poll == first) {
                seeds[0] = x;
                seeds[1] = vx;
                seeds[2] = vy;
            }
        }
        fclose(f);
    }
    if (!timers || sotn_satz_updates < first || sotn_satz_updates >= count ||
        timers[sotn_satz_updates] < 0) {
        return;
    }
    g_Timer = (u32)timers[sotn_satz_updates];
    if (!getenv("SOTN_SATZ_FREE_VOICE")) {
        sotn_satz_voice = (int)voices[sotn_satz_updates] - 1;
    }
    func_06032E88((unsigned int)libcs[sotn_satz_updates]);
    if (sotn_satz_updates == first && !seeded) {
        seeded = 1;
        g_GameDataEnd = (s32)seeds[0];
        g_randomNext = (u32)seeds[1];
        func_06032E88((unsigned int)seeds[2]);
    }
}

static int s_DoorClear;

static void sotn_satz_pokes(int late_pass) {
    static int count = -1;
    static unsigned at[2048];
    static char names[2048][64];
    static long values[2048];
    static char late[2048];
    const char* list;
    int i, j;

    if (count < 0) {
        count = 0;
        for (list = getenv("SOTN_SATZ_POKES"); list && *list && count < 2048;
             list = strchr(list, ';')) {
            list += *list == ';';
            if (sscanf(list, "%u %63s %li", &at[count], names[count],
                       &values[count]) == 3) {
                char* semi = strchr(names[count], ';');
                size_t n;
                if (semi) {
                    *semi = 0;
                }
                n = strlen(names[count]);
                late[count] = n && names[count][n - 1] == '!';
                if (late[count]) {
                    names[count][n - 1] = 0;
                }
                count++;
            }
            if (!strchr(list, ';')) {
                break;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (at[i] != sotn_satz_updates || late[i] != late_pass) {
            continue;
        }
        if (sscanf(names[i], "ent:%d:hp", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":hp")) {
            g_Entities[j].hitPoints = (s16)values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:spawn", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":spawn")) {
            memset(&g_Entities[j], 0, sizeof(g_Entities[j]));
            g_Entities[j].entityId = (u16)values[i];
            g_Entities[j].pfnUpdate = (*PfnEntityUpdates)[values[i] - 1]->func;
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:label:", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":label:")) {
            const char* symbol = strstr(names[i], ":label:") + 7;
            int k;
            for (k = 0; sotn_fixed_symbols[k].name &&
                        strcmp(sotn_fixed_symbols[k].name, symbol);
                 k++) {
            }
            if (!sotn_fixed_symbols[k].name) {
                satz_die("SOTN_SATZ_POKES: no fixed symbol %s", symbol);
            }
            *(u8**)&g_Entities[j].ext = sotn_fixed_symbols[k].data;
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:params", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":params")) {
            g_Entities[j].params = (u16)values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:step", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":step")) {
            g_Entities[j].step = (u16)values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:saveprobe", &j) == 1 && j >= 0 &&
            j < 256 && strstr(names[i], ":saveprobe")) {
            g_Entities[j].ext.save.unk4 = (s32)values[i];
            at[i] = ~0u;
            continue;
        }
        {
            int px, py, cx, cy;
            if (sscanf(names[i], "door:%i:%i:%i:%i", &px, &py, &cx, &cy) == 4) {
                g_Entities[0].posX.i.hi = (s16)px;
                g_Entities[0].posY.i.hi = (s16)py;
                g_CurrentRoom.unkC = cx;
                g_CurrentRoom.unk10 = cy;
                D_80097C98 = values[i];
                s_DoorClear = 1;
                at[i] = ~0u;
                continue;
            }
        }
        if (!strcmp(names[i], "status:hp")) {
            g_Status.hp = values[i];
            at[i] = ~0u;
            continue;
        }
        if (!strcmp(names[i], "status:hearts") ||
            !strcmp(names[i], "status:heartsmax") ||
            !strcmp(names[i], "status:gold")) {
            if (names[i][7] == 'g') {
                g_Status.gold = values[i];
            } else if (names[i][13] == 'm') {
                g_Status.heartsMax = values[i];
            } else {
                g_Status.hearts = values[i];
            }
            at[i] = ~0u;
            continue;
        }
        if (!strcmp(names[i], "status:subweapon")) {
            g_Status.subWeapon = values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:element", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":element")) {
            g_Entities[j].attackElement = (u16)values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:hitflags", &j) == 1 && j >= 0 && j < 256 &&
            strstr(names[i], ":hitflags")) {
            g_Entities[j].hitFlags = (u8)values[i];
            at[i] = ~0u;
            continue;
        }
        if (sscanf(names[i], "ent:%d:", &j) == 1 && j >= 0 && j < 256 &&
            (strstr(names[i], ":x") || strstr(names[i], ":y") ||
             strstr(names[i], ":facing"))) {
            if (strstr(names[i], ":facing")) {
                g_Entities[j].facingLeft = (u16)values[i];
            } else if (strstr(names[i], ":x")) {
                if (j == 0) {
                    g_PlayerX += (s16)values[i] - g_Entities[0].posX.i.hi;
                }
                g_Entities[j].posX.i.hi = (s16)values[i];
            } else {
                if (j == 0) {
                    g_PlayerY += (s16)values[i] - g_Entities[0].posY.i.hi;
                }
                g_Entities[j].posY.i.hi = (s16)values[i];
            }
            at[i] = ~0u;
            continue;
        }
        {
            char* plus = strchr(names[i], '+');
            if (plus) {
                *plus = 0;
                for (j = 0; sotn_fixed_symbols[j].name; j++) {
                    if (!strcmp(sotn_fixed_symbols[j].name, names[i])) {
                        sotn_fixed_symbols[j].data[strtoul(plus + 1, NULL, 0)] =
                            (uint8_t)values[i];
                        break;
                    }
                }
                *plus = '+';
                if (!sotn_fixed_symbols[j].name) {
                    satz_die(
                        "SOTN_SATZ_POKES: %s is not a fixed-address symbol",
                        names[i]);
                }
                at[i] = ~0u;
                continue;
            }
        }
        for (j = 0; sotn_fixed_symbols[j].name; j++) {
            if (!strcmp(sotn_fixed_symbols[j].name, names[i])) {
                *(s32*)sotn_fixed_symbols[j].data = (s32)values[i];
                break;
            }
        }
        if (!sotn_fixed_symbols[j].name) {
            satz_die(
                "SOTN_SATZ_POKES: %s is not a fixed-address symbol", names[i]);
        }
        at[i] = ~0u;
    }
}

static void sotn_satz_subweapon_blueprint(int subweapon) {
    extern SubweaponDef g_MariaSubweaponDefs[];
    static int bp = -2;

    if (bp == -2) {
        const char* v = getenv("SOTN_SATZ_BLUEPRINT");
        bp = v ? atoi(v) : -1;
    }
    if (bp >= 0) {
        g_MariaSubweaponDefs[subweapon].blueprintNum = bp;
        g_MariaSubweaponDefs[subweapon].heartCost = 0;
        g_MariaSubweaponDefs[subweapon].chainLimit = 99;
    }
}

extern const struct {
    const char* name;
    void (*run)(void);
} sotn_unit_table[];
static FILE* s_unit_out;
static unsigned s_unit_words;
static unsigned char s_unit_buf[0x100000];
void sotn_unit_out(int value) {
    if (s_unit_words < sizeof(s_unit_buf) / 4 - 1) {
        unsigned at = 4 + s_unit_words * 4;
        s_unit_buf[at] = (unsigned char)(value >> 24);
        s_unit_buf[at + 1] = (unsigned char)(value >> 16);
        s_unit_buf[at + 2] = (unsigned char)(value >> 8);
        s_unit_buf[at + 3] = (unsigned char)value;
        s_unit_words++;
    }
}
static void sotn_satz_unit(void) {
    static int state;
    static char name[64];
    static unsigned at;
    int k;
    if (state == 0) {
        const char* spec = getenv("SOTN_SATZ_UNIT");
        state = spec && sscanf(spec, "%63s %u", name, &at) == 2 ? 1 : 2;
    }
    if (state != 1 || sotn_satz_updates < at) {
        return;
    }
    state = 2;
    for (k = 0; sotn_unit_table[k].name; k++) {
        if (!strcmp(sotn_unit_table[k].name, name)) {
            break;
        }
    }
    if (!sotn_unit_table[k].name) {
        satz_die("SOTN_SATZ_UNIT: no unit test %s", name);
    }
    s_unit_words = 0;
    sotn_unit_table[k].run();
    s_unit_buf[0] = (unsigned char)(s_unit_words >> 24);
    s_unit_buf[1] = (unsigned char)(s_unit_words >> 16);
    s_unit_buf[2] = (unsigned char)(s_unit_words >> 8);
    s_unit_buf[3] = (unsigned char)s_unit_words;
    if (getenv("SOTN_SATZ_UNIT_OUT") &&
        (s_unit_out = fopen(getenv("SOTN_SATZ_UNIT_OUT"), "wb"))) {
        fwrite(s_unit_buf, 1, 4 + s_unit_words * 4, s_unit_out);
        fclose(s_unit_out);
    }
}

void sotn_satz_poll(void) {
    sotn_satz_unit();
    {
        static FILE* out = (FILE*)1;
        static int last = -1;
        if (out == (FILE*)1) {
            const char* path = getenv("SOTN_SATZ_COLTYPES");
            out = path ? fopen(path, "a") : NULL;
        }
        if (out && g_Tilemap.width > 0 && g_Tilemap.height > 0) {
            unsigned counts[256] = {0};
            unsigned b = (unsigned)(DAT_0605CD90[0].width * 4 / 5) / 2;
            unsigned rows = (unsigned)g_Tilemap.height >> 4;
            unsigned i, k;
            int key = (g_CurrentRoom.stageID << 16) ^ (g_Tilemap.width << 8) ^
                      g_Tilemap.height ^ (g_Tilemap.left << 24) ^
                      (g_Tilemap.top << 4);
            for (i = 0; i < b * rows && i < 0x10000; i++) {
                counts[DAT_0608FFF8[i]]++;
            }
            for (k = 0; k < 256; k++) {
                key = key * 31 + (int)counts[k] * (int)(k + 1);
            }
            if (key != last) {
                last = key;
                fprintf(out, "%d %d %d %d %d %d", g_CurrentRoom.stageID,
                        g_Tilemap.left, g_Tilemap.top, g_Tilemap.width,
                        g_Tilemap.height, b);
                for (k = 0; k < 256; k++) {
                    if (counts[k]) {
                        fprintf(out, " %02x:%u", k, counts[k]);
                    }
                }
                for (i = 0; i < b * rows && i < 0x10000; i++) {
                    if (DAT_0608FFF8[i] >= 0x84) {
                        fprintf(out, " @%02x:%u,%u", DAT_0608FFF8[i],
                                (i % b) * 20, (i / b) * 16);
                    }
                }
                fprintf(out, "\n");
                fflush(out);
            }
        }
    }
    {
        static const char* sym = (const char*)1;
        static int bytes, offset;
        static uint8_t* data;
        if (sym == (const char*)1) {
            const char* w = getenv("SOTN_SATZ_WATCH_SYM");
            sym = NULL;
            if (w && strchr(w, ':')) {
                static char name[64];
                int k;
                snprintf(
                    name, sizeof(name), "%.*s", (int)(strchr(w, ':') - w), w);
                bytes = atoi(strchr(w, ':') + 1);
                if (strchr(strchr(w, ':') + 1, ':')) {
                    offset = (int)strtol(strchr(w, ':') + 1, NULL, 0);
                    bytes = atoi(strchr(strchr(w, ':') + 1, ':') + 1);
                }
                for (k = 0; sotn_fixed_symbols[k].name; k++) {
                    if (!strcmp(sotn_fixed_symbols[k].name, name)) {
                        data = sotn_fixed_symbols[k].data;
                        sym = name;
                    }
                }
            }
        }
        if (sym && data) {
            int k;
            fprintf(stderr, "sym %u %s", sotn_satz_updates, sym);
            for (k = 0; k + 1 < bytes; k += 2) {
                fprintf(stderr, " %d", *(s16*)(data + offset + k));
            }
            fprintf(stderr, " pad %04x\n", g_Player.padPressed);
        }
    }
    {
        static int watch = -2;
        if (watch == -2) {
            const char* w = getenv("SOTN_SATZ_WATCH");
            watch = w ? atoi(w) : -1;
        }
        if (watch >= 0 && watch < 256) {
            Entity* e = &g_Entities[watch];
            fprintf(
                stderr,
                "watch %u slot %d id %d step %d/%d hp %d flags %08x hitbox %d "
                "hitFlags %02x x %d y %d "
                "maria %d %d vram %08x mstep %d/%d\n",
                sotn_satz_updates, watch, e->entityId, e->step, e->step_s,
                e->hitPoints, (unsigned)e->flags, e->hitboxState, e->hitFlags,
                e->posX.i.hi, e->posY.i.hi, g_Entities[0].posX.i.hi,
                g_Entities[0].posY.i.hi, (unsigned)g_Player.vram_flag,
                g_Entities[0].step, g_Entities[0].step_s);
        }
    }
    static int loaded;
    static unsigned polls[4096], subs[4096], bits[4096], count, next, held,
        last_updates = ~0u, since;
    static FILE* objects;
    const char* path;
    FILE* f;

    if (!loaded) {
        loaded = 1;
        if ((path = getenv("SOTN_SATZ_POLL_INPUTS")) &&
            (f = fopen(path, "r"))) {
            char key[32];

            while (
                count < 4096 && fscanf(f, "%31s %x", key, &bits[count]) == 2) {
                subs[count] = 0;
                if (sscanf(key, "%u:%u", &polls[count], &subs[count]) >= 1) {
                    count++;
                }
            }
            fclose(f);
        }
        if ((path = getenv("SOTN_SATZ_POLL_OBJECTS")) &&
            (objects = fopen(path, "w"))) {
            fputs("frame\tslot\tid\tx\ty\tvx\tvy\tfacing\tstep\tstep_s\tanim\n",
                  objects);
        }
    }
    s_Poll++;
    sotn_satz_poll_sync();
    sotn_satz_pokes(0);
    static long hooks_from = -1;
    if (hooks_from < 0) {
        const char* v = getenv("SOTN_SATZ_HOOKS_FROM");
        hooks_from = v ? atol(v) : 0;
    }
    if (sotn_satz_updates >= (unsigned long)hooks_from) {
        {
            static int god = -2;
            if (god == -2) {
                const char* v = getenv("SOTN_SATZ_GOD");
                god = v ? atoi(v) : -1;
            }
            if (god >= 0) {
                g_Status.hp = god;
                g_Status.mp = 200;
            }
        }
        {
            static int subweapon = -2;
            if (subweapon == -2) {
                const char* v = getenv("SOTN_SATZ_SUBWEAPON");
                subweapon = v ? atoi(v) : -1;
            }
            if (subweapon >= 0) {
                g_Status.subWeapon = subweapon;
                g_Status.hearts = 99;
                sotn_satz_subweapon_blueprint(subweapon);
            }
        }
    }
    since = sotn_satz_updates == last_updates ? since + 1 : 0;
    last_updates = sotn_satz_updates;
    if (count) {
        while (next < count &&
               (polls[next] < sotn_satz_updates ||
                (polls[next] == sotn_satz_updates && subs[next] <= since))) {
            held = bits[next++];
        }
        DAT_060505F8->buttons = ~held & 0xFFFF;
    }
    if (objects) {
        sotn_satz_dump_objects_to(objects, s_Poll);
        fprintf(objects, "%u\t-3\t0\t%u\t%llu\t%u\t0\t0\t0\t0\t0\n", s_Poll,
                ~DAT_060505F8->buttons & 0xFFFF, (unsigned long long)s_Frame,
                sotn_satz_updates);
    }
    sotn_satz_pokes(1);
}

int satz_app_fast_forward(void) {
    static int enabled = -1;

    if (enabled < 0) {
        enabled = getenv("SOTN_SATZ_FAST_LOAD") != NULL;
    }
    if (!enabled) {
        return 0;
    }
    if (DAT_0605D770.unk2 != 0) {
        return 1;
    }
    switch (DAT_0605cea0.unk2) {
    case 0x00:
    case 0x20:
    case 0x31:
        return 1;
    case 0x11:
        return DAT_0605cea0.unk0 < 3;
    }
    return 0;
}

void sotn_satz_sound_log(unsigned long long frame);

void satz_app_frame(uint64_t frame) {
    s_Frame = frame;
    if (s_DoorClear) {
        D_80097C98 = 0;
        s_DoorClear = 0;
    }
    sotn_satz_sound_log(frame);
    sotn_satz_watch(frame);
    sotn_satz_sync_seeds(frame);
    sotn_satz_lag(frame);
    sotn_satz_dump_objects(frame);

    static u32 last[9] = {~0u};
    u32 now[9] = {
        DAT_0605cea0.unk2,        DAT_0605cea0.unk0, g_CurrentRoom.stageID,
        (u32)g_PlayableCharacter, DAT_0605D770.unk2, DAT_0605D770.unk8,
        DAT_0605cd70.unk2,        DAT_0605cd70.unk0, g_CurrentRoom.unk4};

    if (memcmp(now, last, sizeof(now))) {
        fprintf(stderr,
                "frame %llu: st=%x sub=%x stage=%x chr=%x d772=%x d778=%x "
                "play=%x/%x layout=%x\n",
                (unsigned long long)frame, now[0], now[1], now[2], now[3],
                now[4], now[5], now[6], now[7], now[8]);
        memcpy(last, now, sizeof(now));
    }
    if (DAT_0605cea0.unk2 == 0x31 && DAT_0605cea0.unk0 >= 6) {
        DAT_0605D7F8 = 1;
    }
}
