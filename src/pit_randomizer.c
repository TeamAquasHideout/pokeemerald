#include "global.h"
#include "malloc.h"
#include "apprentice.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_z_move.h"
#include "bw_summary_screen.h"
#include "data.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "evolution_scene.h"
#include "field_specials.h"
#include "field_weather.h"
#include "graphics.h"
#include "item.h"
#include "level_caps.h"
#include "link.h"
#include "main.h"
#include "overworld.h"
#include "m4a.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "pokemon_animation.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "recorded_battle.h"
#include "rtc.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "trainer_hill.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_frontier.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_partner.h"
#include "constants/cries.h"
#include "constants/event_objects.h"
#include "constants/form_change_types.h"
#include "constants/hold_effects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/union_room.h"
#include "constants/weather.h"
#include "tx_randomizer_and_challenges.h"
#include "daycare.h"
#include "config/general.h"
#include "field_screen_effect.h"
#include "script.h"
#include "pit.h"
#include "wild_encounter.h"
#include "script_pokemon_util.h"


//
//		Random Pokemon
//

//*********************** //tx_randomizer_and_challenges
#define RANDOM_SPECIES_COUNT_LEGENDARY ARRAY_COUNT(sRandomSpeciesLegendary)
static const u16 sRandomSpeciesLegendary[] =
{
    //SPECIES_NONE                    ,
    SPECIES_BULBASAUR               ,
    SPECIES_IVYSAUR                 ,
    SPECIES_VENUSAUR                ,
    SPECIES_CHARMANDER              ,
    SPECIES_CHARMELEON              ,
    SPECIES_CHARIZARD               ,
    SPECIES_SQUIRTLE                ,
    SPECIES_WARTORTLE               ,
    SPECIES_BLASTOISE               ,
    SPECIES_CATERPIE                ,
    SPECIES_METAPOD                 ,
    SPECIES_BUTTERFREE              ,
    SPECIES_WEEDLE                  ,
    SPECIES_KAKUNA                  ,
    SPECIES_BEEDRILL                ,
    SPECIES_PIDGEY                  ,
    SPECIES_PIDGEOTTO               ,
    SPECIES_PIDGEOT                 ,
    SPECIES_RATTATA                 ,
    SPECIES_RATICATE                ,
    SPECIES_SPEAROW                 ,
    SPECIES_FEAROW                  ,
    SPECIES_EKANS                   ,
    SPECIES_ARBOK                   ,
    SPECIES_PIKACHU                 ,
    SPECIES_RAICHU                  ,
    SPECIES_SANDSHREW               ,
    SPECIES_SANDSLASH               ,
    SPECIES_NIDORAN_F               ,
    SPECIES_NIDORINA                ,
    SPECIES_NIDOQUEEN               ,
    SPECIES_NIDORAN_M               ,
    SPECIES_NIDORINO                ,
    SPECIES_NIDOKING                ,
    SPECIES_CLEFAIRY                ,
    SPECIES_CLEFABLE                ,
    SPECIES_VULPIX                  ,
    SPECIES_NINETALES               ,
    SPECIES_JIGGLYPUFF              ,
    SPECIES_WIGGLYTUFF              ,
    SPECIES_ZUBAT                   ,
    SPECIES_GOLBAT                  ,
    SPECIES_ODDISH                  ,
    SPECIES_GLOOM                   ,
    SPECIES_VILEPLUME               ,
    SPECIES_PARAS                   ,
    SPECIES_PARASECT                ,
    SPECIES_VENONAT                 ,
    SPECIES_VENOMOTH                ,
    SPECIES_DIGLETT                 ,
    SPECIES_DUGTRIO                 ,
    SPECIES_MEOWTH                  ,
    SPECIES_PERSIAN                 ,
    SPECIES_PSYDUCK                 ,
    SPECIES_GOLDUCK                 ,
    SPECIES_MANKEY                  ,
    SPECIES_PRIMEAPE                ,
    SPECIES_GROWLITHE               ,
    SPECIES_ARCANINE                ,
    SPECIES_POLIWAG                 ,
    SPECIES_POLIWHIRL               ,
    SPECIES_POLIWRATH               ,
    SPECIES_ABRA                    ,
    SPECIES_KADABRA                 ,
    SPECIES_ALAKAZAM                ,
    SPECIES_MACHOP                  ,
    SPECIES_MACHOKE                 ,
    SPECIES_MACHAMP                 ,
    SPECIES_BELLSPROUT              ,
    SPECIES_WEEPINBELL              ,
    SPECIES_VICTREEBEL              ,
    SPECIES_TENTACOOL               ,
    SPECIES_TENTACRUEL              ,
    SPECIES_GEODUDE                 ,
    SPECIES_GRAVELER                ,
    SPECIES_GOLEM                   ,
    SPECIES_PONYTA                  ,
    SPECIES_RAPIDASH                ,
    SPECIES_SLOWPOKE                ,
    SPECIES_SLOWBRO                 ,
    SPECIES_MAGNEMITE               ,
    SPECIES_MAGNETON                ,
    SPECIES_FARFETCHD               ,
    SPECIES_DODUO                   ,
    SPECIES_DODRIO                  ,
    SPECIES_SEEL                    ,
    SPECIES_DEWGONG                 ,
    SPECIES_GRIMER                  ,
    SPECIES_MUK                     ,
    SPECIES_SHELLDER                ,
    SPECIES_CLOYSTER                ,
    SPECIES_GASTLY                  ,
    SPECIES_HAUNTER                 ,
    SPECIES_GENGAR                  ,
    SPECIES_ONIX                    ,
    SPECIES_DROWZEE                 ,
    SPECIES_HYPNO                   ,
    SPECIES_KRABBY                  ,
    SPECIES_KINGLER                 ,
    SPECIES_VOLTORB                 ,
    SPECIES_ELECTRODE               ,
    SPECIES_EXEGGCUTE               ,
    SPECIES_EXEGGUTOR               ,
    SPECIES_CUBONE                  ,
    SPECIES_MAROWAK                 ,
    SPECIES_HITMONLEE               ,
    SPECIES_HITMONCHAN              ,
    SPECIES_LICKITUNG               ,
    SPECIES_KOFFING                 ,
    SPECIES_WEEZING                 ,
    SPECIES_RHYHORN                 ,
    SPECIES_RHYDON                  ,
    SPECIES_CHANSEY                 ,
    SPECIES_TANGELA                 ,
    SPECIES_KANGASKHAN              ,
    SPECIES_HORSEA                  ,
    SPECIES_SEADRA                  ,
    SPECIES_GOLDEEN                 ,
    SPECIES_SEAKING                 ,
    SPECIES_STARYU                  ,
    SPECIES_STARMIE                 ,
    SPECIES_MR_MIME                 ,
    SPECIES_SCYTHER                 ,
    SPECIES_JYNX                    ,
    SPECIES_ELECTABUZZ              ,
    SPECIES_MAGMAR                  ,
    SPECIES_PINSIR                  ,
    SPECIES_TAUROS                  ,
    SPECIES_MAGIKARP                ,
    SPECIES_GYARADOS                ,
    SPECIES_LAPRAS                  ,
    SPECIES_DITTO                   ,
    SPECIES_EEVEE                   ,
    SPECIES_VAPOREON                ,
    SPECIES_JOLTEON                 ,
    SPECIES_FLAREON                 ,
    SPECIES_PORYGON                 ,
    SPECIES_OMANYTE                 ,
    SPECIES_OMASTAR                 ,
    SPECIES_KABUTO                  ,
    SPECIES_KABUTOPS                ,
    SPECIES_AERODACTYL              ,
    SPECIES_SNORLAX                 ,
    SPECIES_ARTICUNO                ,
    SPECIES_ZAPDOS                  ,
    SPECIES_MOLTRES                 ,
    SPECIES_DRATINI                 ,
    SPECIES_DRAGONAIR               ,
    SPECIES_DRAGONITE               ,
    SPECIES_MEWTWO                  ,
    SPECIES_MEW                     ,
    SPECIES_CHIKORITA                  ,
    SPECIES_BAYLEEF                    ,
    SPECIES_MEGANIUM                   ,
    SPECIES_CYNDAQUIL                  ,
    SPECIES_QUILAVA                    ,
    SPECIES_TYPHLOSION                 ,
    SPECIES_TOTODILE                   ,
    SPECIES_CROCONAW                   ,
    SPECIES_FERALIGATR                 ,
    SPECIES_SENTRET                    ,
    SPECIES_FURRET                     ,
    SPECIES_HOOTHOOT                   ,
    SPECIES_NOCTOWL                    ,
    SPECIES_LEDYBA                     ,
    SPECIES_LEDIAN                     ,
    SPECIES_SPINARAK                   ,
    SPECIES_ARIADOS                    ,
    SPECIES_CROBAT                     ,
    SPECIES_CHINCHOU                   ,
    SPECIES_LANTURN                    ,
    SPECIES_PICHU                      ,
    SPECIES_CLEFFA                     ,
    SPECIES_IGGLYBUFF                  ,
    SPECIES_TOGEPI                     ,
    SPECIES_TOGETIC                    ,
    SPECIES_NATU                       ,
    SPECIES_XATU                       ,
    SPECIES_MAREEP                     ,
    SPECIES_FLAAFFY                    ,
    SPECIES_AMPHAROS                   ,
    SPECIES_BELLOSSOM                  ,
    SPECIES_MARILL                     ,
    SPECIES_AZUMARILL                  ,
    SPECIES_SUDOWOODO                  ,
    SPECIES_POLITOED                   ,
    SPECIES_HOPPIP                     ,
    SPECIES_SKIPLOOM                   ,
    SPECIES_JUMPLUFF                   ,
    SPECIES_AIPOM                      ,
    SPECIES_SUNKERN                    ,
    SPECIES_SUNFLORA                   ,
    SPECIES_YANMA                      ,
    SPECIES_WOOPER                     ,
    SPECIES_QUAGSIRE                   ,
    SPECIES_ESPEON                     ,
    SPECIES_UMBREON                    ,
    SPECIES_MURKROW                    ,
    SPECIES_SLOWKING                   ,
    SPECIES_MISDREAVUS                 ,
    SPECIES_UNOWN                      ,
    SPECIES_WOBBUFFET                  ,
    SPECIES_GIRAFARIG                  ,
    SPECIES_PINECO                     ,
    SPECIES_FORRETRESS                 ,
    SPECIES_DUNSPARCE                  ,
    SPECIES_GLIGAR                     ,
    SPECIES_STEELIX                    ,
    SPECIES_SNUBBULL                   ,
    SPECIES_GRANBULL                   ,
    SPECIES_QWILFISH                   ,
    SPECIES_SCIZOR                     ,
    SPECIES_SHUCKLE                    ,
    SPECIES_HERACROSS                  ,
    SPECIES_SNEASEL                    ,
    SPECIES_TEDDIURSA                  ,
    SPECIES_URSARING                   ,
    SPECIES_SLUGMA                     ,
    SPECIES_MAGCARGO                   ,
    SPECIES_SWINUB                     ,
    SPECIES_PILOSWINE                  ,
    SPECIES_CORSOLA                    ,
    SPECIES_REMORAID                   ,
    SPECIES_OCTILLERY                  ,
    SPECIES_DELIBIRD                   ,
    SPECIES_MANTINE                    ,
    SPECIES_SKARMORY                   ,
    SPECIES_HOUNDOUR                   ,
    SPECIES_HOUNDOOM                   ,
    SPECIES_KINGDRA                    ,
    SPECIES_PHANPY                     ,
    SPECIES_DONPHAN                    ,
    SPECIES_PORYGON2                   ,
    SPECIES_STANTLER                   ,
    SPECIES_SMEARGLE                   ,
    SPECIES_TYROGUE                    ,
    SPECIES_HITMONTOP                  ,
    SPECIES_SMOOCHUM                   ,
    SPECIES_ELEKID                     ,
    SPECIES_MAGBY                      ,
    SPECIES_MILTANK                    ,
    SPECIES_BLISSEY                    ,
    SPECIES_RAIKOU                     ,
    SPECIES_ENTEI                      ,
    SPECIES_SUICUNE                    ,
    SPECIES_LARVITAR                   ,
    SPECIES_PUPITAR                    ,
    SPECIES_TYRANITAR                  ,
    SPECIES_LUGIA                      ,
    SPECIES_HO_OH                      ,
    SPECIES_CELEBI                     ,
    SPECIES_TREECKO           ,
    SPECIES_GROVYLE           ,
    SPECIES_SCEPTILE          ,
    SPECIES_TORCHIC           ,
    SPECIES_COMBUSKEN         ,
    SPECIES_BLAZIKEN          ,
    SPECIES_MUDKIP            ,
    SPECIES_MARSHTOMP         ,
    SPECIES_SWAMPERT          ,
    SPECIES_POOCHYENA         ,
    SPECIES_MIGHTYENA         ,
    SPECIES_ZIGZAGOON         ,
    SPECIES_LINOONE           ,
    SPECIES_WURMPLE           ,
    SPECIES_SILCOON           ,
    SPECIES_BEAUTIFLY         ,
    SPECIES_CASCOON           ,
    SPECIES_DUSTOX            ,
    SPECIES_LOTAD             ,
    SPECIES_LOMBRE            ,
    SPECIES_LUDICOLO          ,
    SPECIES_SEEDOT            ,
    SPECIES_NUZLEAF           ,
    SPECIES_SHIFTRY           ,
    SPECIES_NINCADA           ,
    SPECIES_NINJASK           ,
    // SPECIES_SHEDINJA          ,
    SPECIES_TAILLOW           ,
    SPECIES_SWELLOW           ,
    SPECIES_SHROOMISH         ,
    SPECIES_BRELOOM           ,
    SPECIES_SPINDA            ,
    SPECIES_WINGULL           ,
    SPECIES_PELIPPER          ,
    SPECIES_SURSKIT           ,
    SPECIES_MASQUERAIN        ,
    SPECIES_WAILMER           ,
    SPECIES_WAILORD           ,
    SPECIES_SKITTY            ,
    SPECIES_DELCATTY          ,
    SPECIES_KECLEON           ,
    SPECIES_BALTOY            ,
    SPECIES_CLAYDOL           ,
    SPECIES_NOSEPASS          ,
    SPECIES_TORKOAL           ,
    SPECIES_SABLEYE           ,
    SPECIES_BARBOACH          ,
    SPECIES_WHISCASH          ,
    SPECIES_LUVDISC           ,
    SPECIES_CORPHISH          ,
    SPECIES_CRAWDAUNT         ,
    SPECIES_FEEBAS            ,
    SPECIES_MILOTIC           ,
    SPECIES_CARVANHA          ,
    SPECIES_SHARPEDO          ,
    SPECIES_TRAPINCH          ,
    SPECIES_VIBRAVA           ,
    SPECIES_FLYGON            ,
    SPECIES_MAKUHITA          ,
    SPECIES_HARIYAMA          ,
    SPECIES_ELECTRIKE         ,
    SPECIES_MANECTRIC         ,
    SPECIES_NUMEL             ,
    SPECIES_CAMERUPT          ,
    SPECIES_SPHEAL            ,
    SPECIES_SEALEO            ,
    SPECIES_WALREIN           ,
    SPECIES_CACNEA            ,
    SPECIES_CACTURNE          ,
    SPECIES_SNORUNT           ,
    SPECIES_GLALIE            ,
    SPECIES_LUNATONE          ,
    SPECIES_SOLROCK           ,
    SPECIES_AZURILL           ,
    SPECIES_SPOINK            ,
    SPECIES_GRUMPIG           ,
    SPECIES_PLUSLE            ,
    SPECIES_MINUN             ,
    SPECIES_MAWILE            ,
    SPECIES_MEDITITE          ,
    SPECIES_MEDICHAM          ,
    SPECIES_SWABLU            ,
    SPECIES_ALTARIA           ,
    SPECIES_WYNAUT            ,
    SPECIES_DUSKULL           ,
    SPECIES_DUSCLOPS          ,
    SPECIES_ROSELIA           ,
    SPECIES_SLAKOTH           ,
    SPECIES_VIGOROTH          ,
    SPECIES_SLAKING           ,
    SPECIES_GULPIN            ,
    SPECIES_SWALOT            ,
    SPECIES_TROPIUS           ,
    SPECIES_WHISMUR           ,
    SPECIES_LOUDRED           ,
    SPECIES_EXPLOUD           ,
    SPECIES_CLAMPERL          ,
    SPECIES_HUNTAIL           ,
    SPECIES_GOREBYSS          ,
    SPECIES_ABSOL             ,
    SPECIES_SHUPPET           ,
    SPECIES_BANETTE           ,
    SPECIES_SEVIPER           ,
    SPECIES_ZANGOOSE          ,
    SPECIES_RELICANTH         ,
    SPECIES_ARON              ,
    SPECIES_LAIRON            ,
    SPECIES_AGGRON            ,
    // SPECIES_CASTFORM          ,
    SPECIES_VOLBEAT           ,
    SPECIES_ILLUMISE          ,
    SPECIES_LILEEP            ,
    SPECIES_CRADILY           ,
    SPECIES_ANORITH           ,
    SPECIES_ARMALDO           ,
    SPECIES_RALTS             ,
    SPECIES_KIRLIA            ,
    SPECIES_GARDEVOIR         ,
    SPECIES_BAGON             ,
    SPECIES_SHELGON           ,
    SPECIES_SALAMENCE         ,
    SPECIES_BELDUM            ,
    SPECIES_METANG            ,
    SPECIES_METAGROSS         ,
    SPECIES_REGIROCK          ,
    SPECIES_REGICE            ,
    SPECIES_REGISTEEL         ,
    SPECIES_KYOGRE            ,
    SPECIES_GROUDON           ,
    SPECIES_RAYQUAZA          ,
    SPECIES_LATIAS            ,
    SPECIES_LATIOS            ,
    SPECIES_JIRACHI           ,
    SPECIES_DEOXYS            ,
    SPECIES_CHIMECHO          ,
#ifdef PIT_GEN_5_MODE
    SPECIES_TURTWIG           ,
    SPECIES_GROTLE            ,
    SPECIES_TORTERRA          ,
    SPECIES_CHIMCHAR          ,
    SPECIES_MONFERNO          ,
    SPECIES_INFERNAPE         ,
    SPECIES_PIPLUP            ,
    SPECIES_PRINPLUP          ,
    SPECIES_EMPOLEON          ,
    SPECIES_STARLY            ,
    SPECIES_STARAVIA          ,
    SPECIES_STARAPTOR         ,
    SPECIES_BIDOOF            ,
    SPECIES_BIBAREL           ,
    SPECIES_KRICKETOT         ,
    SPECIES_KRICKETUNE        ,
    SPECIES_SHINX             ,
    SPECIES_LUXIO             ,
    SPECIES_LUXRAY            ,
    SPECIES_BUDEW             ,
    SPECIES_ROSERADE          ,
    SPECIES_CRANIDOS          ,
    SPECIES_RAMPARDOS         ,
    SPECIES_SHIELDON          ,
    SPECIES_BASTIODON         ,
    SPECIES_BURMY             ,
    SPECIES_WORMADAM          ,
    SPECIES_MOTHIM            ,
    SPECIES_COMBEE            ,
    SPECIES_VESPIQUEN         ,
    SPECIES_PACHIRISU         ,
    SPECIES_BUIZEL            ,
    SPECIES_FLOATZEL          ,
    SPECIES_CHERUBI           ,
    SPECIES_CHERRIM           ,
    SPECIES_SHELLOS           ,
    SPECIES_GASTRODON         ,
    SPECIES_AMBIPOM           ,
    SPECIES_DRIFLOON          ,
    SPECIES_DRIFBLIM          ,
    SPECIES_BUNEARY           ,
    SPECIES_LOPUNNY           ,
    SPECIES_MISMAGIUS         ,
    SPECIES_HONCHKROW         ,
    SPECIES_GLAMEOW           ,
    SPECIES_PURUGLY           ,
    SPECIES_CHINGLING         ,
    SPECIES_STUNKY            ,
    SPECIES_SKUNTANK          ,
    SPECIES_BRONZOR           ,
    SPECIES_BRONZONG          ,
    SPECIES_BONSLY            ,
    SPECIES_MIME_JR           ,
    SPECIES_HAPPINY           ,
    SPECIES_CHATOT            ,
    SPECIES_SPIRITOMB         ,
    SPECIES_GIBLE             ,
    SPECIES_GABITE            ,
    SPECIES_GARCHOMP          ,
    SPECIES_MUNCHLAX          ,
    SPECIES_RIOLU             ,
    SPECIES_LUCARIO           ,
    SPECIES_HIPPOPOTAS        ,
    SPECIES_HIPPOWDON         ,
    SPECIES_SKORUPI           ,
    SPECIES_DRAPION           ,
    SPECIES_CROAGUNK          ,
    SPECIES_TOXICROAK         ,
    SPECIES_CARNIVINE         ,
    SPECIES_FINNEON           ,
    SPECIES_LUMINEON          ,
    SPECIES_MANTYKE           ,
    SPECIES_SNOVER            ,
    SPECIES_ABOMASNOW         ,
    SPECIES_WEAVILE           ,
    SPECIES_MAGNEZONE         ,
    SPECIES_LICKILICKY        ,
    SPECIES_RHYPERIOR         ,
    SPECIES_TANGROWTH         ,
    SPECIES_ELECTIVIRE        ,
    SPECIES_MAGMORTAR         ,
    SPECIES_TOGEKISS          ,
    SPECIES_YANMEGA           ,
    SPECIES_LEAFEON           ,
    SPECIES_GLACEON           ,
    SPECIES_GLISCOR           ,
    SPECIES_MAMOSWINE         ,
    SPECIES_PORYGON_Z         ,
    SPECIES_GALLADE           ,
    SPECIES_PROBOPASS         ,
    SPECIES_DUSKNOIR          ,
    SPECIES_FROSLASS          ,
    SPECIES_ROTOM             ,
    SPECIES_UXIE              ,
    SPECIES_MESPRIT           ,
    SPECIES_AZELF             ,
    SPECIES_DIALGA            ,
    SPECIES_PALKIA            ,
    SPECIES_HEATRAN           ,
    SPECIES_REGIGIGAS         ,
    SPECIES_GIRATINA          ,
    SPECIES_CRESSELIA         ,
    SPECIES_PHIONE            ,
    SPECIES_MANAPHY           ,
    SPECIES_DARKRAI           ,
    SPECIES_SHAYMIN           ,
    SPECIES_ARCEUS            ,
    SPECIES_VICTINI           ,
    SPECIES_SNIVY             ,
    SPECIES_SERVINE           ,
    SPECIES_SERPERIOR         ,
    SPECIES_TEPIG             ,
    SPECIES_PIGNITE           ,
    SPECIES_EMBOAR            ,
    SPECIES_OSHAWOTT          ,
    SPECIES_DEWOTT            ,
    SPECIES_SAMUROTT          ,
    SPECIES_PATRAT            ,
    SPECIES_WATCHOG           ,
    SPECIES_LILLIPUP          ,
    SPECIES_HERDIER           ,
    SPECIES_STOUTLAND         ,
    SPECIES_PURRLOIN          ,
    SPECIES_LIEPARD           ,
    SPECIES_PANSAGE           ,
    SPECIES_SIMISAGE          ,
    SPECIES_PANSEAR           ,
    SPECIES_SIMISEAR          ,
    SPECIES_PANPOUR           ,
    SPECIES_SIMIPOUR          ,
    SPECIES_MUNNA             ,
    SPECIES_MUSHARNA          ,
    SPECIES_PIDOVE            ,
    SPECIES_TRANQUILL         ,
    SPECIES_UNFEZANT          ,
    SPECIES_BLITZLE           ,
    SPECIES_ZEBSTRIKA         ,
    SPECIES_ROGGENROLA        ,
    SPECIES_BOLDORE           ,
    SPECIES_GIGALITH          ,
    SPECIES_WOOBAT            ,
    SPECIES_SWOOBAT           ,
    SPECIES_DRILBUR           ,
    SPECIES_EXCADRILL         ,
    SPECIES_AUDINO            ,
    SPECIES_TIMBURR           ,
    SPECIES_GURDURR           ,
    SPECIES_CONKELDURR        ,
    SPECIES_TYMPOLE           ,
    SPECIES_PALPITOAD         ,
    SPECIES_SEISMITOAD        ,
    SPECIES_THROH             ,
    SPECIES_SAWK              ,
    SPECIES_SEWADDLE          ,
    SPECIES_SWADLOON          ,
    SPECIES_LEAVANNY          ,
    SPECIES_VENIPEDE          ,
    SPECIES_WHIRLIPEDE        ,
    SPECIES_SCOLIPEDE         ,
    SPECIES_COTTONEE          ,
    SPECIES_WHIMSICOTT        ,
    SPECIES_PETILIL           ,
    SPECIES_LILLIGANT         ,
    SPECIES_BASCULIN          ,
    SPECIES_SANDILE           ,
    SPECIES_KROKOROK          ,
    SPECIES_KROOKODILE        ,
    SPECIES_DARUMAKA          ,
    SPECIES_DARMANITAN        ,
    SPECIES_MARACTUS          ,
    SPECIES_DWEBBLE           ,
    SPECIES_CRUSTLE           ,
    SPECIES_SCRAGGY           ,
    SPECIES_SCRAFTY           ,
    SPECIES_SIGILYPH          ,
    SPECIES_YAMASK            ,
    SPECIES_COFAGRIGUS        ,
    SPECIES_TIRTOUGA          ,
    SPECIES_CARRACOSTA        ,
    SPECIES_ARCHEN            ,
    SPECIES_ARCHEOPS          ,
    SPECIES_TRUBBISH          ,
    SPECIES_GARBODOR          ,
    SPECIES_ZORUA             ,
    SPECIES_ZOROARK           ,
    SPECIES_MINCCINO          ,
    SPECIES_CINCCINO          ,
    SPECIES_GOTHITA           ,
    SPECIES_GOTHORITA         ,
    SPECIES_GOTHITELLE        ,
    SPECIES_SOLOSIS           ,
    SPECIES_DUOSION           ,
    SPECIES_REUNICLUS         ,
    SPECIES_DUCKLETT          ,
    SPECIES_SWANNA            ,
    SPECIES_VANILLITE         ,
    SPECIES_VANILLISH         ,
    SPECIES_VANILLUXE         ,
    SPECIES_DEERLING          ,
    SPECIES_SAWSBUCK          ,
    SPECIES_EMOLGA            ,
    SPECIES_KARRABLAST        ,
    SPECIES_ESCAVALIER        ,
    SPECIES_FOONGUS           ,
    SPECIES_AMOONGUSS         ,
    SPECIES_FRILLISH          ,
    SPECIES_JELLICENT         ,
    SPECIES_ALOMOMOLA         ,
    SPECIES_JOLTIK            ,
    SPECIES_GALVANTULA        ,
    SPECIES_FERROSEED         ,
    SPECIES_FERROTHORN        ,
    SPECIES_KLINK             ,
    SPECIES_KLANG             ,
    SPECIES_KLINKLANG         ,
    SPECIES_TYNAMO            ,
    SPECIES_EELEKTRIK         ,
    SPECIES_EELEKTROSS        ,
    SPECIES_ELGYEM            ,
    SPECIES_BEHEEYEM          ,
    SPECIES_LITWICK           ,
    SPECIES_LAMPENT           ,
    SPECIES_CHANDELURE        ,
    SPECIES_AXEW              ,
    SPECIES_FRAXURE           ,
    SPECIES_HAXORUS           ,
    SPECIES_CUBCHOO           ,
    SPECIES_BEARTIC           ,
    SPECIES_CRYOGONAL         ,
    SPECIES_SHELMET           ,
    SPECIES_ACCELGOR          ,
    SPECIES_STUNFISK          ,
    SPECIES_MIENFOO           ,
    SPECIES_MIENSHAO          ,
    SPECIES_DRUDDIGON         ,
    SPECIES_GOLETT            ,
    SPECIES_GOLURK            ,
    SPECIES_PAWNIARD          ,
    SPECIES_BISHARP           ,
    SPECIES_BOUFFALANT        ,
    SPECIES_RUFFLET           ,
    SPECIES_BRAVIARY          ,
    SPECIES_VULLABY           ,
    SPECIES_MANDIBUZZ         ,
    SPECIES_HEATMOR           ,
    SPECIES_DURANT            ,
    SPECIES_DEINO             ,
    SPECIES_ZWEILOUS          ,
    SPECIES_HYDREIGON         ,
    SPECIES_LARVESTA          ,
    SPECIES_VOLCARONA         ,
    SPECIES_COBALION          ,
    SPECIES_TERRAKION         ,
    SPECIES_VIRIZION          ,
    SPECIES_TORNADUS          ,
    SPECIES_THUNDURUS         ,
    SPECIES_RESHIRAM          ,
    SPECIES_ZEKROM            ,
    SPECIES_LANDORUS          ,
    SPECIES_KYUREM            ,
    SPECIES_KELDEO            ,
    SPECIES_MELOETTA          ,
    SPECIES_GENESECT          ,
#endif
#if GEN_LATEST > 5
    SPECIES_CHESPIN           ,
    SPECIES_QUILLADIN         ,
    SPECIES_CHESNAUGHT        ,
    SPECIES_FENNEKIN          ,
    SPECIES_BRAIXEN           ,
    SPECIES_DELPHOX           ,
    SPECIES_FROAKIE           ,
    SPECIES_FROGADIER         ,
    SPECIES_GRENINJA          ,
    SPECIES_BUNNELBY          ,
    SPECIES_DIGGERSBY         ,
    SPECIES_FLETCHLING        ,
    SPECIES_FLETCHINDER       ,
    SPECIES_TALONFLAME        ,
    SPECIES_SCATTERBUG        ,
    SPECIES_SPEWPA            ,
    SPECIES_VIVILLON          ,
    SPECIES_LITLEO            ,
    SPECIES_PYROAR            ,
    SPECIES_FLABEBE           ,
    SPECIES_FLOETTE           ,
    SPECIES_FLORGES           ,
    SPECIES_SKIDDO            ,
    SPECIES_GOGOAT            ,
    SPECIES_PANCHAM           ,
    SPECIES_PANGORO           ,
    SPECIES_FURFROU           ,
    SPECIES_ESPURR            ,
    SPECIES_MEOWSTIC          ,
    SPECIES_HONEDGE           ,
    SPECIES_DOUBLADE          ,
    SPECIES_AEGISLASH         ,
    SPECIES_SPRITZEE          ,
    SPECIES_AROMATISSE        ,
    SPECIES_SWIRLIX           ,
    SPECIES_SLURPUFF          ,
    SPECIES_INKAY             ,
    SPECIES_MALAMAR           ,
    SPECIES_BINACLE           ,
    SPECIES_BARBARACLE        ,
    SPECIES_SKRELP            ,
    SPECIES_DRAGALGE          ,
    SPECIES_CLAUNCHER         ,
    SPECIES_CLAWITZER         ,
    SPECIES_HELIOPTILE        ,
    SPECIES_HELIOLISK         ,
    SPECIES_TYRUNT            ,
    SPECIES_TYRANTRUM         ,
    SPECIES_AMAURA            ,
    SPECIES_AURORUS           ,
    SPECIES_SYLVEON           ,
    SPECIES_HAWLUCHA          ,
    SPECIES_DEDENNE           ,
    SPECIES_CARBINK           ,
    SPECIES_GOOMY             ,
    SPECIES_SLIGGOO           ,
    SPECIES_GOODRA            ,
    SPECIES_KLEFKI            ,
    SPECIES_PHANTUMP          ,
    SPECIES_TREVENANT         ,
    SPECIES_PUMPKABOO         ,
    SPECIES_GOURGEIST         ,
    SPECIES_BERGMITE          ,
    SPECIES_AVALUGG           ,
    SPECIES_NOIBAT            ,
    SPECIES_NOIVERN           ,
    SPECIES_XERNEAS           ,
    SPECIES_YVELTAL           ,
    SPECIES_ZYGARDE           ,
    SPECIES_DIANCIE           ,
    SPECIES_HOOPA             ,
    SPECIES_VOLCANION         ,
    SPECIES_ROWLET            ,
    SPECIES_DARTRIX           ,
    SPECIES_DECIDUEYE         ,
    SPECIES_LITTEN            ,
    SPECIES_TORRACAT          ,
    SPECIES_INCINEROAR        ,
    SPECIES_POPPLIO           ,
    SPECIES_BRIONNE           ,
    SPECIES_PRIMARINA         ,
    SPECIES_PIKIPEK           ,
    SPECIES_TRUMBEAK          ,
    SPECIES_TOUCANNON         ,
    SPECIES_YUNGOOS           ,
    SPECIES_GUMSHOOS          ,
    SPECIES_GRUBBIN           ,
    SPECIES_CHARJABUG         ,
    SPECIES_VIKAVOLT          ,
    SPECIES_CRABRAWLER        ,
    SPECIES_CRABOMINABLE      ,
    SPECIES_ORICORIO          ,
    SPECIES_CUTIEFLY          ,
    SPECIES_RIBOMBEE          ,
    SPECIES_ROCKRUFF          ,
    SPECIES_LYCANROC          ,
    SPECIES_WISHIWASHI        ,
    SPECIES_MAREANIE          ,
    SPECIES_TOXAPEX           ,
    SPECIES_MUDBRAY           ,
    SPECIES_MUDSDALE          ,
    SPECIES_DEWPIDER          ,
    SPECIES_ARAQUANID         ,
    SPECIES_FOMANTIS          ,
    SPECIES_LURANTIS          ,
    SPECIES_MORELULL          ,
    SPECIES_SHIINOTIC         ,
    SPECIES_SALANDIT          ,
    SPECIES_SALAZZLE          ,
    SPECIES_STUFFUL           ,
    SPECIES_BEWEAR            ,
    SPECIES_BOUNSWEET         ,
    SPECIES_STEENEE           ,
    SPECIES_TSAREENA          ,
    SPECIES_COMFEY            ,
    SPECIES_ORANGURU          ,
    SPECIES_PASSIMIAN         ,
    SPECIES_WIMPOD            ,
    SPECIES_GOLISOPOD         ,
    SPECIES_SANDYGAST         ,
    SPECIES_PALOSSAND         ,
    SPECIES_PYUKUMUKU         ,
    SPECIES_TYPE_NULL         ,
    SPECIES_SILVALLY          ,
    SPECIES_MINIOR            ,
    SPECIES_KOMALA            ,
    SPECIES_TURTONATOR        ,
    SPECIES_TOGEDEMARU        ,
    SPECIES_MIMIKYU           ,
    SPECIES_BRUXISH           ,
    SPECIES_DRAMPA            ,
    SPECIES_DHELMISE          ,
    SPECIES_JANGMO_O          ,
    SPECIES_HAKAMO_O          ,
    SPECIES_KOMMO_O           ,
    SPECIES_TAPU_KOKO         ,
    SPECIES_TAPU_LELE         ,
    SPECIES_TAPU_BULU         ,
    SPECIES_TAPU_FINI         ,
    SPECIES_COSMOG            ,
    SPECIES_COSMOEM           ,
    SPECIES_SOLGALEO          ,
    SPECIES_LUNALA            ,
    SPECIES_NIHILEGO          ,
    SPECIES_BUZZWOLE          ,
    SPECIES_PHEROMOSA         ,
    SPECIES_XURKITREE         ,
    SPECIES_CELESTEELA        ,
    SPECIES_KARTANA           ,
    SPECIES_GUZZLORD          ,
    SPECIES_NECROZMA          ,
    SPECIES_MAGEARNA          ,
    SPECIES_MARSHADOW         ,
    SPECIES_POIPOLE           ,
    SPECIES_NAGANADEL         ,
    SPECIES_STAKATAKA         ,
    SPECIES_BLACEPHALON       ,
    SPECIES_ZERAORA           ,
    SPECIES_MELTAN            ,
    SPECIES_MELMETAL          ,
    SPECIES_GROOKEY           ,
    SPECIES_THWACKEY          ,
    SPECIES_RILLABOOM         ,
    SPECIES_SCORBUNNY         ,
    SPECIES_RABOOT            ,
    SPECIES_CINDERACE         ,
    SPECIES_SOBBLE            ,
    SPECIES_DRIZZILE          ,
    SPECIES_INTELEON          ,
    SPECIES_SKWOVET           ,
    SPECIES_GREEDENT          ,
    SPECIES_ROOKIDEE          ,
    SPECIES_CORVISQUIRE       ,
    SPECIES_CORVIKNIGHT       ,
    SPECIES_BLIPBUG           ,
    SPECIES_DOTTLER           ,
    SPECIES_ORBEETLE          ,
    SPECIES_NICKIT            ,
    SPECIES_THIEVUL           ,
    SPECIES_GOSSIFLEUR        ,
    SPECIES_ELDEGOSS          ,
    SPECIES_WOOLOO            ,
    SPECIES_DUBWOOL           ,
    SPECIES_CHEWTLE           ,
    SPECIES_DREDNAW           ,
    SPECIES_YAMPER            ,
    SPECIES_BOLTUND           ,
    SPECIES_ROLYCOLY          ,
    SPECIES_CARKOL            ,
    SPECIES_COALOSSAL         ,
    SPECIES_APPLIN            ,
    SPECIES_FLAPPLE           ,
    SPECIES_APPLETUN          ,
    SPECIES_SILICOBRA         ,
    SPECIES_SANDACONDA        ,
    SPECIES_CRAMORANT         ,
    SPECIES_ARROKUDA          ,
    SPECIES_BARRASKEWDA       ,
    SPECIES_TOXEL             ,
    SPECIES_TOXTRICITY        ,
    SPECIES_SIZZLIPEDE        ,
    SPECIES_CENTISKORCH       ,
    SPECIES_CLOBBOPUS         ,
    SPECIES_GRAPPLOCT         ,
    SPECIES_SINISTEA          ,
    SPECIES_POLTEAGEIST       ,
    SPECIES_HATENNA           ,
    SPECIES_HATTREM           ,
    SPECIES_HATTERENE         ,
    SPECIES_IMPIDIMP          ,
    SPECIES_MORGREM           ,
    SPECIES_GRIMMSNARL        ,
    SPECIES_OBSTAGOON         ,
    SPECIES_PERRSERKER        ,
    SPECIES_CURSOLA           ,
    SPECIES_SIRFETCHD         ,
    SPECIES_MR_RIME           ,
    SPECIES_RUNERIGUS         ,
    SPECIES_MILCERY           ,
    SPECIES_ALCREMIE          ,
    SPECIES_FALINKS           ,
    SPECIES_PINCURCHIN        ,
    SPECIES_SNOM              ,
    SPECIES_FROSMOTH          ,
    SPECIES_STONJOURNER       ,
    SPECIES_EISCUE            ,
    SPECIES_INDEEDEE          ,
    SPECIES_MORPEKO           ,
    SPECIES_CUFANT            ,
    SPECIES_COPPERAJAH        ,
    SPECIES_DRACOZOLT         ,
    SPECIES_ARCTOZOLT         ,
    SPECIES_DRACOVISH         ,
    SPECIES_ARCTOVISH         ,
    SPECIES_DURALUDON         ,
    SPECIES_DREEPY            ,
    SPECIES_DRAKLOAK          ,
    SPECIES_DRAGAPULT         ,
    SPECIES_ZACIAN            ,
    SPECIES_ZAMAZENTA         ,
    SPECIES_ETERNATUS         ,
    SPECIES_KUBFU             ,
    SPECIES_URSHIFU           ,
    SPECIES_ZARUDE            ,
    SPECIES_REGIELEKI         ,
    SPECIES_REGIDRAGO         ,
    SPECIES_GLASTRIER         ,
    SPECIES_SPECTRIER         ,
    SPECIES_CALYREX           ,
    SPECIES_RATTATA_ALOLAN    ,
    SPECIES_RATICATE_ALOLAN   ,
    SPECIES_RAICHU_ALOLAN     ,
    SPECIES_SANDSHREW_ALOLAN  ,
    SPECIES_SANDSLASH_ALOLAN  ,
    SPECIES_VULPIX_ALOLAN     ,
    SPECIES_NINETALES_ALOLAN  ,
    SPECIES_DIGLETT_ALOLAN    ,
    SPECIES_DUGTRIO_ALOLAN    ,
    SPECIES_MEOWTH_ALOLAN     ,
    SPECIES_PERSIAN_ALOLAN    ,
    SPECIES_GEODUDE_ALOLAN    ,
    SPECIES_GRAVELER_ALOLAN   ,
    SPECIES_GOLEM_ALOLAN      ,
    SPECIES_GRIMER_ALOLAN     ,
    SPECIES_MUK_ALOLAN        ,
    SPECIES_EXEGGUTOR_ALOLAN  ,
    SPECIES_MAROWAK_ALOLAN    ,
    SPECIES_MEOWTH_GALARIAN   ,
    SPECIES_PONYTA_GALARIAN   ,
    SPECIES_RAPIDASH_GALARIAN ,
    SPECIES_SLOWPOKE_GALARIAN ,
    SPECIES_SLOWBRO_GALARIAN  ,
    SPECIES_FARFETCHD_GALARIAN ,
    SPECIES_WEEZING_GALARIAN  ,
    SPECIES_MR_MIME_GALARIAN  ,
    SPECIES_ARTICUNO_GALARIAN ,
    SPECIES_ZAPDOS_GALARIAN   ,
    SPECIES_MOLTRES_GALARIAN  ,
    SPECIES_SLOWKING_GALARIAN ,
    SPECIES_CORSOLA_GALARIAN  ,
    SPECIES_ZIGZAGOON_GALARIAN ,
    SPECIES_LINOONE_GALARIAN  ,
    SPECIES_DARUMAKA_GALARIAN ,
    SPECIES_DARMANITAN_GALARIAN ,
    SPECIES_YAMASK_GALARIAN   ,
    SPECIES_STUNFISK_GALARIAN ,
    SPECIES_PIKACHU_HOENN_CAP ,
    SPECIES_PICHU_SPIKY_EARED ,
    SPECIES_BURMY_SANDY_CLOAK ,
    SPECIES_BURMY_TRASH_CLOAK ,
    SPECIES_WORMADAM_SANDY_CLOAK ,
    SPECIES_WORMADAM_TRASH_CLOAK ,
    SPECIES_CHERRIM_SUNSHINE  ,
    SPECIES_DEERLING_SUMMER   ,
    SPECIES_DEERLING_AUTUMN   ,
    SPECIES_DEERLING_WINTER   ,
    SPECIES_SAWSBUCK_SUMMER   ,
    SPECIES_SAWSBUCK_AUTUMN   ,
    SPECIES_SAWSBUCK_WINTER   ,
    //SPECIES_KYUREM_WHITE      ,
    //SPECIES_KYUREM_BLACK      ,
    SPECIES_WYRDEER,
    SPECIES_KLEAVOR,
    SPECIES_URSALUNA,
    SPECIES_BASCULEGION_MALE,
    SPECIES_SNEASLER,
    SPECIES_OVERQWIL,
    SPECIES_ENAMORUS_INCARNATE,
    SPECIES_GROWLITHE_HISUIAN,
    SPECIES_ARCANINE_HISUIAN,
    SPECIES_VOLTORB_HISUIAN,
    SPECIES_ELECTRODE_HISUIAN,
    SPECIES_TYPHLOSION_HISUIAN,
    SPECIES_QWILFISH_HISUIAN,
    SPECIES_SNEASEL_HISUIAN,
    SPECIES_SAMUROTT_HISUIAN,
    SPECIES_LILLIGANT_HISUIAN,
    SPECIES_ZORUA_HISUIAN,
    SPECIES_ZOROARK_HISUIAN,
    SPECIES_BRAVIARY_HISUIAN,
    SPECIES_SLIGGOO_HISUIAN,
    SPECIES_GOODRA_HISUIAN,
    SPECIES_AVALUGG_HISUIAN,
    SPECIES_DECIDUEYE_HISUIAN,
    SPECIES_SPRIGATITO,
    SPECIES_FLORAGATO,
    SPECIES_MEOWSCARADA,
    SPECIES_FUECOCO,
    SPECIES_CROCALOR,
    SPECIES_SKELEDIRGE,
    SPECIES_QUAXLY,
    SPECIES_QUAXWELL,
    SPECIES_QUAQUAVAL,
    SPECIES_LECHONK,
    SPECIES_OINKOLOGNE_MALE,
    SPECIES_TAROUNTULA,
    SPECIES_SPIDOPS,
    SPECIES_NYMBLE,
    SPECIES_LOKIX,
    SPECIES_PAWMI,
    SPECIES_PAWMO,
    SPECIES_PAWMOT,
    SPECIES_TANDEMAUS,
    SPECIES_MAUSHOLD_FAMILY_OF_THREE,
    SPECIES_MAUSHOLD_FAMILY_OF_FOUR,
    SPECIES_FIDOUGH,
    SPECIES_DACHSBUN,
    SPECIES_SMOLIV,
    SPECIES_DOLLIV,
    SPECIES_ARBOLIVA,
    SPECIES_SQUAWKABILLY_GREEN_PLUMAGE,
    SPECIES_NACLI,
    SPECIES_NACLSTACK,
    SPECIES_GARGANACL,
    SPECIES_CHARCADET,
    SPECIES_ARMAROUGE,
    SPECIES_CERULEDGE,
    SPECIES_TADBULB,
    SPECIES_BELLIBOLT,
    SPECIES_WATTREL,
    SPECIES_KILOWATTREL,
    SPECIES_MASCHIFF,
    SPECIES_MABOSSTIFF,
    SPECIES_SHROODLE,
    SPECIES_GRAFAIAI,
    SPECIES_BRAMBLIN,
    SPECIES_BRAMBLEGHAST,
    SPECIES_TOEDSCOOL,
    SPECIES_TOEDSCRUEL,
    SPECIES_KLAWF,
    SPECIES_CAPSAKID,
    SPECIES_SCOVILLAIN,
    SPECIES_RELLOR,
    SPECIES_RABSCA,
    SPECIES_FLITTLE,
    SPECIES_ESPATHRA,
    SPECIES_TINKATINK,
    SPECIES_TINKATUFF,
    SPECIES_TINKATON,
    SPECIES_WIGLETT,
    SPECIES_WUGTRIO,
    SPECIES_BOMBIRDIER,
    SPECIES_FINIZEN,
    SPECIES_PALAFIN_ZERO,
    SPECIES_PALAFIN_HERO,
    SPECIES_VAROOM,
    SPECIES_REVAVROOM,
    SPECIES_CYCLIZAR,
    SPECIES_ORTHWORM,
    SPECIES_GLIMMET,
    SPECIES_GLIMMORA,
    SPECIES_GREAVARD,
    SPECIES_HOUNDSTONE,
    SPECIES_FLAMIGO,
    SPECIES_CETODDLE,
    SPECIES_CETITAN,
    SPECIES_VELUZA,
    SPECIES_DONDOZO,
    SPECIES_TATSUGIRI_CURLY,
    SPECIES_TATSUGIRI_DROOPY,
    SPECIES_TATSUGIRI_STRETCHY,
    SPECIES_ANNIHILAPE,
    SPECIES_CLODSIRE,
    SPECIES_FARIGIRAF,
    SPECIES_DUDUNSPARCE_TWO_SEGMENT,
    SPECIES_DUDUNSPARCE_THREE_SEGMENT,
    SPECIES_KINGAMBIT,
    SPECIES_GREAT_TUSK,
    SPECIES_SCREAM_TAIL,
    SPECIES_BRUTE_BONNET,
    SPECIES_FLUTTER_MANE,
    SPECIES_SLITHER_WING,
    SPECIES_SANDY_SHOCKS,
    SPECIES_IRON_TREADS,
    SPECIES_IRON_BUNDLE,
    SPECIES_IRON_HANDS,
    SPECIES_IRON_JUGULIS,
    SPECIES_IRON_MOTH,
    SPECIES_IRON_THORNS,
    SPECIES_FRIGIBAX,
    SPECIES_ARCTIBAX,
    SPECIES_BAXCALIBUR,
    SPECIES_GIMMIGHOUL_CHEST,
    SPECIES_GHOLDENGO,
    SPECIES_WO_CHIEN,
    SPECIES_CHIEN_PAO,
    SPECIES_TING_LU,
    SPECIES_CHI_YU,
    SPECIES_ROARING_MOON,
    SPECIES_IRON_VALIANT,
    SPECIES_KORAIDON,
    SPECIES_MIRAIDON,
    SPECIES_TAUROS_PALDEAN_COMBAT_BREED,
    SPECIES_TAUROS_PALDEAN_BLAZE_BREED,
    SPECIES_TAUROS_PALDEAN_AQUA_BREED,
    SPECIES_WOOPER_PALDEAN,
    SPECIES_WALKING_WAKE,
    SPECIES_IRON_LEAVES,
    SPECIES_DIPPLIN,
    SPECIES_POLTCHAGEIST_COUNTERFEIT,
    SPECIES_SINISTCHA_UNREMARKABLE,
    SPECIES_OKIDOGI,
    SPECIES_MUNKIDORI,
    SPECIES_FEZANDIPITI,
    SPECIES_OGERPON_TEAL_MASK,
    SPECIES_URSALUNA_BLOODMOON,
    SPECIES_ARCHALUDON,
    SPECIES_HYDRAPPLE,
    SPECIES_GOUGING_FIRE,
    SPECIES_RAGING_BOLT,
    SPECIES_IRON_BOULDER,
    SPECIES_IRON_CROWN,
    SPECIES_PECHARUNT,
    SPECIES_TERAPAGOS
    #endif
    // SPECIES_EGG       ,
};

