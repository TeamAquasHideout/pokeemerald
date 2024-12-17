.set LOCALID_MARIO, 5

PitBackRoom_MapScripts::
	.byte 0


PitBackRoom_EventScript_Nico::
	msgbox PitBackRoom_Text_Nico, MSGBOX_NPC
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
	msgbox PitBackRoom_Text_Mudskip, MSGBOX_NPC
	turnobject LOCALID_MARIO, DIR_EAST
	end

PitBackRoom_Text_Mudskip:
	.string "Hiya, I'm mudskip!\p"
	.string "Not to be confused by the streamer\n"
	.string "Mudskip though, as I am shown as the\l"
	.string "Red Luigi man instead of a Mudkip.\p"
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
