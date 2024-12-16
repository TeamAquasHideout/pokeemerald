PitBossArena_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PitBossArena_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PitBossArena_OnFrameTable
	.byte 0

PitBossArena_OnFrameTable:
	map_script_2 VAR_TEMP_0, 0, PitBossArena_CheckForHeal
	.2byte 0

PitBossArena_CheckForHeal::
	delay 20
	callnative CheckIfShouldSkipBossHeal
	goto_if_eq VAR_RESULT, 1, PitBossArena_OnFrame_AutoSave
	msgbox PitBossArena_CheckForHeal_Text, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
PitBossArena_OnFrame_AutoSave::
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitBossArena_OnFrame_End::
	setvar VAR_TEMP_0, 1
	special ShowMapNamePopup
	end

PitBossArena_OnTransition:
	callnative TrySetRandomMusic
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	setflashlevel 0
	return

PitBossArena_CheckForHeal_Text:
	.string "Your party has been mysteriously healed.$"
