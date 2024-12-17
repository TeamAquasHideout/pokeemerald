.set LOCALID_ARCHIE, 4
.set LOCALID_WIZ1989, 5

PitEntrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PitArena_Entrance
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PitEntrance_OnFrameTable
	.byte 0

PitEntrance_OnFrameTable:
	map_script_2 VAR_TEMP_0, 0, PitEntrance_CheckForAutoSave
	.2byte 0

PitEntrance_CheckForAutoSave::
	callnative CheckIfSavedBefore
	goto_if_eq VAR_RESULT, 0, PitEntrance_OnFrame_CheckForAutoSave_Skip
	clearflag FLAG_SAVING_FIELD_EFFECT
	dofieldeffect(FLDEFF_SAVING)
	waitfieldeffect(FLDEFF_SAVING)
	callnative AutoSave
PitEntrance_OnFrame_CheckForAutoSave_Skip::
	@Full dex check for Shiny Dust reward
	callnative CheckAndGiveShinyDust
	goto_if_eq VAR_RESULT, 0, PitEntrance_OnFrame_CheckForAutoSave_SkipShinyDustReward
	callnative CheckIfHasRecievedShinyDust
	goto_if_eq VAR_RESULT, 0, PitEntrance_OnFrame_CheckForAutoSave_SkipShinyDustReward
	lock
	clearflag FLAG_HIDE_ARCHIE
	clearflag FLAG_HIDE_WIZ1989
	addobject LOCALID_ARCHIE, MAP_PIT_ENTRANCE
	setobjectxy LOCALID_ARCHIE, 18, 7
	addobject LOCALID_WIZ1989, MAP_PIT_ENTRANCE
	setobjectxy LOCALID_WIZ1989, 18, 6
	applymovement LOCALID_ARCHIE Movement_Archie
	applymovement LOCALID_WIZ1989 Movement_wiz1989
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox PitEntrance_Text_CheckIfHasRecievedShinyDust, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_SHINY_DUST, 1
	closemessage
	delay 60
	applymovement LOCALID_ARCHIE Movement_Archie_Leave
	applymovement LOCALID_WIZ1989 Movement_wiz1989_Leave
	waitmovement 0
	setflag FLAG_HIDE_ARCHIE
	setflag FLAG_HIDE_WIZ1989
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_WIZ1989
	release
PitEntrance_OnFrame_CheckForAutoSave_SkipShinyDustReward::
	@Full dex check for Shedinja reward
	lock
	callnative CheckAndGiveShedinja
	goto_if_eq VAR_RESULT, 0, PitEntrance_OnFrame_CheckForAutoSave_SkipShedinjaReward
	callnative CheckIfHasReceivedShedinja
	goto_if_eq VAR_RESULT, 0, PitEntrance_OnFrame_CheckForAutoSave_SkipShedinjaReward
	clearflag FLAG_HIDE_ARCHIE
	clearflag FLAG_HIDE_WIZ1989
	addobject LOCALID_ARCHIE, MAP_PIT_ENTRANCE
	setobjectxy LOCALID_ARCHIE, 18, 7
	addobject LOCALID_WIZ1989, MAP_PIT_ENTRANCE
	setobjectxy LOCALID_WIZ1989, 18, 6
	applymovement LOCALID_ARCHIE Movement_Archie
	applymovement LOCALID_WIZ1989 Movement_wiz1989
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox PitEntrance_Text_CheckIfHasReceivedShedinja, MSGBOX_DEFAULT
	setflag FLAG_SEND_TO_PC
	setflag FLAG_DONT_RANDOMIZE_NEXT_MON
	givemon SPECIES_SHEDINJA, 100
	clearflag FLAG_DONT_RANDOMIZE_NEXT_MON
	clearflag FLAG_SEND_TO_PC
	goto PitEntrance_SendShedinjaPC
PitEntrance_OnFrame_CheckForAutoSave_FinishShedinjaScript::
	delay 60
	closemessage
	applymovement LOCALID_ARCHIE Movement_Archie_Leave
	applymovement LOCALID_WIZ1989 Movement_wiz1989_Leave
	waitmovement 0
	setflag FLAG_HIDE_ARCHIE
	setflag FLAG_HIDE_WIZ1989
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_WIZ1989
	release
PitEntrance_OnFrame_CheckForAutoSave_SkipShedinjaReward::
	setvar VAR_TEMP_0, 1
	special ShowMapNamePopup
	end

