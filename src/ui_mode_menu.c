#include "gba/types.h"
#include "gba/defines.h"
#include "gba/isagbprint.h"
#include "global.h"
#include "main.h"
#include "bg.h"
#include "text_window.h"
#include "window.h"
#include "constants/characters.h"
#include "palette.h"
#include "task.h"
#include "overworld.h"
#include "malloc.h"
#include "gba/macro.h"
#include "menu_helpers.h"
#include "menu.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "strings.h"
#include "constants/rgb.h"
#include "decompress.h"
#include "constants/songs.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "pokemon_icon.h"
#include "graphics.h"
#include "data.h"
#include "pokedex.h"
#include "gpu_regs.h"
#include "ui_mode_menu.h"
#include "list_menu.h"
#include "international_string_util.h"
#include "event_data.h"
#include "constants/flags.h"
#include "ui_birch_case.h"
#include "config/general.h"
#include "main_menu.h"
#include "pit.h"


// This code is based on Ghoulslash's excellent UI tutorial:
// https://www.pokecommunity.com/showpost.php?p=10441093

struct ModeMenuState
{
    MainCallback savedCallback;
    u8 loadState;
};

enum WindowIds
{
    WIN_TOPBAR,
    WIN_OPTIONS,
    WIN_DESCRIPTION
};

enum MenuIds
{
    MENU_RUN,
    MENU_DIFF,
    MENU_RAND,
    MENU_PRESETS,
    MENU_COUNT
};

enum MenuItems_Run
{
    MENUITEM_RUN_SPECIES_ARRAY,
    MENUITEM_RUN_BATTLEMODE,
    MENUITEM_RUN_3_MONS_ONLY,
    MENUITEM_RUN_NO_CASE_CHOICE,
    MENUITEM_RUN_50_FLOORS,
    MENUITEM_RUN_INVERSE_BATTLES,
    MENUITEM_RUN_CANCEL,
    MENUITEM_RUN_COUNT,
};

enum MenuItems_Difficulty
{
    MENUITEM_DIFF_XPMODE,
    MENUITEM_DIFF_TRAINER_EVS,
    MENUITEM_DIFF_EVOSTAGE,
    MENUITEM_DIFF_MONOTYPE,
    MENUITEM_DIFF_DOUBLE_CASH,
    MENUITEM_DIFF_HEALFLOORS,
    MENUITEM_DIFF_LEGENDARIES,
#ifdef PIT_GEN_9_MODE
    MENUITEM_DIFF_TRAINER_GIMMICKS,
    MENUITEM_DIFF_MEGAS,
    MENUITEM_DIFF_DYNAMAX,
    MENUITEM_DIFF_TERA,
    MENUITEM_DIFF_ZMOVES,
#endif
    MENUITEM_DIFF_BOSS_HEAL,
    MENUITEM_DIFF_ITEM_DROPS,
    MENUITEM_DIFF_STAT_CHANGER,
    MENUITEM_DIFF_NO_BAG_USE,
    MENUITEM_DIFF_CANCEL,
    MENUITEM_DIFF_COUNT,
};

enum MenuItems_Randomizer
{
    MENUITEM_RAND_MOVES,
    MENUITEM_RAND_ABILITIES,
    MENUITEM_RAND_BASE_STATS,
    MENUITEM_RAND_TYPES,
    MENUITEM_RAND_EVOS,
    MENUITEM_RAND_B_WEATHER,
    MENUITEM_RAND_CANCEL,
    MENUITEM_RAND_COUNT,
};

enum MenuItems_Presets
{
    MENUITEM_PRESET_MODE,
    MENUITEM_PRESET_CANCEL,
    MENUITEM_PRESET_SAVE,
    MENUITEM_PRESET_COUNT,
};

enum Game_Presets
{
    PRESET_NORMAL,
    PRESET_HARD
};

static EWRAM_DATA struct ModeMenuState *sModeMenuState = NULL;

static const struct BgTemplate sModeMenuBgTemplates[] =
{
    {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
    },
    {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
    },
    {
       .bg = 2,
       .charBaseIndex = 0,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
    },
    {
       .bg = 3,
       .charBaseIndex = 3,
       .mapBaseIndex = 27,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
    },
};

static const struct WindowTemplate sModeMenuWindowTemplates[] =
{
    [WIN_TOPBAR] =
    {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] =
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 10,
        .paletteNum = 1,
        .baseBlock = 62
    },
    [WIN_DESCRIPTION] = 
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 1,
        .baseBlock = 500
    },
    DUMMY_WIN_TEMPLATE
};

//
//  Graphics Pointers to Tilemaps, Tilesets, Spritesheets, Palettes
//

// EWRAM vars
EWRAM_DATA static struct ModeMenu *sOptions = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg3TilemapBuffer = NULL;
//static EWRAM_DATA u8 *statePresets = 0;

// const data
static const u8 sEqualSignGfx[]      = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp"); // note: this is only used in the Japanese release
static const u16 sModeMenuBg_Pal[]   = {RGB(17, 18, 31)};
static const u16 sModeMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");
static const u8 sLR_ButtonGfx[]      = INCBIN_U8("graphics/ui_menu/r_button.4bpp");

static const u32 sOptionsPlusTiles[]   = INCBIN_U32("graphics/ui_mode_menu/mode_menu_tiles.4bpp.lz");
static const u16 sOptionsPlusPalette[] = INCBIN_U16("graphics/ui_mode_menu/mode_menu_tiles.gbapal");
static const u32 sOptionsPlusTilemap[] = INCBIN_U32("graphics/ui_mode_menu/mode_menu_tiles.bin.lz");

// Scrolling Background
static const u32 sScrollBgTiles[]   = INCBIN_U32("graphics/ui_mode_menu/scroll_tiles.4bpp.lz");
static const u32 sScrollBgTilemap[] = INCBIN_U32("graphics/ui_mode_menu/scroll_tiles.bin.lz");
static const u16 sScrollBgPalette[] = INCBIN_U16("graphics/ui_mode_menu/scroll_tiles.gbapal");

#define TEXT_COLOR_OPTIONS_WHITE                1
#define TEXT_COLOR_OPTIONS_GRAY_FG              2
#define TEXT_COLOR_OPTIONS_GRAY_SHADOW          3
#define TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG        4
#define TEXT_COLOR_OPTIONS_ORANGE_FG            5
#define TEXT_COLOR_OPTIONS_ORANGE_SHADOW        6
#define TEXT_COLOR_OPTIONS_RED_FG               7
#define TEXT_COLOR_OPTIONS_RED_SHADOW           8
#define TEXT_COLOR_OPTIONS_GREEN_FG             9
#define TEXT_COLOR_OPTIONS_GREEN_SHADOW         10
#define TEXT_COLOR_OPTIONS_GREEN_DARK_FG        11
#define TEXT_COLOR_OPTIONS_GREEN_DARK_SHADOW    12
#define TEXT_COLOR_OPTIONS_RED_DARK_FG          13
#define TEXT_COLOR_OPTIONS_RED_DARK_SHADOW      14

struct ModeMenu
{
    u16 submenu;
    u8 sel_run[MENUITEM_RUN_COUNT];
    u8 sel_diff[MENUITEM_DIFF_COUNT];
    u8 sel_rand[MENUITEM_RAND_COUNT];
    u8 sel_presets[MENUITEM_PRESET_COUNT];
    s8 menuCursor[MENU_COUNT + 1];
    s8 visibleCursor[MENU_COUNT + 1];
    u8 arrowTaskId;
    u8 gfxLoadState;
};

#define Y_DIFF 16 // Difference in pixels between items.
#define OPTIONS_ON_SCREEN 5
#define NUM_OPTIONS_FROM_BORDER 1

//
//  local functions
//

// Callbacks for the sample UI
static void ModeMenu_SetupCB(void);
static void ModeMenu_MainCB(void);
static void ModeMenu_VBlankCB(void);

// Sample UI tasks
static void Task_ModeMenuWaitFadeIn(u8 taskId);
static void Task_ModeMenuMainInput(u8 taskId);
static void Task_ModeMenuSave(u8 taskId);
static void Task_ModeMenuWaitFadeAndExitGracefully(u8 taskId);

// Sample UI helper functions
void ModeMenu_Init(MainCallback callback);
static const u8 *const OptionTextRight(u8 menuItem);
static bool8 CheckConditions(int selection);
static void DrawTopBarText(void); //top Option text
static void DrawLeftSideOptionText(int selection, int y);
static void DrawRightSideChoiceText(const u8 *str, int x, int y, bool8 chosen, bool8 active);
static void DrawDescriptionText(void);
static void DrawModeMenuTexts(void); //left side text;
static void DrawChoices(u8 id, int y); //right side draw function
static void HighlightModeMenuItem(void);
static bool8 ModeMenu_LoadGraphics(void);
static void ModeMenu_FreeResources(void);
static void ScrollMenu(int direction);
static void ScrollAll(int direction); // to bottom or top
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3);
static int XOptions_ProcessInput(int x, int selection);
static int ProcessInput_Options_Two(int selection);
static int ProcessInput_Options_Three(int selection);
static int ProcessInput_Options_Eighteen(int selection);
static int ProcessInput_Options_Nineteen(int selection);
static void ReDrawAll(void);
//static void DrawChoices_Autosave(int selection, int y);
static void DrawChoices_SpeciesArray(int selection, int y);
static void DrawChoices_BattleMode(int selection, int y);
//static void DrawChoices_Randomizer(int selection, int y);
static void DrawChoices_3MonsOnly(int selection, int y);
static void DrawChoices_50Floors(int selection, int y);
static void DrawChoices_InverseBattles(int selection, int y);
static void DrawChoices_NoCaseChoice(int selection, int y);
static void DrawChoices_BossHeal(int selection, int y);
static void DrawChoices_ItemDrops(int selection, int y);
static void DrawChoices_DoubleCash(int selection, int y);
static void DrawChoices_TrainerGimmicks(int selection, int y);
static void DrawChoices_EvoStage(int selection, int y);
static void DrawChoices_MonoType(int selection, int y);
static void DrawChoices_RandBattleWeather(int selection, int y);
static void DrawChoices_RandMoves(int selection, int y);
static void DrawChoices_RandAbilities(int selection, int y);
static void DrawChoices_RandStats(int selection, int y);
static void DrawChoices_RandTypes(int selection, int y);
static void DrawChoices_RandEvos(int selection, int y);
static void DrawChoices_XPMode(int selection, int y);
static void DrawChoices_StatChanger(int selection, int y);
static void DrawChoices_TrainerEVs(int selection, int y);
static void DrawChoices_Legendaries(int selection, int y);
static void DrawChoices_Duplicates(int selection, int y);
static void DrawChoices_Megas(int selection, int y);
static void DrawChoices_ZMoves(int selection, int y);
static void DrawChoices_HealFloors(int selection, int y);
static void DrawChoices_NoBagUse(int selection, int y);
static void DrawChoices_Dynamax(int selection, int y);
static void DrawChoices_Tera(int selection, int y);
static void DrawChoices_PresetsMode(int selection, int y);
static void DrawBgWindowFrames(void);
static void ApplyPresets(void);

