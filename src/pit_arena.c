#include "global.h"
#include "script.h"
#include "pit.h"
#include "event_data.h"
#include "mystery_gift.h"
#include "util.h"
#include "constants/event_objects.h"
#include "constants/map_scripts.h"
#include "main_menu.h"
#include "main.h"
#include "random.h"
#include "battle_setup.h"
#include "string_util.h"
#include "strings.h"
#include "pokemon_storage_system.h"
#include "ui_birch_case.h"
#include "task.h"
#include "field_weather.h"
#include "new_game.h"
#include "ui_mode_menu.h"
#include "start_menu.h"
#include "constants/metatile_labels.h"
#include "fieldmap.h"
#include "field_screen_effect.h"
#include "overworld.h"
#include "event_scripts.h"
#include "sound.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "data.h"
#include "constants/battle.h"
#include "event_object_movement.h"
#include "script_pokemon_util.h"
#include "palette.h"
#include "decompress.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "gpu_regs.h"
#include "constants/weather.h"
#include "global.fieldmap.h"
#include "tilesets.h"
#include "constants/decorations.h"
#include "decoration_inventory.h"
#include "decoration.h"
#include "pokedex.h"
#include "pokedex_plus_hgss.h"
#include "field_player_avatar.h"
#include "naming_screen.h"
#include "config/general.h"

//
// 	Random Trainer Floor Generation Code
//

//general structs for the object events
const struct RandomTrainerNPC RandomNPCTrainers[MAX_RANDOM_TRAINERS] = 
{
    [0] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_0, VAR_OBJ_GFX_ID_0, FLAG_TRAINER_0, TRAINER_RANDOM_BATTLE_0, VAR_TRAINER_0_DEFEAT_TEXT},
    [1] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_1, VAR_OBJ_GFX_ID_1, FLAG_TRAINER_1, TRAINER_RANDOM_BATTLE_1, VAR_TRAINER_1_DEFEAT_TEXT},
    [2] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_2, VAR_OBJ_GFX_ID_2, FLAG_TRAINER_2, TRAINER_RANDOM_BATTLE_2, VAR_TRAINER_2_DEFEAT_TEXT},
    [3] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_3, VAR_OBJ_GFX_ID_3, FLAG_TRAINER_3, TRAINER_RANDOM_BATTLE_3, VAR_TRAINER_3_DEFEAT_TEXT},
};

const struct RandomTrainerNPC RandomNPCTrainers_Doubles[MAX_RANDOM_TRAINERS] = 
{
    [0] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_0, VAR_OBJ_GFX_ID_0, FLAG_TRAINER_4, TRAINER_RANDOM_BATTLE_4, VAR_TRAINER_4_DEFEAT_TEXT},
    [1] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_1, VAR_OBJ_GFX_ID_1, FLAG_TRAINER_5, TRAINER_RANDOM_BATTLE_5, VAR_TRAINER_5_DEFEAT_TEXT},
    [2] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_2, VAR_OBJ_GFX_ID_2, FLAG_TRAINER_6, TRAINER_RANDOM_BATTLE_6, VAR_TRAINER_6_DEFEAT_TEXT},
    [3] = {VAR_PIT_TRAINER_ARRAY_ELEMENT_3, VAR_OBJ_GFX_ID_3, FLAG_TRAINER_7, TRAINER_RANDOM_BATTLE_7, VAR_TRAINER_7_DEFEAT_TEXT},
};

//specific structs for the trainers
#define MALE    0
#define FEMALE  1

struct RandomTrainerClasses {
    u16 graphicsId;
    u16 trainerPic;
    u16 trainerClass;
    u8 gender;
};

#define RANDOM_TRAINER_ENCOUNTER_COUNT ARRAY_COUNT(sRandomTrainerEncounterArray)
static const struct RandomTrainerClasses sRandomTrainerEncounterArray[] = {
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_2,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GIRL_3,
        .trainerPic = TRAINER_PIC_BATTLE_GIRL,
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BEAUTY,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_5,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BLACK_BELT,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BUG_CATCHER,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MANIAC,
        .trainerPic = TRAINER_PIC_BUG_MANIAC,
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_CAMPER,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerClass = TRAINER_CLASS_CAMPER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MANIAC,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_5,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_3,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_3,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_EXPERT_F,
        .trainerPic = TRAINER_PIC_EXPERT_F,
        .trainerClass = TRAINER_CLASS_EXPERT,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_EXPERT_M,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerClass = TRAINER_CLASS_EXPERT,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_FISHERMAN,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GENTLEMAN,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_5,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerClass = TRAINER_CLASS_GUITARIST,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_HEX_MANIAC,
        .trainerPic = TRAINER_PIC_HEX_MANIAC,
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerClass = TRAINER_CLASS_HIKER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_5,
        .trainerPic = TRAINER_PIC_KINDLER,
        .trainerClass = TRAINER_CLASS_KINDLER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_2,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerClass = TRAINER_CLASS_LADY,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_LASS,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerClass = TRAINER_CLASS_LASS,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_NINJA_BOY,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_5,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_PICNICKER,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_2,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_F,
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_4,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_M,
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_PICNICKER,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_CAMPER,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_POKEFAN_F,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerClass = TRAINER_CLASS_POKEFAN,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_POKEFAN_M,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerClass = TRAINER_CLASS_POKEFAN,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MANIAC,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_LASS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_PSYCHIC_M,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_RICH_BOY,
        .trainerPic = TRAINER_PIC_RICH_BOY,
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SAILOR,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerClass = TRAINER_CLASS_SAILOR,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GIRL_3,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_F,
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SCHOOL_KID_M,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_M,
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SWIMMER_F,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SWIMMER_M,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_CYCLING_TRIATHLETE_F,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_F,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_CYCLING_TRIATHLETE_M,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_M,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_M,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SWIMMER_F,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_F,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SWIMMER_M,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_M,
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_TUBER_F,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerClass = TRAINER_CLASS_TUBER_F,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_TUBER_M,
        .trainerPic = TRAINER_PIC_TUBER_M,
        .trainerClass = TRAINER_CLASS_TUBER_M,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_YOUNGSTER,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_AQUA_MEMBER_F,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_F,
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_AQUA_MEMBER_M,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_M,
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_F,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_F,
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_M,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_M,
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GRETA,
        .trainerPic = TRAINER_PIC_ARENA_TYCOON_GRETA,
        .trainerClass = TRAINER_CLASS_ARENA_TYCOON,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_ANABEL,
        .trainerPic = TRAINER_PIC_SALON_MAIDEN_ANABEL,
        .trainerClass = TRAINER_CLASS_SALON_MAIDEN,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BRANDON,
        .trainerPic = TRAINER_PIC_PYRAMID_KING_BRANDON,
        .trainerClass = TRAINER_CLASS_PYRAMID_KING,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_LUCY,
        .trainerPic = TRAINER_PIC_PIKE_QUEEN_LUCY,
        .trainerClass = TRAINER_CLASS_PIKE_QUEEN,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_NOLAND,
        .trainerPic = TRAINER_PIC_FACTORY_HEAD_NOLAND,
        .trainerClass = TRAINER_CLASS_FACTORY_HEAD,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SPENSER,
        .trainerPic = TRAINER_PIC_PALACE_MAVEN_SPENSER,
        .trainerClass = TRAINER_CLASS_PALACE_MAVEN,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_TUCKER,
        .trainerPic = TRAINER_PIC_DOME_ACE_TUCKER,
        .trainerClass = TRAINER_CLASS_DOME_ACE,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BIKER,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerClass = TRAINER_CLASS_BIKER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MANIAC,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_CHANNELER,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GIRL_3,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BIKER,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_1,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerClass = TRAINER_CLASS_ENGINEER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_EXPERT_M,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerClass = TRAINER_CLASS_GAMER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_5,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_GIRL_2,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerClass = TRAINER_CLASS_PAINTER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_ROCKER,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerClass = TRAINER_CLASS_ROCKER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_ROCKET_MEMBER_F,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_ROCKET_MEMBER_M,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SCIENTIST,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_SUPER_NERD,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BOY_2,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerClass = TRAINER_CLASS_TAMER,
        .gender = MALE,
    },
};

#define TRAINER_NAME_COUNT_M ARRAY_COUNT(gRandomTrainerNamesM)
static const u8 gRandomTrainerNamesM[][10] =
{
    _("Sawyer"), 
    _("Marcel"), 
    _("Alberto"), 
    _("Ed"), 
    _("Declan"), 
    _("Frederick"), 
    _("Matt"), 
    _("Zander"), 
    _("Felix"), 
    _("Dusty"), 
    _("Chip"), 
    _("Foster"), 
    _("Jake"), 
    _("John"), 
    _("Steve"), 
    _("Paul"), 
    _("Smith"), 
    _("Blake"), 
    _("Ben"), 
    _("Shane"), 
    _("Hagan"), 
    _("Hayden"), 
    _("Ian"), 
    _("Nick"), 
    _("Matti"), 
    _("Kai"), 
    _("Nolan"), 
    _("Owen"), 
    _("Eli"), 
    _("Finn"), 
    _("Jace"), 
    _("Carter"), 
    _("Cole"), 
    _("Drew"), 
    _("Landon"), 
    _("Ryder"), 
    _("Miles"), 
    _("Logan"), 
    _("Luke"), 
    _("Max"), 
    _("Jay"), 
    _("Zane"), 
    _("Noah"), 
    _("Wyatt"), 
    _("Tate"), 
    _("Ryan"), 
    _("Levi"), 
    _("Jack"), 
    _("Ethan"), 
    _("Cyrus"), 
    _("Aaron"), 
    _("Jared"), 
    _("Bryce"), 
    _("Grant"), 
    _("Reese"), 
    _("Toby"), 
    _("Clark"), 
    _("Derek"), 
    _("Trent"), 
    _("Seth"), 
    _("Vince"), 
    _("Troy"), 
    _("Shawn"), 
    _("Craig"), 
    _("Damon"), 
    _("Peter"), 
    _("Brody"), 
    _("Chase"), 
    _("Cody"), 
    _("Dylan"), 
    _("Gavin"), 
    _("Jaxon"), 
    _("Kaleb"), 
    _("Kaden"), 
    _("Mason"), 
    _("Parker"), 
    _("Quinn"), 
    _("Riley"), 
    _("Simon"), 
    _("Tanner"), 
    _("Wesley"), 
    _("Xander"), 
    _("Harvey"), 
    _("Jason"), 
    _("Justin"), 
    _("Tucker"), 
    _("Victor"), 
    _("Warren"), 
    _("Connor"), 
    _("Grady"), 
    _("Isaac"), 
    _("Jonah"), 
    _("Kevin"), 
    _("Lukas"), 
    _("Marcus"), 
    _("Nathan"), 
    _("Oscar"), 
    _("Philip"), 
    _("Spence"), 
    _("Tyler"), 
};

#define TRAINER_NAME_COUNT_F ARRAY_COUNT(gRandomTrainerNamesF)
static const u8 gRandomTrainerNamesF[][10] =
{
    _("Rose"), 
    _("Gabby"), 
    _("Brittney"), 
    _("Gwen"), 
    _("Mary"), 
    _("Wendy"), 
    _("Keira"), 
    _("Jennifer"), 
    _("Hope"), 
    _("Shannon"), 
    _("Caroline"), 
    _("Julie"), 
    _("Shay"), 
    _("Jess"), 
    _("Katy"), 
    _("Catherine"), 
    _("Sandy"), 
    _("Hannah"), 
    _("Emily"), 
    _("Sadie"), 
    _("Sabrina"), 
    _("Sherry"), 
    _("Carrie"), 
    _("Rachel"), 
    _("Mia"), 
    _("Zoe"), 
    _("Luna"), 
    _("Lila"), 
    _("Piper"), 
    _("Ella"), 
    _("Ruby"), 
    _("Chloe"), 
    _("Aria"), 
    _("Grace"), 
    _("Ava"), 
    _("Lily"), 
    _("Lucy"), 
    _("Stella"), 
    _("Hazel"), 
    _("Sadie"), 
    _("Willow"), 
    _("Jade"), 
    _("Ellie"), 
    _("Violet"), 
    _("Ivy"), 
    _("Faith"), 
    _("Clara"), 
    _("Anna"), 
    _("Lola"), 
    _("Iris"), 
    _("Bella"), 
    _("Daisy"), 
    _("Amber"), 
    _("Leah"), 
    _("Nina"), 
    _("Paige"), 
    _("Naomi"), 
    _("Brooke"), 
    _("Tessa"), 
    _("Eve"), 
    _("Molly"), 
    _("Elsie"), 
    _("Fiona"), 
    _("Laura"), 
    _("Holly"), 
    _("April"), 
    _("Dana"), 
    _("Erica"), 
    _("Tina"), 
    _("Megan"), 
    _("Kayla"), 
    _("Alexa"), 
    _("Jamie"), 
    _("Sofia"), 
    _("Olive"), 
    _("Harper"), 
    _("Diana"), 
    _("Ellen"), 
    _("Maren"), 
    _("Lyric"), 
    _("Serena"), 
    _("Penny"), 
    _("Lilah"), 
    _("Reese"), 
    _("Adele"), 
    _("Nora"), 
    _("Cindy"), 
    _("Brenda"), 
    _("Eliza"), 
    _("Amara"), 
    _("Hailey"), 
    _("Audrey"), 
    _("Taylor"), 
    _("Sienna"), 
    _("Delia"), 
    _("Skye"), 
    _("Shelby"), 
    _("Morgan"), 
    _("Cassie"), 
    _("Vivian"), 
    _("Kelsey"), 
};


//functions
u16 GetLastSpokenVarObjTrainerArrayElement(void)
{
    if(gSpecialVar_LastTalked > 4) // > 4 = Doubles
        return VarGet(RandomNPCTrainers_Doubles[gSpecialVar_LastTalked - 5].arrayElement);
    else
        return VarGet(RandomNPCTrainers[gSpecialVar_LastTalked - 1].arrayElement);
}

