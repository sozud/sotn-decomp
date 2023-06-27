#ifndef RWRP_H
#define RWRP_H

#include "common.h"
#include "stage.h"

extern PfnEntityUpdate D_801803E0[];
extern u16 D_80180494[];
extern s16 D_80180A94[];
extern ObjInit2 D_80181134[];
extern LayoutObject* D_80195A30;
extern LayoutObject* D_80195A34;
void func_8018BD58(Entity*, LayoutObject*);

// *** EntitySoulStealOrb properties START ***

extern u16 D_801810A0[]; // NOTE(sestren): Random angle offsets?
extern u16 D_801810B0[]; // NOTE(sestren): Animation frame properties?
extern u16 D_8018044C[];
extern u16 D_80181110[];

// *** EntitySoulStealOrb properties END ***

#endif