// Menu draw and input functions
struct Menu_Run //MENU_RUN
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsRun[MENUITEM_RUN_COUNT] =
{
    [MENUITEM_RUN_SPECIES_ARRAY]   = {DrawChoices_SpeciesArray,   ProcessInput_Options_Two},
    [MENUITEM_RUN_BATTLEMODE]      = {DrawChoices_BattleMode,     ProcessInput_Options_Three},
    [MENUITEM_RUN_3_MONS_ONLY]     = {DrawChoices_3MonsOnly,      ProcessInput_Options_Two},
    [MENUITEM_RUN_NO_CASE_CHOICE]  = {DrawChoices_NoCaseChoice,   ProcessInput_Options_Two},
    [MENUITEM_RUN_50_FLOORS]       = {DrawChoices_50Floors,       ProcessInput_Options_Two},
    [MENUITEM_RUN_INVERSE_BATTLES] = {DrawChoices_InverseBattles, ProcessInput_Options_Two},
    [MENUITEM_RUN_CANCEL]          = {NULL, NULL},
};

struct Menu_Diff //MENU_DIFF
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsDiff[MENUITEM_DIFF_COUNT] =
{
    [MENUITEM_DIFF_XPMODE]        = {DrawChoices_XPMode,       ProcessInput_Options_Three},
    [MENUITEM_DIFF_TRAINER_EVS]   = {DrawChoices_TrainerEVs,   ProcessInput_Options_Two},
    [MENUITEM_DIFF_EVOSTAGE]      = {DrawChoices_EvoStage,     ProcessInput_Options_Three},
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_MONOTYPE]      = {DrawChoices_MonoType,     ProcessInput_Options_Nineteen},
#else
    [MENUITEM_DIFF_MONOTYPE]      = {DrawChoices_MonoType,     ProcessInput_Options_Eighteen},
#endif
    [MENUITEM_DIFF_STAT_CHANGER]  = {DrawChoices_StatChanger,  ProcessInput_Options_Two},
    [MENUITEM_DIFF_DOUBLE_CASH]   = {DrawChoices_DoubleCash,   ProcessInput_Options_Three},
    [MENUITEM_DIFF_HEALFLOORS]    = {DrawChoices_HealFloors,   ProcessInput_Options_Two},
    [MENUITEM_DIFF_LEGENDARIES]   = {DrawChoices_Legendaries,  ProcessInput_Options_Two},
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_TRAINER_GIMMICKS]   = {DrawChoices_TrainerGimmicks,   ProcessInput_Options_Three},
    [MENUITEM_DIFF_MEGAS]         = {DrawChoices_Megas,        ProcessInput_Options_Two},
    [MENUITEM_DIFF_ZMOVES]        = {DrawChoices_ZMoves,        ProcessInput_Options_Two},
#endif
    [MENUITEM_DIFF_BOSS_HEAL]     = {DrawChoices_BossHeal,     ProcessInput_Options_Two},
    [MENUITEM_DIFF_ITEM_DROPS]    = {DrawChoices_ItemDrops,    ProcessInput_Options_Three},
    [MENUITEM_DIFF_NO_BAG_USE]    = {DrawChoices_NoBagUse,     ProcessInput_Options_Two},
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_DYNAMAX]       = {DrawChoices_Dynamax,      ProcessInput_Options_Two},
    [MENUITEM_DIFF_TERA]          = {DrawChoices_Tera,         ProcessInput_Options_Two},
#endif
    [MENUITEM_DIFF_CANCEL]        = {NULL, NULL},
};

struct Menu_Rand //MENU_RAND
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsRand[MENUITEM_RAND_COUNT] =
{
    [MENUITEM_RAND_B_WEATHER]  = {DrawChoices_RandBattleWeather,    ProcessInput_Options_Three},
    [MENUITEM_RAND_MOVES]      = {DrawChoices_RandMoves,            ProcessInput_Options_Two},
    [MENUITEM_RAND_ABILITIES]  = {DrawChoices_RandAbilities,        ProcessInput_Options_Two},
    [MENUITEM_RAND_BASE_STATS] = {DrawChoices_RandStats,            ProcessInput_Options_Two},
    [MENUITEM_RAND_TYPES]      = {DrawChoices_RandTypes,            ProcessInput_Options_Two},
    [MENUITEM_RAND_EVOS]       = {DrawChoices_RandEvos,             ProcessInput_Options_Two},
    [MENUITEM_RAND_CANCEL]     = {NULL, NULL},
};

struct Menu_Presets //MENU_PRESETS
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsPresets[MENUITEM_PRESET_COUNT] =
{
    [MENUITEM_PRESET_MODE] = {DrawChoices_PresetsMode,     ProcessInput_Options_Two},
    [MENUITEM_PRESET_CANCEL] = {NULL, NULL},
    [MENUITEM_PRESET_SAVE]   = {NULL, NULL},
};

// Menu left side option names text
static const u8 sText_Defaults[]     = _("PRESETS");
static const u8 sText_Autosave[]     = _("AUTOSAVE");
static const u8 sText_SpeciesArray[] = _("TRAINER TEAMS");
static const u8 sText_BattleMode[]   = _("BATTLE MODE");
static const u8 sText_Randomizer[]   = _("RANDOMIZER");
static const u8 sText_XPMode[]       = _("XP MODE");
static const u8 sText_StatChanger[]  = _("STAT CHANGER");
static const u8 sText_TrainerEVs[]   = _("TRAINER EVS");
static const u8 sText_Legendaries[]  = _("LEGENDARIES");
static const u8 sText_Duplicates[]   = _("DUPLICATES");
static const u8 sText_Megas[]        = _("MEGA EVO");
static const u8 sText_HealFloors[]   = _("HEAL FLOORS");
static const u8 sText_ItemDrops[]    = _("ITEM DROPS");
static const u8 sText_NoBagUse[]     = _("BAG IN BATTLE");
static const u8 sText_Dynamax[]      = _("DYNAMAX");
static const u8 sText_Tera[]         = _("TERASTAL");
static const u8 sText_ZMoves[]         = _("Z-MOVES");

static const u8 sText_3MonsOnly[]      = _("3 MONS ONLY");
static const u8 sText_NoCaseChoice[]   = _("NO BIRCH CASE");
static const u8 sText_BossHeal[]       = _("BOSS HEALS");
static const u8 sText_DoubleCash[]     = _("CASH RATE");
static const u8 sText_EvoStage[]       = _("EVO STAGES");
static const u8 sText_TrainerGimmicks[]       = _("FOE GIMMICKS");
static const u8 sText_MonoType[]       = _("MONO TYPE");
static const u8 sText_50Floors[]       = _("50 FLOORS");
static const u8 sText_InverseBattles[] = _("INVERSE BTLS");

static const u8 sText_B_Weather[]    = _("BATTLE WEATHER");
static const u8 sText_Moves[]        = _("MOVES");
static const u8 sText_Abilities[]    = _("ABILITIES");
static const u8 sText_BaseStats[]    = _("BASE STATS");
static const u8 sText_Types[]        = _("TYPES");
static const u8 sText_Evos[]         = _("EVOLUTIONS");
static const u8 sText_Cancel[]       = _("SAVE & LEAVE");

static const u8 sText_GameMode[]     = _("GAME MODE");
static const u8 sText_CancelPreset[] = _("CANCEL&RETURN");
static const u8 sText_SavePreset[]   = _("SAVE PRESETS");

static const u8 *const sModeMenuItemsNamesRun[MENUITEM_RUN_COUNT] =
{
    [MENUITEM_RUN_SPECIES_ARRAY]   = sText_SpeciesArray,
    [MENUITEM_RUN_BATTLEMODE]      = sText_BattleMode,
    [MENUITEM_RUN_3_MONS_ONLY]     = sText_3MonsOnly,
    [MENUITEM_RUN_NO_CASE_CHOICE]  = sText_NoCaseChoice,
    [MENUITEM_RUN_50_FLOORS]       = sText_50Floors,
    [MENUITEM_RUN_INVERSE_BATTLES] = sText_InverseBattles,
    [MENUITEM_RUN_CANCEL]          = sText_Cancel,
};

static const u8 *const sModeMenuItemsNamesDiff[MENUITEM_DIFF_COUNT] =
{
    [MENUITEM_DIFF_XPMODE]        = sText_XPMode,
    [MENUITEM_DIFF_TRAINER_EVS]   = sText_TrainerEVs,
    [MENUITEM_DIFF_EVOSTAGE]      = sText_EvoStage,
    [MENUITEM_DIFF_MONOTYPE]      = sText_MonoType,
    [MENUITEM_DIFF_STAT_CHANGER]  = sText_StatChanger,
    [MENUITEM_DIFF_DOUBLE_CASH]   = sText_DoubleCash,
    [MENUITEM_DIFF_HEALFLOORS]    = sText_HealFloors,
    [MENUITEM_DIFF_LEGENDARIES]   = sText_Legendaries,
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_TRAINER_GIMMICKS] = sText_TrainerGimmicks,
    [MENUITEM_DIFF_MEGAS]         = sText_Megas,
    [MENUITEM_DIFF_ZMOVES]        = sText_ZMoves,
#endif
    [MENUITEM_DIFF_BOSS_HEAL]     = sText_BossHeal,
    [MENUITEM_DIFF_ITEM_DROPS]    = sText_ItemDrops,
    [MENUITEM_DIFF_NO_BAG_USE]    = sText_NoBagUse,
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_DYNAMAX]       = sText_Dynamax,
    [MENUITEM_DIFF_TERA]          = sText_Tera,
#endif
    [MENUITEM_DIFF_CANCEL]        = sText_Cancel,
};

static const u8 *const sModeMenuItemsNamesRand[MENUITEM_RAND_COUNT] =
{
    [MENUITEM_RAND_B_WEATHER]  = sText_B_Weather,
    [MENUITEM_RAND_MOVES]      = sText_Moves,
    [MENUITEM_RAND_ABILITIES]  = sText_Abilities,
    [MENUITEM_RAND_BASE_STATS] = sText_BaseStats,
    [MENUITEM_RAND_TYPES]      = sText_Types,
    [MENUITEM_RAND_EVOS]       = sText_Evos,
    [MENUITEM_RAND_CANCEL]     = sText_Cancel,
};

static const u8 *const sModeMenuItemsNamesPresets[MENUITEM_PRESET_COUNT] =
{
    [MENUITEM_PRESET_MODE]   = sText_GameMode,
    [MENUITEM_PRESET_CANCEL] = sText_CancelPreset,
    [MENUITEM_PRESET_SAVE]   = sText_SavePreset,
};

static const u8 *const OptionTextRight(u8 menuItem)
{
    switch (sOptions->submenu)
    {
        case MENU_RUN:
            return sModeMenuItemsNamesRun[menuItem];
        case MENU_DIFF:
            return sModeMenuItemsNamesDiff[menuItem];
        case MENU_RAND:
            return sModeMenuItemsNamesRand[menuItem];
        case MENU_PRESETS:
            return sModeMenuItemsNamesPresets[menuItem];
        default:
            return gText_EmptyString2;
    }
}

