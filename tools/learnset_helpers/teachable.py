import glob
import pathlib
import re
import json
import os

# before all else, abort if the config is off
with open("./include/config/pokemon.h", "r") as file:
    learnset_config = re.findall(r"#define P_LEARNSET_HELPER_TEACHABLE *([^ ]*)", file.read())
    if len(learnset_config) != 1:
        quit()
    if learnset_config[0] != "TRUE":
        quit()

def parse_mon_name(name):
    return re.sub(r'(?!^)([A-Z]+)', r'_\1', name).upper()
    
tm_moves = []
tutor_moves = []
valid_species = []

# read generational settings from general.h
define_gen_latest = re.compile(r"^#define\s+PIT_GEN_(?P<GEN_LATEST>\w+)", re.MULTILINE)
pit_mode = []

with open(pathlib.Path("include/config/general.h"), "r") as config_general_h:
    if m := define_gen_latest.search(config_general_h.read()):
        pit_mode = m.group("GEN_LATEST")
        print(m.group("GEN_LATEST"))
    else:
        print("No match found")
# set gen_latest for correct learnset determination
if pit_mode == "3_MODE":
    gen_latest = 3
elif pit_mode == "5_MODE":
    gen_latest = 5
else:
    gen_latest = 9

# scan incs
incs_to_check =  glob.glob('./data/scripts/*.inc') # all .incs in the script folder
incs_to_check += glob.glob('./data/maps/*/scripts.inc') # all map scripts

if len(incs_to_check) == 0: # disabled if no jsons present
    quit()

#for file in incs_to_check:
#    with open(file, 'r') as f2:
#        raw = f2.read()
#    if 'special ChooseMonForMoveTutor' in raw:
#        for x in re.findall(r'setvar VAR_0x8005, (MOVE_.*)', raw):
#            if not x in tutor_moves:
#                tutor_moves.append(x)

# scan Tutor Moves
with open("./src/data/pokemon/tutor_moves.h", 'r') as file:
    # split tms_hms.h in only the relevant parts of the current gen setting
    if gen_latest == 3:
        before_end = file.read().split("PIT_GEN_3")[1]
    elif gen_latest == 5:
        before_end = file.read().split("PIT_GEN_5")[1]
    else:
        before_end = file.read().split("PIT_GEN_9")[1]
        # before_end = []
    # only proceed if a file could be read
    if not before_end:
        print("No Tutor Moves available")
    else:
        # determine the list elements
        for x in re.findall(r'\b(MOVE_\w+)\b', before_end):
            if not x in tutor_moves:
                tutor_moves.append(x)

# scan TMs and HMs
with open("./include/constants/tms_hms.h", 'r') as file:
    # split tms_hms.h in only the relevant parts of the current gen setting
    if gen_latest == 3:
        before_end = file.read().split("PIT_GEN_3")[1]
    elif gen_latest == 5:
        before_end = file.read().split("PIT_GEN_5")[1]
    else:
        before_end = file.read().split("PIT_GEN_9")[1]
    # determine the list elements
    for x in re.findall(r'F\((.*)\)', before_end):
        if not 'MOVE_' + x in tm_moves:
            tm_moves.append('MOVE_' + x)

# look up universal moves to exclude them
universal_moves = []
with open("./src/pokemon.c", "r") as file:
    for x in re.findall(r"static const u16 sUniversalMoves\[\] =(.|\n)*?{((.|\n)*?)};", file.read())[0]:
        x = x.replace("\n", "")
        for y in x.split(","):
            y = y.strip()
            if y == "":
                continue
            universal_moves.append(y)