u16 ReturnLastSpokenVarObjGfxId()
{   
    if(gSpecialVar_LastTalked > 4) // > 4 = Doubles
        return VarGet(RandomNPCTrainers_Doubles[gSpecialVar_LastTalked - 5].gfxid);
    else
        return VarGet(RandomNPCTrainers[gSpecialVar_LastTalked - 1].gfxid);
}

u16 ReturnNumberOfTrainersForFloor()
{
    if(VarGet(VAR_LAST_FLOOR_TRAINER_NUMBER) == 4)
        return 1;

    if(VarGet(VAR_PIT_FLOOR) < 5)
        return 1;

    u16 randomValue = Random() % 100;
    if(VarGet(VAR_PIT_FLOOR) < 25) // first 25 floor rates
    {
        if(randomValue < 65)
            return 1;
        if(randomValue < 95)
            return 2;
        if(randomValue < 99)
            return 3;
        if(randomValue < 100)
            return 4;
        return 0;
    }
    else if(VarGet(VAR_PIT_FLOOR) < 50) // second 25 floor rates
    {
        if(randomValue < 45)
            return 1;
        if(randomValue < 75)
            return 2;
        if(randomValue < 95)
            return 3;
        if(randomValue < 100)
            return 4;
        return 0;
    }
    else if(VarGet(VAR_PIT_FLOOR) < 75)  // third 25 floor rates
    {
        if(randomValue < 30)
            return 1;
        if(randomValue < 65)
            return 2;
        if(randomValue < 90)
            return 3;
        if(randomValue < 100)
            return 4;
        return 0;
    }
    else  // last 25 floor rates and post level 100 rates
    {
        if(randomValue < 20)
            return 1;
        if(randomValue < 50)
            return 2;
        if(randomValue < 80)
            return 3;
        if(randomValue < 100)
            return 4;
        return 0;
    }   
    return 0;
}

void SetRandomTrainersMixedDoubles(void);
void SetRandomTrainers(void)
{
    u16 iterator = 0;
    u16 trainerCount = 0;
    u16 trainers[MAX_RANDOM_TRAINERS] = {0, 0, 0, 0};
    u16 gfxId, randomTrainerId, k;
    u8 rerollTrainerId = FALSE;

    //DebugPrintf("random trainers Count: %d", RANDOM_TRAINER_ENCOUNTER_COUNT);

    if(gSaveBlock2Ptr->modeBattleMode == MODE_MIXED)
    {
        SetRandomTrainersMixedDoubles();
        return;
    }

    trainerCount = ReturnNumberOfTrainersForFloor();

    VarSet(VAR_LAST_FLOOR_TRAINER_NUMBER, trainerCount);

    // Handle Random Trainers That Are Spawned
    for (iterator = 0; iterator < trainerCount; iterator++)
    {
        u16 newTrainer = Random() % MAX_RANDOM_TRAINERS;
        while(trainers[newTrainer]) //reroll to guarantee randomized trainer positions in the maps
        {
            newTrainer = Random() % MAX_RANDOM_TRAINERS;
        }
        trainers[newTrainer] = TRUE;

        //set trainer data for scripts handling
        do //reroll so there are no object events duplicates on field
        {
            rerollTrainerId = FALSE;
            randomTrainerId = Random() % RANDOM_TRAINER_ENCOUNTER_COUNT;
            gfxId = sRandomTrainerEncounterArray[randomTrainerId].graphicsId;
            for (k = 0; k < MAX_RANDOM_TRAINERS; k++)
            {
                if (gfxId == VarGet(RandomNPCTrainers_Doubles[newTrainer].gfxid) ||
                  gfxId == VarGet(RandomNPCTrainers[newTrainer].gfxid))
                    rerollTrainerId = TRUE;
            }
        } while (rerollTrainerId);  
        //DebugPrintf("randomTrainerId = %d, graphicsId = %d", randomTrainerId, gfxId);
        if(FlagGet(FLAG_DOUBLES_MODE))
        {
            VarSet(RandomNPCTrainers_Doubles[newTrainer].arrayElement, randomTrainerId);
            VarSet(RandomNPCTrainers_Doubles[newTrainer].gfxid, gfxId);
            VarSet(RandomNPCTrainers_Doubles[newTrainer].defeatTextVar, Random() % getNumberOfDefeatTexts());
            ClearTrainerFlag(RandomNPCTrainers_Doubles[newTrainer].trainerflag);
            FlagClear(RandomNPCTrainers_Doubles[newTrainer].objectflag);
        }
        else
        {
            VarSet(RandomNPCTrainers[newTrainer].arrayElement, randomTrainerId);
            VarSet(RandomNPCTrainers[newTrainer].gfxid, gfxId);
            VarSet(RandomNPCTrainers[newTrainer].defeatTextVar, Random() % getNumberOfDefeatTexts());
            ClearTrainerFlag(RandomNPCTrainers[newTrainer].trainerflag);
            FlagClear(RandomNPCTrainers[newTrainer].objectflag);
        }      
    }

    //handle random trainer objects that aren't spawned
    for (iterator = 0; iterator < MAX_RANDOM_TRAINERS; iterator++)
    {
        //valid trainer objects that were not activated
        if (!trainers[iterator])
        {
            if(FlagGet(FLAG_DOUBLES_MODE))
            {
                FlagSet(RandomNPCTrainers_Doubles[iterator].objectflag);
                SetTrainerFlag(RandomNPCTrainers_Doubles[iterator].trainerflag);
            }
            else
            {
                FlagSet(RandomNPCTrainers[iterator].objectflag);
                SetTrainerFlag(RandomNPCTrainers[iterator].trainerflag);
            }
        }
        //invalid trainer objects
        if(FlagGet(FLAG_DOUBLES_MODE))
        {
            FlagSet(RandomNPCTrainers[iterator].objectflag);
            SetTrainerFlag(RandomNPCTrainers[iterator].trainerflag);
        }
        else
        {
            FlagSet(RandomNPCTrainers_Doubles[iterator].objectflag);
            SetTrainerFlag(RandomNPCTrainers_Doubles[iterator].trainerflag);
        }
    }
}

void SetRandomTrainersMixedDoubles(void)
{
    u16 iterator = 0;
    u16 trainerCount = ReturnNumberOfTrainersForFloor();
    u16 trainers[MAX_RANDOM_TRAINERS] = {0, 0, 0, 0};
    u16 gfxId, randomTrainerId, k;
    u8 rerollTrainerId = FALSE;

    VarSet(VAR_LAST_FLOOR_TRAINER_NUMBER, trainerCount);

    // init all trainer objects with set flags
    for (iterator = 0; iterator < MAX_RANDOM_TRAINERS; iterator++)
    {
        FlagSet(RandomNPCTrainers_Doubles[iterator].objectflag);
        SetTrainerFlag(RandomNPCTrainers_Doubles[iterator].trainerflag);

        FlagSet(RandomNPCTrainers[iterator].objectflag);
        SetTrainerFlag(RandomNPCTrainers[iterator].trainerflag);

    }

    // Handle Random Trainers That Are Spawned
    for (iterator = 0; iterator < trainerCount; iterator++)
    {
        u16 newTrainer = Random() % MAX_RANDOM_TRAINERS;
        u8 reroll = FALSE;

        while (trainers[newTrainer] || reroll)
        {
            newTrainer = (Random() % MAX_RANDOM_TRAINERS);

            if(trainers[newTrainer] == TRUE)
            {
                reroll = TRUE;
            }
            else
            {
                reroll = FALSE;
            }
        }

        trainers[newTrainer] = TRUE;

        do //reroll so there are no object events duplicates on field
        {
            rerollTrainerId = FALSE;
            randomTrainerId = Random() % RANDOM_TRAINER_ENCOUNTER_COUNT;
            gfxId = sRandomTrainerEncounterArray[randomTrainerId].graphicsId;
            for (k = 0; k < MAX_RANDOM_TRAINERS; k++)
            {
                if (gfxId == VarGet(RandomNPCTrainers_Doubles[newTrainer].gfxid) ||
                  gfxId == VarGet(RandomNPCTrainers[newTrainer].gfxid))
                    rerollTrainerId = TRUE;
            }
        } while (rerollTrainerId);  
        //DebugPrintf("randomTrainerId = %d, graphicsId = %d", randomTrainerId, gfxId);
        if(Random() % 2)
        {
            VarSet(RandomNPCTrainers_Doubles[newTrainer].arrayElement, randomTrainerId);
            VarSet(RandomNPCTrainers_Doubles[newTrainer].gfxid, gfxId);
            VarSet(RandomNPCTrainers_Doubles[newTrainer].defeatTextVar, Random() % getNumberOfDefeatTexts());
            ClearTrainerFlag(RandomNPCTrainers_Doubles[newTrainer].trainerflag); 
            FlagClear(RandomNPCTrainers_Doubles[newTrainer].objectflag); 
        }
        else
        {
            VarSet(RandomNPCTrainers[newTrainer].arrayElement, randomTrainerId);
            VarSet(RandomNPCTrainers[newTrainer].gfxid, gfxId);
            VarSet(RandomNPCTrainers[newTrainer].defeatTextVar, Random() % getNumberOfDefeatTexts());
            ClearTrainerFlag(RandomNPCTrainers[newTrainer].trainerflag); 
            FlagClear(RandomNPCTrainers[newTrainer].objectflag); 
        }
    }
}

void CheckFloorCleared()
{
    u16 iterator = 0;
    u16 trainerDefeated = 0;
    for (iterator = 0; iterator < MAX_TRAINER_OBJECTS; iterator++)
    {
        if(iterator >= MAX_RANDOM_TRAINERS) //doubles
            trainerDefeated = (u8) FlagGet(TRAINER_FLAGS_START + RandomNPCTrainers_Doubles[iterator - 4].trainerflag) + trainerDefeated;
        else
            trainerDefeated = (u8) FlagGet(TRAINER_FLAGS_START + RandomNPCTrainers[iterator].trainerflag) + trainerDefeated;
    }
    if (trainerDefeated == MAX_TRAINER_OBJECTS)
        FlagSet(FLAG_FLOOR_CLEARED);
    return;
}

u16 ReturnTrainersRemaining()
{
    u16 iterator = 0;
    u16 trainerDefeated = 0;
    for (iterator = 0; iterator < MAX_TRAINER_OBJECTS; iterator++)
    {
        if(iterator >= MAX_RANDOM_TRAINERS) //doubles
            trainerDefeated = (u8) FlagGet(TRAINER_FLAGS_START + RandomNPCTrainers_Doubles[iterator - 4].trainerflag) + trainerDefeated;
        else
            trainerDefeated = (u8) FlagGet(TRAINER_FLAGS_START + RandomNPCTrainers[iterator].trainerflag) + trainerDefeated;
    }
    return MAX_TRAINER_OBJECTS - trainerDefeated;
}

u16 GetRandomTrainerEncounterTrainerPic(void)
{
    //DebugPrintf("trainerPic = %d", sRandomTrainerEncounterArray[GetLastSpokenVarObjTrainerArrayElement()].trainerPic);
    return sRandomTrainerEncounterArray[GetLastSpokenVarObjTrainerArrayElement()].trainerPic;
}

#define SEED_TRAINER_NAME (trainerId + VarGet(VAR_PIT_FLOOR) + gSaveBlock1Ptr->pos.x + (100 * gSaveBlock1Ptr->pos.y))
const u8 *GetRandomTrainerEncounterTrainerName(u16 trainerId)
{
    if (sRandomTrainerEncounterArray[GetLastSpokenVarObjTrainerArrayElement()].gender == MALE)
        return gRandomTrainerNamesM[RandomSeededModulo2(SEED_TRAINER_NAME, TRAINER_NAME_COUNT_M)];
    else
        return gRandomTrainerNamesF[RandomSeededModulo2(SEED_TRAINER_NAME, TRAINER_NAME_COUNT_F)];
}

const u8 GetRandomTrainerEncounterTrainerClass(void)
{
    if (gSpecialVar_TrainerNumber == TRAINER_RANDOM_PIT_BOSS || gSpecialVar_TrainerNumber == TRAINER_RANDOM_PIT_BOSS_DOUBLES)
        return TRAINER_CLASS_PIT_BOSS;
    else
        return sRandomTrainerEncounterArray[GetLastSpokenVarObjTrainerArrayElement()].trainerClass;
}


//
// 	Player Avatar System Code
//

struct PitAvatarInfo {
    u16 mugshotId;
    u16 graphicsId;
    u16 trainerFrontPicId;
    u16 trainerBackPicId;
};

