

PitStop_HealNPC::
	lock
	faceplayer
	special HealPlayerParty
	msgbox PitStop_HealNPC_Text, MSGBOX_DEFAULT
	release
	end

PitStop_HealNPC_Text:
	.string "Your party has been healed.\p"
	.string "Have a nice descent.$"


PitTutor_MoveRelearner::
	lockall
	faceplayer
@ #ifndef PIT_GEN_9_MODE
	showmoneybox 18, 14
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitTutor_MoveRelearnerText, PitArena_EggMovesText, PitArena_PreEvoMovesText, PitArena_TutorMovesText, PitArena_MoveDeleterText, PitShop_ShopNPC_Option_Exit
@ #else
@ 	showmoneybox 18, 14
@ 	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitTutor_MoveRelearnerText, PitArena_EggMovesText, PitArena_PreEvoMovesText, PitArena_MoveDeleterText, PitShop_ShopNPC_Option_Exit
@ #endif	
	goto_if_eq VAR_RESULT, 0, PitTutor_MartNPCMoveRelearner
	goto_if_eq VAR_RESULT, 1, PitTutor_MartNPCMoveTutorEggMoves
	goto_if_eq VAR_RESULT, 2, PitTutor_MartNPCMoveTutorPreEvoMoves
@ #ifndef PIT_GEN_9_MODE
	goto_if_eq VAR_RESULT, 3, PitTutor_MartNPCMoveTutorTutorMoves
	goto_if_eq VAR_RESULT, 4, PitTutor_MartNPCMoveDeleter
@ #else
@ 	goto_if_eq VAR_RESULT, 3, PitTutor_MartNPCMoveDeleter
@ #endif
EndOfRelearnerScript::
	hidemoneybox
	release
	end

PitTutor_MartNPCMoveRelearner::
	setvar VAR_PIT_TUTOR_STATE, 0
	hidemoneybox
PitTutor_MartNPCMoveTutor::
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EndOfRelearnerScript
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, EndOfRelearnerScript
	goto_if_eq VAR_0x8005, 0, EndOfRelearnerScript
	special TeachMoveRelearnerMove
	waitstate
	goto EndOfRelearnerScript
	end

PitTutor_MartNPCMoveTutorEggMoves::
	checkmoney 8000
	goto_if_eq VAR_RESULT, FALSE, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	setvar VAR_PIT_TUTOR_STATE, 2
	hidemoneybox
	goto PitTutor_MartNPCMoveTutor
	end

PitTutor_MartNPCMoveTutorTutorMoves::
	checkmoney 8000
	goto_if_eq VAR_RESULT, FALSE, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	setvar VAR_PIT_TUTOR_STATE, 1
	hidemoneybox
	goto PitTutor_MartNPCMoveTutor
	end

PitTutor_MartNPCMoveTutorStaticTutorMoves::
	setvar VAR_PIT_TUTOR_STATE, 1
	hidemoneybox
	special ShowTutorMoveList
	waitstate
	call_if_eq VAR_RESULT, 99, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	release
	end

PitTutor_MartNPCMoveTutorPreEvoMoves::
	checkmoney 5000
	goto_if_eq VAR_RESULT, FALSE, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	setvar VAR_PIT_TUTOR_STATE, 4
	hidemoneybox
	goto PitTutor_MartNPCMoveTutor
	end

PitTutor_MartNPCMoveDeleter::
	hidemoneybox
	goto LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	end

PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney::
	hidemoneybox
	msgbox PitArena_Tutor_NotGotTheMoney, MSGBOX_AUTOCLOSE
	release
	end


PitStop_TradeOutPokemon_NPC::
	lock
	showmoneybox 1, 1
	message PitStop_TradeOutPokemon_NPC_Text1 
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitStop_TradeOutPokemon_NPC_Multichoice1, PitShop_ShopNPC_Option_Exit
	closemessage
	hidemoneybox
	goto_if_eq VAR_RESULT, 0, PitStop_TradeOutPokemon_NPC_TradeScript
	release
	end

PitStop_TradeOutPokemon_NPC_TradeScript::
	checkmoney 15000
	goto_if_eq VAR_RESULT, FALSE, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	callnative RemoveFollowingPokemon
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, PitStop_TradeOutPokemon_NPC_TradeScript_EndEarly
	removemoney 15000
	callnative RemoveFollowingPokemon
	callnative RemovePartyPokemon
	callnative CheckNoCaseMode
	goto_if_eq VAR_TEMP_A, 1, PitStop_TradeOutPokemon_NPC_TradeScript_NoCaseModeMode

	setflag FLAG_CASE_TRADE_MODE
	callnative StartNewPokeballCaseUI
	waitstate

	callnative UpdateFollowingPokemon
	msgbox PitStop_Trade_NPC_AfterText, MSGBOX_DEFAULT
	release
	end


PitStop_TradeOutPokemon_NPC_TradeScript_NoCaseModeMode::
	callnative AddNewMonNoCaseMode
	callnative UpdateFollowingPokemon
	msgbox PitStop_Trade_NPC_AfterText, MSGBOX_DEFAULT
	release
	end

PitStop_TradeOutPokemon_NPC_TradeScript_EndEarly::
	msgbox PitArena_Tutor_ConfirmMoveSelection_Text_2, MSGBOX_DEFAULT
	release
	end

PitStop_LevelUpPokemon_NPC::
	lock
	callnative CheckNoExpMode
	goto_if_eq VAR_TEMP_A, 1, PitStop_LevelUpPokemon_NPC_NoExpMode
	showmoneybox 1, 1
	message PitStop_LevelUp_NPC_Text1 
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitStop_LevelUp_NPC_Multichoice1, PitShop_ShopNPC_Option_Exit
	closemessage
	hidemoneybox
	goto_if_eq VAR_RESULT, 0, PitStop_LevelUp_NPC_LevelUpScript
	release
	end

PitStop_LevelUp_NPC_LevelUpScript::
	checkmoney 15000
	goto_if_eq VAR_RESULT, FALSE, PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, PitStop_TradeOutPokemon_NPC_TradeScript_EndEarly
	removemoney 15000
	callnative LevelUpChosenMon
	callnative TryLevelUpOverworldEvo_PitStop
PitArenaContinueAfterEvo_PitStop::
	callnative BufferLevelUpMonName
	msgbox PitStop_LevelUp_NPC_AfterText, MSGBOX_DEFAULT
	release
	end

PitStop_LevelUpPokemon_NPC_NoExpMode::
	msgbox PitStop_NoExpMode_LevelUpText, MSGBOX_DEFAULT
	release
	end

PitStop_LevelUp_NPC_AfterText:
	.string "{STR_VAR_1} was leveled up!$"

PitStop_Trade_NPC_AfterText:
	.string "Your Pokémon was traded!$"

PitStop_TradeOutPokemon_NPC_Text1:
	.string "Trade one of your Pokémon out\n"
	.string "for another. Choice from Full Case.$"

PitStop_TradeOutPokemon_NPC_Multichoice1:
	.string "Trade (¥15,000).$"

PitStop_LevelUp_NPC_Text1:
	.string "Pay to Level Up one of your Pokémon.$"

PitStop_LevelUp_NPC_Multichoice1:
	.string "Buy Level (¥15,000).$"

PitStop_NoExpMode_LevelUpText:
	.string "You cannot buy levels while using\n"
	.string "No Exp Mode.$"