// Menu left side text conditions
static bool8 CheckConditions(int selection)
{
    switch (sOptions->submenu)
    {
        case MENU_RUN:
            switch(selection)
            {
                case MENUITEM_RUN_SPECIES_ARRAY:   return TRUE;
                case MENUITEM_RUN_BATTLEMODE:      return TRUE;
                case MENUITEM_RUN_3_MONS_ONLY:     return TRUE;
                case MENUITEM_RUN_NO_CASE_CHOICE:  return TRUE;
                case MENUITEM_RUN_50_FLOORS:       return TRUE;
                case MENUITEM_RUN_INVERSE_BATTLES: return TRUE;
                case MENUITEM_RUN_CANCEL:          return TRUE;
                case MENUITEM_RUN_COUNT:           return TRUE;
                default:                           return FALSE;
            }
        case MENU_DIFF:
            switch(selection)
            {
                case MENUITEM_DIFF_XPMODE:        return TRUE;
                case MENUITEM_DIFF_STAT_CHANGER:  return TRUE;
                case MENUITEM_DIFF_TRAINER_EVS:   return TRUE;
                case MENUITEM_DIFF_DOUBLE_CASH:   return TRUE;
                case MENUITEM_DIFF_HEALFLOORS:    return TRUE;
                case MENUITEM_DIFF_LEGENDARIES:   return TRUE;
            #ifdef PIT_GEN_9_MODE
                case MENUITEM_DIFF_TRAINER_GIMMICKS: return TRUE;
                case MENUITEM_DIFF_MEGAS:         return TRUE;
                case MENUITEM_DIFF_ZMOVES:        return TRUE;
            #endif
                case MENUITEM_DIFF_EVOSTAGE:      return TRUE;
                case MENUITEM_DIFF_MONOTYPE:      return TRUE;
                case MENUITEM_DIFF_BOSS_HEAL:     return TRUE;
                case MENUITEM_DIFF_ITEM_DROPS:    return TRUE;
                case MENUITEM_DIFF_NO_BAG_USE:    return TRUE;
            #ifdef PIT_GEN_9_MODE
                case MENUITEM_DIFF_DYNAMAX:       return TRUE;
                case MENUITEM_DIFF_TERA:          return TRUE;
            #endif
                case MENUITEM_DIFF_CANCEL:        return TRUE;
                case MENUITEM_DIFF_COUNT:         return TRUE;
                default:                          return FALSE;
            }
        case MENU_RAND:
            switch(selection)
            {
                case MENUITEM_RAND_B_WEATHER:     return TRUE;
                case MENUITEM_RAND_MOVES:         return TRUE;
                case MENUITEM_RAND_ABILITIES:     return TRUE;
                case MENUITEM_RAND_BASE_STATS:    return TRUE;
                case MENUITEM_RAND_TYPES:         return TRUE;
                case MENUITEM_RAND_EVOS:          return TRUE;
                case MENUITEM_RAND_CANCEL:        return TRUE;
                case MENUITEM_RAND_COUNT:         return TRUE;
                default:                          return FALSE;
            }
        case MENU_PRESETS:
            switch(selection)
            {
                case MENUITEM_PRESET_MODE:        return TRUE;
                case MENUITEM_PRESET_CANCEL:      return TRUE;
                case MENUITEM_PRESET_SAVE:        return TRUE;
                case MENUITEM_PRESET_COUNT:       return TRUE;
                default:                          return FALSE;
            }
        default: return FALSE;
    }
}

// Descriptions
static const u8 sText_Empty[]                   = _("");
static const u8 sText_Desc_Save[]               = _("Save your settings.");
static const u8 sText_Desc_CancelPreset[]       = _("Cancel and return without setting\na preset.");
static const u8 sText_Desc_SavePreset[]         = _("Save preset and overwrite current\nmode choice.");
static const u8 sText_Desc_SpeciesArrayRand[]   = _("Trainer Pokémon are fully randomized.");
static const u8 sText_Desc_SpeciesArrayProg[]   = _("Trainer Pokémon scale with floors\nto offer a smoother experience.");
static const u8 sText_Desc_NormalMode[]         = _("HOPE mode settings are used as\nintended by the devs.");
static const u8 sText_Desc_HardMode[]           = _("DESPAIR mode settings are used as\nintended by the devs.");
static const u8 sText_Desc_Defaults_Normal[]    = _("Sets all options for HOPE Mode below.");
static const u8 sText_Desc_Defaults_Hard[]      = _("Sets all options for DESPAIR Mode below.");
static const u8 sText_Desc_Defaults_Custom[]    = _("Is shown when manually changing\nmode settings.");
static const u8 sText_Desc_Autosave_Off[]       = _("Autosave is inactive.");
static const u8 sText_Desc_Autosave_5[]         = _("Autosave is executed every\nfive floors during warping.");
static const u8 sText_Desc_Autosave_On[]        = _("Autosave is executed every\nfloor during warping.");
static const u8 sText_Desc_BattleMode_Singles[] = _("Play only single battles.");
static const u8 sText_Desc_BattleMode_Doubles[] = _("Play only double battles.");
static const u8 sText_Desc_BattleMode_Mix[]     = _("Play mixed singles and double battles.");
static const u8 sText_Desc_Randomizer_Mons[]    = _("Only randomize Pokémon species,\ntrainers and item drops.");
static const u8 sText_Desc_Randomizer_All[]     = _("Also randomize abilities and\nmoves.");
static const u8 sText_Desc_XPMode_75[]          = _("Exp. Share gives 75% XP to party\nmembers.");
static const u8 sText_Desc_XPMode_50[]          = _("Exp. Share gives 50% XP to party\nmembers. WARNING: DESPAIR Mode!");
static const u8 sText_Desc_XPMode_None[]        = _("You won't receive any XP from battles.\nLevels are tied to the floor.");
static const u8 sText_Desc_StatChanger_On[]     = _("Enables the EV/IV Changer\nin the party menu.");
static const u8 sText_Desc_StatChanger_Off[]    = _("Makes the EV/IV Changer read only\nand adds an IV merchant option.");
static const u8 sText_Desc_TrainerEVs_On[]      = _("Opponent's team EVs match the\naverage EVs of your own team.");
static const u8 sText_Desc_TrainerEVs_Off[]     = _("Opponent's team EVs are always set\nto zero unless for boss Aces.");
static const u8 sText_Desc_Legendaries_On[]     = _("Legendaries can be found\nin the Birch Case.");
static const u8 sText_Desc_Legendaries_Off[]    = _("Legendaries can not be found\nin the Birch Case.");
static const u8 sText_Desc_Duplicates_On[]      = _("Truly random. Duplicates are\npossible in the Birch Case.");
static const u8 sText_Desc_Duplicates_Off[]     = _("Birch Case can't hold duplicates.");
static const u8 sText_Desc_Megas_On[]           = _("Mega Evolution is possible.\nA Mega Ring is added to the shop.");
static const u8 sText_Desc_Megas_Off[]          = _("Mega Evolution is not available.");
static const u8 sText_Desc_ZMoves_On[]           = _("Using Z-Moves is possible.\nA Z Power Ring is added to the shop.");
static const u8 sText_Desc_ZMoves_Off[]          = _("Using Z-Moves is not available.");
static const u8 sText_Desc_HealFloors_5[]       = _("Get a rest stop to heal every\n5 floors.");
static const u8 sText_Desc_HealFloors_10[]      = _("SUPER HARD! Get a rest stop to heal\nevery 10 floors.");
static const u8 sText_Desc_3Mons_On[]           = _("Party size will never increase and\nremain at three (incl. trainers).");
static const u8 sText_Desc_3Mons_Off[]          = _("Party size will increase by one\nevery 25 floors.");
static const u8 sText_Desc_NoCaseChoice_On[]    = _("You can't choose your party\nand will be given random species.");
static const u8 sText_Desc_NoCaseChoice_Off[]   = _("You can choose your party from\nthe random Birch Case options.");
static const u8 sText_Desc_BossHeal_On[]        = _("Your party will be healed before\nstarting a boss battle.");
static const u8 sText_Desc_BossHeal_Off[]       = _("Your party won't be healed before\nstarting a boss battle.");
static const u8 sText_Desc_DoubleCash_1x[]      = _("Sets the default amount of money\nreceived after a battle.");
static const u8 sText_Desc_DoubleCash_2x[]      = _("Doubles the amount of money\nreceived after a battle.");
static const u8 sText_Desc_DoubleCash_05x[]     = _("SUPER HARD! Halves the amount of\nmoney received after a battle.");
static const u8 sText_Desc_ItemDrops_Rand[]     = _("Item drops after clearing a floor\nare randomized 1-3.");
static const u8 sText_Desc_ItemDrops_1[]        = _("Only a single item is dropped after\nclearing a floor.");
static const u8 sText_Desc_ItemDrops_3[]        = _("Always three items are dropped after\nclearing a floor.");
static const u8 sText_Desc_EvoStage_All[]       = _("Pokémon to choose from can be all\nkinds of evolution stages.");
static const u8 sText_Desc_EvoStage_Basic[]     = _("Pokémon to choose from will always\nbe Basic Pokémon.");
static const u8 sText_Desc_EvoStage_Full[]      = _("Pokémon to choose from will always\nbe fully evolved Pokémon.");
static const u8 sText_Desc_50Floors_On[]        = _("A shorter Pit experience that\nonly goes 50 floors deep.");
static const u8 sText_Desc_50Floors_Off[]       = _("The regular Pit experience that\ngoes 100 floors deep and beyond.");
static const u8 sText_Desc_InverseBattles_On[]  = _("The type chart is inversed.");
static const u8 sText_Desc_InverseBattles_Off[] = _("The regular type chart is used.");
static const u8 sText_Desc_NoBagUse_On[]        = _("The bag can be used in battle.");
static const u8 sText_Desc_NoBagUse_Off[]       = _("The bag cannot be used in battle.");
static const u8 sText_Desc_Dynamax_On[]         = _("Dynamaxing is possible. A Dynamax\nBand can be bought from the merchant.");
static const u8 sText_Desc_Dynamax_Off[]        = _("Dynamaxing is not available.");
static const u8 sText_Desc_Tera_On[]            = _("Terastallization is possible.\nA Tera Orb is added to the shop.");
static const u8 sText_Desc_Tera_Off[]           = _("Terastallization is not available.");
static const u8 sText_Desc_MonoType[]           = _("Choose a type to play a\nmono type run with.");
static const u8 sText_Desc_RandBWeather_On[]    = _("Weather during battles is randomized.");
static const u8 sText_Desc_RandBWeather_OW[]    = _("Weather during battles is based on\nthe current floor's weather.");
static const u8 sText_Desc_RandBWeather_Off[]   = _("Weather during battles is turned off.");
static const u8 sText_Desc_RandMoves_On[]       = _("Randomizes the move learnsets.");
static const u8 sText_Desc_RandMoves_Off[]      = _("Keeps the default move learnsets.");
static const u8 sText_Desc_RandAbilities_On[]   = _("Randomizes the ability options.");
static const u8 sText_Desc_RandAbilities_Off[]  = _("Keeps the default ability options.");
static const u8 sText_Desc_RandStats_On[]       = _("Randomizes the base stats.");
static const u8 sText_Desc_RandStats_Off[]      = _("Keeps the default base stats.");
static const u8 sText_Desc_RandTypes_On[]       = _("Randomizes the species' type(s).");
static const u8 sText_Desc_RandTypes_Off[]      = _("Keeps the species' default type(s).");
static const u8 sText_Desc_RandEvos_On[]        = _("Randomizes the evolution species.");
static const u8 sText_Desc_RandEvos_Off[]       = _("Keeps the default evo line.");
static const u8 sText_Desc_TrainerGimmicks_None[]      = _("Trainers will not use gimmicks.\n(Boss Aces can still Mega).");
static const u8 sText_Desc_TrainerGimmicks_Random[]      = _("Trainers will have set chances to use\nthe various gimmicks turned on.");
static const u8 sText_Desc_TrainerGimmicks_Prog[]     = _("Trainers will progressively use more \nenabled gimmicks as you get lower. ");