#define PIT_AVATAR_COUNT ARRAY_COUNT(sPitAvatars)
static const struct PitAvatarInfo sPitAvatars[] = {
    {
        .mugshotId = AVATAR_BRENDAN,
        .graphicsId = OBJ_EVENT_GFX_BRENDAN_NORMAL,
        .trainerFrontPicId = TRAINER_PIC_BRENDAN,
        .trainerBackPicId = TRAINER_BACK_PIC_BRENDAN,
    },
    {
        .mugshotId = AVATAR_MAY,
        .graphicsId = OBJ_EVENT_GFX_MAY_NORMAL,
        .trainerFrontPicId = TRAINER_PIC_MAY,
        .trainerBackPicId = TRAINER_BACK_PIC_MAY,
    },

    {
        .mugshotId = AVATAR_RED,
        .graphicsId = OBJ_EVENT_GFX_RED,
        .trainerFrontPicId = TRAINER_PIC_RED,
        .trainerBackPicId = TRAINER_BACK_PIC_RED,
    },
    {
        .mugshotId = AVATAR_LEAF,
        .graphicsId = OBJ_EVENT_GFX_LEAF,
        .trainerFrontPicId = TRAINER_PIC_LEAF,
        .trainerBackPicId = TRAINER_BACK_PIC_LEAF,
    },

    {
        .mugshotId = AVATAR_LUCAS,
        .graphicsId = OBJ_EVENT_GFX_LUCAS,
        .trainerFrontPicId = TRAINER_PIC_LUCAS,
        .trainerBackPicId = TRAINER_BACK_PIC_LUCAS,
    },
    {
        .mugshotId = AVATAR_DAWN,
        .graphicsId = OBJ_EVENT_GFX_DAWN,
        .trainerFrontPicId = TRAINER_PIC_DAWN,
        .trainerBackPicId = TRAINER_BACK_PIC_DAWN,
    },

    {
        .mugshotId = AVATAR_ETHAN,
        .graphicsId = OBJ_EVENT_GFX_ETHAN,
        .trainerFrontPicId = TRAINER_PIC_ETHAN,
        .trainerBackPicId = TRAINER_BACK_PIC_ETHAN,
    },
    {
        .mugshotId = AVATAR_LYRA,
        .graphicsId = OBJ_EVENT_GFX_LYRA,
        .trainerFrontPicId = TRAINER_PIC_LYRA,
        .trainerBackPicId = TRAINER_BACK_PIC_LYRA,
    },

    {
        .mugshotId = AVATAR_STEVEN,
        .graphicsId = OBJ_EVENT_GFX_STEVEN,
        .trainerFrontPicId = TRAINER_PIC_STEVEN,
        .trainerBackPicId = TRAINER_BACK_PIC_STEVEN,
    },
    {
        .mugshotId = AVATAR_CYNTHIA,
        .graphicsId = OBJ_EVENT_GFX_CYNTHIA,
        .trainerFrontPicId = TRAINER_PIC_CYNTHIA,
        .trainerBackPicId = TRAINER_BACK_PIC_CYNTHIA,
    },

    {
        .mugshotId = AVATAR_OAK,
        .graphicsId = OBJ_EVENT_GFX_OAK,
        .trainerFrontPicId = TRAINER_PIC_OAK,
        .trainerBackPicId = TRAINER_BACK_PIC_OAK,
    },
    {
        .mugshotId = AVATAR_PHOEBE,
        .graphicsId = OBJ_EVENT_GFX_PHOEBE,
        .trainerFrontPicId = TRAINER_PIC_ELITE_FOUR_PHOEBE,
        .trainerBackPicId = TRAINER_BACK_PIC_PHOEBE,
    },

    {
        .mugshotId = AVATAR_NATE,
        .graphicsId = OBJ_EVENT_GFX_NATE,
        .trainerFrontPicId = TRAINER_PIC_ELITE_FOUR_PHOEBE, //front pic not used in game
        .trainerBackPicId = TRAINER_BACK_PIC_NATE,
    },
    {
        .mugshotId = AVATAR_ROSA,
        .graphicsId = OBJ_EVENT_GFX_ROSA,
        .trainerFrontPicId = TRAINER_PIC_ELITE_FOUR_PHOEBE, //front pic not used in game
        .trainerBackPicId = TRAINER_BACK_PIC_ROSA,
    },

    {
        .mugshotId = AVATAR_WALLY,
        .graphicsId = OBJ_EVENT_GFX_WALLY,
        .trainerFrontPicId = TRAINER_PIC_WALLY, //front pic not used in game
        .trainerBackPicId = TRAINER_BACK_PIC_WALLY,
    },
    {
        .mugshotId = AVATAR_LILLIE,
        .graphicsId = OBJ_EVENT_GFX_LILLIE,
        .trainerFrontPicId = TRAINER_PIC_ELITE_FOUR_PHOEBE, //front pic not used in game
        .trainerBackPicId = TRAINER_BACK_PIC_LILLIE,
    },

    {
        .mugshotId = AVATAR_POKEMON_CHOICE,
        .graphicsId = 0xFFFF,
        .trainerFrontPicId = 0xFFFF,
        .trainerBackPicId = TRAINER_BACK_PIC_DUMMY,
    },

};

u16 ReturnAvatarMugshotId(u16 avatarId)
{
    return sPitAvatars[avatarId].mugshotId;
}

u16 ReturnAvatarGraphicsId(u16 avatarId)
{
    u16 graphicsId = sPitAvatars[avatarId].graphicsId;
    if(graphicsId == 0xFFFF)
    {
        graphicsId = OBJ_EVENT_GFX_VAR_D;
        VarSet(VAR_OBJ_GFX_ID_D, gSaveBlock2Ptr->pokemonAvatarSpecies + OBJ_EVENT_GFX_MON_BASE);
        TryCreatePokemonAvatarSpriteBob();
    }
    return graphicsId;
}

u16 ReturnAvatarTrainerFrontPicId(u16 avatarId)
{
    return sPitAvatars[avatarId].trainerFrontPicId;
}

u16 ReturnAvatarTrainerBackPicId(u16 avatarId)
{
    return sPitAvatars[avatarId].trainerBackPicId;
}

void SetPlayerAvatar(void)
{
    gSaveBlock2Ptr->playerGfxType = VarGet(VAR_RESULT);
    gSaveBlock2Ptr->playerGender  = VarGet(VAR_RESULT) % 2;
}

void TryCreatePokemonAvatarSpriteBob(void)
{   
    if(!(FuncIsActiveTask(Task_CreatePokemonAvatarBob) || FuncIsActiveTask(Task_PokemonAvatar_HandleBob)))
        CreateTask(Task_CreatePokemonAvatarBob, 0);
}

void Task_CreatePokemonAvatarBob(u8 taskId)
{
    if(gMain.callback2 == CB2_Overworld)
    {
        gTasks[taskId].func = Task_PokemonAvatar_HandleBob;
    }
}

#define STEP_FRAME_DURATION 6
void Task_PokemonAvatar_HandleBob(u8 taskId)
{
    struct ObjectEvent *playerObj = &gObjectEvents[gPlayerAvatar.objectEventId];
    struct Sprite *playerSprite = &gSprites[playerObj->spriteId];
    u8 movementActionId = playerObj->movementActionId;
    s16 *data = gTasks[taskId].data;

    switch(movementActionId)
    {
        case MOVEMENT_ACTION_WALK_FAST_DOWN:  
        case MOVEMENT_ACTION_WALK_FAST_UP:    
        case MOVEMENT_ACTION_WALK_FAST_LEFT:  
        case MOVEMENT_ACTION_WALK_FAST_RIGHT: 
        case MOVEMENT_ACTION_WALK_NORMAL_DOWN:  
        case MOVEMENT_ACTION_WALK_NORMAL_UP:    
        case MOVEMENT_ACTION_WALK_NORMAL_LEFT:  
        case MOVEMENT_ACTION_WALK_NORMAL_RIGHT: 
            break;
        default:
            playerSprite->y2 = 1;
            data[0] = 0;
            return;
    }

    if(data[0] == 0)
    {
        playerSprite->y2 = 1;
    }

    if(data[0] == STEP_FRAME_DURATION)
    {
        playerSprite->y2 -= 1;
    }

    if(data[0] == (STEP_FRAME_DURATION * 2))
    {
        playerSprite->y2 += 1;
        data[0] = 0;
        return;
    }

    data[0]++;

}


//
// 	Random Pit Arena / Map Code
//

struct sRandomMap {
    u16 mapConstant;
    u16 warpMetatileId;
    u16 battleTerrainId;
    u16 weatherId;
    u16 weatherChance;
    u16 dest_x;
    u16 dest_y;
    u16 warp_x;
    u16 warp_y;
};

// Default Coords for Random Maps size 20x20 with the warp in the center at 9x9
#define DEFAULT_RANDOM_MAP_COORDS           .dest_x = 9,    \
                                            .dest_y = 8,    \
                                            .warp_x = 9,    \
                                            .warp_y = 9,

#define WEATHER_CHANCE(x, y)    .weatherId = WEATHER_##x, \
                                .weatherChance = y

#define RANDOM_MAP_COUNT    ARRAY_COUNT(sRandomMapArray)
static const struct sRandomMap sRandomMapArray[] = {
    {
        .mapConstant = MAP_PIT_ARENA,
        .warpMetatileId = METATILE_Cave_FLOOR_COMPLETE,
        .battleTerrainId = BATTLE_TERRAIN_CAVE,
        WEATHER_CHANCE(NONE, 0),
        DEFAULT_RANDOM_MAP_COORDS
    },     
    {
        .mapConstant = MAP_PIT_ARENA_BEACH,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(RAIN, 10),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_WATER,
        .warpMetatileId = METATILE_PitWaterTheme_WATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_WATER,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_DESERT,
        .warpMetatileId = METATILE_PitArenaDesert_DESERT_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(SANDSTORM, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_SNOW,
        .warpMetatileId = METATILE_PitArenaSnow_SNOW_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(SNOW, 90),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_MUSHROOM_WOODS,
        .warpMetatileId = METATILE_PitArenaMushroomWoods_MUSHROOM_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },        
    {
        .mapConstant = MAP_PIT_ARENA_DIRT_PATH,
        .warpMetatileId = METATILE_PitArenaDirtPath_DIRT_PATH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_SPIDER_WOODS,
        .warpMetatileId = METATILE_PitArenaSpiderWoods_SPIDER_WOODS_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_UNDERWATER,
        .warpMetatileId = METATILE_PitArenaUnderwater_UNDERWATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_UNDERWATER,
        WEATHER_CHANCE(UNDERWATER_BUBBLES, 100),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_MINE,
        .warpMetatileId = METATILE_PitArenaMine_MINE_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_CAVE,
        WEATHER_CHANCE(FOG_HORIZONTAL, 15),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_WHITE_BARK,
        .warpMetatileId = METATILE_PitArenaWhiteBark_WHITEBARK_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },       
    {
        .mapConstant = MAP_PIT_ARENA_WATER02,
        .warpMetatileId = METATILE_PitWaterTheme_WATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_WATER,
        WEATHER_CHANCE(RAIN, 50),
        .dest_x = 9,
        .dest_y = 10,
        .warp_x = 9,
        .warp_y = 11,
    },          
    {
        .mapConstant = MAP_PIT_ARENA_SNOW02,
        .warpMetatileId = METATILE_PitArenaSnow_SNOW_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(SNOW, 90),
        DEFAULT_RANDOM_MAP_COORDS
    },      
    {
        .mapConstant = MAP_PIT_ARENA_MINE02,
        .warpMetatileId = METATILE_PitArenaMine_MINE_TOP_CAVE_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_CAVE,
        WEATHER_CHANCE(FOG_HORIZONTAL, 15),
        .dest_x = 15,
        .dest_y = 13,
        .warp_x = 15,
        .warp_y = 14,
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH02,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(RAIN, 10),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH03,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(RAIN, 10),
        DEFAULT_RANDOM_MAP_COORDS
    },    
     {
        .mapConstant = MAP_PIT_ARENA_BEACH04,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(RAIN, 10),
        DEFAULT_RANDOM_MAP_COORDS
    },       
    {
        .mapConstant = MAP_PIT_ARENA_DEEP_FOREST,
        .warpMetatileId = METATILE_PitArenaDeepForest_DEEP_FOREST_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 17,
        .dest_y = 17,
        .warp_x = 17,
        .warp_y = 18,
    },
    {
        .mapConstant = MAP_PIT_ARENA_DEEP_FOREST02,
        .warpMetatileId = METATILE_PitArenaDeepForest_DEEP_FOREST_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 18,
        .dest_y = 17,
        .warp_x = 18,
        .warp_y = 18,
    },
    {
        .mapConstant = MAP_PIT_ARENA_WHITE_BARK02,
        .warpMetatileId = METATILE_PitArenaWhiteBark_WHITEBARK_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 80),
        .dest_x = 10,
        .dest_y = 9,
        .warp_x = 10,
        .warp_y = 10,
    },   
     {
        .mapConstant = MAP_PIT_ARENA_SNOW03,
        .warpMetatileId = METATILE_PitArenaSnow_SNOW_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(SNOW, 90),
        .dest_x = 12,
        .dest_y = 11,
        .warp_x = 12,
        .warp_y = 12,
    },    
    {
        .mapConstant = MAP_PIT_ARENA_DESERT02,
        .warpMetatileId = METATILE_PitArenaDesert_DESERT_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(SANDSTORM, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_DIRT_PATH02,
        .warpMetatileId = METATILE_PitArenaDirtPath_DIRT_PATH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_UNDERWATER02,
        .warpMetatileId = METATILE_PitArenaUnderwater_UNDERWATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_UNDERWATER,
        WEATHER_CHANCE(UNDERWATER_BUBBLES, 100),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_MINE03,
        .warpMetatileId = METATILE_PitArenaMine_MINE_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_CAVE,
        WEATHER_CHANCE(FOG_HORIZONTAL, 15),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_DIRT_PATH03,
        .warpMetatileId = METATILE_PitArenaDirtPath_DIRT_PATH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },    
    {
        .mapConstant = MAP_PIT_ARENA_MUSHROOM_WOODS02,
        .warpMetatileId = METATILE_PitArenaMushroomWoods_MUSHROOM_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(FOG_HORIZONTAL, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_SPIDER_WOODS02,
        .warpMetatileId = METATILE_PitArenaSpiderWoods_SPIDER_WOODS_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_SNOW04,
        .warpMetatileId = METATILE_PitArenaSnow_SNOW_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(SNOW, 90),
        .dest_x = 9,
        .dest_y = 16,
        .warp_x = 9,
        .warp_y = 17,
    },   
    {
        .mapConstant = MAP_PIT_ARENA_WATER03,
        .warpMetatileId = METATILE_PitWaterTheme_WATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_WATER,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },  
    {
        .mapConstant = MAP_PIT_ARENA_WATER04,
        .warpMetatileId = METATILE_PitWaterTheme_WATER_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_WATER,
        WEATHER_CHANCE(RAIN, 50),
        .dest_x = 13,
        .dest_y = 12,
        .warp_x = 13,
        .warp_y = 13,
    },  
    {
        .mapConstant = MAP_PIT_ARENA_DIRT_PATH04,
        .warpMetatileId = METATILE_PitArenaDirtPath_DIRT_PATH_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_MOUNTAIN,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_DESERT03,
        .warpMetatileId = METATILE_PitArenaDesert_DESERT_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(SANDSTORM, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_DESERT04,
        .warpMetatileId = METATILE_PitArenaDesert_DESERT_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(SANDSTORM, 80),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_SPIDER_WOODS03,
        .warpMetatileId = METATILE_PitArenaSpiderWoods_SPIDER_WOODS_WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_GRASS,
        WEATHER_CHANCE(RAIN, 50),
        DEFAULT_RANDOM_MAP_COORDS
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH_CAVE,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_CAVE__WARP_ACTIVE_2,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 17,
        .dest_y = 10,
        .warp_x = 17,
        .warp_y = 11,
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH_CAVE02,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_CAVE__WARP_ACTIVE_2,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 15,
        .dest_y = 17,
        .warp_x = 15,
        .warp_y = 15,
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH_CAVE03,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_CAVE__WARP_ACTIVE_2,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 13,
        .dest_y = 8,
        .warp_x = 13,
        .warp_y = 9,
    },
    {
        .mapConstant = MAP_PIT_ARENA_BEACH_CAVE04,
        .warpMetatileId = METATILE_PitArenaBeach_BEACH_CAVE__WARP_ACTIVE,
        .battleTerrainId = BATTLE_TERRAIN_SAND,
        WEATHER_CHANCE(FOG_HORIZONTAL, 50),
        .dest_x = 21,
        .dest_y = 13,
        .warp_x = 21,
        .warp_y = 14,
    },
    
};

void WarpToRandomPitArena(void)
{
    u16 index;
    u16 indexCurrentMap = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);

    do
    {
        index = Random() % RANDOM_MAP_COUNT;
    }
    while (index == indexCurrentMap); //don't roll the current map again

     //return default map if randomization is turned off
    if (!FlagGet(FLAG_RANDOM_MAPS))
        index = 0;
    
    VarSet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY, index);
    SetWarpDestination(0, (u8)(sRandomMapArray[index].mapConstant & 0x00FF), WARP_ID_NONE, sRandomMapArray[index].dest_x, sRandomMapArray[index].dest_y);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
    return;
}

void SetWarpTileActive(void)
{
    u16 currentIndex = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);
    if(currentIndex != 0xFF)
        MapGridSetMetatileIdAt(sRandomMapArray[currentIndex].warp_x + MAP_OFFSET, sRandomMapArray[currentIndex].warp_y + MAP_OFFSET, sRandomMapArray[currentIndex].warpMetatileId);
}

