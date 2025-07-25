// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

static AluFrame D_800CF748;
static AluFrame D_800CF750;
static AluFrame D_800CF758;
static AluFrame D_800CF760;
static AluFrame D_800CF768;
static AluFrame D_800CF770;
static AluFrame D_800CF778;
static AluFrame D_800CF780;
static AluFrame D_800CF788;
static AluFrame D_800CF790;
static AluFrame D_800CF798;
static AluFrame D_800CF7A0;
static AluFrame D_800CF7A8;
static AluFrame D_800CF7B0;
static AluFrame D_800CF7B8;
static AluFrame D_800CF7C0;
static AluFrame D_800CF7C8;
static AluFrame D_800CF7D0;
static AluFrame D_800CF7D8;
static AluFrame D_800CF7E0;
static AluFrame D_800CF7E8;
static AluFrame D_800CF7F0;
static AluFrame D_800CF7F8;
static AluFrame D_800CF800;
static AluFrame D_800CF808;
static AluFrame D_800CF810;
static AluFrame D_800CF818;
static AluFrame D_800CF820;
static AluFrame D_800CF828;
static AluFrame D_800CF830;
static AluFrame D_800CF838;
static AluFrame D_800CF840;
static AluFrame D_800CF848;
static AluFrame D_800CF850;
static AluFrame D_800CF858;
static AluFrame D_800CF860;
static AluFrame D_800CF868;
static AluFrame D_800CF870;
static AluFrame D_800CF878;
static AluFrame D_800CF880;
static AluFrame D_800CF888;
static AluFrame D_800CF890;
static AluFrame D_800CF898;
static AluFrame D_800CF8A0;
static AluFrame D_800CF8A8;
static AluFrame D_800CF8B0;
static AluFrame D_800CF8B8;
static AluFrame D_800CF8C0;
static AluFrame D_800CF8C8;
static AluFrame D_800CF8D0;
static AluFrame D_800CF8D8;
static AluFrame D_800CF8E0;
static AluFrame D_800CF8E8;
static AluFrame D_800CF8F0;
static AluFrame D_800CF8F8;
static AluFrame D_800CF900;
static AluFrame D_800CF908;
static AluFrame D_800CF910;
static AluFrame D_800CF918;
static AluFrame D_800CF920;
static AluFrame D_800CF928;
static AluFrame D_800CF930;
static AluFrame D_800CF938;
static AluFrame D_800CF940;
static AluFrame D_800CF948;
static AluFrame D_800CF950;
static AluFrame D_800CF958;
static AluFrame D_800CF960;
static AluFrame D_800CF968;
static AluFrame D_800CF970;
static AluFrame D_800CF978;
static AluFrame D_800CF980;
static AluFrame D_800CF988;
static AluFrame D_800CF990;
static AluFrame D_800CF998;
static AluFrame D_800CF9A0;
static AluFrame D_800CF9A8;
static AluFrame D_800CF9B0;
static AluFrame D_800CF9B8;
static AluFrame D_800CF9C0;
static AluFrame D_800CF9C8;
static AluFrame D_800CF9D0;
static AluFrame D_800CF9D8;
static AluFrame D_800CF9E0;
static AluFrame D_800CF9E8;
static AluFrame D_800CF9F0;
static AluFrame D_800CF9F8;
static AluFrame D_800CFA00;
static AluFrame D_800CFA08;
static AluFrame D_800CFA10;
static AluFrame D_800CFA18;
static AluFrame D_800CFA20;
static AluFrame D_800CFA28;
static AluFrame D_800CFA30;
static AluFrame D_800CFA38;
static AluFrame D_800CFA40;
static AluFrame D_800CFA48;
static AluFrame D_800CFA50;
static AluFrame D_800CFA58;
static AluFrame D_800CFA60;
static AluFrame D_800CFA68;
static AluFrame D_800CFA70;
static AluFrame D_800CFA78;
static AluFrame D_800CFA80;
static AluFrame D_800CFA88;
static AluFrame D_800CFA90;
static AluFrame D_800CFA98;
static AluFrame D_800CFAA0;
static AluFrame D_800CFAA8;
static AluFrame D_800CFAB0;
static AluFrame D_800CFAB8;
static AluFrame D_800CFAC0;
static AluFrame D_800CFAC8;
static AluFrame D_800CFAD0;
static AluFrame D_800CFAD8;
static AluFrame D_800CFAE0;
static AluFrame D_800CFAE8;
static AluFrame D_800CFAF0;
static AluFrame D_800CFAF8;
static AluFrame D_800CFB00;
static AluFrame D_800CFB08;
static AluFrame D_800CFB10;
static AluFrame D_800CFB18;
static AluFrame D_800CFB20;
static AluFrame D_800CFB28;
static AluFrame D_800CFB30;
static AluFrame D_800CFB38;
static AluFrame D_800CFB40;
static AluFrame D_800CFB48;
static AluFrame D_800CFB50;
static AluFrame D_800CFB58;
static AluFrame D_800CFB60;
static AluFrame D_800CFB68;
static AluFrame D_800CFB70;
static AluFrame D_800CFB78;
static AluFrame D_800CFB80;
static AluFrame D_800CFB88;
static AluFrame D_800CFB90;
static AluFrame D_800CFB98;
static AluFrame D_800CFBA0;
static AluFrame D_800CFBA8;
static AluFrame D_800CFBB0;
static AluFrame D_800CFBB8;
static AluFrame D_800CFBC0;
static AluFrame D_800CFBC8;
static AluFrame D_800CFBD0;
static AluFrame D_800CFBD8;
static AluFrame D_800CFBE0;
static AluFrame D_800CFBE8;
static AluFrame D_800CFBF0;
static AluFrame D_800CFBF8;
static AluFrame D_800CFC00;
static AluFrame D_800CFC08;
static AluFrame D_800CFC10;
static AluFrame D_800CFC18;
static AluFrame D_800CFC20;
static AluFrame D_800CFC28;
static AluFrame D_800CFC30;
static AluFrame D_800CFC38;
static AluFrame D_800CFC40;
static AluFrame D_800CFC48;
static AluFrame D_800CFC50;
static AluFrame D_800CFC58;
static AluFrame D_800CFC60;
static AluFrame D_800CFC68;
static AluFrame D_800CFC70;
static AluFrame D_800CFC78;
static AluFrame D_800CFC80;
static AluFrame D_800CFC88;
static AluFrame D_800CFC90;
static AluFrame D_800CFC98;
static AluFrame D_800CFCA0;
static AluFrame D_800CFCA8;
static AluFrame D_800CFCB0;
static AluFrame D_800CFCB8;
static AluFrame D_800CFCC0;
static AluFrame D_800CFCC8;
static AluFrame D_800CFCD0;
static AluFrame D_800CFCD8;
static AluFrame D_800CFCE0;
static AluFrame D_800CFCE8;
static AluFrame D_800CFCF0;
static AluFrame D_800CFCF8;
static AluFrame D_800CFD00;
static AluFrame D_800CFD08;
static AluFrame D_800CFD10;
static AluFrame D_800CFD18;
static AluFrame D_800CFD20;
static AluFrame D_800CFD28;
static AluFrame D_800CFD30;
static AluFrame D_800CFD38;
static AluFrame D_800CFD40;
static AluFrame D_800CFD48;
static AluFrame D_800CFD50;
static AluFrame D_800CFD58;
static AluFrame D_800CFD60;
static AluFrame D_800CFD68;
static AluFrame D_800CFD70;
static AluFrame D_800CFD78;
static AluFrame D_800CFD80;
static AluFrame D_800CFD88;
static AluFrame D_800CFD90;
static AluFrame D_800CFD98;
static AluFrame D_800CFDA0;
static AluFrame D_800CFDA8;
static AluFrame D_800CFDB0;
static AluFrame D_800CFDB8;
static AluFrame D_800CFDC0;
static AluFrame D_800CFDC8;
static AluFrame D_800CFDD0;
static AluFrame D_800CFDD8;
static AluFrame D_800CFDE0;
static AluFrame D_800CFDE8;
static AluFrame D_800CFDF0;
static AluFrame D_800CFDF8;
static AluFrame D_800CFE00;
static AluFrame D_800CFE08;
static AluFrame D_800CFE10;
static AluFrame D_800CFE18;
static AluFrame D_800CFE20;
static AluFrame D_800CFE28;
static AluFrame D_800CFE30;
static AluFrame D_800CFE38;
static AluFrame D_800CFE40;
#ifdef VERSION_PSP
static AluFrame D_psp_09234A30;
static AluFrame D_psp_09234A38;
static AluFrame D_psp_09234A40;
static AluFrame D_psp_09234A48;
static AluFrame D_psp_09234A50;
static AluFrame D_psp_09234A58;
static AluFrame D_psp_09234A60;
static AluFrame D_psp_09234A68;
static AluFrame D_psp_09234A70;
static AluFrame D_psp_09234A78;
static AluFrame D_psp_09234A80;
static AluFrame D_psp_09234A88;
static AluFrame D_psp_09234A90;
static AluFrame D_psp_09234A98;
static AluFrame D_psp_09234AA0;
static AluFrame D_psp_09234AA8;
static AluFrame D_psp_09234AB0;
static AluFrame D_psp_09234AB8;
static AluFrame D_psp_09234AC0;
static AluFrame D_psp_09234AC8;
static AluFrame D_psp_09234AD0;
static AluFrame D_psp_09234AD8;
static AluFrame D_psp_09234AE0;
static AluFrame D_psp_09234AE8;
static AluFrame D_psp_09234AF0;
static AluFrame D_psp_09234AF8;
static AluFrame D_psp_09234B00;
static AluFrame D_psp_09234B08;
static AluFrame D_psp_09234B10;
static AluFrame D_psp_09234B18;
static AluFrame D_psp_09234B20;
static AluFrame D_psp_09234B28;
static AluFrame D_psp_09234B30;
static AluFrame D_psp_09234B38;
static AluFrame D_psp_09234B40;
static AluFrame D_psp_09234B48;
static AluFrame D_psp_09234B50;
static AluFrame D_psp_09234B58;
static AluFrame D_psp_09234B60;
#endif

