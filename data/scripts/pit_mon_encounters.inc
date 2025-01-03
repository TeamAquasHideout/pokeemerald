PitOverworldMonEncounter::
	lock
	faceplayer
	callnative CallRandomMonEncounterScript
	end

PitEncounter_ChooseMonScript::
	getpartysize
	goto_if_eq VAR_RESULT, 0, PitEncounter_ChooseMonScriptEnd
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, PitEncounter_ChooseMonScriptEnd
	copyvar VAR_0x8005, VAR_0x8004
PitEncounter_ChooseMonScriptEnd::
	return

PitEncounter_Common_AlreadyUsedEffect:: @ Can Swap for a Mon Specific Post Script From the Struct if we want
	faceplayer
	msgbox PitEncounter_Common_AlreadyUsedEffect_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_Common_AlreadyUsedEffect_Text:
	.string "Already used effect.$"

PitEncounter_Common_AfterUse::
	setflag FLAG_USED_RANDOM_ENCOUNTER_THIS_FLOOR
	return

PitEncounter_Mover_alreadyUsed::
	faceplayer
	msgbox PitEncounter_Common_AlreadyUsedEffect_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_Mover_alreadyUsed_Text:
	.string "Abra!$"

PitEncounter_HealOneMon_alreadyUsed::
	faceplayer
	msgbox PitEncounter_HealOneMon_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_HealOneMon_alreadyUsed_Text:
	.string "Chansey!$"

PitEncounter_GrantWishChoiceItem_alreadyUsed::
	faceplayer
	msgbox PitEncounter_GrantWishChoiceItem_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_GrantWishChoiceItem_alreadyUsed_Text:
	.string "Jirachi!$"

PitEncounter_ReviveOneMon_alreadyUsed::
	faceplayer
	msgbox PitEncounter_ReviveOneMon_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_ReviveOneMon_alreadyUsed_Text:
	.string "Shedinja!$"

PitEncounter_AmuletCoinDrop_alreadyUsed::
	faceplayer
	msgbox PitEncounter_AmuletCoinDrop_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_AmuletCoinDrop_alreadyUsed_Text:
	.string "Meowth!$"

PitEncounter_Present_alreadyUsed::
	faceplayer
	msgbox PitEncounter_Present_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_Present_alreadyUsed_Text:
	.string "Delibird!$"

PitEncounter_NuggetDrop_alreadyUsed::
	faceplayer
	msgbox PitEncounter_NuggetDrop_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
#ifdef PIT_GEN_9_MODE
PitEncounter_NuggetDrop_alreadyUsed_Text:
	.string "Gholdengo$"
#else
PitEncounter_NuggetDrop_alreadyUsed_Text:
	.string "Sableye$"
#endif

PitEncounter_WonderTrade_alreadyUsed::
	faceplayer
	msgbox PitEncounter_WonderTrade_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_WonderTrade_alreadyUsed_Text:
	.string "Ziggie!$"

PitEncounter_MooMooMilkDrop_alreadyUsed::
	faceplayer
	msgbox PitEncounter_MooMooMilkDrop_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_MooMooMilkDrop_alreadyUsed_Text:
	.string "Miltank!$"

PitEncounter_CureAllStatus_alreadyUsed::
	faceplayer
	msgbox PitEncounter_CureAllStatus_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_CureAllStatus_alreadyUsed_Text:
	.string "Chimecho!$"

PitEncounter_LeftoversDrop_alreadyUsed::
	faceplayer
	msgbox PitEncounter_LeftoversDrop_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
#ifdef PIT_GEN_3_MODE
PitEncounter_LeftoversDrop_alreadyUsed_Text:
	.string "Snore...$"
#else
PitEncounter_LeftoversDrop_alreadyUsed_Text:
	.string "Munchlax!$"
#endif

PitEncounter_RareCandyDrop_alreadyUsed::
	faceplayer
	msgbox PitEncounter_RareCandyDrop_alreadyUsed_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_RareCandyDrop_alreadyUsed_Text:
	.string "Eevee!!$"


@ Heal Single Pokemon
PitEncounter_HealOneMon::
	msgbox PitEncounter_HealOneMon_Text, MSGBOX_DEFAULT
	msgbox PitEncounter_HealOneMon_YesNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitEncounter_HealOneMon_NoThanks
	call PitEncounter_ChooseMonScript
	goto_if_ge VAR_0x8004, PARTY_SIZE, PitEncounter_HealOneMon_End
	callnative HealPlayerPokemon
	call PitEncounter_Common_AfterUse
	msgbox PitEncounter_HealOneMon_Text2, MSGBOX_DEFAULT
