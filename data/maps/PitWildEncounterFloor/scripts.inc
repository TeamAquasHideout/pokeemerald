PitWildEncounterFloor_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PitWildEncounterFloor_OnTransition
	.byte 0

PitWildEncounterFloor_OnTransition:
	callnative TrySetRandomMusic
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	setflashlevel 0
	return

PitWildEncounterFloor_TriggerLeaveEarly::
	lock
	message PitWildEncounterFloor_TriggerLeaveEarly_Text
	dynmultichoice 22, 8, 1, 5, 0, DYN_MULTICHOICE_CB_NONE, PitWildEncounterFloor_TriggerLeaveEarly_Text_Text_77, PitWildEncounterFloor_TriggerLeaveEarly_Text_Text_99
	closemessage
	goto_if_eq VAR_RESULT, 0, PitWildEncounterFloor_TriggerLeaveEarly_End
PitWildEncounterFloor_TriggerLeaveEarly_WarpOut::
	callnative BufferMapFloorString
	warpteleport MAP_PIT_REST_FLOOR, 9, 9
	waitstate
PitWildEncounterFloor_TriggerLeaveEarly_End::
	release
	end

PitWildEncounterFloor_TriggerLeaveEarly_Text_Text_77:
	.string "Stay$"
PitWildEncounterFloor_TriggerLeaveEarly_Text_Text_99:
	.string "Skip Reward$"

PitWildEncounterFloor_TriggerLeaveEarly_Text:
	.string "Are you sure you want to leave early?\n"
	.string "You will miss out on a Pokemon!$"