// clang-format off

AluFrame* D_800CF324[] = {
    NULL,        &D_800CF748, &D_800CF750, &D_800CF758, &D_800CF760,
    &D_800CF768, &D_800CF770, &D_800CF778, &D_800CF780, &D_800CF788,
    &D_800CF790, &D_800CF798, &D_800CF7A0, &D_800CF7A8, &D_800CF7B0,
    &D_800CF7B8, &D_800CF7C0, &D_800CF7C8, &D_800CF7D0, &D_800CF7D8,
    &D_800CF7E0, &D_800CF7E8, &D_800CF7F0, &D_800CF7F8, &D_800CF800,
    &D_800CF808, &D_800CF810, &D_800CF818, &D_800CF820, &D_800CF828,
    &D_800CF830, &D_800CF838, &D_800CF840, &D_800CF848, &D_800CF850,
    &D_800CF858, &D_800CF860, &D_800CF868, &D_800CF870, &D_800CF878,
    &D_800CF880, &D_800CF888, &D_800CF890, &D_800CF898, &D_800CF8A0,
    &D_800CF8A8, &D_800CF8B0, &D_800CF8B8, &D_800CF8C0, &D_800CF8C8,
    &D_800CF8D0, &D_800CF8D8, &D_800CF8E0, &D_800CF8E8, &D_800CF8F0,
    &D_800CF8F8, &D_800CF900, &D_800CF908, &D_800CF910, &D_800CF918,
    &D_800CF920, &D_800CF928, &D_800CF930, &D_800CF938, &D_800CF940,
    &D_800CF948, &D_800CF950, &D_800CF958, &D_800CF960, &D_800CF968,
    &D_800CF970, &D_800CF978, &D_800CF980, &D_800CF988, &D_800CF990,
    &D_800CF998, &D_800CF9A0, &D_800CF9A8, &D_800CF9B0, &D_800CF9B8,
    &D_800CF9C0, &D_800CF9C8, &D_800CF9D0, &D_800CF9D8, &D_800CF9E0,
    &D_800CF9E8, &D_800CF9F0, &D_800CF9F8, &D_800CFA00, &D_800CFA08,
    &D_800CFA10, &D_800CFA18, &D_800CFA20, &D_800CFA28, &D_800CFA30,
    &D_800CFA38, &D_800CFA40, &D_800CFA48, &D_800CFA50, &D_800CFA58,
    &D_800CFA60, &D_800CFA68, &D_800CFA70, &D_800CFA78, &D_800CFA80,
    &D_800CFA88, &D_800CFA90, &D_800CFA98, &D_800CFAA0, &D_800CFAA8,
    &D_800CFAB0, &D_800CFAB8, &D_800CFAC0, &D_800CFAC8, &D_800CFAD0,
    &D_800CFAD8, &D_800CFAE0, &D_800CFAE8, &D_800CFAF0, &D_800CFAF8,
    &D_800CFB00, &D_800CFB08, &D_800CFB10, &D_800CFB18, &D_800CFB20,
    &D_800CFB28, &D_800CFB30, &D_800CFB38, &D_800CFB40, &D_800CFB48,
    &D_800CFB50, &D_800CFB58, &D_800CFB60, &D_800CFB68, &D_800CFB70,
    &D_800CFB78, &D_800CFB80, &D_800CFB88, &D_800CFB90, &D_800CFB98,
    &D_800CFBA0, &D_800CFBA8, &D_800CFBB0, &D_800CFBB8, &D_800CFBC0,
    &D_800CFBC8, &D_800CFBD0, &D_800CFBD8, &D_800CFBE0, &D_800CFBE8,
    &D_800CFBF0, &D_800CFBF8, &D_800CFC00, &D_800CFC08, &D_800CFC10,
    &D_800CFC18, &D_800CFC20, &D_800CFC28, &D_800CFC30, &D_800CFC38,
    &D_800CFC40, &D_800CFC48, &D_800CFC50, &D_800CFC58, &D_800CFC60,
    &D_800CFC68, &D_800CFC70, &D_800CFC78, &D_800CFC80, &D_800CFC88,
    &D_800CFC90, &D_800CFC98, &D_800CFCA0, &D_800CFCA8, &D_800CFCB0,
    &D_800CFCB8, &D_800CFCC0, &D_800CFCC8, &D_800CFCD0, &D_800CFCD8,
    &D_800CFCE0, &D_800CFCE8, &D_800CFCF0, &D_800CFCF8, &D_800CFD00,
    &D_800CFD08, &D_800CFD10, &D_800CFD18, &D_800CFD20, &D_800CFD28,
    &D_800CFD30, &D_800CFD38, &D_800CFD40, &D_800CFD48, &D_800CFD50,
    &D_800CFD58, &D_800CFD60, &D_800CFD68, &D_800CFD70, &D_800CFD78,
    &D_800CFD80, &D_800CFD88, &D_800CFD90, &D_800CFD98, &D_800CFDA0,
    &D_800CFDA8, &D_800CFDB0, &D_800CFDB8, &D_800CFDC0, &D_800CFDC8,
    &D_800CFDD0, &D_800CFDD8, &D_800CFDE0, &D_800CFDE8, &D_800CFDF0,
    &D_800CFDF8, &D_800CFE00, &D_800CFE08, &D_800CFE10, &D_800CFE18,
    &D_800CFE20, &D_800CFE28, &D_800CFE30, &D_800CFE38, &D_800CFE40,
#ifdef VERSION_PSP
    &D_psp_09234A30, &D_psp_09234A38, &D_psp_09234A40, &D_psp_09234A48, &D_psp_09234A50,
    &D_psp_09234A58, &D_psp_09234A60, &D_psp_09234A68, &D_psp_09234A70, &D_psp_09234A78,
    &D_psp_09234A80, &D_psp_09234A88, &D_psp_09234A90, &D_psp_09234A98, &D_psp_09234AA0,
    &D_psp_09234AA8, &D_psp_09234AB0, &D_psp_09234AB8, &D_psp_09234AC0, &D_psp_09234AC8,
    &D_psp_09234AD0, &D_psp_09234AD8, &D_psp_09234AE0, &D_psp_09234AE8, &D_psp_09234AF0,
    &D_psp_09234AF8, &D_psp_09234B00, &D_psp_09234B08, &D_psp_09234B10, &D_psp_09234B18,
    &D_psp_09234B20, &D_psp_09234B28, &D_psp_09234B30, &D_psp_09234B38, &D_psp_09234B40,
    &D_psp_09234B48, &D_psp_09234B50, &D_psp_09234B58, &D_psp_09234B60, NULL,
#else
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10,
    &D_800CFE10, &D_800CFE10, &D_800CFE10, &D_800CFE10, NULL,
#endif
};