PitEntrance_SendShedinjaPC::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SHEDINJA
	playfanfare MUS_OBTAIN_ITEM
	message PitEntrance_Text_ObtainedShedinja
	waitmessage
	waitfanfare
	call Common_EventScript_TransferredToPC
	goto PitEntrance_OnFrame_CheckForAutoSave_FinishShedinjaScript

PitEntrance_Text_CheckIfHasRecievedShinyDust:
	.string "Congrats on filling out your Pokédex!\n"
	.string "Here is a reward!$"

PitEntrance_Text_CheckIfHasReceivedShedinja:
	.string "Congrats on having seen all species\n"
	.string "listed in your Pokédex.\p"
	.string "Here is your reward!$"

PitEntrance_Text_ObtainedShedinja:
	.string "{PLAYER} obtained a SHEDINJA.$"

PitArena_Entrance:
	setflag FLAG_HIDE_ARCHIE @always hide these NPCs
	setflag FLAG_HIDE_WIZ1989 @always hide these NPCs
	goto_if_set FLAG_PIT_STARTED, PitArena_EntranceEnd
	callnative SetOnMapLoadDefaultOptions
	setvar VAR_PIT_FLOOR, 0
	setflag FLAG_PIT_STARTED
	setflag	FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_SYS_NATIONAL_DEX
	setflag FLAG_SYS_POKEDEX_GET
	special EnableNationalPokedex
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setflashlevel 0
PitArena_EntranceEnd:
	return

PitEntrance_Warp::
	lockall
	setflag FLAG_PIT_ENTERED
	setvar VAR_PIT_FLOOR, 1
	setvar VAR_REWARD_STATE, 0
	setflag FLAG_EXP_SHARE
	callnative BufferMapFloorString
	callnative SetRandomTrainers
	callnative SetRandomMonEncounter
	additem ITEM_SACRED_ASH, 1
	additem ITEM_POTION, 5
	additem ITEM_SUPER_POTION, 2
	additem ITEM_FULL_RESTORE, 1
	additem ITEM_REVIVE, 2
	additem ITEM_FULL_HEAL, 3
	additem ITEM_ETHER, 2
	additem ITEM_ELIXIR, 1
	additem ITEM_ESCAPE_ROPE, 1
	callnative CheckAndGiveShinyDust
	goto_if_eq VAR_RESULT, 0, PitEntrance_Warp_SkipShinyDust
	additem ITEM_SHINY_DUST, 1
PitEntrance_Warp_SkipShinyDust::
#ifdef PIT_GEN_9_MODE
	additem ITEM_MEGA_RING, 1
	@additem ITEM_TERA_ORB, 1
	additem ITEM_Z_POWER_RING, 1
#endif
	additem ITEM_EXP_SHARE, 1
	setflag FLAG_SYS_POKEMON_GET
	warpteleport MAP_PIT_ARENA, 9, 7
	waitstate
	releaseall
	end

PitEntrance_Sign_Luck:
	.string "Good Luck...$"

PitEntrance_ModeMenu:
	.string "Please choose your game mode.$"

PitEntrance_ReadyToStart:
	.string "Are you ready to start?$"

PitEntrance_MsgYes:
	.string "Let's go!$"

PitEntrance_MsgModeMenu:
	.string "Change game mode again!$"

PitEntrance_StartBag::
	lockall
PitEntrace_ModeMenu::
	setflag FLAG_CASE_STARTER_MODE
	callnative InitTrainerIdAndNameData
	callnative CheckNoCaseMode
	goto_if_eq VAR_TEMP_A, 1, PitEntrace_NoCaseModeMode
	callnative StartNewPokeballCaseUI
	waitstate
	goto PitEntrace_SkipOverNoCaseModeMode
PitEntrace_NoCaseModeMode::
	callnative AddInitial3MonsNoCaseMode
PitEntrace_SkipOverNoCaseModeMode::
	clearflag FLAG_CASE_STARTER_MODE
	removeobject 1
	setflag FLAG_STARTER_CHOICE_BAG

	specialvar VAR_RESULT, GetPlayerFacingDirection
	call_if_eq VAR_RESULT, DIR_NORTH, PitEntrance_EndGameStatue1
	call_if_eq VAR_RESULT, DIR_SOUTH, PitEntrance_EndGameStatue2
	call_if_eq VAR_RESULT, DIR_WEST, PitEntrance_EndGameStatue4
	call_if_eq VAR_RESULT, DIR_EAST, PitEntrance_EndGameStatue3

	msgbox PitEntrance_Sign_Luck, MSGBOX_DEFAULT
	goto PitEntrance_Warp

	releaseall
	end