static const u8 *const sModeMenuItemDescriptionsRun[MENUITEM_RUN_COUNT][3] =
{
    [MENUITEM_RUN_SPECIES_ARRAY]   = {sText_Desc_SpeciesArrayRand,    sText_Desc_SpeciesArrayProg,    sText_Empty},
    [MENUITEM_RUN_BATTLEMODE]      = {sText_Desc_BattleMode_Singles,  sText_Desc_BattleMode_Doubles,  sText_Desc_BattleMode_Mix},
    [MENUITEM_RUN_3_MONS_ONLY]     = {sText_Desc_3Mons_On,            sText_Desc_3Mons_Off,           sText_Empty},
    [MENUITEM_RUN_NO_CASE_CHOICE]  = {sText_Desc_NoCaseChoice_On,     sText_Desc_NoCaseChoice_Off,    sText_Empty},
    [MENUITEM_RUN_50_FLOORS]       = {sText_Desc_50Floors_On,         sText_Desc_50Floors_Off,        sText_Empty},
    [MENUITEM_RUN_INVERSE_BATTLES] = {sText_Desc_InverseBattles_On,   sText_Desc_InverseBattles_Off,  sText_Empty},
    [MENUITEM_RUN_CANCEL]          = {sText_Desc_Save,                sText_Empty,                    sText_Empty},
};

static const u8 *const sModeMenuItemDescriptionsDiff[MENUITEM_DIFF_COUNT][3] =
{
    [MENUITEM_DIFF_XPMODE]        = {sText_Desc_XPMode_75,        sText_Desc_XPMode_50,         sText_Desc_XPMode_None},
    [MENUITEM_DIFF_STAT_CHANGER]  = {sText_Desc_StatChanger_On,   sText_Desc_StatChanger_Off,   sText_Empty},
    [MENUITEM_DIFF_TRAINER_EVS]   = {sText_Desc_TrainerEVs_On,    sText_Desc_TrainerEVs_Off,    sText_Empty},
    [MENUITEM_DIFF_DOUBLE_CASH]   = {sText_Desc_DoubleCash_1x,    sText_Desc_DoubleCash_2x,     sText_Desc_DoubleCash_05x},
    [MENUITEM_DIFF_HEALFLOORS]    = {sText_Desc_HealFloors_5,     sText_Desc_HealFloors_10,     sText_Empty},
    [MENUITEM_DIFF_LEGENDARIES]   = {sText_Desc_Legendaries_On,   sText_Desc_Legendaries_Off,   sText_Empty},
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_TRAINER_GIMMICKS]   = {sText_Desc_TrainerGimmicks_Random,    sText_Desc_TrainerGimmicks_Prog,     sText_Desc_TrainerGimmicks_None},
    [MENUITEM_DIFF_MEGAS]         = {sText_Desc_Megas_On,         sText_Desc_Megas_Off,         sText_Empty},
    [MENUITEM_DIFF_ZMOVES]          = {sText_Desc_ZMoves_On,         sText_Desc_ZMoves_Off,         sText_Empty},
#endif
    [MENUITEM_DIFF_EVOSTAGE]      = {sText_Desc_EvoStage_All,     sText_Desc_EvoStage_Basic,    sText_Desc_EvoStage_Full},
    [MENUITEM_DIFF_MONOTYPE]      = {sText_Desc_MonoType,         sText_Desc_MonoType,          sText_Desc_MonoType},
    [MENUITEM_DIFF_BOSS_HEAL]     = {sText_Desc_BossHeal_On,      sText_Desc_BossHeal_Off,      sText_Empty},
    [MENUITEM_DIFF_ITEM_DROPS]    = {sText_Desc_ItemDrops_Rand,   sText_Desc_ItemDrops_1,       sText_Desc_ItemDrops_3},
    [MENUITEM_DIFF_NO_BAG_USE]    = {sText_Desc_NoBagUse_On,      sText_Desc_NoBagUse_Off,      sText_Empty},
#ifdef PIT_GEN_9_MODE
    [MENUITEM_DIFF_DYNAMAX]       = {sText_Desc_Dynamax_On,       sText_Desc_Dynamax_Off,       sText_Empty},
    [MENUITEM_DIFF_TERA]          = {sText_Desc_Tera_On,          sText_Desc_Tera_Off,          sText_Empty},
#endif
    [MENUITEM_DIFF_CANCEL]        = {sText_Desc_Save,             sText_Empty,                  sText_Empty},
};

static const u8 *const sModeMenuItemDescriptionsRand[MENUITEM_RAND_COUNT][3] =
{
    [MENUITEM_RAND_B_WEATHER]     = {sText_Desc_RandBWeather_On,   sText_Desc_RandBWeather_OW,    sText_Desc_RandBWeather_Off},
    [MENUITEM_RAND_MOVES]         = {sText_Desc_RandMoves_On,      sText_Desc_RandMoves_Off,      sText_Empty},
    [MENUITEM_RAND_ABILITIES]     = {sText_Desc_RandAbilities_On,  sText_Desc_RandAbilities_Off,  sText_Empty},
    [MENUITEM_RAND_BASE_STATS]    = {sText_Desc_RandStats_On,      sText_Desc_RandStats_Off,      sText_Empty},
    [MENUITEM_RAND_TYPES]         = {sText_Desc_RandTypes_On,      sText_Desc_RandTypes_Off,      sText_Empty},
    [MENUITEM_RAND_EVOS]          = {sText_Desc_RandEvos_On,       sText_Desc_RandEvos_Off,       sText_Empty},
    [MENUITEM_RAND_CANCEL]        = {sText_Desc_Save,              sText_Empty,                   sText_Empty},
};

static const u8 *const sModeMenuItemDescriptionsPresets[MENUITEM_PRESET_COUNT][3] =
{
    [MENUITEM_PRESET_MODE]        = {sText_Desc_NormalMode,    sText_Desc_HardMode,           sText_Empty},
    [MENUITEM_PRESET_CANCEL]      = {sText_Desc_CancelPreset,  sText_Empty,                   sText_Empty},
    [MENUITEM_PRESET_SAVE]        = {sText_Desc_SavePreset,    sText_Empty,                   sText_Empty},
};

static const u8 *const OptionTextDescription(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu];
    u8 selection;

    switch (sOptions->submenu)
    {
    case MENU_RUN:
        selection = sOptions->sel_run[menuItem];
        return sModeMenuItemDescriptionsRun[menuItem][selection];
    case MENU_DIFF:
        selection = sOptions->sel_diff[menuItem];
        if (menuItem == MENUITEM_DIFF_MONOTYPE)
            return sModeMenuItemDescriptionsDiff[menuItem][0];
        else
            return sModeMenuItemDescriptionsDiff[menuItem][selection];
    case MENU_RAND:
        selection = sOptions->sel_rand[menuItem];
        return sModeMenuItemDescriptionsRand[menuItem][selection];
    case MENU_PRESETS:
        selection = sOptions->sel_presets[menuItem];
        return sModeMenuItemDescriptionsPresets[menuItem][selection];
    default:
        return gText_EmptyString2;
    }
}

static u8 MenuItemCount(void)
{
    switch (sOptions->submenu)
    {
        case MENU_RUN:
            return MENUITEM_RUN_COUNT;
        case MENU_DIFF:
            return MENUITEM_DIFF_COUNT;
        case MENU_RAND:
            return MENUITEM_RAND_COUNT;
        case MENU_PRESETS:
            return MENUITEM_PRESET_COUNT;
        default:
            return 0;
    }
}

static u8 MenuItemCancel(void)
{
    switch (sOptions->submenu)
    {
        case MENU_RUN:
            return MENUITEM_RUN_CANCEL;
        case MENU_DIFF:
            return MENUITEM_DIFF_CANCEL;
        case MENU_RAND:
            return MENUITEM_RAND_CANCEL;
        default:
            return 0;
    }
}

static u8 MenuItemPresetsSave(void)
{
    if (sOptions->submenu == MENU_PRESETS)
        return MENUITEM_PRESET_SAVE;
    else
        return 0;
}

static u8 MenuItemPresetsCancel(void)
{
    switch (sOptions->submenu)
    {
        case MENU_PRESETS:
            return MENUITEM_PRESET_CANCEL;
        default:
            return 0;
    }
}

//
//  main code
//

void Task_OpenModeMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        ModeMenu_Init(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        DestroyTask(taskId);
    }
}

