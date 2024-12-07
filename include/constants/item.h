#ifndef GUARD_ITEM_CONSTANTS_H
#define GUARD_ITEM_CONSTANTS_H

// These constants are used in gItems
#define POCKET_NONE         0
#define POCKET_KEY_ITEMS    1
#define POCKET_POKE_BALLS   2
#define POCKET_MEDICINE     3
#define POCKET_ITEMS        4
#define POCKET_BATTLE_ITEMS 5
#define POCKET_BERRIES      6
#define POCKET_POWER_UP     7
#define POCKET_TM_HM        8
#define POCKET_MEGA_STONES  9
#define POCKET_Z_CRYSTALS   10

#define KEYITEMS_POCKET     0
#define BALLS_POCKET        1
#define MEDICINE_POCKET     2
#define ITEMS_POCKET        3
#define BATTLEITEMS_POCKET  4
#define BERRIES_POCKET      5
#define POWERUP_POCKET      6
#define TMHM_POCKET         7
#define MEGASTONES_POCKET   8
#define ZCRYSTALS_POCKET    9
#ifdef PIT_GEN_9_MODE
#define POCKETS_COUNT       10
#else
#define POCKETS_COUNT       8
#endif

#define REPEL_LURE_MASK         (1 << 15)
#define IS_LAST_USED_LURE(var)  (var & REPEL_LURE_MASK)
#define REPEL_LURE_STEPS(var)   (var & (REPEL_LURE_MASK - 1))
#define LURE_STEP_COUNT         (IS_LAST_USED_LURE(VarGet(VAR_REPEL_STEP_COUNT)) ? REPEL_LURE_STEPS(VarGet(VAR_REPEL_STEP_COUNT)) : 0)
#define REPEL_STEP_COUNT        (!IS_LAST_USED_LURE(VarGet(VAR_REPEL_STEP_COUNT)) ? REPEL_LURE_STEPS(VarGet(VAR_REPEL_STEP_COUNT)) : 0)

#endif // GUARD_ITEM_CONSTANTS_H
