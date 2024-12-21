#include "global.h"
#include "ui_main_menu.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "pit.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "pokemon_icon.h"
#include "region_map.h"
#include "pokedex.h"
#include "title_screen.h"
#include "main_menu.h"
#include "option_menu.h"
#include "mystery_event_menu.h"
#include "mystery_gift_menu.h"
#include "link.h"
#include "trainer_pokemon_sprites.h"
#include "ui_trainer_stats.h"
#include "credits.h"
#include "start_menu.h"
#include "load_save.h"

/*
 * 
 */
 
//==========DEFINES==========//
struct TrainerStatsResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
	u8 returnMode;
    u16 iconBoxSpriteIds[6];
    u16 iconMonSpriteIds[6];
    u16 mugshotSpriteId;
    u8 sSelectedOption;
};

enum WindowIds
{
    WINDOW_HEADER,
    WINDOW_MIDDLE,
};

enum {
    HW_WIN_CONTINUE,
    HW_WIN_NEW_GAME,
    HW_WIN_OPTIONS,
    HW_WIN_MYSTERY_GIFT,
    HW_WIN_MYSTERY_EVENT,
    HW_WIN_MYSTERY_BOTH,
};

enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

//==========EWRAM==========//
static EWRAM_DATA struct TrainerStatsResources *sTrainerStatsDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
static EWRAM_DATA u8 sSelectedOption = {0};
static EWRAM_DATA u8 menuType = {0};

//==========STATIC=DEFINES==========//
static void TrainerStats_RunSetup(void);
static bool8 TrainerStats_DoGfxSetup(void);
static bool8 TrainerStats_InitBgs(void);
static void TrainerStats_FadeAndBail(void);
static bool8 TrainerStats_LoadGraphics(void);
static void TrainerStats_InitWindows(void);
static void PrintToWindow(u8 windowId, u8 colorIdx);
static void Task_TrainerStatsWaitFadeIn(u8 taskId);
static void Task_TrainerStatsMain(u8 taskId);

//==========Background and Window Data==========//
static const struct BgTemplate sTrainerStatsBgTemplates[] =
{
    {
        .bg = 0,                // Text Background
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 0
    }, 
    {
        .bg = 1,                // Main Background
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    },
    {
        .bg = 2,                // Scroll Background
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .priority = 2
    }
};

static const struct WindowTemplate sTrainerStatsWindowTemplates[] = 
{
    [WINDOW_HEADER] = // Prints the Map and Playtime
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 0,  // position from left (per 8 pixels)
        .tilemapTop = 0,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 3,        // height (per 8 pixels)
        .paletteNum = 0,    // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    },

    [WINDOW_MIDDLE] = // Prints the name, dex number, and badges
    {
        .bg = 0,                   // which bg to print text on
        .tilemapLeft = 0,          // position from left (per 8 pixels)
        .tilemapTop = 2,           // position from top (per 8 pixels)
        .width = 30,               // width (per 8 pixels)
        .height = 17,               // height (per 8 pixels)
        .paletteNum = 0,           // palette index to use for text
        .baseBlock = 1 + (30 * 3), // tile start in VRAM
    },
    DUMMY_WIN_TEMPLATE
};

//  Positions of Hardware/GPU Windows
//       that highlight and hide sections of the Bg
struct HighlightWindowCoords {
    u8 left;
    u8 right;
};

struct HWWindowPosition {
    struct HighlightWindowCoords winh;
    struct HighlightWindowCoords winv;
};


//
//  Graphic and Tilemap Pointers for Bgs and Mughsots
//
static const u32 sMainBgTiles[] = INCBIN_U32("graphics/ui_main_menu/hof_trainer_card_tiles.4bpp.lz");
static const u32 sMainBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/hof_trainer_card_tiles.bin.lz");
static const u16 sMainBgPalette[] = INCBIN_U16("graphics/ui_main_menu/hof_trainer_card.gbapal");

static const u32 sScrollBgTiles[] = INCBIN_U32("graphics/ui_main_menu/scroll_tiles.4bpp.lz");
static const u32 sScrollBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/scroll_tiles.bin.lz");
static const u16 sScrollBgPalette[] = INCBIN_U16("graphics/ui_main_menu/scroll_tiles.gbapal");


//==========UI Initialization from Ghoulslash's UI Shell Branch==========//
void Task_OpenTrainerStats(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {   
        CleanupOverworldWindowsAndTilemaps();
        TrainerStats_Init(CB2_InitTitleScreen, STATS_MODE_TRAINER_CARD); // if need to bail go to title screen
        DestroyTask(taskId);
    }
}

