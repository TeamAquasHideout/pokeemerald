.set LOCALID_MARIO, 5
.set LOCALID_RAVEPOSSUM, 6
.set LOCALID_PHANTONOMY, 7

PitBackRoom_MapScripts::
	.byte 0


PitBackRoom_EventScript_Nico::
	lock
	faceplayer
	msgbox PitBackRoom_Text_Nico, MSGBOX_NPC
	release
	end

PitBackRoom_Text_Nico:
	.string "Oh, uhm, hi!\n"
	.string "I'm Nico!\p"
	.string "I did a lot of the mapping for this\n"
	.string "game, as well as some of the Battle\l"
	.string "UI.\p"
	.string "Let me tell you, making maps is not\n"
	.string "easy!\p"
	.string "It might be called the Pit of 100\n"
	.string "Trials, but we didn't quite get to\l"
	.string "100 maps.\p"
	.string "Wanna know why?\p"
	.string "It's because we all are but unpaid\n"
	.string "volunteers, pouring our love into\l"
	.string "passion projects in the brief moments\l"
	.string "of respite that are allowed us when\l"
	.string "we're not busy being crushed by the\l"
	.string "cruel, cruel wheels of capitalism.\p"
	.string "… … …\p"
	.string "So I hope you enjoy our work!!!$"

PitBackRoom_EventScript_Mudskip::
	lock
	faceplayer
	msgbox PitBackRoom_Text_Mudskip, MSGBOX_NPC
	turnobject LOCALID_MARIO, DIR_EAST
	release
	end

PitBackRoom_Text_Mudskip:
	.string "Hiya, I'm mudskip!\p"
	.string "I am shown as the Red Luigi man\n"
	.string "instead of a Mudkip.\p"
	.string "Anyhoo, I worked on Pit as an artist,\n"
	.string "ranging from the Birch's Case UI for\l"
	.string "the 9 starters, to the indirect\l"
	.string "origin of Pit's obsession with blue\l"
	.string "and black themed UIs, and a few other.\p"
	.string "This was one of the few early works\n"
	.string "I made on a ROM hack that helps me\l"
	.string "hone my skill as a pixel artist, I\l"
	.string "hope that I'll truly get to spread\l"
	.string "the excellent idea of Mario being a\l"
	.string "Pokémon Trainer some day.\p"
	.string "Well, we hope you're enjoying this\n"
	.string "hack!\l"
	.string "Because I sure do at least, ehe."
	.string "$"

PitBackRoom_EventScript_RavePossum::
	lock
	faceplayer
	msgbox PitBackRoom_Text_RavePossum, MSGBOX_NPC
	turnobject LOCALID_RAVEPOSSUM, DIR_WEST
	release
	end

PitBackRoom_Text_RavePossum:
	.string "RavePossum here! Surprisingly, I am not\n" 
	.string "actually a marsupial.\p"
	.string "I programmed the summary screen and a\n"
	.string "few other random bits here and there.\p"
	.string "Enjoy your time in the Pit!$"


PitBackRoom_EventScript_Phantonomy::
	lock
	faceplayer
	msgbox PitBackRoom_Text_Phantonomy, MSGBOX_NPC
	turnobject LOCALID_PHANTONOMY, DIR_EAST
	release
	end

PitBackRoom_Text_Phantonomy:
	.string "Hello!\p" 
	.string "I'm Phantonomy.\p"
	.string "I had the priviledge to playtest some\n"
	.string "of the later builds of this project to\l"
	.string "help polish it up for release!\p"
	.string "I'll share a quick tip with you that\n"
	.string "will greatly benefit your runs.\p"		
	.string "Pick up all of the items BEFORE\n"
	.string "you step on the warp tile.\p"
	.string "It makes the game a lot easier.\n"
	.string "Trust me…$"

PitBackRoom_EventScript_wiz1989::
	lock
	faceplayer
	msgbox PitBackRoom_EventScript_wiz1989_Text_0
	waitmessage
	msgbox PitBackRoom_EventScript_wiz1989_Text_1, MSGBOX_YESNO
	msgbox PitBackRoom_EventScript_wiz1989_Text_2, MSGBOX_AUTOCLOSE
	release
	end

PitBackRoom_EventScript_wiz1989_Text_0:
	.string "I am the Game Master.\p"
	.string "I will give you helpful advice for each\n"
	.string "situation, but it adds an additional\l"
	.string "20min to your play clock.$"

PitBackRoom_EventScript_wiz1989_Text_1:
	.string "Do you want me to give you a hint?$"

PitBackRoom_EventScript_wiz1989_Text_2:
	.string "Haha! I dumbfounded you!\p"
	.string "Actually my name is wiz1989 and this\n"
	.string "is my safe room I like to escape to...\l"
	.string "if you know what I mean.\p"
	.string "I joined Archie early on this venture\n"
	.string "and did a bit of everything.\p"
	.string "I really hope you enjoy this hack as\n"
	.string "much as I do and can value the passion\l"
	.string "that went into making it.\p"
	.string "Now go and try to escape from The Pit!$"
	

PitBackRoom_EventScript_Archie::
	lock
	faceplayer
	msgbox PitBackRoom_EventScript_Archie_Text_0, MSGBOX_DEFAULT
	turnobject 1, DIR_SOUTH
	release
	end

PitBackRoom_EventScript_Archie_Text_0:
	.string "You know....\n"
	.string "I've been thinking....\p"
	.string "Do you think I could flood The Pit?$"



PitBackRoom_EventScript_Aereon::
	lock
	faceplayer
	msgbox PitBackRoom_EventScript_Aereon_text, MSGBOX_DEFAULT
	release
	end

PitBackRoom_EventScript_Aereon_text::
	.string "Hello, I'm Aereon! I helped a lot with\n"
	.string "balance changes and the Boss Ace\l"
	.string "Pokemon! Best of luck on your future\l"
	.string "attempts in The Pit, I'm rooting for\l"
	.string "you!$"