u16 GetRandomMapTerrain(void)
{   
    u16 currentIndex = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);
    if(currentIndex != 0xFF)
    {
        return sRandomMapArray[currentIndex].battleTerrainId;
    }
    return BATTLE_TERRAIN_CAVE;
}

u32 GetRandomMapWeather(void)
{
    u16 currentIndex = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);
    if(currentIndex != 0xFF)
    {
        return sRandomMapArray[currentIndex].weatherId;
    }
    return B_WEATHER_NONE;
}

void SetMapWeather(void)
{
    SetWeather(GetRandomMapWeather());
    DoCurrentWeather();
}

void SetMapWeatherAtRandom(void)
{
    u16 currentChance = 0;
   
    u16 currentIndex = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);
    if(currentIndex != 0xFF)
    {
        currentChance = sRandomMapArray[currentIndex].weatherChance;
    }

    u8 rand = Random() % 100;
    if (rand < currentChance)
    {
        SetMapWeather();
    }
}

u16 GetCurrentMapConstant(void)
{
    u16 currentIndex = VarGet(VAR_PIT_CURRENT_MAP_INDEX_IN_ARRAY);
    if(currentIndex != 0xFF)
    {
        return sRandomMapArray[currentIndex].mapConstant;
    }
    return MAP_PIT_ARENA;
}

u16 GetPrimaryTilesetIdCurrentMap(void)
{
    if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitWaterTheme)
        return TILESET_WATER;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaWhiteBark)
        return TILESET_WHITE_BARK;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaDesert)
        return TILESET_DESERT;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaSnow)
        return TILESET_SNOW;
    else if (gMapHeader.mapLayout->secondaryTileset == &gTileset_PitArenaBeachCave) //must be before PitArenaBeach as they both share the same primary
        return TILESET_BEACH_CAVE;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaBeach)
        return TILESET_BEACH;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaDirtPath)
        return TILESET_DIRT_PATH;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaMushroomWoods)
        return TILESET_MUSHROOM_WOODS;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaSpiderWoods)
        return TILESET_SPIDER_WOODS;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaUnderwater)
        return TILESET_UNDERWATER;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaMine)
        return TILESET_MINE;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaDeepForest)
        return TILESET_DEEP_FOREST;
    else if (gMapHeader.mapLayout->primaryTileset == &gTileset_PitArenaClouds)
        return TILESET_CLOUDS;
    else
        return TILESET_VANILLA;
}



//
// 	Random Overworld Pokemon Script System Code
//

struct RandomMonEncounters {
    u16 species;
    u16 flagId; // id into gSaveBlock1Ptr->randomMonEncounters not normal flags
    const u8 *monScript;
    const u8 *alreadyUsedScript;
    const u8 resetOnFloor;
};

