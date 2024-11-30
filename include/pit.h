#ifndef GUARD_PIT_H
#define GUARD_PIT_H

u16 GetLastSpokenVarObjTrainerArrayElement(void);
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
void UpdateRunningStats(void);
void IncrementStatsRunKOs(void);
void IncrementStatsRunRevives(void);
void ResetRunStats(void);
void SaveTempHofData(void);
u8 getNumberOfApproachTexts(void);
u8 getNumberOfDefeatTexts(void);
u16 GetRandomTrainerEncounterTrainerPic(void);
const u8 *GetRandomTrainerEncounterTrainerName(u16 trainerId);
const u8 GetRandomTrainerEncounterTrainerClass(void);

u16 AccessValidSpeciesArrayIndex(u16 index);
u16 GetIndexOfSpeciesInValidSpeciesArray(u16 species);

void RecieveGoldShield(void);
void RecieveSilverShield(void);

u16 GetRandomSecretBaseID(void);

struct RandomTrainerNPC 
{
    u16 arrayElement;
    u16 gfxid;
    u16 objectflag;
    u16 trainerflag;
    u16 defeatTextVar;
};

#define MAX_RANDOM_TRAINERS 4
#define MAX_TRAINER_OBJECTS 8
#define BOSS_FLOOR_RATE 25

//fixed value defines for game modes and options
#define OPTIONS_ON       0
#define OPTIONS_OFF      1
#define CASH_1X          0
#define CASH_2X          1
#define CASH_05X         2
#define MODE_SINGLES     0
#define MODE_DOUBLES     1
#define MODE_MIXED       2
#define HEAL_FLOORS_5    0
#define HEAL_FLOORS_10   1
#define RANDOM_B_WEATHER 0
#define OW_B_WEATHER     1
#define NO_B_WEATHER     2
#define XP_75            0
#define XP_50            1
#define XP_NONE          2

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
    AVATAR_NATE,
    AVATAR_ROSA,
    AVATAR_WALLY,
    AVATAR_LILLIE,
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
