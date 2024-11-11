#ifndef GUARD_UI_TRAINER_STATS_H
#define GUARD_UI_TRAINER_STATS_H

#include "main.h"

#define STATS_MODE_TRAINER_CARD 0
#define STATS_MODE_HALL_OF_FAME 1

void Task_OpenTrainerStats(u8 taskId);
void TrainerStats_Init(MainCallback callback, u8 mode);

#endif // GUARD_UI_TRAINER_STATS
