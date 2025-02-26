

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
#ifndef PIT_GEN_9_MODE
	showmoneybox 18, 16
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitTutor_MoveRelearnerText, PitArena_EggMovesText, PitArena_PreEvoMovesText, PitArena_TutorMovesText, PitArena_MoveDeleterText, PitShop_ShopNPC_Option_Exit
#else
	showmoneybox 18, 14
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitTutor_MoveRelearnerText, PitArena_EggMovesText, PitArena_PreEvoMovesText, PitArena_MoveDeleterText, PitShop_ShopNPC_Option_Exit
#endif	
	goto_if_eq VAR_RESULT, 0, PitTutor_MartNPCMoveRelearner
	goto_if_eq VAR_RESULT, 1, PitTutor_MartNPCMoveTutorEggMoves
	goto_if_eq VAR_RESULT, 2, PitTutor_MartNPCMoveTutorPreEvoMoves
	goto_if_eq VAR_RESULT, 3, PitTutor_MartNPCMoveDeleter
#ifndef PIT_GEN_9_MODE
	goto_if_eq VAR_RESULT, 3, PitTutor_MartNPCMoveTutorTutorMoves
	goto_if_eq VAR_RESULT, 4, PitTutor_MartNPCMoveDeleter
#endif
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
	checkmoney 10000
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
	goto LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	end

PitTutor_MartNPCMoveTutorTutorMoves_NotEnoughMoney::
	hidemoneybox
	msgbox PitArena_Tutor_NotGotTheMoney, MSGBOX_AUTOCLOSE
	release
	end
