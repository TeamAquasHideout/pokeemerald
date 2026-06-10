# The Pit Import: Functionality TODO

Generated from the imported FireRed data in this decomp after the Aether type icon/summary fixes.

## Moves needing battle-effect functionality

80 imported moves still use `EFFECT_PLACEHOLDER`. They compile, but their real FireRed battle-script behavior has not been ported into pokeemerald-expansion yet.

| # | Constant | Move | Type | Category | Imported effect note |
|---:|---|---|---|---|---|
| 848 | `MOVE_ABYSS_MIASMA` | Abyss Miasma | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 72 "LowerSpDefense1HitChance" |
| 849 | `MOVE_ABYSS_WRATH` | Abyss Wrath | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 89 "DoubleBackPhysicalDamage" |
| 850 | `MOVE_AD_NIHILO` | Ad Nihilo | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 12 "Unused0C" |
| 851 | `MOVE_AKASHIC_NOVA` | Akashic Nova | `TYPE_DRAGON` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 198 "33Recoil" |
| 852 | `MOVE_ARCANE_BLAST` | Arcane Blast | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 198 "33Recoil" |
| 854 | `MOVE_ATROPHIC_EYE` | Atrophic Eye | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 227 "227" |
| 855 | `MOVE_AZURE_FLOOD` | Azure Flood | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 55 "Unused37" |
| 856 | `MOVE_BAFFLINGSTEP` | BafflingStep | `TYPE_NORMAL` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 76 "ConfusionHitChance" |
| 857 | `MOVE_BRIGHT_SONG` | Bright Song | `TYPE_ELECTRIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 858 | `MOVE_CALL_ALLIES` | Call: Allies | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 154 "DamageBasedOnPartySize" |
| 859 | `MOVE_CALL_LION` | Call: Lion | `TYPE_FIRE` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 860 | `MOVE_CALL_OWL` | Call: Owl | `TYPE_FLYING` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 218 "218" |
| 861 | `MOVE_CALL_SNAKE` | Call: Snake | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 202 "BadPoisonHitChance" |
| 862 | `MOVE_CELL_SHIELD` | Cell Shield | `TYPE_WATER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 232 "232" |
| 863 | `MOVE_CHAINWEATHER` | ChainWeather | `TYPE_NORMAL` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 203 "WeatherBall" |
| 864 | `MOVE_CHAIN_KILLER` | Chain Killer | `TYPE_FLYING` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 220 "220" |
| 865 | `MOVE_CORKSCREW` | Corkscrew | `TYPE_FIGHTING` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 867 | `MOVE_CRAZED_SHOUT` | Crazed Shout | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 76 "ConfusionHitChance" |
| 868 | `MOVE_DARKNESSFIST` | DarknessFist | `TYPE_DARK` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 198 "33Recoil" |
| 869 | `MOVE_DEMONIC_RUSH` | Demonic Rush | `TYPE_GHOST` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 870 | `MOVE_DIVINE_STORM` | Divine Storm | `TYPE_ELECTRIC` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 871 | `MOVE_DOUBLEHAMMER` | DoubleHammer | `TYPE_STEEL` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 872 | `MOVE_ELECTROSHOCK` | Electroshock | `TYPE_ELECTRIC` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 873 | `MOVE_ENERGY_EDGE` | Energy Edge | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 69 "LowerDefense1HitChance" |
| 874 | `MOVE_ETHERIC_BOON` | Etheric Boon | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 14 "Unused0E" |
| 875 | `MOVE_FIRST_PRESS` | First Press | `TYPE_BUG` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 216 "216" |
| 876 | `MOVE_FLARE_MASK` | Flare Mask | `TYPE_FIRE` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 230 "230" |
| 877 | `MOVE_FREEZERIPPLE` | FreezeRipple | `TYPE_ICE` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 878 | `MOVE_FREEZE_MASK` | Freeze Mask | `TYPE_ICE` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 230 "230" |
| 879 | `MOVE_FROST_CURSE` | Frost Curse | `TYPE_ICE` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 215 "215" |
| 880 | `MOVE_FUKUBARI` | Fukubari | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 218 "218" |
| 881 | `MOVE_HARVESTPARTY` | HarvestParty | `TYPE_GROUND` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 220 "220" |
| 882 | `MOVE_HEAL` | Heal | `TYPE_NORMAL` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 157 "RestoreHPOrAllyInField" |
| 883 | `MOVE_ICY_ARIA` | Icy Aria | `TYPE_ICE` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 885 | `MOVE_IZUNA` | Izuna | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 886 | `MOVE_KUMOGAKURE` | Kumogakure | `TYPE_DARK` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 219 "219" |
| 887 | `MOVE_LEADING_BLOW` | Leading Blow | `TYPE_FIGHTING` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 222 "222" |
| 888 | `MOVE_LIFE_BALLAD` | Life Ballad | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 889 | `MOVE_LIFE_CONTROL` | Life Control | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 63 "Unused3F" |
| 891 | `MOVE_LIMIT_BREAK` | Limit Break | `TYPE_DRAGON` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 212 "RaiseAttack1Speed1Primary" |
| 892 | `MOVE_LULLABY` | Lullaby | `TYPE_NORMAL` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 893 | `MOVE_MEGALODIVE` | Megalodive | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 894 | `MOVE_MESMERIZE` | Mesmerize | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 218 "218" |
| 895 | `MOVE_METEOR` | Meteor | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 204 "LowerSpAttack2Self" |
| 897 | `MOVE_NOBLE_ORDER` | Noble Order | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 224 "224" |
| 898 | `MOVE_OCEAN_RAVE` | Ocean Rave | `TYPE_WATER` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 899 | `MOVE_ONE_TWOPUNCH` | One-TwoPunch | `TYPE_FIGHTING` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 900 | `MOVE_ORIGIN_CRUSH` | Origin Crush | `TYPE_DARK` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 902 | `MOVE_PHALANXGUARD` | PhalanxGuard | `TYPE_FIGHTING` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 903 | `MOVE_POTION_BOMB` | Potion Bomb | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 235 "235" |
| 905 | `MOVE_RADIANT_STAR` | Radiant Star | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 70 "LowerSpeed1HitChance" |
| 907 | `MOVE_ROCK_HAMMER` | Rock Hammer | `TYPE_ROCK` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 69 "LowerDefense1HitChance" |
| 908 | `MOVE_ROTTEN_EGG` | Rotten Egg | `TYPE_NORMAL` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 225 "225" |
| 909 | `MOVE_ROYAL_ORDER` | Royal Order | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 229 "229" |
| 911 | `MOVE_SEALINGLIGHT` | SealingLight | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 913 | `MOVE_SHOGUN_DECOY` | Shogun Decoy | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 21 "Unused15" |
| 914 | `MOVE_SLASHRAMPAGE` | SlashRampage | `TYPE_FLYING` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 915 | `MOVE_SOLAR_FLAME` | Solar Flame | `TYPE_FIRE` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 198 "33Recoil" |
| 919 | `MOVE_SPRING_TANGO` | Spring Tango | `TYPE_GRASS` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 920 | `MOVE_STAR_DROP` | Star Drop | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 64 "Unused40" |
| 922 | `MOVE_STRANGESEEDS` | StrangeSeeds | `TYPE_GRASS` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 226 "226" |
| 923 | `MOVE_SUBZERO_GALE` | Subzero Gale | `TYPE_ICE` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 924 | `MOVE_SUMMER_TANGO` | Summer Tango | `TYPE_FIRE` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 925 | `MOVE_TAGEN_BATTOU` | Tagen Battou | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 217 "217" |
| 926 | `MOVE_TIME_CIRCLE` | Time Circle | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 110 "Unused6E" |
| 927 | `MOVE_TITAN_KILLER` | Titan Killer | `TYPE_FIGHTING` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 221 "221" |
| 928 | `MOVE_TOXIC_HERB` | Toxic Herb | `TYPE_GRASS` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 236 "236" |
| 929 | `MOVE_TOXIC_REAP` | Toxic Reap | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 202 "BadPoisonHitChance" |
| 930 | `MOVE_VEIL_ORDER` | Veil Order | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 224 "224" |
| 931 | `MOVE_VENOM_GUST` | Venom Gust | `TYPE_POISON` | `DAMAGE_CATEGORY_PHYSICAL` | gen3 effect 202 "BadPoisonHitChance" |
| 932 | `MOVE_VOLT_MASK` | Volt Mask | `TYPE_ELECTRIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 230 "230" |
| 933 | `MOVE_VOLT_WINGS` | Volt Wings | `TYPE_ELECTRIC` | `DAMAGE_CATEGORY_SPECIAL` | FireRed-only imported effect |
| 934 | `MOVE_WAKINGCHAKRA` | WakingChakra | `TYPE_PSYCHIC` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 223 "223" |
| 935 | `MOVE_WARDING_MIST` | Warding Mist | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 228 "228" |
| 936 | `MOVE_WATER_BOMB` | Water Bomb | `TYPE_WATER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 214 "214" |
| 938 | `MOVE_WEIRD_POTION` | Weird Potion | `TYPE_GRASS` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 234 "234" |
| 939 | `MOVE_WHIP_RIPPER` | Whip Ripper | `TYPE_GROUND` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 940 | `MOVE_WILT_MIASMA` | Wilt. Miasma | `TYPE_DARK` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 131 "Unused83" |
| 941 | `MOVE_WING_TALON` | Wing Talon | `TYPE_FLYING` | `DAMAGE_CATEGORY_PHYSICAL` | FireRed-only imported effect |
| 943 | `MOVE_YGGDRASLASH` | Yggdraslash | `TYPE_AETHER` | `DAMAGE_CATEGORY_SPECIAL` | gen3 effect 103 "NormalPlusPriority" |