void ModeMenu_Init(MainCallback callback)
{
    sModeMenuState = AllocZeroed(sizeof(struct ModeMenuState));
    if (sModeMenuState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sModeMenuState->loadState = 0;
    sModeMenuState->savedCallback = callback;

    SetMainCallback2(ModeMenu_SetupCB);
}

static void ModeMenu_SetupCB(void)
{
    u32 i;
    u8 taskId;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        sOptions = AllocZeroed(sizeof(*sOptions));
        FreeAllSpritePalettes();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        ResetBgsAndClearDma3BusyFlags(0);
        ResetBgPositions();
        
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG2);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        
        ResetAllBgsCoordinates();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sModeMenuBgTemplates, NELEMS(sModeMenuBgTemplates));
        InitWindows(sModeMenuWindowTemplates);

        sBg2TilemapBuffer = Alloc(0x800);
        memset(sBg2TilemapBuffer, 0, 0x800);
        SetBgTilemapBuffer(2, sBg2TilemapBuffer);
        ScheduleBgCopyTilemapToVram(2);

        sBg3TilemapBuffer = Alloc(0x800);
        memset(sBg3TilemapBuffer, 0, 0x800);
        SetBgTilemapBuffer(3, sBg3TilemapBuffer);
        ScheduleBgCopyTilemapToVram(3);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        gMain.state++;
        sOptions->gfxLoadState = 0;
        break;
    case 3:
        if (ModeMenu_LoadGraphics() == TRUE)
        {
            gMain.state++;
            LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        }
        break;
    case 4:
        LoadPalette(sModeMenuBg_Pal, 0, sizeof(sModeMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sModeMenuText_Pal, 16, sizeof(sModeMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        //run settings
        sOptions->sel_run[MENUITEM_RUN_SPECIES_ARRAY]   = gSaveBlock2Ptr->modeSpeciesArray;
        sOptions->sel_run[MENUITEM_RUN_BATTLEMODE]      = gSaveBlock2Ptr->modeBattleMode;
        sOptions->sel_run[MENUITEM_RUN_3_MONS_ONLY]     = gSaveBlock2Ptr->mode3MonsOnly;
        sOptions->sel_run[MENUITEM_RUN_NO_CASE_CHOICE]  = gSaveBlock2Ptr->modeNoCaseChoice;
        sOptions->sel_run[MENUITEM_RUN_50_FLOORS]       = !(gSaveBlock2Ptr->mode50Floors);
        sOptions->sel_run[MENUITEM_RUN_INVERSE_BATTLES] = !(gSaveBlock2Ptr->modeInverseBattles);
        //difficulty settings
        sOptions->sel_diff[MENUITEM_DIFF_XPMODE]        = gSaveBlock2Ptr->modeXP;
        sOptions->sel_diff[MENUITEM_DIFF_STAT_CHANGER]  = gSaveBlock2Ptr->modeStatChanger;
        sOptions->sel_diff[MENUITEM_DIFF_TRAINER_EVS]   = gSaveBlock2Ptr->modeTrainerEVs;
        sOptions->sel_diff[MENUITEM_DIFF_DOUBLE_CASH]   = gSaveBlock2Ptr->modeCashRewards;
        
        sOptions->sel_diff[MENUITEM_DIFF_HEALFLOORS]    = gSaveBlock2Ptr->modeHealFloors10;
        sOptions->sel_diff[MENUITEM_DIFF_LEGENDARIES]   = gSaveBlock2Ptr->modeLegendaries;
    #ifdef PIT_GEN_9_MODE
        sOptions->sel_diff[MENUITEM_DIFF_TRAINER_GIMMICKS]   = gSaveBlock2Ptr->trainerGimmicks;
        sOptions->sel_diff[MENUITEM_DIFF_MEGAS]         = gSaveBlock2Ptr->modeMegas;
        sOptions->sel_diff[MENUITEM_DIFF_ZMOVES]        = gSaveBlock2Ptr->modeZMoves;
    #endif
        sOptions->sel_diff[MENUITEM_DIFF_EVOSTAGE]      = gSaveBlock2Ptr->modeChoiceEvoStage;
        if (gSaveBlock2Ptr->modeMonoType >= TYPE_MYSTERY)
            sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE]  = gSaveBlock2Ptr->modeMonoType - 1;
        else
            sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE]  = gSaveBlock2Ptr->modeMonoType;
        sOptions->sel_diff[MENUITEM_DIFF_BOSS_HEAL]     = gSaveBlock2Ptr->modeBossHeal;
        sOptions->sel_diff[MENUITEM_DIFF_ITEM_DROPS]    = gSaveBlock2Ptr->modeChoiceItemReward;
        sOptions->sel_diff[MENUITEM_DIFF_NO_BAG_USE]    = gSaveBlock2Ptr->modeNoBagUse;
    #ifdef PIT_GEN_9_MODE
        sOptions->sel_diff[MENUITEM_DIFF_DYNAMAX]       = !(gSaveBlock2Ptr->modeDynamax);
        sOptions->sel_diff[MENUITEM_DIFF_TERA]          = !(gSaveBlock2Ptr->modeTera);
    #endif
        //randomizer settings
        sOptions->sel_rand[MENUITEM_RAND_B_WEATHER]     = gSaveBlock2Ptr->randomBattleWeather;
        sOptions->sel_rand[MENUITEM_RAND_MOVES]         = gSaveBlock2Ptr->randomMoves;
        sOptions->sel_rand[MENUITEM_RAND_ABILITIES]     = gSaveBlock2Ptr->randomAbilities;
        sOptions->sel_rand[MENUITEM_RAND_BASE_STATS]    = gSaveBlock2Ptr->randomBST;
        sOptions->sel_rand[MENUITEM_RAND_TYPES]         = gSaveBlock2Ptr->randomType;
        sOptions->sel_rand[MENUITEM_RAND_EVOS]          = gSaveBlock2Ptr->randomEvos;
        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_TOPBAR);
        DrawTopBarText();
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_DESCRIPTION);
        DrawDescriptionText();
        gMain.state++;
        break;
    case 9:
        PutWindowTilemap(WIN_OPTIONS);
        DrawModeMenuTexts();
        gMain.state++;
        break;
    case 10:
        taskId = CreateTask(Task_ModeMenuWaitFadeIn, 0);
        
        sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MENUITEM_RUN_COUNT - 1, 110, 110, 0);

        for (i = 0; i < min(OPTIONS_ON_SCREEN, MenuItemCount()); i++)
            DrawChoices(i, i * Y_DIFF);

        HighlightModeMenuItem();

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    case 11:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 12:
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        // Finally we can set our main callbacks since loading is finished
        SetVBlankCallback(ModeMenu_VBlankCB);
        SetMainCallback2(ModeMenu_MainCB);
        break;
    }
}

static void ModeMenu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void ModeMenu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ChangeBgY(3, 128, BG_COORD_SUB);
}

//Header Window
//static const u8 sText_TopBar_Run[] = _("CHOOSE GAME MODE");
static const u8 sText_TopBar_Run[]        = _("RUN SETTINGS");
static const u8 sText_TopBar_Diff[]       = _("DIFFICULTY");
static const u8 sText_TopBar_Rand[]       = _("RANDOMIZER");
static const u8 sText_TopBar_Select[]     = _("{SELECT_BUTTON} PRESETS");
static const u8 sText_TopBar_Right[]      = _("PAGE");
static const u8 gText_SmallDot[]          = _("·");
static const u8 gText_LargeDot[]          = _("{EMOJI_CIRCLE}");
static void DrawTopBarText(void)
{
    const u8 color[3] = { 0, TEXT_COLOR_WHITE, TEXT_COLOR_OPTIONS_GRAY_FG };
    u8 pageDots[2*(MENU_COUNT - 1)] = _("");
    int i;

    if (sOptions->submenu != MENU_PRESETS)
    {
        //create navigation dots
        for (i = 0; i < (MENU_COUNT - 1); i++)
        {
            if (i == sOptions->submenu)
                StringAppend(pageDots, gText_LargeDot);
            else
                StringAppend(pageDots, gText_SmallDot);
            if (i < MENU_RAND)
                StringAppend(pageDots, gText_Space);
        }

        FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(0));
        AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, pageDots);

        switch (sOptions->submenu)
        {
            case MENU_RUN:
                AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 40, 1, color, 0, sText_TopBar_Run);
                break;
            case MENU_DIFF:
                AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 40, 1, color, 0, sText_TopBar_Diff);
                break;
            case MENU_RAND:
                AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 40, 1, color, 0, sText_TopBar_Rand);
                break;
        }
        AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 125, 1, color, 0, sText_TopBar_Select);
        BlitBitmapToWindow(WIN_TOPBAR, sLR_ButtonGfx, 190, 4, 24, 8);
        AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 215, 1, color, 0, sText_TopBar_Right);
    }
    else
    {
        FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(0));
        AddTextPrinterParameterized3(WIN_TOPBAR, FONT_NORMAL, 10, 1, color, 0, sText_Defaults);
    }

    PutWindowTilemap(WIN_TOPBAR);
    CopyWindowToVram(WIN_TOPBAR, COPYWIN_FULL);
}

static void DrawModeMenuTexts(void) //left side text
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(0));
    for (i = 0; i < MenuItemCount(); i++)
        DrawLeftSideOptionText(i, (i * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDescriptionText(void)
{
    u8 color_gray[3];
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_FG;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
        
    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized4(WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextDescription());
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}

static void DrawLeftSideOptionText(int selection, int y)
{
    u8 color_yellow[3];
    u8 color_gray[3];
    u8 color_red[3];

    color_yellow[0] = TEXT_COLOR_TRANSPARENT;
    color_yellow[1] = TEXT_COLOR_WHITE;
    color_yellow[2] = TEXT_COLOR_OPTIONS_GRAY_FG;
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_WHITE;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
    color_red[0] = TEXT_COLOR_TRANSPARENT;
    color_red[1] = TEXT_COLOR_OPTIONS_RED_FG;
    color_red[2] = TEXT_COLOR_OPTIONS_GRAY_FG;

    if (CheckConditions(selection))
    {
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_yellow, TEXT_SKIP_DRAW, OptionTextRight(selection));
    }
    else
    {
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextRight(selection));
    }
}

static void DrawRightSideChoiceText(const u8 *text, int x, int y, bool8 chosen, bool8 active)
{
    u8 color_red[3];
    u8 color_gray[3];

    if (active)
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_ORANGE_FG;
        color_red[2] = TEXT_COLOR_OPTIONS_GRAY_FG;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_WHITE;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_FG;
    }
    else
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_WHITE;
        color_red[2] = TEXT_COLOR_OPTIONS_GRAY_FG;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_WHITE;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_FG;
    }


    if (chosen)
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_red, TEXT_SKIP_DRAW, text);
    else
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_gray, TEXT_SKIP_DRAW, text);
}

static void DrawChoices(u8 id, int y) //right side draw function
{
    switch (sOptions->submenu)
    {
        case MENU_RUN:
            if (sItemFunctionsRun[id].drawChoices != NULL)
                sItemFunctionsRun[id].drawChoices(sOptions->sel_run[id], y);
            break;
        case MENU_DIFF:
            if (sItemFunctionsDiff[id].drawChoices != NULL)
                sItemFunctionsDiff[id].drawChoices(sOptions->sel_diff[id], y);
            break;
        case MENU_RAND:
            if (sItemFunctionsRand[id].drawChoices != NULL)
                sItemFunctionsRand[id].drawChoices(sOptions->sel_rand[id], y);
            break;
        case MENU_PRESETS:
            if (sItemFunctionsPresets[id].drawChoices != NULL)
                sItemFunctionsPresets[id].drawChoices(sOptions->sel_presets[id], y);
            break;
    }
}

static void HighlightModeMenuItem(void)
{
    int cursor = sOptions->visibleCursor[sOptions->submenu];

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(8, 232));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

static bool8 ModeMenu_LoadGraphics(void) //Load all the tilesets, tilemaps, spritesheets, and palettes
{
    switch (sOptions->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sOptionsPlusTiles, 0, 0, 0);
        sOptions->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sOptionsPlusTilemap, sBg2TilemapBuffer);
            sOptions->gfxLoadState++;
        }
        break;
    case 2:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(3, sScrollBgTiles, 0, 0, 0);
        sOptions->gfxLoadState++;
        break;
    case 3:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sScrollBgTilemap, sBg3TilemapBuffer);
            sOptions->gfxLoadState++;
        }
        break;
    case 4:
        LoadPalette(sOptionsPlusPalette, 64, 32);
        LoadPalette(sScrollBgPalette, 32, 32);
        sOptions->gfxLoadState++;
        break;
    default:
        sOptions->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void Task_ModeMenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_ModeMenuMainInput;
        SetGpuReg(REG_OFFSET_WIN0H, 0); // Idk man Im just trying to stop this stupid graphical bug from happening dont judge me
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG2);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        HighlightModeMenuItem();
        return;
    }
}

