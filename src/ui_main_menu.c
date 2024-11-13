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
#include "ui_outfits.h"
#include "ui_mode_menu.h"
#include "ui_options_menu.h"

/*
 * 
 */
 
//==========DEFINES==========//
struct MainMenuResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u16 iconBoxSpriteIds[6];
    u16 iconMonSpriteIds[6];
    u16 mugshotSpriteId;
    u8 sSelectedOption;
};

enum WindowIds
{
    WINDOW_HEADER,
};

enum {
    HW_WIN_CONTINUE,
    HW_WIN_NEW_GAME,
    HW_WIN_OPTIONS,
    HW_WIN_MYSTERY_GIFT,
    HW_WIN_MYSTERY_EVENT,
    HW_WIN_MYSTERY_BOTH,
};

enum {
    HW_WIN_CUSTOM,
    HW_WIN_NORMAL,
    HW_WIN_HARD,
};


enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};

enum
{
    HAS_NO_SAVED_GAME,  //NEW GAME, OPTION
    HAS_SAVED_GAME,     //CONTINUE, NEW GAME, OPTION
    HAS_MYSTERY_GIFT,   //CONTINUE, NEW GAME, MYSTERY GIFT, OPTION
    HAS_MYSTERY_EVENTS, //CONTINUE, NEW GAME, MYSTERY GIFT, MYSTERY EVENTS, OPTION
};

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

//==========EWRAM==========//
static EWRAM_DATA struct MainMenuResources *sMainMenuDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg3TilemapBuffer = NULL;
static EWRAM_DATA u8 sSelectedOption = {0};
static EWRAM_DATA u8 sNewGameSelectedOption = {0};
static EWRAM_DATA u8 menuType = {0};
static EWRAM_DATA u8 sAlreadySelectedAvatar = {0};

//==========STATIC=DEFINES==========//
static void MainMenu_RunSetup(void);
static bool8 MainMenu_DoGfxSetup(void);
static bool8 MainMenu_InitBgs(void);
static void MainMenu_FadeAndBail(void);
static bool8 MainMenu_LoadGraphics(u8 reload);
static void MainMenu_InitWindows(void);
static void PrintToWindow(u8 windowId, u8 colorIdx);
static void Task_MainMenuWaitFadeIn(u8 taskId);
static void Task_MainMenuMain(u8 taskId);
static void MainMenu_InitializeGPUWindows(void);
static bool8 NewGame_LoadGraphics(u8 fromMainMenu);
static void Task_MainNewGameMenu(u8 taskId);

static void CreateMugshot();
static void DestroyMugshot();
static void CreateIconShadow();
static void DestroyIconShadow();
static u32 GetHPEggCyclePercent(u32 partyIndex);
static void CreatePartyMonIcons();
static void DestroyMonIcons();
static void PrintNewGameToWindow(u8 windowId, u8 colorIdx);
static void MoveNewGameHWindowsWithInput(void);


//==========Background and Window Data==========//
static const struct BgTemplate sMainMenuBgTemplates[] =
{
    {
        .bg = 0,                // Text Background
        .charBaseIndex = 0,
        .mapBaseIndex = 22,
        .priority = 0
    }, 
    {
        .bg = 1,                // Main Background
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 1
    },
    {
        .bg = 2,                // Scroll Background
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .priority = 2
    },
    {
        .bg = 3,                // Main Background
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .priority = 1
    },
};

