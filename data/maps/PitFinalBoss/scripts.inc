PitFinalBoss_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PitFinalBoss_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PitFinalBoss_OnFrameTable
	.byte 0

PitFinalBoss_OnFrameTable:
	map_script_2 VAR_TEMP_0, 0, PitBossArena_CheckForHeal
	.2byte 0

PitFinalBoss_OnTransition:
	callnative TrySetRandomMusic
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	setflashlevel 0
	return