PitEntrance_EndGameStatue1::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerNorthMovement2
	waitmovement 0
	return

PitEntrance_EndGameStatue2::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerSouthMovement2
	waitmovement 0
	return

PitEntrance_EndGameStatue3::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerWestMovement2
	waitmovement 0
	return

PitEntrance_EndGameStatue4::
	applymovement OBJ_EVENT_ID_PLAYER, PlayerEastMovement2
	waitmovement 0
	return

PlayerWestMovement2:
	walk_right
	face_down
	step_end

PlayerEastMovement2:
	walk_left
	face_down
	step_end

PlayerNorthMovement2:
	walk_up
	face_down
	step_end

PlayerSouthMovement2:
	walk_down
	face_down
	step_end

PitEntrance_EventScript_Sign::
	lockall
	msgbox PitEntrance_Text_Rules, MSGBOX_DEFAULT
PitEntrance_EventScript_Sign_Hook::
	message PitEntrance_Sign_Text
	dynmultichoice 17, 0, 0, 6, VAR_TEMP_9, DYN_MULTICHOICE_CB_NONE, PitEntrance_Sign_Option0, PitEntrance_Sign_Option1, PitEntrance_Sign_Option_GameModes, PitEntrance_Sign_Option_Nickname, PitEntrance_Sign_Option6, PitEntrance_Sign_Option2, PitEntrance_Sign_Option4, PitEntrance_Sign_Option5, PitEntrance_Sign_Option3
	closemessage
	copyvar VAR_TEMP_9, VAR_RESULT
	goto_if_eq VAR_RESULT, 0, PitEntrance_MoreInfo
	goto_if_eq VAR_RESULT, 1, PitEntrance_BattleInfo
	goto_if_eq VAR_RESULT, 2, PitEntrance_HardModeInfo
	goto_if_eq VAR_RESULT, 3, PitEntrance_ChangeNickname
	goto_if_eq VAR_RESULT, 4, PitEntrance_SecretBaseInfo
	goto_if_eq VAR_RESULT, 5, PitEntrance_Credits
	goto_if_eq VAR_RESULT, 6, PitEntrance_Bugs
	goto_if_eq VAR_RESULT, 7, PitEntrance_Discord
	goto_if_eq VAR_RESULT, 8, PitEntrance_Cheats
	release
	end

PitEntrance_SecretBaseInfo:
	msgbox PitEntrance_Text_SecretBaseInfo, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_Text_SecretBaseInfo::
	.string "As you defeat trainers you are awarded\n"
	.string "with BP for every victory, this can be\l"
	.string "traded in the Pit Entrance for decor\l"
	.string "for your Secret Base.\p"
	.string "Next to the Decor Shop Employee is the\n"
	.string "Secret Base Tree, this tree randomizes\l"
	.string "every time you enter it to a different\l"
	.string "base map until you claim your choice.$"


PitEntrance_MoreInfo:
	msgbox PitEntrance_Text_MoreInfo, MSGBOX_DEFAULT
	msgbox PitEntrance_Text_MoreInfo2, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_BattleInfo:
	msgbox PitEntrance_Text_BattleInfo, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end

PitEntrance_HardModeInfo:
	msgbox PitEntrance_Text_GameModeInfo, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end

PitEntrance_Credits:
	msgbox PitEntrance_Text_Credits, MSGBOX_DEFAULT
	msgbox PitEntrance_Text_Credits2, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_Cheats:
	msgbox PitEntrance_Text_Cheats, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_Bugs:
	msgbox PitEntrance_Text_Bugs, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_Discord:
	msgbox PitEntrance_Text_Discord, MSGBOX_DEFAULT
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_ChangeAvatar:
	goto PitArena_ChangeAvatar
	release
	end 

PitEntrance_ChangeNickname:
	fadescreen FADE_TO_BLACK
	callnative CallRenameScreen
	waitstate
	goto PitEntrance_EventScript_Sign_Hook
	release
	end 

PitEntrance_Sign_Text:
	.string "Would you like more information?$"

PitEntrance_Sign_Option0:
	.string "More Info$"
PitEntrance_Sign_Option1:
	.string "BattleInfo$"
PitEntrance_Sign_Option2:
	.string "Credits$"
PitEntrance_Sign_Option_Nickname:
	.string "Nickname$"
PitEntrance_Sign_Option3:
	.string "Cheats$"
PitEntrance_Sign_Option4:
	.string "Bugs$"
PitEntrance_Sign_Option5:
	.string "Discord$"
