// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 g_IsServantDestroyed;

#ifndef VERSION_PSP
/* func_us_80171864 uses pointers by a different naming scheme forcing
 * a breakout of ServantDesc.  Once that function is decompiled,
 * these structs should be able to be removed and the declaration
 * set to a  ServantDesc */
typedef struct {
    void (*Init)(s32 arg0);
    void (*Update)(Entity* self);
    void (*Unk08)(Entity* self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
} ServantDesc_Brk1;

typedef struct {
    
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity* self);
} ServantDesc_Brk2;

void func_us_80171624(s32 arg0);
void func_us_80171864(Entity* self);
void func_us_801720A4(Entity* self);
void func_us_801720AC(void);
void func_us_801720B4(void);
void func_us_801720BC(void);
void func_us_801720C4(void);
void func_us_801720CC(void);
void func_us_801720D4(void);
void func_us_801720DC(void);
void func_us_801720E4(Entity* self);
void func_us_8017246C(void);
void func_us_801728EC(void);
void func_us_801728F4(void);
void func_us_801728FC(void);
void DestroyServantEntity(Entity* self);



// glabel D_us_80170000
// /* 0 80170000 24161780 */ .word func_us_80171624
// /* 4 80170004 64181780 */ .word func_us_80171864
// /* 8 80170008 A4201780 */ .word func_us_801720A4
// /* C 8017000C AC201780 */ .word func_us_801720AC
// /* 10 80170010 B4201780 */ .word func_us_801720B4
// /* 14 80170014 BC201780 */ .word func_us_801720BC
// /* 18 80170018 C4201780 */ .word func_us_801720C4
// /* 1C 8017001C CC201780 */ .word func_us_801720CC
// /* 20 80170020 D4201780 */ .word func_us_801720D4
// /* 24 80170024 DC201780 */ .word func_us_801720DC
// .size D_us_80170000, . - D_us_80170000

// glabel D_us_80170028
// /* 28 80170028 E4201780 */ .word func_us_801720E4
// .size D_us_80170028, . - D_us_80170028

// glabel D_us_8017002C
// /* 2C 8017002C 6C241780 */ .word func_us_8017246C
// /* 30 80170030 EC281780 */ .word func_us_801728EC
// /* 34 80170034 F4281780 */ .word func_us_801728F4
// /* 38 80170038 FC281780 */ .word func_us_801728FC
// /* 3C 8017003C 04291780 */ .word DestroyServantEntity
// .size D_us_8017002C, . - D_us_8017002C

// glabel D_us_80170040
// /* 40 80170040 00000000 */ .word 0x00000000


ServantDesc_Brk1 g_ServantDesc_Brk1 = {
    func_us_80171624, func_us_80171864, func_us_801720A4, func_us_801720AC,
    func_us_801720B4, func_us_801720BC, func_us_801720C4, func_us_801720CC,
    func_us_801720D4, func_us_801720DC, func_us_801720E4, func_us_8017246C,
        func_us_801728EC, func_us_801728F4, func_us_801728FC,
    DestroyServantEntity
    };


const s32 pad = 0;

// void (*Unk28)(Entity* self) = &func_us_801720E4;
// void (*Unk2C)(/*?*/) = &func_us_8017246C;

// ServantDesc_Brk2 g_ServantDesc_Brk2 = {
//     func_us_801728EC, func_us_801728F4, func_us_801728FC,
//     DestroyServantEntity};
#endif

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

#include "../check_entity_valid.h"

void func_us_80171560(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171568);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171624);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171864);

void func_us_801720A4(Entity* self) {}

void func_us_801720AC(void) {}

void func_us_801720B4(void) {}

void func_us_801720BC(void) {}

void func_us_801720C4(void) {}

void func_us_801720CC(void) {}

void func_us_801720D4(void) {}

void func_us_801720DC(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801720E4);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017246C);

void func_us_801728EC(void) {}

void func_us_801728F4(void) {}

void func_us_801728FC(void) {}

#include "../destroy_servant_entity.h"

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C08);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C4C);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172CC0);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172EE8);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801732BC);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173378);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173490);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017353C);

INCLUDE_RODATA("servant/tt_001/nonmatchings/F84", func_us_80170F60);