## Imported moves with basic function already mapped

17 imported moves have a non-placeholder `effect` constant. These may still need custom animations, but their basic battle function is not currently marked as missing.

| # | Constant | Move | Mapped effect |
|---:|---|---|---|
| 853 | `MOVE_ASTRAL_GLEAM` | Astral Gleam | `EFFECT_HIT` |
| 866 | `MOVE_COSMIC_SLASH` | Cosmic Slash | `EFFECT_HIT` |
| 884 | `MOVE_IRON_DRILL` | Iron Drill | `EFFECT_HIT` |
| 890 | `MOVE_LIGHT_SHOT` | Light Shot | `EFFECT_HIT` |
| 896 | `MOVE_MIND_BASH` | Mind Bash | `EFFECT_HIT` |
| 901 | `MOVE_PANIC_SPORES` | Panic Spores | `EFFECT_CONFUSE` |
| 904 | `MOVE_PRIMAL_DRUMS` | Primal Drums | `EFFECT_DEFENSE_DOWN_2` |
| 906 | `MOVE_RAPID_FIRE` | Rapid Fire | `EFFECT_MULTI_HIT` |
| 910 | `MOVE_SCYTHE_DANCE` | Scythe Dance | `EFFECT_MULTI_HIT` |
| 912 | `MOVE_SHATTER_SHOT` | Shatter Shot | `EFFECT_RECOIL` |
| 916 | `MOVE_SONIC_RAID` | Sonic Raid | `EFFECT_HIT` |
| 917 | `MOVE_SOUL_TRADE` | Soul Trade | `EFFECT_ABSORB` |
| 918 | `MOVE_SPOREBARRAGE` | SporeBarrage | `EFFECT_MULTI_HIT` |
| 921 | `MOVE_STOMP_CRUSH` | Stomp Crush | `EFFECT_HIT` |
| 937 | `MOVE_WATER_TACKLE` | Water Tackle | `EFFECT_HIT` |
| 942 | `MOVE_YGGDRAIN` | Yggdrain | `EFFECT_ABSORB` |
| 944 | `MOVE__5_RING_SWORD` | 5-Ring Sword | `EFFECT_MULTI_HIT` |