static void Task_ModeMenuMainInput(u8 taskId)
{
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN , MenuItemCount());

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu != MENU_PRESETS && sOptions->menuCursor[sOptions->submenu] == MenuItemCancel())
            gTasks[taskId].func = Task_ModeMenuSave;
        if (sOptions->submenu == MENU_PRESETS && sOptions->menuCursor[sOptions->submenu] == MenuItemPresetsSave())
            ApplyPresets();
        if (sOptions->submenu == MENU_PRESETS && sOptions->menuCursor[sOptions->submenu] == MenuItemPresetsCancel())
        {
            if (sOptions->submenu == MENU_PRESETS)
            {
                sOptions->submenu = MENU_RUN;
                DrawTopBarText();
                ReDrawAll();
                HighlightModeMenuItem();
                DrawDescriptionText();
            }
        }
    }
    // Exit the menu when the player presses START
    else if (JOY_NEW(START_BUTTON) && sOptions->submenu != MENU_PRESETS)
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_ModeMenuSave;
    }
    else if (JOY_REPEAT(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        if (sOptions->visibleCursor[sOptions->submenu] == optionsToDraw-2) // don't advance visible cursor until scrolled to the bottom
        {
            if (++sOptions->menuCursor[sOptions->submenu] == MenuItemCount() - 1)
                sOptions->visibleCursor[sOptions->submenu]++;
            else
                ScrollMenu(0);
        }
        else
        {
            if (++sOptions->menuCursor[sOptions->submenu] >= MenuItemCount()-1) // Scroll all the way to the top.
            {
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-2;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - optionsToDraw-1;
                ScrollAll(1);
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = 0;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]++;
            }
        }
        HighlightModeMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_REPEAT(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        if (sOptions->visibleCursor[sOptions->submenu] == NUM_OPTIONS_FROM_BORDER) // don't advance visible cursor until scrolled to the bottom
        {
            if (--sOptions->menuCursor[sOptions->submenu] == 0)
                sOptions->visibleCursor[sOptions->submenu]--;
            else
                ScrollMenu(1);
        }
        else
        {
            if (--sOptions->menuCursor[sOptions->submenu] < 0) // Scroll all the way to the bottom.
            {
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = optionsToDraw-2;
                ScrollAll(0);
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-1;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - 1;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]--;
            }
        }
        HighlightModeMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu == MENU_RUN)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_run[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsRun[cursor].processInput != NULL)
                {
                    sOptions->sel_run[cursor] = sItemFunctionsRun[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_run[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_DIFF)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_diff[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsDiff[cursor].processInput != NULL)
                {
                    sOptions->sel_diff[cursor] = sItemFunctionsDiff[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_diff[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_RAND)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_rand[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsRand[cursor].processInput != NULL)
                {
                    sOptions->sel_rand[cursor] = sItemFunctionsRand[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_rand[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_PRESETS)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_presets[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsPresets[cursor].processInput != NULL)
                {
                    sOptions->sel_presets[cursor] = sItemFunctionsPresets[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_presets[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
    }
    else if (JOY_NEW(R_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu != MENU_PRESETS)
        {
            if (sOptions->submenu == MENU_RAND)
                sOptions->submenu = MENU_RUN;
            else
                sOptions->submenu++;

            DrawTopBarText();
            ReDrawAll();
            HighlightModeMenuItem();
            DrawDescriptionText();
        }
    }
    else if (JOY_NEW(L_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu != MENU_PRESETS)
        {
            if (sOptions->submenu == MENU_RUN)
                sOptions->submenu = MENU_RAND;
            else
                sOptions->submenu--;
            
            DrawTopBarText();
            ReDrawAll();
            HighlightModeMenuItem();
            DrawDescriptionText();
        }
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu != MENU_PRESETS)
            sOptions->submenu = MENU_PRESETS;
        else
            sOptions->submenu = MENU_RUN;

        DrawTopBarText();
        ReDrawAll();
        HighlightModeMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(B_BUTTON)) //return from Presets view
    {
        PlaySE(SE_SELECT);
        if (sOptions->submenu == MENU_PRESETS)
        {
            sOptions->submenu = MENU_RUN;
            DrawTopBarText();
            ReDrawAll();
            HighlightModeMenuItem();
            DrawDescriptionText();
        }
    }
}

static void Task_ModeMenuSave(u8 taskId)
{
    //write in saveblock
    //run settings
    gSaveBlock2Ptr->modeSpeciesArray   = sOptions->sel_run[MENUITEM_RUN_SPECIES_ARRAY];
    gSaveBlock2Ptr->modeBattleMode     = sOptions->sel_run[MENUITEM_RUN_BATTLEMODE];
    gSaveBlock2Ptr->mode3MonsOnly      = sOptions->sel_run[MENUITEM_RUN_3_MONS_ONLY];
    gSaveBlock2Ptr->modeNoCaseChoice   = sOptions->sel_run[MENUITEM_RUN_NO_CASE_CHOICE];
    gSaveBlock2Ptr->mode50Floors       = !(sOptions->sel_run[MENUITEM_RUN_50_FLOORS]);
    gSaveBlock2Ptr->modeInverseBattles = !(sOptions->sel_run[MENUITEM_RUN_INVERSE_BATTLES]);

    //difficulty settings
    gSaveBlock2Ptr->modeXP           = sOptions->sel_diff[MENUITEM_DIFF_XPMODE];
    gSaveBlock2Ptr->modeBossHeal     = sOptions->sel_diff[MENUITEM_DIFF_BOSS_HEAL];
    gSaveBlock2Ptr->modeStatChanger  = sOptions->sel_diff[MENUITEM_DIFF_STAT_CHANGER];
    gSaveBlock2Ptr->modeTrainerEVs   = sOptions->sel_diff[MENUITEM_DIFF_TRAINER_EVS];
    gSaveBlock2Ptr->modeCashRewards  = sOptions->sel_diff[MENUITEM_DIFF_DOUBLE_CASH];
    gSaveBlock2Ptr->modeHealFloors10 = sOptions->sel_diff[MENUITEM_DIFF_HEALFLOORS];
    gSaveBlock2Ptr->modeLegendaries  = sOptions->sel_diff[MENUITEM_DIFF_LEGENDARIES];
#ifdef PIT_GEN_9_MODE
    gSaveBlock2Ptr->trainerGimmicks = sOptions->sel_diff[MENUITEM_DIFF_TRAINER_GIMMICKS];
    gSaveBlock2Ptr->modeMegas        = sOptions->sel_diff[MENUITEM_DIFF_MEGAS];
    gSaveBlock2Ptr->modeZMoves        = sOptions->sel_diff[MENUITEM_DIFF_ZMOVES];
#endif
    gSaveBlock2Ptr->modeChoiceItemReward = sOptions->sel_diff[MENUITEM_DIFF_ITEM_DROPS];
    gSaveBlock2Ptr->modeChoiceEvoStage   = sOptions->sel_diff[MENUITEM_DIFF_EVOSTAGE];
    gSaveBlock2Ptr->modeNoBagUse         = sOptions->sel_diff[MENUITEM_DIFF_NO_BAG_USE];
#ifdef PIT_GEN_9_MODE
    gSaveBlock2Ptr->modeDynamax          = !(sOptions->sel_diff[MENUITEM_DIFF_DYNAMAX]);
    gSaveBlock2Ptr->modeTera             = !(sOptions->sel_diff[MENUITEM_DIFF_TERA]);
#endif

    if (sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE] >= TYPE_MYSTERY)
        gSaveBlock2Ptr->modeMonoType     = sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE] + 1;
    else
        gSaveBlock2Ptr->modeMonoType     = sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE];

    //randomizer settings
    gSaveBlock2Ptr->randomBattleWeather    = sOptions->sel_rand[MENUITEM_RAND_B_WEATHER];
    gSaveBlock2Ptr->randomMoves            = sOptions->sel_rand[MENUITEM_RAND_MOVES];
    gSaveBlock2Ptr->randomAbilities        = sOptions->sel_rand[MENUITEM_RAND_ABILITIES];
    gSaveBlock2Ptr->randomBST              = sOptions->sel_rand[MENUITEM_RAND_BASE_STATS];
    gSaveBlock2Ptr->randomType             = sOptions->sel_rand[MENUITEM_RAND_TYPES];
    gSaveBlock2Ptr->randomEvos             = sOptions->sel_rand[MENUITEM_RAND_EVOS];


    //set flags/vars
    //####################### run settings #######################

    //!!!! Reminder: Flags are cleared after the intro menus - See SetOnMapLoadDefaultOptions() !!!!
    if (sOptions->sel_run[MENUITEM_RUN_BATTLEMODE] == MODE_DOUBLES)
        FlagSet(FLAG_DOUBLES_MODE);
    else if(sOptions->sel_run[MENUITEM_RUN_BATTLEMODE] == MODE_MIXED)
    {
        FlagClear(FLAG_DOUBLES_MODE);
    }
    else
    {
        FlagClear(FLAG_DOUBLES_MODE);
    }

    if (sOptions->sel_diff[MENUITEM_DIFF_STAT_CHANGER] == OPTIONS_ON)
        FlagSet(FLAG_STAT_CHANGER);
    else
        FlagClear(FLAG_STAT_CHANGER);

    if (sOptions->sel_diff[MENUITEM_DIFF_TRAINER_EVS] == OPTIONS_ON)
        FlagSet(FLAG_TRAINER_EVS);
    else
        FlagClear(FLAG_TRAINER_EVS);

    if (gSaveBlock2Ptr->modeInverseBattles)
    {
        FlagSet(FLAG_INVERSE_BATTLE);
    }
    else
        FlagClear(FLAG_INVERSE_BATTLE);

    if (gSaveBlock2Ptr->modeNoBagUse)
    {
        FlagSet(FLAG_NO_BAG_USE);
    }
    else
        FlagClear(FLAG_NO_BAG_USE);


    //####################### randomizer settings #######################
    //all randomizer settings are handled without VARs/FLAGs directly from the saveblock


    //finish task
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_ModeMenuWaitFadeAndExitGracefully;
}

static void Task_ModeMenuWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_NewGameBirchSpeech_FromNewMainMenu);
        //BirchCase_Init(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        ModeMenu_FreeResources();
        DestroyTask(taskId);
    }
}

//menu navigation code
static void ScrollMenu(int direction)
{
    int menuItem, pos;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor[sOptions->submenu] + NUM_OPTIONS_FROM_BORDER, pos = optionsToDraw - 1;
    else
        menuItem = sOptions->menuCursor[sOptions->submenu] - NUM_OPTIONS_FROM_BORDER, pos = 0;

    // Hide one
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF, PIXEL_FILL(0));
    // Show one
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(0), 0, Y_DIFF * pos, 26 * 8, Y_DIFF);
    // Print
    DrawChoices(menuItem, pos * Y_DIFF);
    DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

