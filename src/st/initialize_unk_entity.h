// SPDX-License-Identifier: AGPL-3.0-or-later
static u8 g_UnkEntityAnimData[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};

void InitializeUnkEntity(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->opacity = 0xF0;
        self->rotX = 0x01A0;
        self->rotY = 0x01A0;
        self->animSet = ANIMSET_DRA(8);
        self->animCurFrame = 1;
        self->zPriority += 16;

        if (self->params) {
            self->palette = self->params;
        } else {
            self->palette = PAL_OVL(0x160);
        }

        self->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(g_UnkEntityAnimData, self)) {
            DestroyEntity(self);
        }
    }
}
