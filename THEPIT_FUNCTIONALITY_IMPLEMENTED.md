# The Pit Imported Move and Ability Functionality

This patch ports the battle behavior for the imported FireRed custom moves and abilities into the Emerald decomp battle engine.

## Ability hooks implemented

| Ability | Implemented behavior |
|---|---|
| Abyss Boost | Uses the Beast Boost-style faint hook: after the user KOs a target, raises the user's highest stat by 1 stage. |
| Abyss Grace | Gives the user and its active ally a 1.1x accuracy modifier, matching the exported team accuracy description. |
| Arcanist | Boosts Psychic-type move damage by 20%. |
| Botanist | Gives +1 priority to Toxic Herb, Potion Bomb, and Weird Potion. |
| Eerie Aura | Boosts Ghost-type move damage by 20%. |
| Fafnir | Boosts Electric- and Dragon-type move damage by 20%. |
| Intense Care | Gives +1 priority to moves flagged as healing moves. |
| Omnihunter | Boosts Flying-type move damage by 50%. |
| Omni-Chase | Boosts Speed by 50% while effective weather is active. |
| Radiance | Converts Normal-type moves to Aether-type through the existing -ate type-conversion path. |
| Singularity | Boosts Fire- and Ice-type move damage by 25%. |
| Sovereignty | Gives +1 priority to Noble Order, Royal Order, and Veil Order. |
| Venom Blood | Boosts Poison-type move damage by 50%. |

AI ratings for these imported abilities were also filled in instead of leaving them at TODO/0.

## New custom move effect handlers

The following FireRed-only effects were implemented as native Emerald battle scripts and helpers:

| Move/effect | Implemented behavior |
|---|---|
| Abyss Wrath | Custom counter-any-hit calculator: counters the last physical or special hit from a foe for 2x damage. |
| Atrophic Eye | Lowers both opponents' Defense and Sp. Def by 1 stage. |
| Bright Song | Raises the user's side Accuracy by 2 stages and the partner's Speed by 1 stage. |
| Cell Shield | Raises the user's Attack, Defense, and Sp. Def by 1 stage. |
| Kumogakure | Halves the user's HP, then raises Evasion by 2 stages. |
| Life Ballad | Raises the user's side Speed by 1 stage and cures party status via Aromatherapy behavior. |
| Life Control | Restores 50% of the user's max HP and raises Speed by 1 stage. |
| Limit Break | Raises Attack and Sp. Atk by 1 stage, then lowers Defense and Sp. Def by 1 stage. |
| Noble Order | Raises the user's side Sp. Atk by 1 stage. |
| PhalanxGuard | Raises the user's side Defense by 1 stage. |
| Rotten Egg | Lowers both opponents' Attack and Sp. Atk by 1 stage. |
| Shogun Decoy | Applies Follow Me/center-of-attention behavior and raises Attack and Defense by 1 stage. |
| Spring Tango | Raises the user's Speed by 1 stage, and the partner's Defense and Sp. Def by 1 stage. |
| StrangeSeeds | Lowers both opponents' Speed and Evasion by 1 stage. |
| Summer Tango | Raises the user's Evasion by 1 stage, and the partner's Attack and Sp. Atk by 1 stage. |
| Time Circle | Raises the user's side Speed by 1 stage. |
| Veil Order | Raises the user's side Sp. Def by 1 stage. |
| Volt Mask | Raises the user's Speed and Accuracy by 1 stage. |
| WakingChakra | Applies Aqua Ring-style per-turn healing and raises Speed by 1 stage. |
| Warding Mist | Sets Safeguard and cures party status via Aromatherapy behavior. |
| Wilt. Miasma | Lowers both opponents' Accuracy and Evasion by 1 stage. |

## Existing Emerald effects reused for imported moves

Where the FireRed export described a behavior already supported by pokeemerald-expansion, the imported move was mapped to that native effect instead of adding a duplicate handler. Examples include recoil, Weather Ball, Beat Up/party-size damage, high critical-hit ratio, two-hit attacks, Punishment, level damage, fixed 50% HP damage, Heal Pulse, first-turn-only attacks, Cosmic Power, Attack + Sp. Atk boosts, Frostbite status, bad poison, burn/paralysis/confusion/sleep secondaries, flinching, and self stat drops.

## Remaining notes

- This patch implements battle functionality, not the original FireRed animation bytecode. Imported moves still use the safe placeholder animation assigned during import unless separately ported.
- Leading Blow is approximated with the existing double-power-on-any-status effect. Its export says it hits a second time if the target is burned, paralyzed, poisoned, or asleep; the damage output is close, but it will not trigger separate second-hit side effects.
- Call: Allies uses the expansion Beat Up/party-size damage effect as the closest native equivalent to the export's party-size damage behavior.