u16 GetSpeciesRandomSeeded(u16 species)
{
    return sRandomSpeciesLegendary[RandomSeededModulo2(species, RANDOM_SPECIES_COUNT_LEGENDARY)];
}

u16 GetSpeciesRandomNotSeeded(u16 species)
{
    return sRandomSpeciesLegendary[RandomModulo(species, RANDOM_SPECIES_COUNT_LEGENDARY)];
}

u16 GetRandomMove(u16 move, u16 species)
{
    u16 val = RandomSeededModulo2((Random() % GetRandomValidMovesCount()) + move + species, GetRandomValidMovesCount());
    u16 final = gRandomValidMoves[val];

    DebugPrintf("move = %d", move);
    DebugPrintf("species = %d", species);
    DebugPrintf("GetRandomMove = %d", final);
    return final;
}
const u8 *GetMoveName(u16 moveId)
{
    return gMovesInfo[moveId].name;
}

bool8 IsSpeciesLegendary(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].isLegendary)
        return TRUE;
    return FALSE;
}

bool8 IsSpeciesMythical(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].isMythical)
        return TRUE;
    return FALSE;
}

bool8 IsSpeciesUltraBeast(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].isUltraBeast)
        return TRUE;
    return FALSE;
}

bool8 IsSpeciesParadoxMon(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].isParadox)
        return TRUE;
    return FALSE;
}

