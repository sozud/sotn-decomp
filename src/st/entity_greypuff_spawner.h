// SPDX-License-Identifier: AGPL-3.0-or-later
void EntityGreyPuffSpawner(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 index, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->entityId = E_GREY_PUFF;
            newEntity->pfnUpdate = EntityGreyPuff;
            newEntity->posX.i.hi = newX + i * xGap;
            newEntity->posY.i.hi = newY;
            newEntity->params = i;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