static const struct WindowTemplate sMainMenuWindowTemplates[] = 
{
    [WINDOW_HEADER] = // Prints the Map and Playtime
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 0,  // position from left (per 8 pixels)
        .tilemapTop = 0,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 20,        // height (per 8 pixels)
        .paletteNum = 0,    // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
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

static const struct HWWindowPosition HWinCoords[6] = 
{
    [HW_WIN_CONTINUE]        = {{7, 233},   {7, 89},},
    [HW_WIN_NEW_GAME]        = {{7, 113},   {103, 122},},
    [HW_WIN_OPTIONS]         = {{126, 233}, {103, 122},},
    [HW_WIN_MYSTERY_GIFT]    = {{7, 113},   {135, 154},},
    [HW_WIN_MYSTERY_EVENT]   = {{126, 233}, {135, 154},},
    [HW_WIN_MYSTERY_BOTH]    = {{7, 233},   {135, 154}},
};

static const struct HWWindowPosition HWinNewGameCoords[6] = 
{
    [HW_WIN_CUSTOM]        = {{7, 233},   {7, 40},},
    [HW_WIN_NORMAL]        = {{7, 233},   {40, 70},},
    [HW_WIN_HARD]          = {{7, 233},   {70, 100},},
};


//
//  Graphic and Tilemap Pointers for Bgs and Mughsots
//
static const u32 sMainBgTiles[] = INCBIN_U32("graphics/ui_main_menu/main_tiles.4bpp.lz");
static const u32 sMainBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/main_tiles.bin.lz");
static const u16 sMainBgPalette[] = INCBIN_U16("graphics/ui_main_menu/main_tiles.gbapal");

static const u32 sNewGameBgTiles[] = INCBIN_U32("graphics/ui_main_menu/new_game_menu_tiles.4bpp.lz");
static const u32 sNewGameBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/new_game_menu_tiles.bin.lz");
static const u32 sNewGameTextBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/new_game_text_tiles.bin.lz");
static const u16 sNewGameBgPalette[] = INCBIN_U16("graphics/ui_main_menu/new_game_menu_tiles.gbapal");

static const u32 sMainBgTilesFem[] = INCBIN_U32("graphics/ui_main_menu/main_tiles_fem.4bpp.lz");
static const u32 sMainBgTilemapFem[] = INCBIN_U32("graphics/ui_main_menu/main_tiles_fem.bin.lz");
static const u16 sMainBgPaletteFem[] = INCBIN_U16("graphics/ui_main_menu/main_tiles_fem.gbapal");

static const u32 sScrollBgTiles[] = INCBIN_U32("graphics/ui_main_menu/scroll_tiles.4bpp.lz");
static const u32 sScrollBgTilemap[] = INCBIN_U32("graphics/ui_main_menu/scroll_tiles.bin.lz");
static const u16 sScrollBgPalette[] = INCBIN_U16("graphics/ui_main_menu/scroll_tiles.gbapal");

static const u16 sIconBox_Pal[] = INCBIN_U16("graphics/ui_main_menu/icon_shadow.gbapal");
static const u32 sIconBox_Gfx[] = INCBIN_U32("graphics/ui_main_menu/icon_shadow.4bpp.lz");

static const u16 sIconBox_PalFem[] = INCBIN_U16("graphics/ui_main_menu/icon_shadow_fem.gbapal");
static const u32 sIconBox_GfxFem[] = INCBIN_U32("graphics/ui_main_menu/icon_shadow_fem.4bpp.lz");

static const u16 sBrendanMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/brendan_mugshot.gbapal");
static const u32 sBrendanMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/brendan_mugshot.4bpp.lz");
static const u16 sMayMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/may_mugshot.gbapal");
static const u32 sMayMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/may_mugshot.4bpp.lz");

static const u16 sRedMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/red_mugshot.gbapal");
static const u32 sRedMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/red_mugshot.4bpp.lz");
static const u16 sLeafMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/leaf_mugshot.gbapal");
static const u32 sLeafMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/leaf_mugshot.4bpp.lz");

static const u16 sLucasMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/lucas_mugshot.gbapal");
static const u32 sLucasMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/lucas_mugshot.4bpp.lz");
static const u16 sDawnMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/dawn_mugshot.gbapal");
static const u32 sDawnMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/dawn_mugshot.4bpp.lz");

static const u16 sStevenMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/steven.gbapal");
static const u32 sStevenMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/steven.4bpp.lz");
static const u16 sCynthiaMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/cynthia.gbapal");
static const u32 sCynthiaMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/cynthia.4bpp.lz");

static const u16 sOakMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/oak.gbapal");
static const u32 sOakMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/oak.4bpp.lz");
static const u16 sPhoebeMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/phoebe.gbapal");
static const u32 sPhoebeMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/phoebe.4bpp.lz");

static const u16 sEthanMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/ethan.gbapal");
static const u32 sEthanMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/ethan.4bpp.lz");
static const u16 sLyraMugshot_Pal[] = INCBIN_U16("graphics/ui_main_menu/lyra.gbapal");
static const u32 sLyraMugshot_Gfx[] = INCBIN_U32("graphics/ui_main_menu/lyra.4bpp.lz");

//
//  Sprite Data for Mugshots and Icon Shadows 
//
#define TAG_MUGSHOT 30012
#define TAG_ICON_BOX 30006
static const struct OamData sOamData_Mugshot =
{
    .size = SPRITE_SIZE(64x64),
    .shape = SPRITE_SHAPE(64x64),
    .priority = 1,
};

static const struct CompressedSpriteSheet sSpriteSheet_BrendanMugshot =
{
    .data = sBrendanMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_BrendanMugshot =
{
    .data = sBrendanMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_MayMugshot =
{
    .data = sMayMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_MayMugshot =
{
    .data = sMayMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_RedMugshot =
{
    .data = sRedMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_RedMugshot =
{
    .data = sRedMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_LeafMugshot =
{
    .data = sLeafMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_LeafMugshot =
{
    .data = sLeafMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_LucasMugshot =
{
    .data = sLucasMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_LucasMugshot =
{
    .data = sLucasMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_DawnMugshot =
{
    .data = sDawnMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_DawnMugshot =
{
    .data = sDawnMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_StevenMugshot =
{
    .data = sStevenMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_StevenMugshot =
{
    .data = sStevenMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_CynthiaMugshot =
{
    .data = sCynthiaMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_CynthiaMugshot =
{
    .data = sCynthiaMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_OakMugshot =
{
    .data = sOakMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_OakMugshot =
{
    .data = sOakMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_PhoebeMugshot =
{
    .data = sPhoebeMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_PhoebeMugshot =
{
    .data = sPhoebeMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_EthanMugshot =
{
    .data = sEthanMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_EthanMugshot =
{
    .data = sEthanMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const struct CompressedSpriteSheet sSpriteSheet_LyraMugshot =
{
    .data = sLyraMugshot_Gfx,
    .size = 64*64*1/2,
    .tag = TAG_MUGSHOT,
};

static const struct SpritePalette sSpritePal_LyraMugshot =
{
    .data = sLyraMugshot_Pal,
    .tag = TAG_MUGSHOT
};

static const union AnimCmd sSpriteAnim_Mugshot[] =
{
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sSpriteAnimTable_Mugshot[] =
{
    sSpriteAnim_Mugshot,
};

static const struct SpriteTemplate sSpriteTemplate_Mugshot =
{
    .tileTag = TAG_MUGSHOT,
    .paletteTag = TAG_MUGSHOT,
    .oam = &sOamData_Mugshot,
    .anims = sSpriteAnimTable_Mugshot,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_IconBox =
{
    .size = SPRITE_SIZE(32x32),
    .shape = SPRITE_SHAPE(32x32),
    .priority = 1,
};

static const struct CompressedSpriteSheet sSpriteSheet_IconBox =
{
    .data = sIconBox_Gfx,
    .size = 32*32*1/2,
    .tag = TAG_ICON_BOX,
};

static const struct CompressedSpriteSheet sSpriteSheet_IconBoxFem =
{
    .data = sIconBox_GfxFem,
    .size = 32*32*1/2,
    .tag = TAG_ICON_BOX,
};

static const struct SpritePalette sSpritePal_IconBox =
{
    .data = sIconBox_Pal,
    .tag = TAG_ICON_BOX
};

static const struct SpritePalette sSpritePal_IconBoxFem =
{
    .data = sIconBox_PalFem,
    .tag = TAG_ICON_BOX
};

static const union AnimCmd sSpriteAnim_IconBox0[] =
{
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sSpriteAnimTable_IconBox[] =
{
    sSpriteAnim_IconBox0,
};

static const struct SpriteTemplate sSpriteTemplate_IconBox =
{
    .tileTag = TAG_ICON_BOX,
    .paletteTag = TAG_ICON_BOX,
    .oam = &sOamData_IconBox,
    .anims = sSpriteAnimTable_IconBox,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

//==========UI Initialization from Ghoulslash's UI Shell Branch==========//
void Task_OpenMainMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {   
        switch (data[0]) // This data[0] comes from the main_menu.c Task_DisplayMainMenu, 
        {                //  where the UI is initialized by swapping a task func with this one 
            case HAS_NO_SAVED_GAME:
            default:
                if(sAlreadySelectedAvatar != 1)
                {
                    sAlreadySelectedAvatar = 1;
                    OutfitsMenu_Init(CB2_InitTitleScreen, OUTFITS_NO_SAVE_AVATAR_MENU);
                    DestroyTask(taskId);
                    return;
                }
                menuType = HAS_SAVED_GAME;
                break;
            case HAS_SAVED_GAME:       
            case HAS_MYSTERY_GIFT:
            case HAS_MYSTERY_EVENTS:
                menuType = HAS_SAVED_GAME;
                break;
        }
        CleanupOverworldWindowsAndTilemaps();
        MainMenu_Init(CB2_InitTitleScreen); // if need to bail go to title screen
        DestroyTask(taskId);
    }
}

//
//  Setup Menu Functions
//
void MainMenu_Init(MainCallback callback)
{
    u32 i = 0;
    if ((sMainMenuDataPtr = AllocZeroed(sizeof(struct MainMenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }
    //DebugTestRandomness();
    sMainMenuDataPtr->gfxLoadState = 0;
    sMainMenuDataPtr->savedCallback = callback;
    sNewGameSelectedOption = 0xFF;
    for(i = 0; i < 6; i++)
    {
        sMainMenuDataPtr->iconBoxSpriteIds[i] = SPRITE_NONE;
        sMainMenuDataPtr->iconMonSpriteIds[i] = SPRITE_NONE;
    }
    
    SetMainCallback2(MainMenu_RunSetup);
}

static void MainMenu_RunSetup(void)
{
    while (1)
    {
        if (MainMenu_DoGfxSetup() == TRUE)
            break;
    }
}

static void MainMenu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void MainMenu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ChangeBgY(2, 128, BG_COORD_SUB); // This controls the scrolling of the scroll bg, remove it to stop scrolling
}

//
//  Quit Out Functions
//
static void MainMenu_FreeResources(void)
{
    FreeAllWindowBuffers();
    DestroyMugshot();
    DestroyIconShadow();
    DestroyMonIcons();
    try_free(sMainMenuDataPtr);
    try_free(sBg1TilemapBuffer);
    try_free(sBg2TilemapBuffer);
    try_free(sBg3TilemapBuffer);
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
}

static void Task_MainMenuWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sMainMenuDataPtr->savedCallback);
        MainMenu_FreeResources();
        DestroyTask(taskId);
    }
}

static void MainMenu_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_MainMenuWaitFadeAndBail, 0);
    SetVBlankCallback(MainMenu_VBlankCB);
    SetMainCallback2(MainMenu_MainCB);
}

static void Task_MainMenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if(sAlreadySelectedAvatar == 1)
            gTasks[taskId].func = Task_MainNewGameMenu;
        else
            gTasks[taskId].func = Task_MainMenuMain;
    }
        
}

void LoadNormalModePresets(void)
{

}

void LoadHardModePresets(void)
{
    
}

void LoadCustomModePresets(void)
{

}


static void Task_MainMenuTurnOff(u8 taskId)
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

        if (sNewGameSelectedOption != 0xFF)
        {
            if (sNewGameSelectedOption == 0)
            {
                gTasks[taskId].func = Task_OpenModeMenu;
                MainMenu_FreeResources();
                return;
            }
            if (sNewGameSelectedOption == 1)
            {
                LoadNormalModePresets();
                sMainMenuDataPtr->savedCallback = CB2_NewGameBirchSpeech_FromNewMainMenu;
            }
            if (sNewGameSelectedOption == 2)
            {
                LoadHardModePresets();
                sMainMenuDataPtr->savedCallback = CB2_NewGameBirchSpeech_FromNewMainMenu;
            }
        }

        SetMainCallback2(sMainMenuDataPtr->savedCallback);
        MainMenu_FreeResources();
        DestroyTask(taskId);
    }
}


//
//  Load Graphics Functions
//
static bool8 MainMenu_DoGfxSetup(void)
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
        MainMenu_InitializeGPUWindows();
        if(sAlreadySelectedAvatar == 1)
        {
            sNewGameSelectedOption = 0;
            MoveNewGameHWindowsWithInput();
            SetGpuReg(REG_OFFSET_WIN1H, 0);
            SetGpuReg(REG_OFFSET_WIN1V, 0);
        }
        gMain.state++;
        break;
    case 2:
        if (MainMenu_InitBgs())
        {
            sMainMenuDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            MainMenu_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if(sAlreadySelectedAvatar == 0)
        {
            if (MainMenu_LoadGraphics(FALSE) == TRUE)
                gMain.state++;
        }
        else
        {
            if (NewGame_LoadGraphics(FALSE) == TRUE)
                gMain.state++;
        }
        break;
    case 4:
        LoadMessageBoxAndBorderGfxOverride();
        MainMenu_InitWindows();
        gMain.state++;
        break;
    case 5: // Here is where the sprites are drawn and text is printed
        if(sAlreadySelectedAvatar == 0)
            PrintToWindow(WINDOW_HEADER, FONT_WHITE);
        else
            PrintNewGameToWindow(WINDOW_HEADER, FONT_WHITE);

        if(sAlreadySelectedAvatar == 0)
        {
            CreateIconShadow();
            CreatePartyMonIcons();
            CreateMugshot();
        }

        CreateTask(Task_MainMenuWaitFadeIn, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        if(sAlreadySelectedAvatar == 1)
            ShowBg(3);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(MainMenu_VBlankCB);
        SetMainCallback2(MainMenu_MainCB);
        return TRUE;
    }
    return FALSE;
}

static bool8 MainMenu_InitBgs(void)
{
    ResetAllBgsCoordinates();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sMainMenuBgTemplates, NELEMS(sMainMenuBgTemplates));

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

    sBg3TilemapBuffer = Alloc(0x800);
    if (sBg3TilemapBuffer == NULL)
        return FALSE;
    memset(sBg3TilemapBuffer, 0, 0x800);
    SetBgTilemapBuffer(3, sBg3TilemapBuffer);
    ScheduleBgCopyTilemapToVram(3);

    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    HideBg(3);
    return TRUE;
}

static void MainMenu_InitializeGPUWindows(void) // This function creates the windows that highlight an option and cover mystery options when not enabled
{
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN1_ON | DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP); // Turn on Windows 0 and 1 and Enable Sprites
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(HWinCoords[sSelectedOption].winh.left, HWinCoords[sSelectedOption].winh.right));  // Set Window 0 width/height Which defines the not darkened space
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(HWinCoords[sSelectedOption].winv.left, HWinCoords[sSelectedOption].winv.right));
    switch(menuType)
    {
            case HAS_SAVED_GAME:    // The three Window 1 states either block out the mystery buttons both, just the mystery event, or nothing. 
                SetGpuReg(REG_OFFSET_WIN1H,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_BOTH].winh.left, HWinCoords[HW_WIN_MYSTERY_BOTH].winh.right));
                SetGpuReg(REG_OFFSET_WIN1V,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_BOTH].winv.left, HWinCoords[HW_WIN_MYSTERY_BOTH].winv.right));
                break;   
            case HAS_MYSTERY_GIFT:
                SetGpuReg(REG_OFFSET_WIN1H,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_EVENT].winh.left, HWinCoords[HW_WIN_MYSTERY_EVENT].winh.right));
                SetGpuReg(REG_OFFSET_WIN1V,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_EVENT].winv.left, HWinCoords[HW_WIN_MYSTERY_EVENT].winv.right));
                break;
        }

    SetGpuReg(REG_OFFSET_WININ, (WININ_WIN1_BG0 | WININ_WIN1_BG2 | WININ_WIN1_BG3) | (WININ_WIN0_BG_ALL | WININ_WIN0_OBJ)); // Set Win 0 Active everywhere, Win 1 active on everything except bg 1 
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_ALL);                                                                     // where the main tiles are so the window hides whats behind it
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_OBJ);   // Set Darken Effect on things not in the window on bg 0, 1, and sprite layer
    SetGpuReg(REG_OFFSET_BLDY, 7);  // Set Level of Darken effect, can be changed 0-16
}

static void MoveHWindowsWithInput(void) // Update GPU windows after selection is changed
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(HWinCoords[sSelectedOption].winh.left, HWinCoords[sSelectedOption].winh.right));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(HWinCoords[sSelectedOption].winv.left, HWinCoords[sSelectedOption].winv.right));
}


static void MoveNewGameHWindowsWithInput(void) // Update GPU windows after selection is changed
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(HWinNewGameCoords[sNewGameSelectedOption].winh.left, HWinNewGameCoords[sNewGameSelectedOption].winh.right));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(HWinNewGameCoords[sNewGameSelectedOption].winv.left, HWinNewGameCoords[sNewGameSelectedOption].winv.right));
}