u32 GetMaxNumberOfSpecies(void)
{
    return RANDOM_SPECIES_COUNT_LEGENDARY;
}

u8 GetCurrentMaxMonGeneratedCount(void)
{
    u32 speciesCountReduced = ((GetMaxNumberOfSpecies() * 15) / 16);
    return (gSaveBlock3Ptr->monsGeneratedCount / (speciesCountReduced)) + 1;
}

u16 GetRandomSpeciesFlattenedCurve(void)
{
    u16 randomSpecies = 0;
    u16 largestMonCount = gSaveBlock3Ptr->largestMonCount;
    u16 notChosen = TRUE;
    u8 maxChosenNumber = 0;
    u16 breakOut = 0;

    gSaveBlock3Ptr->monsGeneratedCount += 1;
    maxChosenNumber = GetCurrentMaxMonGeneratedCount();

    //SeedRngWithRtc();

    while(notChosen)
    {
        randomSpecies = GetSpeciesRandomNotSeeded(0);
        if(gSaveBlock3Ptr->monRolledCounts[randomSpecies] < maxChosenNumber)
            notChosen = FALSE;

        breakOut++;
        if(breakOut > 100000)
            notChosen = FALSE;
    }

    gSaveBlock3Ptr->monRolledCounts[randomSpecies] += 1;
    if(gSaveBlock3Ptr->monRolledCounts[randomSpecies] > largestMonCount)
        gSaveBlock3Ptr->largestMonCount = gSaveBlock3Ptr->monRolledCounts[randomSpecies] + 1;

    return randomSpecies;
        
}