#define RANDOM_ENCOUNTER_COUNT ARRAY_COUNT(sRandomEncounterArray)
static const struct RandomMonEncounters sRandomEncounterArray[] = {
    {
        .species = SPECIES_ABRA,
        .flagId = 0,
        .monScript = PitEncounter_Mover,
        .alreadyUsedScript = PitEncounter_Mover_alreadyUsed,
        .resetOnFloor = 50,
    },
#ifndef PIT_GEN_3_MODE
    {
        .species = SPECIES_JIRACHI,
        .flagId = 1,
        .monScript = PitEncounter_GrantWishChoiceItem,
        .alreadyUsedScript = PitEncounter_GrantWishChoiceItem_alreadyUsed,
        .resetOnFloor = 100,
    },
#endif
    {
        .species = SPECIES_SHEDINJA,
        .flagId = 2,
        .monScript = PitEncounter_ReviveOneMon,
        .alreadyUsedScript = PitEncounter_ReviveOneMon_alreadyUsed,
        .resetOnFloor = 50,
    },
    {
        .species = SPECIES_CHANSEY,
        .flagId = 3,
        .monScript = PitEncounter_HealOneMon,
        .alreadyUsedScript = PitEncounter_HealOneMon_alreadyUsed,
        .resetOnFloor = 100,
        //.monScript = PitEncounter_LuckyEggDrop,
    },
    {
        .species = SPECIES_MEOWTH,
        .flagId = 4,
        .monScript = PitEncounter_AmuletCoinDrop,
        .alreadyUsedScript = PitEncounter_AmuletCoinDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
    {
        .species = SPECIES_DELIBIRD,
        .flagId = 5,
        .monScript = PitEncounter_Present,
        .alreadyUsedScript = PitEncounter_Present_alreadyUsed,
        .resetOnFloor = 50,
    },
#if (GEN_LATEST == GEN_9)
    {
        .species = SPECIES_GHOLDENGO,
        .flagId = 6,
        .monScript = PitEncounter_NuggetDrop,
        .alreadyUsedScript = PitEncounter_NuggetDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
#else
    {
        .species = SPECIES_SABLEYE,
        .flagId = 6,
        .monScript = PitEncounter_NuggetDrop,
        .alreadyUsedScript = PitEncounter_NuggetDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
#endif
    {
        .species = SPECIES_ZIGZAGOON,
        .flagId = 7,
        .monScript = PitEncounter_WonderTrade,
        .alreadyUsedScript = PitEncounter_WonderTrade_alreadyUsed,
        .resetOnFloor = 25,
    },
    {
        .species = SPECIES_MILTANK,
        .flagId = 8,
        .monScript = PitEncounter_MooMooMilkDrop,
        .alreadyUsedScript = PitEncounter_MooMooMilkDrop_alreadyUsed,
        .resetOnFloor = 50,
    },
    {
        .species = SPECIES_CHIMECHO,
        .flagId = 9,
        .monScript = PitEncounter_CureAllStatus,
        .alreadyUsedScript = PitEncounter_CureAllStatus_alreadyUsed,
        .resetOnFloor = 25,
    },
#if (GEN_LATEST != GEN_3)
    {
        .species = SPECIES_MUNCHLAX,
        .flagId = 10,
        .monScript = PitEncounter_LeftoversDrop,
        .alreadyUsedScript = PitEncounter_LeftoversDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
#else
    {
        .species = SPECIES_SNORLAX,
        .flagId = 10,
        .monScript = PitEncounter_LeftoversDrop,
        .alreadyUsedScript = PitEncounter_LeftoversDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
#endif
    {
        .species = SPECIES_EEVEE,
        .flagId = 11,
        .monScript = PitEncounter_RareCandyDrop,
        .alreadyUsedScript = PitEncounter_RareCandyDrop_alreadyUsed,
        .resetOnFloor = 100,
    },
};

u8 *GetEncounterFlagPointer(u16 id)
{
    return &gSaveBlock1Ptr->randomMonEncounters[id / 8];
}

u8 EncounterFlagSet(u16 id)
{
    u8 *ptr = GetEncounterFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 EncounterFlagClear(u16 id)
{
    u8 *ptr = GetEncounterFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 EncounterFlagGet(u16 id)
{
    u8 *ptr = GetEncounterFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}

bool8 RemainingEncounters(void)
{
    u8 i = 0;
    u8 count = 0;

    for(i = 0; i < RANDOM_ENCOUNTER_COUNT; i++)
    {
        if(!EncounterFlagGet(i))
            count++;
    }
    return count;
}

void ClearAllRandomEncounters(void)
{
    u8 i = 0;
    for(i = 0; i < RANDOM_ENCOUNTER_COUNT; i++)
    {
        EncounterFlagClear(i);
    }
}

void ClearRandomEncounters(void)
{
    u8 i = 0;
    for(i = 0; i < RANDOM_ENCOUNTER_COUNT; i++)
    {
        if ((VarGet(VAR_PIT_FLOOR) % sRandomEncounterArray[i].resetOnFloor) == 0)
            EncounterFlagClear(i);
    }
}

void SetRandomMonEncounter(void)
{
    bool8 reroll = FALSE;
    FlagSet(FLAG_OVERWORLD_MON_ENCOUNTER);

    ClearRandomEncounters();

    if (Random() % 5) // Odds of A Random Encounter On Each Floor
        return;

    if(VarGet(VAR_PIT_FLOOR) <= 5)
        return;

    if(!RemainingEncounters()) // Cancel if All Random Encounters have been done
        return;

    do {
        u16 index = Random() % RANDOM_ENCOUNTER_COUNT;
        if(EncounterFlagGet(index))
        {
            reroll = TRUE;
        }
        //floor skipping only if 3 floors before pit stops
        else if (sRandomEncounterArray[index].species == SPECIES_ABRA
         && (VarGet(VAR_PIT_FLOOR) % 5) != 3)
        {
            //if Abra is the last remaining encounter we would be stuck otherwise
            if (RemainingEncounters() <= 1)
                return;
            if ((RemainingEncounters() <= 2) && (gSaveBlock2Ptr->modeXP == 2))
                return;

            reroll = TRUE;
        }
        else if ((sRandomEncounterArray[index].species == SPECIES_EEVEE) && ((gSaveBlock2Ptr->modeXP == 2)))
        {
            //if Eevee is the last remaining encounter we would be stuck otherwise
            if (RemainingEncounters() <= 2)
                return;

            reroll = TRUE;
        }
        else
        {
            reroll = FALSE;
            EncounterFlagSet(index);
            VarSet(VAR_OVERWORLD_MON_SPECIES, sRandomEncounterArray[index].species);
            VarSet(VAR_CURRENT_OVERWORLD_ENCOUNTER_INDEX, index);
            FlagClear(FLAG_OVERWORLD_MON_ENCOUNTER);
            FlagClear(FLAG_USED_RANDOM_ENCOUNTER_THIS_FLOOR);
            return;
        }
    } while (reroll);

}

void CallRandomMonEncounterScript(void)
{
    if(FlagGet(FLAG_USED_RANDOM_ENCOUNTER_THIS_FLOOR))
    {
        //ScriptContext_SetupScript(PitEncounter_Common_AlreadyUsedEffect); // Can Swap for a Mon Specific Post Script From the Struct if we want
        ScriptContext_SetupScript(sRandomEncounterArray[VarGet(VAR_CURRENT_OVERWORLD_ENCOUNTER_INDEX)].alreadyUsedScript);
    }
    else
    {
        ScriptContext_SetupScript(sRandomEncounterArray[VarGet(VAR_CURRENT_OVERWORLD_ENCOUNTER_INDEX)].monScript);
    }
}

void HealPlayerPokemon(void)
{
    HealPokemon(&gPlayerParty[VarGet(VAR_0x8005)]);
}

void CheckMonFainted(void)
{
    struct Pokemon *pokemon = &gPlayerParty[VarGet(VAR_0x8005)];
    u16 species = GetMonData(pokemon, MON_DATA_SPECIES_OR_EGG);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
    {
        VarSet(VAR_RESULT, FALSE);
        return;
    }
    if ((GetMonData(pokemon, MON_DATA_HP) == 0))
        VarSet(VAR_RESULT, TRUE);
    else
        VarSet(VAR_RESULT, FALSE);
}

void HealAllStatus(void)
{
    u32 status = 0;
    for(u8 i = 0; i < 6; i++)
    {
        SetMonData(&gPlayerParty[i], MON_DATA_STATUS, &status);
    }
}



//
// 	Random Overworld Music Code
//

static const u16 sRandomOverworldSongs[] = {
    MUS_C_COMM_CENTER,
    MUS_ROUTE101,
    MUS_ROUTE110,
    MUS_ROUTE120,
    MUS_PETALBURG,
    MUS_OLDALE,
    MUS_GYM,
    MUS_SURF,
    MUS_PETALBURG_WOODS,
    MUS_LILYCOVE_MUSEUM,
    MUS_ROUTE122,
    MUS_OCEANIC_MUSEUM,
    MUS_ABANDONED_SHIP,
    MUS_FORTREE,
    MUS_BIRCH_LAB,
    MUS_B_TOWER_RS,
    MUS_CAVE_OF_ORIGIN,
    MUS_AWAKEN_LEGEND,
    MUS_VERDANTURF,
    MUS_RUSTBORO,
    MUS_POKE_CENTER,
    MUS_ROUTE104,
    MUS_ROUTE119,
    MUS_CYCLING,
    MUS_POKE_MART,
    MUS_LITTLEROOT,
    MUS_MT_CHIMNEY,
    MUS_LILYCOVE,
    MUS_ROUTE111,
    MUS_UNDERWATER,
    MUS_ROUTE113,
    MUS_EVER_GRANDE,
    MUS_CABLE_CAR,
    MUS_GAME_CORNER,
    MUS_DEWFORD,
    MUS_SAFARI_ZONE,
    MUS_VICTORY_ROAD,
    MUS_AQUA_MAGMA_HIDEOUT,
    MUS_SAILING,
    MUS_MT_PYRE,
    MUS_SLATEPORT,
    MUS_MT_PYRE_EXTERIOR,
    MUS_SCHOOL,
    MUS_FALLARBOR,
    MUS_SEALED_CHAMBER,
    MUS_CONTEST,
    MUS_WEATHER_KYOGRE,
    MUS_SOOTOPOLIS,
    MUS_HALL_OF_FAME_ROOM,
    MUS_TRICK_HOUSE,
    MUS_CONTEST_LOBBY,
    MUS_RG_GAME_CORNER,
    MUS_RG_ROCKET_HIDEOUT,
    MUS_RG_GYM,
    MUS_RG_CINNABAR,
    MUS_RG_LAVENDER,
    MUS_RG_CYCLING,
    MUS_RG_HALL_OF_FAME,
    MUS_RG_VIRIDIAN_FOREST,
    MUS_RG_MT_MOON,
    MUS_RG_POKE_MANSION,
    MUS_RG_ROUTE1,
    MUS_RG_ROUTE24,
    MUS_RG_ROUTE3,
    MUS_RG_ROUTE11,
    MUS_RG_VICTORY_ROAD,
    MUS_RG_PALLET,
    MUS_RG_OAK_LAB,
    MUS_RG_POKE_CENTER,
    MUS_RG_SS_ANNE,
    MUS_RG_SURF,
    MUS_RG_POKE_TOWER,
    MUS_RG_SILPH,
    MUS_RG_FUCHSIA,
    MUS_RG_CELADON,
    MUS_RG_VERMILLION,
    MUS_RG_PEWTER,
    MUS_RG_SEVII_ROUTE,
    MUS_ABNORMAL_WEATHER,
    MUS_B_FRONTIER,
    MUS_B_ARENA,
    MUS_B_PYRAMID,
    MUS_B_PALACE,
    MUS_B_TOWER,
    MUS_B_DOME,
    MUS_B_PIKE,
    MUS_B_FACTORY,
    MUS_DP_TWINLEAF_DAY,
    MUS_DP_SANDGEM_DAY,
    MUS_DP_FLOAROMA_DAY,
    MUS_DP_SOLACEON_DAY,
    MUS_DP_ROUTE225_DAY,
    MUS_DP_VALOR_LAKEFRONT_DAY,
    MUS_DP_JUBILIFE_DAY,
    MUS_DP_CANALAVE_DAY,
    MUS_DP_OREBURGH_DAY,
    MUS_DP_ETERNA_DAY,
    MUS_DP_HEARTHOME_DAY,
    MUS_DP_VEILSTONE_DAY,
    MUS_DP_SUNYSHORE_DAY,
    MUS_DP_SNOWPOINT_DAY,
    MUS_DP_FIGHT_AREA_DAY,
    MUS_DP_ROUTE201_DAY,
    MUS_DP_ROUTE203_DAY,
    MUS_DP_ROUTE205_DAY,
    MUS_DP_ROUTE206_DAY,
    MUS_DP_ROUTE209_DAY,
    MUS_DP_ROUTE210_DAY,
    MUS_DP_ROUTE216_DAY,
    MUS_DP_ROUTE228_DAY,
    MUS_DP_UNDERGROUND,
    MUS_DP_VICTORY_ROAD,
    MUS_DP_ETERNA_FOREST,
    MUS_DP_OLD_CHATEAU,
    MUS_DP_LAKE_CAVERNS,
    MUS_DP_AMITY_SQUARE,
    MUS_DP_GALACTIC_HQ,
    MUS_DP_GALACTIC_ETERNA_BUILDING,
    MUS_DP_GREAT_MARSH,
    MUS_DP_LAKE,
    MUS_DP_MT_CORONET,
    MUS_DP_SPEAR_PILLAR,
    MUS_DP_STARK_MOUNTAIN,
    MUS_DP_OREBURGH_GATE,
    MUS_DP_OREBURGH_MINE,
    MUS_DP_INSIDE_POKEMON_LEAGUE,
    MUS_DP_HALL_OF_FAME_ROOM,
    MUS_DP_POKE_CENTER_DAY,
    MUS_DP_GYM,
    MUS_DP_ROWAN_LAB,
    MUS_DP_CONTEST_LOBBY,
    MUS_DP_POKE_MART,
    MUS_DP_GAME_CORNER,
    MUS_DP_B_TOWER,
    MUS_DP_TV_STATION,
    MUS_DP_GTS,
    MUS_DP_SURF,
    MUS_DP_CYCLING,
    MUS_PL_B_ARCADE,
    MUS_PL_B_HALL,
    MUS_PL_B_CASTLE,
    MUS_PL_B_FACTORY,
    MUS_PL_LILYCOVE_BOSSA_NOVA,
    MUS_HG_CYCLING,
    MUS_HG_SURF,
    MUS_HG_NEW_BARK,
    MUS_HG_CHERRYGROVE,
    MUS_HG_VIOLET,
    MUS_HG_AZALEA,
    MUS_HG_GOLDENROD,
    MUS_HG_ECRUTEAK,
    MUS_HG_CIANWOOD,
    MUS_HG_ROUTE29,
    MUS_HG_ROUTE30,
    MUS_HG_ROUTE34,
    MUS_HG_ROUTE38,
    MUS_HG_ROUTE42,
    MUS_HG_VERMILION,
    MUS_HG_PEWTER,
    MUS_HG_CERULEAN,
    MUS_HG_LAVENDER,
    MUS_HG_CELADON,
    MUS_HG_PALLET,
    MUS_HG_CINNABAR,
    MUS_HG_ROUTE1,
    MUS_HG_ROUTE3,
    MUS_HG_ROUTE11,
    MUS_HG_ROUTE24,
    MUS_HG_ROUTE26,
    MUS_HG_POKE_CENTER,
    MUS_HG_POKE_MART,
    MUS_HG_GYM,
    MUS_HG_ELM_LAB,
    MUS_HG_DANCE_THEATER,
    MUS_HG_GAME_CORNER,
    MUS_HG_B_TOWER,
    MUS_HG_SPROUT_TOWER,
    MUS_HG_UNION_CAVE,
    MUS_HG_RUINS_OF_ALPH,
    MUS_HG_NATIONAL_PARK,
    MUS_HG_BURNED_TOWER,
    MUS_HG_BELL_TOWER,
    MUS_HG_LIGHTHOUSE,
    MUS_HG_TEAM_ROCKET_HQ,
    MUS_HG_ICE_PATH,
    MUS_HG_DRAGONS_DEN,
    MUS_HG_ROCK_TUNNEL,
    MUS_HG_VIRIDIAN_FOREST,
    MUS_HG_VICTORY_ROAD,
    MUS_HG_POKEMON_LEAGUE,
    MUS_HG_POKEATHLON_LOBBY,
    MUS_HG_B_FACTORY,
    MUS_HG_B_HALL,
    MUS_HG_B_ARCADE,
    MUS_HG_B_CASTLE,
    MUS_HG_ROUTE47,
    MUS_HG_SAFARI_ZONE_GATE,
    MUS_HG_SAFARI_ZONE,
};

#define NUM_OVERWORLD_SONGS 198

void TrySetRandomMusic(void)
{
    if (!gSaveBlock2Ptr->optionsRandomMusic)
        return;

    u16 songIndex = Random() % NUM_OVERWORLD_SONGS;
    Overworld_SetSavedMusic(sRandomOverworldSongs[songIndex]);
    PlayNewMapMusic(sRandomOverworldSongs[songIndex]);
}



//
// 	Boss Encounter Code
//

struct RandomBossEncounters {
    u16 graphicsId;
    u16 trainerPic;
    u16 flagId; // id into gSaveBlock1Ptr->randomBossEncounters not normal flags
    const u8 *bossName;
    const u8 *bossApproachText;
    const u8 *bossLoseText;
    const u8 *bossAceText;
    const struct TrainerMon trainerAce;
};

#define RANDOM_BOSS_ENCOUNTER_COUNT ARRAY_COUNT(sRandomBossEncounterArray)
static const struct RandomBossEncounters sRandomBossEncounterArray[] = {
    {
        .graphicsId = OBJ_EVENT_GFX_NORMAN,
        .trainerPic = TRAINER_PIC_LEADER_NORMAN,
        .bossName = COMPOUND_STRING("Norman"),
        .bossApproachText =  COMPOUND_STRING("I lost...\p"
                                            "I rethought everything about myself,\n"
                                            "so now there's no way I can lose!\p"
                                            "You'd better give it your best shot!$"),
        .bossLoseText =     COMPOUND_STRING("You went all out and earned that\n"
                                            "victory... You're a wonderful Trainer!\p"
                                            "I want my kid to learn from you.$"),
        .bossAceText =      COMPOUND_STRING("I'm giving this everything I've got!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SLAKING,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_SHADOW_BALL}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SLAKING,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_NIGHT_SLASH}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SLAKING,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_KNOCK_OFF}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_WINONA,
        .trainerPic = TRAINER_PIC_LEADER_WINONA,
        .bossName = COMPOUND_STRING("Winona"),
        .bossApproachText =  COMPOUND_STRING("I have become one with bird Pokémon\n"
                                            "and have soared the skies...\p"
                                            "However grueling the battle, we have\n"
                                            "triumphed with grace...\p"
                                            "Witness the elegant choreography of my\n"
                                            "Pokémon and I!$"),
        .bossLoseText =     COMPOUND_STRING("Your devotion... That's what brought\n"
                                            "you victory. It's praiseworthy.$"),
        .bossAceText =      COMPOUND_STRING("I will seize the wind!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ALTARIA,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_DRAGON_CLAW, MOVE_DOUBLE_EDGE}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ALTARIA,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_DRAGON_CLAW, MOVE_DOUBLE_EDGE}
        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ALTARIA,
                            .heldItem = ITEM_ALTARIANITE,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_DRAGON_CLAW, MOVE_DOUBLE_EDGE}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_KOGA,
        .trainerPic = TRAINER_PIC_KOGA,
        .bossName = COMPOUND_STRING("Koga"),
        .bossApproachText =  COMPOUND_STRING("Fwahahaha! A fool like you dares to\n"
                                            "challenge me?\p"
                                            "Very well, I shall show you true terror\n"
                                            "as a ninja master!\p"
                                            "Despair as you feel the creeping horror\n"
                                            "of Poison-type Pokemon!$"),
        .bossLoseText =     COMPOUND_STRING("...If I am not strong enough to defeat\n"
                                            "you now, there is but one thing to do.\p"
                                            "I must hone my skills for our next\n"
                                            "encounter.$"),
        .bossAceText =      COMPOUND_STRING("Fwahaha! Prepare yourselves!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_CROBAT,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_SLUDGE_BOMB, MOVE_AERIAL_ACE, MOVE_SHADOW_BALL, MOVE_FACADE}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_CROBAT,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 2,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_CROSS_POISON, MOVE_X_SCISSOR, MOVE_BRAVE_BIRD, MOVE_FACADE}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_CROBAT,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 2,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_CROSS_POISON, MOVE_LEECH_LIFE, MOVE_BRAVE_BIRD, MOVE_FACADE}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_GIOVANNI,
        .trainerPic = TRAINER_PIC_GIOVANNI,
        .bossName = COMPOUND_STRING("Giovanni"),
        .bossApproachText =  COMPOUND_STRING("For your insolence, you will feel a world\n"
                                            "of pain!$"),
        .bossLoseText =     COMPOUND_STRING("I'll tell you this now... No matter how\n"
                                            "strong you are, someday you'll lose.$"),
        .bossAceText =      COMPOUND_STRING("You're in for a world of pain!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MEWTWO,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_ICE_BEAM, MOVE_THUNDERBOLT}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MEWTWO,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 2,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_AURA_SPHERE, MOVE_PSYSTRIKE, MOVE_ICE_BEAM, MOVE_THUNDERBOLT}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MEWTWO,
                            .heldItem = ITEM_MEWTWONITE_Y,
                            .ability = 2,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_AURA_SPHERE, MOVE_PSYSTRIKE, MOVE_ICE_BEAM, MOVE_THUNDERBOLT}
                        },
#endif
   },

   {
        .graphicsId = OBJ_EVENT_GFX_BROCK,
        .trainerPic = TRAINER_PIC_BROCK,
        .bossName = COMPOUND_STRING("Brock"),
        .bossApproachText =  COMPOUND_STRING("My Pokémon are impervious to most\n"
                                            "physical attacks.\p"
                                            "You'll have a hard time inflicting any\n"
                                            "damage!$"),
        .bossLoseText =     COMPOUND_STRING("That was a really great battle!\p"
                                            "I compliment you on your victory!$"),
        .bossAceText =      COMPOUND_STRING("Show me what you got!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(30, 30, 30, 31, 30, 30),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_AERODACTYL,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_ROCK_SLIDE, MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(30, 30, 30, 31, 30, 30),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_AERODACTYL,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_ROCK_SLIDE, MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_AERODACTYL,
                            .heldItem = ITEM_AERODACTYLITE,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_ROCK_SLIDE, MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_DUAL_WINGBEAT}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_AGATHA,
        .trainerPic = TRAINER_PIC_AGATHA,
        .bossName = COMPOUND_STRING("Agatha"),
        .bossApproachText =  COMPOUND_STRING("So you've come! It's not in my character\n"
                                            "to lose.\p"
                                            "Give this battle everything you've got!$"),
        .bossLoseText =     COMPOUND_STRING("Not bad!$"),
        .bossAceText =      COMPOUND_STRING("Put your back into it!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 30, 31, 31, 30, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_GENGAR,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_THUNDERBOLT, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_HIDDEN_POWER}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_GENGAR,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_SLUDGE_BOMB, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_THUNDERBOLT}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_GENGAR,
                            .heldItem = ITEM_GENGARITE,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_SLUDGE_BOMB, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_THUNDERBOLT}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_STEVEN,
        .trainerPic = TRAINER_PIC_STEVEN,
        .bossName = COMPOUND_STRING("Steven"),
        .bossApproachText =  COMPOUND_STRING("What has awoken in you because of your\n"
                                            "journey?\p"
                                            "I want you to hit me with it all! Now\n"
                                            "bring it!!$"),
        .bossLoseText =     COMPOUND_STRING("Congratulations! The feelings you have\n"
                                            "for your Pokémon…\p"
                                            "And the Pokémon that responded to\n"
                                            "those feelings with all their might...\p"
                                            "They came together as one and created\n"
                                            "an even greater power.\p"
                                            "And thus, you were able to grasp\n"
                                            "victory!$"),
        .bossAceText =      COMPOUND_STRING("Steel yourselves!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_METAGROSS,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_METEOR_MASH, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_AERIAL_ACE}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_METAGROSS,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_BULLET_PUNCH, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_ICE_PUNCH}
                        }
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_METAGROSS,
                            .heldItem = ITEM_METAGROSSITE,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_BULLET_PUNCH, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_ICE_PUNCH}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_MAXIE,
        .trainerPic = TRAINER_PIC_MAGMA_LEADER_MAXIE,
        .bossName = COMPOUND_STRING("Maxie"),
        .bossApproachText =  COMPOUND_STRING("Clear out of the way! Don't you dare\n"
                                            "interfere!$"),
        .bossLoseText =     COMPOUND_STRING("You've really done it...\p"
                                            "You've shown a power that exceeds that\n"
                                            "of the great Maxie!$"),
        .bossAceText =      COMPOUND_STRING("I shall educate you!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 4, 0),
                            .lvl = 100,
                            .species = SPECIES_GROUDON,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_NAIVE,
                            .moves = {MOVE_BULK_UP, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_OVERHEAT}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_GROUDON,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_BULK_UP, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_FIRE_PUNCH}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_GROUDON,
                            .heldItem = ITEM_RED_ORB,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_BULK_UP, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE, MOVE_FIRE_PUNCH}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_ARCHIE,
        .trainerPic = TRAINER_PIC_AQUA_LEADER_ARCHIE,
        .bossName = COMPOUND_STRING("Archie"),
        .bossApproachText =  COMPOUND_STRING("I have waited so long for this day to\n"
                                            "come...\p"
                                            "For the realization of my dream, you\n"
                                            "must disappear now!$"),
        .bossLoseText =     COMPOUND_STRING("I commend you. I must recognize that\n"
                                            "you are truly gifted.$"),
        .bossAceText =      COMPOUND_STRING("It's the road's end for you!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_KYOGRE,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_CALM_MIND, MOVE_HYDRO_PUMP, MOVE_THUNDER, MOVE_ICE_BEAM}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_KYOGRE,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_CALM_MIND, MOVE_HYDRO_PUMP, MOVE_THUNDER, MOVE_ICE_BEAM}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_KYOGRE,
                            .heldItem = ITEM_BLUE_ORB,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_CALM_MIND, MOVE_HYDRO_PUMP, MOVE_THUNDER, MOVE_ICE_BEAM}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_ERIKA,
        .trainerPic = TRAINER_PIC_ERIKA,
        .bossName = COMPOUND_STRING("Erika"),
        .bossApproachText =  COMPOUND_STRING("My name is Erika, and I love Grass-type\n"
                                            "Pokemon.\p"
                                            "I have been training myself on not only\n"
                                            "flower arrangement but also battles.\p"
                                            "I shall not lose.$"),
        .bossLoseText =     COMPOUND_STRING("It would make me verry happy if I could\n"
                                            "battle with you again.$"),
        .bossAceText =      COMPOUND_STRING("I shall not lose!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 30, 31, 31, 30),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_VENUSAUR,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_SLUDGE_BOMB, MOVE_EARTHQUAKE, MOVE_HIDDEN_POWER}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 30, 30, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_VENUSAUR,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_SLEEP_POWDER, MOVE_SLUDGE_BOMB, MOVE_ENERGY_BALL, MOVE_HIDDEN_POWER}
                        }
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_VENUSAUR,
                            .heldItem = ITEM_VENUSAURITE,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_SLEEP_POWDER, MOVE_SLUDGE_BOMB, MOVE_GIGA_DRAIN, MOVE_EARTH_POWER}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_WATTSON,
        .trainerPic = TRAINER_PIC_LEADER_WATTSON,
        .bossName = COMPOUND_STRING("Wattson"),
        .bossApproachText =  COMPOUND_STRING("Wahahahaha! Good things come to those\n"
                                            "who laugh!\p"
                                            "I'm going to have a fun Pokemon battle\n"
                                            "and laugh even more!$"),
        .bossLoseText =     COMPOUND_STRING("Wahahahah! That was a great victory!\n"
                                            "I'm so impressed by the way you battle\n"
                                            "that I can't help but laugh!$"),
        .bossAceText =      COMPOUND_STRING("Wahahahah! Now, this is amusing!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(30, 31, 30, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MANECTRIC,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_THUNDERBOLT, MOVE_HIDDEN_POWER, MOVE_CRUNCH, MOVE_DOUBLE_TEAM}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MANECTRIC,
                            .heldItem = ITEM_EXPERT_BELT,
                            .ability = 1,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_THUNDERBOLT, MOVE_FLAMETHROWER, MOVE_SIGNAL_BEAM, MOVE_DOUBLE_TEAM}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_MANECTRIC,
                            .heldItem = ITEM_MANECTITE,
                            .ability = 1,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_THUNDERBOLT, MOVE_FLAMETHROWER, MOVE_SIGNAL_BEAM, MOVE_DOUBLE_TEAM}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_SABRINA,
        .trainerPic = TRAINER_PIC_SABRINA,
        .bossName = COMPOUND_STRING("Sabrina"),
        .bossApproachText =  COMPOUND_STRING("Three years ago I had a vision of\n"
                                            "battling you.\p"
                                            "Since you wish it, I will show you my\n"
                                            "psychic powers!$"),
        .bossLoseText =     COMPOUND_STRING("Your victory... It's exactly as I\n"
                                            "foresaw actually.\p"
                                            "But I wanted to turn that future on its\n"
                                            "head with my conviction as a Trainer!$"),
        .bossAceText =      COMPOUND_STRING("I'll hold nothing back!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_ALAKAZAM,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_PSYCHIC, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_ALAKAZAM,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 2,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_ENERGY_BALL}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 252, 4),
                            .lvl = 100,
                            .species = SPECIES_ALAKAZAM,
                            .heldItem = ITEM_ALAKAZITE,
                            .ability = 2,
                            .nature = NATURE_TIMID,
                            .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_FOCUS_BLAST, MOVE_ENERGY_BALL}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_GLACIA,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_GLACIA,
        .bossName = COMPOUND_STRING("Glacia"),
        .bossApproachText =  COMPOUND_STRING("Welcome, my name is Glacia.\p"
                                            "I've traveled from afar so that I may\n"
                                            "hone my icy skills.\p"
                                            "It would please me to no end if I could\n"
                                            "go all out against you!$"),
        .bossLoseText =     COMPOUND_STRING("You and your Pokemon... How hot your\n"
                                            "spirits burn!\p"
                                            "It's no surprise that my icy skills\n"
                                            "failed to harm you.$"),
        .bossAceText =      COMPOUND_STRING("Careful you don't freeze up!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 30, 30, 31, 30),
                            .ev = TRAINER_PARTY_EVS(252, 0, 4, 0, 252, 0),
                            .lvl = 100,
                            .species = SPECIES_WALREIN,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_ICE_BEAM, MOVE_EARTHQUAKE, MOVE_SURF, MOVE_PROTECT}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 0, 4, 0, 252, 0),
                            .lvl = 100,
                            .species = SPECIES_WALREIN,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_MODEST,
                            .moves = {MOVE_ICE_BEAM, MOVE_EARTHQUAKE, MOVE_SURF, MOVE_PROTECT}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_GLALIE,
                            .heldItem = ITEM_GLALITITE,
                            .ability = 2,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_ICE_SHARD, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_TRAILBLAZE}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_LANCE,
        .trainerPic = TRAINER_PIC_LANCE,
        .bossName = COMPOUND_STRING("Lance"),
        .bossApproachText =  COMPOUND_STRING("There's no need for words now.\p"
                                            "We will battle to determine who is the\n"
                                            "stronger of the two of us.\p"
                                            "I, Lance the Dragon-type master,\n"
                                            "accept your challenge!$"),
        .bossLoseText =     COMPOUND_STRING("I'm sure you already know this, but\n"
                                            "dragons are legendary creatures!\p"
                                            "That's why I won't lose next time!$"),
        .bossAceText =      COMPOUND_STRING("Here we come!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_DRAGONITE,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_AERIAL_ACE}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_DRAGONITE,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 2,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_EXTREME_SPEED, MOVE_EARTHQUAKE, MOVE_AERIAL_ACE}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_DRAGONITE,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 2,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_DRAGON_DANCE, MOVE_EXTREME_SPEED, MOVE_EARTHQUAKE, MOVE_AERIAL_ACE}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_SIDNEY,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_SIDNEY,
        .bossName = COMPOUND_STRING("Sidney"),
        .bossApproachText =  COMPOUND_STRING("Welcome, challenger! Call me Sidney. I\n"
                                            "like that look you're giving me.\p"
                                            "You and me, let's enjoy a battle that\n"
                                            "can only be staged here!$"),
        .bossLoseText =     COMPOUND_STRING("You've got what it takes to go far!\p"
                                            "Now, go on to the next room and enjoy\n"
                                            "your next battle!$"),
        .bossAceText =      COMPOUND_STRING("Don't let up!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 30, 30, 30, 30),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ABSOL,
                            .heldItem = ITEM_CHOICE_BAND,
                            .ability = 0,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_DOUBLE_EDGE, MOVE_QUICK_ATTACK, MOVE_SHADOW_BALL, MOVE_HIDDEN_POWER}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ABSOL,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 1,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_SUCKER_PUNCH, MOVE_SUPERPOWER, MOVE_PURSUIT, MOVE_ROCK_SLIDE}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_ABSOL,
                            .heldItem = ITEM_ABSOLITE,
                            .ability = 1,
                            .nature = NATURE_JOLLY,
                            .moves = {MOVE_SUCKER_PUNCH, MOVE_CLOSE_COMBAT, MOVE_KNOCK_OFF, MOVE_PLAY_ROUGH}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_BUGSY,
        .trainerPic = TRAINER_PIC_BUGSY,
        .bossName = COMPOUND_STRING("Bugsy"),
        .bossApproachText =  COMPOUND_STRING("I never lose when it comes to Bug-type\n"
                                            "Pokémon.\p"
                                            "Let me demonstrate what I've learned\n"
                                            "from my studies.$"),
        .bossLoseText =     COMPOUND_STRING("I never lose when it comes to Bug-type\n"
                                            "Pokémon.\p"
                                            "I'm so embarrassed to have said that.\p"
                                            "I'll start my studies of other Pokémon\n"
                                            "over from the beginning, too.\p"
                                            "I'm truly grateful that you made me\n"
                                            "realize I need to do that.$"),
        .bossAceText =      COMPOUND_STRING("All right, let's do this!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 30, 30, 31, 30),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SCIZOR,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_SILVER_WIND, MOVE_HIDDEN_POWER, MOVE_STEEL_WING}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SCIZOR,
                            .heldItem = ITEM_LIFE_ORB,
                            .ability = 1,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_BULLET_PUNCH, MOVE_KNOCK_OFF, MOVE_AERIAL_ACE}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_SCIZOR,
                            .heldItem = ITEM_SCIZORITE,
                            .ability = 1,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_BULLET_PUNCH, MOVE_KNOCK_OFF, MOVE_TRAILBLAZE}
                        },
#endif
    },

    {
        .graphicsId = OBJ_EVENT_GFX_BRUNO,
        .trainerPic = TRAINER_PIC_BRUNO,
        .bossName = COMPOUND_STRING("Bruno"),
        .bossApproachText =  COMPOUND_STRING("Through rigorous training, people and\n"
                                            "Pokémon can become stronger.\p"
                                            "I've lived and trained with my Fighting\n"
                                            "type Pokémon!\p"
                                            "We will grind you down with our superior\n"
                                            "power! Hoo hah!$"),
        .bossLoseText =     COMPOUND_STRING("If you have defeated me, then my job is\n"
                                            "done. Ugh!\p"
                                            "I may not like it, but... go! Go face your\n"
                                            "next challenge!$"),
        .bossAceText =      COMPOUND_STRING("Take this!\p$"),
#if (GEN_LATEST == GEN_3)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_MACHAMP,
                            .heldItem = ITEM_LEFTOVERS,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_CROSS_CHOP, MOVE_FACADE, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE}
                        },
