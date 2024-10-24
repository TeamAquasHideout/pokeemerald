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
	callnative SetAutosaveFlag
	goto_if_unset FLAG_AUTO_SAVE, PitBoss_NoAutoSave
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitBoss_NoAutoSave::
	lock
	callnative BufferMapFloorString
	callnative SetRandomGiveMonRewardEncounters
	warpteleport MAP_PIT_WILD_ENCOUNTER_FLOOR, 13, 13
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
	callnative SetAutosaveFlag
	goto_if_unset FLAG_AUTO_SAVE, PitStatueNoAutoSave
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitStatueNoAutoSave:
	msgbox Pit_EndGameStatue_Text2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Pit_EndGameStatue2
	special HealPlayerParty
	removeobject 2
	setflag FLAG_FLOOR_CLEARED
	callnative SetWarpTileActive
	special DrawWholeMapView
	release
	end

Pit_EndGameStatue2::
	msgbox Pit_EndGameStatue_Text3, MSGBOX_AUTOCLOSE 
	fadescreen FADE_TO_BLACK
	special GameClear
	waitstate
	release
	end

Pit_EndGameStatue_Text1:
	.string "Congratulations, you have.\n"
	.string "completed the Pit of 100\l"
	.string "Trials....\p"
	.string "I hope your descent was\n"
	.string "pleasant.$"

Pit_EndGameStatue_Text2:
	.string "Do you want to keep going?$"

Pit_EndGameStatue_Text3:
	.string "Well, thanks for playing!$"