PitEntrance_Sign_Option6:
	.string "SecretBase$"
PitEntrance_Sign_Option_GameModes:
	.string "Game Modes$"

PitArena_ChangeAvatar::
	lock
	message PitArena_ChangeAvatarText
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitArena_NPCAvatarChange0, PitArena_NPCAvatarChange1, PitArena_NPCAvatarChange2, PitArena_NPCAvatarChange3, PitArena_NPCAvatarChange4, PitArena_NPCAvatarChange5, PitArena_NPCAvatarChange6, PitArena_NPCAvatarChange7, PitArena_NPCAvatarChange8, PitArena_NPCAvatarChange9, PitArena_NPCAvatarChange10, PitArena_NPCAvatarChange11
	callnative SetPlayerAvatar
	closemessage
	warpteleport MAP_PIT_ENTRANCE, 7, 8
	waitstate
	release
	end

PitArena_ChangeAvatarDebug::
	lock
	message PitArena_ChangeAvatarText
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitArena_NPCAvatarChange0, PitArena_NPCAvatarChange1, PitArena_NPCAvatarChange2, PitArena_NPCAvatarChange3, PitArena_NPCAvatarChange4, PitArena_NPCAvatarChange5, PitArena_NPCAvatarChange6, PitArena_NPCAvatarChange7, PitArena_NPCAvatarChange8, PitArena_NPCAvatarChange9, PitArena_NPCAvatarChange10, PitArena_NPCAvatarChange11
	callnative SetPlayerAvatar
	closemessage
	warpteleport MAP_PIT_ARENA, 9, 7
	waitstate
	release
	end

PitArena_ChangeAvatarText:
	.string "Who do you want to play as?$"

PitArena_NPCAvatarChange0:
	.string "Brendan$"
PitArena_NPCAvatarChange1:
	.string "May$"
PitArena_NPCAvatarChange2:
	.string "Red$"
PitArena_NPCAvatarChange3:
	.string "Leaf$"
PitArena_NPCAvatarChange4:
	.string "Lucas$"
PitArena_NPCAvatarChange5:
	.string "Dawn$"
PitArena_NPCAvatarChange6:
	.string "Steven$"
PitArena_NPCAvatarChange7:
	.string "Cynthia$"
PitArena_NPCAvatarChange8:
	.string "Oak$"
PitArena_NPCAvatarChange9:
	.string "Phoebe$"
PitArena_NPCAvatarChange10:
	.string "Ethan$"
PitArena_NPCAvatarChange11:
	.string "Lyra$"


PitEntrance_Text_MoreInfo::
	.string "In this challenge you start with 3\n"
	.string "random Pokémon and must fight around\l"
	.string "200 trainers in a randomized gauntlet.\p"
	.string "You and each trainer have random mons.\n"
	.string "Trainer Pokémon levels are tied to the\l"
	.string "floor number, with 1/100 being min/max.\p"
	.string "Trainer numbers are also randomized\n"
	.string "ranging from 1 to 4 with generally less\l"
	.string "opponents in the lower floors.\p"
	.string "After clearing each floor you will \n"
	.string "get 1-3 random item drops and then\l"
	.string "the next floor warp will activate.\l"
	.string "This is the only way to aquire medicine.\p"
	.string "Winning a battle will get you ¥500.\p"
	.string "Every 5th floor is a Heal/Shop floor\n"
	.string "where you will be able to rest and\l"
	.string "prepare for the next Trial.\p"
	.string "Every ten floors there will be\n"
	.string "a Move Tutor.\p"
	.string "And every 25th floor there will be a\n"
	.string "boss fight after that you will be able\l"
	.string "to choose another random Pokémon.$"

PitEntrance_Text_MoreInfo2::
	.string "If you do manage to beat the final\n"
	.string "trainer on Floor 100, you can choose to\l"
	.string "keep going and see how far you can get.\p"
	.string "After a successful run you are able to\n"
	.string "deposit your team members in the PC\l"
	.string "to use in a later run if you'd like.\p"
	.string "Your Pokédex will also keep getting\n"
	.string "filled from run to run and provides\l"
	.string "great insights into your team members.\p"
	.string "Thats all the info for now.\n"
	.string "Hopefully you have fun!$"

PitEntrance_Text_BattleInfo::
	.string "This hack is built on a base called the\n"
	.string "pokeemerald-expansion. By default most\l"
	.string "later Gen mechanics are in the game.\p"
	.string "Depending on the version you chose that\n"
	.string "means things like Megas and late Gen\l"
	.string "Pokémon exist.\p"
	.string "If you have specific questions you can\n"
	.string "check the Expansion Github to see what\l"
	.string "changes they have made.$"

