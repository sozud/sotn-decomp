// SPDX-License-Identifier: AGPL-3.0-or-later
#define E_UNK_DC 220
#define E_UNK_DF 223
// clang-format off
#define MAKE_EVENT(servant, roomX, roomY, camX, camY, check, delay, entity, params) \
    { 0, 0, servant, roomX, roomY, camX, camY, check, delay, entity, params, 1 }
#define NULL_EVENT \
    { 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0 }
ServantEvent g_Events[] = {
    NULL_EVENT,
    MAKE_EVENT(FAM_ACTIVE_BAT, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_GHOST, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 32, 40, 0, 4, FOR_CASTLE_FLAG(CHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_DEMON, -31, 20, 0, 772, FOR_CASTLE_FLAG(RCHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 32, 40, 0, 4, FOR_CASTLE_FLAG(CHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, -31, 20, 0, 772, FOR_CASTLE_FLAG(RCHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 48, E_UNK_DC, 1),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 21, 22, 150, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 60, 26, 0, 255, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 44, 18, 633, 772, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 10, 15, 790, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 39, 37, 0, 516, FOR_CASTLE_FLAG(NO4_SECRET_FLOOR_OPEN), 96, E_UNK_DC, 3),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 36, 27, 0, 4, FOR_CASTLE_FLAG(NO4_SECRET_WALL_OPEN), 256, E_UNK_DC, 4),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 12, 32, 0, 516, FOR_CASTLE_FLAG(NZ0_SECRET_WALL_OPEN), 160, E_UNK_DC, 5),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 12, 32, 0, 511, FOR_CASTLE_FLAG(NZ0_SECRET_FLOOR_OPEN), 32, E_UNK_DC, 6),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 27, 21, 512, 260, FOR_CASTLE_FLAG(NO2_SECRET_WALL_OPEN), 64, E_UNK_DC, 7),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 49, 18, 0, 4, FOR_CASTLE_FLAG(LIB_BOOKSHELF_SECRET), 512, E_UNK_DC, 8),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 50, 11, 0, 4, FOR_CASTLE_FLAG(NZ1_UPPER_WALL_OPEN), 32, E_UNK_DC, 9),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 43, 10, 0, 255, FOR_CASTLE_FLAG(NZ1_LOWER_WALL_OPEN), 0x80, E_UNK_DC, 10),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 48, E_UNK_DC, 1),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 21, 22, 150, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 60, 26, 0, 255, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 44, 18, 633, 772, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 10, 15, 790, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 39, 37, 0, 516, FOR_CASTLE_FLAG(NO4_SECRET_FLOOR_OPEN), 96, E_UNK_DC, 3),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 36, 27, 0, 4, FOR_CASTLE_FLAG(NO4_SECRET_WALL_OPEN), 256, E_UNK_DC, 4),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 12, 32, 0, 516, FOR_CASTLE_FLAG(NZ0_SECRET_WALL_OPEN), 160, E_UNK_DC, 5),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 12, 32, 0, 511, FOR_CASTLE_FLAG(NZ0_SECRET_FLOOR_OPEN), 32, E_UNK_DC, 6),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 27, 21, 512, 260, FOR_CASTLE_FLAG(NO2_SECRET_WALL_OPEN), 64, E_UNK_DC, 7),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 49, 18, 0, 4, FOR_CASTLE_FLAG(LIB_BOOKSHELF_SECRET), 512, E_UNK_DC, 8),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 50, 11, 0, 4, FOR_CASTLE_FLAG(NZ1_UPPER_WALL_OPEN), 32, E_UNK_DC, 9),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 43, 10, 0, 255, FOR_CASTLE_FLAG(NZ1_LOWER_WALL_OPEN), 128, E_UNK_DC, 10),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
#if defined(VERSION_HD)
    { 0, 0, -1, 1, -1, -1, -1, -1, -1, -1, 0, 0, 0 }
#else
    NULL_EVENT
#endif
};