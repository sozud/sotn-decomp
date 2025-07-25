// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