//
//  Setup Menu Functions
//
void TrainerStats_Init(MainCallback callback, u8 mode)
{
    u32 i = 0;
    if ((sTrainerStatsDataPtr = AllocZeroed(sizeof(struct TrainerStatsResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

	if(mode == STATS_MODE_TRAINER_CARD)
	{
		sTrainerStatsDataPtr->returnMode = STATS_MODE_TRAINER_CARD;
	}
	else if (mode == STATS_MODE_HALL_OF_FAME)
	{
		sTrainerStatsDataPtr->returnMode = STATS_MODE_HALL_OF_FAME;
	}
	
    //DebugTestRandomness();
    sTrainerStatsDataPtr->gfxLoadState = 0;
    sTrainerStatsDataPtr->savedCallback = callback;
    SetMainCallback2(TrainerStats_RunSetup);
}

static void TrainerStats_RunSetup(void)
{
    while (1)
    {
        if (TrainerStats_DoGfxSetup() == TRUE)
            break;
    }
}

static void TrainerStats_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void TrainerStats_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ChangeBgY(2, 128, BG_COORD_SUB); // This controls the scrolling of the scroll bg, remove it to stop scrolling
}

//
//  Quit Out Functions
//
static void TrainerStats_FreeResources(void)
{
	DestroySpriteAndFreeResources(&gSprites[sTrainerStatsDataPtr->mugshotSpriteId]);
    try_free(sTrainerStatsDataPtr);
    try_free(sBg1TilemapBuffer);
    try_free(sBg2TilemapBuffer);
    FreeAllWindowBuffers();
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
}

static void Task_TrainerStatsWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sTrainerStatsDataPtr->savedCallback);
        TrainerStats_FreeResources();
        DestroyTask(taskId);
    }
}

static void TrainerStats_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_TrainerStatsWaitFadeAndBail, 0);
    SetVBlankCallback(TrainerStats_VBlankCB);
    SetMainCallback2(TrainerStats_MainCB);
}

static void Task_TrainerStatsWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_TrainerStatsMain;
}

static void Task_TrainerStatsTurnOff(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);

		if (sTrainerStatsDataPtr->returnMode == STATS_MODE_HALL_OF_FAME)
		{
            TrainerStats_FreeResources();
            DestroyTask(taskId);
            ClearSav1();
            ClearSav3();
            gSaveBlock2Ptr->forceNewRun = TRUE;
            AutoSaveDoSaveCallback();
            TrainerStats_OpenMainMenu();
            return;
		}
		else
		{
			SetMainCallback2(sTrainerStatsDataPtr->savedCallback);
		}

        TrainerStats_FreeResources();
        DestroyTask(taskId);
    }
}