void LoadMugshotIconGraphics(void)
{
    if(gSaveBlock2Ptr->playerGfxType == 0) {
        LoadCompressedSpriteSheet(&sSpriteSheet_BrendanMugshot);
        LoadSpritePalette(&sSpritePal_BrendanMugshot);
    }
    else if (gSaveBlock2Ptr->playerGfxType == 1){
        LoadCompressedSpriteSheet(&sSpriteSheet_MayMugshot);
        LoadSpritePalette(&sSpritePal_MayMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 2){
        LoadCompressedSpriteSheet(&sSpriteSheet_RedMugshot);
        LoadSpritePalette(&sSpritePal_RedMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 3){
        LoadCompressedSpriteSheet(&sSpriteSheet_LeafMugshot);
        LoadSpritePalette(&sSpritePal_LeafMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 4) {
        LoadCompressedSpriteSheet(&sSpriteSheet_LucasMugshot);
        LoadSpritePalette(&sSpritePal_LucasMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 5){
        LoadCompressedSpriteSheet(&sSpriteSheet_DawnMugshot);
        LoadSpritePalette(&sSpritePal_DawnMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 6) {
        LoadCompressedSpriteSheet(&sSpriteSheet_EthanMugshot);
        LoadSpritePalette(&sSpritePal_EthanMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 7){
        LoadCompressedSpriteSheet(&sSpriteSheet_LyraMugshot);
        LoadSpritePalette(&sSpritePal_LyraMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 8) {
        LoadCompressedSpriteSheet(&sSpriteSheet_StevenMugshot);
        LoadSpritePalette(&sSpritePal_StevenMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 9){
        LoadCompressedSpriteSheet(&sSpriteSheet_CynthiaMugshot);
        LoadSpritePalette(&sSpritePal_CynthiaMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 10) {
        LoadCompressedSpriteSheet(&sSpriteSheet_OakMugshot);
        LoadSpritePalette(&sSpritePal_OakMugshot);
    }
    else if(gSaveBlock2Ptr->playerGfxType == 11){
        LoadCompressedSpriteSheet(&sSpriteSheet_PhoebeMugshot);
        LoadSpritePalette(&sSpritePal_PhoebeMugshot);
    }
}


static bool8 NewGame_LoadGraphics(u8 fromMainMenu) // Load all the tilesets, tilemaps, spritesheets, and palettes
{
    switch (sMainMenuDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sNewGameBgTiles, 0, 0, 0);
        sMainMenuDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sNewGameBgTilemap, sBg1TilemapBuffer);
            sMainMenuDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        if(fromMainMenu)
        {
            sMainMenuDataPtr->gfxLoadState++;
            break;
        }
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sScrollBgTiles, 0, 0, 0);
        sMainMenuDataPtr->gfxLoadState++;
        break;
    case 3:
        if(fromMainMenu)
        {
            sMainMenuDataPtr->gfxLoadState++;
            break;
        }
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sScrollBgTilemap, sBg2TilemapBuffer);
            sMainMenuDataPtr->gfxLoadState++;
        }
        break;
    case 4:
        LoadPalette(sNewGameBgPalette, 0, 32);
        if(fromMainMenu)
        {
            sMainMenuDataPtr->gfxLoadState++;
            break;
        }
        LoadPalette(sScrollBgPalette, 16, 32);
        sMainMenuDataPtr->gfxLoadState++;
        break;
    case 5:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sNewGameTextBgTilemap, sBg3TilemapBuffer);
            sMainMenuDataPtr->gfxLoadState++;
        }
        break;
    default:
        ScheduleBgCopyTilemapToVram(1);
        ScheduleBgCopyTilemapToVram(3);
        if(fromMainMenu)
            ScheduleBgCopyTilemapToVram(2);
        sMainMenuDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static bool8 MainMenu_LoadGraphics(u8 reload) // Load all the tilesets, tilemaps, spritesheets, and palettes
{
    switch (sMainMenuDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        if (gSaveBlock2Ptr->playerGender == MALE)
        {
            DecompressAndCopyTileDataToVram(1, sMainBgTiles, 0, 0, 0);
        }
        else
        {
            DecompressAndCopyTileDataToVram(1, sMainBgTilesFem, 0, 0, 0);
        }
        sMainMenuDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
            {
                LZDecompressWram(sMainBgTilemap, sBg1TilemapBuffer);
            }
            else
            {
                LZDecompressWram(sMainBgTilemapFem, sBg1TilemapBuffer);
            }
            sMainMenuDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        if(reload)
        {
            sMainMenuDataPtr->gfxLoadState++;
            break;
        }
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sScrollBgTiles, 0, 0, 0);
        sMainMenuDataPtr->gfxLoadState++;
        break;
    case 3:
        if(reload)
        {
            sMainMenuDataPtr->gfxLoadState++;
            break;
        }
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sScrollBgTilemap, sBg2TilemapBuffer);
            sMainMenuDataPtr->gfxLoadState++;
        }
        break;
    case 4:
        LoadMugshotIconGraphics();
        if(gSaveBlock2Ptr->playerGender == MALE)
        {
            LoadCompressedSpriteSheet(&sSpriteSheet_IconBox);
            LoadSpritePalette(&sSpritePal_IconBox);           
            LoadPalette(sMainBgPalette, 0, 32);
        }
        else
        {
            LoadCompressedSpriteSheet(&sSpriteSheet_IconBoxFem);
            LoadSpritePalette(&sSpritePal_IconBoxFem);
            LoadPalette(sMainBgPaletteFem, 0, 32);
        }
        LoadPalette(sScrollBgPalette, 16, 32);
        sMainMenuDataPtr->gfxLoadState++;
        break;
    default:
        sMainMenuDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void MainMenu_InitWindows(void) // Init Text Windows
{
    InitWindows(sMainMenuWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    
    FillWindowPixelBuffer(WINDOW_HEADER, 0);
    PutWindowTilemap(WINDOW_HEADER);
    CopyWindowToVram(WINDOW_HEADER, 3);
}


/*    Sprite Creation Functions     */

//
//      Mugshot Functions
//
static void CreateMugshot()
{   
    u16 facilityClass = ReturnAvatarTrainerFrontPicId(gSaveBlock2Ptr->playerGfxType);
    if (facilityClass == 0xFFFF)
    {
        sMainMenuDataPtr->mugshotSpriteId = CreateMonPicSprite(VarGet(VAR_AVATAR_POKEMON_CHOICE), 
                    FALSE, 
                    0, 
                    TRUE, 
                    48,
                    56,
                    15, 
                    TAG_NONE);
    }
    else
    {
        sMainMenuDataPtr->mugshotSpriteId = CreateSprite(&sSpriteTemplate_Mugshot, 48, 56, 1);
        gSprites[sMainMenuDataPtr->mugshotSpriteId].invisible = FALSE;
        StartSpriteAnim(&gSprites[sMainMenuDataPtr->mugshotSpriteId], 0);
        gSprites[sMainMenuDataPtr->mugshotSpriteId].oam.priority = 0;
    }
    
    return;
}

static void DestroyMugshot()
{
    u16 facilityClass = ReturnAvatarTrainerFrontPicId(gSaveBlock2Ptr->playerGfxType);
    if (facilityClass == 0xFFFF)
        FreeAndDestroyMonPicSprite(sMainMenuDataPtr->mugshotSpriteId);
    else
        DestroySpriteAndFreeResources(&gSprites[sMainMenuDataPtr->mugshotSpriteId]);
    sMainMenuDataPtr->mugshotSpriteId = SPRITE_NONE;
}


static void HideShowMugshot(u8 visible)
{
    gSprites[sMainMenuDataPtr->mugshotSpriteId].invisible = visible;
}

u16 CreateMugshotExternal()
{
    u16 spriteId = CreateSprite(&sSpriteTemplate_Mugshot, 40, 111, 1);
    gSprites[spriteId].invisible = FALSE;
    StartSpriteAnim(&gSprites[spriteId], 0);
    gSprites[spriteId].oam.priority = 0;
    return spriteId;
}

//
//  Create Mon Icon and Shadow Sprites
//
#define ICON_BOX_1_START_X          136 + 8
#define ICON_BOX_1_START_Y          38
#define ICON_BOX_X_DIFFERENCE       32
#define ICON_BOX_Y_DIFFERENCE       32
static void CreateIconShadow()
{
    u8 i = 0;

    sMainMenuDataPtr->iconBoxSpriteIds[0] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 0), ICON_BOX_1_START_Y, 2);
    sMainMenuDataPtr->iconBoxSpriteIds[1] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 1), ICON_BOX_1_START_Y, 2);
    sMainMenuDataPtr->iconBoxSpriteIds[2] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 2), ICON_BOX_1_START_Y, 2);
    
    sMainMenuDataPtr->iconBoxSpriteIds[3] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 0), ICON_BOX_1_START_Y + (ICON_BOX_Y_DIFFERENCE * 1), 2);
    sMainMenuDataPtr->iconBoxSpriteIds[4] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 1), ICON_BOX_1_START_Y + (ICON_BOX_Y_DIFFERENCE * 1), 2);
    sMainMenuDataPtr->iconBoxSpriteIds[5] = CreateSprite(&sSpriteTemplate_IconBox, ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 2), ICON_BOX_1_START_Y + (ICON_BOX_Y_DIFFERENCE * 1), 2);

    for(i = 0; i < gPlayerPartyCount; i++)
    {
        gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]].invisible = FALSE;
        StartSpriteAnim(&gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]], 0);
        gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]].oam.priority = 1;
    }

    for(i = gPlayerPartyCount; i < 6; i++) // Hide Shadows For Mons that don't exist
    {
        gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]].invisible = TRUE;
    }

    return;
}

