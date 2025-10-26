#ifndef GUARD_ITEM_H
#define GUARD_ITEM_H

#include "config/general.h"
#include "constants/item.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/tms_hms.h"
#include "constants/item_effects.h"
#include "constants/hold_effects.h"


enum PACKED ItemSortType
{
    ITEM_TYPE_UNCATEGORIZED,
    ITEM_TYPE_FIELD_USE,
    ITEM_TYPE_LEVEL_UP_ITEM,
    ITEM_TYPE_HEALTH_RECOVERY,
    ITEM_TYPE_STATUS_RECOVERY,
    ITEM_TYPE_PP_RECOVERY,
    ITEM_TYPE_NATURE_MINT,
    ITEM_TYPE_STAT_BOOST_DRINK,
    ITEM_TYPE_STAT_BOOST_FEATHER,
    ITEM_TYPE_STAT_BOOST_MOCHI,
    ITEM_TYPE_BATTLE_ITEM,
    ITEM_TYPE_FLUTE,
    ITEM_TYPE_X_ITEM,
    ITEM_TYPE_AUX_ITEM,
    ITEM_TYPE_EVOLUTION_STONE,
    ITEM_TYPE_EVOLUTION_ITEM,
    ITEM_TYPE_SPECIAL_HELD_ITEM,
    ITEM_TYPE_MEGA_STONE,
    ITEM_TYPE_Z_CRYSTAL,
    ITEM_TYPE_TERA_SHARD,
    ITEM_TYPE_HELD_ITEM,
    ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
    ITEM_TYPE_CONTEST_HELD_ITEM,
    ITEM_TYPE_EV_BOOST_HELD_ITEM,
    ITEM_TYPE_GEM,
    ITEM_TYPE_PLATE,
    ITEM_TYPE_MEMORY,
    ITEM_TYPE_DRIVE,
    ITEM_TYPE_INCENSE,
    ITEM_TYPE_NECTAR,
    ITEM_TYPE_GROWTH,
    ITEM_TYPE_SHARD,
    ITEM_TYPE_SELLABLE,
    ITEM_TYPE_RELIC,
    ITEM_TYPE_FOSSIL,
    ITEM_TYPE_MAIL,
};

typedef void (*ItemUseFunc)(u8);

struct Item
{
    u32 price;
    u16 secondaryId;
    ItemUseFunc fieldUseFunc;
    const u8 *description;
    const u16 *effect;
    const u8 *name;
    const u8 *pluralName;
    u8 holdEffect;
    u8 holdEffectParam;
    u8 importance:2;
    u8 notConsumed:1;
    enum Pocket pocket:5;
    enum ItemSortType sortType;
    u8 type;
    u8 battleUsage;
    u8 flingPower;
    const u32 *iconPic;
    const u16 *iconPalette;
};

struct ALIGNED(2) BagPocket
{
    struct ItemSlot *itemSlots;
    u16 capacity:10;
    enum Pocket id:6;
};

extern const u8 gQuestionMarksItemName[];
extern const struct Item gItemsInfo[];
extern struct BagPocket gBagPockets[];

void BagPocket_SetSlotData(struct BagPocket *pocket, u32 pocketPos, struct ItemSlot newSlot);
struct ItemSlot BagPocket_GetSlotData(struct BagPocket *pocket, u32 pocketPos);

static inline void BagPocket_SetSlotItemIdAndCount(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity)
{
    BagPocket_SetSlotData(pocket, pocketPos, (struct ItemSlot) {itemId, quantity});
}

static inline u16 GetBagItemId(enum Pocket pocketId, u32 pocketPos)
{
    return BagPocket_GetSlotData(&gBagPockets[pocketId], pocketPos).itemId;
}

static inline u16 GetBagItemQuantity(enum Pocket pocketId, u32 pocketPos)
{
    return BagPocket_GetSlotData(&gBagPockets[pocketId], pocketPos).quantity;
}

static inline struct ItemSlot GetBagItemIdAndQuantity(enum Pocket pocketId, u32 pocketPos)
{
    return BagPocket_GetSlotData(&gBagPockets[pocketId], pocketPos);
}

void ApplyNewEncryptionKeyToBagItems(u32 newKey);
void SetBagItemsPointers(void);
u8 *CopyItemName(u16 itemId, u8 *dst);
u8 *CopyItemNameHandlePlural(u16 itemId, u8 *dst, u32 quantity);
bool32 IsBagPocketNonEmpty(enum Pocket pocketId);
bool32 CheckBagHasItem(u16 itemId, u16 count);
bool32 HasAtLeastOneBerry(void);
bool32 HasAtLeastOnePokeBall(void);
bool32 CheckBagHasSpace(u16 itemId, u16 count);
u32 GetFreeSpaceForItemInBag(u16 itemId);
bool32 AddBagItem(u16 itemId, u16 count);
bool32 RemoveBagItem(u16 itemId, u16 count);
u8 GetPocketByItemId(u16 itemId);
u8 SellsForBuyPrice(u16 itemId);
u8 CountUsedPCItemSlots(void);
bool32 CheckPCHasItem(u16 itemId, u16 count);
bool32 AddPCItem(u16 itemId, u16 count);
void RemovePCItem(u8 index, u16 count);
void CompactPCItems(void);
void SwapRegisteredBike(void);
void CompactItemsInBagPocket(enum Pocket pocketId);
void MoveItemSlotInPocket(enum Pocket pocketId, u32 from, u32 to);
void MoveItemSlotInPC(struct ItemSlot *itemSlots, u32 from, u32 to);
void ClearBag(void);
u16 CountTotalItemQuantityInBag(u16 itemId);
bool32 AddPyramidBagItem(u16 itemId, u16 count);
bool32 RemovePyramidBagItem(u16 itemId, u16 count);
const u8 *GetItemName(u16 itemId);
u32 GetItemPrice(u16 itemId);
const u16 *GetItemEffect(u32 itemId);
u32 GetItemHoldEffect(u32 itemId);
u32 GetItemHoldEffectParam(u32 itemId);
const u8 *GetItemDescription(u16 itemId);
const u8 *ItemId_GetTMData(u16 itemId);
bool8 IsTM(u16 itemId);
u8 GetItemImportance(u16 itemId);
u8 GetItemConsumability(u16 itemId);
enum Pocket GetItemPocket(u16 itemId);
u8 ItemId_GetType(u16 itemId);
ItemUseFunc ItemId_GetFieldFunc(u16 itemId);
u8 ItemId_GetBattleUsage(u16 itemId);
u8 ItemId_GetSecondaryId(u16 itemId);
u32 ItemId_GetFlingPower(u32 itemId);
u32 GetItemStatus2Mask(u16 itemId);
void DrawHeaderBox(void);
void HideHeaderBox(void);

//tx_randomizer_and_challenges
u16 RandomItemId(u16 itemId);
u16 RandomItem(void);
u16 RandomItemHidden(void);
u16 GetRandomHeldItemOpponent(void);

u8 GetItemType(u16 itemId);
ItemUseFunc GetItemFieldFunc(u16 itemId);
u8 GetItemBattleUsage(u16 itemId);
u32 GetItemSecondaryId(u32 itemId);
u32 GetItemFlingPower(u32 itemId);
u32 GetItemStatus1Mask(u16 itemId);
bool32 ItemHasVolatileFlag(u16 itemId, enum Volatile volatile);
u32 GetItemSellPrice(u32 itemId);
bool32 IsHoldEffectChoice(enum ItemHoldEffect holdEffect);

#endif // GUARD_ITEM_H