//
//  Load Graphics Functions
//
static bool8 TrainerStats_DoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (TrainerStats_InitBgs())
        {
            sTrainerStatsDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            TrainerStats_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (TrainerStats_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        LoadMessageBoxAndBorderGfx();
        u16 facilityClass = ReturnAvatarTrainerFrontPicId(gSaveBlock2Ptr->playerGfxType);
        if (facilityClass == 0xFFFF)
        {
            sTrainerStatsDataPtr->mugshotSpriteId = CreateMonPicSprite(gSaveBlock2Ptr->pokemonAvatarSpecies, 
                        FALSE, 
                        0, 
                        TRUE, 
                        164, 
                        56,
                        15, 
                        TAG_NONE);
        }
        else
		{
			LoadMugshotIconGraphics();
			sTrainerStatsDataPtr->mugshotSpriteId = CreateMugshotExternal();
		}

		gSprites[sTrainerStatsDataPtr->mugshotSpriteId].x = 240 - 48;
		gSprites[sTrainerStatsDataPtr->mugshotSpriteId].y = 56;
        TrainerStats_InitWindows();
        gMain.state++;
        break;
    case 5: // Here is where the sprites are drawn and text is printed
        PrintToWindow(WINDOW_HEADER, FONT_WHITE);
        CreateTask(Task_TrainerStatsWaitFadeIn, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
		SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(TrainerStats_VBlankCB);
        SetMainCallback2(TrainerStats_MainCB);
        return TRUE;
    }
    return FALSE;
}

static bool8 TrainerStats_InitBgs(void)
{
    ResetAllBgsCoordinates();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sTrainerStatsBgTemplates, NELEMS(sTrainerStatsBgTemplates));

    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    memset(sBg1TilemapBuffer, 0, 0x800);
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);

    sBg2TilemapBuffer = Alloc(0x800);
    if (sBg2TilemapBuffer == NULL)
        return FALSE;
    memset(sBg2TilemapBuffer, 0, 0x800);
    SetBgTilemapBuffer(2, sBg2TilemapBuffer);
    ScheduleBgCopyTilemapToVram(2);

    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 TrainerStats_LoadGraphics(void) // Load all the tilesets, tilemaps, spritesheets, and palettes
{
    switch (sTrainerStatsDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sMainBgTiles, 0, 0, 0);
        sTrainerStatsDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sMainBgTilemap, sBg1TilemapBuffer);
            sTrainerStatsDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sScrollBgTiles, 0, 0, 0);
        sTrainerStatsDataPtr->gfxLoadState++;
        break;
    case 3:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sScrollBgTilemap, sBg2TilemapBuffer);
            sTrainerStatsDataPtr->gfxLoadState++;
        }
        break;
    case 4:
        LoadPalette(sMainBgPalette, 0, 32);
        LoadPalette(sScrollBgPalette, 16, 32);
        sTrainerStatsDataPtr->gfxLoadState++;
        break;
    default:
        sTrainerStatsDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void TrainerStats_InitWindows(void) // Init Text Windows
{
    InitWindows(sTrainerStatsWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    
    FillWindowPixelBuffer(WINDOW_HEADER, 0);
    PutWindowTilemap(WINDOW_HEADER);
    CopyWindowToVram(WINDOW_HEADER, 3);

    FillWindowPixelBuffer(WINDOW_MIDDLE, 0);
    PutWindowTilemap(WINDOW_MIDDLE);
    CopyWindowToVram(WINDOW_MIDDLE, 3);
}

//
//  Print 
//
static const u8 sText_ModeNormal[]          = _("Mode: NORM");
static const u8 sText_ModeHard[]            = _("Mode: HARD");
static const u8 sText_ModeCustom[]          = _("Mode: CUSTOM");

static const u8 sText_ExpNormal[]          = _("Exp: Normal");
static const u8 sText_ExpHard[]            = _("Exp: Hard");
static const u8 sText_ExpNone[]          = _("Exp: None");

static const u8 sText_Money1x[]          = _("Money: 1x");
static const u8 sText_Money2x[]          = _("Money: 2x");
static const u8 sText_Money12x[]          = _("Money: 1/2x");

static const u8 sText_PitStp5x[]          = _("Shop: 5 fl.");
static const u8 sText_PitStp10x[]          = _("Shop: 10 fl.");

static const u8 sText_ModeEVsOn[]          = _("EVs: On");
static const u8 sText_ModeEVsOff[]            = _("EVs: Off");

static const u8 sText_BattleMode_Singles[]  = _("Singles");
static const u8 sText_BattleMode_Doubles[]  = _("Doubles");
static const u8 sText_BattleMode_Mixed[]  = _("Mixed");

static const u8 sText_Randomizer_Moves[]     = _("Moves");
static const u8 sText_Randomizer_Ability[]     = _("Ability");
static const u8 sText_Randomizer_Stats[]     = _("Stats");
static const u8 sText_Randomizer_Types[]     = _("Types");
static const u8 sText_Randomizer_Evos[]     = _("Evos");
static const u8 sText_Randomizer_Weather[]     = _("Weather");

static const u8 sText_Stat_KOs[]     		= _("Run KOs:");
static const u8 sText_Stat_Revives[]     	= _("Run Revives:");
static const u8 sText_Stat_Highscore[]     	= _("Highscore:");
static const u8 sText_Stat_Clears[]     	= _("Pit Clears:");
static const u8 sText_Stat_Attempts[]     	= _("Pit Attempts:");

static const u8 sText_Legends[]           = _("Legendaries");
static const u8 sText_StatEdit[]           = _("Stat Edit");
static const u8 sText_Megas[]           = _("Megas");
static const u8 sText_3MonMode[]           = _("3 Mon Mode");
static const u8 sText_SkipChoice[]           = _("Skip Choice");

#define SETTINGS_X_POS 20
#define SETTINGS2_X_POSITION 90
#define SETTINGS_Y_START_POS 7
#define SETTINGS_Y_DIFFERENCE 12
#define SETTINGS2_Y_DIFFERENCE 12

#define RANDOMIZER_X_POS 20
#define RANDOMIZER_X_DIFFERENCE 42
#define RANDOMIZER_Y_START_POS 94
#define RANDOMIZER_Y_DIFFERENCE 12

#define STATS_X_START_POS 140
#define STATS_X_RIGHT_POS 197
#define STATS_Y_START_POS 92
#define STATS_Y_DIFFERENCE 10

static const u8 sWinMarkerGfx[]         = INCBIN_U8("graphics/ui_main_menu/star.4bpp");

#ifdef PIT_GEN_3_MODE
const u8 gText_VersionText[] = _("v2.0.1 Gen3");
#endif
#ifdef PIT_GEN_5_MODE
const u8 gText_VersionText[] = _("v2.0.1 Gen5");
#endif
#ifdef PIT_GEN_9_MODE
const u8 gText_VersionText[] = _("v2.0.1 Gen9");
#endif

static void PrintToWindow(u8 windowId, u8 colorIdx)
{
    const u8 colors[3] = {0,  5,  2}; 
	const u8 colors2[3] = {0,  5,  2}; 
	const u8 green_colors[3] = {0,  6,  2}; 
	const u8 red_colors[3] = {0,  7,  2}; 
    u8 mapDisplayHeader[24];
    u8 *withoutPrefixPtr, *playTimePtr;
    u16 dexCount = 0; u8 badgeCount = 0;
    u32 i = 0;
	const u8 *modeText;

    FillWindowPixelBuffer(WINDOW_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WINDOW_MIDDLE, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    if(FlagGet(FLAG_TEMP_HOF_VICTORY))
        BlitBitmapToWindow(WINDOW_MIDDLE, sWinMarkerGfx, 240 - 24, 80 - 24, 16, 16);
    
	// Game Mode
    switch(gSaveBlock2Ptr->modeBattleMode)
    {
        case 0:
            modeText = sText_BattleMode_Singles;
            break;
        case 1:
            modeText = sText_BattleMode_Doubles;
            break;
        case 2:
            modeText = sText_BattleMode_Mixed;
            break;
        default:
            modeText = sText_BattleMode_Singles;
            break;
    }
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS, 0, 0, colors2, TEXT_SKIP_DRAW, modeText);

	// Exp
	u8 expMode = 0;
	if ((gSaveBlock2Ptr->modeXP == 2))
        expMode = 2;
	else
	{
		if (gSaveBlock2Ptr->modeXP == 1)
			expMode = 1;
		else
			expMode = 0;
	}

    switch(expMode)
    {
        case 0:
            modeText = sText_ExpNormal;
            break;
        case 1:
            modeText = sText_ExpHard;
            break;
        case 2:
            modeText = sText_ExpNone;
            break;
        default:
            modeText = sText_ExpNormal;
            break;
    }
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + SETTINGS_Y_DIFFERENCE, 0, 0, colors2, TEXT_SKIP_DRAW, modeText);

	// Money
    switch(gSaveBlock2Ptr->modeCashRewards)
    {
        case 0:
            modeText = sText_Money1x;
            break;
        case 1:
            modeText = sText_Money2x;
            break;
        case 2:
            modeText = sText_Money12x;
            break;
        default:
            modeText = sText_Money1x;
            break;
    }
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + (SETTINGS_Y_DIFFERENCE * 2), 0, 0, colors2, TEXT_SKIP_DRAW, modeText);

	// Pit Stop
    if(!gSaveBlock2Ptr->modeHealFloors10)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + (SETTINGS_Y_DIFFERENCE * 3), 0, 0, colors2, TEXT_SKIP_DRAW, sText_PitStp5x);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + (SETTINGS_Y_DIFFERENCE * 3), 0, 0, colors2, TEXT_SKIP_DRAW, sText_PitStp10x);

    // Trainer EVs
    if(!gSaveBlock2Ptr->modeTrainerEVs)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + (SETTINGS_Y_DIFFERENCE * 4), 0, 0, colors2, TEXT_SKIP_DRAW, sText_ModeEVsOn);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS_X_POS, SETTINGS_Y_START_POS + (SETTINGS_Y_DIFFERENCE * 4), 0, 0, colors2, TEXT_SKIP_DRAW, sText_ModeEVsOff);


    //
    // Second Column
    //

	// Legends
    if(!gSaveBlock2Ptr->modeLegendaries)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 0), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Legends);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 0), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Legends);


	// StatEdit
    if(!gSaveBlock2Ptr->modeStatChanger)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 1), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_StatEdit);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 1), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_StatEdit);


	// Megas
    if(!gSaveBlock2Ptr->modeMegas)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 2), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Megas);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 2), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Megas);


	// 3 Mon Mode
    if(!gSaveBlock2Ptr->mode3MonsOnly)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 3), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_3MonMode);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 3), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_3MonMode);


	// Skip Mon Choice
    if(!gSaveBlock2Ptr->modeNoCaseChoice)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 4), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_SkipChoice);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, SETTINGS2_X_POSITION, SETTINGS_Y_START_POS + (SETTINGS2_Y_DIFFERENCE * 4), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_SkipChoice);



	// sText_Randomizer_Moves
    if(!gSaveBlock2Ptr->randomMoves)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 0), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Moves);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 0), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Moves);


	// sText_Randomizer_Ability
    if(!gSaveBlock2Ptr->randomAbilities)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS, 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Ability);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS, 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Ability);


	// sText_Randomizer_Stats
    if(!gSaveBlock2Ptr->randomBST)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 1), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Stats);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 1), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Stats);


	// sText_Randomizer_Types
    if(!gSaveBlock2Ptr->randomType)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 1), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Types);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 1), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Types);


	// sText_Randomizer_Evos
    if(!gSaveBlock2Ptr->randomEvos)
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 2), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Evos);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 2), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Evos);


	// sText_Randomizer_Weather
    if(!(gSaveBlock2Ptr->randomBattleWeather == 2))
    	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 2), 0, 0, green_colors, TEXT_SKIP_DRAW, sText_Randomizer_Weather);
	else
		AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, RANDOMIZER_X_POS + RANDOMIZER_X_DIFFERENCE, RANDOMIZER_Y_START_POS + (RANDOMIZER_Y_DIFFERENCE * 2), 0, 0, red_colors, TEXT_SKIP_DRAW, sText_Randomizer_Weather);

	// RUN KOS
	ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->statsRunKOs, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, sText_Stat_KOs);
	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_START_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 0), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_RIGHT_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 0), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar1);

	// RUN REVIVES
	/*ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->statsRunRevives, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, sText_Stat_Revives);
	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_START_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 1), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_RIGHT_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 1), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar1);*/

	// HIGHSCORE
	ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->statsAllHighscore, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, sText_Stat_Highscore);
	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_START_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 1), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_RIGHT_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 1), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar1);

    // PIT ATTEMPTS
	ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->statsAllAttempts, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, sText_Stat_Attempts);
	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_START_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 2), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_RIGHT_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 2), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar1);

	// CLEARS
	ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->statsAllClears, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringExpandPlaceholders(gStringVar4, sText_Stat_Clears);
	AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_START_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 3), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    AddTextPrinterParameterized4(WINDOW_MIDDLE, FONT_SMALL_NARROW, STATS_X_RIGHT_POS, STATS_Y_START_POS + (STATS_Y_DIFFERENCE * 3), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar1);


    // Print Map Name In Header
    withoutPrefixPtr = &(mapDisplayHeader[3]);
    GetMapName(withoutPrefixPtr, GetCurrentRegionMapSectionId(), 0);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    BufferMapFloorString();
    StringCopy(gStringVar2, mapDisplayHeader);
    StringExpandPlaceholders(mapDisplayHeader, gStringVar2);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NARROW, GetStringCenterAlignXOffset(FONT_NARROW, withoutPrefixPtr, 10 * 8) + 76, 7, 0, 0, colors, 0xFF, mapDisplayHeader);

    // Print Player Name
    AddTextPrinterParameterized3(WINDOW_HEADER, FONT_NORMAL, 20, 7, colors, TEXT_SKIP_DRAW, gSaveBlock2Ptr->playerName);

    // Print Version Number
    AddTextPrinterParameterized3(WINDOW_HEADER, FONT_NARROW, 168, 7, colors, TEXT_SKIP_DRAW, gText_VersionText);

    PutWindowTilemap(WINDOW_MIDDLE);
    CopyWindowToVram(WINDOW_MIDDLE, 3);
    PutWindowTilemap(WINDOW_HEADER);
    CopyWindowToVram(WINDOW_HEADER, 3);
}


//
//  Main Input Control Task
//
static void Task_TrainerStatsMain(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON | START_BUTTON))
    {
        PlaySE(SE_SELECT);
        FlagClear(FLAG_TEMP_HOF_VICTORY);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
		if (sTrainerStatsDataPtr->returnMode == STATS_MODE_HALL_OF_FAME)
			sTrainerStatsDataPtr->savedCallback = CB2_InitTitleScreen;
		gTasks[taskId].func = Task_TrainerStatsTurnOff;
	}
}