#elif (GEN_LATEST == GEN_5)
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(252, 252, 0, 0, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_MACHAMP,
                            .heldItem = ITEM_FLAME_ORB,
                            .ability = 0,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_CLOSE_COMBAT, MOVE_FACADE, MOVE_ROCK_SLIDE, MOVE_KNOCK_OFF}
                        },
#else
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(0, 252, 0, 252, 0, 4),
                            .lvl = 100,
                            .species = SPECIES_LUCARIO,
                            .heldItem = ITEM_LUCARIONITE,
                            .ability = 2,
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_CLOSE_COMBAT, MOVE_BULLET_PUNCH, MOVE_EXTREME_SPEED}
                        },
#endif
    },
    
#if (GEN_LATEST == GEN_9)
    {
        .graphicsId = OBJ_EVENT_GFX_VALERIE,
        .trainerPic = TRAINER_PIC_VALERIE,
        .bossName = COMPOUND_STRING("Valerie"),
        .bossApproachText = COMPOUND_STRING("I'm Valerie, a Fairy-type specialist.\p"
                                            "The elusive fairy may appear delicate\n"
                                            "as a bloom, but it is strong.$"),
        .bossLoseText =     COMPOUND_STRING("That was truly a captivating battle.\p"
                                            "I might just be captivated by you.$"),
        .bossAceText =      COMPOUND_STRING("I hope the sun is shining tomorrow.\p$"),
        .trainerAce =   {
                            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
                            .ev = TRAINER_PARTY_EVS(116, 252, 0, 140, 0, 0),
                            .lvl = 100,
                            .species = SPECIES_MAWILE,
                            .heldItem = ITEM_MAWILITE,
                            .ability = 1, //Intimidate
                            .nature = NATURE_ADAMANT,
                            .moves = {MOVE_SWORDS_DANCE, MOVE_PLAY_ROUGH, MOVE_KNOCK_OFF, MOVE_IRON_HEAD}
                        },
    },