PitEntrance_Text_GameModeInfo::
	.string "This game offers a wide range of game\n"
	.string "modes that you can choose whenever you\l"
	.string "start a new game.\p"
	.string "NORMAL mode will offer a challenging, but\n"
	.string "still fair Pit experience with the basic\l"
	.string "setup intended by the devs.\p"
	.string "HARD mode will reduce shared XP to 50%,\n"
	.string "won't offer Legendaries to the player,\l"
	.string "allows trainers to have Megas in Gen 9\p"
	.string "and turns off the EV/IV Changer.\p"
	.string "Trainer EVs will be evenly distributed and\n"
	.string "match the average EVs of your own team.\p"
	.string "Having the EV/IV Change disabled\n"
	.string "also enables new merchant items in\l"
	.string "the vitamins section to reset EVs for\l"
	.string "your own Pokémon.\p"
	.string "Additionally there are special challenge\n"
	.string "modes like '3 Mons only' or a shorter\l"
	.string "'50 floors' variant.\p"
	.string "If you are into fully randomized\n"
	.string "challenges there are also numerous\l"
	.string "randomizer options to choose from.$"

PitEntrance_Text_Credits::
	.string "Lead Developer: Archie from Team Aqua\n"
	.string "Co-Lead: wiz1989\p"
	.string "Lead Artist: Mudskip\n"
	.string "Balance/Testing: Aereon\p"
	.string "RavePossum implemented the Gen 5\n"
	.string "Summary Screen and lots of other stuff.\p"
	.string "All battle / late Gen stuff / plenty\n"
	.string "more is from the Expansion Team at RHH.\l"
	.string "They do amazing work!\p"
	.string "The decomps themselves were created by \n"
	.string "people at pret.\p"
	.string "Nico made the Battle UI.\n"
	.string "Chairry/Logan/Livra: Extra Avatars\p"
	.string "Ghoulslash made the Item Desc Code +\n"
	.string "the UI shell code used for the UIs.\p"
	.string "Mudskip and Archie together made the \n"
	.string "majority of the new UIs in the hack.$"

PitEntrance_Text_Credits2::
	.string "Hyo/Poffin made the FRLG style sprites.\n"
	.string "The tilesets used are from TAAR.\l"
	.string "Bsbob made the map pop-up branch.\p"
	.string "Lunos wrote the Wonder Trade code.\n"
	.string "TheXaman wrote some of the randomizer\l"
	.string "and Party Menu code.\p"
	.string "Devolov/Rioluwott/EliteRedux/Graion\n"
	.string "for various QOL additions, mostly\l"
	.string "battle related.\p"
	.string "Bassoonian provided the Egg Moves\n"
	.string "Tutor code.\p"
	.string "Special thanks to everyone in our\n"
	.string "Team Aqua Discord. There are too many\l"
	.string "people to thank here, but this hack is\l"
	.string "built on community resources.\p"
	.string "Without all of them this hack would\n"
	.string "not exist. Thank you all <3$"

PitEntrance_Text_Bugs::
	.string "If you have any Battle related bugs you\n"
	.string "can report them on the GitHub for the\l"
	.string "pokeemerald-expansion as I have not\l"
	.string "changed any Battle Code myself.\p"
	.string "Other bugs can be reported in the\n"
	.string "The Pit Discord Server.$"

PitEntrance_Text_Cheats::
	.string "You can enable the Expansion debug\n"
	.string "menu by pressing R and Start at the\l"
	.string "same time.\p"
	.string "These features can break the game\n"
	.string "so don't report bugs if using it.$"

PitEntrance_Text_Rules::
	.string "Welcome to the Pit of 100 Trials!$"
	@ .string "Beyond this point is a neverending\l" comment out for now maybe remove for good
	@ .string "series of rooms filled with opponents.\p"
	@ .string "Can you survive even 100 floors?$"

PitEntrance_Text_Discord:
	.string "To talk about the hack join our server.\n"
	.string "Discord: https://discord.gg/3b83g96NTW$"


PitEntrance_AccessPC::
	lock
	playse SE_PC_ON
	setvar VAR_TEMP_B, 0
	special ShowPokemonStorageSystemPC
	waitstate
	release
	end

PitEntrance_Text_SecretBaseShop_GiveGoldShield:
	.string "Oh, Hey! I have something here for you\n"
	.string "for beating The Pit with Hard Exp.\l"
	.string "Here is a Gold Shield Decoration!$"