static void DestroyIconShadow()
{
    u8 i = 0;
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        DestroySprite(&gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]]);
        sMainMenuDataPtr->iconBoxSpriteIds[i] = SPRITE_NONE;
    }
}

static void HideShowIconShadows(u8 visible)
{
    u8 i = 0;
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        gSprites[sMainMenuDataPtr->iconBoxSpriteIds[i]].invisible = visible;
    }
}


static u32 GetHPEggCyclePercent(u32 partyIndex) // Random HP function from psf's hack written by Rioluwott
{
    struct Pokemon *mon = &gPlayerParty[partyIndex];
    if (!GetMonData(mon, MON_DATA_IS_EGG))
        return ((GetMonData(mon, MON_DATA_HP)) * 100 / (GetMonData(mon,MON_DATA_MAX_HP)));
    else
        return ((GetMonData(mon, MON_DATA_FRIENDSHIP)) * 100 / (gSpeciesInfo[GetMonData(mon,MON_DATA_SPECIES)].eggCycles));
}

static void CreatePartyMonIcons()
{
    u8 i = 0;
    s16 x = ICON_BOX_1_START_X;
    s16 y = ICON_BOX_1_START_Y;
    struct Pokemon *mon;
    LoadMonIconPalettes();
    for(i = 0; i < gPlayerPartyCount; i++)
    {   
        switch (i) // choose position for each icon
        {
            case 0:
                x = ICON_BOX_1_START_X;
                y = ICON_BOX_1_START_Y;
                break;
            case 1:
                x = ICON_BOX_1_START_X + ICON_BOX_X_DIFFERENCE;
                y = ICON_BOX_1_START_Y;
                break;
            case 2:
                x = ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 2);
                y = ICON_BOX_1_START_Y;
                break;
            case 3:
                x = ICON_BOX_1_START_X;
                y = ICON_BOX_1_START_Y + (ICON_BOX_Y_DIFFERENCE * 1);
                break;
            case 4:
                x = ICON_BOX_1_START_X + ICON_BOX_X_DIFFERENCE;
                y = ICON_BOX_1_START_Y + (ICON_BOX_X_DIFFERENCE * 1);
                break;
            case 5:
                x = ICON_BOX_1_START_X + (ICON_BOX_X_DIFFERENCE * 2);
                y = ICON_BOX_1_START_Y + (ICON_BOX_Y_DIFFERENCE * 1);
                break;
        }

#ifdef RHH_EXPANSION
            sMainMenuDataPtr->iconMonSpriteIds[i] = CreateMonIcon(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG), SpriteCB_MonIcon, x, y - 2, 0, GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY));