PitEncounter_HealOneMon_End::
	release
	end

PitEncounter_HealOneMon_NoThanks:
	msgbox PitEncounter_HealOneMon_NoThanks_Text, MSGBOX_DEFAULT
	goto PitEncounter_HealOneMon_End

PitEncounter_HealOneMon_Text:
	.string "Chansey wants to heal one of your\nparty members.$"
PitEncounter_HealOneMon_Text2:
	.string "Your Pokémon was healed.$"
PitEncounter_HealOneMon_YesNo:
	.string "Do you want to proceed?$"
PitEncounter_HealOneMon_NoThanks_Text:
	.string "Come back later.$"


@ Choose a choice item
PitEncounter_GrantWishChoiceItem::
	msgbox PitEncounter_GrantWishChoiceItem_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitEncounter_GrantWishChoiceItem_Band, PitEncounter_GrantWishChoiceItem_Scarf, PitEncounter_GrantWishChoiceItem_Specs
	goto_if_eq VAR_RESULT, 0, PitEncounter_GrantWishChoiceItem_0
	goto_if_eq VAR_RESULT, 1, PitEncounter_GrantWishChoiceItem_1
	goto_if_eq VAR_RESULT, 2, PitEncounter_GrantWishChoiceItem_2
	goto PitEncounter_GrantWishChoiceItem_End_SkippedItem
PitEncounter_GrantWishChoiceItem_End:
	call PitEncounter_Common_AfterUse
PitEncounter_GrantWishChoiceItem_End_SkippedItem:
	release
	end

PitEncounter_GrantWishChoiceItem_0:
	giveitem ITEM_CHOICE_BAND, 1
	goto PitEncounter_GrantWishChoiceItem_End
PitEncounter_GrantWishChoiceItem_1:
	giveitem ITEM_CHOICE_SCARF, 1
	goto PitEncounter_GrantWishChoiceItem_End
PitEncounter_GrantWishChoiceItem_2:
	giveitem ITEM_CHOICE_SPECS, 1
	goto PitEncounter_GrantWishChoiceItem_End
PitEncounter_GrantWishChoiceItem_Text:
	.string "Jirachi grants you a wish!\nChoose wisely!$"
PitEncounter_GrantWishChoiceItem_Band:
	.string "Choice Band$"
PitEncounter_GrantWishChoiceItem_Scarf:
	.string "Choice Scarf$"
PitEncounter_GrantWishChoiceItem_Specs:
	.string "Choice Specs$"


@ Revive Single Pokemon
PitEncounter_ReviveOneMon::
	msgbox PitEncounter_ReviveOneMon_Text, MSGBOX_DEFAULT
	call PitEncounter_ChooseMonScript
	goto_if_ge VAR_0x8004, PARTY_SIZE, PitEncounter_HealOneMon_End
	callnative CheckMonFainted
	goto_if_eq VAR_RESULT, 0, PitEncounter_ReviveMonNotFainted
	callnative HealPlayerPokemon
	call PitEncounter_Common_AfterUse
	msgbox PitEncounter_ReviveOneMon_Text2, MSGBOX_DEFAULT
	release
	end
PitEncounter_ReviveOneMon_Text:
	.string "Shedinja wants to save a lost soul!$"
PitEncounter_ReviveOneMon_Text2:
	.string "Your Pokémon was revived.$"

PitEncounter_ReviveMonNotFainted::
	msgbox PitEncounter_ReviveMonNotFainted_Text, MSGBOX_DEFAULT
	release
	end
PitEncounter_ReviveMonNotFainted_Text:
	.string "This Pokémon can't be revived.$"


@ Give Lucky Egg Item
PitEncounter_LuckyEggDrop::
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_LUCKY_EGG, 1
	call PitEncounter_Common_AfterUse
	release
	end


@ Give Amulet Coin Item
PitEncounter_AmuletCoinDrop::
	msgbox PitEncounter_AmuletCoinDrop_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_AMULET_COIN, 1
	call PitEncounter_Common_AfterUse
	release
	end
PitEncounter_AmuletCoinDrop_Text:
	.string "Meowth, that's right!$"


@ Give Present
PitEncounter_Present::
	msgbox PitEncounter_Present_Text, MSGBOX_DEFAULT
	msgbox PitEncounter_Present_YesNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitEncounter_Present_NoThanks
	call PitEncounter_Common_AfterUse
	random 5
	switch VAR_RESULT
	case 0, PitEncounter_Present_Jackpot
	case 1, PitEncounter_Present_Prize
	case 2, PitEncounter_Present_Prize
	case 3, PitEncounter_Present_Prize
	case 4, PitEncounter_Present_Loss