#endif
};

u8 *GetBossEncounterFlagPointer(u16 id)
{
    return &gSaveBlock1Ptr->randomBossEncounters[id / 8];
}

u8 BossEncounterFlagSet(u16 id)
{
    u8 *ptr = GetBossEncounterFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 BossEncounterFlagClear(u16 id)
{
    u8 *ptr = GetBossEncounterFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 BossEncounterFlagGet(u16 id)
{
    u8 *ptr = GetBossEncounterFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}

bool8 RemainingBossEncounters(void)
{
    u8 i = 0;
    for(i = 0; i < RANDOM_ENCOUNTER_COUNT; i++)
    {
        if(!BossEncounterFlagGet(i))
            return TRUE;
    }
    return FALSE;
}

void ClearAllRandomBossEncounters(void)
{
    u8 i = 0;
    for(i = 0; i < RANDOM_ENCOUNTER_COUNT; i++)
    {
        BossEncounterFlagClear(i);
    }
}

void SetRandomBossEncounter(void)
{
    bool8 reroll = FALSE;
        
    do {
        u16 index = Random() % RANDOM_BOSS_ENCOUNTER_COUNT;
        //index = RANDOM_BOSS_ENCOUNTER_COUNT - 3; //test
        if(BossEncounterFlagGet(index))
        {
            reroll = TRUE;
        }
        else
        {
            reroll = FALSE;
            BossEncounterFlagSet(index);
            ClearTrainerFlag(TRAINER_RANDOM_PIT_BOSS);
            ClearTrainerFlag(TRAINER_RANDOM_PIT_BOSS_DOUBLES);
            VarSet(VAR_OBJ_GFX_ID_F, sRandomBossEncounterArray[index].graphicsId);
            VarSet(VAR_CURRENT_BOSS, index);
            FlagClear(FLAG_BOSS_ENCOUNTER);
            return;
        }
    } while (reroll);
}

const struct TrainerMon *GetRandomBossEncounterAcePokemon(void)
{
    return &sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].trainerAce;
}

u16 GetRandomBossEncounterTrainerPic(void)
{
    return sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].trainerPic;
}

const u8 *GetRandomBossEncounterBossName(void)
{
    return sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].bossName;
}

const u8 *GetRandomBossEncounterBossApproachText(void)
{
    return sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].bossApproachText;
}

const u8 *GetRandomBossEncounterBossDefeatText(void)
{
    return sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].bossLoseText;
}

const u8 *GetRandomBossEncounterBossAceText(void)
{
    return sRandomBossEncounterArray[VarGet(VAR_CURRENT_BOSS)].bossAceText;
}



//
//  Random GiveMon Floor Reward Encounters Post Boss Fight 
//

const u16 variableGraphicsIdsForEncounters[9] = {VAR_OBJ_GFX_ID_4, VAR_OBJ_GFX_ID_5, VAR_OBJ_GFX_ID_6, VAR_OBJ_GFX_ID_7,
                                            VAR_OBJ_GFX_ID_8, VAR_OBJ_GFX_ID_9, VAR_OBJ_GFX_ID_A, VAR_OBJ_GFX_ID_B, VAR_OBJ_GFX_ID_C};

void DebugPrintAllSpecies(void)
{
    for(u8 i = 0; i < 9; i++)
    {
        DebugPrintf("Species: %d", gSaveBlock1Ptr->wildEncounterFloorSpecies[i]);
    }
}

void SetRandomGiveMonRewardEncounters(void)
{
    bool8 reroll = FALSE;

    for(u8 i = 0; i < 9; i++)
    {
        gSaveBlock1Ptr->wildEncounterFloorSpecies[i] = 0;
    }

    GenerateRandomSpeciesRewards(gSaveBlock1Ptr->wildEncounterFloorSpecies);

    for(u8 i = 0; i < 9; i++)
    {
        VarSet(variableGraphicsIdsForEncounters[i], gSaveBlock1Ptr->wildEncounterFloorSpecies[i] + OBJ_EVENT_GFX_MON_BASE);
    }
}

void GiveRandomMonRewardEncounter(void)
{
    u8 mapGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 mapNum = gSaveBlock1Ptr->location.mapNum;
    u16 species = gSaveBlock1Ptr->wildEncounterFloorSpecies[gSpecialVar_LastTalked - 1];
    u16 level = VarGet(VAR_PIT_FLOOR) <= 100 ? VarGet(VAR_PIT_FLOOR) : 100;
    u8 evs[] = {0, 0, 0, 0, 0, 0};
    u8 ivs[] = {31, 31, 31, 31, 31, 31};
    u16 moves[] = {0, 0, 0, 0};
    gSpecialVar_Result = ScriptGiveMonParameterized(species, level, ITEM_NONE, 0, NUM_NATURES, 3, 0, (u8 *) &evs, (u8 *) &ivs, (u16 *) &moves, 0, NUMBER_OF_MON_TYPES, 0);
}

void BufferNameText_RandomMonRewardEncounter(void)
{
    u16 species = gSaveBlock1Ptr->wildEncounterFloorSpecies[gSpecialVar_LastTalked - 1];

#ifdef POKEMON_EXPANSION
    StringCopy(gStringVar2, GetSpeciesName(species));
#else
    StringCopy(gStringVar2, &gSpeciesNames[species][0]);
#endif
}



//
//  Overworld Trainers Left HUD
//

static void Task_DelayPrintOverworldTrainerHUD(u8 taskId);
static void Task_DelayPrintOverworldMonHUD(u8 taskId);
static void PrintTrainerCount(u32 spriteId, u32 bgColor, u32 startTile);
void MonHUDSpriteCallback(struct Sprite *sprite);

static EWRAM_DATA u8 gOWHUDSprite;
static EWRAM_DATA u8 gOWHUDSpriteMask;
static EWRAM_DATA u8 gOWMonHUDSprite;
static EWRAM_DATA u8 gOWMonHUDSpriteMask;
static const u32 sTrainerCountGfx[] = INCBIN_U32("graphics/interface/trainercount_hud.4bpp.lz");
static const u32 sMonRewardGfx[] = INCBIN_U32("graphics/interface/monreward_hud.4bpp.lz");

static const u16 sTrainerCountPal[] = INCBIN_U16("graphics/interface/trainercount_hud.gbapal");

#define TRAINER_COUNT_PAL_TAG       OBJ_EVENT_PAL_TAG_NPC_4 // Shares the same pal as the trainer it uses
#define TAG_TRAINER_COUNT_GFX       30050
#define TAG_MON_REWARD_GFX          30051

static const struct SpritePalette sSpritePal_TrainerCountHUD =
{
    .data = sTrainerCountPal,
    .tag = TRAINER_COUNT_PAL_TAG,
};

static const struct CompressedSpriteSheet sSpriteSheet_TrainerCountHUD = 
{
    .data = sTrainerCountGfx,
    .size = 32*32*1/2,
    .tag = TAG_TRAINER_COUNT_GFX,
};

static const struct CompressedSpriteSheet sSpriteSheet_MonRewardHUD = 
{
    .data = sMonRewardGfx,
    .size = 16*32*1/2,
    .tag = TAG_MON_REWARD_GFX,
};

static const union AnimCmd sSpriteAnim_TrainerCountHUD0[] =
{
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sSpriteAnimTable_TrainerCountHUD[] =
{
    sSpriteAnim_TrainerCountHUD0,
};

static const struct OamData sOamData_TrainerCountHUD =
{
    .size = SPRITE_SIZE(32x32),
    .shape = SPRITE_SHAPE(32x32),
    .priority = 1,
};

static const struct OamData sOamData_MonRewardHUD =
{
    .size = SPRITE_SIZE(16x32),
    .shape = SPRITE_SHAPE(16x32),
    .priority = 1,
};

static const struct SpriteTemplate sSpriteTemplate_TrainerCountHUD =
{
    .tileTag = TAG_TRAINER_COUNT_GFX,
    .paletteTag = TRAINER_COUNT_PAL_TAG,
    .oam = &sOamData_TrainerCountHUD,
    .anims = sSpriteAnimTable_TrainerCountHUD,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sSpriteTemplate_MonRewardHUD =
{
    .tileTag = TAG_MON_REWARD_GFX,
    .paletteTag = TRAINER_COUNT_PAL_TAG,
    .oam = &sOamData_MonRewardHUD,
    .anims = sSpriteAnimTable_TrainerCountHUD,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = MonHUDSpriteCallback
};


void CreateOverworldTrainerHUD(void)
{
    if(FuncIsActiveTask(Task_DelayPrintOverworldTrainerHUD))
        return;
    u16 remainingTrainers = ReturnTrainersRemaining();
    if ((remainingTrainers == 0) || (VarGet(VAR_PIT_FLOOR) == 0) || ((VarGet(VAR_PIT_FLOOR) % BOSS_FLOOR_RATE) == 0) || ((VarGet(VAR_PIT_FLOOR) % (gSaveBlock2Ptr->modeHealFloors10 ? 10 : 5)) == 0))
        return;
    CreateTask(Task_DelayPrintOverworldTrainerHUD, 15);
}

static void Task_DelayPrintOverworldTrainerHUD(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        LoadCompressedSpriteSheet(&sSpriteSheet_TrainerCountHUD);
        LoadSpritePalette(&sSpritePal_TrainerCountHUD);
        gOWHUDSprite = SPRITE_NONE;
        gOWHUDSprite = CreateSprite(&sSpriteTemplate_TrainerCountHUD, 224, 16, 0);
        gSprites[gOWHUDSprite].invisible = FALSE;

        PrintTrainerCount(gOWHUDSprite, 0, gSprites[gOWHUDSprite].oam.tileNum + 6);

        if (GetFlashLevel() > 0)
        {
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
            SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
            gOWHUDSpriteMask = SPRITE_NONE;
            gOWHUDSpriteMask = CreateSprite(&sSpriteTemplate_TrainerCountHUD, 224, 16, 0);
            gSprites[gOWHUDSpriteMask].invisible = FALSE;
            gSprites[gOWHUDSpriteMask].oam.objMode = ST_OAM_OBJ_WINDOW;
        }
        DestroyTask(taskId);
    }
}


void CreateOverworldMonHUD(void)
{
    if(FuncIsActiveTask(Task_DelayPrintOverworldMonHUD))
        return;
    if ((FlagGet(FLAG_OVERWORLD_MON_ENCOUNTER)) || (VarGet(VAR_PIT_FLOOR) == 0) || ((VarGet(VAR_PIT_FLOOR) % BOSS_FLOOR_RATE) == 0) || ((VarGet(VAR_PIT_FLOOR) % (gSaveBlock2Ptr->modeHealFloors10 ? 10 : 5)) == 0))
        return;
    CreateTask(Task_DelayPrintOverworldMonHUD, 15);
}

static void Task_DelayPrintOverworldMonHUD(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        LoadCompressedSpriteSheet(&sSpriteSheet_MonRewardHUD);
        LoadSpritePalette(&sSpritePal_TrainerCountHUD);
        gOWMonHUDSprite = SPRITE_NONE;
        gOWMonHUDSprite = CreateSprite(&sSpriteTemplate_MonRewardHUD, 14, 14, 0);
        gSprites[gOWMonHUDSprite].invisible = FALSE;

        if (GetFlashLevel() > 0)
        {
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
            SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
            gOWMonHUDSpriteMask = SPRITE_NONE;
            gOWMonHUDSpriteMask = CreateSprite(&sSpriteTemplate_MonRewardHUD, 14, 14, 0);
            gSprites[gOWMonHUDSpriteMask].invisible = FALSE;
            gSprites[gOWMonHUDSpriteMask].oam.objMode = ST_OAM_OBJ_WINDOW;
        }
        DestroyTask(taskId);
    }
}