void ClearGeneratedMons(void)
{
    u16 i = 0;
    gSaveBlock3Ptr->monsGeneratedCount = 0;
    for(i = 0; i < GetMaxNumberOfSpecies(); i++)
    {
        gSaveBlock3Ptr->monRolledCounts[i] = 0;
    }
}

void DebugTestRandomness(void)
{
    u16 i = 0;
    u16 floor = 0;
    u16 partyNum = 0;
    u16 trainerNum = 0;

    ClearGeneratedMons();
    //SeedRngWithRtc();

    i = 0;
    while(i < 1)
    {
        for(floor = 0; floor < 10; floor++)
        {
            for(trainerNum = 0; trainerNum < 4; trainerNum++)
            {
                for(partyNum = 0; partyNum < 5; partyNum++)
                {
                    GetRandomSpeciesFlattenedCurve();
                }
            }
        }
        i++;
    }

    //DebugPrintf("\n\n\nDebugTestRandomness New");
    for(i = 0; i < GetMaxNumberOfSpecies(); i++)
    {
        StringCopy(gStringVar1, GetSpeciesName(i));
        //DebugPrintf("Species %S: %d", &gStringVar1, gSaveBlock3Ptr->monRolledCounts[i]);
    }
    //DebugPrintf("Number of Mons Generated: %d", gSaveBlock3Ptr->monsGeneratedCount);
    
    ClearGeneratedMons();
}



//
//		Random Items
//

//tx_randomizer_and_challenges
#define RANDOM_CONSUMABLE_ITEM_COUNT ARRAY_COUNT(sRandomConsumableValidItems)
static const u16 sRandomConsumableValidItems[] =
{
    // Medicine
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_RESTORE,
    ITEM_REVIVE,
    ITEM_MAX_REVIVE,
    ITEM_FRESH_WATER,
    ITEM_SODA_POP,
    ITEM_LEMONADE,
    ITEM_MOOMOO_MILK,
    ITEM_ENERGY_POWDER,
    ITEM_ENERGY_ROOT,
    ITEM_HEAL_POWDER,
    ITEM_REVIVAL_HERB,
    ITEM_ANTIDOTE,
    ITEM_PARALYZE_HEAL,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_FULL_HEAL,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_MAX_ELIXIR,
    ITEM_RARE_CANDY,
};

#define RANDOM_X_ITEM_COUNT ARRAY_COUNT(sRandomXItems)
static const u16 sRandomXItems[] =
{
    ITEM_X_ATTACK,
    ITEM_X_DEFENSE,
    ITEM_X_SP_ATK,
    ITEM_X_SP_DEF,
    ITEM_X_SPEED,
    ITEM_X_ACCURACY,
    ITEM_DIRE_HIT,
    ITEM_GUARD_SPEC,
};

