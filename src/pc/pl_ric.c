#include <game.h>

extern void (*D_8013C000)(void);
extern void (*D_8013C004)(s32);
extern void (*D_8013C008)(void);
extern void (*D_8013C00C)(void);

static void Stub_8013C004(int isPrologue) { func_80109594(); }

void UpdateEntityRichter(void);
void func_80156F40(s16 arg0);
void func_801603C4(void);
void func_8015E7B4(Unkstruct_8010BF64* arg0);

void InitPlayerRic(void) {
    g_PlayableCharacter = PLAYER_RICHTER;

    g_PlOvl.D_8013C000 = UpdateEntityRichter;
    g_PlOvl.D_8013C004 = func_80156F40;
    g_PlOvl.D_8013C008 = func_801603C4;
    g_PlOvl.D_8013C00C = func_8015E7B4;
}

// ric stubs
SubweaponDef D_80154688[] = {
    {0, 30000, 0, 0, 0, 0, 0, 0, 2, 1, 15, 0, 0},
    {20, 1, 4160, 3, 4, 4, 0, 43, 2, 129, 21, 0, 32},
    {50, 1, 4160, 3, 32, 4, 0, 19, 2, 129, 20, 0, 32},
    {5, 1, 32, 1, 32, 4, 0, 6, 2, 1, 16, 0, 0},
    {40, 1, 4128, 4, 32, 4, 0, 2, 2, 129, 12, 0, 0},
    {5, 5, 4096, 2, 24, 4, 0, 61, 2, 1, 26, 0, 0},
    {0, 10, 0, 1, 50, 0, 0, 63, 0, 0, 27, 0, 0},
    {40, 1, 4128, 3, 32, 4, 0, 50, 2, 1, 25, 0, 0},
    {20, 1, 4096, 3, 10, 4, 0, 49, 2, 1, 24, 0, 0},
    {20, 10, 20480, 1, 10, 10, 0, 51, 2, 129, 28, 0, 0},
    {15, 30000, 4096, 1, 10, 4, 0, 0, 2, 1, 10, 0, 0},
    {8, 1, 36864, 2, 16, 4, 0, 9, 2, 1, 0, 0, 0},
    {40, 20, 4128, 1, 32, 4, 0, 13, 2, 1, 0, 0, 0},
    {60, 0, 4128, 1, 24, 4, 0, 0, 2, 1, 0, 0, 0},
    {32, 5, 4128, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {64, 15, 36896, 1, 32, 4, 0, 0, 2, 1, 0, 0, 32},
    {80, 15, 4128, 1, 32, 24, 0, 12, 130, 1, 0, 0, 0},
    {80, 0, 32, 1, 32, 4, 0, 0, 2, 1, 0, 0, 32},
    {20, 0, 32, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {5, 0, 4128, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {40, 10, 4160, 1, 32, 4, 0, 41, 2, 129, 0, 0, 32},
    {20, 10, 4160, 1, 4, 4, 0, 44, 2, 129, 0, 0, 32},
    {80, 0, 32, 1, 32, 4, 0, 0, 2, 1, 0, 0, 32},
    {60, 0, 32, 1, 32, 4, 0, 0, 2, 1, 0, 0, 128},
    {20, 10, 4128, 1, 32, 4, 0, 54, 2, 1, 0, 0, 0},
    {20, 10, 32, 1, 32, 4, 0, 56, 2, 1, 0, 0, 0},
    {80, 15, 4128, 1, 32, 4, 0, 59, 2, 1, 0, 0, 0},
    {0, 20, 32, 1, 32, 32, 0, 65, 2, 1, 0, 0, 0},
    {80, 20, 16416, 1, 32, 4, 0, 67, 2, 1, 0, 0, 0},
    {10, 30000, 32, 1, 32, 4, 0, 0, 2, 1, 0, 0, 0},
    {15, 30000, 16416, 1, 32, 64, 0, 0, 2, 1, 0, 0, 0},
};

FactoryBlueprint g_RicFactoryBlueprints[78];
