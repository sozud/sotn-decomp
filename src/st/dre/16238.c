
#if 1
INCLUDE_ASM("st/dre/nonmatchings/16238", EntityUnkId21);
#else
extern u8 D_80180944[]; // Animation
void EntityCSMoveAlucard(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 posX;

    FntPrint("step %x\n", self->step);
    if ((D_801A3ED4 != 0) && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        if (g_DemoMode != Demo_None) {
            self->ext.generic.unk7C.s = 64;
        } else {
            self->ext.generic.unk7C.s = 128;
        }
        break;

    case 1:
        g_Player.padSim = 0;
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        if (g_Player.unk0C & 7) {
            if (g_Timer & 1) {
                if (g_Player.unk0C & 1) {
                    g_Player.padSim = 8;
                } else if (g_Player.unk0C & 2) {
                    g_Player.padSim = 4;
                } else if (g_Player.unk0C & 4) {
                    g_Player.padSim = 2;
                }
            }
        } else if (self->ext.generic.unk7C.u == 0) {
            self->step++;
            g_Player.padSim = 0x2000;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2: // Alucard walks forward
        g_Player.padSim = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(D_801A3F84 & 1)) {
                D_801A3F84 |= 1;
            }
        }
        if (posX > 288) {
            g_Player.padSim = 0;
            player->posX.i.hi = 288 -currentRoomTileLayout->scrollX.i.hi;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3: // Alucard stops walking
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        func_801961DC(0x20);
        if (D_801A3F84 & 2) {
            self->step++;
        }
        break;

    case 4:
        g_Player.padSim = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(D_801A3F84 & 1)) {
                D_801A3F84 |= 1;
            }
        }
        if (posX > 352) {
            g_Player.padSim = 0;
            player->posX.i.hi = 352 -currentRoomTileLayout->scrollX.i.hi;
            posX = 352;
            self->step++;
        }
        g_unkGraphicsStruct.unkC = posX - 256;
        g_Player.D_80072EFC = 1;
        break;

    case 5: // Conversation with fake lisa
        g_Player.D_80072EFC = 1;
        if (D_801A3F84 & 8) {
            SetStep(6);
        }
        break;

    case 6: // Alucard's reaction to realizing she's not his mother
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180944, self) == 0) {
            SetStep(7);
        } else {
            player->animCurFrame = self->animCurFrame;
        }
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (D_801A3F84 & 0x200) {
            SetStep(8);
        }
        break;

    case 8:
        func_801961DC(0x80);
        if (g_unkGraphicsStruct.unkC == 0x80) {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0  != 0) {
                g_unkGraphicsStruct.unk0  = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}


const u32 rodata_footer = 0;
#endif

// appears to load from the CD and freeze the game
INCLUDE_ASM("st/dre/nonmatchings/16238", EntityUnkId23);
