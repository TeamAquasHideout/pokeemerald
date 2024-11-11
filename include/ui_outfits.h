#ifndef GUARD_UI_OUTFITS_H
#define GUARD_UI_OUTFITS_H

#include "main.h"

#define OUTFITS_NO_SAVE_AVATAR_MENU 0
#define OUTFITS_NORMAL_AVATAR_MENU 1

void Task_OpenOutfitsMenu(u8 taskId);
void OutfitsMenu_Init(MainCallback callback, u8 mode);

#endif // GUARD_UI_OUTFITS_H
