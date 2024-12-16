PitBoss_BossEncounter::
	lock
	faceplayer
	setflag FLAG_START_BOSS_ENCOUNTER
	special HealPlayerParty
	goto_if_set FLAG_DOUBLES_MODE, PitBoss_CommonScriptDoubles
	trainerbattle_single TRAINER_RANDOM_PIT_BOSS, PitArena_Text_Intro, PitArena_Text_Defeat, PitBoss_CommonAfterBattleScript
	clearflag FLAG_START_BOSS_ENCOUNTER
	goto PitBoss_CommonAfterBattleScript
	release
	end

PitBoss_CommonScriptDoubles::
	trainerbattle_double TRAINER_RANDOM_PIT_BOSS_DOUBLES, PitArena_Text_Intro, PitArena_Text_Defeat, PitArena_Text_NotEnoughMons, PitBoss_CommonAfterBattleScript
	goto PitBoss_CommonAfterBattleScript
	release
	end

PitBoss_CommonAfterBattleScript::
	clearflag FLAG_START_BOSS_ENCOUNTER
	goto_if_eq VAR_PIT_FLOOR, 100, PitBoss_FinalBossAfterBattle
	callnative Check50FloorMode
	goto_if_eq VAR_TEMP_A, 0, PitBoss_ContinueAfterBattleScript
	goto_if_eq VAR_PIT_FLOOR, 50, PitBoss_FinalBossAfterBattle
PitBoss_ContinueAfterBattleScript::
	callnative SetAutosaveFlag
	goto_if_unset FLAG_AUTO_SAVE, PitBoss_NoAutoSave
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitBoss_NoAutoSave::
	lock
	callnative BufferMapFloorString
	callnative Check3MonMode
	goto_if_eq VAR_TEMP_A, 1, PitBoss_3MonMode
	callnative CheckNoCaseMode
	goto_if_eq VAR_TEMP_A, 1, PitBoss_NoCaseModeMode
	callnative SetRandomGiveMonRewardEncounters
	warpteleport MAP_PIT_WILD_ENCOUNTER_FLOOR, 9, 12
	waitstate
	release
	end

PitBoss_PartyFullRemoveOne::
	message PitGiveMonCommon_GiveMonFullNothingChosen_Text1
	waitbuttonpress
	msgbox PitGiveMonCommon_GiveMonFullNothingChosen_Text2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitBoss_NoCaseModeMode2
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, PitBoss_NoCaseModeMode2
	callnative RemovePartyPokemon
	goto PitBoss_NoCaseModeMode2

PitBoss_NoCaseModeMode::
	callnative PlayerPartyCountToResultVar
	goto_if_eq VAR_RESULT, 6, PitBoss_PartyFullRemoveOne
PitBoss_NoCaseModeMode2::
	callnative AddNewMonNoCaseMode
PitBoss_3MonMode::
	callnative BufferMapFloorString
	warpteleport MAP_PIT_REST_FLOOR, 9, 9
	waitstate
	release
	end

PitBoss_FinalBossAfterBattle::
	msgbox Pit_EndGameStatue_Text1, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	setflag FLAG_BOSS_ENCOUNTER
	addobject 2
	clearflag FLAG_END_GAME_STATUE
	fadescreen FADE_FROM_BLACK
	callnative SetAutosaveFlag
	goto_if_unset FLAG_AUTO_SAVE, PitFinalBossNoAutoSave
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitFinalBossNoAutoSave:
	release
	end

Pit_EndGameStatue:: 
	lock
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, Pit_EndGameStatue222
	goto_if_eq VAR_RESULT, DIR_SOUTH, Pit_EndGameStatue222
	goto_if_eq VAR_RESULT, DIR_WEST, Pit_EndGameStatue4
	goto_if_eq VAR_RESULT, DIR_EAST, Pit_EndGameStatue3
	release
	end

Pit_EndGameStatue3::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerWestMovement
	waitmovement 0
	goto Pit_EndGameStatue222

Pit_EndGameStatue4::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerEastMovement
	waitmovement 0
	goto Pit_EndGameStatue222

PlayerWestMovement:
	walk_down
	walk_right
	face_up
	step_end

PlayerEastMovement:
	walk_down
	walk_left
	face_up
	step_end

Pit_EndGameStatue222::
	lockall
	callnative ClearAllRandomBossEncounters
	callnative SetAutosaveFlag
	goto_if_unset FLAG_AUTO_SAVE, PitStatueNoAutoSave
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitStatueNoAutoSave:
	msgbox Pit_EndGameStatue_Text2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Pit_EndGameStatue2
	special HealPlayerParty
	callnative BufferMapFloorString
	callnative Check3MonMode
	goto_if_eq VAR_TEMP_A, 1, PitBoss_3MonMode
	callnative CheckNoCaseMode
	goto_if_eq VAR_TEMP_A, 1, PitBoss_NoCaseModeMode
	callnative SetRandomGiveMonRewardEncounters
	warpteleport MAP_PIT_WILD_ENCOUNTER_FLOOR, 9, 12
	waitstate
	release
	end

Pit_EndGameStatue2::
	msgbox Pit_EndGameStatue_TextSaveTeam, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PitStatue_AccessPC
Pit_EndGameStatue5::
	msgbox Pit_EndGameStatue_Text3, MSGBOX_AUTOCLOSE 
	fadescreen FADE_TO_BLACK
	setflag FLAG_TEMP_HOF_VICTORY
	special GameClear
	waitstate
	release
	end

PitStatue_AccessPC::
	playse SE_PC_ON
	setvar VAR_TEMP_B, 1
	callnative SaveTempHofData
	special ShowPokemonStorageSystemPC
	waitstate
	goto Pit_EndGameStatue5
	end

Pit_EndGameStatue_TextSaveTeam:
	.string "Do you want to save your Winning Team?$"


Pit_EndGameStatue_Text1:
	.string "Congratulations, you have.\n"
	.string "completed the Pit of 100\l"
	.string "Trials....\p"
	.string "I hope your descent was\n"
	.string "pleasant.\p"
	.string "You can now return to the\n"
	.string "entrance, prepare for a\l"
	.string "new trial and store your\l"
	.string "winning party in the PC.\p"
	.string "Or continue lower for an\n"
	.string "infinite challenge!$"

Pit_EndGameStatue_Text2:
	.string "Start a new run?            (YES)\n"
	.string "Or continue the grind?      (NO).$"

Pit_EndGameStatue_Text3:
	.string "Well, thanks for playing!$"