#define RANDOM_BERRY_ITEM_COUNT ARRAY_COUNT(sRandomBerryValidItems)
static const u16 sRandomBerryValidItems[] =
{
    ITEM_CHERI_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_PECHA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_LEPPA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_LUM_BERRY,
    ITEM_SITRUS_BERRY,
    ITEM_FIGY_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_MAGO_BERRY,
    ITEM_AGUAV_BERRY,
    ITEM_IAPAPA_BERRY,
    ITEM_CHILAN_BERRY,
#ifdef PIT_GEN_3_MODE
    ITEM_LIECHI_BERRY,
    ITEM_GANLON_BERRY,
    ITEM_SALAC_BERRY,
    ITEM_PETAYA_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_STARF_BERRY,
    ITEM_ENIGMA_BERRY,
#else
    ITEM_OCCA_BERRY,
    ITEM_PASSHO_BERRY,
    ITEM_WACAN_BERRY,
    ITEM_RINDO_BERRY,
    ITEM_YACHE_BERRY,
    ITEM_CHOPLE_BERRY,
    ITEM_KEBIA_BERRY,
    ITEM_SHUCA_BERRY,
    ITEM_COBA_BERRY,
    ITEM_PAYAPA_BERRY,
    ITEM_TANGA_BERRY,
    ITEM_CHARTI_BERRY,
    ITEM_KASIB_BERRY,
    ITEM_HABAN_BERRY,
    ITEM_COLBUR_BERRY,
    ITEM_BABIRI_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_GANLON_BERRY,
    ITEM_SALAC_BERRY,
    ITEM_PETAYA_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_STARF_BERRY,
    ITEM_ENIGMA_BERRY,
    ITEM_MICLE_BERRY,
    ITEM_CUSTAP_BERRY,
    ITEM_JABOCA_BERRY,
    ITEM_ROWAP_BERRY,    
    ITEM_ROSELI_BERRY,
    ITEM_KEE_BERRY,
    ITEM_MARANGA_BERRY,
#endif
};

#define RANDOM_HELD_ITEM_COUNT ARRAY_COUNT(sRandomHeldValidItems)
static const u16 sRandomHeldValidItems[] =
{
    ITEM_SILK_SCARF,
    ITEM_CHARCOAL,
    ITEM_MYSTIC_WATER,
    ITEM_MAGNET,
    ITEM_MIRACLE_SEED,
    ITEM_NEVER_MELT_ICE,
    ITEM_BLACK_BELT,
    ITEM_POISON_BARB,
    ITEM_SOFT_SAND,
    ITEM_SHARP_BEAK,
    ITEM_TWISTED_SPOON,
    ITEM_SILVER_POWDER,
    ITEM_HARD_STONE,
    ITEM_SPELL_TAG,
    ITEM_DRAGON_FANG,
    ITEM_BLACK_GLASSES,
    ITEM_BRIGHT_POWDER,
    ITEM_FOCUS_BAND,
    ITEM_LEFTOVERS,
    ITEM_QUICK_CLAW,
    ITEM_SCOPE_LENS,
    ITEM_BLUE_FLUTE,
    ITEM_CHOICE_BAND,
    ITEM_CHOICE_SCARF,
    ITEM_MENTAL_HERB,
    ITEM_RED_FLUTE,
    ITEM_SHELL_BELL,
    ITEM_SOOTHE_BELL,
    ITEM_WHITE_HERB,
    ITEM_YELLOW_FLUTE,
#ifndef PIT_GEN_3_MODE
    ITEM_BIG_ROOT,
    ITEM_BLACK_SLUDGE,
    ITEM_CHOICE_SPECS,
    ITEM_DAMP_ROCK,
    ITEM_DESTINY_KNOT,
    ITEM_EXPERT_BELT,
    ITEM_FLAME_ORB,
    ITEM_FOCUS_SASH,
    ITEM_GRIP_CLAW,
    ITEM_HEAT_ROCK,
    ITEM_ICY_ROCK,
    ITEM_IRON_BALL,
    ITEM_LAGGING_TAIL,
    ITEM_LIGHT_CLAY,
    ITEM_LIFE_ORB,
    ITEM_METRONOME,
    ITEM_MUSCLE_BAND,
    ITEM_POWER_HERB,
    ITEM_SHED_SHELL,
    ITEM_SMOOTH_ROCK,
    ITEM_TOXIC_ORB,
    ITEM_WISE_GLASSES,
    ITEM_WIDE_LENS,
    ITEM_ZOOM_LENS,
    ITEM_AIR_BALLOON,
    ITEM_BINDING_BAND,
    ITEM_EJECT_BUTTON,
    ITEM_EVIOLITE,
    ITEM_FLOAT_STONE,
    ITEM_RED_CARD,
    ITEM_RING_TARGET,
    ITEM_ROCKY_HELMET,
#endif
#ifdef PIT_GEN_9_MODE
    ITEM_AMULET_COIN,
    ITEM_ASSAULT_VEST,
    ITEM_SAFETY_GOGGLES,
    ITEM_WEAKNESS_POLICY,
    ITEM_ADRENALINE_ORB,
    ITEM_PROTECTIVE_PADS,
    ITEM_TERRAIN_EXTENDER,
    ITEM_BLUNDER_POLICY,
    ITEM_EJECT_PACK,
    ITEM_HEAVY_DUTY_BOOTS,
    ITEM_ROOM_SERVICE,
    ITEM_THROAT_SPRAY,
    ITEM_UTILITY_UMBRELLA,
    ITEM_ABILITY_SHIELD,
    ITEM_CLEAR_AMULET,
    ITEM_COVERT_CLOAK,
    ITEM_LOADED_DICE,
    ITEM_MIRROR_HERB,
    ITEM_PUNCHING_GLOVE,
    ITEM_FAIRY_FEATHER,
#endif
};

#define RANDOM_ITEM_REROLL_COUNT ARRAY_COUNT(sRandomItemsRerollCheck)
static const u16 sRandomItemsRerollCheck[] =
{
    ITEM_BLUE_FLUTE,
    ITEM_YELLOW_FLUTE,
    ITEM_RED_FLUTE,
    ITEM_AMULET_COIN,
};

#define RANDOM_HELD_ITEM_OPPONENT_COUNT ARRAY_COUNT(sRandomHeldItemsForOpponents)
static const u16 sRandomHeldItemsForOpponents[] =
{
    ITEM_NONE,
    ITEM_NONE,
    ITEM_NONE,
    ITEM_SILK_SCARF,
    ITEM_CHARCOAL,
    ITEM_MYSTIC_WATER,
    ITEM_MAGNET,
    ITEM_MIRACLE_SEED,
    ITEM_NEVER_MELT_ICE,
    ITEM_BLACK_BELT,
    ITEM_POISON_BARB,
    ITEM_SOFT_SAND,
    ITEM_SHARP_BEAK,
    ITEM_TWISTED_SPOON,
    ITEM_SILVER_POWDER,
    ITEM_HARD_STONE,
    ITEM_SPELL_TAG,
    ITEM_DRAGON_FANG,
    ITEM_BLACK_GLASSES,
    ITEM_METAL_COAT,
    ITEM_CHERI_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_PECHA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_LEPPA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_LUM_BERRY,
    ITEM_SITRUS_BERRY,
    ITEM_BRIGHT_POWDER,
    ITEM_FOCUS_BAND,
    ITEM_LEFTOVERS,
    ITEM_QUICK_CLAW,
    ITEM_SCOPE_LENS,
    ITEM_SOOTHE_BELL,
    ITEM_CHOICE_BAND,
    ITEM_CHOICE_SCARF,
    ITEM_MENTAL_HERB,
    ITEM_SHELL_BELL,
    ITEM_WHITE_HERB,
    ITEM_AMULET_COIN,
#ifndef PIT_GEN_3_MODE
    ITEM_BIG_ROOT,
    ITEM_CHOICE_SPECS,
    ITEM_DESTINY_KNOT,
    ITEM_EXPERT_BELT,
    ITEM_FOCUS_SASH,
    ITEM_GRIP_CLAW,
    ITEM_LIFE_ORB,
    ITEM_METRONOME,
    ITEM_MUSCLE_BAND,
    ITEM_POWER_HERB,
    ITEM_SHED_SHELL,
    ITEM_STICKY_BARB,
    ITEM_WIDE_LENS,
    ITEM_WISE_GLASSES,
    ITEM_ZOOM_LENS,
    ITEM_AIR_BALLOON,
    ITEM_BINDING_BAND,
    ITEM_EJECT_BUTTON,
    ITEM_EVIOLITE,
    ITEM_FLOAT_STONE,
    ITEM_RED_CARD,
    ITEM_RING_TARGET,
    ITEM_ROCKY_HELMET,
#endif
#ifdef PIT_GEN_9_MODE
    ITEM_ASSAULT_VEST,
    ITEM_SAFETY_GOGGLES,
    ITEM_ADRENALINE_ORB,
    ITEM_PROTECTIVE_PADS,
    ITEM_TERRAIN_EXTENDER,
    ITEM_THROAT_SPRAY,
    ITEM_EJECT_PACK,
    ITEM_HEAVY_DUTY_BOOTS,
    ITEM_CLEAR_AMULET,
    ITEM_COVERT_CLOAK,
    ITEM_LOADED_DICE,
    ITEM_MIRROR_HERB,
    ITEM_FAIRY_FEATHER,
#endif
};

u16 GetRandomHeldItemOpponent(void)
{
    u16 item;

    item = (Random() % (RANDOM_HELD_ITEM_OPPONENT_COUNT - 1));
    item = sRandomHeldItemsForOpponents[item];
    return item;
}

u16 RandomItemId(u16 itemId)
{
    u16 randomItemCategory = 0;
    bool8 rerollItem = FALSE;
    int i;
    int counter = 0;

    do
    {    
        if (ItemId_GetPocket(itemId) == POCKET_TM_HM)
        {
            return itemId;
        }
        else if (ItemId_GetPocket(itemId) != POCKET_KEY_ITEMS)
        {
            randomItemCategory = Random32() % 1000;
            if(randomItemCategory < 100)
                itemId = sRandomXItems[RandomModulo(itemId + VarGet(VAR_PIT_FLOOR) + gSaveBlock1Ptr->pos.x, RANDOM_X_ITEM_COUNT)];
            else if(randomItemCategory < 700)
                itemId = sRandomConsumableValidItems[RandomModulo(itemId + VarGet(VAR_PIT_FLOOR) + gSaveBlock1Ptr->pos.x, RANDOM_CONSUMABLE_ITEM_COUNT)];
            else if(randomItemCategory < 900)
                itemId = sRandomHeldValidItems[RandomModulo(itemId + VarGet(VAR_PIT_FLOOR) + gSaveBlock1Ptr->pos.x, RANDOM_HELD_ITEM_COUNT)];
            else if(randomItemCategory < 997)
                itemId = sRandomBerryValidItems[RandomModulo(itemId + VarGet(VAR_PIT_FLOOR) + gSaveBlock1Ptr->pos.x, RANDOM_BERRY_ITEM_COUNT)];
            else
                itemId = ITEM_NUGGET;
        }
        //check for reroll
        for (i = 0; i < RANDOM_ITEM_REROLL_COUNT; i++)
        {
            if((itemId == sRandomItemsRerollCheck[i]) && (CheckBagHasItem(itemId, 1) || CheckPartyMonHasHeldItem(itemId)))
            {
                DebugPrintf("rerollItem = TRUE, i=%d", i);
                rerollItem = TRUE;
            }
        }
        //exit in case of infinite loop
        if (counter >= 20)
            rerollItem = FALSE;
        counter++;
    } while (rerollItem);

    VarSet(VAR_0x8006, itemId);
    DebugPrintf("itemId = %d", itemId);
    return itemId;
}

u16 RandomItem(void)
{
    u16 itemId = ITEM_NONE;
    if(FlagGet(FLAG_DONT_RANDOMIZE_NEXT_ITEM))
        itemId = gSpecialVar_0x8000;
    else
        itemId = RandomItemId(gSpecialVar_0x8000);
    FlagClear(FLAG_DONT_RANDOMIZE_NEXT_ITEM);

    gSpecialVar_0x8000 = itemId;
    gSpecialVar_0x8006 = itemId;
    return itemId;
}

u16 RandomItemHidden(void) //same as normal hidden item, but differen special var
{
    u16 itemId = RandomItemId(gSpecialVar_0x8005);

    gSpecialVar_0x8005 = itemId;
    return itemId;
}

// Returns ITEM_NONE if no mega evolution by mega stone is possible
u16 GetMegaStone(u32 species)
{
    u32 i;
    u32 megaStone = ITEM_NONE;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (formChanges != NULL)
    {
        for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
        {
            if (formChanges[i].method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM)
            {
                //multiple mega stones (X/Y) currently not considered
                megaStone = formChanges[i].param1;
            }
        }
    }

    return megaStone;
}




//
//		Random Moves
//

