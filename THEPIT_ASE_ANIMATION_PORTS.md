# The Pit FireRed `.ase` Animation Port Follow-up

This patch replaces the previous closest-native animation assignments with scripts generated from the FireRed export `.ase.txt` command streams. Pointer operands were translated through the supplied `pokefirered` decompilation wherever a matching FireRed symbol exists, then through safe Emerald-equivalent templates for newer/expansion particles. Raw FireRed addresses are not embedded.

For CFRU/ROM-hack-only visual tasks that have no matching symbol in this Emerald branch, the script keeps the surrounding sprite/sound/timing commands and routes only that missing task to `AnimTask_ThePitAseNoOp`.

| Export Move | Constant | Move | Port Status | Notes |
|---:|---|---|---|---|
| 144 | `MOVE_ABYSS_MIASMA` | Abyss Miasma | converted |  |
| 166 | `MOVE_ABYSS_WRATH` | Abyss Wrath | converted |  |
| 360 | `MOVE_AD_NIHILO` | Ad Nihilo | converted |  |
| 447 | `MOVE_AKASHIC_NOVA` | Akashic Nova | converted |  |
| 442 | `MOVE_ARCANE_BLAST` | Arcane Blast | converted | call:1CE54B->skipped; createsoundtask:0DCF39->AnimTask_ThePitAseNoOp |
| 356 | `MOVE_ASTRAL_GLEAM` | Astral Gleam | converted |  |
| 439 | `MOVE_ATROPHIC_EYE` | Atrophic Eye | converted |  |
| 370 | `MOVE_AZURE_FLOOD` | Azure Flood | converted |  |
| 470 | `MOVE_BAFFLINGSTEP` | BafflingStep | converted |  |
| 391 | `MOVE_BRIGHT_SONG` | Bright Song | converted |  |
| 431 | `MOVE_CALL_ALLIES` | Call: Allies | converted |  |
| 430 | `MOVE_CALL_LION` | Call: Lion | converted |  |
| 429 | `MOVE_CALL_OWL` | Call: Owl | converted |  |
| 428 | `MOVE_CALL_SNAKE` | Call: Snake | converted |  |
| 460 | `MOVE_CELL_SHIELD` | Cell Shield | converted |  |
| 420 | `MOVE_CHAINWEATHER` | ChainWeather | converted | createsoundtask:0DCF39->AnimTask_ThePitAseNoOp |
| 421 | `MOVE_CHAIN_KILLER` | Chain Killer | converted |  |
| 422 | `MOVE_CORKSCREW` | Corkscrew | converted | createvisualtask:098E91->AnimTask_ThePitAseNoOp |
| 363 | `MOVE_COSMIC_SLASH` | Cosmic Slash | converted |  |
| 401 | `MOVE_CRAZED_SHOUT` | Crazed Shout | converted |  |
| 426 | `MOVE_DARKNESSFIST` | DarknessFist | converted |  |
| 461 | `MOVE_DEMONIC_RUSH` | Demonic Rush | converted | createvisualtask:098E91->AnimTask_ThePitAseNoOp |
| 412 | `MOVE_DIVINE_STORM` | Divine Storm | converted |  |
| 404 | `MOVE_DOUBLEHAMMER` | DoubleHammer | converted | call:1CA6D1->skipped |
| 131 | `MOVE_ELECTROSHOCK` | Electroshock | converted |  |
| 364 | `MOVE_ENERGY_EDGE` | Energy Edge | converted |  |
| 359 | `MOVE_ETHERIC_BOON` | Etheric Boon | converted |  |
| 386 | `MOVE_FIRST_PRESS` | First Press | converted |  |
| 454 | `MOVE_FLARE_MASK` | Flare Mask | converted | createvisualtask:0BACED->AnimTask_ThePitAseNoOp |
| 450 | `MOVE_FREEZERIPPLE` | FreezeRipple | converted |  |
| 455 | `MOVE_FREEZE_MASK` | Freeze Mask | converted | createvisualtask:0BACED->AnimTask_ThePitAseNoOp |
| 411 | `MOVE_FROST_CURSE` | Frost Curse | converted | createvisualtask:0B68C9->AnimTask_ThePitAseNoOp |
| 414 | `MOVE_FUKUBARI` | Fukubari | converted |  |
| 435 | `MOVE_HARVESTPARTY` | HarvestParty | converted | call:1D5A07->skipped |
| 160 | `MOVE_HEAL` | Heal | converted |  |
| 406 | `MOVE_ICY_ARIA` | Icy Aria | converted | call:1CE7B8->skipped |
| 457 | `MOVE_IRON_DRILL` | Iron Drill | converted |  |
| 413 | `MOVE_IZUNA` | Izuna | converted |  |
| 415 | `MOVE_KUMOGAKURE` | Kumogakure | converted |  |
| 425 | `MOVE_LEADING_BLOW` | Leading Blow | converted |  |
| 392 | `MOVE_LIFE_BALLAD` | Life Ballad | converted |  |
| 381 | `MOVE_LIFE_CONTROL` | Life Control | converted |  |
| 355 | `MOVE_LIGHT_SHOT` | Light Shot | converted |  |
| 448 | `MOVE_LIMIT_BREAK` | Limit Break | converted |  |
| 436 | `MOVE_LULLABY` | Lullaby | converted |  |
| 369 | `MOVE_MEGALODIVE` | Megalodive | converted |  |
| 433 | `MOVE_MESMERIZE` | Mesmerize | converted |  |
| 358 | `MOVE_METEOR` | Meteor | converted | createsprite:1AE5A20->gBasicHitSplatSpriteTemplate |
| 362 | `MOVE_MIND_BASH` | Mind Bash | converted |  |
| 417 | `MOVE_NOBLE_ORDER` | Noble Order | converted | createvisualtask:0BACED->AnimTask_ThePitAseNoOp |
| 451 | `MOVE_OCEAN_RAVE` | Ocean Rave | converted |  |
| 424 | `MOVE_ONE_TWOPUNCH` | One-TwoPunch | converted |  |
| 469 | `MOVE_ORIGIN_CRUSH` | Origin Crush | converted |  |
| 438 | `MOVE_PANIC_SPORES` | Panic Spores | converted |  |
| 403 | `MOVE_PHALANXGUARD` | PhalanxGuard | converted |  |
| 473 | `MOVE_POTION_BOMB` | Potion Bomb | converted |  |
| 432 | `MOVE_PRIMAL_DRUMS` | Primal Drums | converted |  |
| 357 | `MOVE_RADIANT_STAR` | Radiant Star | converted | createsoundtask:0DCF39->AnimTask_ThePitAseNoOp |
| 393 | `MOVE_RAPID_FIRE` | Rapid Fire | converted |  |
| 475 | `MOVE_ROCK_HAMMER` | Rock Hammer | converted |  |
| 434 | `MOVE_ROTTEN_EGG` | Rotten Egg | converted | createvisualtask:0AFD81->AnimTask_ThePitAseNoOp |
| 452 | `MOVE_ROYAL_ORDER` | Royal Order | converted |  |
| 444 | `MOVE_SCYTHE_DANCE` | Scythe Dance | converted |  |
| 372 | `MOVE_SEALINGLIGHT` | SealingLight | converted | call:1D5A07->skipped; createvisualtask:0BA47D->AnimTask_ThePitAseNoOp |
| 476 | `MOVE_SHATTER_SHOT` | Shatter Shot | converted | createvisualtask:0E2519->AnimTask_ThePitAseNoOp |
| 366 | `MOVE_SHOGUN_DECOY` | Shogun Decoy | converted |  |
| 449 | `MOVE_SLASHRAMPAGE` | SlashRampage | converted |  |
| 462 | `MOVE_SOLAR_FLAME` | Solar Flame | converted | call:1D5A07->skipped; createvisualtask:0BA47D->AnimTask_ThePitAseNoOp |
| 446 | `MOVE_SONIC_RAID` | Sonic Raid | converted |  |
| 368 | `MOVE_SOUL_TRADE` | Soul Trade | converted | createvisualtask:0B6021->AnimTask_ThePitAseNoOp |
| 419 | `MOVE_SPOREBARRAGE` | SporeBarrage | converted | call:1B04AF0->skipped |
| 390 | `MOVE_SPRING_TANGO` | Spring Tango | converted |  |
| 382 | `MOVE_STAR_DROP` | Star Drop | converted |  |
| 405 | `MOVE_STOMP_CRUSH` | Stomp Crush | converted |  |
| 437 | `MOVE_STRANGESEEDS` | StrangeSeeds | converted |  |
| 410 | `MOVE_SUBZERO_GALE` | Subzero Gale | converted | call:1CE7B8->skipped |
| 389 | `MOVE_SUMMER_TANGO` | Summer Tango | converted |  |
| 416 | `MOVE_TAGEN_BATTOU` | Tagen Battou | converted |  |
| 441 | `MOVE_TIME_CIRCLE` | Time Circle | converted |  |
| 423 | `MOVE_TITAN_KILLER` | Titan Killer | converted |  |
| 471 | `MOVE_TOXIC_HERB` | Toxic Herb | converted |  |
| 394 | `MOVE_TOXIC_REAP` | Toxic Reap | converted |  |
| 418 | `MOVE_VEIL_ORDER` | Veil Order | converted | createvisualtask:0BACED->AnimTask_ThePitAseNoOp |
| 407 | `MOVE_VENOM_GUST` | Venom Gust | converted |  |
| 453 | `MOVE_VOLT_MASK` | Volt Mask | converted | createvisualtask:0BACED->AnimTask_ThePitAseNoOp |
| 399 | `MOVE_VOLT_WINGS` | Volt Wings | converted |  |
| 427 | `MOVE_WAKINGCHAKRA` | WakingChakra | converted |  |
| 440 | `MOVE_WARDING_MIST` | Warding Mist | converted | call:1B0AB30->skipped |
| 409 | `MOVE_WATER_BOMB` | Water Bomb | converted |  |
| 237 | `MOVE_WATER_TACKLE` | Water Tackle | converted |  |
| 472 | `MOVE_WEIRD_POTION` | Weird Potion | converted |  |
| 402 | `MOVE_WHIP_RIPPER` | Whip Ripper | converted |  |
| 395 | `MOVE_WILT_MIASMA` | Wilt. Miasma | converted |  |
| 474 | `MOVE_WING_TALON` | Wing Talon | converted |  |
| 340 | `MOVE_YGGDRAIN` | Yggdrain | converted |  |
| 408 | `MOVE_YGGDRASLASH` | Yggdraslash | converted |  |
| 365 | `MOVE__5_RING_SWORD` | 5-Ring Sword | converted |  |
