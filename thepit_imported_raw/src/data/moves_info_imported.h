#include "constants/battle_move_effects.h"
#include "constants/moves.h"

// Generated from a FireRed ROM by ExtractFireRedToThePit.hma.
// NOTE: .effect mapping is best-effort (see EFFECT_PLACEHOLDER comments).
// NOTE: gen-3 secondaryEffectChance is emitted as a comment; in expansion
//       it belongs in .additionalEffects = ADDITIONAL_EFFECTS(...).

const struct MoveInfo gMovesInfoImported[] =
{
    [MOVE_UNNAMED] =
    {
        .name = COMPOUND_STRING("-"),
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_000_*
    },
    [MOVE_POUND] =
    {
        .name = COMPOUND_STRING("Pound"),
        .description = COMPOUND_STRING("A physical attack\ndelivered with a\nlong tail or a\nforeleg, etc."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_001_*
    },
    [MOVE_KARATE_CHOP] =
    {
        .name = COMPOUND_STRING("Karate Chop"),
        .description = COMPOUND_STRING("The foe is attacked\nwith a sharp chop.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_002_*
    },
    [MOVE_DOUBLESLAP] =
    {
        .name = COMPOUND_STRING("Doubleslap"),
        .description = COMPOUND_STRING("The foe is slapped\nrepeatedly, back\nand forth, two to\nfive times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_003_*
    },
    [MOVE_BULLET_PUNCH] =
    {
        .name = COMPOUND_STRING("Bullet Punch"),
        .description = COMPOUND_STRING("The user strikes\nwith a tough punch\nthat always goes\nfirst."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_004_*
    },
    [MOVE_MEGA_PUNCH] =
    {
        .name = COMPOUND_STRING("Mega Punch"),
        .description = COMPOUND_STRING("The foe is slugged\nby a punch thrown\nwith muscle-packed\npower."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_005_*
    },
    [MOVE_PAY_DAY] =
    {
        .name = COMPOUND_STRING("Pay Day"),
        .description = COMPOUND_STRING("Numerous coins are\nhurled at the foe.\nMoney is earned\nafter battle."),
        .effect = EFFECT_PAY_DAY,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_006_*
    },
    [MOVE_FIRE_PUNCH] =
    {
        .name = COMPOUND_STRING("Fire Punch"),
        .description = COMPOUND_STRING("The foe is punched\nwith a fiery fist.\nIt may leave the\nfoe with a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_007_*
    },
    [MOVE_ICE_PUNCH] =
    {
        .name = COMPOUND_STRING("Ice Punch"),
        .description = COMPOUND_STRING("The foe is punched\nwith an icy fist.\nIt may leave the\nfoe frozen."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_008_*
    },
    [MOVE_THUNDERPUNCH] =
    {
        .name = COMPOUND_STRING("Thunderpunch"),
        .description = COMPOUND_STRING("The foe is punched\nwith an electrified\nfist. It may leave\nthe foe paralyzed."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_009_*
    },
    [MOVE_SCRATCH] =
    {
        .name = COMPOUND_STRING("Scratch"),
        .description = COMPOUND_STRING("Hard, pointed, and\nsharp claws rake\nthe foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_010_*
    },
    [MOVE_VICEGRIP] =
    {
        .name = COMPOUND_STRING("Vicegrip"),
        .description = COMPOUND_STRING("Huge, impressive\npincers grip and\nsqueeze the foe."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_011_*
    },
    [MOVE_FLARE_BLITZ] =
    {
        .name = COMPOUND_STRING("Flare Blitz"),
        .description = COMPOUND_STRING("The user charges\nat the foe. This\nalso damages the\nuser."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_012_*
    },
    [MOVE_SHADOW_CLAW] =
    {
        .name = COMPOUND_STRING("Shadow Claw"),
        .description = COMPOUND_STRING("The user slashes\nwith a sharp claw\nmade from shadows.\nHigh crit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 70,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_013_*
    },
    [MOVE_SWORDS_DANCE] =
    {
        .name = COMPOUND_STRING("Swords Dance"),
        .description = COMPOUND_STRING("A frenetic dance of\nfighting. It sharply\nraises the Attack\nstat."),
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_014_*
    },
    [MOVE_MEMENTO] =
    {
        .name = COMPOUND_STRING("Memento"),
        .description = COMPOUND_STRING("A basic attack.\nIt can be used to\ncut down thin trees\nand grass."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 168 "SelfKOLowerAttack2SpAttack2" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_015_*
    },
    [MOVE_GUST] =
    {
        .name = COMPOUND_STRING("Gust"),
        .description = COMPOUND_STRING("Strikes the foe\nwith a gust of wind\nwhipped up by\nwings."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 149 "DoubleDamageToFly" - port battle script */,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_016_*
    },
    [MOVE_WING_ATTACK] =
    {
        .name = COMPOUND_STRING("Wing Attack"),
        .description = COMPOUND_STRING("The foe is struck\nwith large, imposing\nwings spread wide."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_017_*
    },
    [MOVE_HURRICANE] =
    {
        .name = COMPOUND_STRING("Hurricane"),
        .description = COMPOUND_STRING("The user attacks\nby wrapping its\nopponent in a\nstrong wind."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 152 "ParalyzeAndIncreaseAccuracyInRain" - port battle script */,
        .power = 110,
        .type = TYPE_FLYING,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_018_*
    },
    [MOVE_FLY] =
    {
        .name = COMPOUND_STRING("Fly"),
        .description = COMPOUND_STRING("The user vanishes,\nthen strikes on the\nnext turn, hitting\neven protected foes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 155 "2turn" - port battle script */,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        // animation + sounds: scripts/move_animations/move_019_*
    },
    [MOVE_BIND] =
    {
        .name = COMPOUND_STRING("Bind"),
        .description = COMPOUND_STRING("A long body or\ntentacles are used\nto bind the foe for\ntwo to five turns."),
        .effect = EFFECT_BIND,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_020_*
    },
    [MOVE_SLAM] =
    {
        .name = COMPOUND_STRING("Slam"),
        .description = COMPOUND_STRING("The foe is struck\nwith a long tail,\nvines, etc."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_021_*
    },
    [MOVE_VINE_WHIP] =
    {
        .name = COMPOUND_STRING("Vine Whip"),
        .description = COMPOUND_STRING("The foe is struck\nwith slender, whip-\nlike vines."),
        .effect = EFFECT_HIT,
        .power = 45,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_022_*
    },
    [MOVE_STOMP] =
    {
        .name = COMPOUND_STRING("Stomp"),
        .description = COMPOUND_STRING("The foe is stomped\nwith a big foot.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 150 "FlinchAndDoubleDamageToMinimize" - port battle script */,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_023_*
    },
    [MOVE_DOUBLE_KICK] =
    {
        .name = COMPOUND_STRING("Double Kick"),
        .description = COMPOUND_STRING("Two legs are used\nto quickly kick the\nfoe twice in one\nturn."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_024_*
    },
    [MOVE_MEGA_KICK] =
    {
        .name = COMPOUND_STRING("Mega Kick"),
        .description = COMPOUND_STRING("The foe is attacked\nby a kick fired\nwith muscle-packed\npower."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_025_*
    },
    [MOVE_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("Jump Kick"),
        .description = COMPOUND_STRING("The user jumps up\nhigh, then kicks.\nIf it misses, the\nuser hurts itself."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_026_*
    },
    [MOVE_ROLLING_KICK] =
    {
        .name = COMPOUND_STRING("Rolling Kick"),
        .description = COMPOUND_STRING("A quick kick from a\nrolling spin.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_027_*
    },
    [MOVE_SAND_ATTACK] =
    {
        .name = COMPOUND_STRING("Sand Attack"),
        .description = COMPOUND_STRING("A lot of sand is\nhurled in the foe's\nface, reducing its\naccuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_028_*
    },
    [MOVE_HEADBUTT] =
    {
        .name = COMPOUND_STRING("Headbutt"),
        .description = COMPOUND_STRING("The user sticks its\nhead out and rams.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_029_*
    },
    [MOVE_HORN_ATTACK] =
    {
        .name = COMPOUND_STRING("Horn Attack"),
        .description = COMPOUND_STRING("The foe is jabbed\nwith a sharply\npointed horn to\ninflict damage."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_030_*
    },
    [MOVE_FURY_ATTACK] =
    {
        .name = COMPOUND_STRING("Fury Attack"),
        .description = COMPOUND_STRING("The foe is jabbed\nrepeatedly with a\nhorn or beak two to\nfive times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_031_*
    },
    [MOVE_DRILL_RUN] =
    {
        .name = COMPOUND_STRING("Drill Run"),
        .description = COMPOUND_STRING("The user rotates\nits body like\na drill. High\ncrit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_032_*
    },
    [MOVE_TACKLE] =
    {
        .name = COMPOUND_STRING("Tackle"),
        .description = COMPOUND_STRING("A physical attack\nin which the user\ncharges, full body,\ninto the foe."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_033_*
    },
    [MOVE_BODY_SLAM] =
    {
        .name = COMPOUND_STRING("Body Slam"),
        .description = COMPOUND_STRING("The user drops its\nfull body on the\nfoe. It may leave\nthe foe paralyzed."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_034_*
    },
    [MOVE_WRAP] =
    {
        .name = COMPOUND_STRING("Wrap"),
        .description = COMPOUND_STRING("A long body or\nvines are used to\nwrap the foe for\ntwo to five turns."),
        .effect = EFFECT_BIND,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_035_*
    },
    [MOVE_TAKE_DOWN] =
    {
        .name = COMPOUND_STRING("Take Down"),
        .description = COMPOUND_STRING("A reckless, full-\nbody charge attack\nthat also hurts the\nuser a little."),
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_036_*
    },
    [MOVE_THRASH] =
    {
        .name = COMPOUND_STRING("Thrash"),
        .description = COMPOUND_STRING("The user rampages\nabout for two to\nthree turns, then\nbecomes confused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 27 "2to3turnsThenConfused" - port battle script */,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_037_*
    },
    [MOVE_DOUBLE_EDGE] =
    {
        .name = COMPOUND_STRING("Double-Edge"),
        .description = COMPOUND_STRING("A reckless, life-\nrisking tackle that\nalso hurts the user\na little."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_038_*
    },
    [MOVE_TAIL_WHIP] =
    {
        .name = COMPOUND_STRING("Tail Whip"),
        .description = COMPOUND_STRING("The user wags its\ntail cutely, making\nthe foe lower its\nDefense stat."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_039_*
    },
    [MOVE_POISON_STING] =
    {
        .name = COMPOUND_STRING("Poison Sting"),
        .description = COMPOUND_STRING("The foe is stabbed\nwith a toxic barb,\netc. It may poison\nthe foe."),
        .effect = EFFECT_POISON_HIT,
        .power = 15,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_040_*
    },
    [MOVE_QUIVER_DANCE] =
    {
        .name = COMPOUND_STRING("Quiver Dance"),
        .description = COMPOUND_STRING("The user dances\nto raise its Sp. Atk,\nSp. Def and\nSpeed stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 211 "RaiseSpAttack1SpDefense1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_041_*
    },
    [MOVE_PIN_MISSILE] =
    {
        .name = COMPOUND_STRING("Pin Missile"),
        .description = COMPOUND_STRING("Sharp pins are shot\nat the foe and hit\ntwo to five times\nat once."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_042_*
    },
    [MOVE_LEER] =
    {
        .name = COMPOUND_STRING("Leer"),
        .description = COMPOUND_STRING("The foe is given an\nintimidating look\nthat lowers its\nDefense stat."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_043_*
    },
    [MOVE_BITE] =
    {
        .name = COMPOUND_STRING("Bite"),
        .description = COMPOUND_STRING("The user bites with\nvicious fangs.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_044_*
    },
    [MOVE_GROWL] =
    {
        .name = COMPOUND_STRING("Growl"),
        .description = COMPOUND_STRING("The user growls in\na cute way, making\nthe foe lower its\nAttack stat."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_045_*
    },
    [MOVE_SNARL] =
    {
        .name = COMPOUND_STRING("Snarl"),
        .description = COMPOUND_STRING("The user yells,\nmaking the target's\nSp. Atk stat\ndecrease."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 71 "LowerSpAttack1HitChance" - port battle script */,
        .power = 55,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_046_*
    },
    [MOVE_SING] =
    {
        .name = COMPOUND_STRING("Sing"),
        .description = COMPOUND_STRING("A soothing song\nin a calming voice\nlulls the foe into\na deep slumber."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_047_*
    },
    [MOVE_SUPERSONIC] =
    {
        .name = COMPOUND_STRING("Supersonic"),
        .description = COMPOUND_STRING("The user generates\nodd sound waves.\nIt may confuse the\nfoe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_048_*
    },
    [MOVE_SONICBOOM] =
    {
        .name = COMPOUND_STRING("Sonicboom"),
        .description = COMPOUND_STRING("The foe is hit with\na shock wave that\nalways inflicts 20-\nHP damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 130 "20Damage" - port battle script */,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_049_*
    },
    [MOVE_DISABLE] =
    {
        .name = COMPOUND_STRING("Disable"),
        .description = COMPOUND_STRING("For a few turns,\nit prevents the foe\nfrom using the move\nit last used."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 86 "Disable" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_050_*
    },
    [MOVE_ACID] =
    {
        .name = COMPOUND_STRING("Acid"),
        .description = COMPOUND_STRING("The foe is sprayed\nwith a harsh, hide-\nmelting acid that\nmay lower Defense."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_051_*
    },
    [MOVE_EMBER] =
    {
        .name = COMPOUND_STRING("Ember"),
        .description = COMPOUND_STRING("The foe is attacked\nwith small flames.\nThe foe may suffer\na burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_052_*
    },
    [MOVE_FLAMETHROWER] =
    {
        .name = COMPOUND_STRING("Flamethrower"),
        .description = COMPOUND_STRING("The foe is scorched\nwith intense flames.\nThe foe may suffer\na burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 95,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_053_*
    },
    [MOVE_MIST] =
    {
        .name = COMPOUND_STRING("Mist"),
        .description = COMPOUND_STRING("The ally party is\nprotected by a\nmist that prevents\nstat reductions."),
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_054_*
    },
    [MOVE_WATER_GUN] =
    {
        .name = COMPOUND_STRING("Water Gun"),
        .description = COMPOUND_STRING("The foe is struck\nwith a lot of water\nexpelled forcibly\nfrom the mouth."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_055_*
    },
    [MOVE_HYDRO_PUMP] =
    {
        .name = COMPOUND_STRING("Hydro Pump"),
        .description = COMPOUND_STRING("A high volume of\nwater is blasted at\nthe foe under great\npressure."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_056_*
    },
    [MOVE_SURF] =
    {
        .name = COMPOUND_STRING("Surf"),
        .description = COMPOUND_STRING("A big wave crashes\ndown on the foe.\nCan also be used\nfor crossing water."),
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_057_*
    },
    [MOVE_ICE_BEAM] =
    {
        .name = COMPOUND_STRING("Ice Beam"),
        .description = COMPOUND_STRING("The foe is struck\nwith an icy beam.\nIt may inflict\nfrostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 95,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_058_*
    },
    [MOVE_BLIZZARD] =
    {
        .name = COMPOUND_STRING("Blizzard"),
        .description = COMPOUND_STRING("The foe is blasted\nwith a blizzard.\nIt may inflict\nfrostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 120,
        .type = TYPE_ICE,
        .accuracy = 70,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_059_*
    },
    [MOVE_PSYBEAM] =
    {
        .name = COMPOUND_STRING("Psybeam"),
        .description = COMPOUND_STRING("A peculiar ray is\nshot at the foe.\nIt may leave the\nfoe confused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_060_*
    },
    [MOVE_BUBBLEBEAM] =
    {
        .name = COMPOUND_STRING("Bubblebeam"),
        .description = COMPOUND_STRING("A spray of bubbles\nstrikes the foe.\nIt may lower the\nfoe's Speed stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 33%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_061_*
    },
    [MOVE_AURORA_BEAM] =
    {
        .name = COMPOUND_STRING("Aurora Beam"),
        .description = COMPOUND_STRING("A rainbow-colored\nattack beam.\nIt may lower the\nfoe's Attack stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 68 "LowerAttack1HitChance" - port battle script */,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_062_*
    },
    [MOVE_HYPER_BEAM] =
    {
        .name = COMPOUND_STRING("Hyper Beam"),
        .description = COMPOUND_STRING("A severely damaging\nattack that makes\nthe user rest on\nthe next turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 80 "SkipNextTurn" - port battle script */,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_063_*
    },
    [MOVE_PECK] =
    {
        .name = COMPOUND_STRING("Peck"),
        .description = COMPOUND_STRING("The foe is jabbed\nwith a sharply\npointed beak or\nhorn."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_064_*
    },
    [MOVE_DRILL_PECK] =
    {
        .name = COMPOUND_STRING("Drill Peck"),
        .description = COMPOUND_STRING("A corkscrewing\nattack with the\nsharp beak acting\nas a drill."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_065_*
    },
    [MOVE_SUBMISSION] =
    {
        .name = COMPOUND_STRING("Submission"),
        .description = COMPOUND_STRING("A reckless, full-\nbody throw attack\nthat also hurts the\nuser a little."),
        .effect = EFFECT_RECOIL,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_066_*
    },
    [MOVE_LOW_KICK] =
    {
        .name = COMPOUND_STRING("Low Kick"),
        .description = COMPOUND_STRING("A low, tripping kick\nthat inflicts more\ndamage on heavier\nfoes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 196 "DamageBasedOnTargetWeight" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_067_*
    },
    [MOVE_COUNTER] =
    {
        .name = COMPOUND_STRING("Counter"),
        .description = COMPOUND_STRING("A retaliation move\nthat counters any\nphysical hit with\ndouble the damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 89 "DoubleBackPhysicalDamage" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_068_*
    },
    [MOVE_SEISMIC_TOSS] =
    {
        .name = COMPOUND_STRING("Seismic Toss"),
        .description = COMPOUND_STRING("A gravity-fed throw\nthat causes damage\nmatching the user's\nlevel."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 87 "DamageBasedOnLevel" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_069_*
    },
    [MOVE_RAGE_FIST] =
    {
        .name = COMPOUND_STRING("Rage Fist"),
        .description = COMPOUND_STRING("Becomes stronger\neach time the user\nis hit in battle\nafter being used."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 81 "RaiseAttack1IfDamaged" - port battle script */,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_070_*
    },
    [MOVE_ABSORB] =
    {
        .name = COMPOUND_STRING("Absorb"),
        .description = COMPOUND_STRING("An attack that\nabsorbs half the\ndamage it inflicted\nto restore HP."),
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_071_*
    },
    [MOVE_MEGA_DRAIN] =
    {
        .name = COMPOUND_STRING("Mega Drain"),
        .description = COMPOUND_STRING("A tough attack that\ndrains half the\ndamage it inflicted\nto restore HP."),
        .effect = EFFECT_ABSORB,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_072_*
    },
    [MOVE_LEECH_SEED] =
    {
        .name = COMPOUND_STRING("Leech Seed"),
        .description = COMPOUND_STRING("A seed is planted\non the foe to steal\nsome HP for the \nuser on every turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 84 "SeedOpponent" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_073_*
    },
    [MOVE_GROWTH] =
    {
        .name = COMPOUND_STRING("Growth"),
        .description = COMPOUND_STRING("The user's body is\nforced to grow,\nraising the Sp.\nAtk stat."),
        .effect = EFFECT_SPECIAL_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_074_*
    },
    [MOVE_RAZOR_LEAF] =
    {
        .name = COMPOUND_STRING("Razor Leaf"),
        .description = COMPOUND_STRING("The foe is hit with\na cutting leaf.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_075_*
    },
    [MOVE_SOLAR_BEAM] =
    {
        .name = COMPOUND_STRING("Solar Beam"),
        .description = COMPOUND_STRING("A 2-turn move that\nblasts the foe with\nabsorbed energy in\nthe 2nd turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 151 "ChargeFirstTurn" - port battle script */,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_076_*
    },
    [MOVE_POISONPOWDER] =
    {
        .name = COMPOUND_STRING("Poisonpowder"),
        .description = COMPOUND_STRING("A cloud of toxic\ndust is scattered.\nIt may poison the\nfoe."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_077_*
    },
    [MOVE_STUN_SPORE] =
    {
        .name = COMPOUND_STRING("Stun Spore"),
        .description = COMPOUND_STRING("Paralyzing dust is\nscattered wildly.\nIt may paralyze\nthe foe."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_078_*
    },
    [MOVE_SLEEP_POWDER] =
    {
        .name = COMPOUND_STRING("Sleep Powder"),
        .description = COMPOUND_STRING("A sleep-inducing\ndust is scattered\nin high volume\naround a foe."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_079_*
    },
    [MOVE_PETAL_DANCE] =
    {
        .name = COMPOUND_STRING("Petal Dance"),
        .description = COMPOUND_STRING("The user attacks\nwith petals for two\nto three turns,\nthen gets confused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 27 "2to3turnsThenConfused" - port battle script */,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_080_*
    },
    [MOVE_STRING_SHOT] =
    {
        .name = COMPOUND_STRING("String Shot"),
        .description = COMPOUND_STRING("The foe is bound\nwith strings shot\nfrom the mouth to\nreduce its Speed."),
        .effect = EFFECT_SPEED_DOWN,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_081_*
    },
    [MOVE_DRAGON_RUSH] =
    {
        .name = COMPOUND_STRING("Dragon Rush"),
        .description = COMPOUND_STRING("The user tackles\nwith menace.\nMay also flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_082_*
    },
    [MOVE_FIRE_SPIN] =
    {
        .name = COMPOUND_STRING("Fire Spin"),
        .description = COMPOUND_STRING("The foe is trapped\nin an intense spiral\nof fire that rages\ntwo to five turns."),
        .effect = EFFECT_BIND,
        .power = 35,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_083_*
    },
    [MOVE_THUNDERSHOCK] =
    {
        .name = COMPOUND_STRING("Thundershock"),
        .description = COMPOUND_STRING("An electric shock\nattack that may\nalso leave the foe\nparalyzed."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_084_*
    },
    [MOVE_THUNDERBOLT] =
    {
        .name = COMPOUND_STRING("Thunderbolt"),
        .description = COMPOUND_STRING("A strong electrical\nattack that may\nalso leave the foe\nparalyzed."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 95,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_085_*
    },
    [MOVE_THUNDER_WAVE] =
    {
        .name = COMPOUND_STRING("Thunder Wave"),
        .description = COMPOUND_STRING("A weak electric\nshock that is sure\nto cause paralysis\nif it hits."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_086_*
    },
    [MOVE_THUNDER] =
    {
        .name = COMPOUND_STRING("Thunder"),
        .description = COMPOUND_STRING("A brutal lightning\nattack that may\nalso leave the foe\nparalyzed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 152 "ParalyzeAndIncreaseAccuracyInRain" - port battle script */,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_087_*
    },
    [MOVE_ROCK_THROW] =
    {
        .name = COMPOUND_STRING("Rock Throw"),
        .description = COMPOUND_STRING("The foe is attacked\nwith a shower of\nsmall, easily\nthrown rocks."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_088_*
    },
    [MOVE_EARTHQUAKE] =
    {
        .name = COMPOUND_STRING("Earthquake"),
        .description = COMPOUND_STRING("An earthquake that\nstrikes all Pokémon\nin battle excluding\nthe user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 147 "DoubleDamageToDig" - port battle script */,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_089_*
    },
    [MOVE_EARTH_POWER] =
    {
        .name = COMPOUND_STRING("Earth Power"),
        .description = COMPOUND_STRING("Powerful eruption\nthat may lower\nthe target's\nSp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_090_*
    },
    [MOVE_DIG] =
    {
        .name = COMPOUND_STRING("Dig"),
        .description = COMPOUND_STRING("An attack that hits\non the 2nd turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 155 "2turn" - port battle script */,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_091_*
    },
    [MOVE_TOXIC] =
    {
        .name = COMPOUND_STRING("Toxic"),
        .description = COMPOUND_STRING("A move that badly\npoisons the foe.\nIts poison damage\nworsens every turn."),
        .effect = EFFECT_TOXIC,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_092_*
    },
    [MOVE_CONFUSION] =
    {
        .name = COMPOUND_STRING("Confusion"),
        .description = COMPOUND_STRING("A weak telekinetic\nattack that may\nalso leave the foe\nconfused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_093_*
    },
    [MOVE_PSYCHIC] =
    {
        .name = COMPOUND_STRING("Psychic"),
        .description = COMPOUND_STRING("A strong telekinetic\nattack. It may also\nlower the foe's\nSp. Def stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_094_*
    },
    [MOVE_HYPNOSIS] =
    {
        .name = COMPOUND_STRING("Hypnosis"),
        .description = COMPOUND_STRING("Hypnotic suggestion\nis used to make the\nfoe fall into a\ndeep sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 70,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_095_*
    },
    [MOVE_MEDITATE] =
    {
        .name = COMPOUND_STRING("Meditate"),
        .description = COMPOUND_STRING("The user meditates\nto awaken its power\nand raise its\nAttack stat."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_096_*
    },
    [MOVE_AGILITY] =
    {
        .name = COMPOUND_STRING("Agility"),
        .description = COMPOUND_STRING("The user relaxes\nand lightens its\nbody to sharply\nboost its Speed."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_097_*
    },
    [MOVE_QUICK_ATTACK] =
    {
        .name = COMPOUND_STRING("Quick Attack"),
        .description = COMPOUND_STRING("An almost invisibly\nfast attack that\nis certain to strike\nfirst."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_098_*
    },
    [MOVE_RAGE] =
    {
        .name = COMPOUND_STRING("Rage"),
        .description = COMPOUND_STRING("An attack that\nbecomes stronger\neach time the user\nis hit in battle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 139 "RaiseAttack1HitChance" - port battle script */,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_099_*
    },
    [MOVE_TELEPORT] =
    {
        .name = COMPOUND_STRING("Teleport"),
        .description = COMPOUND_STRING("Use it to flee from\nany wild POKéMON.\nAlso warps to the\nlast POKé CENTER."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 153 "Escape" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_100_*
    },
    [MOVE_NIGHT_SHADE] =
    {
        .name = COMPOUND_STRING("Night Shade"),
        .description = COMPOUND_STRING("An attack with a\nmirage that inflicts\ndamage matching\nthe user's level."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 87 "DamageBasedOnLevel" - port battle script */,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_101_*
    },
    [MOVE_MIMIC] =
    {
        .name = COMPOUND_STRING("Mimic"),
        .description = COMPOUND_STRING("The user copies the\nmove last used by\nthe foe for the\nrest of the battle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 82 "Mimic" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_102_*
    },
    [MOVE_SCREECH] =
    {
        .name = COMPOUND_STRING("Screech"),
        .description = COMPOUND_STRING("An ear-splitting\nscreech is emitted\nto sharply reduce\nthe foe's Defense."),
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_103_*
    },
    [MOVE_DOUBLE_TEAM] =
    {
        .name = COMPOUND_STRING("Double Team"),
        .description = COMPOUND_STRING("The user creates\nillusory copies of\nitself to raise its\nevasiveness."),
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_104_*
    },
    [MOVE_RECOVER] =
    {
        .name = COMPOUND_STRING("Recover"),
        .description = COMPOUND_STRING("A self-healing move\nthat restores HP by\nup to half of the\nuser's maximum HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_105_*
    },
    [MOVE_HARDEN] =
    {
        .name = COMPOUND_STRING("Harden"),
        .description = COMPOUND_STRING("The user stiffens\nall the muscles in\nits body to raise\nits Defense stat."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_106_*
    },
    [MOVE_MINIMIZE] =
    {
        .name = COMPOUND_STRING("Minimize"),
        .description = COMPOUND_STRING("The user compresses\nall the cells in its\nbody to raise its\nevasiveness."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 108 "RaiseEvasivenessAndBecomeSmaller" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_107_*
    },
    [MOVE_SMOKESCREEN] =
    {
        .name = COMPOUND_STRING("Smokescreen"),
        .description = COMPOUND_STRING("An obscuring cloud\nof smoke or ink\nreduces the foe's\naccuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_108_*
    },
    [MOVE_CONFUSE_RAY] =
    {
        .name = COMPOUND_STRING("Confuse Ray"),
        .description = COMPOUND_STRING("The foe is exposed\nto a sinister ray\nthat triggers\nconfusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_109_*
    },
    [MOVE_WITHDRAW] =
    {
        .name = COMPOUND_STRING("Withdraw"),
        .description = COMPOUND_STRING("The user withdraws\nits body in its hard\nshell, raising its\nDefense stat."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_110_*
    },
    [MOVE_DEFENSE_CURL] =
    {
        .name = COMPOUND_STRING("Defense Curl"),
        .description = COMPOUND_STRING("The user curls up\nto conceal weak\nspots and raise its\nDefense stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 156 "RaiseDefenseAndImproveRollingMoves" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_111_*
    },
    [MOVE_BARRIER] =
    {
        .name = COMPOUND_STRING("Barrier"),
        .description = COMPOUND_STRING("The user creates a\nsturdy wall that\nsharply raises its\nDefense stat."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_112_*
    },
    [MOVE_LIGHT_SCREEN] =
    {
        .name = COMPOUND_STRING("Light Screen"),
        .description = COMPOUND_STRING("A wall of light\ncuts damage from\nSp. Atk attacks\nfor five turns."),
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_113_*
    },
    [MOVE_HAZE] =
    {
        .name = COMPOUND_STRING("Haze"),
        .description = COMPOUND_STRING("Eliminates all stat\nchanges among all\nPokémon engaged in\nbattle."),
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_114_*
    },
    [MOVE_REFLECT] =
    {
        .name = COMPOUND_STRING("Reflect"),
        .description = COMPOUND_STRING("A wall of light\ncuts damage from\nphysical attacks\nfor five turns."),
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_115_*
    },
    [MOVE_FOCUS_ENERGY] =
    {
        .name = COMPOUND_STRING("Focus Energy"),
        .description = COMPOUND_STRING("The user takes a\ndeep breath and\nfocuses to raise its\ncritical-hit ratio."),
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_116_*
    },
    [MOVE_BIDE] =
    {
        .name = COMPOUND_STRING("Bide"),
        .description = COMPOUND_STRING("The user endures\nattacks for two\nturns, then strikes\nback double."),
        .effect = EFFECT_BIDE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_117_*
    },
    [MOVE_METRONOME] =
    {
        .name = COMPOUND_STRING("Metronome"),
        .description = COMPOUND_STRING("Waggles a finger\nand stimulates the\nbrain into using any\nmove at random."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 83 "RandomMove" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_118_*
    },
    [MOVE_MIRROR_MOVE] =
    {
        .name = COMPOUND_STRING("Mirror Move"),
        .description = COMPOUND_STRING("The user counters\nthe move last used\nby the foe with the\nsame move."),
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_119_*
    },
    [MOVE_SELFDESTRUCT] =
    {
        .name = COMPOUND_STRING("Selfdestruct"),
        .description = COMPOUND_STRING("The user blows up\nto inflict severe\ndamage, even\nmaking itself faint."),
        .effect = EFFECT_EXPLOSION,
        .power = 200,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_120_*
    },
    [MOVE_EGG_BOMB] =
    {
        .name = COMPOUND_STRING("Egg Bomb"),
        .description = COMPOUND_STRING("A large egg is\nhurled with great\nforce at the foe to\ninflict damage."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_121_*
    },
    [MOVE_LICK] =
    {
        .name = COMPOUND_STRING("Lick"),
        .description = COMPOUND_STRING("The foe is licked\nand hit with a long\ntongue. It may\nalso paralyze."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_122_*
    },
    [MOVE_SMOG] =
    {
        .name = COMPOUND_STRING("Smog"),
        .description = COMPOUND_STRING("The foe is attacked\nwith exhaust gases.\nIt may also poison\nthe foe."),
        .effect = EFFECT_POISON_HIT,
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 40%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_123_*
    },
    [MOVE_SLUDGE] =
    {
        .name = COMPOUND_STRING("Sludge"),
        .description = COMPOUND_STRING("Toxic sludge is\nhurled at the foe.\nIt may poison the\ntarget."),
        .effect = EFFECT_POISON_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_124_*
    },
    [MOVE_BONE_CLUB] =
    {
        .name = COMPOUND_STRING("Bone Club"),
        .description = COMPOUND_STRING("The foe is clubbed\nwith a bone held in\nhand. It may make\nthe foe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_125_*
    },
    [MOVE_FIRE_BLAST] =
    {
        .name = COMPOUND_STRING("Fire Blast"),
        .description = COMPOUND_STRING("The foe is hit with\nan intense flame.\nIt may leave the\ntarget with a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_126_*
    },
    [MOVE_WATERFALL] =
    {
        .name = COMPOUND_STRING("Waterfall"),
        .description = COMPOUND_STRING("A powerful charge\nattack.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_127_*
    },
    [MOVE_CLAMP] =
    {
        .name = COMPOUND_STRING("Clamp"),
        .description = COMPOUND_STRING("The foe is clamped\nand squeezed by\nthe user's shell for\ntwo to five turns."),
        .effect = EFFECT_BIND,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_128_*
    },
    [MOVE_SWIFT] =
    {
        .name = COMPOUND_STRING("Swift"),
        .description = COMPOUND_STRING("Star-shaped rays\nthat never miss are\nfired at all foes in\nbattle."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_129_*
    },
    [MOVE_ZEN_HEADBUTT] =
    {
        .name = COMPOUND_STRING("Zen Headbutt"),
        .description = COMPOUND_STRING("The user rams at\nthe foe. It may\nalso make the\ntarget flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_130_*
    },
    [MOVE_ELECTROSHOCK] =
    {
        .name = COMPOUND_STRING("Electroshock"),
        .description = COMPOUND_STRING("A flare of\nelectricity\nthat may burn\nthe opponent."),
        .effect = EFFECT_BURN_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_131_*
    },
    [MOVE_CONSTRICT] =
    {
        .name = COMPOUND_STRING("Constrict"),
        .description = COMPOUND_STRING("The foe is attacked\nwith long tentacles\nor vines. It may\nlower Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_132_*
    },
    [MOVE_AMNESIA] =
    {
        .name = COMPOUND_STRING("Amnesia"),
        .description = COMPOUND_STRING("Forgets about\nsomething and\nsharply raises\nSp. Def."),
        .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_133_*
    },
    [MOVE_AURA_SPHERE] =
    {
        .name = COMPOUND_STRING("Aura Sphere"),
        .description = COMPOUND_STRING("The user looses\na blast of aura\npower that can't\nmiss its opponent."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_134_*
    },
    [MOVE_SOFTBOILED] =
    {
        .name = COMPOUND_STRING("Softboiled"),
        .description = COMPOUND_STRING("Heals the user by\nup to half its\nfull HP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 157 "RestoreHPOrAllyInField" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_135_*
    },
    [MOVE_HI_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("Hi Jump Kick"),
        .description = COMPOUND_STRING("A strong jumping\nknee kick. If it\nmisses, the user is\nhurt."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 130,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_136_*
    },
    [MOVE_GLARE] =
    {
        .name = COMPOUND_STRING("Glare"),
        .description = COMPOUND_STRING("The user intimidates\nthe foe with the\ndesign on its belly\nto cause paralysis."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_137_*
    },
    [MOVE_DREAM_EATER] =
    {
        .name = COMPOUND_STRING("Dream Eater"),
        .description = COMPOUND_STRING("Absorbs half the\ndamage it inflicted\non a sleeping foe\nto restore HP."),
        .effect = EFFECT_DREAM_EATER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_138_*
    },
    [MOVE_POISON_GAS] =
    {
        .name = COMPOUND_STRING("Poison Gas"),
        .description = COMPOUND_STRING("The foe is sprayed\nwith a cloud of\ntoxic gas that may\npoison the foe."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_139_*
    },
    [MOVE_BUG_BUZZ] =
    {
        .name = COMPOUND_STRING("Bug Buzz"),
        .description = COMPOUND_STRING("A damaging sound\nwave that may\nlower the target's\nSp. Def stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_140_*
    },
    [MOVE_LEECH_LIFE] =
    {
        .name = COMPOUND_STRING("Leech Life"),
        .description = COMPOUND_STRING("An attack that\nabsorbs half the\ndamage it inflicted\nto restore HP."),
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_141_*
    },
    [MOVE_LOVELY_KISS] =
    {
        .name = COMPOUND_STRING("Lovely Kiss"),
        .description = COMPOUND_STRING("The user forces a\nkiss on the foe\nwith a scary face\nthat induces sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_142_*
    },
    [MOVE_BRAVE_BIRD] =
    {
        .name = COMPOUND_STRING("Brave Bird"),
        .description = COMPOUND_STRING("The user tucks in\nits wings and\ncharges the enemy.\nAlso causes recoil."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_143_*
    },
    [MOVE_ABYSS_MIASMA] =
    {
        .name = COMPOUND_STRING("Abyss Miasma"),
        .description = COMPOUND_STRING("A wave of miasma\nhits the opponent.\nMay also lower\nthe target Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 95,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_144_*
    },
    [MOVE_AQUA_JET] =
    {
        .name = COMPOUND_STRING("Aqua Jet"),
        .description = COMPOUND_STRING("The user lunges\nat the target.\nAlways goes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_145_*
    },
    [MOVE_DIZZY_PUNCH] =
    {
        .name = COMPOUND_STRING("Dizzy Punch"),
        .description = COMPOUND_STRING("The foe is hit with\na rhythmic punch\nthat may leave it\nconfused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_146_*
    },
    [MOVE_SPORE] =
    {
        .name = COMPOUND_STRING("Spore"),
        .description = COMPOUND_STRING("The user scatters\nbursts of fine\nspores that induce\nsleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_147_*
    },
    [MOVE_MET_ASSAULT] =
    {
        .name = COMPOUND_STRING("Met. Assault"),
        .description = COMPOUND_STRING("Attack with a thick\nleek that makes the\nuser rest during\nits next turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 80 "SkipNextTurn" - port battle script */,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_148_*
    },
    [MOVE_DARK_PULSE] =
    {
        .name = COMPOUND_STRING("Dark Pulse"),
        .description = COMPOUND_STRING("The user releases\na horrible aura.\nMay also make\nthe target flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_149_*
    },
    [MOVE_SPLASH] =
    {
        .name = COMPOUND_STRING("Splash"),
        .description = COMPOUND_STRING("The user just flops\nand splashes around\nwithout having any\neffect."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 85 "Splash" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_150_*
    },
    [MOVE_ACID_ARMOR] =
    {
        .name = COMPOUND_STRING("Acid Armor"),
        .description = COMPOUND_STRING("The user alters its\ncells to liquefy\nitself and sharply\nraise Defense."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_151_*
    },
    [MOVE_CRABHAMMER] =
    {
        .name = COMPOUND_STRING("Crabhammer"),
        .description = COMPOUND_STRING("A large pincer is\nused to hammer the\nfoe. It has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_152_*
    },
    [MOVE_EXPLOSION] =
    {
        .name = COMPOUND_STRING("Explosion"),
        .description = COMPOUND_STRING("The user explodes\nto inflict terrible\ndamage even while\nfainting itself."),
        .effect = EFFECT_EXPLOSION,
        .power = 250,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_153_*
    },
    [MOVE_FURY_SWIPES] =
    {
        .name = COMPOUND_STRING("Fury Swipes"),
        .description = COMPOUND_STRING("The foe is raked\nwith sharp claws or\nscythes two to five\ntimes."),
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_154_*
    },
    [MOVE_BONEMERANG] =
    {
        .name = COMPOUND_STRING("Bonemerang"),
        .description = COMPOUND_STRING("The user throws a\nbone that hits the\nfoe once, then once\nagain on return."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 50,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_155_*
    },
    [MOVE_REST] =
    {
        .name = COMPOUND_STRING("Rest"),
        .description = COMPOUND_STRING("The user sleeps for\ntwo turns to fully\nrestore HP and heal\nany status problem."),
        .effect = EFFECT_REST,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_156_*
    },
    [MOVE_ROCK_SLIDE] =
    {
        .name = COMPOUND_STRING("Rock Slide"),
        .description = COMPOUND_STRING("Large boulders are\nhurled at the foe.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_157_*
    },
    [MOVE_HYPER_FANG] =
    {
        .name = COMPOUND_STRING("Hyper Fang"),
        .description = COMPOUND_STRING("The foe is attacked\nwith sharp fangs.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_158_*
    },
    [MOVE_FLASH_CANNON] =
    {
        .name = COMPOUND_STRING("Flash Cannon"),
        .description = COMPOUND_STRING("Light energy is\nreleased at once.\nMay also lower\nthe target Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_159_*
    },
    [MOVE_HEAL] =
    {
        .name = COMPOUND_STRING("Heal"),
        .description = COMPOUND_STRING("The user\nrestores 50%\nof its target's\nMax health."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 157 "RestoreHPOrAllyInField" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_160_*
    },
    [MOVE_TRI_ATTACK] =
    {
        .name = COMPOUND_STRING("Tri Attack"),
        .description = COMPOUND_STRING("A simultaneous\n3-beam attack that\nmay paralyze, burn,\nor freeze the foe."),
        .effect = EFFECT_TRI_ATTACK,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_161_*
    },
    [MOVE_SUPER_FANG] =
    {
        .name = COMPOUND_STRING("Super Fang"),
        .description = COMPOUND_STRING("The user attacks\nwith sharp fangs\nand halves the\nfoe's HP."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_162_*
    },
    [MOVE_SLASH] =
    {
        .name = COMPOUND_STRING("Slash"),
        .description = COMPOUND_STRING("The foe is slashed\nwith claws, etc.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_163_*
    },
    [MOVE_SUBSTITUTE] =
    {
        .name = COMPOUND_STRING("Substitute"),
        .description = COMPOUND_STRING("The user creates a\ndecoy using one-\nquarter of its full\nHP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 79 "Substitute" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_164_*
    },
    [MOVE_STRUGGLE] =
    {
        .name = COMPOUND_STRING("Struggle"),
        .description = COMPOUND_STRING("An attack that is\nused only if there\nis no PP. It also\nhurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_165_*
    },
    [MOVE_ABYSS_WRATH] =
    {
        .name = COMPOUND_STRING("Abyss Wrath"),
        .description = COMPOUND_STRING("A retaliation move\nthat counters any\nhit with double\nthe damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 89 "DoubleBackPhysicalDamage" - port battle script */,
        .power = 1,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_166_*
    },
    [MOVE_TRIPLE_KICK] =
    {
        .name = COMPOUND_STRING("Triple Kick"),
        .description = COMPOUND_STRING("A 3-kick attack\nthat becomes more\npowerful with each\nsuccessive hit."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 104 "3turnTripleHit" - port battle script */,
        .power = 20,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_167_*
    },
    [MOVE_THIEF] =
    {
        .name = COMPOUND_STRING("Thief"),
        .description = COMPOUND_STRING("An attack that may\ntake the foe's held\nitem if the user\nisn't holding one."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 105 "StealItem" - port battle script */,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_168_*
    },
    [MOVE_ELECTROWEB] =
    {
        .name = COMPOUND_STRING("Electroweb"),
        .description = COMPOUND_STRING("The user attacks\nwith an electric\nnet. Also lowers\nthe Speed stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 55,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_169_*
    },
    [MOVE_MIND_READER] =
    {
        .name = COMPOUND_STRING("Mind Reader"),
        .description = COMPOUND_STRING("The user predicts\nthe foe's action to\nensure its next\nattack hits."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 94 "NextAttackHits" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_170_*
    },
    [MOVE_NIGHTMARE] =
    {
        .name = COMPOUND_STRING("Nightmare"),
        .description = COMPOUND_STRING("A sleeping foe is\nshown a nightmare\nthat inflicts some\ndamage every turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 107 "Nightmare" - port battle script */,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_171_*
    },
    [MOVE_FLAME_WHEEL] =
    {
        .name = COMPOUND_STRING("Flame Wheel"),
        .description = COMPOUND_STRING("The user makes a\nfiery charge at the\nfoe. It may cause\na burn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 125 "BurnDefrost" - port battle script */,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_172_*
    },
    [MOVE_SNORE] =
    {
        .name = COMPOUND_STRING("Snore"),
        .description = COMPOUND_STRING("An attack that can\nbe used only while\nasleep. It may\ncause flinching."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 92 "WhileSleepingAndFlinch" - port battle script */,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_173_*
    },
    [MOVE_CURSE] =
    {
        .name = COMPOUND_STRING("Curse"),
        .description = COMPOUND_STRING("A move that works\ndifferently for the\nGhost-type and all\nthe other types."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 109 "Curse" - port battle script */,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_174_*
    },
    [MOVE_FLAIL] =
    {
        .name = COMPOUND_STRING("Flail"),
        .description = COMPOUND_STRING("A desperate attack\nthat becomes more\npowerful the less\nHP the user has."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 99 "StrengthDependsOnHealth" - port battle script */,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_175_*
    },
    [MOVE_CONVERSION_2] =
    {
        .name = COMPOUND_STRING("Conversion 2"),
        .description = COMPOUND_STRING("The user changes\ntype to make itself\nresistant to the\nlast attack it took."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 93 "ChangeTypeToResistPreviousHit" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_176_*
    },
    [MOVE_AEROBLAST] =
    {
        .name = COMPOUND_STRING("Aeroblast"),
        .description = COMPOUND_STRING("A vortex of air is\nshot at the foe.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_177_*
    },
    [MOVE_COTTONSPORE] =
    {
        .name = COMPOUND_STRING("Cottonspore"),
        .description = COMPOUND_STRING("Cotton-like spores\ncling to the foe,\nsharply reducing\nits Speed stat."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_178_*
    },
    [MOVE_REVERSAL] =
    {
        .name = COMPOUND_STRING("Reversal"),
        .description = COMPOUND_STRING("An all-out attack\nthat becomes more\npowerful the less\nHP the user has."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 99 "StrengthDependsOnHealth" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_179_*
    },
    [MOVE_HEX] =
    {
        .name = COMPOUND_STRING("Hex"),
        .description = COMPOUND_STRING("An attack that does\ndouble damage to a\ntarget affected by\na status problem."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 220 "220" - port battle script */,
        .power = 65,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_180_*
    },
    [MOVE_POWDER_SNOW] =
    {
        .name = COMPOUND_STRING("Powder Snow"),
        .description = COMPOUND_STRING("Blasts the foe with\na snowy gust.\nIt may cause\nfrostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_181_*
    },
    [MOVE_PROTECT] =
    {
        .name = COMPOUND_STRING("Protect"),
        .description = COMPOUND_STRING("Enables the user to\nevade all attacks.\nIt may fail if used\nin succession."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 111 "EvadeNextAttack" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_182_*
    },
    [MOVE_MACH_PUNCH] =
    {
        .name = COMPOUND_STRING("Mach Punch"),
        .description = COMPOUND_STRING("A punch thrown at\nblinding speed.\nIt is certain to\nstrike first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_183_*
    },
    [MOVE_SCARY_FACE] =
    {
        .name = COMPOUND_STRING("Scary Face"),
        .description = COMPOUND_STRING("Frightens the foe\nwith a scary face\nto sharply reduce\nits Speed."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_184_*
    },
    [MOVE_FEINT_ATTACK] =
    {
        .name = COMPOUND_STRING("Feint Attack"),
        .description = COMPOUND_STRING("The user draws up\nclose to the foe\ndisarmingly, then\nhits without fail."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_185_*
    },
    [MOVE_SWEET_KISS] =
    {
        .name = COMPOUND_STRING("Sweet Kiss"),
        .description = COMPOUND_STRING("The user kisses\nthe foe with sweet\ncuteness that\ncauses confusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_186_*
    },
    [MOVE_BELLY_DRUM] =
    {
        .name = COMPOUND_STRING("Belly Drum"),
        .description = COMPOUND_STRING("The user maximizes\nits Attack stat at\nthe cost of half\nits full HP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 142 "HalfHealthToRaiseAttackMax" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_187_*
    },
    [MOVE_SLUDGE_BOMB] =
    {
        .name = COMPOUND_STRING("Sludge Bomb"),
        .description = COMPOUND_STRING("Filthy sludge is\nhurled at the foe.\nIt may poison the\ntarget."),
        .effect = EFFECT_POISON_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_188_*
    },
    [MOVE_MUD_SLAP] =
    {
        .name = COMPOUND_STRING("Mud Slap"),
        .description = COMPOUND_STRING("Mud is hurled in\nthe foe's face to\ninflict damage and\nlower its accuracy."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 73 "LowerAccuracy1HitChance" - port battle script */,
        .power = 20,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_189_*
    },
    [MOVE_OCTAZOOKA] =
    {
        .name = COMPOUND_STRING("Octazooka"),
        .description = COMPOUND_STRING("Ink is blasted in\nthe foe's face to\nmake it flinch. Works\nonly on turn 1."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 158 "MoveFirstFlinchOnlyWorksTurn1" - port battle script */,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_190_*
    },
    [MOVE_SPIKES] =
    {
        .name = COMPOUND_STRING("Spikes"),
        .description = COMPOUND_STRING("A trap of spikes is\nlaid around the\nfoe's party to hurt\nfoes switching in."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 112 "Spikes" - port battle script */,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_191_*
    },
    [MOVE_ZAP_CANNON] =
    {
        .name = COMPOUND_STRING("Zap Cannon"),
        .description = COMPOUND_STRING("An electric blast is\nfired like a cannon\nto inflict damage\nand paralyze."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_192_*
    },
    [MOVE_ICE_SHARD] =
    {
        .name = COMPOUND_STRING("Ice Shard"),
        .description = COMPOUND_STRING("The user hurls\nchunks of ice\nat the target.\nAlways goes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_193_*
    },
    [MOVE_SHADOW_SNEAK] =
    {
        .name = COMPOUND_STRING("Shadow Sneak"),
        .description = COMPOUND_STRING("The user extends\nits shadow and\nattacks.\nAlways goes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 40,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_194_*
    },
    [MOVE_DRAGON_PULSE] =
    {
        .name = COMPOUND_STRING("Dragon Pulse"),
        .description = COMPOUND_STRING("The foe is attacked\nwith a shock wave\ngenerated by the\nuser's gaping mouth."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_195_*
    },
    [MOVE_ICY_WIND] =
    {
        .name = COMPOUND_STRING("Icy Wind"),
        .description = COMPOUND_STRING("A chilling wind is\nused to attack.\nIt also lowers the\nSpeed stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 55,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_196_*
    },
    [MOVE_DETECT] =
    {
        .name = COMPOUND_STRING("Detect"),
        .description = COMPOUND_STRING("Enables the user to\nevade all attacks.\nIt may fail if used\nin succession."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 111 "EvadeNextAttack" - port battle script */,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_197_*
    },
    [MOVE_BONE_RUSH] =
    {
        .name = COMPOUND_STRING("Bone Rush"),
        .description = COMPOUND_STRING("The user strikes\nthe foe with a bone\nin hand two to five\ntimes."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_198_*
    },
    [MOVE_LOCK_ON] =
    {
        .name = COMPOUND_STRING("Lock-On"),
        .description = COMPOUND_STRING("The user locks on\nto the foe, making\nthe next move sure\nto hit."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 94 "NextAttackHits" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_199_*
    },
    [MOVE_OUTRAGE] =
    {
        .name = COMPOUND_STRING("Outrage"),
        .description = COMPOUND_STRING("The user thrashes\nabout for two to\nthree turns, then\nbecomes confused."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 27 "2to3turnsThenConfused" - port battle script */,
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_200_*
    },
    [MOVE_SANDSTORM] =
    {
        .name = COMPOUND_STRING("Sandstorm"),
        .description = COMPOUND_STRING("A 5-turn sandstorm\nthat damages all\ntypes except Rock,\nGround, and Steel."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 115 "Sand5Turns" - port battle script */,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_201_*
    },
    [MOVE_GIGA_DRAIN] =
    {
        .name = COMPOUND_STRING("Giga Drain"),
        .description = COMPOUND_STRING("A harsh attack that\nabsorbs half the\ndamage it inflicted\nto restore HP."),
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_202_*
    },
    [MOVE_ENDURE] =
    {
        .name = COMPOUND_STRING("Endure"),
        .description = COMPOUND_STRING("The user endures\nany hit with 1 HP\nleft. It may fail if\nused in succession."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 116 "Endure" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_203_*
    },
    [MOVE_CHARM] =
    {
        .name = COMPOUND_STRING("Charm"),
        .description = COMPOUND_STRING("The foe is charmed\nby the user's cute\nappeals, sharply\ncutting its Attack."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_204_*
    },
    [MOVE_ROLLOUT] =
    {
        .name = COMPOUND_STRING("Rollout"),
        .description = COMPOUND_STRING("A 5-turn rolling\nattack that becomes\nstronger each time\nit hits."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 117 "5turnsUntilMiss" - port battle script */,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_205_*
    },
    [MOVE_FALSE_SWIPE] =
    {
        .name = COMPOUND_STRING("False Swipe"),
        .description = COMPOUND_STRING("A restrained attack\nthat always leaves\nthe foe with at\nleast 1 HP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 101 "NeverKOTarget" - port battle script */,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_206_*
    },
    [MOVE_SWAGGER] =
    {
        .name = COMPOUND_STRING("Swagger"),
        .description = COMPOUND_STRING("A move that makes\nthe foe confused,\nbut also sharply\nraises its Attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 118 "ConfuseAndRaiseAttack2" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_207_*
    },
    [MOVE_MILK_DRINK] =
    {
        .name = COMPOUND_STRING("Milk Drink"),
        .description = COMPOUND_STRING("Heals the user by\nup to half its full\nHP. It can be used\nto heal an ally."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 157 "RestoreHPOrAllyInField" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_208_*
    },
    [MOVE_SPARK] =
    {
        .name = COMPOUND_STRING("Spark"),
        .description = COMPOUND_STRING("An electrically\ncharged tackle that\nmay also paralyze\nthe foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_209_*
    },
    [MOVE_FURY_CUTTER] =
    {
        .name = COMPOUND_STRING("Fury Cutter"),
        .description = COMPOUND_STRING("An attack that\ngrows stronger on\neach successive\nhit."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 119 "GetStrongerEachHit" - port battle script */,
        .power = 40,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_210_*
    },
    [MOVE_STEEL_WING] =
    {
        .name = COMPOUND_STRING("Steel Wing"),
        .description = COMPOUND_STRING("The foe is hit with\nwings of steel.\nIt may also raise\nthe user's Defense."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 138 "RaiseDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_211_*
    },
    [MOVE_DRAIN_PUNCH] =
    {
        .name = COMPOUND_STRING("Drain Punch"),
        .description = COMPOUND_STRING("The user attacks\nwith a draining\npunch, restoring\nits HP."),
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_212_*
    },
    [MOVE_ATTRACT] =
    {
        .name = COMPOUND_STRING("Attract"),
        .description = COMPOUND_STRING("If it is the other\ngender, the foe is\nmade infatuated and\nunlikely to attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 120 "Attract" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_213_*
    },
    [MOVE_SLEEP_TALK] =
    {
        .name = COMPOUND_STRING("Sleep Talk"),
        .description = COMPOUND_STRING("While asleep, the\nuser randomly uses\none of the moves it\nknows."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 97 "SleepTalk" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_214_*
    },
    [MOVE_HEAL_BELL] =
    {
        .name = COMPOUND_STRING("Heal Bell"),
        .description = COMPOUND_STRING("A soothing bell\nchimes to heal the\nstatus problems of\nall allies."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 102 "HealPartyStatus" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_215_*
    },
    [MOVE_RETURN] =
    {
        .name = COMPOUND_STRING("Return"),
        .description = COMPOUND_STRING("This attack move\ngrows more powerful\nthe more the user\nlikes its Trainer."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 121 "StrongerWithFriendship" - port battle script */,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_216_*
    },
    [MOVE_BULLDOZE] =
    {
        .name = COMPOUND_STRING("Bulldoze"),
        .description = COMPOUND_STRING("The user stomps\ndown on the ground\nlowering the Speed\nstat of those hit."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_217_*
    },
    [MOVE_FRUSTRATION] =
    {
        .name = COMPOUND_STRING("Frustration"),
        .description = COMPOUND_STRING("This attack move\ngrows more powerful\nthe less the user\nlikes its Trainer."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 123 "WeakerWithFriendship" - port battle script */,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_218_*
    },
    [MOVE_SAFEGUARD] =
    {
        .name = COMPOUND_STRING("Safeguard"),
        .description = COMPOUND_STRING("It protects the\nuser's party from\nall status problems\nfor five turns."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 124 "PreventStatus5Turns" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_219_*
    },
    [MOVE_PAIN_SPLIT] =
    {
        .name = COMPOUND_STRING("Pain Split"),
        .description = COMPOUND_STRING("The user adds its\nHP to the foe's HP,\nthen equally shares\nthe total HP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 91 "PainSplit" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_220_*
    },
    [MOVE_SACRED_FIRE] =
    {
        .name = COMPOUND_STRING("Sacred Fire"),
        .description = COMPOUND_STRING("A mystical and\npowerful fire\nattack that may\ninflict a burn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 125 "BurnDefrost" - port battle script */,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_221_*
    },
    [MOVE_MAGNITUDE] =
    {
        .name = COMPOUND_STRING("Magnitude"),
        .description = COMPOUND_STRING("A ground-shaking\nattack against all\nstanding Pokémon.\nIts power varies."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 126 "Magnitude" - port battle script */,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_222_*
    },
    [MOVE_DYNAMICPUNCH] =
    {
        .name = COMPOUND_STRING("Dynamicpunch"),
        .description = COMPOUND_STRING("The foe is punched\nwith the user's full\npower. It confuses\nthe foe if it hits."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_223_*
    },
    [MOVE_MEGAHORN] =
    {
        .name = COMPOUND_STRING("Megahorn"),
        .description = COMPOUND_STRING("A brutal ramming\nattack delivered\nwith a tough and\nimpressive horn."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_224_*
    },
    [MOVE_DRAGONBREATH] =
    {
        .name = COMPOUND_STRING("Dragonbreath"),
        .description = COMPOUND_STRING("The foe is hit with\nan incredible blast\nof breath that may\nalso paralyze."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_225_*
    },
    [MOVE_BATON_PASS] =
    {
        .name = COMPOUND_STRING("Baton Pass"),
        .description = COMPOUND_STRING("The user switches\nout, passing along\nany stat changes\nto the new battler."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 127 "BatonPass" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_226_*
    },
    [MOVE_ENCORE] =
    {
        .name = COMPOUND_STRING("Encore"),
        .description = COMPOUND_STRING("Makes the foe use\nthe move it last\nused repeatedly for\ntwo to six turns."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 90 "OpponentRepeatMoveFor2to6turns" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_227_*
    },
    [MOVE_PURSUIT] =
    {
        .name = COMPOUND_STRING("Pursuit"),
        .description = COMPOUND_STRING("An attack move that\nworks especially\nwell on a foe that\nis switching out."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 128 "DoublePowerIfOpponentSwitching" - port battle script */,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_228_*
    },
    [MOVE_RAPID_SPIN] =
    {
        .name = COMPOUND_STRING("Rapid Spin"),
        .description = COMPOUND_STRING("An attack that\nfrees the user from\nBind, Wrap, Leech\nSeed, and Spikes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 129 "RemoveBindSeedSpikes" - port battle script */,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_229_*
    },
    [MOVE_SWEET_SCENT] =
    {
        .name = COMPOUND_STRING("Sweet Scent"),
        .description = COMPOUND_STRING("Allures the foe to\nreduce evasiveness.\nIt also attracts\nwild Pokémon."),
        .effect = EFFECT_EVASION_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_230_*
    },
    [MOVE_IRON_TAIL] =
    {
        .name = COMPOUND_STRING("Iron Tail"),
        .description = COMPOUND_STRING("An attack with a\nsteel-hard tail.\nIt may lower the\nfoe's Defense stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_231_*
    },
    [MOVE_METAL_CLAW] =
    {
        .name = COMPOUND_STRING("Metal Claw"),
        .description = COMPOUND_STRING("The foe is attacked\nwith steel claws.\nIt may also raise\nthe user's Attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 139 "RaiseAttack1HitChance" - port battle script */,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_232_*
    },
    [MOVE_VITAL_THROW] =
    {
        .name = COMPOUND_STRING("Vital Throw"),
        .description = COMPOUND_STRING("Makes the user\nattack after the\nfoe. In return,\nit will not miss."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 78 "NeverMissMoveLast" - port battle script */,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_233_*
    },
    [MOVE_MORNING_SUN] =
    {
        .name = COMPOUND_STRING("Morning Sun"),
        .description = COMPOUND_STRING("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 132 "MorningSun" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_234_*
    },
    [MOVE_SYNTHESIS] =
    {
        .name = COMPOUND_STRING("Synthesis"),
        .description = COMPOUND_STRING("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 133 "Synthesis" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_235_*
    },
    [MOVE_MOONLIGHT] =
    {
        .name = COMPOUND_STRING("Moonlight"),
        .description = COMPOUND_STRING("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 134 "Moonlight" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_236_*
    },
    [MOVE_WATER_TACKLE] =
    {
        .name = COMPOUND_STRING("Water Tackle"),
        .description = COMPOUND_STRING("The user hits\nthe enemy while\nsurfing on a wave."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_237_*
    },
    [MOVE_CROSS_CHOP] =
    {
        .name = COMPOUND_STRING("Cross Chop"),
        .description = COMPOUND_STRING("The foe is hit with\ndouble chops.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_238_*
    },
    [MOVE_TWISTER] =
    {
        .name = COMPOUND_STRING("Twister"),
        .description = COMPOUND_STRING("A vicious twister\nattacks the foe.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 146 "FlinchAndDoubleDamageToFly" - port battle script */,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_239_*
    },
    [MOVE_RAIN_DANCE] =
    {
        .name = COMPOUND_STRING("Rain Dance"),
        .description = COMPOUND_STRING("A heavy rain falls\nfor five turns,\npowering up Water-\ntype moves."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 136 "Rain5turns" - port battle script */,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_240_*
    },
    [MOVE_SUNNY_DAY] =
    {
        .name = COMPOUND_STRING("Sunny Day"),
        .description = COMPOUND_STRING("The sun blazes for\nfive turns, powering\nup Fire-type\nmoves."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 137 "Sun5turns" - port battle script */,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_241_*
    },
    [MOVE_CRUNCH] =
    {
        .name = COMPOUND_STRING("Crunch"),
        .description = COMPOUND_STRING("The foe is crunched\nwith sharp fangs.\nIt may lower the\nfoe's Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_242_*
    },
    [MOVE_MIRROR_COAT] =
    {
        .name = COMPOUND_STRING("Mirror Coat"),
        .description = COMPOUND_STRING("A retaliation move\nthat pays back the\nfoe's special attack\ndouble."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 144 "DoubleBackSpecialDamage" - port battle script */,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_243_*
    },
    [MOVE_PSYCH_UP] =
    {
        .name = COMPOUND_STRING("Psych Up"),
        .description = COMPOUND_STRING("The user hypnotizes\nitself into copying\nany stat change\nmade by the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 143 "CopyTargetStatChangesPrimary" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_244_*
    },
    [MOVE_EXTREMESPEED] =
    {
        .name = COMPOUND_STRING("Extremespeed"),
        .description = COMPOUND_STRING("A blindingly speedy\ncharge attack that\nalways goes before\nany other."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_245_*
    },
    [MOVE_ANCIENTPOWER] =
    {
        .name = COMPOUND_STRING("Ancientpower"),
        .description = COMPOUND_STRING("An ancient power is\nused to attack. It\nmay also raise all\nthe user's stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 140 "RaiseAllStats1HitChance" - port battle script */,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_246_*
    },
    [MOVE_SHADOW_BALL] =
    {
        .name = COMPOUND_STRING("Shadow Ball"),
        .description = COMPOUND_STRING("A shadowy blob is\nhurled at the foe.\nMay also lower the\nfoe's Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 72 "LowerSpDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_247_*
    },
    [MOVE_LEAF_STORM] =
    {
        .name = COMPOUND_STRING("Leaf Storm"),
        .description = COMPOUND_STRING("Attacks with a\nstorm of leaves.\nHarshly reduces\nthe user's Sp. Atk."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 204 "LowerSpAttack2Self" - port battle script */,
        .power = 130,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_248_*
    },
    [MOVE_ROCK_SMASH] =
    {
        .name = COMPOUND_STRING("Rock Smash"),
        .description = COMPOUND_STRING("An attack that may\nalso cut Defense.\nIt can also smash\ncracked boulders."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_249_*
    },
    [MOVE_WHIRLPOOL] =
    {
        .name = COMPOUND_STRING("Whirlpool"),
        .description = COMPOUND_STRING("The foe is trapped\nin a fast, vicious\nwhirlpool for two\nto five turns."),
        .effect = EFFECT_BIND,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_250_*
    },
    [MOVE_BEAT_UP] =
    {
        .name = COMPOUND_STRING("Beat Up"),
        .description = COMPOUND_STRING("All party Pokémon\njoin in the attack.\nThe more allies,\nthe more damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 154 "DamageBasedOnPartySize" - port battle script */,
        .power = 10,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_251_*
    },
    [MOVE_FAKE_OUT] =
    {
        .name = COMPOUND_STRING("Fake Out"),
        .description = COMPOUND_STRING("An attack that hits\nfirst and causes\nflinching. Usable\nonly on 1st turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 158 "MoveFirstFlinchOnlyWorksTurn1" - port battle script */,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_252_*
    },
    [MOVE_UPROAR] =
    {
        .name = COMPOUND_STRING("Uproar"),
        .description = COMPOUND_STRING("The user attacks in\nan uproar that\nprevents sleep for\ntwo to five turns."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 159 "2to5turnsAndAllNoSleep" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_253_*
    },
    [MOVE_STOCKPILE] =
    {
        .name = COMPOUND_STRING("Stockpile"),
        .description = COMPOUND_STRING("The user charges\nup power for use\nlater. It can be\nused three times."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 160 "Stockpile" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_254_*
    },
    [MOVE_SPIT_UP] =
    {
        .name = COMPOUND_STRING("Spit Up"),
        .description = COMPOUND_STRING("The power built\nusing Stockpile is\nreleased at once\nfor attack"),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 161 "Spit Up" - port battle script */,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_255_*
    },
    [MOVE_SWALLOW] =
    {
        .name = COMPOUND_STRING("Swallow"),
        .description = COMPOUND_STRING("The energy it built\nusing Stockpile is\nabsorbed to restore\nHP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 162 "Swallow" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_256_*
    },
    [MOVE_HEAT_WAVE] =
    {
        .name = COMPOUND_STRING("Heat Wave"),
        .description = COMPOUND_STRING("The user exhales a\nheated breath to\nattack. It may also\ninflict a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_257_*
    },
    [MOVE_HAIL] =
    {
        .name = COMPOUND_STRING("Hail"),
        .description = COMPOUND_STRING("A hailstorm lasting\nfive turns damages\nall Pokémon except\nthe Ice-type."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 164 "Hail5turns" - port battle script */,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_258_*
    },
    [MOVE_TORMENT] =
    {
        .name = COMPOUND_STRING("Torment"),
        .description = COMPOUND_STRING("It enrages the foe,\nmaking it incapable\nof using the same\nmove successively."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 165 "Torment" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_259_*
    },
    [MOVE_FLATTER] =
    {
        .name = COMPOUND_STRING("Flatter"),
        .description = COMPOUND_STRING("Flattery is used to\nconfuse the foe,\nbut its Sp. Atk\nalso rises."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 166 "ConfuseAndRaiseSpAttack2" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_260_*
    },
    [MOVE_WILL_O_WISP] =
    {
        .name = COMPOUND_STRING("Will-o-Wisp"),
        .description = COMPOUND_STRING("A sinister, bluish\nwhite flame is shot\nat the foe to\ninflict a burn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 167 "BurnPrimary" - port battle script */,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_261_*
    },
    [MOVE_SCALD] =
    {
        .name = COMPOUND_STRING("Scald"),
        .description = COMPOUND_STRING("Boiling hot water\nis shot at the\nenemy. May burn\nthe target."),
        .effect = EFFECT_BURN_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_262_*
    },
    [MOVE_FACADE] =
    {
        .name = COMPOUND_STRING("Facade"),
        .description = COMPOUND_STRING("An attack that is\nboosted if user is\nburned, poisoned,\nor paralyzed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 169 "DoubleDamageIfSelfStatus" - port battle script */,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_263_*
    },
    [MOVE_FOCUS_PUNCH] =
    {
        .name = COMPOUND_STRING("Focus Punch"),
        .description = COMPOUND_STRING("An attack that is\nexecuted last.\nThe user flinches\nif hit beforehand."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 170 "SelfFlinchIfHit" - port battle script */,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_264_*
    },
    [MOVE_IRON_HEAD] =
    {
        .name = COMPOUND_STRING("Iron Head"),
        .description = COMPOUND_STRING("The user slams\nthe target with its\nhead. May also make\nthe target flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_265_*
    },
    [MOVE_FOLLOW_ME] =
    {
        .name = COMPOUND_STRING("Follow Me"),
        .description = COMPOUND_STRING("The user draws\nattention to itself,\nmaking foes attack\nonly the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 172 "ForceFoesTargetUser" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_266_*
    },
    [MOVE_NATURE_POWER] =
    {
        .name = COMPOUND_STRING("Nature Power"),
        .description = COMPOUND_STRING("An attack that\nchanges type\ndepending on the\nuser's location."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 173 "NaturePower" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_267_*
    },
    [MOVE_CHARGE] =
    {
        .name = COMPOUND_STRING("Charge"),
        .description = COMPOUND_STRING("The user charges\npower to boost the\nElectric move it\nuses next."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 174 "BoostNextElectricMove" - port battle script */,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_268_*
    },
    [MOVE_TAUNT] =
    {
        .name = COMPOUND_STRING("Taunt"),
        .description = COMPOUND_STRING("The foe is taunted\ninto a rage that\nallows it to use\nonly attack moves."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 175 "Taunt" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_269_*
    },
    [MOVE_HELPING_HAND] =
    {
        .name = COMPOUND_STRING("Helping Hand"),
        .description = COMPOUND_STRING("A move that boosts\nthe power of the\nally's attack in a\nbattle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 176 "BoostAllyPower" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 5,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_270_*
    },
    [MOVE_TRICK] =
    {
        .name = COMPOUND_STRING("Trick"),
        .description = COMPOUND_STRING("A move that tricks\nthe foe into\ntrading held items\nwith the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 177 "TradeHeldItems" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_271_*
    },
    [MOVE_MAGNET_BOMB] =
    {
        .name = COMPOUND_STRING("Magnet Bomb"),
        .description = COMPOUND_STRING("Launches a steel\nbomb that sticks\nto the target.\nNever misses."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_272_*
    },
    [MOVE_WISH] =
    {
        .name = COMPOUND_STRING("Wish"),
        .description = COMPOUND_STRING("A self-healing move\nthat restores half\nthe full HP on the\nnext turn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 179 "HealHalfNextTurn" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_273_*
    },
    [MOVE_MUD_BOMB] =
    {
        .name = COMPOUND_STRING("Mud Bomb"),
        .description = COMPOUND_STRING("Launches a mud ball.\nMay also lower the\ntarget's accuracy."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 73 "LowerAccuracy1HitChance" - port battle script */,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_274_*
    },
    [MOVE_INGRAIN] =
    {
        .name = COMPOUND_STRING("Ingrain"),
        .description = COMPOUND_STRING("The user lays roots\nthat restore HP on\nevery turn.\nIt can't switch out."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 181 "Ingrain" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_275_*
    },
    [MOVE_SUPERPOWER] =
    {
        .name = COMPOUND_STRING("Superpower"),
        .description = COMPOUND_STRING("A powerful attack,\nbut it also lowers\nthe user's Attack\nand Defense stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 182 "LowerSelfAttack1Defense1" - port battle script */,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_276_*
    },
    [MOVE_X_SCISSOR] =
    {
        .name = COMPOUND_STRING("X-Scissor"),
        .description = COMPOUND_STRING("The user slashes at\nthe foe by crossing\nscythes or claws."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_277_*
    },
    [MOVE_NIGHT_SLASH] =
    {
        .name = COMPOUND_STRING("Night Slash"),
        .description = COMPOUND_STRING("Instant slash with\na high critical\nhit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_278_*
    },
    [MOVE_REVENGE] =
    {
        .name = COMPOUND_STRING("Revenge"),
        .description = COMPOUND_STRING("An attack move that\ngains in intensity if\nthe target has hurt\nthe user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 185 "DoubleDamageIfHitThisTurn" - port battle script */,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_279_*
    },
    [MOVE_BRICK_BREAK] =
    {
        .name = COMPOUND_STRING("Brick Break"),
        .description = COMPOUND_STRING("An attack that also\nbreaks any barrier\nlike Light Screen\nand Reflect."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 186 "BreakWall" - port battle script */,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_280_*
    },
    [MOVE_YAWN] =
    {
        .name = COMPOUND_STRING("Yawn"),
        .description = COMPOUND_STRING("A huge yawn lulls\nthe foe into falling\nasleep on the next\nturn."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 187 "Yawn" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_281_*
    },
    [MOVE_KNOCK_OFF] =
    {
        .name = COMPOUND_STRING("Knock Off"),
        .description = COMPOUND_STRING("Knocks down the\nfoe's held item to\nprevent its use\nduring the battle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 188 "KnockOff" - port battle script */,
        .power = 65,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_282_*
    },
    [MOVE_ENDEAVOR] =
    {
        .name = COMPOUND_STRING("Endeavor"),
        .description = COMPOUND_STRING("Gains power the\nfewer HP the user\nhas compared with\nthe foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 189 "TargetHPEqualUser" - port battle script */,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_283_*
    },
    [MOVE_ERUPTION] =
    {
        .name = COMPOUND_STRING("Eruption"),
        .description = COMPOUND_STRING("The higher the\nuser's HP, the more\npowerful this\nattack becomes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 190 "DamageBasedOnHighRemainingHealth" - port battle script */,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_284_*
    },
    [MOVE_SKILL_SWAP] =
    {
        .name = COMPOUND_STRING("Skill Swap"),
        .description = COMPOUND_STRING("The user employs\nits psychic power\nto swap abilities\nwith the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 191 "SwapAbilityWithTarget" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_285_*
    },
    [MOVE_POWER_GEM] =
    {
        .name = COMPOUND_STRING("Power Gem"),
        .description = COMPOUND_STRING("The user attacks\nwith a ray of light\nthat may rise the\nuser's Def by 1."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 138 "RaiseDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_286_*
    },
    [MOVE_REFRESH] =
    {
        .name = COMPOUND_STRING("Refresh"),
        .description = COMPOUND_STRING("A self-healing move\nthat cures the user\nof a poisoning,\nburn, or paralysis."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 193 "HealSelfStatus" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_287_*
    },
    [MOVE_MYSTICALFIRE] =
    {
        .name = COMPOUND_STRING("Mysticalfire"),
        .description = COMPOUND_STRING("Attacks by breathing\na hot fire. May also\nlower the target's\nSp. Atk."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 71 "LowerSpAttack1HitChance" - port battle script */,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_288_*
    },
    [MOVE_SNATCH] =
    {
        .name = COMPOUND_STRING("Snatch"),
        .description = COMPOUND_STRING("Steals the effects\nof the foe's\nhealing or status-\nchanging move."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 195 "Snatch" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_289_*
    },
    [MOVE_POISON_JAB] =
    {
        .name = COMPOUND_STRING("Poison Jab"),
        .description = COMPOUND_STRING("A stab attack that\nmay also poison\nthe target."),
        .effect = EFFECT_POISON_HIT,
        .power = 80,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_290_*
    },
    [MOVE_PHANTOMFORCE] =
    {
        .name = COMPOUND_STRING("PhantomForce"),
        .description = COMPOUND_STRING("The user vanishes,\nthen strikes on the\nnext turn, hitting\neven protected foes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 155 "2turn" - port battle script */,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        // animation + sounds: scripts/move_animations/move_291_*
    },
    [MOVE_ARM_THRUST] =
    {
        .name = COMPOUND_STRING("Arm Thrust"),
        .description = COMPOUND_STRING("A quick flurry of\nstraight-arm\npunches that hit\ntwo to five times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_292_*
    },
    [MOVE_SEED_BOMB] =
    {
        .name = COMPOUND_STRING("Seed Bomb"),
        .description = COMPOUND_STRING("The user slams a\nbarrage of seed on\nthe foe from above."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_293_*
    },
    [MOVE_TAIL_GLOW] =
    {
        .name = COMPOUND_STRING("Tail Glow"),
        .description = COMPOUND_STRING("The user flashes a\nlight that sharply\nraises its Sp. Atk\nstat."),
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_294_*
    },
    [MOVE_STONE_EDGE] =
    {
        .name = COMPOUND_STRING("Stone Edge"),
        .description = COMPOUND_STRING("The foe is stabbed\nby sharpened stones.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_295_*
    },
    [MOVE_SHELL_SMASH] =
    {
        .name = COMPOUND_STRING("Shell Smash"),
        .description = COMPOUND_STRING("Raises the user's\noffensive stats,\nat the cost of its\ndefensive stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 212 "RaiseAttack1Speed1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_296_*
    },
    [MOVE_ROOST] =
    {
        .name = COMPOUND_STRING("Roost"),
        .description = COMPOUND_STRING("The user lands and\nrest its body.\nIt restores half\nthe user's HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_297_*
    },
    [MOVE_TEETER_DANCE] =
    {
        .name = COMPOUND_STRING("Teeter Dance"),
        .description = COMPOUND_STRING("A wobbly dance\nthat confuses all\nthe Pokémon in\nbattle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 199 "ConfuseAllPokemon" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_298_*
    },
    [MOVE_BLAZE_KICK] =
    {
        .name = COMPOUND_STRING("Blaze Kick"),
        .description = COMPOUND_STRING("A fiery kick with a\nhigh critical-hit\nratio. It may also\nburn the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 200 "HighCritBurn" - port battle script */,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_299_*
    },
    [MOVE_RAGE_POWDER] =
    {
        .name = COMPOUND_STRING("Rage Powder"),
        .description = COMPOUND_STRING("The user scatters\npowder to draw\nattention to itself."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 172 "ForceFoesTargetUser" - port battle script */,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_300_*
    },
    [MOVE_STONE_AXE] =
    {
        .name = COMPOUND_STRING("Stone Axe"),
        .description = COMPOUND_STRING("The user swings\nits stone axe\nat the target.\nHigh Crit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_301_*
    },
    [MOVE_NEEDLE_ARM] =
    {
        .name = COMPOUND_STRING("Needle Arm"),
        .description = COMPOUND_STRING("This move allows\nthe user to strike\nfirst, if the foe is\nreadying an attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 56 "Unused38" - port battle script */,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_302_*
    },
    [MOVE_SLACK_OFF] =
    {
        .name = COMPOUND_STRING("Slack Off"),
        .description = COMPOUND_STRING("The user slacks off\nand restores its HP\nby half its full\nHP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_303_*
    },
    [MOVE_HYPER_VOICE] =
    {
        .name = COMPOUND_STRING("Hyper Voice"),
        .description = COMPOUND_STRING("The user lets loose\na horribly loud\nshout with the\npower to damage."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_304_*
    },
    [MOVE_POISON_FANG] =
    {
        .name = COMPOUND_STRING("Poison Fang"),
        .description = COMPOUND_STRING("The foe is bitten\nwith toxic fangs.\nIt may also badly\npoison the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 202 "BadPoisonHitChance" - port battle script */,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_305_*
    },
    [MOVE_CRUSH_CLAW] =
    {
        .name = COMPOUND_STRING("Crush Claw"),
        .description = COMPOUND_STRING("The foe is attacked\nwith sharp claws.\nIt may also lower\nthe foe's Defense."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_306_*
    },
    [MOVE_BOOMBURST] =
    {
        .name = COMPOUND_STRING("Boomburst"),
        .description = COMPOUND_STRING("The user attacks\neverything around it\nwith a terrible\nexplosive sound."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 147 "DoubleDamageToDig" - port battle script */,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_307_*
    },
    [MOVE_INFESTATION] =
    {
        .name = COMPOUND_STRING("Infestation"),
        .description = COMPOUND_STRING("The target is\ninfested and\nattacked for four\nto five turns."),
        .effect = EFFECT_BIND,
        .power = 20,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_308_*
    },
    [MOVE_METEOR_MASH] =
    {
        .name = COMPOUND_STRING("Meteor Mash"),
        .description = COMPOUND_STRING("The foe is hit with\na hard, fast punch.\nIt may also raise\nthe user's Attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 139 "RaiseAttack1HitChance" - port battle script */,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_309_*
    },
    [MOVE_ASTONISH] =
    {
        .name = COMPOUND_STRING("Astonish"),
        .description = COMPOUND_STRING("An attack using a\nstartling shout.\nIt also may make\nthe foe flinch."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 150 "FlinchAndDoubleDamageToMinimize" - port battle script */,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_310_*
    },
    [MOVE_WEATHER_BALL] =
    {
        .name = COMPOUND_STRING("Weather Ball"),
        .description = COMPOUND_STRING("An attack that\nvaries in power and\ntype depending on\nthe weather."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 203 "WeatherBall" - port battle script */,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_311_*
    },
    [MOVE_AROMATHERAPY] =
    {
        .name = COMPOUND_STRING("Aromatherapy"),
        .description = COMPOUND_STRING("A soothing scent is\nreleased to heal\nall status problems\nin the user's party."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 102 "HealPartyStatus" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_312_*
    },
    [MOVE_FAKE_TEARS] =
    {
        .name = COMPOUND_STRING("Fake Tears"),
        .description = COMPOUND_STRING("The user feigns\ncrying to sharply\nlower the foe's\nSp. Def stat."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_313_*
    },
    [MOVE_AIR_CUTTER] =
    {
        .name = COMPOUND_STRING("Air Cutter"),
        .description = COMPOUND_STRING("The foe is hit with\nrazor-like wind.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_314_*
    },
    [MOVE_OVERHEAT] =
    {
        .name = COMPOUND_STRING("Overheat"),
        .description = COMPOUND_STRING("An intense attack\nthat also sharply\nreduces the user's\nSp. Atk stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 204 "LowerSpAttack2Self" - port battle script */,
        .power = 140,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_315_*
    },
    [MOVE_POWERUPPUNCH] =
    {
        .name = COMPOUND_STRING("PowerUpPunch"),
        .description = COMPOUND_STRING("A fist that raises\nthe Attack stat\nof the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 139 "RaiseAttack1HitChance" - port battle script */,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_316_*
    },
    [MOVE_ROCK_TOMB] =
    {
        .name = COMPOUND_STRING("Rock Tomb"),
        .description = COMPOUND_STRING("Boulders are hurled\nat the foe. It also\nlowers the foe's\nSpeed if it hits."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_317_*
    },
    [MOVE_SILVER_WIND] =
    {
        .name = COMPOUND_STRING("Silver Wind"),
        .description = COMPOUND_STRING("The foe is attacked\nwith a silver dust.\nIt may raise all\nthe user's stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 140 "RaiseAllStats1HitChance" - port battle script */,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_318_*
    },
    [MOVE_METAL_SOUND] =
    {
        .name = COMPOUND_STRING("Metal Sound"),
        .description = COMPOUND_STRING("A horrible metallic\nscreech is used to\nsharply lower the\nfoe's Sp. Def."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_319_*
    },
    [MOVE_HEAD_SMASH] =
    {
        .name = COMPOUND_STRING("Head Smash"),
        .description = COMPOUND_STRING("Hazardous, full\npower headbutt that\ndamages the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_320_*
    },
    [MOVE_TICKLE] =
    {
        .name = COMPOUND_STRING("Tickle"),
        .description = COMPOUND_STRING("The foe is made to\nlaugh, reducing its\nAttack and Defense\nstats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 205 "LowerAttack1Defense1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .magicCoatAffected = TRUE,
        // animation + sounds: scripts/move_animations/move_321_*
    },
    [MOVE_COSMIC_POWER] =
    {
        .name = COMPOUND_STRING("Cosmic Power"),
        .description = COMPOUND_STRING("The user absorbs a\nmystic power to\nraise its Defense\nand Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 206 "RaiseDefense1SpDefense1" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_322_*
    },
    [MOVE_WATER_SPOUT] =
    {
        .name = COMPOUND_STRING("Water Spout"),
        .description = COMPOUND_STRING("The higher the\nuser's HP, the more\npowerful this\nattack becomes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 190 "DamageBasedOnHighRemainingHealth" - port battle script */,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_323_*
    },
    [MOVE_SIGNAL_BEAM] =
    {
        .name = COMPOUND_STRING("Signal Beam"),
        .description = COMPOUND_STRING("The foe is hit with\na flashing beam\nthat may also\ncause confusion."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_324_*
    },
    [MOVE_SHADOW_PUNCH] =
    {
        .name = COMPOUND_STRING("Shadow Punch"),
        .description = COMPOUND_STRING("The user throws a\npunch from the\nshadows. It cannot\nbe evaded."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_325_*
    },
    [MOVE_EXTRASENSORY] =
    {
        .name = COMPOUND_STRING("Extrasensory"),
        .description = COMPOUND_STRING("The user attacks\nwith an odd power\nthat may make the\nfoe flinch."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 150 "FlinchAndDoubleDamageToMinimize" - port battle script */,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_326_*
    },
    [MOVE_SKY_UPPERCUT] =
    {
        .name = COMPOUND_STRING("Sky Uppercut"),
        .description = COMPOUND_STRING("The user attacks\nwith an uppercut\nthrown skywards\nwith force."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 207 "CanDamageFly" - port battle script */,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_327_*
    },
    [MOVE_SAND_TOMB] =
    {
        .name = COMPOUND_STRING("Sand Tomb"),
        .description = COMPOUND_STRING("The foe is trapped\ninside a painful\nsandstorm for two\nto five turns."),
        .effect = EFFECT_BIND,
        .power = 35,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_328_*
    },
    [MOVE_HIHORSEPOWER] =
    {
        .name = COMPOUND_STRING("HiHorsepower"),
        .description = COMPOUND_STRING("The user fiercely\nattacks the target\nusing its entire\nbody."),
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_329_*
    },
    [MOVE_MUDDY_WATER] =
    {
        .name = COMPOUND_STRING("Muddy Water"),
        .description = COMPOUND_STRING("The user attacks\nwith muddy water.\nIt may also lower\nthe foe's accuracy."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 73 "LowerAccuracy1HitChance" - port battle script */,
        .power = 95,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_330_*
    },
    [MOVE_BULLET_SEED] =
    {
        .name = COMPOUND_STRING("Bullet Seed"),
        .description = COMPOUND_STRING("The user shoots\nseeds at the foe.\nTwo to five seeds\nare shot at once."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_331_*
    },
    [MOVE_AERIAL_ACE] =
    {
        .name = COMPOUND_STRING("Aerial Ace"),
        .description = COMPOUND_STRING("An extremely fast\nattack against one\ntarget. It can't be\nevaded."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_332_*
    },
    [MOVE_ICICLE_SPEAR] =
    {
        .name = COMPOUND_STRING("Icicle Spear"),
        .description = COMPOUND_STRING("Sharp icicles are\nfired at the foe.\nIt strikes two to\nfive times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_333_*
    },
    [MOVE_IRON_DEFENSE] =
    {
        .name = COMPOUND_STRING("Iron Defense"),
        .description = COMPOUND_STRING("The user hardens\nits body's surface\nto sharply raise its\nDefense stat."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_334_*
    },
    [MOVE_ROCK_POLISH] =
    {
        .name = COMPOUND_STRING("Rock Polish"),
        .description = COMPOUND_STRING("The user polishes\nits body and sharply\nraises its Speed\nstat."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_335_*
    },
    [MOVE_HOWL] =
    {
        .name = COMPOUND_STRING("Howl"),
        .description = COMPOUND_STRING("The user howls to\nboost the its and\nits partner's\nAttack stat."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_336_*
    },
    [MOVE_DRAGON_CLAW] =
    {
        .name = COMPOUND_STRING("Dragon Claw"),
        .description = COMPOUND_STRING("Sharp, huge claws\nhook and slash the\nfoe quickly and\nwith great power."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_337_*
    },
    [MOVE_ICICLE_CRASH] =
    {
        .name = COMPOUND_STRING("Icicle Crash"),
        .description = COMPOUND_STRING("The user drops an\nicicle onto the\ntarget. May cause\nflinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 85,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_338_*
    },
    [MOVE_BULK_UP] =
    {
        .name = COMPOUND_STRING("Bulk Up"),
        .description = COMPOUND_STRING("The user bulks up\nits body to boost\nboth its Attack and\nDefense stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 208 "RaiseAttack1Defense1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_339_*
    },
    [MOVE_YGGDRAIN] =
    {
        .name = COMPOUND_STRING("Yggdrain"),
        .description = COMPOUND_STRING("An attack imbued\nwith sacred power.\nHeals by half\nthe damage done."),
        .effect = EFFECT_ABSORB,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_340_*
    },
    [MOVE_MUD_SHOT] =
    {
        .name = COMPOUND_STRING("Mud Shot"),
        .description = COMPOUND_STRING("The user attacks by\nhurling mud.\nIt also reduces the\nfoe's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_341_*
    },
    [MOVE_POISON_TAIL] =
    {
        .name = COMPOUND_STRING("Poison Tail"),
        .description = COMPOUND_STRING("An attack with a\nhigh critical-hit\nratio. It may also\npoison the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 209 "HighCritPoison" - port battle script */,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_342_*
    },
    [MOVE_COVET] =
    {
        .name = COMPOUND_STRING("Covet"),
        .description = COMPOUND_STRING("A cutely executed\nattack that also\nsteals the foe's\nhold item."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 105 "StealItem" - port battle script */,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_343_*
    },
    [MOVE_WILD_CHARGE] =
    {
        .name = COMPOUND_STRING("Wild Charge"),
        .description = COMPOUND_STRING("The user shrouds\nitself in\nelectricity.\nCauses recoil."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_344_*
    },
    [MOVE_MAGICAL_LEAF] =
    {
        .name = COMPOUND_STRING("Magical Leaf"),
        .description = COMPOUND_STRING("The foe is attacked\nwith a strange leaf\nthat cannot be\nevaded."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_345_*
    },
    [MOVE_COTTON_GUARD] =
    {
        .name = COMPOUND_STRING("Cotton Guard"),
        .description = COMPOUND_STRING("The user protects\nitself and sharply\nraises its Defense."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_346_*
    },
    [MOVE_CALM_MIND] =
    {
        .name = COMPOUND_STRING("Calm Mind"),
        .description = COMPOUND_STRING("The user focuses\nits mind to raise\nthe Sp. Atk and\nSp. Def stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 211 "RaiseSpAttack1SpDefense1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_347_*
    },
    [MOVE_LEAF_BLADE] =
    {
        .name = COMPOUND_STRING("Leaf Blade"),
        .description = COMPOUND_STRING("The foe is slashed\nwith a sharp leaf.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_348_*
    },
    [MOVE_DRAGON_DANCE] =
    {
        .name = COMPOUND_STRING("Dragon Dance"),
        .description = COMPOUND_STRING("A mystic, powerful\ndance that boosts\nthe user's Attack\nand Speed stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 212 "RaiseAttack1Speed1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_349_*
    },
    [MOVE_ROCK_BLAST] =
    {
        .name = COMPOUND_STRING("Rock Blast"),
        .description = COMPOUND_STRING("The user hurls two\nto five hard rocks\nat the foe to\nattack."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_350_*
    },
    [MOVE_SHOCK_WAVE] =
    {
        .name = COMPOUND_STRING("Shock Wave"),
        .description = COMPOUND_STRING("A rapid jolt of\nelectricity strikes\nthe foe. It can't\nbe evaded."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_351_*
    },
    [MOVE_WATER_PULSE] =
    {
        .name = COMPOUND_STRING("Water Pulse"),
        .description = COMPOUND_STRING("An attack with a\npulsing blast of\nwater. It may also\nconfuse the foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_352_*
    },
    [MOVE_DOOM_DESIRE] =
    {
        .name = COMPOUND_STRING("Doom Desire"),
        .description = COMPOUND_STRING("A move that attacks\nthe foe with a\nblast of light two\nturns after use."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 148 "DamageIn2Turns" - port battle script */,
        .power = 140,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_353_*
    },
    [MOVE_NASTY_PLOT] =
    {
        .name = COMPOUND_STRING("Nasty Plot"),
        .description = COMPOUND_STRING("The user stimulates\nits brain to sharply\nraise its Sp. Atk\nstat."),
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_354_*
    },
    [MOVE_LIGHT_SHOT] =
    {
        .name = COMPOUND_STRING("Light Shot"),
        .description = COMPOUND_STRING("The enemy is hit\nby a weak shot\nof etheric energy."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_355_*
    },
    [MOVE_ASTRAL_GLEAM] =
    {
        .name = COMPOUND_STRING("Astral Gleam"),
        .description = COMPOUND_STRING("The user emits\netheric energy\nthat hits both\nopponents."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_356_*
    },
    [MOVE_RADIANT_STAR] =
    {
        .name = COMPOUND_STRING("Radiant Star"),
        .description = COMPOUND_STRING("A huge sphere of\nmana that may lower\nthe target's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 70 "LowerSpeed1HitChance" - port battle script */,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_357_*
    },
    [MOVE_METEOR] =
    {
        .name = COMPOUND_STRING("Meteor"),
        .description = COMPOUND_STRING("A mana meteor\nthat also sharply\nreduces the user's\nSp. Atk stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 204 "LowerSpAttack2Self" - port battle script */,
        .power = 140,
        .type = TYPE_AETHER,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_358_*
    },
    [MOVE_ETHERIC_BOON] =
    {
        .name = COMPOUND_STRING("Etheric Boon"),
        .description = COMPOUND_STRING("The user charges up\nwith etheric energy.\nRaises its Atk\nand Sp. Atk stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 14 "Unused0E" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_359_*
    },
    [MOVE_AD_NIHILO] =
    {
        .name = COMPOUND_STRING("Ad Nihilo"),
        .description = COMPOUND_STRING("An etheric wind that\nresets stat changes\nto zero."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 12 "Unused0C" - port battle script */,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_360_*
    },
    [MOVE_FINAL_GAMBIT] =
    {
        .name = COMPOUND_STRING("Final Gambit"),
        .description = COMPOUND_STRING("The user risks all,\ndealing damage\nequal to its HP\nand then fainting."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 15 "Unused0F" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_361_*
    },
    [MOVE_MIND_BASH] =
    {
        .name = COMPOUND_STRING("Mind Bash"),
        .description = COMPOUND_STRING("An etheric attack\nin which the user\ncharges, full body,\ninto the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_362_*
    },
    [MOVE_COSMIC_SLASH] =
    {
        .name = COMPOUND_STRING("Cosmic Slash"),
        .description = COMPOUND_STRING("An attack performed\nby edges or claws\nimbued with etheric\nenergy."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_363_*
    },
    [MOVE_ENERGY_EDGE] =
    {
        .name = COMPOUND_STRING("Energy Edge"),
        .description = COMPOUND_STRING("A reckless, etheric\ntackle that may\nlower the opponent's\nDef stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_364_*
    },
    [MOVE__5_RING_SWORD] =
    {
        .name = COMPOUND_STRING("5-Ring Sword"),
        .description = COMPOUND_STRING("The user imbues its\nswords with etheric\nenergy.\nMulti-hit attack."),
        .effect = EFFECT_MULTI_HIT,
        .power = 30,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_365_*
    },
    [MOVE_SHOGUN_DECOY] =
    {
        .name = COMPOUND_STRING("Shogun Decoy"),
        .description = COMPOUND_STRING("The user draws\nattention to itself\nand boosts its\nAttack and Defense."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 21 "Unused15" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_366_*
    },
    [MOVE_CHIME_BOOST] =
    {
        .name = COMPOUND_STRING("Chime Boost"),
        .description = COMPOUND_STRING("A soothing bell that\nsharply raises\nuser and partner's\nSpeed stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_367_*
    },
    [MOVE_SOUL_TRADE] =
    {
        .name = COMPOUND_STRING("Soul Trade"),
        .description = COMPOUND_STRING("The user drains the\ntarget's energy and\nrestores HP equal\nto half the damage."),
        .effect = EFFECT_ABSORB,
        .power = 85,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_368_*
    },
    [MOVE_MEGALODIVE] =
    {
        .name = COMPOUND_STRING("Megalodive"),
        .description = COMPOUND_STRING("Earth-shattering\ntail slap.\nIt may make the\nfoe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_369_*
    },
    [MOVE_AZURE_FLOOD] =
    {
        .name = COMPOUND_STRING("Azure Flood"),
        .description = COMPOUND_STRING("Aether-charged ice\nparticles that may\ninflict frostbite."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 55 "Unused37" - port battle script */,
        .power = 80,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_370_*
    },
    [MOVE_SUCKER_PUNCH] =
    {
        .name = COMPOUND_STRING("Sucker Punch"),
        .description = COMPOUND_STRING("This move allows\nthe user to strike\nfirst, if the foe is\nreadying an attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 56 "Unused38" - port battle script */,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_371_*
    },
    [MOVE_SEALINGLIGHT] =
    {
        .name = COMPOUND_STRING("SealingLight"),
        .description = COMPOUND_STRING("The user emits an\nimmense amount of\netheric energy that\nhalves the foe's HP."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_372_*
    },
    [MOVE_CLOSE_COMBAT] =
    {
        .name = COMPOUND_STRING("Close Combat"),
        .description = COMPOUND_STRING("The foe is fought\nup close. This cuts\nthe user's Defense\nand Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 61 "Unused3D" - port battle script */,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_373_*
    },
    [MOVE_AIR_SLASH] =
    {
        .name = COMPOUND_STRING("Air Slash"),
        .description = COMPOUND_STRING("The foe is sliced\nby a blade of air.\nIt may also make\nthe foe flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 75,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_374_*
    },
    [MOVE_TRIPLE_AXEL] =
    {
        .name = COMPOUND_STRING("Triple Axel"),
        .description = COMPOUND_STRING("A 3-kick attack\nthat becomes more\npowerful with each\nsuccessive hit."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 104 "3turnTripleHit" - port battle script */,
        .power = 20,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_375_*
    },
    [MOVE_FIRE_FANG] =
    {
        .name = COMPOUND_STRING("Fire Fang"),
        .description = COMPOUND_STRING("The user bites the\nfoe. It may also\nmake the foe flinch,\nor leave it burned."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 65,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_376_*
    },
    [MOVE_ICE_FANG] =
    {
        .name = COMPOUND_STRING("Ice Fang"),
        .description = COMPOUND_STRING("The user bites the\nfoe. It may also\nmake the foe flinch,\nor inflict frostbite."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 10%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_377_*
    },
    [MOVE_THUNDER_FANG] =
    {
        .name = COMPOUND_STRING("Thunder Fang"),
        .description = COMPOUND_STRING("The user bites the\nfoe. It may also\nmake the foe flinch,\nor paralyze it."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_378_*
    },
    [MOVE_TAIL_SLAP] =
    {
        .name = COMPOUND_STRING("Tail Slap"),
        .description = COMPOUND_STRING("The user hits the\ntarget with its tail.\nIt hits two to five\ntimes in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_379_*
    },
    [MOVE_HORN_LEECH] =
    {
        .name = COMPOUND_STRING("Horn Leech"),
        .description = COMPOUND_STRING("A harsh attack that\nabsorbs half the\ndamage it inflicted\nto restore HP."),
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_380_*
    },
    [MOVE_LIFE_CONTROL] =
    {
        .name = COMPOUND_STRING("Life Control"),
        .description = COMPOUND_STRING("Restores half of the\nuser's maximum HP\nand raises\nthe user's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 63 "Unused3F" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_381_*
    },
    [MOVE_STAR_DROP] =
    {
        .name = COMPOUND_STRING("Star Drop"),
        .description = COMPOUND_STRING("Causes damage equal\nto the user's level\nand decreases\nthe target's Defense."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 64 "Unused40" - port battle script */,
        .power = 1,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_382_*
    },
    [MOVE_TRAILBLAZE] =
    {
        .name = COMPOUND_STRING("Trailblaze"),
        .description = COMPOUND_STRING("The user quickly\nleaps out from tall\nGrass. It also ups\nthe user's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 74 "Unused4A" - port battle script */,
        .power = 50,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_383_*
    },
    [MOVE_FLAME_CHARGE] =
    {
        .name = COMPOUND_STRING("Flame Charge"),
        .description = COMPOUND_STRING("The user cloaks\nitself in flames and\nattacks. It also ups\nthe user's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 74 "Unused4A" - port battle script */,
        .power = 50,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_384_*
    },
    [MOVE_SOLAR_BLADE] =
    {
        .name = COMPOUND_STRING("Solar Blade"),
        .description = COMPOUND_STRING("The user gathers\nsolar energy to\nstrike foes with\na blade of light."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 151 "ChargeFirstTurn" - port battle script */,
        .power = 125,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_385_*
    },
    [MOVE_FIRST_PRESS] =
    {
        .name = COMPOUND_STRING("First Press"),
        .description = COMPOUND_STRING("Powerful move, but it\nonly works the first\nturn the user is in\nbattle."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 216 "216" - port battle script */,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_386_*
    },
    [MOVE_VOLT_SWITCH] =
    {
        .name = COMPOUND_STRING("Volt Switch"),
        .description = COMPOUND_STRING("After attacking,\nthe user switches\nplaces with a\nparty Pokémon."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 96 "Unused60" - port battle script */,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_387_*
    },
    [MOVE_U_TURN] =
    {
        .name = COMPOUND_STRING("U-Turn"),
        .description = COMPOUND_STRING("After attacking,\nthe user switches\nplaces with a\nparty Pokémon."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 96 "Unused60" - port battle script */,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_388_*
    },
    [MOVE_SUMMER_TANGO] =
    {
        .name = COMPOUND_STRING("Summer Tango"),
        .description = COMPOUND_STRING("A dance that raises\nthe user's Evasion\nand the partner's\nAtk and Sp. Atk."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_389_*
    },
    [MOVE_SPRING_TANGO] =
    {
        .name = COMPOUND_STRING("Spring Tango"),
        .description = COMPOUND_STRING("A dance that raises\nthe user's Speed\nand the partner's\nDef and Sp. Def."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_390_*
    },
    [MOVE_BRIGHT_SONG] =
    {
        .name = COMPOUND_STRING("Bright Song"),
        .description = COMPOUND_STRING("A song that sharply\nraises the team's\nAccuracy and the\npartner's Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_391_*
    },
    [MOVE_LIFE_BALLAD] =
    {
        .name = COMPOUND_STRING("Life Ballad"),
        .description = COMPOUND_STRING("A song that raises\nthe team's Speed\nand heals their\nstatus condition."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_392_*
    },
    [MOVE_RAPID_FIRE] =
    {
        .name = COMPOUND_STRING("Rapid Fire"),
        .description = COMPOUND_STRING("A piercing attack\nthat fires 2 to 5\nbullets at once\nat one enemy."),
        .effect = EFFECT_MULTI_HIT,
        .power = 30,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_393_*
    },
    [MOVE_TOXIC_REAP] =
    {
        .name = COMPOUND_STRING("Toxic Reap"),
        .description = COMPOUND_STRING("A poison-imbued\nscythe slash that\nmay badly poison\nthe foe."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 202 "BadPoisonHitChance" - port battle script */,
        .power = 75,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_394_*
    },
    [MOVE_WILT_MIASMA] =
    {
        .name = COMPOUND_STRING("Wilt. Miasma"),
        .description = COMPOUND_STRING("A wave of miasma\nhits both opponents\nand reduces their\nAccuracy and Evasion."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 131 "Unused83" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_395_*
    },
    [MOVE_LADYBUG_RUSH] =
    {
        .name = COMPOUND_STRING("Ladybug Rush"),
        .description = COMPOUND_STRING("A reckless rush\nthat may lower the\nopponent's Defense\nstat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_396_*
    },
    [MOVE_COIL] =
    {
        .name = COMPOUND_STRING("Coil"),
        .description = COMPOUND_STRING("The user coils up,\nraising its Attack,\nDefense, and\naccuracy."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 208 "RaiseAttack1Defense1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_397_*
    },
    [MOVE_FOUL_PLAY] =
    {
        .name = COMPOUND_STRING("Foul Play"),
        .description = COMPOUND_STRING("Turns the target's\npower against it.\nPower increases with\nthe foe's Atk stat."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 141 "Unused8D" - port battle script */,
        .power = 95,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_398_*
    },
    [MOVE_VOLT_WINGS] =
    {
        .name = COMPOUND_STRING("Volt Wings"),
        .description = COMPOUND_STRING("The foe is struck\nwith large, electric\nwings that may also\ninflict paralysis."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_399_*
    },
    [MOVE_FLIP_TURN] =
    {
        .name = COMPOUND_STRING("Flip Turn"),
        .description = COMPOUND_STRING("After attacking,\nthe user switches\nplaces with a\nparty Pokémon."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 96 "Unused60" - port battle script */,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_400_*
    },
    [MOVE_CRAZED_SHOUT] =
    {
        .name = COMPOUND_STRING("Crazed Shout"),
        .description = COMPOUND_STRING("The user emits a very\nloud cry that may\nconfuse the foes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_401_*
    },
    [MOVE_WHIP_RIPPER] =
    {
        .name = COMPOUND_STRING("Whip Ripper"),
        .description = COMPOUND_STRING("The user violently\nwhirls its vines to\nlash the foe. May\ninflict paralysis."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 25%  -> port to .additionalEffects
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_402_*
    },
    [MOVE_PHALANXGUARD] =
    {
        .name = COMPOUND_STRING("PhalanxGuard"),
        .description = COMPOUND_STRING("A defensive formation\nthat boosts the team's\nDefense stat.\nAlways strikes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_403_*
    },
    [MOVE_DOUBLEHAMMER] =
    {
        .name = COMPOUND_STRING("DoubleHammer"),
        .description = COMPOUND_STRING("A sequence of 2\nearth-shattering\npunches is thrown\nat the enemy."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_404_*
    },
    [MOVE_STOMP_CRUSH] =
    {
        .name = COMPOUND_STRING("Stomp Crush"),
        .description = COMPOUND_STRING("The user violently\nstomps the ground to\ncause a rock slide\nthat hits the foes."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        // animation + sounds: scripts/move_animations/move_405_*
    },
    [MOVE_ICY_ARIA] =
    {
        .name = COMPOUND_STRING("Icy Aria"),
        .description = COMPOUND_STRING("A strong hailstorm\nhits the opponents.\nIt may inflict\nfrostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_406_*
    },
    [MOVE_VENOM_GUST] =
    {
        .name = COMPOUND_STRING("Venom Gust"),
        .description = COMPOUND_STRING("A poisonous wind hits\nboth opponents.\nIt may also badly\npoison the foes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 202 "BadPoisonHitChance" - port battle script */,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 40%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_407_*
    },
    [MOVE_YGGDRASLASH] =
    {
        .name = COMPOUND_STRING("Yggdraslash"),
        .description = COMPOUND_STRING("An attack imbued\nwith sacred power.\nAlways strikes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 103 "NormalPlusPriority" - port battle script */,
        .power = 90,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_408_*
    },
    [MOVE_WATER_BOMB] =
    {
        .name = COMPOUND_STRING("Water Bomb"),
        .description = COMPOUND_STRING("The user summons a\ntempest to hit\nthe enemy with\na water bomb."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 214 "214" - port battle script */,
        .power = 70,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_409_*
    },
    [MOVE_SUBZERO_GALE] =
    {
        .name = COMPOUND_STRING("Subzero Gale"),
        .description = COMPOUND_STRING("An icy wind hits\nboth opponents.\nIt may also\ninflict frostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 40%  -> port to .additionalEffects
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_410_*
    },
    [MOVE_FROST_CURSE] =
    {
        .name = COMPOUND_STRING("Frost Curse"),
        .description = COMPOUND_STRING("The user curses\nthe opponent in order\nto inflict frostbite."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 215 "215" - port battle script */,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .magicCoatAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_411_*
    },
    [MOVE_DIVINE_STORM] =
    {
        .name = COMPOUND_STRING("Divine Storm"),
        .description = COMPOUND_STRING("The opponents are hit\nby a violent storm\nthat breaks the sky.\nMay paralyze the foes."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 85,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_412_*
    },
    [MOVE_IZUNA] =
    {
        .name = COMPOUND_STRING("Izuna"),
        .description = COMPOUND_STRING("A ninja-style\nslash attack that\nmay paralyze\nthe opponent."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_413_*
    },
    [MOVE_FUKUBARI] =
    {
        .name = COMPOUND_STRING("Fukubari"),
        .description = COMPOUND_STRING("A piercing attack\nmade with ninja tools\nthat may put the\nopponent to sleep."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 218 "218" - port battle script */,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_414_*
    },
    [MOVE_KUMOGAKURE] =
    {
        .name = COMPOUND_STRING("Kumogakure"),
        .description = COMPOUND_STRING("A ninja art that\nhalves the user's HP\nto sharply increase\nits Evasion."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 219 "219" - port battle script */,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_415_*
    },
    [MOVE_TAGEN_BATTOU] =
    {
        .name = COMPOUND_STRING("Tagen Battou"),
        .description = COMPOUND_STRING("The foe is hit by\nviolent slashes.\nIt sharply reduces\nthe user's Evasion."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 217 "217" - port battle script */,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_416_*
    },
    [MOVE_NOBLE_ORDER] =
    {
        .name = COMPOUND_STRING("Noble Order"),
        .description = COMPOUND_STRING("The user inspires\nits underlings to\nboost the team's\nSp. Atk by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 224 "224" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_417_*
    },
    [MOVE_VEIL_ORDER] =
    {
        .name = COMPOUND_STRING("Veil Order"),
        .description = COMPOUND_STRING("The user inspires\nits underlings to\nboost the team's\nSp. Def by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 224 "224" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_418_*
    },
    [MOVE_SPOREBARRAGE] =
    {
        .name = COMPOUND_STRING("SporeBarrage"),
        .description = COMPOUND_STRING("The user shoots\na barrage of spores\nto the enemy.\n2 to 5 hits."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_419_*
    },
    [MOVE_CHAINWEATHER] =
    {
        .name = COMPOUND_STRING("ChainWeather"),
        .description = COMPOUND_STRING("A violent slash that\nchanges its type\naccording to the\nweather."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 203 "WeatherBall" - port battle script */,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_420_*
    },
    [MOVE_CHAIN_KILLER] =
    {
        .name = COMPOUND_STRING("Chain Killer"),
        .description = COMPOUND_STRING("An attack that does\ndouble damage to a\ntarget affected by\na status problem."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 220 "220" - port battle script */,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_421_*
    },
    [MOVE_CORKSCREW] =
    {
        .name = COMPOUND_STRING("Corkscrew"),
        .description = COMPOUND_STRING("A melee bash\nattack that may\nparalyze the foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_422_*
    },
    [MOVE_TITAN_KILLER] =
    {
        .name = COMPOUND_STRING("Titan Killer"),
        .description = COMPOUND_STRING("The more HP the\ntarget has, the\ngreater the power."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 221 "221" - port battle script */,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_423_*
    },
    [MOVE_ONE_TWOPUNCH] =
    {
        .name = COMPOUND_STRING("One-TwoPunch"),
        .description = COMPOUND_STRING("A left hand jab\nfollowed by a right\ncross. Hits 2 times."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_424_*
    },
    [MOVE_LEADING_BLOW] =
    {
        .name = COMPOUND_STRING("Leading Blow"),
        .description = COMPOUND_STRING("An attack that hits\nanother time if the\ntarget is BRN, PAR,\nPSN or SLP."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 222 "222" - port battle script */,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_425_*
    },
    [MOVE_DARKNESSFIST] =
    {
        .name = COMPOUND_STRING("DarknessFist"),
        .description = COMPOUND_STRING("A cursed punch\nthat hits both\nopponents and\ndamages the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 100,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_426_*
    },
    [MOVE_WAKINGCHAKRA] =
    {
        .name = COMPOUND_STRING("WakingChakra"),
        .description = COMPOUND_STRING("The user recovers\nHP every turn and\nraises its speed\nby 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 223 "223" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_427_*
    },
    [MOVE_CALL_SNAKE] =
    {
        .name = COMPOUND_STRING("Call: Snake"),
        .description = COMPOUND_STRING("Summons an Ekans's\nspirit that may\nbadly poison\nthe opponent."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 202 "BadPoisonHitChance" - port battle script */,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_428_*
    },
    [MOVE_CALL_OWL] =
    {
        .name = COMPOUND_STRING("Call: Owl"),
        .description = COMPOUND_STRING("Summons a Noctowl's\nspirit that may put\nthe enemy to sleep."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 218 "218" - port battle script */,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_429_*
    },
    [MOVE_CALL_LION] =
    {
        .name = COMPOUND_STRING("Call: Lion"),
        .description = COMPOUND_STRING("Summons a Pyroar's\nspirit that may\nburn the opponent."),
        .effect = EFFECT_BURN_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_430_*
    },
    [MOVE_CALL_ALLIES] =
    {
        .name = COMPOUND_STRING("Call: Allies"),
        .description = COMPOUND_STRING("Summons the allies\nfor an all-out hit.\nThe more allies,\nthe more damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 154 "DamageBasedOnPartySize" - port battle script */,
        .power = 50,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_431_*
    },
    [MOVE_PRIMAL_DRUMS] =
    {
        .name = COMPOUND_STRING("Primal Drums"),
        .description = COMPOUND_STRING("An ancient song\nthat sharply lowers\nthe Defense of\nthe opponents."),
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_432_*
    },
    [MOVE_MESMERIZE] =
    {
        .name = COMPOUND_STRING("Mesmerize"),
        .description = COMPOUND_STRING("The foe is hit by\na psychic attack\nthat may put it\nto sleep."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 218 "218" - port battle script */,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_433_*
    },
    [MOVE_ROTTEN_EGG] =
    {
        .name = COMPOUND_STRING("Rotten Egg"),
        .description = COMPOUND_STRING("The user throws a\nrotten egg that\nlowers Atk and Sp.Atk\nof the opponents."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 225 "225" - port battle script */,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_434_*
    },
    [MOVE_HARVESTPARTY] =
    {
        .name = COMPOUND_STRING("HarvestParty"),
        .description = COMPOUND_STRING("An attack that does\ndouble damage to a\ntarget affected by\na status problem."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 220 "220" - port battle script */,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_435_*
    },
    [MOVE_LULLABY] =
    {
        .name = COMPOUND_STRING("Lullaby"),
        .description = COMPOUND_STRING("A soothing song\nthat may put the\nopponents to sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 50,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_436_*
    },
    [MOVE_STRANGESEEDS] =
    {
        .name = COMPOUND_STRING("StrangeSeeds"),
        .description = COMPOUND_STRING("The user plants\nseeds at the enemies'\nfeet that lower their\nSpeed and Evasion."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 226 "226" - port battle script */,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_437_*
    },
    [MOVE_PANIC_SPORES] =
    {
        .name = COMPOUND_STRING("Panic Spores"),
        .description = COMPOUND_STRING("A confusion\ninducing dust\nis scattered\naround a foe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_438_*
    },
    [MOVE_ATROPHIC_EYE] =
    {
        .name = COMPOUND_STRING("Atrophic Eye"),
        .description = COMPOUND_STRING("A mystic eye\nthat lowers Def\nand Sp. Def of\nthe opponents."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 227 "227" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_439_*
    },
    [MOVE_WARDING_MIST] =
    {
        .name = COMPOUND_STRING("Warding Mist"),
        .description = COMPOUND_STRING("An etheric mist\nthat protects and\nheals the party\nfrom status problems."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 228 "228" - port battle script */,
        .power = 0,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_440_*
    },
    [MOVE_TIME_CIRCLE] =
    {
        .name = COMPOUND_STRING("Time Circle"),
        .description = COMPOUND_STRING("Accelerates time\nto boost the team's\nSpeed by 1. Always\nstrikes first."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 110 "Unused6E" - port battle script */,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_441_*
    },
    [MOVE_ARCANE_BLAST] =
    {
        .name = COMPOUND_STRING("Arcane Blast"),
        .description = COMPOUND_STRING("The foe is hit\nby a blast of arcane\nenergy that also\nhurts the user."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 110,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_442_*
    },
    [MOVE_WOBBUSHIELD] =
    {
        .name = COMPOUND_STRING("Wobbushield"),
        .description = COMPOUND_STRING("A retaliation move\nthat counters any\nhit with double\nthe damage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 89 "DoubleBackPhysicalDamage" - port battle script */,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_443_*
    },
    [MOVE_SCYTHE_DANCE] =
    {
        .name = COMPOUND_STRING("Scythe Dance"),
        .description = COMPOUND_STRING("The foe is slashed\nrepeatedly with a\nscythe two to\nfive times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_444_*
    },
    [MOVE_DUALWINGBEAT] =
    {
        .name = COMPOUND_STRING("DualWingbeat"),
        .description = COMPOUND_STRING("The user slams\nthe target with its\nwings. The target is\nhit twice in a row."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_445_*
    },
    [MOVE_SONIC_RAID] =
    {
        .name = COMPOUND_STRING("Sonic Raid"),
        .description = COMPOUND_STRING("An almost invisibly\nfast attack that\nis certain to strike\nfirst."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_446_*
    },
    [MOVE_AKASHIC_NOVA] =
    {
        .name = COMPOUND_STRING("Akashic Nova"),
        .description = COMPOUND_STRING("The user unleashes\nFafnir's power.\nHits both enemies\nbut causes recoil."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_447_*
    },
    [MOVE_LIMIT_BREAK] =
    {
        .name = COMPOUND_STRING("Limit Break"),
        .description = COMPOUND_STRING("Raises the user's\noffensive stats,\nat the cost of its\ndefensive stats."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 212 "RaiseAttack1Speed1Primary" - port battle script */,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_448_*
    },
    [MOVE_SLASHRAMPAGE] =
    {
        .name = COMPOUND_STRING("SlashRampage"),
        .description = COMPOUND_STRING("The foe is hit by\nviolent slashes.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 75,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_449_*
    },
    [MOVE_FREEZERIPPLE] =
    {
        .name = COMPOUND_STRING("FreezeRipple"),
        .description = COMPOUND_STRING("The foes are hit\nby a freezing howl\nthat may inflict\nfrostbite."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 95,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_450_*
    },
    [MOVE_OCEAN_RAVE] =
    {
        .name = COMPOUND_STRING("Ocean Rave"),
        .description = COMPOUND_STRING("The foes are hit by\na violent tsunami.\nIt has a high\ncritical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 120,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_451_*
    },
    [MOVE_ROYAL_ORDER] =
    {
        .name = COMPOUND_STRING("Royal Order"),
        .description = COMPOUND_STRING("The more the target's\nstats have been\nraised, the stronger\nthe move is."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 229 "229" - port battle script */,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_452_*
    },
    [MOVE_VOLT_MASK] =
    {
        .name = COMPOUND_STRING("Volt Mask"),
        .description = COMPOUND_STRING("The user wears a\nmask that boosts\nits Speed and\nAccuracy by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 230 "230" - port battle script */,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_453_*
    },
    [MOVE_FLARE_MASK] =
    {
        .name = COMPOUND_STRING("Flare Mask"),
        .description = COMPOUND_STRING("The user wears a\nmask that boosts\nits Atk and\nSp. Atk by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 230 "230" - port battle script */,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_454_*
    },
    [MOVE_FREEZE_MASK] =
    {
        .name = COMPOUND_STRING("Freeze Mask"),
        .description = COMPOUND_STRING("The user wears a\nmask that boosts\nits Def and\nSp. Def by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 230 "230" - port battle script */,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .snatchAffected = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_455_*
    },
    [MOVE_ACCELEROCK] =
    {
        .name = COMPOUND_STRING("Accelerock"),
        .description = COMPOUND_STRING("The user smashes into\nthe target at high\nspeed. This move\nalways goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_456_*
    },
    [MOVE_IRON_DRILL] =
    {
        .name = COMPOUND_STRING("Iron Drill"),
        .description = COMPOUND_STRING("The user spins into\nthe target at high\nspeed. This move\nalways goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_457_*
    },
    [MOVE_SHIFT_GEAR] =
    {
        .name = COMPOUND_STRING("Shift Gear"),
        .description = COMPOUND_STRING("Rotating its gears,\nthe user raises its\nAttack and sharply\nraises its Speed."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 231 "231" - port battle script */,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_458_*
    },
    [MOVE_GUNK_SHOT] =
    {
        .name = COMPOUND_STRING("Gunk Shot"),
        .description = COMPOUND_STRING("Filthy garbage is\nshot at the foe.\nIt may also poison\nthe target."),
        .effect = EFFECT_POISON_HIT,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_459_*
    },
    [MOVE_CELL_SHIELD] =
    {
        .name = COMPOUND_STRING("Cell Shield"),
        .description = COMPOUND_STRING("The user hardens\nits body to boost\nits Atk, Def and\nSp.Def by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 232 "232" - port battle script */,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_460_*
    },
    [MOVE_DEMONIC_RUSH] =
    {
        .name = COMPOUND_STRING("Demonic Rush"),
        .description = COMPOUND_STRING("Slashes imbued\nwith miasma that\nmay paralyze\nthe target."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 100,
        .type = TYPE_GHOST,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_461_*
    },
    [MOVE_SOLAR_FLAME] =
    {
        .name = COMPOUND_STRING("Solar Flame"),
        .description = COMPOUND_STRING("A reckless move\nthat blasts foes\nwith a solar\ntempest."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 198 "33Recoil" - port battle script */,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_462_*
    },
    [MOVE_DEMON_RAGE] =
    {
        .name = COMPOUND_STRING("Demon Rage"),
        .description = COMPOUND_STRING("No description\navailable."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 100,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_463_*
    },
    [MOVE_RISING_CLAW] =
    {
        .name = COMPOUND_STRING("Rising Claw"),
        .description = COMPOUND_STRING("No description\navailable."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_464_*
    },
    [MOVE_HYDRO_STEAM] =
    {
        .name = COMPOUND_STRING("Hydro Steam"),
        .description = COMPOUND_STRING("Boiling hot water\nis shot at the\nenemy."),
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_465_*
    },
    [MOVE_THUNDERCLAP] =
    {
        .name = COMPOUND_STRING("Thunderclap"),
        .description = COMPOUND_STRING("This move allows\nthe user to strike\nfirst, if the foe is\nreadying an attack."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 56 "Unused38" - port battle script */,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_466_*
    },
    [MOVE_FIERYBULWARK] =
    {
        .name = COMPOUND_STRING("FieryBulwark"),
        .description = COMPOUND_STRING("A flame charge that\nraises the user's\nDef and Sp.Def\nby 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 233 "233" - port battle script */,
        .power = 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_467_*
    },
    [MOVE_ABYSS_BLAZE] =
    {
        .name = COMPOUND_STRING("Abyss Blaze"),
        .description = COMPOUND_STRING("The foe is hit\nby an explosion\nof miasma that may\nburn the target."),
        .effect = EFFECT_BURN_HIT,
        .power = 100,
        .type = TYPE_AETHER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 50%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_468_*
    },
    [MOVE_ORIGIN_CRUSH] =
    {
        .name = COMPOUND_STRING("Origin Crush"),
        .description = COMPOUND_STRING("A primordial blow\nthat may make\nthe foes flinch."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 100,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_469_*
    },
    [MOVE_BAFFLINGSTEP] =
    {
        .name = COMPOUND_STRING("BafflingStep"),
        .description = COMPOUND_STRING("The foe is stomped\non its head.\nIt may also confuse\nthe target."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 76 "ConfusionHitChance" - port battle script */,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 30%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_470_*
    },
    [MOVE_TOXIC_HERB] =
    {
        .name = COMPOUND_STRING("Toxic Herb"),
        .description = COMPOUND_STRING("Venom-imbued petals\nthat may badly\npoison are thrown\nat the foes."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 236 "236" - port battle script */,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 40%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_471_*
    },
    [MOVE_WEIRD_POTION] =
    {
        .name = COMPOUND_STRING("Weird Potion"),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // animation + sounds: scripts/move_animations/move_472_*
    },
    [MOVE_POTION_BOMB] =
    {
        .name = COMPOUND_STRING("Potion Bomb"),
        .description = COMPOUND_STRING("The user throws\nan explosive potion\nthat may make\nthe foe flinch."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 235 "235" - port battle script */,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_473_*
    },
    [MOVE_WING_TALON] =
    {
        .name = COMPOUND_STRING("Wing Talon"),
        .description = COMPOUND_STRING("Strikes the foe with\nsharp wing claws\nthat may paralyze\nthe target."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 15%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_474_*
    },
    [MOVE_ROCK_HAMMER] =
    {
        .name = COMPOUND_STRING("Rock Hammer"),
        .description = COMPOUND_STRING("The foe is hit by\na hammer blow that\nmay lower its Def\nstat by 1 stage."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 69 "LowerDefense1HitChance" - port battle script */,
        .power = 80,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 20%  -> port to .additionalEffects
        .makesContact = TRUE,
        // animation + sounds: scripts/move_animations/move_475_*
    },
    [MOVE_SHATTER_SHOT] =
    {
        .name = COMPOUND_STRING("Shatter Shot"),
        .description = COMPOUND_STRING("The foe is hit by\na violent storm\nof rocks that also\nhurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = TRUE,
        // animation + sounds: scripts/move_animations/move_476_*
    },
    [MOVE_TWINEEDLE] =
    {
        .name = COMPOUND_STRING("Twineedle"),
        .description = COMPOUND_STRING("The foe is stabbed\ntwice with foreleg\nstingers. It raises\nthe user's Speed by 1."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 74 "Unused4A" - port battle script */,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // secondaryEffectChance (gen3) = 100%  -> port to .additionalEffects
        // animation + sounds: scripts/move_animations/move_477_*
    },
    [MOVE_MOVE_478] =
    {
        .name = COMPOUND_STRING(""),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_478_*
    },
    [MOVE_MOVE_479] =
    {
        .name = COMPOUND_STRING(""),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_479_*
    },
    [MOVE_MOVE_480] =
    {
        .name = COMPOUND_STRING(""),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_480_*
    },
    [MOVE_MOVE_481] =
    {
        .name = COMPOUND_STRING(""),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_481_*
    },
    [MOVE_MOVE_482] =
    {
        .name = COMPOUND_STRING(""),
        .description = COMPOUND_STRING("A potion that causes\ndamage to the foe.\nIf it targets an ally,\nit heals instead."),
        .effect = EFFECT_PLACEHOLDER /* gen3 effect 234 "234" - port battle script */,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        // animation + sounds: scripts/move_animations/move_482_*
    },
};