#else
            sMainMenuDataPtr->iconMonSpriteIds[i] = CreateMonIcon(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG), SpriteCB_MonIcon, x, y - 2, 0, GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY), TRUE);
#endif

        gSprites[sMainMenuDataPtr->iconMonSpriteIds[i]].oam.priority = 0;

        if (GetHPEggCyclePercent(i) == 0)
        {
            gSprites[sMainMenuDataPtr->iconMonSpriteIds[i]].callback = SpriteCallbackDummy;
        }

    }
}

static void DestroyMonIcons()
{
    u8 i = 0;
    for(i = 0; i < 6; i++)
    {
        DestroySprite(&gSprites[sMainMenuDataPtr->iconMonSpriteIds[i]]);
        sMainMenuDataPtr->iconMonSpriteIds[i] = SPRITE_NONE;
    }
}


static void HideShowIcons(u8 visible)
{
    u8 i = 0;
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        gSprites[sMainMenuDataPtr->iconMonSpriteIds[i]].invisible = visible;
    }
}



//
//  Print The Text For Dex Num, Badges, Name, Playtime, Location
//
static const u8 sText_DexNum[] = _("Dex {STR_VAR_1}");
static const u8 sText_Badges[] = _("Badges {STR_VAR_1}");
static void PrintToWindow(u8 windowId, u8 colorIdx)
{
    const u8 colors[3] = {0,  2,  3}; 
    u8 mapDisplayHeader[24];
    u8 *withoutPrefixPtr, *playTimePtr;
    u16 dexCount = 0; u8 badgeCount = 0;
    u32 i = 0;

    FillWindowPixelBuffer(WINDOW_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    // Print Map Name In Header
    withoutPrefixPtr = &(mapDisplayHeader[3]);
    GetMapName(withoutPrefixPtr, GetCurrentRegionMapSectionId(), 0);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    BufferMapFloorString();
    StringCopy(gStringVar2, mapDisplayHeader);
    StringExpandPlaceholders(mapDisplayHeader, gStringVar2);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NARROW, GetStringCenterAlignXOffset(FONT_NARROW, withoutPrefixPtr, 10 * 8) + (8 * 10), 1 + (8), 0, 0, colors, 0xFF, mapDisplayHeader);

    // Print Playtime In Header
    playTimePtr = ConvertIntToDecimalStringN(gStringVar4, gSaveBlock2Ptr->playTimeHours, STR_CONV_MODE_LEFT_ALIGN, 3);
    *playTimePtr = 0xF0;
    ConvertIntToDecimalStringN(playTimePtr + 1, gSaveBlock2Ptr->playTimeMinutes, STR_CONV_MODE_LEADING_ZEROS, 2);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, (104 - 12) + GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, (6*8)) + (8 * 10), 1 + (8), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);

    // Print Dex Numbers if You Have It
    if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
    {
        if (IsNationalPokedexEnabled())
            dexCount = GetNationalPokedexCount(FLAG_GET_CAUGHT);
        else
            dexCount = GetHoennPokedexCount(FLAG_GET_CAUGHT);
        ConvertIntToDecimalStringN(gStringVar1, dexCount, STR_CONV_MODE_RIGHT_ALIGN, 4);
        StringExpandPlaceholders(gStringVar4, sText_DexNum);
        AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, 8 + 8 + (8 * 8), 16 + 2 + (8 * 3), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);
    }

    // Print Badge Numbers if You Have Them
    for (i = FLAG_BADGE01_GET; i < FLAG_BADGE01_GET + NUM_BADGES; i++)
    {
        if (FlagGet(i))
            badgeCount++;
    } 
    ConvertIntToDecimalStringN(gStringVar1, badgeCount, STR_CONV_MODE_LEADING_ZEROS, 1);
    StringExpandPlaceholders(gStringVar4, sText_Badges);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, 16 + (8 * 8), 32 + 2 + (8 * 3), 0, 0, colors, TEXT_SKIP_DRAW, gStringVar4);

    // Print Player Name
    AddTextPrinterParameterized3(WINDOW_HEADER, FONT_NORMAL, 16 + (8 * 8), 2 + (8 * 3), colors, TEXT_SKIP_DRAW, gSaveBlock2Ptr->playerName);

    PutWindowTilemap(WINDOW_HEADER);
    CopyWindowToVram(WINDOW_HEADER, 3);
}