PitEncounter_Present_End:
	release
	end
PitEncounter_Present_Text:
	.string "Delibird is holding a present\nwith a skull painted on it.$"
PitEncounter_Present_YesNo:
	.string "Do you want to take it?$"

PitEncounter_Present_Jackpot:
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_MAX_REVIVE, 1
	goto PitEncounter_Present_End

PitEncounter_Present_Prize:
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_REVIVE, 1
	goto PitEncounter_Present_End

PitEncounter_Present_Loss:
	msgbox PitEncounter_Present_Loss_Text, MSGBOX_DEFAULT
	goto Debug_EventScript_InflictStatus1_Party_Poison
PitEncounter_Present_Loss_Text:
	.string "Oh no, there was poison barb inside!\nIt poisoned your whole party!$"

PitEncounter_Present_NoThanks:
	msgbox PitEncounter_Present_NoThanks_Text, MSGBOX_DEFAULT
	goto PitEncounter_Present_End
PitEncounter_Present_NoThanks_Text:
	.string "Whatever you like.$"


@ Give Nugget Item
PitEncounter_NuggetDrop::
	msgbox PitEncounter_NuggetDrop_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_NUGGET, 1
	call PitEncounter_Common_AfterUse
	release
	end
#ifdef PIT_GEN_9_MODE
PitEncounter_NuggetDrop_Text:
	.string "Gholdengo just lost a Nugget.\nQuick, take it!$"
#else
PitEncounter_NuggetDrop_Text:
	.string "Sableye just lost a Nugget.\nQuick, take it!$"
#endif

@ Wonder Trade NPC
PitEncounter_WonderTrade::
	msgbox PitEncounter_WonderTrade_Text, MSGBOX_DEFAULT
	msgbox PitEncounter_WonderTrade_YesNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitEncounter_WonderTradeEnd
	additem ITEM_RARE_CANDY, 1
	call EventScript_DoWonderTrade
	goto_if_eq VAR_0x8004, 0xFF, PitEncounter_WonderTrade_EndEarly
	call PitEncounter_Common_AfterUse
PitEncounter_WonderTradeEnd::
	release
	end

PitEncounter_WonderTrade_EndEarly::
	release
	end

PitEncounter_WonderTrade_Text:
	.string "Zigzagoon offers you a Wonder Trade.$"
PitEncounter_WonderTrade_YesNo:
	.string "Do you accept?$"


@ Give MooMooMilk Item
PitEncounter_MooMooMilkDrop::
	msgbox PitEncounter_MooMooMilkDrop_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_MOOMOO_MILK, 3
	call PitEncounter_Common_AfterUse
	release
	end
PitEncounter_MooMooMilkDrop_Text:
	.string "Miltank offers you a fresh bottle\nof milk.$"


@ Give RareCandy Item
PitEncounter_RareCandyDrop::
	msgbox PitEncounter_RareCandyDrop_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_RARE_CANDY, 3
	call PitEncounter_Common_AfterUse
	release
	end
PitEncounter_RareCandyDrop_Text:
	.string "Eevee loves evolving!\nTake this so you can evolve, too!.$"


@ Cure All Mons Status
PitEncounter_CureAllStatus::
	msgbox PitEncounter_CureAllStatus_Text, MSGBOX_DEFAULT
	callnative HealAllStatus
	msgbox PitEncounter_CureAllStatus_Cured, MSGBOX_DEFAULT
	call PitEncounter_Common_AfterUse
	release
	end
PitEncounter_CureAllStatus_Text:
	.string "Chimecho boosts out an enchanting\nhealing sound!$"
PitEncounter_CureAllStatus_Cured:
	.string "All status conditions have been\ncured.$"


@ Skip Floor NPC
PitEncounter_Mover::
	lock
	faceplayer
	msgbox PitEncounter_NPCMoverOpen, MSGBOX_DEFAULT
	message PitEncounter_NPCMoverOpen2
	dynmultichoice 17, 1, 0, 5, 0, DYN_MULTICHOICE_CB_NONE, PitEncounter_NPCMover2, PitEncounter_NPCMover3, PitShop_ShopNPC_Option8
	goto_if_eq VAR_RESULT, 0, PitEncounter_MoverSkip1
	goto_if_eq VAR_RESULT, 1, PitEncounter_MoverSkip2
	closemessage