#define RANDOM_MOVES_COUNT ARRAY_COUNT(gRandomValidMoves)
const u16 gRandomValidMoves[] =
{
    MOVE_POUND,
    MOVE_KARATE_CHOP,
    MOVE_DOUBLE_SLAP,
    MOVE_COMET_PUNCH,
    MOVE_MEGA_PUNCH,
    MOVE_PAY_DAY,
    MOVE_FIRE_PUNCH,
    MOVE_ICE_PUNCH,
    MOVE_THUNDER_PUNCH,
    MOVE_SCRATCH,
    MOVE_VISE_GRIP,
    MOVE_GUILLOTINE,
    MOVE_RAZOR_WIND,
    MOVE_SWORDS_DANCE,
    MOVE_CUT,
    MOVE_GUST,
    MOVE_WING_ATTACK,
    MOVE_WHIRLWIND,
    MOVE_FLY,
    MOVE_BIND,
    MOVE_SLAM,
    MOVE_VINE_WHIP,
    MOVE_STOMP,
    MOVE_DOUBLE_KICK,
    MOVE_MEGA_KICK,
    MOVE_JUMP_KICK,
    MOVE_ROLLING_KICK,
    MOVE_SAND_ATTACK,
    MOVE_HEADBUTT,
    MOVE_HORN_ATTACK,
    MOVE_FURY_ATTACK,
    MOVE_HORN_DRILL,
    MOVE_TACKLE,
    MOVE_BODY_SLAM,
    MOVE_WRAP,
    MOVE_TAKE_DOWN,
    MOVE_THRASH,
    MOVE_DOUBLE_EDGE,
    MOVE_TAIL_WHIP,
    MOVE_POISON_STING,
    MOVE_TWINEEDLE,
    MOVE_PIN_MISSILE,
    MOVE_LEER,
    MOVE_BITE,
    MOVE_GROWL,
    MOVE_ROAR,
    MOVE_SING,
    MOVE_SUPERSONIC,
    MOVE_SONIC_BOOM,
    MOVE_DISABLE,
    MOVE_ACID,
    MOVE_EMBER,
    MOVE_FLAMETHROWER,
    MOVE_MIST,
    MOVE_WATER_GUN,
    MOVE_HYDRO_PUMP,
    MOVE_SURF,
    MOVE_ICE_BEAM,
    MOVE_BLIZZARD,
    MOVE_PSYBEAM,
    MOVE_BUBBLE_BEAM,
    MOVE_AURORA_BEAM,
    MOVE_HYPER_BEAM,
    MOVE_PECK,
    MOVE_DRILL_PECK,
    MOVE_SUBMISSION,
    MOVE_LOW_KICK,
    MOVE_COUNTER,
    MOVE_SEISMIC_TOSS,
    MOVE_STRENGTH,
    MOVE_ABSORB,
    MOVE_MEGA_DRAIN,
    MOVE_LEECH_SEED,
    MOVE_GROWTH,
    MOVE_RAZOR_LEAF,
    MOVE_SOLAR_BEAM,
    MOVE_POISON_POWDER,
    MOVE_STUN_SPORE,
    MOVE_SLEEP_POWDER,
    MOVE_PETAL_DANCE,
    MOVE_STRING_SHOT,
    MOVE_DRAGON_RAGE,
    MOVE_FIRE_SPIN,
    MOVE_THUNDER_SHOCK,
    MOVE_THUNDERBOLT,
    MOVE_THUNDER_WAVE,
    MOVE_THUNDER,
    MOVE_ROCK_THROW,
    MOVE_EARTHQUAKE,
    MOVE_FISSURE,
    MOVE_DIG,
    MOVE_TOXIC,
    MOVE_CONFUSION,
    MOVE_PSYCHIC,
    MOVE_HYPNOSIS,
    MOVE_MEDITATE,
    MOVE_AGILITY,
    MOVE_QUICK_ATTACK,
    MOVE_RAGE,
    MOVE_TELEPORT,
    MOVE_NIGHT_SHADE,
    MOVE_MIMIC,
    MOVE_SCREECH,
    MOVE_DOUBLE_TEAM,
    MOVE_RECOVER,
    MOVE_HARDEN,
    MOVE_MINIMIZE,
    MOVE_SMOKESCREEN,
    MOVE_CONFUSE_RAY,
    MOVE_WITHDRAW,
    MOVE_DEFENSE_CURL,
    MOVE_BARRIER,
    MOVE_LIGHT_SCREEN,
    MOVE_HAZE,
    MOVE_REFLECT,
    MOVE_FOCUS_ENERGY,
    MOVE_BIDE,
    MOVE_METRONOME,
    MOVE_MIRROR_MOVE,
    MOVE_SELF_DESTRUCT,
    MOVE_EGG_BOMB,
    MOVE_LICK,
    MOVE_SMOG,
    MOVE_SLUDGE,
    MOVE_BONE_CLUB,
    MOVE_FIRE_BLAST,
    MOVE_WATERFALL,
    MOVE_CLAMP,
    MOVE_SWIFT,
    MOVE_SKULL_BASH,
    MOVE_SPIKE_CANNON,
    MOVE_CONSTRICT,
    MOVE_AMNESIA,
    MOVE_KINESIS,
    MOVE_SOFT_BOILED,
    MOVE_HIGH_JUMP_KICK,
    MOVE_GLARE,
    MOVE_DREAM_EATER,
    MOVE_POISON_GAS,
    MOVE_BARRAGE,
    MOVE_LEECH_LIFE,
    MOVE_LOVELY_KISS,
    MOVE_SKY_ATTACK,
    MOVE_TRANSFORM,
    MOVE_BUBBLE,
    MOVE_DIZZY_PUNCH,
    MOVE_SPORE,
    MOVE_FLASH,
    MOVE_PSYWAVE,
    MOVE_SPLASH,
    MOVE_ACID_ARMOR,
    MOVE_CRABHAMMER,
    MOVE_EXPLOSION,
    MOVE_FURY_SWIPES,
    MOVE_BONEMERANG,
    MOVE_REST,
    MOVE_ROCK_SLIDE,
    MOVE_HYPER_FANG,
    MOVE_SHARPEN,
    MOVE_CONVERSION,
    MOVE_TRI_ATTACK,
    MOVE_SUPER_FANG,
    MOVE_SLASH,
    MOVE_SUBSTITUTE,
    //MOVE_SKETCH,
    MOVE_TRIPLE_KICK,
    MOVE_THIEF,
    MOVE_SPIDER_WEB,
    MOVE_MIND_READER,
    MOVE_NIGHTMARE,
    MOVE_FLAME_WHEEL,
    MOVE_SNORE,
    MOVE_CURSE,
    MOVE_FLAIL,
    MOVE_CONVERSION_2,
    MOVE_AEROBLAST,
    MOVE_COTTON_SPORE,
    MOVE_REVERSAL,
    MOVE_SPITE,
    MOVE_POWDER_SNOW,
    MOVE_PROTECT,
    MOVE_MACH_PUNCH,
    MOVE_SCARY_FACE,
    MOVE_FEINT_ATTACK,
    MOVE_SWEET_KISS,
    MOVE_BELLY_DRUM,
    MOVE_SLUDGE_BOMB,
    MOVE_MUD_SLAP,
    MOVE_OCTAZOOKA,
    MOVE_SPIKES,
    MOVE_ZAP_CANNON,
    MOVE_FORESIGHT,
    MOVE_DESTINY_BOND,
    MOVE_PERISH_SONG,
    MOVE_ICY_WIND,
    MOVE_DETECT,
    MOVE_BONE_RUSH,
    MOVE_LOCK_ON,
    MOVE_OUTRAGE,
    MOVE_SANDSTORM,
    MOVE_GIGA_DRAIN,
    MOVE_ENDURE,
    MOVE_CHARM,
    MOVE_ROLLOUT,
    MOVE_FALSE_SWIPE,
    MOVE_SWAGGER,
    MOVE_MILK_DRINK,
    MOVE_SPARK,
    MOVE_FURY_CUTTER,
    MOVE_STEEL_WING,
    MOVE_MEAN_LOOK,
    MOVE_ATTRACT,
    MOVE_SLEEP_TALK,
    MOVE_HEAL_BELL,
    MOVE_RETURN,
    MOVE_PRESENT,
    MOVE_FRUSTRATION,
    MOVE_SAFEGUARD,
    MOVE_PAIN_SPLIT,
    MOVE_SACRED_FIRE,
    MOVE_MAGNITUDE,
    MOVE_DYNAMIC_PUNCH,
    MOVE_MEGAHORN,
    MOVE_DRAGON_BREATH,
    MOVE_BATON_PASS,
    MOVE_ENCORE,
    MOVE_PURSUIT,
    MOVE_RAPID_SPIN,
    MOVE_SWEET_SCENT,
    MOVE_IRON_TAIL,
    MOVE_METAL_CLAW,
    MOVE_VITAL_THROW,
    MOVE_MORNING_SUN,
    MOVE_SYNTHESIS,
    MOVE_MOONLIGHT,
    MOVE_HIDDEN_POWER,
    MOVE_CROSS_CHOP,
    MOVE_TWISTER,
    MOVE_RAIN_DANCE,
    MOVE_SUNNY_DAY,
    MOVE_CRUNCH,
    MOVE_MIRROR_COAT,
    MOVE_PSYCH_UP,
    MOVE_EXTREME_SPEED,
    MOVE_ANCIENT_POWER,
    MOVE_SHADOW_BALL,
    //MOVE_FUTURE_SIGHT, REMOVED UNTIL NOT BUGGY
    MOVE_ROCK_SMASH,
    MOVE_WHIRLPOOL,
    MOVE_BEAT_UP,
    MOVE_FAKE_OUT,
    MOVE_UPROAR,
    MOVE_STOCKPILE,
    MOVE_SPIT_UP,
    MOVE_SWALLOW,
    MOVE_HEAT_WAVE,
    MOVE_HAIL,
    MOVE_TORMENT,
    MOVE_FLATTER,
    MOVE_WILL_O_WISP,
    MOVE_MEMENTO,
    MOVE_FACADE,
    MOVE_FOCUS_PUNCH,
    MOVE_SMELLING_SALTS,
    MOVE_FOLLOW_ME,
    MOVE_NATURE_POWER,
    MOVE_CHARGE,
    MOVE_TAUNT,
    MOVE_HELPING_HAND,
    MOVE_TRICK,
    MOVE_ROLE_PLAY,
    MOVE_WISH,
    MOVE_ASSIST,
    MOVE_INGRAIN,
    MOVE_SUPERPOWER,
    MOVE_MAGIC_COAT,
    MOVE_RECYCLE,
    MOVE_REVENGE,
    MOVE_BRICK_BREAK,
    MOVE_YAWN,
    MOVE_KNOCK_OFF,
    MOVE_ENDEAVOR,
    MOVE_ERUPTION,
    MOVE_SKILL_SWAP,
    MOVE_IMPRISON,
    MOVE_REFRESH,
    MOVE_GRUDGE,
    MOVE_SNATCH,
    MOVE_SECRET_POWER,
    MOVE_DIVE,
    MOVE_ARM_THRUST,
    MOVE_CAMOUFLAGE,
    MOVE_TAIL_GLOW,
    MOVE_LUSTER_PURGE,
    MOVE_MIST_BALL,
    MOVE_FEATHER_DANCE,
    MOVE_TEETER_DANCE,
    MOVE_BLAZE_KICK,
    MOVE_MUD_SPORT,
    MOVE_ICE_BALL,
    MOVE_NEEDLE_ARM,
    MOVE_SLACK_OFF,
    MOVE_HYPER_VOICE,
    MOVE_POISON_FANG,
    MOVE_CRUSH_CLAW,
    MOVE_BLAST_BURN,
    MOVE_HYDRO_CANNON,
    MOVE_METEOR_MASH,
    MOVE_ASTONISH,
    MOVE_WEATHER_BALL,
    MOVE_AROMATHERAPY,
    MOVE_FAKE_TEARS,
    MOVE_AIR_CUTTER,
    MOVE_OVERHEAT,
    MOVE_ODOR_SLEUTH,
    MOVE_ROCK_TOMB,
    MOVE_SILVER_WIND,
    MOVE_METAL_SOUND,
    MOVE_GRASS_WHISTLE,
    MOVE_TICKLE,
    MOVE_COSMIC_POWER,
    MOVE_WATER_SPOUT,
    MOVE_SIGNAL_BEAM,
    MOVE_SHADOW_PUNCH,
    MOVE_EXTRASENSORY,
    MOVE_SKY_UPPERCUT,
    MOVE_SAND_TOMB,
    MOVE_SHEER_COLD,
    MOVE_MUDDY_WATER,
    MOVE_BULLET_SEED,
    MOVE_AERIAL_ACE,
    MOVE_ICICLE_SPEAR,
    MOVE_IRON_DEFENSE,
    MOVE_BLOCK,
    MOVE_HOWL,
    MOVE_DRAGON_CLAW,
    MOVE_FRENZY_PLANT,
    MOVE_BULK_UP,
    MOVE_BOUNCE,
    MOVE_MUD_SHOT,
    MOVE_POISON_TAIL,
    MOVE_COVET,
    MOVE_VOLT_TACKLE,
    MOVE_MAGICAL_LEAF,
    MOVE_WATER_SPORT,
    MOVE_CALM_MIND,
    MOVE_LEAF_BLADE,
    MOVE_DRAGON_DANCE,
    MOVE_ROCK_BLAST,
    MOVE_SHOCK_WAVE,
    MOVE_WATER_PULSE,
    MOVE_DOOM_DESIRE,
    MOVE_PSYCHO_BOOST,
#ifndef PIT_GEN_3_MODE
    // Gen 4 moves
    MOVE_ROOST,
    MOVE_GRAVITY,
    MOVE_MIRACLE_EYE,
    MOVE_WAKE_UP_SLAP,
    MOVE_HAMMER_ARM,
    MOVE_GYRO_BALL,
    MOVE_HEALING_WISH,
    MOVE_BRINE,
    MOVE_NATURAL_GIFT,
    MOVE_FEINT,
    MOVE_PLUCK,
    MOVE_TAILWIND,
    MOVE_ACUPRESSURE,
    MOVE_METAL_BURST,
    MOVE_U_TURN,
    MOVE_CLOSE_COMBAT,
    MOVE_PAYBACK,
    MOVE_ASSURANCE,
    MOVE_EMBARGO,
    MOVE_FLING,
    MOVE_PSYCHO_SHIFT,
    MOVE_TRUMP_CARD,
    MOVE_HEAL_BLOCK,
    MOVE_WRING_OUT,
    MOVE_POWER_TRICK,
    MOVE_GASTRO_ACID,
    MOVE_LUCKY_CHANT,
    MOVE_ME_FIRST,
    MOVE_COPYCAT,
    MOVE_POWER_SWAP,
    MOVE_GUARD_SWAP,
    MOVE_PUNISHMENT,
    MOVE_LAST_RESORT,
    MOVE_WORRY_SEED,
    MOVE_SUCKER_PUNCH,
    MOVE_TOXIC_SPIKES,
    MOVE_HEART_SWAP,
    MOVE_AQUA_RING,
    MOVE_MAGNET_RISE,
    MOVE_FLARE_BLITZ,
    MOVE_FORCE_PALM,
    MOVE_AURA_SPHERE,
    MOVE_ROCK_POLISH,
    MOVE_POISON_JAB,
    MOVE_DARK_PULSE,
    MOVE_NIGHT_SLASH,
    MOVE_AQUA_TAIL,
    MOVE_SEED_BOMB,
    MOVE_AIR_SLASH,
    MOVE_X_SCISSOR,
    MOVE_BUG_BUZZ,
    MOVE_DRAGON_PULSE,
    MOVE_DRAGON_RUSH,
    MOVE_POWER_GEM,
    MOVE_DRAIN_PUNCH,
    MOVE_VACUUM_WAVE,
    MOVE_FOCUS_BLAST,
    MOVE_ENERGY_BALL,
    MOVE_BRAVE_BIRD,
    MOVE_EARTH_POWER,
    MOVE_SWITCHEROO,
    MOVE_GIGA_IMPACT,
    MOVE_NASTY_PLOT,
    MOVE_BULLET_PUNCH,
    MOVE_AVALANCHE,
    MOVE_ICE_SHARD,
    MOVE_SHADOW_CLAW,
    MOVE_THUNDER_FANG,
    MOVE_ICE_FANG,
    MOVE_FIRE_FANG,
    MOVE_SHADOW_SNEAK,
    MOVE_MUD_BOMB,
    MOVE_PSYCHO_CUT,
    MOVE_ZEN_HEADBUTT,
    MOVE_MIRROR_SHOT,
    MOVE_FLASH_CANNON,
    MOVE_ROCK_CLIMB,
    MOVE_DEFOG,
    MOVE_TRICK_ROOM,
    MOVE_DRACO_METEOR,
    MOVE_DISCHARGE,
    MOVE_LAVA_PLUME,
    MOVE_LEAF_STORM,
    MOVE_POWER_WHIP,
    MOVE_ROCK_WRECKER,
    MOVE_CROSS_POISON,
    MOVE_GUNK_SHOT,
    MOVE_IRON_HEAD,
    MOVE_MAGNET_BOMB,
    MOVE_STONE_EDGE,
    MOVE_CAPTIVATE,
    MOVE_STEALTH_ROCK,
    MOVE_GRASS_KNOT,
    MOVE_CHATTER,
    MOVE_JUDGMENT,
    MOVE_BUG_BITE,
    MOVE_CHARGE_BEAM,
    MOVE_WOOD_HAMMER,
    MOVE_AQUA_JET,
    MOVE_ATTACK_ORDER,
    MOVE_DEFEND_ORDER,
    MOVE_HEAL_ORDER,
    MOVE_HEAD_SMASH,
    MOVE_DOUBLE_HIT,
    MOVE_ROAR_OF_TIME,
    MOVE_SPACIAL_REND,
    MOVE_LUNAR_DANCE,
    MOVE_CRUSH_GRIP,
    MOVE_MAGMA_STORM,
    MOVE_SEED_FLARE,
    MOVE_OMINOUS_WIND,
    MOVE_SHADOW_FORCE,
    // Gen 5 moves
    MOVE_HONE_CLAWS,
    MOVE_WIDE_GUARD,
    MOVE_GUARD_SPLIT,
    MOVE_POWER_SPLIT,
    MOVE_WONDER_ROOM,
    MOVE_PSYSHOCK,
    MOVE_VENOSHOCK,
    MOVE_AUTOTOMIZE,
    MOVE_RAGE_POWDER,
    MOVE_TELEKINESIS,
    MOVE_MAGIC_ROOM,
    MOVE_SMACK_DOWN,
    MOVE_STORM_THROW,
    MOVE_FLAME_BURST,
    MOVE_SLUDGE_WAVE,
    MOVE_QUIVER_DANCE,
    MOVE_HEAVY_SLAM,
    MOVE_SYNCHRONOISE,
    MOVE_ELECTRO_BALL,
    MOVE_SOAK,
    MOVE_FLAME_CHARGE,
    MOVE_COIL,
    MOVE_LOW_SWEEP,
    MOVE_ACID_SPRAY,
    MOVE_FOUL_PLAY,
    MOVE_SIMPLE_BEAM,
    MOVE_ENTRAINMENT,
    MOVE_AFTER_YOU,
    MOVE_ROUND,
    MOVE_ECHOED_VOICE,
    MOVE_CHIP_AWAY,
    MOVE_CLEAR_SMOG,
    MOVE_STORED_POWER,
    MOVE_QUICK_GUARD,
    MOVE_ALLY_SWITCH,
    MOVE_SCALD,
    MOVE_SHELL_SMASH,
    MOVE_HEAL_PULSE,
    MOVE_HEX,
    MOVE_SKY_DROP,
    MOVE_SHIFT_GEAR,
    MOVE_CIRCLE_THROW,
    MOVE_INCINERATE,
    MOVE_QUASH,
    MOVE_ACROBATICS,
    MOVE_REFLECT_TYPE,
    MOVE_RETALIATE,
    MOVE_FINAL_GAMBIT,
    MOVE_BESTOW,
    MOVE_INFERNO,
    MOVE_WATER_PLEDGE,
    MOVE_FIRE_PLEDGE,
    MOVE_GRASS_PLEDGE,
    MOVE_VOLT_SWITCH,
    MOVE_STRUGGLE_BUG,
    MOVE_BULLDOZE,
    MOVE_FROST_BREATH,
    MOVE_DRAGON_TAIL,
    MOVE_WORK_UP,
    MOVE_ELECTROWEB,
    MOVE_WILD_CHARGE,
    MOVE_DRILL_RUN,
    MOVE_DUAL_CHOP,
    MOVE_HEART_STAMP,
    MOVE_HORN_LEECH,
    MOVE_SACRED_SWORD,
    MOVE_RAZOR_SHELL,
    MOVE_HEAT_CRASH,
    MOVE_LEAF_TORNADO,
    MOVE_STEAMROLLER,
    MOVE_COTTON_GUARD,
    MOVE_NIGHT_DAZE,
    MOVE_PSYSTRIKE,
    MOVE_TAIL_SLAP,
    MOVE_HURRICANE,
    MOVE_HEAD_CHARGE,
    MOVE_GEAR_GRIND,
    MOVE_SEARING_SHOT,
    MOVE_TECHNO_BLAST,
    MOVE_RELIC_SONG,
    MOVE_SECRET_SWORD,
    MOVE_GLACIATE,
    MOVE_BOLT_STRIKE,
    MOVE_BLUE_FLARE,
    MOVE_FIERY_DANCE,
    MOVE_FREEZE_SHOCK,
    MOVE_ICE_BURN,
    MOVE_SNARL,
    MOVE_ICICLE_CRASH,
    MOVE_V_CREATE,
    MOVE_FUSION_FLARE,
    MOVE_FUSION_BOLT,
#endif
#ifdef PIT_GEN_9_MODE
    // Gen 6 moves
    MOVE_FLYING_PRESS,
    MOVE_MAT_BLOCK,
    MOVE_BELCH,
    MOVE_ROTOTILLER,
    MOVE_STICKY_WEB,
    MOVE_FELL_STINGER,
    MOVE_PHANTOM_FORCE,
    MOVE_TRICK_OR_TREAT,
    MOVE_NOBLE_ROAR,
    MOVE_ION_DELUGE,
    MOVE_PARABOLIC_CHARGE,
    MOVE_FORESTS_CURSE,
    MOVE_PETAL_BLIZZARD,
    MOVE_FREEZE_DRY,
    MOVE_DISARMING_VOICE,
    MOVE_PARTING_SHOT,
    MOVE_TOPSY_TURVY,
    MOVE_DRAINING_KISS,
    MOVE_CRAFTY_SHIELD,
    MOVE_FLOWER_SHIELD,
    MOVE_GRASSY_TERRAIN,
    MOVE_MISTY_TERRAIN,
    MOVE_ELECTRIFY,
    MOVE_PLAY_ROUGH,
    MOVE_FAIRY_WIND,
    MOVE_MOONBLAST,
    MOVE_BOOMBURST,
    MOVE_FAIRY_LOCK,
    MOVE_KINGS_SHIELD,
    MOVE_PLAY_NICE,
    MOVE_CONFIDE,
    MOVE_DIAMOND_STORM,
    MOVE_STEAM_ERUPTION,
    MOVE_WATER_SHURIKEN,
    MOVE_MYSTICAL_FIRE,
    MOVE_SPIKY_SHIELD,
    MOVE_AROMATIC_MIST,
    MOVE_EERIE_IMPULSE,
    MOVE_VENOM_DRENCH,
    MOVE_POWDER,
    MOVE_GEOMANCY,
    MOVE_MAGNETIC_FLUX,
    MOVE_HAPPY_HOUR,
    MOVE_ELECTRIC_TERRAIN,
    MOVE_DAZZLING_GLEAM,
    MOVE_CELEBRATE,
    MOVE_HOLD_HANDS,
    MOVE_BABY_DOLL_EYES,
    MOVE_NUZZLE,
    MOVE_HOLD_BACK,
    MOVE_INFESTATION,
    MOVE_POWER_UP_PUNCH,
    MOVE_OBLIVION_WING,
    MOVE_THOUSAND_ARROWS,
    MOVE_THOUSAND_WAVES,
    MOVE_LANDS_WRATH,
    MOVE_LIGHT_OF_RUIN,
    // ORAS Moves
    MOVE_ORIGIN_PULSE,
    MOVE_PRECIPICE_BLADES,
    MOVE_DRAGON_ASCENT,
    //MOVE_HYPERSPACE_FURY,
    // Gen 7 moves
    MOVE_SHORE_UP,
    MOVE_FIRST_IMPRESSION,
    MOVE_BANEFUL_BUNKER,
    MOVE_SPIRIT_SHACKLE,
    MOVE_DARKEST_LARIAT,
    MOVE_SPARKLING_ARIA,
    MOVE_ICE_HAMMER,
    MOVE_FLORAL_HEALING,
    MOVE_HIGH_HORSEPOWER,
    MOVE_STRENGTH_SAP,
    MOVE_SOLAR_BLADE,
    MOVE_LEAFAGE,
    MOVE_SPOTLIGHT,
    MOVE_TOXIC_THREAD,
    MOVE_LASER_FOCUS,
    MOVE_GEAR_UP,
    MOVE_THROAT_CHOP,
    MOVE_POLLEN_PUFF,
    MOVE_ANCHOR_SHOT,
    MOVE_PSYCHIC_TERRAIN,
    MOVE_LUNGE,
    MOVE_FIRE_LASH,
    MOVE_POWER_TRIP,
    MOVE_BURN_UP,
    MOVE_SPEED_SWAP,
    MOVE_SMART_STRIKE,
    MOVE_PURIFY,
    MOVE_REVELATION_DANCE,
    MOVE_CORE_ENFORCER,
    MOVE_TROP_KICK,
    MOVE_INSTRUCT,
    MOVE_BEAK_BLAST,
    MOVE_CLANGING_SCALES,
    MOVE_DRAGON_HAMMER,
    MOVE_BRUTAL_SWING,
    MOVE_AURORA_VEIL,
    MOVE_SHELL_TRAP,
    MOVE_FLEUR_CANNON,
    MOVE_PSYCHIC_FANGS,
    MOVE_STOMPING_TANTRUM,
    MOVE_SHADOW_BONE,
    MOVE_ACCELEROCK,
    MOVE_LIQUIDATION,
    MOVE_PRISMATIC_LASER,
    MOVE_SPECTRAL_THIEF,
    MOVE_SUNSTEEL_STRIKE,
    MOVE_MOONGEIST_BEAM,
    MOVE_TEARFUL_LOOK,
    MOVE_ZING_ZAP,
    MOVE_NATURES_MADNESS,
    MOVE_MULTI_ATTACK,
    // USUM Moves
    MOVE_MIND_BLOWN,
    MOVE_PLASMA_FISTS,
    MOVE_PHOTON_GEYSER,
    // Gen 8 moves
    MOVE_DYNAMAX_CANNON,
    MOVE_SNIPE_SHOT,
    MOVE_JAW_LOCK,
    MOVE_STUFF_CHEEKS,
    MOVE_NO_RETREAT,
    MOVE_TAR_SHOT,
    MOVE_MAGIC_POWDER,
    MOVE_DRAGON_DARTS,
    MOVE_TEATIME,
    MOVE_OCTOLOCK,
    MOVE_BOLT_BEAK,
    MOVE_FISHIOUS_REND,
    MOVE_COURT_CHANGE,
    MOVE_CLANGOROUS_SOUL,
    MOVE_BODY_PRESS,
    MOVE_DECORATE,
    MOVE_DRUM_BEATING,
    MOVE_SNAP_TRAP,
    MOVE_PYRO_BALL,
    MOVE_BEHEMOTH_BLADE,
    MOVE_BEHEMOTH_BASH,
    MOVE_BREAKING_SWIPE,
    MOVE_BRANCH_POKE,
    MOVE_OVERDRIVE,
    MOVE_APPLE_ACID,
    MOVE_GRAV_APPLE,
    MOVE_SPIRIT_BREAK,
    MOVE_STRANGE_STEAM,
    MOVE_LIFE_DEW,
    MOVE_OBSTRUCT,
    MOVE_FALSE_SURRENDER,
    MOVE_METEOR_ASSAULT,
    MOVE_ETERNABEAM,
    MOVE_STEEL_BEAM,
    // Isle of Armor Moves
    MOVE_EXPANDING_FORCE,
    MOVE_STEEL_ROLLER,
    MOVE_SCALE_SHOT,
    MOVE_METEOR_BEAM,
    MOVE_SHELL_SIDE_ARM,
    MOVE_MISTY_EXPLOSION,
    MOVE_GRASSY_GLIDE,
    MOVE_RISING_VOLTAGE,
    MOVE_TERRAIN_PULSE,
    MOVE_SKITTER_SMACK,
    MOVE_BURNING_JEALOUSY,
    MOVE_LASH_OUT,
    MOVE_POLTERGEIST,
    MOVE_CORROSIVE_GAS,
    MOVE_COACHING,
    MOVE_FLIP_TURN,
    MOVE_TRIPLE_AXEL,
    MOVE_DUAL_WINGBEAT,
    MOVE_SCORCHING_SANDS,
    MOVE_JUNGLE_HEALING,
    MOVE_WICKED_BLOW,
    MOVE_SURGING_STRIKES,
    // Crown Tundra Moves
    MOVE_THUNDER_CAGE,
    MOVE_DRAGON_ENERGY,
    MOVE_FREEZING_GLARE,
    MOVE_FIERY_WRATH,
    MOVE_THUNDEROUS_KICK,
    MOVE_GLACIAL_LANCE,
    MOVE_ASTRAL_BARRAGE,
    MOVE_EERIE_SPELL,
    #endif
};