//
//  Print The Text For Dex Num, Badges, Name, Playtime, Location
//
static const u8 sText_NewGame_Button_Custom[] = _("Custom");
static const u8 sText_NewGame_Button_Normal[] = _("Normal");
static const u8 sText_NewGame_Button_Hard[] = _("Hard");

static const u8 sText_NewGame_Text_Custom[] = _(" Custom Mode lets you choose your own \n ruleset to play with.");
static const u8 sText_NewGame_Text_Normal[] = _(" Normal Mode is not too difficult, \n a fun way to play through The Pit.");
static const u8 sText_NewGame_Text_Hard[] = _(" Hard Mode is a bit of a challenge, \n less Exp and harder trainers await you.");

static void PrintNewGameToWindow(u8 windowId, u8 colorIdx)
{
    const u8 colors[3] = {0,  5,  3}; 
    const u8 colors2[3] = {0,  6,  7}; 
    u32 i = 0;

    FillWindowPixelBuffer(WINDOW_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, GetStringCenterAlignXOffset(FONT_NORMAL, sText_NewGame_Button_Custom, 14 * 8) + 64, 18, 0, 0, colors, 0xFF, sText_NewGame_Button_Custom);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, GetStringCenterAlignXOffset(FONT_NORMAL, sText_NewGame_Button_Normal, 14 * 8) + 64, 50, 0, 0, colors, 0xFF, sText_NewGame_Button_Normal);
    AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, GetStringCenterAlignXOffset(FONT_NORMAL, sText_NewGame_Button_Hard, 14 * 8) + 64, 82, 0, 0, colors, 0xFF, sText_NewGame_Button_Hard);

    if (sNewGameSelectedOption == 0)
        AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, 16, 120, 0, 0, colors2, 0xFF, sText_NewGame_Text_Custom);
    else if(sNewGameSelectedOption == 1)
        AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, 16, 120, 0, 0, colors2, 0xFF, sText_NewGame_Text_Normal);
    else
        AddTextPrinterParameterized4(WINDOW_HEADER, FONT_NORMAL, 16, 120, 0, 0, colors2, 0xFF, sText_NewGame_Text_Hard);

    PutWindowTilemap(WINDOW_HEADER);
    CopyWindowToVram(WINDOW_HEADER, 3);
}


