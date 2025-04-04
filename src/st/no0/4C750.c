// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

static s16 D_us_80181C14[] = {0x50, 0x68, 0x70, 0x68, 0x50, 0x38, 0x30, 0x38};
static s16 D_us_80181C24[] = {0x90, 0x93, 0x9C, 0xA5, 0xA8, 0xA5, 0x9C, 0x93};

extern void func_us_801CC8F8(Entity*);

void func_us_801CC750(Entity* self) {
    Entity* entityPtr;
    s16 i;
    Primitive* prim;
    s32 primIndex;

    if (self->step != 0) {
        return;
    }

    InitializeEntity(D_us_80180A88);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
    if (primIndex != -1) {
        prim = &g_PrimBuf[primIndex];
        i = -0x10;
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x2A;
            prim->u0 = prim->u2 = 0xC0;
            prim->u1 = prim->u3 = 0xE0;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB0;
            prim->x0 = prim->x2 = i;
            prim->x1 = prim->x3 = i + 0x20;
            prim->y0 = prim->y1 = 0x91;
            prim->y2 = prim->y3 = 0xC1;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            i += 0x1E;
        }
    }

    entityPtr = &self[1];

    for (i = -0x10; i < 0x130; i += 0x60) {
        DestroyEntity(entityPtr);
        entityPtr->entityId = 0x16;
        entityPtr->pfnUpdate = func_us_801CC8F8;
        entityPtr->posY.i.hi = 0x8E;
        entityPtr->posX.i.hi = i;

        entityPtr++;
    }
}

void func_us_801CC8F8(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 3;
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x54;
        self->unk68 = 0xC0;
        self->flags &= ~FLAG_UNK_20000000;
        return;
    }

    if (self->posX.i.hi < -0x40) {
        self->posX.i.hi += 0x180;
    }

    if (self->posX.i.hi >= 0x141) {
        self->posX.i.hi -= 0x180;
    }
}

// updates entity movement direction
void func_us_801CC9B4(Entity* self) {
    s32 angleIndex;
    u8 adjustedAngle;

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 5;
        self->zPriority = 1;
        self->ext.et_801CC9B4.currentAngle = 0;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        return;
    }
    if (!(g_GameTimer & 0xF)) {
        angleIndex = (Random() & 7);
        self->ext.et_801CC9B4.targetAngle = GetAnglePointToEntityShifted(
            D_us_80181C14[angleIndex], D_us_80181C24[angleIndex]);
    }
    adjustedAngle = AdjustValueWithinThreshold(
        8U, (u8)self->ext.et_801CC9B4.currentAngle,
        (u8)self->ext.et_801CC9B4.targetAngle);
    SetEntityVelocityFromAngle(adjustedAngle & 0xFF, 4);
    MoveEntity();
    self->ext.et_801CC9B4.currentAngle = (u8)adjustedAngle;
}