//
//		Random Battle Weathers
//

//tx_randomizer_and_challenges
#define RANDOM_BATTLE_WEATHER_COUNT ARRAY_COUNT(sRandomBattleWeathers)
static const u16 sRandomBattleWeathers[] =
{
    WEATHER_NONE,
    WEATHER_RAIN,
    WEATHER_SANDSTORM,
    WEATHER_DROUGHT,
    WEATHER_SNOW,
};

u16 GetRandomBattleWeather(void)
{
    u16 battleWeather;

    battleWeather = (Random() % (RANDOM_BATTLE_WEATHER_COUNT - 1));
    battleWeather = sRandomBattleWeathers[battleWeather];
    return battleWeather;
}


//**********************

u16 GetRandomValidMovesCount(void)
{
	return RANDOM_MOVES_COUNT;
}

u8 GetNumberOfEggMoves(struct Pokemon *mon)
{
    u16 eggMoveBuffer[EGG_MOVES_ARRAY_COUNT];
    u16 learnedMoves[MAX_MON_MOVES];
    u8 numMoves = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    u16 firstStage = GetEggSpecies(species);
    u8 numEggMoves = GetEggMovesBySpecies(firstStage, eggMoveBuffer);
    //u16 moves[numEggMoves];
    int i, j;
    bool8 hasMonMove = FALSE;

    if (species == SPECIES_EGG)
        return 0;
    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < numEggMoves; i++)
    {
        hasMonMove = FALSE;

        for (j = 0; j < MAX_MON_MOVES; j++){
            if(learnedMoves[j] == eggMoveBuffer[i])
                hasMonMove = TRUE;
        }

        if(!hasMonMove)
            numMoves++;
    }

    return numMoves;
}