void MonHUDSpriteCallback(struct Sprite *sprite)
{
    if(FlagGet(FLAG_OVERWORLD_MON_ENCOUNTER) || FlagGet(FLAG_USED_RANDOM_ENCOUNTER_THIS_FLOOR))
    {
        DestroySprite(sprite);
    }
}

static const struct WindowTemplate sTrainerCountWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 2,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 1 + 120
};

static u8 *AddTextPrinterAndCreateWindowOnTrainerCount(const u8 *str, u32 x, u32 y, u32 bgColor, u32 *windowId)
{
    u16 winId;
    u8 color[3];
    struct WindowTemplate winTemplate = sTrainerCountWindowTemplate;

    winId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(winId, PIXEL_FILL(bgColor));

    color[0] = bgColor;
    color[1] = 14;
    color[2] = 15;

    AddTextPrinterParameterized4(winId, FONT_SMALL_NARROW, x, y, 0, 0, color, TEXT_SKIP_DRAW, str);

    *windowId = winId;
    return (u8 *)(GetWindowAttribute(winId, WINDOW_TILE_DATA));
}

static void TextIntoTrainerCountObject(void *dest, u8 *windowTileData, u32 windowWidth)
{
    CpuCopy32(windowTileData, dest, windowWidth * TILE_SIZE_4BPP);
    CpuCopy32(windowTileData + (2 * TILE_SIZE_4BPP), dest + (4 * TILE_SIZE_4BPP), windowWidth * TILE_SIZE_4BPP);
}

static const u8 sText_TrainerCountPrefix[]         = _("x{STR_VAR_3}");
static void PrintTrainerCount(u32 spriteId, u32 bgColor, u32 startTile) // 0xbc0 for one part of the TrainerCount
{
    u8 *windowTileData;
    u32 windowId;

    void *objVram = (void *)(OBJ_VRAM0);
    ConvertIntToDecimalStringN(gStringVar3, ReturnTrainersRemaining(), STR_CONV_MODE_LEFT_ALIGN, 1);
    StringExpandPlaceholders(gStringVar4, sText_TrainerCountPrefix);

    windowTileData = AddTextPrinterAndCreateWindowOnTrainerCount(gStringVar4, 2, 0, bgColor, &windowId);
    TextIntoTrainerCountObject(objVram + (startTile * TILE_SIZE_4BPP), windowTileData, 2);
    RemoveWindow(windowId);
}



//
// 	Auto Save, Modes + Misc Callnatives and Such
//

void InitTrainerIdAndNameData()
{
    u32 trainerId = 0;
    SeedRngWithRtc();
    trainerId = (Random() << 16) | Random();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

void BufferMapFloorString()
{
    ConvertIntToDecimalStringN(gStringVar1, VarGet(VAR_PIT_FLOOR), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void StartNewPokeballCaseUI(void)
{
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_OpenBirchCase, 0);
}

void CallModeMenu(void)
{
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_OpenModeMenu, 0);
}

void AutoSave(void)
{
    ScriptContext_Stop();
    AutoSaveDoSaveCallback();
    FlagSet(FLAG_SAVING_FIELD_EFFECT);
    ScriptContext_Enable();
}

void SetAutosaveFlag(void)
{
    switch(gSaveBlock2Ptr->optionsAutosave)
    {
        case SAVE_NO:
            FlagClear(FLAG_AUTO_SAVE);
            break;
        case SAVE_5_FLOORS:
            if((VarGet(VAR_PIT_FLOOR) % 5) == 0) //every fifth floor
                FlagSet(FLAG_AUTO_SAVE);
            else
                FlagClear(FLAG_AUTO_SAVE);
            break;
        case SAVE_EACH_FLOOR:
            FlagSet(FLAG_AUTO_SAVE);
            break;
    }
    
}

void PlayerPartyCountToResultVar()
{
    VarSet(VAR_RESULT, gPlayerPartyCount);
}

void RemovePartyPokemon(void)
{
    ZeroMonData(&gPlayerParty[VarGet(VAR_RESULT)]);
    CompactPartySlots();
    CalculatePlayerPartyCount();
}

void LevelUpParty(void)
{   
    if(!((gSaveBlock2Ptr->modeXP == 2)))
    {
        FlagClear(FLAG_LEVEL_UP_TWICE);
        FlagClear(FLAG_LEVEL_UP_THRICE);
        return;
    }
        
    if(VarGet(VAR_PIT_FLOOR) <= 5)
    {
        FlagClear(FLAG_LEVEL_UP_TWICE);
        FlagClear(FLAG_LEVEL_UP_THRICE);
        return;
    }

    u8 levels_to_gain = 1;
    if(FlagGet(FLAG_LEVEL_UP_TWICE))
    {
        levels_to_gain = 2;
        FlagClear(FLAG_LEVEL_UP_TWICE);
    }

    if(FlagGet(FLAG_LEVEL_UP_THRICE))
    {
        levels_to_gain = 3;
        FlagClear(FLAG_LEVEL_UP_THRICE);
    }
    
    for(u8 level = 0; level < levels_to_gain; level++)
    {
        u32 i = 0;
        for(i = 0; i < 6; i++)
        {
            struct Pokemon *mon = &gPlayerParty[i];
            ForceIncrementMonLevel(mon);
            MonTryLearningNewMove(mon, TRUE);
        }
    }
    return;
}

void Check3MonMode(void)
{
    if(gSaveBlock2Ptr->mode3MonsOnly == 0)
        VarSet(VAR_TEMP_A, 1);
    else
        VarSet(VAR_TEMP_A, 0);
}

void Check50FloorMode(void)
{
    if(gSaveBlock2Ptr->mode50Floors)
        VarSet(VAR_TEMP_A, 1);
    else
        VarSet(VAR_TEMP_A, 0);
}

void CheckNoCaseMode(void)
{
    if(gSaveBlock2Ptr->modeNoCaseChoice == 0)
        VarSet(VAR_TEMP_A, 1);
    else
        VarSet(VAR_TEMP_A, 0);
}

void CheckNoExpMode(void)
{
    if((gSaveBlock2Ptr->modeXP == 2))
        VarSet(VAR_TEMP_A, 1);
    else
        VarSet(VAR_TEMP_A, 0);
}

void AddInitial3MonsNoCaseMode(void)
{   
    int i = 0;
    if(gPlayerPartyCount == 1)
        i = 1;
    SetRandomGiveMonRewardEncounters();
    for(; i < 3; i++)
    {
        u16 species = gSaveBlock1Ptr->wildEncounterFloorSpecies[i];
        u16 level = 5;
        u8 evs[] = {0, 0, 0, 0, 0, 0};
        u8 ivs[] = {31, 31, 31, 31, 31, 31};
        u16 moves[] = {0, 0, 0, 0};
        ScriptGiveMonParameterized(species, level, ITEM_NONE, 0, NUM_NATURES, 3, 0, (u8 *) &evs, (u8 *) &ivs, (u16 *) &moves, 0, NUMBER_OF_MON_TYPES, 0);
    }
}

void AddNewMonNoCaseMode(void)
{   
    if(gPlayerPartyCount == 6)
        return;
    SetRandomGiveMonRewardEncounters();
    u16 species = gSaveBlock1Ptr->wildEncounterFloorSpecies[0];
    u16 level = VarGet(VAR_PIT_FLOOR) <= 100 ? VarGet(VAR_PIT_FLOOR) : 100;
    u8 evs[] = {0, 0, 0, 0, 0, 0};
    u8 ivs[] = {31, 31, 31, 31, 31, 31};
    u16 moves[] = {0, 0, 0, 0};
    ScriptGiveMonParameterized(species, level, ITEM_NONE, 0, NUM_NATURES, 3, 0, (u8 *) &evs, (u8 *) &ivs, (u16 *) &moves, 0, NUMBER_OF_MON_TYPES, 0);
}

void UpdateRunningStats(void)
{
    gSaveBlock2Ptr->statsAllAttempts++;

    if (VarGet(VAR_PIT_FLOOR) > gSaveBlock2Ptr->statsAllHighscore)
        gSaveBlock2Ptr->statsAllHighscore = VarGet(VAR_PIT_FLOOR);
}

void IncrementStatsRunKOs(void)
{
    gSaveBlock2Ptr->statsRunKOs++;
}

void IncrementStatsRunRevives(void)
{
    gSaveBlock2Ptr->statsRunRevives++;
}

void ResetRunStats(void)
{
    gSaveBlock2Ptr->statsRunKOs = 0;
    gSaveBlock2Ptr->statsRunRevives = 0;
}


void RecieveSilverShield(void)
{
    if(gSaveBlock2Ptr->giveSilverShield == 0)
    {
        if(!CheckHasDecoration(DECOR_SILVER_SHIELD))
        {
            gSaveBlock2Ptr->giveSilverShield = 1;
            return;
        }
    }
}

void RecieveGoldShield(void)
{
    if(gSaveBlock2Ptr->giveGoldShield == 0)
    {
        if(!CheckHasDecoration(DECOR_GOLD_SHIELD))
        {
            gSaveBlock2Ptr->giveGoldShield = 1;
            return;
        }
    }
}

void CheckAndGiveShieldsOnVictory(void)
{
    if(gSaveBlock2Ptr->giveSilverShield)
    {
        if(DecorationCheckSpace(DECOR_SILVER_SHIELD))
        {
            if(!CheckHasDecoration(DECOR_SILVER_SHIELD))
            {
                DecorationAdd(DECOR_SILVER_SHIELD);
                VarSet(VAR_RESULT, 1);
                gSaveBlock2Ptr->giveSilverShield = 0;
                return;
            }
        }
    }
    if(gSaveBlock2Ptr->giveGoldShield)
    {
        if(DecorationCheckSpace(DECOR_GOLD_SHIELD))
        {
            if(!CheckHasDecoration(DECOR_GOLD_SHIELD))
            {
                DecorationAdd(DECOR_GOLD_SHIELD);
                VarSet(VAR_RESULT, 2);
                gSaveBlock2Ptr->giveGoldShield = 0;
                return;
            }
        }
    }
    VarSet(VAR_RESULT, 0);
    return;
}

void CheckIfSavedBefore(void)
{
    if(gSaveBlock2Ptr->hasSavedOnce == 0)
    {
        VarSet(VAR_RESULT, 1);
        gSaveBlock2Ptr->hasSavedOnce = 1;
        return;
    }

    VarSet(VAR_RESULT, 0);
    return;
}

void CheckIfHasRecievedShinyDust(void)
{
    if(gSaveBlock2Ptr->hasRecievedShinyDust == 0)
    {
        VarSet(VAR_RESULT, 1);
        gSaveBlock2Ptr->hasRecievedShinyDust = 1;
        return;
    }

    VarSet(VAR_RESULT, 0);
    return;
}

void CheckAndGiveShinyDust(void)
{
    if(isDexCompleted(FLAG_GET_CAUGHT))
        VarSet(VAR_RESULT, 1);
    else
        VarSet(VAR_RESULT, 0);
    return;
}

void MakePlayerPokemonShiny(void)
{
    u32 shiny = TRUE;
    SetMonData(&gPlayerParty[VarGet(VAR_0x8005)], MON_DATA_IS_SHINY, &shiny);
}

void CheckIfShouldWalkBackwards(void)
{   
    u16 facingDirection = GetPlayerFacingDirection();
    if((facingDirection == DIR_SOUTH) || (facingDirection == DIR_WEST) || (facingDirection == DIR_EAST))
        VarSet(VAR_RESULT, 1);
    else
        VarSet(VAR_RESULT, 0);
    return;
}

void CallRenameScreen()
{
    if(gSaveBlock2Ptr->playerGfxType == AVATAR_POKEMON_CHOICE)
    {
        DoNamingScreen(NAMING_SCREEN_PLAYER_IS_POKEMON, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->pokemonAvatarSpecies, 0, 0, CB2_ReturnToField);  
    }
    else
    {
        DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, 0, CB2_ReturnToField);  
    }
}

void ChooseRandomRewardNumberForFloor(void)
{
    u16 random_val = Random() % 100;

    // fixed item amount setting
    switch(gSaveBlock2Ptr->modeChoiceItemReward)
    {
        case ITEM_DROPS_1: // always 1 reward
            VarSet(VAR_RESULT, 0);
            return;
        case ITEM_DROPS_3: // always 3 rewards
            VarSet(VAR_RESULT, 2);
            return;
    }

    // fallthrough if set to Random
    if(random_val < 10 && !FlagGet(FLAG_DOUBLES_MODE)) // doubles mode shouldn't give single items
    {
        if(VarGet(VAR_PIT_FLOOR) < 5)
            VarSet(VAR_RESULT, 1);
        else
            VarSet(VAR_RESULT, 0);
    }
    else if(random_val < 40)
    {
        VarSet(VAR_RESULT, 1);
    }
    else
    {
        VarSet(VAR_RESULT, 2);
    }
    return;
}

void CheckIfHasReceivedShedinja(void)
{
    if(gSaveBlock2Ptr->hasReceivedShedinja == 0)
    {
        VarSet(VAR_RESULT, 1);
        gSaveBlock2Ptr->hasReceivedShedinja = 1;
        return;
    }

    VarSet(VAR_RESULT, 0);
    return;
}

void CheckAndGiveShedinja(void)
{
    if(isDexCompleted(FLAG_GET_SEEN))
        VarSet(VAR_RESULT, 1);
    else
        VarSet(VAR_RESULT, 0);
    return;
}

void CheckIfShouldSkipBossHeal(void)
{
    if(gSaveBlock2Ptr->modeBossHeal == OPTIONS_ON)
        VarSet(VAR_RESULT, 0);
    else
        VarSet(VAR_RESULT, 1);
    return;
}