## Abilities needing battle-engine functionality

All 13 imported custom abilities currently only have data entries and descriptions. They need battle-engine hooks/AI ratings to implement their described behavior.

| # | Constant | Ability | Intended behavior from import |
|---:|---|---|---|
| 311 | `ABILITY_ABYSS_BOOST` | Abyss Boost | KOing a foe ups highest stat. |
| 312 | `ABILITY_ABYSS_GRACE` | Abyss Grace | Boosts team accuracy by 10%. |
| 313 | `ABILITY_ARCANIST` | Arcanist | Boosts Psychic-type moves by 20%. |
| 314 | `ABILITY_BOTANIST` | Botanist | Herb & Potion moves gain priority. |
| 315 | `ABILITY_EERIE_AURA` | Eerie Aura | Boosts Ghost-type moves by 20%. |
| 316 | `ABILITY_FAFNIR` | Fafnir | Boosts Electr and Dragon by 20%. |
| 317 | `ABILITY_INTENSE_CARE` | Intense Care | Healing moves have priority. |
| 318 | `ABILITY_OMNIHUNTER` | Omnihunter | Boosts Flying-type moves by 50%. |
| 319 | `ABILITY_OMNI_CHASE` | Omni-Chase | 50% Speed up during weather. |
| 320 | `ABILITY_RADIANCE` | Radiance | Normal moves become Aether. |
| 321 | `ABILITY_SINGULARITY` | Singularity | Boosts Fire & Ice-type moves by 25%. |
| 322 | `ABILITY_SOVEREIGNTY` | Sovereignty | Order moves have priority. |
| 323 | `ABILITY_VENOM_BLOOD` | Venom Blood | Boosts Poison-type moves by 50%. |

## Animation note

The FireRed `.ase` and `.bse` bytecode is preserved under `thepit_imported_raw/`, but it is not directly compatible with pokeemerald-expansion animation/battle-script formats. Custom imported moves still use placeholder Emerald animations unless manually ported.