u8 GetEggMoveTutorMoves(struct Pokemon *mon, u16 *moves)
{
    u16 learnedMoves[4];
    u8 numMoves = 0;
    u16 eggMoveBuffer[EGG_MOVES_ARRAY_COUNT];
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    u16 eggSpecies = GetEggSpecies(species);
    u16 numEggMoves = GetEggMovesBySpecies(eggSpecies, eggMoveBuffer);
    int i, j;
    bool8 hasMonMove = FALSE;

    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < numEggMoves; i++)
    {
        hasMonMove = FALSE;

        for (j = 0; j < MAX_MON_MOVES; j++){
            if(learnedMoves[j] == eggMoveBuffer[i])
                hasMonMove = TRUE;
        }

        if(!hasMonMove)
            moves[numMoves++] = eggMoveBuffer[i];
    }

    return numMoves;
}

u8 GetNumberOfTutorMoves(struct Pokemon *mon)
{
    u16 tutorMoveBuffer[TUTOR_MOVES_ARRAY_COUNT];
    u16 learnedMoves[MAX_MON_MOVES];
    u8 numMoves = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    //u16 firstStage = GetEggSpecies(species);
    u16 numTutorMoves = GetTutorMovesSpecies(species, tutorMoveBuffer);
    //u16 moves[numTutorMoves];
    int i, j;
    bool8 hasMonMove = FALSE;

    if (species == SPECIES_EGG)
        return 0;
    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < numTutorMoves; i++)
    {
        hasMonMove = FALSE;

        for (j = 0; j < MAX_MON_MOVES; j++){
            if(learnedMoves[j] == tutorMoveBuffer[i])
                hasMonMove = TRUE;
        }

        if(!hasMonMove)
            numMoves++;
    }

    return numMoves;
}

u8 GetTutorMoves(struct Pokemon *mon, u16 *moves)
{
    u16 learnedMoves[4];
    u8 numMoves = 0;
    u16 tutorMoveBuffer[TUTOR_MOVES_ARRAY_COUNT];
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    //u16 eggSpecies = GetEggSpecies(species);
    u16 numTutorMoves = GetTutorMovesSpecies(species, tutorMoveBuffer);
    int i, j;
    bool8 hasMonMove = FALSE;

    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < numTutorMoves; i++)
    {
        hasMonMove = FALSE;

        for (j = 0; j < MAX_MON_MOVES; j++){
            if(learnedMoves[j] == tutorMoveBuffer[i])
                hasMonMove = TRUE;
        }

        if(!hasMonMove)
            moves[numMoves++] = tutorMoveBuffer[i];
    }

    return numMoves;
}

u16 GetPreEvolution(u16 species)
{
    int i, j;

    for (i = 1; i < NUM_SPECIES; i++)
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;
        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (SanitizeSpeciesId(evolutions[j].targetSpecies) == species)
                return i;
        }
    }
    return SPECIES_NONE;
}

u8 GetPreEvoMoves(struct Pokemon *mon, u16 *moves, bool8 PreEvoCheckOnly)
{
    u16 learnedMoves[4];
    u8 numMoves = 0;
    u16 speciesPreEvo;
    u16 speciesOriginal = GetMonData(mon, MON_DATA_SPECIES, 0);
    u8 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    const struct LevelUpMove *learnset, *learnsetOriginal;
    int i, j, k;

    speciesPreEvo = GetPreEvolution(speciesOriginal);
    learnset = GetSpeciesLevelUpLearnset(speciesPreEvo);
    learnsetOriginal = GetSpeciesLevelUpLearnset(speciesOriginal);

    //save current moveset
    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    while (speciesPreEvo != SPECIES_NONE)
    {
        //iterate all level up moves
        for (i = 0; i < MAX_LEVEL_UP_MOVES; i++)
        {
            u16 moveLevel;

            //exit if last move from learnset is reached
            if (learnset[i].move == LEVEL_UP_MOVE_END)
                break;

            //check if said move is not currently known
            for (j = 0; j < MAX_MON_MOVES && learnedMoves[j] != learnset[i].move; j++)
                ;

            //if move is currently unknown
            if (j == MAX_MON_MOVES)
            {
                //check if not already in the list
                for (k = 0; k < numMoves && moves[k] != learnset[i].move; k++)
                    ;

                if (k == numMoves)
                {
                    // check if move is not learnable by level-up by original species
                    // to identify if it as an actual PreEvo move
                    for (j = 0; j < MAX_LEVEL_UP_MOVES; j++)
                    {
                        if (learnsetOriginal[j].move == learnset[i].move)
                            break;
                        if (learnsetOriginal[j].move == LEVEL_UP_MOVE_END)
                        {
                            j = 255;
                            break;
                        }
                    }
                    //found a PreEvo move
                    if (j == 255)
                    {
                        if (PreEvoCheckOnly)
                            return TRUE;
                        moves[numMoves++] = learnset[i].move;
                    }
                }
            }
        }
        speciesPreEvo = GetPreEvolution(speciesPreEvo);
        learnset = GetSpeciesLevelUpLearnset(speciesPreEvo);
    }

    return numMoves;
}

#define TUTOR_MOVES_COUNT ARRAY_COUNT(sTutorMoves)
static const u16 sTutorMoves[] =
{
#ifdef PIT_GEN_9_MODE
    MOVE_GRASS_PLEDGE,
    MOVE_FIRE_PLEDGE,
    MOVE_WATER_PLEDGE,
    MOVE_DRACO_METEOR,
    MOVE_FRENZY_PLANT,
    MOVE_BLAST_BURN,
    MOVE_HYDRO_CANNON,
    MOVE_RELIC_SONG,
    MOVE_SECRET_SWORD,
#endif
};

u8 GetStaticTutorMoves(u16 *moves)
{
    int i;

    for (i = 0; i < TUTOR_MOVES_COUNT; i++)
        moves[i] = sTutorMoves[i];

    return TUTOR_MOVES_COUNT;
}



//
//		Ability Randomizer
//

#define INVALID_ABILITIES_COUNT ARRAY_COUNT(sInvalidRandomAbilities)
static const u16 sInvalidRandomAbilities[] =
{
    ABILITY_MULTITYPE,
    ABILITY_STANCE_CHANGE,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_DISGUISE,
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_ICE_FACE,
    ABILITY_GULP_MISSILE,
    ABILITY_ZERO_TO_HERO,
    ABILITY_COMMANDER,
    ABILITY_ZEN_MODE,
    ABILITY_FORECAST,
    ABILITY_FLOWER_GIFT,
    ABILITY_AS_ONE_ICE_RIDER,
    ABILITY_AS_ONE_SHADOW_RIDER,
    ABILITY_NEUTRALIZING_GAS,
};

u16 GetRandomAbilityBySpecies(u16 species, u8 abilityNum)
{
    int i;
    bool8 reroll;
    int counter = 0;

    //DebugPrintf("GetAbilityBySpecies");

#ifdef PIT_GEN_3_MODE
    //exclude hidden abilities
    if(abilityNum == 2)
        abilityNum = 1;
#endif

    do
    {
        reroll = FALSE;

        DebugPrintf("randomAbilities = %d", gSaveBlock2Ptr->randomAbilities);
        //randomize species to determine ability
        if(gSaveBlock2Ptr->randomAbilities == OPTIONS_ON)
        {
            species = GetSpeciesRandomSeeded(species);
            if ((gSpeciesInfo[species].abilities[1] == ABILITY_NONE) && (abilityNum == 1))
                abilityNum = 0;
            DebugPrintf("species = %d", species);
        }

        DebugPrintf("species = %d", species);

        if (abilityNum < NUM_ABILITY_SLOTS)
            gLastUsedAbility = gSpeciesInfo[species].abilities[abilityNum];
        else
            gLastUsedAbility = ABILITY_NONE;

        if (abilityNum >= NUM_NORMAL_ABILITY_SLOTS) // if abilityNum is empty hidden ability, look for other hidden abilities
        {
            for (i = NUM_NORMAL_ABILITY_SLOTS; i < NUM_ABILITY_SLOTS && gLastUsedAbility == ABILITY_NONE; i++)
            {
                gLastUsedAbility = gSpeciesInfo[species].abilities[i];
            }
        }

        for (i = 0; i < NUM_ABILITY_SLOTS && gLastUsedAbility == ABILITY_NONE; i++) // look for any non-empty ability
        {
            gLastUsedAbility = gSpeciesInfo[species].abilities[i];
        }

        //check if ability is valid
        if(gSaveBlock2Ptr->randomAbilities == OPTIONS_ON)
        {
            //DebugPrintf("check for invalid abilities");
            for (i=0; i < INVALID_ABILITIES_COUNT; i++)
            {
                if (gLastUsedAbility == sInvalidRandomAbilities[i])
                {
                    //DebugPrintf("reroll Ability: %d", gLastUsedAbility);
                    reroll = TRUE;
                    i = INVALID_ABILITIES_COUNT;
                }
            }
            // infinite loop protection setting a default ability if nothing is found
            if (counter >= 10)
            {
                reroll = FALSE;
                gLastUsedAbility = ABILITY_TECHNICIAN;
            }

            counter++;
        }
    } while (reroll);

    DebugPrintf("gLastUsedAbility = %d", gLastUsedAbility);
    return gLastUsedAbility;
}



//
//	Type Randomizer
//

#define RANDOM_TYPE_COUNT ARRAY_COUNT(sOneTypeChallengeValidTypes)
static const u8  sOneTypeChallengeValidTypes[RANDOM_MON_TYPES - 2] =
{
    TYPE_NORMAL   ,
    TYPE_FIGHTING ,
    TYPE_FLYING   ,
    TYPE_POISON   ,
    TYPE_GROUND   ,
    TYPE_ROCK     ,
    TYPE_BUG      ,
    TYPE_GHOST    ,
    TYPE_STEEL    ,
    TYPE_FIRE     ,
    TYPE_WATER    ,
    TYPE_GRASS    ,
    TYPE_ELECTRIC ,
    TYPE_PSYCHIC  ,
    TYPE_ICE      ,
    TYPE_DRAGON   ,
    TYPE_DARK     ,
    #if P_UPDATED_TYPES >= GEN_6
        TYPE_FAIRY,
    #endif
};

u8 GetTypeBySpecies(u16 species, u8 typeNum)
{
    u8 type;

    if (typeNum == 1)
        type = gSpeciesInfo[species].types[0];
    else
        type = gSpeciesInfo[species].types[1];

    if (gSaveBlock2Ptr->randomType == OPTIONS_OFF)
        return type;

    type = sOneTypeChallengeValidTypes[RandomSeededModulo2(type + typeNum + species, RANDOM_MON_TYPES - 2) % (RANDOM_MON_TYPES - 2)];
    return type;
}

u8 GetTypeEffectivenessRandom(u8 type)
{
    //if (type == TYPE_NONE)
    //    return TYPE_NONE;
    //
    //if (!gSaveBlock1Ptr->tx_Random_TypeEffectiveness)
    //    return type;
	//
    //return sTypeEffectivenessList[type];
	return TYPE_NONE;
}