// clang-format on

static AluFrame D_800CF748 = {0x8000, -16, -23, 0};
static AluFrame D_800CF750 = {0x8001, -40, -31, 0};
static AluFrame D_800CF758 = {0x8002, -40, -31, 0};
static AluFrame D_800CF760 = {0x8003, -40, -31, 0};
static AluFrame D_800CF768 = {0x8004, -40, -31, 0};
static AluFrame D_800CF770 = {0x8005, -40, -31, 0};
static AluFrame D_800CF778 = {0x8006, -40, -31, 0};
static AluFrame D_800CF780 = {0x8007, -40, -31, 0};
static AluFrame D_800CF788 = {0x8008, -32, -15, 0};
static AluFrame D_800CF790 = {0x8009, -32, -7, 0};
static AluFrame D_800CF798 = {0x800A, -32, -7, 0};
static AluFrame D_800CF7A0 = {0x800B, -32, -7, 0};
static AluFrame D_800CF7A8 = {0x800C, -32, -7, 0};
static AluFrame D_800CF7B0 = {0x800D, -24, -7, 0};
static AluFrame D_800CF7B8 = {0x800E, -24, -7, 0};
static AluFrame D_800CF7C0 = {0x800F, -16, -15, 0};
static AluFrame D_800CF7C8 = {0x8010, -16, -23, 0};
static AluFrame D_800CF7D0 = {0x8011, -16, -23, 0};
static AluFrame D_800CF7D8 = {0x8012, -16, -23, 0};
static AluFrame D_800CF7E0 = {0x8013, -16, -23, 0};
static AluFrame D_800CF7E8 = {0x8014, -16, -23, 0};
static AluFrame D_800CF7F0 = {0x8015, -16, -23, 0};
static AluFrame D_800CF7F8 = {0x8016, -16, -23, 0};
static AluFrame D_800CF800 = {0x8017, -16, -23, 0};
static AluFrame D_800CF808 = {0x8018, -16, -23, 0};
static AluFrame D_800CF810 = {0x8019, -16, -23, 0};
static AluFrame D_800CF818 = {0x801A, -16, -23, 0};
static AluFrame D_800CF820 = {0x801B, -16, -23, 0};
static AluFrame D_800CF828 = {0x801C, -16, -23, 0};
static AluFrame D_800CF830 = {0x801D, -32, -31, 0};
static AluFrame D_800CF838 = {0x801E, -32, -31, 0};
static AluFrame D_800CF840 = {0x801F, -32, -31, 0};
static AluFrame D_800CF848 = {0x8020, -32, -31, 0};
static AluFrame D_800CF850 = {0x8021, -32, -31, 0};
static AluFrame D_800CF858 = {0x8022, -32, -31, 0};
static AluFrame D_800CF860 = {0x8023, -32, -31, 0};
static AluFrame D_800CF868 = {0x8024, -32, -31, 0};
static AluFrame D_800CF870 = {0x8025, -32, -31, 0};
static AluFrame D_800CF878 = {0x8026, -32, -31, 0};
static AluFrame D_800CF880 = {0x8027, -32, -31, 0};
static AluFrame D_800CF888 = {0x8028, -24, -23, 0};
static AluFrame D_800CF890 = {0x8029, -32, -31, 0};
static AluFrame D_800CF898 = {0x802A, -32, -31, 0};
static AluFrame D_800CF8A0 = {0x802B, -32, -31, 0};
static AluFrame D_800CF8A8 = {0x802C, -32, -31, 0};
static AluFrame D_800CF8B0 = {0x802D, -32, -31, 0};
static AluFrame D_800CF8B8 = {0x802E, -32, -31, 0};
static AluFrame D_800CF8C0 = {0x802F, -32, -31, 0};
static AluFrame D_800CF8C8 = {0x8030, -32, -31, 0};
static AluFrame D_800CF8D0 = {0x8031, -32, -31, 0};
static AluFrame D_800CF8D8 = {0x8032, -32, -31, 0};
static AluFrame D_800CF8E0 = {0x8033, -32, -31, 0};
static AluFrame D_800CF8E8 = {0x8034, -32, -31, 0};
static AluFrame D_800CF8F0 = {0x8035, -32, -31, 0};
static AluFrame D_800CF8F8 = {0x8036, -32, -31, 0};
static AluFrame D_800CF900 = {0x8037, -32, -31, 0};
static AluFrame D_800CF908 = {0x8038, -32, -31, 0};
static AluFrame D_800CF910 = {0x8039, -32, -31, 0};
static AluFrame D_800CF918 = {0x803A, -32, -31, 0};
static AluFrame D_800CF920 = {0x803B, -32, -31, 0};
static AluFrame D_800CF928 = {0x803C, -32, -31, 0};
static AluFrame D_800CF930 = {0x803D, -32, -31, 0};
static AluFrame D_800CF938 = {0x803E, -32, -31, 0};
static AluFrame D_800CF940 = {0x803F, -32, -31, 0};
static AluFrame D_800CF948 = {0x8040, -32, -31, 0};
static AluFrame D_800CF950 = {0x8041, -32, -31, 0};
static AluFrame D_800CF958 = {0x8042, -32, -23, 0};
static AluFrame D_800CF960 = {0x8043, -32, -31, 0};
static AluFrame D_800CF968 = {0x8044, -32, -31, 0};
static AluFrame D_800CF970 = {0x8045, -32, -31, 0};
static AluFrame D_800CF978 = {0x8046, -32, -31, 0};
static AluFrame D_800CF980 = {0x8047, -32, -31, 0};
static AluFrame D_800CF988 = {0x8048, -32, -31, 0};
static AluFrame D_800CF990 = {0x8049, -32, -31, 0};
static AluFrame D_800CF998 = {0x804A, -32, -31, 0};
static AluFrame D_800CF9A0 = {0x804B, -32, -31, 0};
static AluFrame D_800CF9A8 = {0x804C, -32, -31, 0};
static AluFrame D_800CF9B0 = {0x804D, -32, -31, 0};
static AluFrame D_800CF9B8 = {0x804E, -32, -31, 0};
static AluFrame D_800CF9C0 = {0x804F, -32, -23, 0};
static AluFrame D_800CF9C8 = {0x8050, -32, -31, 0};
static AluFrame D_800CF9D0 = {0x8051, -32, -31, 0};
static AluFrame D_800CF9D8 = {0x8052, -32, -31, 0};
static AluFrame D_800CF9E0 = {0x8053, -32, -31, 0};
static AluFrame D_800CF9E8 = {0x8054, -32, -31, 0};
static AluFrame D_800CF9F0 = {0x8055, -32, -23, 0};
static AluFrame D_800CF9F8 = {0x8056, -32, -31, 0};
static AluFrame D_800CFA00 = {0x8057, -32, -31, 0};
static AluFrame D_800CFA08 = {0x8058, -32, -31, 0};
static AluFrame D_800CFA10 = {0x8059, -32, -31, 0};
static AluFrame D_800CFA18 = {0x805A, -32, -31, 0};
static AluFrame D_800CFA20 = {0x805B, -32, -31, 0};
static AluFrame D_800CFA28 = {0x805C, -32, -31, 0};
static AluFrame D_800CFA30 = {0x805D, -32, -31, 0};
static AluFrame D_800CFA38 = {0x805E, -16, -31, 0};
static AluFrame D_800CFA40 = {0x805F, -16, -31, 0};
static AluFrame D_800CFA48 = {0x8060, -16, -31, 0};
static AluFrame D_800CFA50 = {0x8061, -16, -31, 0};
static AluFrame D_800CFA58 = {0x8062, -32, -31, 0};
static AluFrame D_800CFA60 = {0x8063, -32, -31, 0};
static AluFrame D_800CFA68 = {0x8064, -32, -31, 0};
static AluFrame D_800CFA70 = {0x8065, -32, -31, 0};
static AluFrame D_800CFA78 = {0x8066, -16, -31, 0};
static AluFrame D_800CFA80 = {0x8067, -16, -31, 0};
static AluFrame D_800CFA88 = {0x8068, -16, -31, 0};
static AluFrame D_800CFA90 = {0x8069, -40, -31, 0};
static AluFrame D_800CFA98 = {0x806A, -40, -31, 0};
static AluFrame D_800CFAA0 = {0x806B, -40, -31, 0};
static AluFrame D_800CFAA8 = {0x806C, -40, -31, 0};
static AluFrame D_800CFAB0 = {0x806D, -40, -31, 0};
static AluFrame D_800CFAB8 = {0x806E, -40, -31, 0};
static AluFrame D_800CFAC0 = {0x806F, -40, -31, 0};
static AluFrame D_800CFAC8 = {0x8070, -40, -39, 0};
static AluFrame D_800CFAD0 = {0x8071, -40, -39, 0};
static AluFrame D_800CFAD8 = {0x8072, -40, -39, 0};
static AluFrame D_800CFAE0 = {0x8073, -32, -31, 0};
static AluFrame D_800CFAE8 = {0x8074, -32, -31, 0};
static AluFrame D_800CFAF0 = {0x8075, -32, -31, 0};
static AluFrame D_800CFAF8 = {0x8076, -32, -31, 0};
static AluFrame D_800CFB00 = {0x8077, -32, -31, 0};
static AluFrame D_800CFB08 = {0x8078, -16, -23, 0};
static AluFrame D_800CFB10 = {0x8079, -16, -23, 0};
static AluFrame D_800CFB18 = {0x807A, -16, -23, 0};
static AluFrame D_800CFB20 = {0x807B, -8, -31, 0};
static AluFrame D_800CFB28 = {0x807C, -8, -31, 0};
static AluFrame D_800CFB30 = {0x807D, -8, -31, 0};
static AluFrame D_800CFB38 = {0x807E, -8, -31, 0};
static AluFrame D_800CFB40 = {0x807F, -8, -31, 0};
static AluFrame D_800CFB48 = {0x8080, -16, -7, 0};
static AluFrame D_800CFB50 = {0x8081, -16, -7, 0};
static AluFrame D_800CFB58 = {0x8082, -24, -5, 0};
static AluFrame D_800CFB60 = {0x8083, -24, -5, 0};
static AluFrame D_800CFB68 = {0x8084, -40, -31, 0};
static AluFrame D_800CFB70 = {0x8085, -40, -31, 0};
static AluFrame D_800CFB78 = {0x8086, -40, -31, 0};
static AluFrame D_800CFB80 = {0x8087, -40, -39, 0};
static AluFrame D_800CFB88 = {0x8088, -32, -39, 0};
static AluFrame D_800CFB90 = {0x8089, -32, -39, 0};
static AluFrame D_800CFB98 = {0x808A, -40, -39, 0};
static AluFrame D_800CFBA0 = {0x808B, -16, -31, 0};
static AluFrame D_800CFBA8 = {0x808C, -24, -39, 0};
static AluFrame D_800CFBB0 = {0x808D, -16, -31, 0};
static AluFrame D_800CFBB8 = {0x808E, -16, -31, 0};
static AluFrame D_800CFBC0 = {0x808F, -16, -31, 0};
static AluFrame D_800CFBC8 = {0x8090, -16, -31, 0};
static AluFrame D_800CFBD0 = {0x8091, -16, -31, 0};
static AluFrame D_800CFBD8 = {0x8092, -24, -23, 0};
static AluFrame D_800CFBE0 = {0x8093, -24, -23, 0};
static AluFrame D_800CFBE8 = {0x8094, -24, -23, 0};
static AluFrame D_800CFBF0 = {0x8095, -24, -23, 0};
static AluFrame D_800CFBF8 = {0x8096, -32, -31, 0};
static AluFrame D_800CFC00 = {0x8097, -32, -79, 0};
static AluFrame D_800CFC08 = {0x8098, -24, -31, 0};
static AluFrame D_800CFC10 = {0x8099, -32, -23, 0};
static AluFrame D_800CFC18 = {0x809A, -32, -23, 0};
static AluFrame D_800CFC20 = {0x809B, -24, -23, 0};
static AluFrame D_800CFC28 = {0x809C, -16, -23, 0};
static AluFrame D_800CFC30 = {0x809D, -27, -27, 0};
static AluFrame D_800CFC38 = {0x809E, -16, -31, 0};
static AluFrame D_800CFC40 = {0x809E, -16, -32, 0};
static AluFrame D_800CFC48 = {0x809F, -16, -31, 0};
static AluFrame D_800CFC50 = {0x80A0, -16, -31, 0};
static AluFrame D_800CFC58 = {0x80A1, -16, -31, 0};
static AluFrame D_800CFC60 = {0x80A1, -16, -32, 0};
static AluFrame D_800CFC68 = {0x80A2, -32, -31, 0};
static AluFrame D_800CFC70 = {0x80A2, -33, -31, 0};
static AluFrame D_800CFC78 = {0x80A3, -32, -31, 0};
static AluFrame D_800CFC80 = {0x80A3, -33, -31, 0};
static AluFrame D_800CFC88 = {0x80A4, -32, -31, 0};
static AluFrame D_800CFC90 = {0x80A4, -31, -31, 0};
static AluFrame D_800CFC98 = {0x80A5, -32, -31, 0};
static AluFrame D_800CFCA0 = {0x80A5, -31, -31, 0};
static AluFrame D_800CFCA8 = {0x80A6, -24, -23, 158};
static AluFrame D_800CFCB0 = {0x80A7, -11, -23, 159};
static AluFrame D_800CFCB8 = {0x80A8, -73, -47, 158};
static AluFrame D_800CFCC0 = {0x80A9, -32, -31, 0};
static AluFrame D_800CFCC8 = {0x80AA, -40, -31, 0};
static AluFrame D_800CFCD0 = {0x80AB, -40, -31, 0};
static AluFrame D_800CFCD8 = {0x80AC, -40, -31, 0};
static AluFrame D_800CFCE0 = {0x80AD, -32, -31, 0};
static AluFrame D_800CFCE8 = {0x80AE, -32, -31, 0};
static AluFrame D_800CFCF0 = {0x80AF, -32, -31, 0};
static AluFrame D_800CFCF8 = {0x80B0, -32, -31, 0};
static AluFrame D_800CFD00 = {0x80B1, -32, -31, 0};
static AluFrame D_800CFD08 = {0x80B2, -24, -31, 0};
static AluFrame D_800CFD10 = {0x80B3, -32, -23, 0};
static AluFrame D_800CFD18 = {0x80B4, -24, -23, 0};
static AluFrame D_800CFD20 = {0x80B5, -24, -31, 0};
static AluFrame D_800CFD28 = {0x80B6, -24, -31, 0};
static AluFrame D_800CFD30 = {0x80B7, -16, -23, 0};
static AluFrame D_800CFD38 = {0x80B8, -16, -23, 0};
static AluFrame D_800CFD40 = {0x80B9, -8, -23, 0};
static AluFrame D_800CFD48 = {0x80BA, -8, -23, 0};
static AluFrame D_800CFD50 = {0x80BB, -16, -23, 0};
static AluFrame D_800CFD58 = {0x80BC, -16, -23, 0};
static AluFrame D_800CFD60 = {0x80BD, -24, -7, 0};
static AluFrame D_800CFD68 = {0x80BE, -32, -7, 0};
static AluFrame D_800CFD70 = {0x80BF, -32, -7, 0};
static AluFrame D_800CFD78 = {0x80C0, -32, -7, 0};
static AluFrame D_800CFD80 = {0x80C1, -32, -15, 0};
static AluFrame D_800CFD88 = {0x80C2, -24, -7, 0};
static AluFrame D_800CFD90 = {0x80C3, -24, -7, 0};
static AluFrame D_800CFD98 = {0x80C4, -24, -7, 0};
static AluFrame D_800CFDA0 = {0x80C5, -16, -7, 0};
static AluFrame D_800CFDA8 = {0x80C6, -16, -7, 0};
static AluFrame D_800CFDB0 = {0x80C7, -16, -7, 0};
static AluFrame D_800CFDB8 = {0x80C8, -16, -7, 0};
static AluFrame D_800CFDC0 = {0x80C9, -32, -31, 0};
static AluFrame D_800CFDC8 = {0x80CA, -40, -31, 0};
static AluFrame D_800CFDD0 = {0x80CB, -32, -23, 0};
static AluFrame D_800CFDD8 = {0x80CC, -32, -23, 0};
static AluFrame D_800CFDE0 = {0x80CD, -40, -39, 0};
static AluFrame D_800CFDE8 = {0x80CE, -32, -39, 0};
static AluFrame D_800CFDF0 = {0x80CF, -32, -39, 0};
static AluFrame D_800CFDF8 = {0x80D0, -32, -47, 0};
static AluFrame D_800CFE00 = {0x80D1, -32, -47, 0};
static AluFrame D_800CFE08 = {0x80D2, -24, -15, 0};
static AluFrame D_800CFE10 = {0x80D3, -18, -22, 0};
static AluFrame D_800CFE18 = {0x80D4, -16, -22, 0};
static AluFrame D_800CFE20 = {0x80D5, -14, -22, 0};
static AluFrame D_800CFE28 = {0x80D6, -21, -21, 0};
static AluFrame D_800CFE30 = {0x80D7, -19, -21, 0};
static AluFrame D_800CFE38 = {0x80D8, -19, -21, 0};
static AluFrame D_800CFE40 = {0x80D9, -12, -20, 0};
#ifdef VERSION_PSP
static AluFrame D_psp_09234A30 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A38 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A40 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A48 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A50 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A58 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A60 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A68 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A70 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A78 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A80 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A88 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A90 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234A98 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AA0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AA8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AB0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AB8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AC0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AC8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AD0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AD8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AE0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AE8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AF0 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234AF8 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B00 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B08 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B10 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B18 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B20 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B28 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B30 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B38 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B40 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B48 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B50 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B58 = {0x0000, 0, 0, 0};
static AluFrame D_psp_09234B60 = {0x0000, 0, 0, 0};
#endif