static void Task_ReloadMainMenu(u8 taskId)
{
    switch (gMain.state)
    {
    case 0:
        HideBg(0);
        HideBg(1);
        HideBg(3);
        sNewGameSelectedOption = 0xFF;
        SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(HWinCoords[sSelectedOption].winh.left, HWinCoords[sSelectedOption].winh.right));  // Set Window 0 width/height Which defines the not darkened space
        SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(HWinCoords[sSelectedOption].winv.left, HWinCoords[sSelectedOption].winv.right));
        switch(menuType)
        {
            case HAS_SAVED_GAME:    // The three Window 1 states either block out the mystery buttons both, just the mystery event, or nothing. 
                SetGpuReg(REG_OFFSET_WIN1H,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_BOTH].winh.left, HWinCoords[HW_WIN_MYSTERY_BOTH].winh.right));
                SetGpuReg(REG_OFFSET_WIN1V,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_BOTH].winv.left, HWinCoords[HW_WIN_MYSTERY_BOTH].winv.right));
                break;   
            case HAS_MYSTERY_GIFT:
                SetGpuReg(REG_OFFSET_WIN1H,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_EVENT].winh.left, HWinCoords[HW_WIN_MYSTERY_EVENT].winh.right));
                SetGpuReg(REG_OFFSET_WIN1V,  WIN_RANGE(HWinCoords[HW_WIN_MYSTERY_EVENT].winv.left, HWinCoords[HW_WIN_MYSTERY_EVENT].winv.right));
                break;
        }
        memset(sBg1TilemapBuffer, 0, 0x800);
        gMain.state++;
        break;
    case 1:
        if (MainMenu_LoadGraphics(TRUE) == TRUE)
        {
            ScheduleBgCopyTilemapToVram(1);
            gMain.state++;
        }
        break;
    case 2:
        HideShowMugshot(FALSE);
        HideShowIconShadows(FALSE);
        HideShowIcons(FALSE);
        PrintToWindow(WINDOW_HEADER, FONT_WHITE);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gMain.state++;
        break;
    default:
        gTasks[taskId].func = Task_MainMenuMain;
        gMain.state = 0;
        return;
    }
    return;
    
}


static void Task_MainNewGameMenu(u8 taskId)
{
    if (JOY_NEW(A_BUTTON)) // If Pressed A go to thing you pressed A on
    {   
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_MainMenuTurnOff;
        sSelectedOption = HW_WIN_CONTINUE;
    }
    if (JOY_NEW(START_BUTTON))
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        LoadCustomModePresets();
        sMainMenuDataPtr->savedCallback = CB2_NewGameBirchSpeech_FromNewMainMenu;
        sNewGameSelectedOption = 0xFF;
        gTasks[taskId].func = Task_MainMenuTurnOff;
        sSelectedOption = HW_WIN_CONTINUE;
    }
    if (JOY_NEW(B_BUTTON) && (sAlreadySelectedAvatar == 0)) // If Pressed A go to thing you pressed A on
    {
        gMain.state = 0;
        gTasks[taskId].func = Task_ReloadMainMenu;
        return;
    }
    if (JOY_NEW(DPAD_UP))
    {
        if (sNewGameSelectedOption == 0)
            sNewGameSelectedOption = 2;
        else
            sNewGameSelectedOption--;
        MoveNewGameHWindowsWithInput();
        PrintNewGameToWindow(WINDOW_HEADER, FONT_WHITE);
    }
    if (JOY_NEW(DPAD_DOWN))
    {
        if (sNewGameSelectedOption == 2)
            sNewGameSelectedOption = 0;
        else
            sNewGameSelectedOption++;
        MoveNewGameHWindowsWithInput();
        PrintNewGameToWindow(WINDOW_HEADER, FONT_WHITE);
    }
}

static void Task_LoadNewGameMenu(u8 taskId)
{
    switch (gMain.state)
    {
    case 0:
        HideBg(1);
        HideBg(0);
        HideShowMugshot(TRUE);
        HideShowIconShadows(TRUE);
        HideShowIcons(TRUE);
        memset(sBg1TilemapBuffer, 0, 0x800);
        sNewGameSelectedOption = 0;
        gMain.state++;
        break;
    case 1:
        SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(HWinNewGameCoords[0].winh.left, HWinNewGameCoords[0].winh.right));  // Set Window 0 width/height Which defines the not darkened space
        SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(HWinNewGameCoords[0].winv.left, HWinNewGameCoords[0].winv.right));
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        if (NewGame_LoadGraphics(TRUE) == TRUE)
        {
            gMain.state++;
        }
        break;
    case 2:
        PrintNewGameToWindow(WINDOW_HEADER, FONT_WHITE);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        gMain.state++;
        break;
    default:
        gTasks[taskId].func = Task_MainNewGameMenu;
        gMain.state = 0;
        return;
    }
    return;
    
}