# get compatibility from jsons
def construct_compatibility_dict(force_custom_check):
    dict_out = {}
    if gen_latest == 3:
        learnsets = [
            './tools/learnset_helpers/porymoves_files/rse.json',
        ]
    elif gen_latest == 5:
        learnsets = [
            './tools/learnset_helpers/porymoves_files/b2w2.json',
            './tools/learnset_helpers/porymoves_files/hgss.json',
            './tools/learnset_helpers/porymoves_files/rse.json',
        ]
    else:
        learnsets = [
            './tools/learnset_helpers/porymoves_files/sv.json',
            './tools/learnset_helpers/porymoves_files/bdsp.json',
            './tools/learnset_helpers/porymoves_files/la.json',
            './tools/learnset_helpers/porymoves_files/swsh.json',
            './tools/learnset_helpers/porymoves_files/usum.json',
            './tools/learnset_helpers/porymoves_files/oras.json',
            './tools/learnset_helpers/porymoves_files/b2w2.json',
            './tools/learnset_helpers/porymoves_files/hgss.json',
            './tools/learnset_helpers/porymoves_files/rse.json',
        ]

    for pth in learnsets:
        f = open(pth, 'r')
        data = json.load(f)
        for mon in data.keys():
            if not mon in dict_out:
                dict_out[mon] = []
                valid_species.append(mon)
            if not dict_out[mon]:
                # for move in data[mon]['LevelMoves']:
                #     if not move['Move'] in dict_out[mon]:
                #         dict_out[mon].append(move['Move'])
                #for move in data[mon]['PreEvoMoves']:
                #    if not move in dict_out[mon]:
                #        dict_out[mon].append(move)
                for move in data[mon]['TMMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)
                # for move in data[mon]['EggMoves']:
                #     if not move in dict_out[mon]:
                #         dict_out[mon].append(move)
                for move in data[mon]['TutorMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)

    # if the file was not previously generated, check if there is custom data there that needs to be preserved
    with open("./src/data/pokemon/teachable_learnsets.h", 'r') as file:
        raw = file.read()
        if not "// DO NOT MODIFY THIS FILE!" in raw and force_custom_check == True:
            custom_teachable_compatibilities = {}
            for entry in re.findall(r"static const u16 s(.*)TeachableLearnset\[\] = {\n((.|\n)*?)\n};", raw):
                monname = parse_mon_name(entry[0])
                if monname == "NONE":
                    continue
                compatibility = entry[1].split("\n")
                if not monname in custom_teachable_compatibilities:
                    custom_teachable_compatibilities[monname] = []
                if not monname in dict_out:
                    # this mon is unknown, so all data needs to be preserved
                    for move in compatibility:
                        move = move.replace(",", "").strip()
                        if move == "" or move == "MOVE_UNAVAILABLE":
                            continue
                        custom_teachable_compatibilities[monname].append(move)
                else:
                    # this mon is known, so check if the moves in the old teachable_learnsets.h are not in the jsons
                    for move in compatibility:
                        move = move.replace(",", "").strip()
                        if move == "" or move == "MOVE_UNAVAILABLE":
                            continue
                        if not move in dict_out[monname]:
                            custom_teachable_compatibilities[monname].append(move)
            # actually store the data in custom.json
            if os.path.exists("./tools/learnset_helpers/porymoves_files/custom.json"):
                f2 = open("./tools/learnset_helpers/porymoves_files/custom.json", "r")
                custom_json = json.load(f2)
                f2.close()
            else:
                custom_json = {}
            for x in custom_teachable_compatibilities:
                if len(custom_teachable_compatibilities[x]) == 0:
                    continue
                if not x in custom_json:
                    custom_json[x] = {"LevelMoves": [], "PreEvoMoves": [], "TMMoves": [], "EggMoves": [], "TutorMoves": []}
                for move in custom_teachable_compatibilities[x]:
                    custom_json[x]["TutorMoves"].append(move)
                f2 = open("./tools/learnset_helpers/porymoves_files/custom.json", "w")
                f2.write(json.dumps(custom_json, indent=2))
                f2.close()
            print("FIRST RUN: Updated custom.json with teachable_learnsets.h's data")
            # rerun the process
            dict_out = construct_compatibility_dict(False)
    return dict_out

compatibility_dict = construct_compatibility_dict(True)

# actually prepare the file
with open("./src/data/pokemon/teachable_learnsets.h", 'r') as file:
    out = file.read()
    list_of_mons = re.findall(r'static const u16 s(.*)TeachableLearnset', out)
for mon in list_of_mons:
    mon_parsed = parse_mon_name(mon)
    tm_learnset = []
    tutor_learnset = []
    if mon_parsed == "NONE" or mon_parsed == "MEW":
        continue
    if not mon_parsed in compatibility_dict:
        print("Unable to find %s in json" % mon)
    else:
        for move in tm_moves:
            if move in universal_moves:
                continue
            if move in tm_learnset:
                continue
            if move in compatibility_dict[mon_parsed]:
                tm_learnset.append(move)
                continue
        for move in tutor_moves:
            # if move in universal_moves:
            #     continue
            if move in tutor_learnset:
                continue
            if move in compatibility_dict[mon_parsed]:
                tutor_learnset.append(move)
                continue
    tm_learnset.sort()
    tutor_learnset.sort()
    tm_learnset += tutor_learnset
    repl = "static const u16 s%sTeachableLearnset[] = {\n    " % mon
    if len(tm_learnset) > 0:
        repl += ",\n    ".join(tm_learnset) + ",\n    "
    repl += "MOVE_UNAVAILABLE,\n};"
    newout = re.sub(r'static const u16 s%sTeachableLearnset\[\] = {[\s\S]*?};' % mon, repl, out)
    if newout != out:
        out = newout
        print("Updated %s" % mon)

# add/update header
header = "//\n// DO NOT MODIFY THIS FILE! It is auto-generated from tools/learnset_helpers/teachable.py\n//\n\n"
longest_move_name = 0
for move in tm_moves + tutor_moves:
    if len(move) > longest_move_name:
        longest_move_name = len(move)
longest_move_name += 2 # + 2 for a hyphen and a space

universal_title = "Near-universal moves found in sUniversalMoves:"
tmhm_title = "TM/HM moves found in \"include/constants/tms_hms.h\":"
tutor_title = "Tutor moves found in \"src/data/pokemon/tutor_moves.h\":"

if longest_move_name < len(universal_title):
    longest_move_name = len(universal_title)
if longest_move_name < len(tmhm_title):
    longest_move_name = len(tmhm_title)
if longest_move_name < len(tutor_title):
    longest_move_name = len(tutor_title)

def header_print(str):
    global header
    header += "// " + str + " " * (longest_move_name - len(str)) + " //\n"

header += "// " + longest_move_name * "*" + " //\n"
header_print(tmhm_title)
for move in tm_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(tutor_title)
tutor_moves.sort() # alphabetically sort tutor moves for easier referencing
for move in tutor_moves: 
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(universal_title)
universal_moves.sort() # alphabetically sort near-universal moves for easier referencing
for move in universal_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n\n"

if not "// DO NOT MODIFY THIS FILE!" in out:
    out = header + out
else:
    out = re.sub(r"\/\/\n\/\/ DO NOT MODIFY THIS FILE!(.|\n)*\* \/\/\n\n", header, out)

with open("./src/data/pokemon/teachable_learnsets.h", 'w') as file:
    file.write(out)
