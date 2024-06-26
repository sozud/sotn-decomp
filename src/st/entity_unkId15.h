extern s16 unk15_rot[];
extern s32 unk15_yVel[];

// looks like a particle of dust fading away
void EntityUnkId15(Entity* self) {
    if (!self->step) {
        self->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = unk15_rot[self->params];
        self->rotY = self->rotX;
        self->velocityY = unk15_yVel[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->animFrameDuration++;
        if (!(self->animFrameDuration % 2)) {
            self->animCurFrame++;
        }
        if (self->animFrameDuration > 36) {
            DestroyEntity(self);
        }
    }
}