EndOfMoverScript::
	release
	end

PitEncounter_NPCMoverOpen:
	.string "Abra has a special offer for you!\pIt can teleport you away.$"
PitEncounter_NPCMoverOpen2:
	.string "Free Rare Candies included with purchase!$"

PitEncounter_MoverSkip1::
	additem ITEM_RARE_CANDY, 1
	setflag FLAG_LEVEL_UP_TWICE
	setflag FLAG_FLOOR_CLEARED
	call PitEncounter_Common_AfterUse
	callnative SetWarpTileActive
	addvar VAR_PIT_FLOOR, 0
	special DrawWholeMapView
	goto Pit_Warp_Advance_Floor
	release
	end

PitEncounter_MoverSkip2::
	additem ITEM_RARE_CANDY, 2
	setflag FLAG_FLOOR_CLEARED
	setflag FLAG_LEVEL_UP_THRICE
	callnative SetWarpTileActive
	call PitEncounter_Common_AfterUse
	addvar VAR_PIT_FLOOR, 1
	special DrawWholeMapView
	goto Pit_Warp_Advance_Floor
	release
	end


@ Give Leftovers Item
PitEncounter_LeftoversDrop::
	msgbox PitEncounter_LeftoversDrop_Text, MSGBOX_DEFAULT
	setflag FLAG_DONT_RANDOMIZE_NEXT_ITEM
	giveitem ITEM_LEFTOVERS, 1
	call PitEncounter_Common_AfterUse
	release
	end
#ifdef PIT_GEN_3_MODE
PitEncounter_LeftoversDrop_Text:
	.string "Snorlax loves you!\pIt even wants to share its Leftovers\nwith you.$"
#else
PitEncounter_LeftoversDrop_Text:
	.string "Munchlax loves you!\pIt even wants to share its Leftovers\nwith you.$"
#endif


PitEncounter_Mover_NotEnoughMoney:
	msgbox PitEncounter_NPCMoverNotEnoughMoneyText, MSGBOX_DEFAULT
	release
	end

PitEncounter_NPCMoverNotEnoughMoneyText:
	.string "Not enough money...$"

PitEncounter_NPCMover2:
	.string "Skip 1 Floor  (1RC)$"
PitEncounter_NPCMover3:
	.string "Skip 2 Floors (2RC)$"
PitEncounter_NPCMover4:
	.string "Wonder Trade$"




@
@			Random GiveMon Reward Encounters Post Boss Fight 
@		
PitGiveMonCommon::
	lock
	faceplayer
	callnative BufferNameText_RandomMonRewardEncounter
	msgbox PitGiveMonCommon_Text_AskMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitGiveMonCommon_FullPartyNothingChosen
	callnative PlayerPartyCountToResultVar
	goto_if_eq VAR_RESULT, 6, PitGiveMonCommon_PartyFullRemoveOne
	callnative Check3MonMode
	goto_if_eq VAR_TEMP_A, 1, PitGiveMonCommon_PartyFullRemoveOne
PitGiveMonCommon_NewMon2::
	callnative GiveRandomMonRewardEncounter
	callnative BufferNameText_RandomMonRewardEncounter
	msgbox PitGiveMonCommon_Text_ReceivedMon, MSGBOX_DEFAULT
	callnative BufferMapFloorString
	warpteleport MAP_PIT_REST_FLOOR, 9, 9
	waitstate
	release
	end

PitGiveMonCommon_PartyFullRemoveOne::
	message PitGiveMonCommon_GiveMonFullNothingChosen_Text1
	waitbuttonpress
	msgbox PitGiveMonCommon_GiveMonFullNothingChosen_Text2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PitGiveMonCommon_FullPartyNothingChosen
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, PitGiveMonCommon_FullPartyNothingChosen
	callnative RemovePartyPokemon
	goto PitGiveMonCommon_NewMon2
	release
	end

PitGiveMonCommon_FullPartyNothingChosen::
	release
	end

PitGiveMonCommon_GiveMonFullNothingChosen_Text1::
	.string "Your party is too full.$"

PitGiveMonCommon_GiveMonFullNothingChosen_Text2::
	.string "Do you want to get rid\n"
	.string "of a party member?$"

PitGiveMonCommon_Text_ReceivedMon:
	.string "The wild {STR_VAR_2} has become\n"
	.string "a member of your team!$"

PitGiveMonCommon_Text_AskMon:
	.string "Do you want {STR_VAR_2} to\n"
	.string "join your team?$"