PitEntrance_Text_SecretBaseShop_GiveSilverShield:
	.string "Oh, Hey! I have something here for you\n"
	.string "for beating The Pit with Normal Exp.\l"
	.string "Here is a Silver Shield Decoration!$"

PitEntrance_SecretBaseShop_GiveGoldShield::
	msgbox PitEntrance_Text_SecretBaseShop_GiveGoldShield, MSGBOX_DEFAULT
	goto PitEntrance_SecretBaseShop_CheckShields

PitEntrance_SecretBaseShop_GiveSilverShield::
	msgbox PitEntrance_Text_SecretBaseShop_GiveSilverShield, MSGBOX_DEFAULT
	goto PitEntrance_SecretBaseShop_CheckShields

PitEntrance_SecretBaseShop::
	lock
	faceplayer
PitEntrance_SecretBaseShop_CheckShields::
	callnative CheckAndGiveShieldsOnVictory
	goto_if_eq VAR_RESULT, 1, PitEntrance_SecretBaseShop_GiveSilverShield
	goto_if_eq VAR_RESULT, 2, PitEntrance_SecretBaseShop_GiveGoldShield
PitEntrance_SecretBaseShop_CommonRestart::
	message gText_HowMayIServeYou
	waitmessage
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitEntrance_SecretBaseShop_Dolls_Text, PitEntrance_SecretBaseShop_Plants_Text, PitEntrance_SecretBaseShop_Mats_Text, PitEntrance_SecretBaseShop_Posters_Text, PitEntrance_SecretBaseShop_Cushions_Text, PitEntrance_SecretBaseShop_Desks_Text, PitEntrance_SecretBaseShop_Chairs_Text, PitEntrance_SecretBaseShop_Misc_Text
	closemessage
	copyvar VAR_TEMP_9, VAR_RESULT
	setflag FLAG_BUY_FROM_MART
	goto_if_eq VAR_RESULT, 0, PitEntrance_SecretBaseShop_Dolls_Shop
	goto_if_eq VAR_RESULT, 1, PitEntrance_SecretBaseShop_Plants_Shop
	goto_if_eq VAR_RESULT, 2, PitEntrance_SecretBaseShop_Mats_Shop
	goto_if_eq VAR_RESULT, 3, PitEntrance_SecretBaseShop_Posters_Shop
	goto_if_eq VAR_RESULT, 4, PitEntrance_SecretBaseShop_Cushions_Shop
	goto_if_eq VAR_RESULT, 5, PitEntrance_SecretBaseShop_Desks_Shop
	goto_if_eq VAR_RESULT, 6, PitEntrance_SecretBaseShop_Chairs_Shop
	goto_if_eq VAR_RESULT, 7, PitEntrance_SecretBaseShop_Misc_Shop
PitEntrance_SecretBaseShop_CommonEnd::
	clearflag FLAG_BUY_FROM_MART
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

PitEntrance_SecretBaseShop_Dolls_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Dolls
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Plants_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Plants
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Mats_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Mats
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Posters_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Posters
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Cushions_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Cushions
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Desks_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Desks
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Chairs_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Chairs
	goto PitEntrance_SecretBaseShop_CommonRestart

PitEntrance_SecretBaseShop_Misc_Shop::
	pokemartdecoration2 PitEntrance_SecretBaseShop_Misc
	goto PitEntrance_SecretBaseShop_CommonRestart


PitEntrance_SecretBaseShop_Desks_Text:
	.string "Desks$"
PitEntrance_SecretBaseShop_Chairs_Text:
	.string "Chairs$"
PitEntrance_SecretBaseShop_Plants_Text:
	.string "Plants$"
PitEntrance_SecretBaseShop_Misc_Text:
	.string "Misc$"
PitEntrance_SecretBaseShop_Mats_Text:
	.string "Mats$"
PitEntrance_SecretBaseShop_Posters_Text:
	.string "Posters$"
PitEntrance_SecretBaseShop_Dolls_Text:
	.string "Dolls$"
PitEntrance_SecretBaseShop_Cushions_Text:
	.string "Cushions$"

	.align 2
PitEntrance_SecretBaseShop_Desks:
	.2byte DECOR_SMALL_DESK      
	.2byte DECOR_POKEMON_DESK    
	.2byte DECOR_HEAVY_DESK      
	.2byte DECOR_RAGGED_DESK     
	.2byte DECOR_COMFORT_DESK    
	.2byte DECOR_PRETTY_DESK     
	.2byte DECOR_BRICK_DESK      
	.2byte DECOR_CAMP_DESK       
	.2byte DECOR_HARD_DESK    
	.2byte 0
	release
	end 

	.align 2
