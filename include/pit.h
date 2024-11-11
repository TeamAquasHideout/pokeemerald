#ifndef GUARD_PIT_H
#define GUARD_PIT_H

u16 ReturnLastSpokenVarObjGfxId();
void BufferMapFloorString();
void WarpToRandomPitArena(void);
void SetRandomBossEncounter(void);
const struct TrainerMon *GetRandomBossEncounterAcePokemon(void);
u16 GetRandomBossEncounterTrainerPic(void);
const u8 *GetRandomBossEncounterBossName(void);
const u8 *GetRandomBossEncounterBossApproachText(void);
const u8 *GetRandomBossEncounterBossDefeatText(void);
const u8 *GetRandomBossEncounterBossAceText(void);
u16 GetRandomMapTerrain(void);
u32 GetRandomMapWeather(void);
u16 GetRandomBattleWeather(void);
u16 GetCurrentMapConstant(void);
u16 GetPrimaryTilesetIdCurrentMap(void);
void CreateOverworldHUD(void);
void SetMapWeather(void);
void SetMapWeatherAtRandom(void);

struct RandomTrainerNPC 
{
    u16 gfxid;
    u16 objectflag;
    u16 trainerflag;
    u16 defeatTextVar;
};

#define MAX_RANDOM_TRAINERS 4
#define BOSS_FLOOR_RATE 25

//fixed value defines
#define OPTIONS_ON       0
#define OPTIONS_OFF      1
#define CASH_1X          0
#define CASH_2X          1
#define CASH_05X         2

//Autosave defines
#define SAVE_NO         0
#define SAVE_5_FLOORS   1
#define SAVE_EACH_FLOOR 2

extern const struct RandomTrainerNPC RandomNPCTrainers[];
extern const struct RandomTrainerNPC RandomNPCTrainers_Doubles[];

u16 ReturnAvatarMugshotId(u16 avatarId);
u16 ReturnAvatarGraphicsId(u16 avatarId);
u16 ReturnAvatarTrainerFrontPicId(u16 avatarId);
u16 ReturnAvatarTrainerBackPicId(u16 avatarId);

enum {
    AVATAR_BRENDAN,
    AVATAR_MAY,
    AVATAR_RED,
    AVATAR_LEAF,
    AVATAR_LUCAS,
    AVATAR_DAWN,
    AVATAR_ETHAN,
    AVATAR_LYRA,
    AVATAR_STEVEN,
    AVATAR_CYNTHIA,
    AVATAR_OAK,
    AVATAR_PHOEBE,
    AVATAR_POKEMON_CHOICE,
};

enum TilesetsPrimary
{
    TILESET_VANILLA,
    TILESET_WHITE_BARK,
    TILESET_DIRT_PATH,
    TILESET_MUSHROOM_WOODS,
    TILESET_WATER,
    TILESET_DESERT,
    TILESET_SNOW,
    TILESET_BEACH,
    TILESET_SPIDER_WOODS,
    TILESET_UNDERWATER,
    TILESET_MINE,
    TILESET_DEEP_FOREST,
    TILESET_CLOUDS,
};

#endif // GUARD_PIT_H