static void ScrollAll(int direction) // to bottom or top
{
    int i, y, menuItem, pos;
    int scrollCount;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    scrollCount = MenuItemCount() - optionsToDraw;

    // Move items up/down
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF * scrollCount, PIXEL_FILL(1));

    // Clear moved items
    if (direction == 0)
    {
        y = optionsToDraw - scrollCount;
        if (y < 0)
            y = 0;
        y *= Y_DIFF;
    }
    else
    {
        y = 0;
    }
    
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(0), 0, y, 26 * 8, Y_DIFF * scrollCount);
    // Print new texts
    for (i = 0; i < scrollCount; i++)
    {
        if (direction == 0) // From top to bottom
            menuItem = MenuItemCount() - 1 - i, pos = optionsToDraw - 1 - i;
        else // From bottom to top
            menuItem = i, pos = i;
        DrawChoices(menuItem, pos * Y_DIFF);
        DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Process Input functions ****GENERIC****
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3)
{
    int xMid;
    int widthLeft = GetStringWidth(1, txt1, 0);
    int widthMid = GetStringWidth(1, txt2, 0);
    int widthRight = GetStringWidth(1, txt3, 0);

    widthMid -= (198 - 104);
    xMid = (widthLeft - widthMid - widthRight) / 2 + 104;
    return xMid;
}

static int XOptions_ProcessInput(int x, int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (++selection > (x - 1))
            selection = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (--selection < 0)
            selection = (x - 1);
    }
    return selection;
}

static int ProcessInput_Options_Two(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

static int ProcessInput_Options_Three(int selection)
{
    return XOptions_ProcessInput(3, selection);
}

static int ProcessInput_Options_Eighteen(int selection)
{
    return XOptions_ProcessInput(18, selection);
}

static int ProcessInput_Options_Nineteen(int selection)
{
    return XOptions_ProcessInput(19, selection);
}

// Draw Choices functions ****GENERIC****
static void DrawModeMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active)
{
    bool8 chosen = FALSE;
    if (style != 0)
        chosen = TRUE;

    DrawRightSideChoiceText(text, x, y+1, chosen, active);
}

static void ReDrawAll(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu] - sOptions->visibleCursor[sOptions->submenu];
    u8 i;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (MenuItemCount() <= OPTIONS_ON_SCREEN) // Draw or delete the scrolling arrows based on options in the menu
    {
        if (sOptions->arrowTaskId != TASK_NONE)
        {
            RemoveScrollIndicatorArrowPair(sOptions->arrowTaskId);
            sOptions->arrowTaskId = TASK_NONE;
        }
    }
    else
    {
        if (sOptions->arrowTaskId == TASK_NONE)
            sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MenuItemCount() - 1, 110, 110, 0);

    }

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(0));
    for (i = 0; i < optionsToDraw; i++)
    {
        DrawChoices(menuItem + i, i * Y_DIFF);
        DrawLeftSideOptionText(menuItem + i, (i * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Process Input functions ****SPECIFIC****
static const u8 sText_ModeNormal[]          = _("HOPE");
static const u8 sText_ModeHard[]            = _("DESPAIR");
static const u8 sText_ModeCustom[]          = _("CUST");
static const u8 sText_Autosave_Off[]        = _("OFF");
static const u8 sText_Autosave_5[]          = _("5FLRS");
static const u8 sText_Autosave_On[]         = _("ON");
static const u8 sText_SpeciesArray_Rand[]   = _("RANDOM");
static const u8 sText_SpeciesArray_Prog[]   = _("PROG");
static const u8 sText_BattleMode_Singles[]  = _("SNGLS");
static const u8 sText_BattleMode_Doubles[]  = _("DUOS");
static const u8 sText_BattleMode_Mix[]      = _("MIX");
static const u8 sText_Randomizer_Mons[]     = _("MONS");
static const u8 sText_Randomizer_All[]      = _("ALL");
static const u8 sText_XPShare_75[]          = _("NORMAL");
static const u8 sText_XPShare_50[]          = _("HARD");
static const u8 sText_XPShare_None[]        = _("NONE");
static const u8 sText_StatChanger_On[]      = _("ACTIVE");
static const u8 sText_StatChanger_Off[]     = _("INACTIVE");
static const u8 sText_TrainerEVs_On[]       = _("ACTIVE");
static const u8 sText_TrainerEVs_Off[]      = _("INACTIVE");
static const u8 sText_Choice_Yes[]          = _("YES");
static const u8 sText_Choice_No[]           = _("NO");
static const u8 sText_HealFloors_5[]        = _("5FLRS");
static const u8 sText_HealFloors_10[]       = _("10FLRS");
static const u8 sText_B_Weather_On[]        = _("YES");
static const u8 sText_B_Weather_Map[]       = _("MAP");
static const u8 sText_B_Weather_Off[]       = _("NO");
static const u8 sText_Cash_1x[]             = _("1x");
static const u8 sText_Cash_2x[]             = _("2x");
static const u8 sText_Cash_05x[]            = _(".5x");
static const u8 sText_TrainerGimmicks_None[]             = _("NONE");
static const u8 sText_TrainerGimmicks_Random[]             = _("RAND");
static const u8 sText_TrainerGimmicks_Prog[]            = _("PROG");
static const u8 sText_EvoStage_All[]        = _("ALL");
static const u8 sText_EvoStage_Basic[]      = _("BASIC");
static const u8 sText_EvoStage_Full[]       = _("FULL");
static const u8 sText_ItemDrops_Rand[]      = _("RAND");
static const u8 sText_ItemDrops_1[]         = _("1");
static const u8 sText_ItemDrops_3[]         = _("3");
static const u8 sText_Type_Normal[]         = _("NORMAL");
static const u8 sText_Type_Fighting[]       = _("FIGHT");
static const u8 sText_Type_Flying[]         = _("FLYING");
static const u8 sText_Type_Poison[]         = _("POISON");
static const u8 sText_Type_Ground[]         = _("GROUND");
static const u8 sText_Type_Rock[]           = _("ROCK");
static const u8 sText_Type_Bug[]            = _("BUG");
static const u8 sText_Type_Ghost[]          = _("GHOST");
static const u8 sText_Type_Steel[]          = _("STEEL"); //TYPE_MYSTERY
static const u8 sText_Type_Fire[]           = _("FIRE");
static const u8 sText_Type_Water[]          = _("WATER");
static const u8 sText_Type_Grass[]          = _("GRASS");
static const u8 sText_Type_Electric[]       = _("ELECTRIC");
static const u8 sText_Type_Psychic[]        = _("PSYCHIC");
static const u8 sText_Type_Ice[]            = _("ICE");
static const u8 sText_Type_Dragon[]         = _("DRAGON");
static const u8 sText_Type_Dark[]           = _("DARK");
static const u8 sText_Type_Fairy[]          = _("FAIRY");
static const u8 sText_Arrows_Left[]         = _("<<");
static const u8 sText_Arrows_Right[]        = _(">>");


/*static void DrawChoices_Autosave(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_AUTOSAVE);
    u8 styles[3] = {0};
    int xMid;

    styles[selection] = 1;
    xMid = GetMiddleX(sText_Autosave_Off, sText_Autosave_5, sText_Autosave_On);

    DrawModeMenuChoice(sText_Autosave_Off, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Autosave_5, xMid, y, styles[1], active);
    DrawModeMenuChoice(sText_Autosave_On, GetStringRightAlignXOffset(1, sText_Autosave_On, 198), y, styles[2], active);
}*/

static void DrawChoices_SpeciesArray(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_SPECIES_ARRAY);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_SpeciesArray_Rand, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_SpeciesArray_Prog, GetStringRightAlignXOffset(FONT_NORMAL, sText_SpeciesArray_Prog, 198), y, styles[1], active);
}

static void DrawChoices_3MonsOnly(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_3_MONS_ONLY);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_NoCaseChoice(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_NO_CASE_CHOICE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_50Floors(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_50_FLOORS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_InverseBattles(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_INVERSE_BATTLES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_BossHeal(int selection, int y)
{
   bool8 active = CheckConditions(MENUITEM_DIFF_BOSS_HEAL);
   u8 styles[2] = {0};
   styles[selection] = 1;

   DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
   DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_DoubleCash(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_DOUBLE_CASH);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Cash_1x, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Cash_2x, GetStringRightAlignXOffset(FONT_NORMAL, sText_Cash_2x, 198 - 41), y, styles[1], active);
    DrawModeMenuChoice(sText_Cash_05x, GetStringRightAlignXOffset(FONT_NORMAL, sText_Cash_05x, 198), y, styles[2], active);
}
#ifdef PIT_GEN_9_MODE
static void DrawChoices_TrainerGimmicks(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_TRAINER_GIMMICKS);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_TrainerGimmicks_Random, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_TrainerGimmicks_Prog, GetStringRightAlignXOffset(FONT_NORMAL, sText_TrainerGimmicks_Prog, 198 - 33), y, styles[1], active);
    DrawModeMenuChoice(sText_TrainerGimmicks_None, GetStringRightAlignXOffset(FONT_NORMAL, sText_TrainerGimmicks_None, 198), y, styles[2], active);
}
#endif
static void DrawChoices_ItemDrops(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_ITEM_DROPS);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_ItemDrops_Rand, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_ItemDrops_1, GetStringRightAlignXOffset(FONT_NORMAL, sText_ItemDrops_1, 198 - 37), y, styles[1], active);
    DrawModeMenuChoice(sText_ItemDrops_3, GetStringRightAlignXOffset(FONT_NORMAL, sText_ItemDrops_3, 198), y, styles[2], active);
}

static void DrawChoices_HealFloors(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_HEALFLOORS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_HealFloors_5, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_HealFloors_10, GetStringRightAlignXOffset(FONT_NORMAL, sText_HealFloors_10, 198), y, styles[1], active);
}

static void DrawChoices_BattleMode(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_BATTLEMODE);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_BattleMode_Singles, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_BattleMode_Doubles, GetStringRightAlignXOffset(FONT_NORMAL, sText_BattleMode_Doubles, 198 - 29), y, styles[1], active);
    DrawModeMenuChoice(sText_BattleMode_Mix, GetStringRightAlignXOffset(FONT_NORMAL, sText_BattleMode_Mix, 198), y, styles[2], active);
}

/*static void DrawChoices_Randomizer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RUN_RANDOMIZER);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Randomizer_Mons, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Randomizer_All, GetStringRightAlignXOffset(FONT_NORMAL, sText_Randomizer_All, 198), y, styles[1], active);
}*/

static void DrawChoices_XPMode(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_XPMODE);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_XPShare_75, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_XPShare_50, GetStringRightAlignXOffset(FONT_NORMAL, sText_XPShare_50, 198 - 29), y, styles[1], active);
    DrawModeMenuChoice(sText_XPShare_None, GetStringRightAlignXOffset(FONT_NORMAL, sText_XPShare_None, 198), y, styles[2], active);
}