//
//  Main Input Control Task
//
static void Task_MainMenuMain(u8 taskId)
{
    if (JOY_NEW(A_BUTTON)) // If Pressed A go to thing you pressed A on
    {
        PlaySE(SE_SELECT);
        
        switch(sSelectedOption)
        {
            case HW_WIN_CONTINUE:
                sMainMenuDataPtr->savedCallback = CB2_ContinueSavedGame;
                sSelectedOption = HW_WIN_CONTINUE;
                break;
            case HW_WIN_NEW_GAME:
                gTasks[taskId].func = Task_LoadNewGameMenu;
                gMain.state = 0;
                return;
            case HW_WIN_OPTIONS:
                gMain.savedCallback = CB2_ReinitMainMenu;
                sMainMenuDataPtr->savedCallback = CB2_InitOptionMenu;
                break;
            case HW_WIN_MYSTERY_EVENT:
                sMainMenuDataPtr->savedCallback = CB2_InitMysteryEventMenu;
                sSelectedOption = HW_WIN_CONTINUE;
                break;
            case HW_WIN_MYSTERY_GIFT:
                if((menuType == HAS_MYSTERY_EVENTS) && !(IsWirelessAdapterConnected()))
                    //sMainMenuDataPtr->savedCallback = CB2_InitEReader;
                    sMainMenuDataPtr->savedCallback = CB2_InitMysteryGift; // E-Reader Crashes IDK Why Exactly But You Can Uncomment It
                else
                    sMainMenuDataPtr->savedCallback = CB2_InitMysteryGift;
                sSelectedOption = HW_WIN_CONTINUE;
                break;
        }
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_MainMenuTurnOff;
    }

    if (JOY_NEW(B_BUTTON)) // If B Pressed Go To Title Screen
    {

    }

    if(JOY_NEW(DPAD_DOWN)) // Handle DPad directions, kinda bad way to do it with each case handled individually but its whatever
    {
        switch (menuType)
        {
            case HAS_SAVED_GAME:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_NEW_GAME;
                else if((sSelectedOption == HW_WIN_NEW_GAME) || (sSelectedOption == HW_WIN_OPTIONS))
                    sSelectedOption = HW_WIN_CONTINUE;
                break;
            case HAS_MYSTERY_GIFT:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_NEW_GAME;
                else if((sSelectedOption == HW_WIN_NEW_GAME) || (sSelectedOption == HW_WIN_OPTIONS))
                    sSelectedOption = HW_WIN_MYSTERY_GIFT;
                else
                    sSelectedOption = HW_WIN_CONTINUE;
                break;
            case HAS_MYSTERY_EVENTS:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_NEW_GAME;
                else if(sSelectedOption == HW_WIN_NEW_GAME)
                    sSelectedOption = HW_WIN_MYSTERY_GIFT;
                else if(sSelectedOption == HW_WIN_OPTIONS)
                    sSelectedOption = HW_WIN_MYSTERY_EVENT;
                else
                    sSelectedOption = HW_WIN_CONTINUE;
                break;
        }
        MoveHWindowsWithInput();
    }

    if(JOY_NEW(DPAD_UP))
    {
        switch (menuType)
        {
            case HAS_SAVED_GAME:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_NEW_GAME;
                else if((sSelectedOption == HW_WIN_NEW_GAME) || (sSelectedOption == HW_WIN_OPTIONS))
                    sSelectedOption = HW_WIN_CONTINUE;
                break;
            case HAS_MYSTERY_GIFT:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_MYSTERY_GIFT;
                else if((sSelectedOption == HW_WIN_NEW_GAME) || (sSelectedOption == HW_WIN_OPTIONS))
                    sSelectedOption = HW_WIN_CONTINUE;
                else
                    sSelectedOption = HW_WIN_NEW_GAME;
                break;
            case HAS_MYSTERY_EVENTS:
                if(sSelectedOption == HW_WIN_CONTINUE)
                    sSelectedOption = HW_WIN_MYSTERY_GIFT;
                else if(sSelectedOption == HW_WIN_NEW_GAME)
                    sSelectedOption = HW_WIN_CONTINUE;
                else if(sSelectedOption == HW_WIN_OPTIONS)
                    sSelectedOption = HW_WIN_CONTINUE;
                else if(sSelectedOption == HW_WIN_MYSTERY_GIFT)
                    sSelectedOption = HW_WIN_NEW_GAME;
                else if(sSelectedOption == HW_WIN_MYSTERY_EVENT)
                    sSelectedOption = HW_WIN_OPTIONS;
                break;
        }
        MoveHWindowsWithInput();
    }

    if(JOY_NEW(DPAD_LEFT) || JOY_NEW(DPAD_RIGHT))
    {
        switch (menuType)
        {
            case HAS_SAVED_GAME:
                if(sSelectedOption == HW_WIN_NEW_GAME)
                    sSelectedOption = HW_WIN_OPTIONS;
                else if(sSelectedOption == HW_WIN_OPTIONS)
                    sSelectedOption = HW_WIN_NEW_GAME;
                break;
            case HAS_MYSTERY_GIFT:
                if(sSelectedOption == HW_WIN_NEW_GAME)
                    sSelectedOption = HW_WIN_OPTIONS;
                else if(sSelectedOption == HW_WIN_OPTIONS)
                    sSelectedOption = HW_WIN_NEW_GAME;
                break;
            case HAS_MYSTERY_EVENTS:
                if(sSelectedOption == HW_WIN_NEW_GAME)
                    sSelectedOption = HW_WIN_OPTIONS;
                else if(sSelectedOption == HW_WIN_OPTIONS)
                    sSelectedOption = HW_WIN_NEW_GAME;

                else if(sSelectedOption == HW_WIN_MYSTERY_GIFT)
                    sSelectedOption = HW_WIN_MYSTERY_EVENT;
                else if(sSelectedOption == HW_WIN_MYSTERY_EVENT)
                    sSelectedOption = HW_WIN_MYSTERY_GIFT;
                break;
        }
        MoveHWindowsWithInput();
    }
}