PitEntrance_SecretBaseShop_Chairs:  
	.2byte DECOR_SMALL_CHAIR     
	.2byte DECOR_POKEMON_CHAIR   
	.2byte DECOR_HEAVY_CHAIR     
	.2byte DECOR_PRETTY_CHAIR    
	.2byte DECOR_COMFORT_CHAIR   
	.2byte DECOR_RAGGED_CHAIR    
	.2byte DECOR_BRICK_CHAIR     
	.2byte DECOR_CAMP_CHAIR      
	.2byte DECOR_HARD_CHAIR    
	.2byte 0
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Plants:  
	.2byte DECOR_RED_PLANT       
	.2byte DECOR_TROPICAL_PLANT  
	.2byte DECOR_PRETTY_FLOWERS  
	.2byte DECOR_COLORFUL_PLANT  
	.2byte DECOR_BIG_PLANT       
	.2byte DECOR_GORGEOUS_PLANT  
	.2byte 0
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Misc:
	.2byte DECOR_RED_BRICK       
	.2byte DECOR_YELLOW_BRICK    
	.2byte DECOR_BLUE_BRICK      
	.2byte DECOR_RED_BALLOON     
	.2byte DECOR_BLUE_BALLOON    
	.2byte DECOR_YELLOW_BALLOON  
	.2byte DECOR_RED_TENT        
	.2byte DECOR_BLUE_TENT       
	.2byte DECOR_SOLID_BOARD     
	.2byte DECOR_SLIDE           
	.2byte DECOR_FENCE_LENGTH    
	.2byte DECOR_FENCE_WIDTH     
	.2byte DECOR_TIRE            
	.2byte DECOR_STAND           
	.2byte DECOR_MUD_BALL        
	.2byte DECOR_BREAKABLE_DOOR  
	.2byte DECOR_SAND_ORNAMENT   
	.2byte DECOR_GLASS_ORNAMENT  
	.2byte DECOR_TV              
	.2byte DECOR_ROUND_TV        
	.2byte DECOR_CUTE_TV      
	.2byte 0   
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Mats:
	.2byte DECOR_GLITTER_MAT     
	.2byte DECOR_JUMP_MAT        
	.2byte DECOR_SPIN_MAT        
	.2byte DECOR_C_LOW_NOTE_MAT  
	.2byte DECOR_D_NOTE_MAT      
	.2byte DECOR_E_NOTE_MAT      
	.2byte DECOR_F_NOTE_MAT      
	.2byte DECOR_G_NOTE_MAT      
	.2byte DECOR_A_NOTE_MAT      
	.2byte DECOR_B_NOTE_MAT      
	.2byte DECOR_C_HIGH_NOTE_MAT 
	.2byte DECOR_SURF_MAT        
	.2byte DECOR_THUNDER_MAT     
	.2byte DECOR_FIRE_BLAST_MAT  
	.2byte DECOR_POWDER_SNOW_MAT 
	.2byte DECOR_ATTRACT_MAT     
	.2byte DECOR_FISSURE_MAT     
	.2byte DECOR_SPIKES_MAT      
	.2byte 0
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Posters:
	.2byte DECOR_BALL_POSTER     
	.2byte DECOR_GREEN_POSTER    
	.2byte DECOR_RED_POSTER      
	.2byte DECOR_BLUE_POSTER     
	.2byte DECOR_CUTE_POSTER     
	.2byte DECOR_PIKA_POSTER     
	.2byte DECOR_LONG_POSTER     
	.2byte DECOR_SEA_POSTER      
	.2byte DECOR_SKY_POSTER      
	.2byte DECOR_KISS_POSTER     
	.2byte 0
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Dolls:
	.2byte DECOR_PICHU_DOLL      
	.2byte DECOR_PIKACHU_DOLL    
	.2byte DECOR_MARILL_DOLL     
	.2byte DECOR_TOGEPI_DOLL     
	.2byte DECOR_CYNDAQUIL_DOLL  
	.2byte DECOR_CHIKORITA_DOLL  
	.2byte DECOR_TOTODILE_DOLL   
	.2byte DECOR_JIGGLYPUFF_DOLL 
	.2byte DECOR_MEOWTH_DOLL     
	.2byte DECOR_CLEFAIRY_DOLL   
	.2byte DECOR_DITTO_DOLL      
	.2byte DECOR_SMOOCHUM_DOLL   
	.2byte DECOR_TREECKO_DOLL    
	.2byte DECOR_TORCHIC_DOLL    
	.2byte DECOR_MUDKIP_DOLL     
	.2byte DECOR_DUSKULL_DOLL    
	.2byte DECOR_WYNAUT_DOLL     
	.2byte DECOR_BALTOY_DOLL     
	.2byte DECOR_KECLEON_DOLL    
	.2byte DECOR_AZURILL_DOLL    
	.2byte DECOR_SKITTY_DOLL     
	.2byte DECOR_SWABLU_DOLL     
	.2byte DECOR_GULPIN_DOLL     
	.2byte DECOR_LOTAD_DOLL      
	.2byte DECOR_SEEDOT_DOLL     
	.2byte DECOR_SNORLAX_DOLL    
	.2byte DECOR_RHYDON_DOLL     
	.2byte DECOR_LAPRAS_DOLL     
	.2byte DECOR_VENUSAUR_DOLL   
	.2byte DECOR_CHARIZARD_DOLL  
	.2byte DECOR_BLASTOISE_DOLL  
	.2byte DECOR_WAILMER_DOLL    
	.2byte DECOR_REGIROCK_DOLL   
	.2byte DECOR_REGICE_DOLL     
	.2byte DECOR_REGISTEEL_DOLL  
	.2byte 0
	release
	end

	.align 2