static void DrawChoices_StatChanger(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_STAT_CHANGER);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_StatChanger_On, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_StatChanger_Off, GetStringRightAlignXOffset(FONT_NORMAL, sText_StatChanger_Off, 198), y, styles[1], active);
}

static void DrawChoices_TrainerEVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_TRAINER_EVS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_TrainerEVs_On, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_TrainerEVs_Off, GetStringRightAlignXOffset(FONT_NORMAL, sText_TrainerEVs_Off, 198), y, styles[1], active);
}

static void DrawChoices_Legendaries(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_LEGENDARIES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_Duplicates(int selection, int y)
{
    bool8 active = TRUE;//CheckConditions(MENUITEM_RUN_DUPLICATES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

#ifdef PIT_GEN_9_MODE
static void DrawChoices_Megas(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_MEGAS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}
#endif

#ifdef PIT_GEN_9_MODE
static void DrawChoices_ZMoves(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_ZMOVES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}
#endif

static void DrawChoices_EvoStage(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_EVOSTAGE);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_EvoStage_All, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_EvoStage_Basic, GetStringRightAlignXOffset(FONT_NORMAL, sText_EvoStage_Basic, 198 - 35), y, styles[1], active);
    DrawModeMenuChoice(sText_EvoStage_Full, GetStringRightAlignXOffset(FONT_NORMAL, sText_EvoStage_Full, 198), y, styles[2], active);
}

static void DrawChoices_MonoType(int selection, int y)
{
    // DrawModeMenuChoice(sText_Autosave_Off, 104, y, styles[0], active);
    // DrawModeMenuChoice(sText_Type_Normal, GetStringRightAlignXOffset(FONT_NORMAL, sText_Type_Normal, 198 - 35), y, styles[1], active);
    // DrawModeMenuChoice(sText_Type_Fighting, GetStringRightAlignXOffset(FONT_NORMAL, sText_Type_Fighting, 198), y, styles[2], active);

    bool8 active = CheckConditions(MENUITEM_DIFF_MONOTYPE);
    u16 xMid = 0;

    DrawModeMenuChoice(sText_Arrows_Left, 104, y, 0, active);

    switch (selection)
    {
    case 1:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Normal, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Normal, xMid, y, 1, active);
        break;
    case 2:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Fighting, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Fighting, xMid, y, 1, active);
        break;
    case 3:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Flying, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Flying, xMid, y, 1, active);
        break;
    case 4:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Poison, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Poison, xMid, y, 1, active);
        break;
    case 5:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Ground, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Ground, xMid, y, 1, active);
        break;
    case 6:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Rock, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Rock, xMid, y, 1, active);
        break;
    case 7:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Bug, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Bug, xMid, y, 1, active);
        break;
    case 8:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Ghost, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Ghost, xMid, y, 1, active);
        break;
    case 9:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Steel, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Steel, xMid, y, 1, active);
        break;
    case 10:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Fire, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Fire, xMid, y, 1, active);
        break;
    case 11:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Water, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Water, xMid, y, 1, active);
        break;
    case 12:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Grass, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Grass, xMid, y, 1, active);
        break;
    case 13:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Electric, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Electric, xMid, y, 1, active);
        break;
    case 14:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Psychic, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Psychic, xMid, y, 1, active);
        break;
    case 15:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Ice, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Ice, xMid, y, 1, active);
        break;
    case 16:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Dragon, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Dragon, xMid, y, 1, active);
        break;
    case 17:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Dark, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Dark, xMid, y, 1, active);
        break;
    case 18:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Type_Fairy, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Type_Fairy, xMid, y, 1, active);
        break;
    default:
        xMid = GetMiddleX(sText_Arrows_Left, sText_Autosave_Off, sText_Arrows_Left);
        DrawModeMenuChoice(sText_Autosave_Off, xMid, y, 1, active);
        break;
    }

    DrawModeMenuChoice(sText_Arrows_Right, GetStringRightAlignXOffset(FONT_NORMAL, sText_Arrows_Right, 198), y, 0, active);
}

#ifdef PIT_GEN_9_MODE
static void DrawChoices_Dynamax(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_DYNAMAX);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_Tera(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_TERA);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}
#endif

static void DrawChoices_NoBagUse(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFF_NO_BAG_USE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_RandBattleWeather(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_B_WEATHER);
    u8 styles[3] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_B_Weather_On, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_B_Weather_Map, GetStringRightAlignXOffset(FONT_NORMAL, sText_B_Weather_Map, 198 - 35), y, styles[1], active);
    DrawModeMenuChoice(sText_B_Weather_Off, GetStringRightAlignXOffset(FONT_NORMAL, sText_B_Weather_Off, 198), y, styles[2], active);
}

static void DrawChoices_RandMoves(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_MOVES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_RandAbilities(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_ABILITIES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_RandStats(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_BASE_STATS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_RandTypes(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_TYPES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_RandEvos(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RAND_EVOS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_Choice_Yes, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_Choice_No, GetStringRightAlignXOffset(FONT_NORMAL, sText_Choice_No, 198), y, styles[1], active);
}

static void DrawChoices_PresetsMode(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_PRESET_MODE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawModeMenuChoice(sText_ModeNormal, 104, y, styles[0], active);
    DrawModeMenuChoice(sText_ModeHard, GetStringRightAlignXOffset(FONT_NORMAL, sText_ModeHard, 198), y, styles[1], active);
}

// Background tilemap
#define TILE_TOP_CORNER_L 0x1A2 // 418
#define TILE_TOP_EDGE     0x1A3 // 419
#define TILE_TOP_CORNER_R 0x1A4 // 420
#define TILE_LEFT_EDGE    0x1A5 // 421
#define TILE_RIGHT_EDGE   0x1A7 // 423
#define TILE_BOT_CORNER_L 0x1A8 // 424
#define TILE_BOT_EDGE     0x1A9 // 425
#define TILE_BOT_CORNER_R 0x1AA // 426

static void DrawBgWindowFrames(void)
{
    // Description window
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2, 14, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void ModeMenu_FreeResources(void)
{
    FreeAllWindowBuffers();
    ResetSpriteData();
    FREE_AND_SET_NULL(sOptions);
    try_free(sBg2TilemapBuffer);
    try_free(sBg3TilemapBuffer);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 4);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    HideBg(2);
    HideBg(3);
}

static void ApplyPresets(void)
{
    int cursor = sOptions->visibleCursor[sOptions->submenu];

    //general defaults:
    //run settings
    sOptions->sel_run[MENUITEM_RUN_SPECIES_ARRAY]   = ARRAY_RANDOM;
    sOptions->sel_run[MENUITEM_RUN_BATTLEMODE]      = MODE_MIXED;
    sOptions->sel_run[MENUITEM_RUN_3_MONS_ONLY]     = OPTIONS_OFF;
    sOptions->sel_run[MENUITEM_RUN_NO_CASE_CHOICE]  = OPTIONS_OFF;
    sOptions->sel_run[MENUITEM_RUN_50_FLOORS]       = OPTIONS_OFF;
    sOptions->sel_run[MENUITEM_RUN_INVERSE_BATTLES] = OPTIONS_OFF;
    //difficulty settings
    sOptions->sel_diff[MENUITEM_DIFF_DOUBLE_CASH]   = CASH_1X;
    sOptions->sel_diff[MENUITEM_DIFF_HEALFLOORS]    = HEAL_FLOORS_5;
    sOptions->sel_diff[MENUITEM_DIFF_EVOSTAGE]      = EVOSTAGE_ALL;
    sOptions->sel_diff[MENUITEM_DIFF_MONOTYPE]      = TYPE_NONE;
    sOptions->sel_diff[MENUITEM_DIFF_BOSS_HEAL]     = OPTIONS_ON;
    sOptions->sel_diff[MENUITEM_DIFF_ITEM_DROPS]    = ITEM_DROPS_3;
    sOptions->sel_diff[MENUITEM_DIFF_NO_BAG_USE]    = OPTIONS_ON;
#ifdef PIT_GEN_9_MODE
    sOptions->sel_diff[MENUITEM_DIFF_MEGAS]         = OPTIONS_ON;
    sOptions->sel_diff[MENUITEM_DIFF_ZMOVES]        = OPTIONS_ON;
    sOptions->sel_diff[MENUITEM_DIFF_DYNAMAX]       = OPTIONS_OFF;
    sOptions->sel_diff[MENUITEM_DIFF_TERA]          = OPTIONS_OFF;
    sOptions->sel_diff[MENUITEM_DIFF_TRAINER_GIMMICKS]    = TRAINER_GIMMICKS_NONE;
#endif
    //randomizer settings
    sOptions->sel_rand[MENUITEM_RAND_B_WEATHER]     = NO_B_WEATHER;
    sOptions->sel_rand[MENUITEM_RAND_MOVES]         = OPTIONS_OFF;
    sOptions->sel_rand[MENUITEM_RAND_ABILITIES]     = OPTIONS_OFF;
    sOptions->sel_rand[MENUITEM_RAND_BASE_STATS]    = OPTIONS_OFF;
    sOptions->sel_rand[MENUITEM_RAND_TYPES]         = OPTIONS_OFF;
    sOptions->sel_rand[MENUITEM_RAND_EVOS]          = OPTIONS_OFF;

    switch(sOptions->sel_presets[MENUITEM_PRESET_MODE])
    {
        case PRESET_NORMAL:
            sOptions->sel_run[MENUITEM_RUN_SPECIES_ARRAY]   = ARRAY_PROG;
            sOptions->sel_diff[MENUITEM_DIFF_XPMODE]        = XP_75;
            sOptions->sel_diff[MENUITEM_DIFF_STAT_CHANGER]  = OPTIONS_ON;
            sOptions->sel_diff[MENUITEM_DIFF_TRAINER_EVS]   = OPTIONS_OFF;
            sOptions->sel_diff[MENUITEM_DIFF_LEGENDARIES]   = OPTIONS_ON;
            break;
        case PRESET_HARD:
            sOptions->sel_diff[MENUITEM_DIFF_XPMODE]        = XP_50;
            sOptions->sel_diff[MENUITEM_DIFF_STAT_CHANGER]  = OPTIONS_OFF;
            sOptions->sel_diff[MENUITEM_DIFF_TRAINER_EVS]   = OPTIONS_ON;
            sOptions->sel_diff[MENUITEM_DIFF_LEGENDARIES]   = OPTIONS_OFF;
        #ifdef PIT_GEN_9_MODE
            sOptions->sel_diff[MENUITEM_DIFF_TRAINER_GIMMICKS]    = TRAINER_GIMMICKS_RANDOM;
        #endif
            break;
        default:
            break;
    }

    //return to mode menu
    if (sOptions->submenu == MENU_PRESETS)
    {
        sOptions->submenu = MENU_RUN;
        DrawTopBarText();
        ReDrawAll();
        HighlightModeMenuItem();
        DrawDescriptionText();
    }
}