PitEntrance_SecretBaseShop_Cushions:
	.2byte DECOR_PIKA_CUSHION    
	.2byte DECOR_ROUND_CUSHION   
	.2byte DECOR_KISS_CUSHION    
	.2byte DECOR_ZIGZAG_CUSHION  
	.2byte DECOR_SPIN_CUSHION    
	.2byte DECOR_DIAMOND_CUSHION 
	.2byte DECOR_BALL_CUSHION    
	.2byte DECOR_GRASS_CUSHION   
	.2byte DECOR_FIRE_CUSHION    
	.2byte DECOR_WATER_CUSHION   
	.2byte 0
	release
	end


PitEntrance_Pinball_NPC::
	lock
	faceplayer
	message PitEntrance_Pinball_Text
	waitmessage
	dynmultichoice 22, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitEntrance_Pinball_ModeMeowth_Text, PitEntrance_Pinball_ModeDiglett_Text, PitEntrance_Pinball_ModeSeel_Text, PitEntrance_Pinball_ModeGengar_Text
	closemessage
	copyvar VAR_TEMP_9, VAR_RESULT
	setflag FLAG_BUY_FROM_MART
	goto_if_eq VAR_RESULT, 0, PitEntrance_Pinball_ModeMeowth
	goto_if_eq VAR_RESULT, 1, PitEntrance_Pinball_ModeDiglett
	goto_if_eq VAR_RESULT, 2, PitEntrance_Pinball_ModeSeel
	goto_if_eq VAR_RESULT, 3, PitEntrance_Pinball_ModeGengar
PitEntrance_Pinball_CommonEnd::
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

PitEntrance_Pinball_Text::
	.string "Would you like to play a game?$"

PitEntrance_Pinball_ModeMeowth_Text::
	.string "Meowth$"
PitEntrance_Pinball_ModeDiglett_Text::
	.string "Diglett$"
PitEntrance_Pinball_ModeSeel_Text::
	.string "Seel$"
PitEntrance_Pinball_ModeGengar_Text::
	.string "Gengar$"

PitEntrance_Pinball_ModeMeowth::
	callnative PlayMeowthPinballGame
	waitstate
	goto PitEntrance_Pinball_CommonEnd

PitEntrance_Pinball_ModeDiglett::
	callnative PlayDiglettPinballGame
	waitstate
	goto PitEntrance_Pinball_CommonEnd

PitEntrance_Pinball_ModeSeel::
	callnative PlaySeelPinballGame
	waitstate
	goto PitEntrance_Pinball_CommonEnd

PitEntrance_Pinball_ModeGengar::
	callnative PlayGengarPinballGame
	waitstate
	goto PitEntrance_Pinball_CommonEnd

PitEntrance_MakePokemonShiny_Text:
	.string "Choose a mon to make a Shiny$"

PitEntrance_MakePokemonShiny::
	lock
	msgbox PitEntrance_MakePokemonShiny_Text, MSGBOX_DEFAULT
	call PitEncounter_ChooseMonScript
	callnative MakePlayerPokemonShiny
	release
	end

Movement_Archie:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

Movement_wiz1989:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
	
Movement_Archie_Leave:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Movement_wiz1989_Leave:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
