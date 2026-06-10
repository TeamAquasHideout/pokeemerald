import os, re, json, shutil, textwrap
from pathlib import Path

root = Path('/mnt/data/work_pit/pokeemerald-thepit_v2')
imp = Path('/mnt/data/work_pit/thepit_import')
requested_import = [
'RATTATA','RATREECATE','SPEAROW','FEAROW','EKANS','ARBOK','SANDSHREW','SANDSLASH','PONYTA','RAPIDASH','KRABBY','KINGLER',
'EXEGGCUTE','EXEGGUTOR','SMOOCHUM','JYNX','AERODACTYL','STANTLER','TANGELA','TANGROWTH','MEGANIUM',
'FERALIGATR','NATU','XATU','MAGBY','MAGMAR','MAGMORTAR','MAREEP','FLAAFFY','AMPHAROS','MISMAGIUS',
'MANTINE','BELLOSSOM','POOCHYENA','MIGHTYENA','BARBOACH','WHISCASH','GULPIN','SWALOT','RELICANTH',
'DUSKULL','DUSCLOPS','DUSKNOIR','RALTS','KIRLIA','GARDEVOIR','ABSOL','VOLBEAT','ILLUMISE',
'ARON','LAIRON','AGGRON','DUSTOX','BEAUTIFLY','GALLADE','CHANSEY','BLISSEY',
'VULPIX','NINETALES','CORSOLA','REEFSOLA','YGGDREON','SNEASEL','WEAVILE','SHROOMISH','BRELOOM','MEDITITE','MEDICHAM',
'JIGGLYPUFF','WIGGLYTUFF','HOOTHOOT','NOCTOWL','SUNKERN','SUNFLORA','OMANYTE','OMASTAR','KABUTO','KABUTOPS','CUBONE','MAROWAK',
'MACHOP','MACHOKE','MACHAMP','FARFETCH_D','BALTOY','CLAYDOL','WAILORD',
'ELEKID','ELECTABUZZ','ELECTIVIRE',
'CELEBI','REGIROCK','REGICE','REGISTEEL','REGIGIGAS',
'PLUSLE','MINUN','KECLEON','MAWILE','BLAZIKEN','GOROCHU'
]
custom_species = {
    'GOROCHU': ('SPECIES_GOROCHU', 'Gorochu', 'gorochu'),
    'REEFSOLA': ('SPECIES_REEFSOLA', 'Reefsola', 'reefsola'),
    'YGGDREON': ('SPECIES_YGGDREON', 'Yggdreon', 'yggdreon'),
    'PLUSLE': ('SPECIES_PLUSLE_BATTLE_BOND', 'Plusle-BB', 'plusle_battle_bond'),
    'MINUN': ('SPECIES_MINUN_BATTLE_BOND', 'Minun-BB', 'minun_battle_bond'),
    'KECLEON': ('SPECIES_KECLEON_BATTLE_BOND', 'Kecleon-BB', 'kecleon_battle_bond'),
    'MAWILE': ('SPECIES_MAWILE_BATTLE_BOND', 'Mawile-BB', 'mawile_battle_bond'),
    'BLAZIKEN': ('SPECIES_BLAZIKEN_BATTLE_BOND', 'BlazikenBB', 'blaziken_battle_bond'),
}
existing_map = {s:s for s in requested_import if s not in custom_species}
existing_map.update({'RATREECATE':'RATICATE','FARFETCH_D':'FARFETCHD'})
for s in ['PLUSLE','MINUN','KECLEON','MAWILE','BLAZIKEN','GOROCHU','REEFSOLA','YGGDREON']:
    existing_map.pop(s, None)

camel_overrides = {'FARFETCHD':'Farfetchd','MR_MIME':'MrMime','MIME_JR':'MimeJr','HO_OH':'HoOh','PORYGON_Z':'PorygonZ','NIDORAN_F':'NidoranF','NIDORAN_M':'NidoranM','RATICATE':'Raticate'}
def camel_species(sym):
    if sym in camel_overrides: return camel_overrides[sym]
    return ''.join(part.capitalize() for part in sym.lower().split('_'))
def read(p): return Path(p).read_text()
def write(p,t): Path(p).write_text(t)

species_info_imp=read(imp/'src/data/pokemon/species_info_imported.h')
learn_imp=read(imp/'src/data/pokemon/level_up_learnsets_imported.h')
move_imp=read(imp/'src/data/moves_info_imported.h')
ability_imp=read(imp/'src/data/abilities_imported.h')
manifest=json.loads(read(imp/'manifest.json'))

def extract_entry(text, designator):
    pat=re.compile(r'^\s*\['+re.escape(designator)+r'\]\s*=\s*\{.*?^\s*\},', re.M|re.S)
    m=pat.search(text)
    return m.group(0) if m else None

def extract_learnset(import_sp):
    pat=re.compile(r'static const struct LevelUpMove sLevelUpLearnset_'+re.escape(import_sp)+r'\[\]\s*=\s*\{(.*?)\n\};', re.S)
    m=pat.search(learn_imp)
    return m.group(1).strip() if m else None

def extract_import_species_fields(import_sp):
    block=extract_entry(species_info_imp, 'SPECIES_'+import_sp)
    if not block: raise KeyError(import_sp)
    fields={}
    for fld in ['baseHP','baseAttack','baseDefense','baseSpeed','baseSpAttack','baseSpDefense','catchRate','expYield','genderRatio','eggCycles','friendship','growthRate','bodyColor','natDexNum']:
        m=re.search(r'\.'+fld+r'\s*=\s*([^,\n]+)', block)
        if m: fields[fld]=m.group(1).strip()
    for fld in ['types','eggGroups']:
        m=re.search(r'\.'+fld+r'\s*=\s*([^\n]+),', block)
        if m: fields[fld]=m.group(1).strip()
    m=re.search(r'\.abilities\s*=\s*\{([^}]*)\}', block)
    if m: fields['abilities']='{ '+m.group(1).strip()+' }'
    m=re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', block)
    if m:
        fields['speciesName']='_("'+m.group(1)+'")'
        fields['species_name_text']=m.group(1)
    return fields, block

# Aliases for expansion naming.
move_alias_manual={
 'MOVE_MYSTICALFIRE':'MOVE_MYSTICAL_FIRE','MOVE_PHANTOMFORCE':'MOVE_PHANTOM_FORCE','MOVE_POWERUPPUNCH':'MOVE_POWER_UP_PUNCH','MOVE_HIHORSEPOWER':'MOVE_HIGH_HORSEPOWER','MOVE_DUALWINGBEAT':'MOVE_DUAL_WINGBEAT','MOVE_COTTONSPORE':'MOVE_COTTON_SPORE',
}
ability_alias_manual={'ABILITY_LIGHTNINGROD':'ABILITY_LIGHTNING_ROD','ABILITY_RUNAWAY':'ABILITY_RUN_AWAY','ABILITY_COMPOUNDEYES':'ABILITY_COMPOUND_EYES','ABILITY_MEGA_LAUNCHR':'ABILITY_MEGA_LAUNCHER'}

target_move_names=set(re.findall(r'#define\s+(MOVE_[A-Z0-9_]+)\b',read(root/'include/constants/moves.h')))
for name in set(re.findall(r'MOVE_[A-Z0-9_]+', learn_imp+'\n'+move_imp)):
    if name not in target_move_names and name not in move_alias_manual:
        norm=name.replace('_','')
        c=[m for m in target_move_names if m.replace('_','')==norm]
        if len(c)==1: move_alias_manual[name]=c[0]

target_ability_names=set(re.findall(r'#define\s+(ABILITY_[A-Z0-9_]+)\b',read(root/'include/constants/abilities.h')))
for name in set(re.findall(r'ABILITY_[A-Z0-9_]+', species_info_imp+'\n'+ability_imp)):
    if name not in target_ability_names and name not in ability_alias_manual:
        norm=name.replace('_','')
        c=[a for a in target_ability_names if a.replace('_','')==norm]
        if len(c)==1: ability_alias_manual[name]=c[0]

def norm_moves(s):
    for a,b in sorted(move_alias_manual.items(), key=lambda kv:-len(kv[0])):
        s=re.sub(r'\b'+re.escape(a)+r'\b', b, s)
    return s

def norm_abilities(s):
    for a,b in sorted(ability_alias_manual.items(), key=lambda kv:-len(kv[0])):
        s=re.sub(r'\b'+re.escape(a)+r'\b', b, s)
    return s

# Used moves/abilities.
used_moves=set(); used_abilities=set()
for sp in requested_import:
    ls=extract_learnset(sp)
    if ls: used_moves.update(re.findall(r'MOVE_[A-Z0-9_]+', norm_moves(ls)))
    f,_=extract_import_species_fields(sp)
    used_abilities.update(re.findall(r'ABILITY_[A-Z0-9_]+', norm_abilities(f.get('abilities',''))))

# 1) Type constant.
pokemon_h=read(root/'include/constants/pokemon.h')
if 'TYPE_AETHER' not in pokemon_h:
    pokemon_h=pokemon_h.replace('#define TYPE_STELLAR          20\n#define NUMBER_OF_MON_TYPES   21', '#define TYPE_STELLAR          20\n#define TYPE_AETHER           21\n#define NUMBER_OF_MON_TYPES   22')
write(root/'include/constants/pokemon.h', pokemon_h)

# 2) Type info/effectiveness.
types_h=read(root/'src/data/types_info.h')
if '[TYPE_AETHER]' not in types_h:
    # extend rows with a default Aether column, then patch imported Aether matchup column and row.
    types_h=types_h.replace('Stellar', 'Stellar  Aether', 1)
    def add_col(m): return m.group(1)+', ______'+m.group(2)
    types_h=re.sub(r'^(\s*\[TYPE_[A-Z_]+\]\s*=\s*\{[^\n\}]+)(\},)$', add_col, types_h, flags=re.M)
    target_type_order=['TYPE_NONE','TYPE_NORMAL','TYPE_FIGHTING','TYPE_FLYING','TYPE_POISON','TYPE_GROUND','TYPE_ROCK','TYPE_BUG','TYPE_GHOST','TYPE_STEEL','TYPE_MYSTERY','TYPE_FIRE','TYPE_WATER','TYPE_GRASS','TYPE_ELECTRIC','TYPE_PSYCHIC','TYPE_ICE','TYPE_DRAGON','TYPE_DARK','TYPE_FAIRY','TYPE_STELLAR','TYPE_AETHER']
    eff={(e['attack'],e['defend']):e['multiplierByte'] for e in manifest['typeChart']}
    def mval(atk,defn):
        b=eff.get((atk,defn),10)
        return {0:'X(0.0)',5:'X(0.5)',10:'______',20:'X(2.0)'}.get(b, f'X({b/10:.1f})')
    # patch Aether defender values into existing rows
    for atk in target_type_order[:-1]:
        row=re.search(r'^(\s*\['+atk+r'\]\s*=\s*\{)([^\n]+)(\},)$', types_h, re.M)
        if not row: continue
        cells=[c.strip() for c in row.group(2).split(',')]
        if len(cells)>=22:
            cells[21]=mval(atk,'TYPE_AETHER') if (atk,'TYPE_AETHER') in eff else '______'
            types_h=types_h[:row.start(2)]+', '.join(cells)+types_h[row.end(2):]
    arow=', '.join(mval('TYPE_AETHER', t) if ('TYPE_AETHER',t) in eff else '______' for t in target_type_order)
    types_h=re.sub(r'(\n\s*\[TYPE_STELLAR\]\s*=\s*\{[^\n]+\},)', r'\1\n    [TYPE_AETHER]  = {'+arow+'},', types_h, count=1)
    ainfo=textwrap.dedent('''\
        [TYPE_AETHER] =
        {
            .name = _("Aether"),
            .name_short = _("Aethr"),
            .name_code = _("AET"),
            .generic = _("an AETHER move"),
            .palette = 15, // Reuses Mystery palette until a dedicated type icon is supplied.
            .teraTypeRGBValue = RGB(20, 20, 31),
            .damageCategory = DAMAGE_CATEGORY_SPECIAL,
            .paletteTMHM = gItemIconPalette_NormalTMHM,
            .useSecondTypeIconPalette = FALSE,
            .isSpecialCaseType = FALSE,
            .isHiddenPowerType = TRUE,
        },
    ''')
    idx=types_h.rfind('\n};')
    types_h=types_h[:idx]+'\n'+ainfo+types_h[idx:]
write(root/'src/data/types_info.h', types_h)

# 3) Move constants and move data.
moves_h=read(root/'include/constants/moves.h')
existing_moves=set(re.findall(r'#define\s+(MOVE_[A-Z0-9_]+)\b', moves_h))
# Add official alias defines for used import spellings.
alias_lines=[]
for a,b in sorted(move_alias_manual.items()):
    if a in used_moves or a in re.findall(r'MOVE_[A-Z0-9_]+', learn_imp):
        if a not in existing_moves and b in existing_moves:
            alias_lines.append(f'#define {a} {b} // ThePit FireRed import alias')
# Used moves already normalized, missing custom are those no existing define.
used_norm={move_alias_manual.get(m,m) for m in used_moves}
existing_moves=set(re.findall(r'#define\s+(MOVE_[A-Z0-9_]+)\b', moves_h))
missing_custom=sorted(m for m in used_norm if m not in existing_moves)
# include only custom moves with import data
missing_custom=[m for m in missing_custom if extract_entry(move_imp,m)]
if 'MOVE_THEPIT_IMPORT_FIRST' not in moves_h:
    last_gen9=int(re.search(r'#define\s+MOVES_COUNT_GEN9\s+(\d+)', moves_h).group(1))
    const_lines=[]
    if alias_lines:
        const_lines.append('// Aliases for FireRed-import move names used by The Pit data.')
        const_lines.extend(alias_lines)
        const_lines.append('')
    const_lines.append('// Custom moves imported from the FireRed The Pit ROM hack.')
    const_lines.append(f'#define MOVE_THEPIT_IMPORT_FIRST {last_gen9}')
    for i,m in enumerate(missing_custom):
        const_lines.append(f'#define {m:<38} {last_gen9+i}')
    const_lines.append(f'#define MOVES_COUNT_THEPIT_IMPORT {last_gen9+len(missing_custom)}')
    insert='\n'.join(const_lines)+'\n\n'
    moves_h=moves_h.replace('#define MOVES_COUNT_GEN9 848\n\n#define MOVES_COUNT         MOVES_COUNT_GEN9', '#define MOVES_COUNT_GEN9 848\n\n'+insert+'#define MOVES_COUNT         MOVES_COUNT_THEPIT_IMPORT')
write(root/'include/constants/moves.h', moves_h)

moves_info_h=read(root/'src/data/moves_info.h')
if 'The Pit FireRed custom move entries' not in moves_info_h:
    entries=['    // The Pit FireRed custom move entries. FireRed animation/effect bytecode is preserved under thepit_imported_raw/;\n    // battleAnimScript uses a safe placeholder until scripts are ported to expansion format.']
    for m in missing_custom:
        block=extract_entry(move_imp,m)
        if not block: continue
        # strip designator indentation to 4 spaces and normalize aliases/abilities; remove unsupported comments fine.
        block=norm_moves(block)
        block=block.replace('    ['+m+']', '    ['+m+']')
        # Avoid leaving imported placeholder comment as invalid? EFFECT_PLACEHOLDER /*...*/ is valid.
        if '.battleAnimScript' not in block:
            # add before closing of block
            block=re.sub(r'\n\s*\},\s*$', '\n        .battleAnimScript = gBattleAnimMove_Tackle,\n    },', block)
        entries.append(block.rstrip())
    idx=moves_info_h.rfind('\n};')
    moves_info_h=moves_info_h[:idx]+'\n\n'+'\n'.join(entries)+'\n'+moves_info_h[idx:]
write(root/'src/data/moves_info.h', moves_info_h)

# 4) Ability constants and info.
abilities_h=read(root/'include/constants/abilities.h')
existing_abs=set(re.findall(r'#define\s+(ABILITY_[A-Z0-9_]+)\b', abilities_h))
custom_abs=sorted(a for a in used_abilities if a not in existing_abs)
# add only if import block exists
custom_abs=[a for a in custom_abs if extract_entry(ability_imp,a)]
if 'ABILITY_THEPIT_IMPORT_FIRST' not in abilities_h:
    last=int(re.search(r'#define\s+ABILITIES_COUNT_GEN9\s+(\d+)', abilities_h).group(1))
    lines=['// Aliases for FireRed-import ability spellings.']
    for a,b in sorted(ability_alias_manual.items()):
        if a not in existing_abs and b in existing_abs:
            lines.append(f'#define {a} {b} // ThePit FireRed import alias')
    lines.append('')
    lines.append('// Custom abilities imported from the FireRed The Pit ROM hack.')
    lines.append(f'#define ABILITY_THEPIT_IMPORT_FIRST {last}')
    for i,a in enumerate(custom_abs):
        lines.append(f'#define {a:<38} {last+i}')
    lines.append(f'#define ABILITIES_COUNT_THEPIT_IMPORT {last+len(custom_abs)}')
    abilities_h=abilities_h.replace('#define ABILITIES_COUNT_GEN9 311\n\n#define ABILITIES_COUNT ABILITIES_COUNT_GEN9', '#define ABILITIES_COUNT_GEN9 311\n\n'+'\n'.join(lines)+'\n\n#define ABILITIES_COUNT ABILITIES_COUNT_THEPIT_IMPORT')
write(root/'include/constants/abilities.h', abilities_h)

abilities_info_h=read(root/'src/data/abilities.h')
if 'The Pit FireRed custom ability entries' not in abilities_info_h:
    entries=['    // The Pit FireRed custom ability entries. Behavior still requires C battle-engine hooks where noted by the extractor.']
    for a in custom_abs:
        block=extract_entry(ability_imp,a)
        if not block: continue
        block=norm_abilities(block)
        # Add description_short if absent; optional but useful.
        if '.description_short' not in block:
            dm=re.search(r'\.description\s*=\s*COMPOUND_STRING\((.*?)\),', block, re.S)
            if dm:
                desc=dm.group(1).strip()
                block=block.replace(dm.group(0), dm.group(0)+f'\n        .description_short = COMPOUND_STRING({desc}),')
        entries.append(block.rstrip())
    idx=abilities_info_h.rfind('\n};')
    abilities_info_h=abilities_info_h[:idx]+'\n\n'+'\n'.join(entries)+'\n'+abilities_info_h[idx:]
write(root/'src/data/abilities.h', abilities_info_h)

# 5) Species constants: custom forms and alias Ratreecate.
species_h=read(root/'include/constants/species.h')
if 'SPECIES_RATREECATE' not in species_h:
    species_h=species_h.replace('#define SPECIES_RATICATE                                20', '#define SPECIES_RATICATE                                20\n#define SPECIES_RATREECATE                              SPECIES_RATICATE // ThePit FireRed import alias')
if 'SPECIES_GOROCHU' not in species_h:
    egg_match=re.search(r'#define\s+SPECIES_EGG\s+\(SPECIES_SUBSTITUTE_DOLL \+ 1\)', species_h)
    start=int(re.search(r'#define\s+SPECIES_SUBSTITUTE_DOLL\s+(\d+)', species_h).group(1))+1
    lines=['// The Pit FireRed imported custom species/forms']
    ordered_custom=['GOROCHU','REEFSOLA','YGGDREON','PLUSLE','MINUN','KECLEON','MAWILE','BLAZIKEN']
    val=start
    for sp in ordered_custom:
        const,_,_=custom_species[sp]
        lines.append(f'#define {const:<52} {val}')
        val+=1
    species_h=species_h[:egg_match.start()]+'\n'.join(lines)+'\n\n'+species_h[egg_match.start():]
    species_h=species_h.replace('#define SPECIES_EGG                                     (SPECIES_SUBSTITUTE_DOLL + 1)', f'#define SPECIES_EGG                                     ({custom_species["BLAZIKEN"][0]} + 1)')
write(root/'include/constants/species.h', species_h)

# 6) Patch existing species fields.
fields_to_replace=['baseHP','baseAttack','baseDefense','baseSpeed','baseSpAttack','baseSpDefense','types','catchRate','expYield','genderRatio','eggCycles','friendship','growthRate','eggGroups','abilities','bodyColor','speciesName']
# Locate family files that contain species entries.
species_files=list((root/'src/data/pokemon/species_info').glob('gen_*_families.h'))
patch_log=[]
for import_sp,target_sp in existing_map.items():
    fields,_=extract_import_species_fields(import_sp)
    fields={k:norm_abilities(v) if k=='abilities' else v for k,v in fields.items()}
    found=False
    for path in species_files:
        text=read(path)
        pat=re.compile(r'(?m)^    \[SPECIES_'+re.escape(target_sp)+r'\]\s*=\s*\{.*?^    \},', re.S)
        m=pat.search(text)
        if not m: continue
        block=m.group(0)
        for fld in fields_to_replace:
            if fld not in fields: continue
            val=fields[fld]
            # For imported Raticate replacement, name should be Ratreecate.
            if import_sp=='RATREECATE' and fld=='speciesName': val='_("Ratreecate")'
            line_re=re.compile(r'^(\s*\.'+fld+r'\s*=\s*)([^\n]+?)(,\s*)$', re.M)
            if line_re.search(block):
                block=line_re.sub(lambda mm: mm.group(1)+val+mm.group(3), block, count=1)
        text=text[:m.start()]+block+text[m.end():]
        write(path,text)
        patch_log.append(f'{import_sp}->{target_sp}')
        found=True
        break
    if not found:
        patch_log.append(f'MISSING_TARGET:{import_sp}->{target_sp}')

# 7) Patch level-up learnsets in active gen_9 and add custom form sets.
gen9=root/'src/data/pokemon/level_up_learnsets/gen_9.h'
g9=read(gen9)
def make_target_ls_body(import_sp, target_symbol):
    body=extract_learnset(import_sp)
    if body is None: return None
    body=norm_moves(body)
    return f'static const struct LevelUpMove s{camel_species(target_symbol)}LevelUpLearnset[] = {{\n{body}\n}};'
for import_sp,target_sp in existing_map.items():
    newdef=make_target_ls_body(import_sp,target_sp)
    if not newdef: continue
    pat=re.compile(r'static const struct LevelUpMove s'+re.escape(camel_species(target_sp))+r'LevelUpLearnset\[\]\s*=\s*\{.*?\n\};', re.S)
    if pat.search(g9):
        g9=pat.sub(newdef,g9,count=1)
# custom levelsets append
if 'The Pit FireRed imported custom species/form learnsets' not in g9:
    extra=['\n// The Pit FireRed imported custom species/form learnsets']
    for import_sp,(const,_,_) in custom_species.items():
        target_symbol=const.replace('SPECIES_','')
        newdef=make_target_ls_body(import_sp,target_symbol)
        if newdef: extra.append(newdef)
    g9 += '\n\n'+'\n\n'.join(extra)+'\n'
write(gen9,g9)

# 8) Add custom species entries to species_info.h.
spinfo=root/'src/data/pokemon/species_info.h'
si=read(spinfo)
if 'The Pit FireRed imported custom species/forms' not in si:
    entries=['    // The Pit FireRed imported custom species/forms']
    for import_sp,(const,display,dir_name) in custom_species.items():
        fields,_=extract_import_species_fields(import_sp)
        fields['abilities']=norm_abilities(fields['abilities'])
        symbol=const.replace('SPECIES_','')
        gfx=camel_species(symbol)
        body=f'''    [{const}] =
    {{
        .baseHP = {fields['baseHP']},
        .baseAttack = {fields['baseAttack']},
        .baseDefense = {fields['baseDefense']},
        .baseSpeed = {fields['baseSpeed']},
        .baseSpAttack = {fields['baseSpAttack']},
        .baseSpDefense = {fields['baseSpDefense']},
        .types = {fields['types']},
        .catchRate = {fields['catchRate']},
        .expYield = {fields['expYield']},
        .genderRatio = {fields['genderRatio']},
        .eggCycles = {fields['eggCycles']},
        .friendship = {fields['friendship']},
        .growthRate = {fields['growthRate']},
        .eggGroups = {fields['eggGroups']},
        .abilities = {fields['abilities']},
        .bodyColor = {fields['bodyColor']},
        .speciesName = _("{display}"),
        .cryId = CRY_NONE,
        .natDexNum = {fields.get('natDexNum','0')},
        .categoryName = _("Imported"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_{gfx},
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_{gfx},
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_{gfx},
        .shinyPalette = gMonShinyPalette_{gfx},
        .iconSprite = gMonIcon_{gfx},
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
        .levelUpLearnset = s{camel_species(symbol)}LevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
    }},'''
        entries.append(body)
    insert='\n\n'.join(entries)+'\n\n'
    marker='    /* You may add any custom species below this point based on the following structure: */'
    si=si.replace(marker, insert+marker)
write(spinfo,si)

# 9) Graphics: copy imported requested sprites over target dirs where existing, and add graphics symbols for custom forms.
# Existing dir mappings for sprite replacement.
dir_map={s.lower():s.lower() for s in requested_import}
dir_map.update({'ratreecate':'raticate','farfetch_d':'farfetchd'})
for s in ['plusle','minun','kecleon','mawile','blaziken','gorochu','reefsola','yggdreon']:
    dir_map.pop(s, None)
for import_dir,target_dir in dir_map.items():
    src=imp/'graphics/pokemon'/import_dir
    dst=root/'graphics/pokemon'/target_dir
    if src.exists() and dst.exists():
        for fname in ['anim_front.png','back.png','normal.pal','shiny.pal','icon.png']:
            if (src/fname).exists(): shutil.copy2(src/fname,dst/fname)
# Custom dirs.
custom_dir_sources={'gorochu':'gorochu','reefsola':'reefsola','yggdreon':'yggdreon','plusle_battle_bond':'plusle','minun_battle_bond':'minun','kecleon_battle_bond':'kecleon','mawile_battle_bond':'mawile','blaziken_battle_bond':'blaziken'}
for dst_dir,src_dir in custom_dir_sources.items():
    src=imp/'graphics/pokemon'/src_dir
    dst=root/'graphics/pokemon'/dst_dir
    dst.mkdir(parents=True,exist_ok=True)
    for fname in ['anim_front.png','back.png','normal.pal','shiny.pal','icon.png']:
        if (src/fname).exists(): shutil.copy2(src/fname,dst/fname)

gfx_h=read(root/'src/data/graphics/pokemon.h')
if 'The Pit FireRed imported custom species graphics' not in gfx_h:
    lines=['// The Pit FireRed imported custom species graphics']
    for import_sp,(const,_,dir_name) in custom_species.items():
        sym=camel_species(const.replace('SPECIES_',''))
        lines += [
            f'const u32 gMonFrontPic_{sym}[] = INCBIN_U32("graphics/pokemon/{dir_name}/anim_front.4bpp.smol");',
            f'const u32 gMonBackPic_{sym}[] = INCBIN_U32("graphics/pokemon/{dir_name}/back.4bpp.smol");',
            f'const u16 gMonPalette_{sym}[] = INCBIN_U16("graphics/pokemon/{dir_name}/normal.gbapal");',
            f'const u16 gMonShinyPalette_{sym}[] = INCBIN_U16("graphics/pokemon/{dir_name}/shiny.gbapal");',
            f'const u8 gMonIcon_{sym}[] = INCBIN_U8("graphics/pokemon/{dir_name}/icon.4bpp");',
            ''
        ]
    gfx_h += '\n'+'\n'.join(lines)+'\n'
write(root/'src/data/graphics/pokemon.h', gfx_h)

# 10) Preserve raw imported animations/effects and write report.
raw_dst=root/'thepit_imported_raw'
if not raw_dst.exists():
    shutil.copytree(imp, raw_dst, ignore=shutil.ignore_patterns('graphics/pokemon'))
# Write a concise integration report.
report=root/'THEPIT_IMPORT_REPORT.md'
report.write_text(f'''# The Pit FireRed Import Integration Report

Generated by `patch_thepit.py` from `/mnt/data/thepit_import.zip` into this `pokeemerald-thepit_v2` project.

## Imported scope

- Requested species patched or added: {len(requested_import)} FireRed export entries.
- Existing species patched in-place: {len([x for x in patch_log if not x.startswith('MISSING')])}.
- Custom species/form constants added: {len(custom_species)} (`GOROCHU`, `REEFSOLA`, `YGGDREON`, and Battle Bond form slots for Plusle/Minun/Kecleon/Mawile/Blaziken).
- Aether type added as `TYPE_AETHER` and `NUMBER_OF_MON_TYPES` bumped to 22.
- Custom moves added: {len(missing_custom)}.
- Custom abilities added: {len(custom_abs)}.

## Important caveats

- The FireRed export does **not** contain TM/HM compatibility data. I left teachable/TM learnsets unchanged for existing species and used `sNoneTeachableLearnset` for newly added custom species/forms.
- FireRed move animation scripts (`.ase`) and battle-effect scripts (`.bse`) are raw bytecode from a different engine. They are preserved under `thepit_imported_raw/`, but custom moves use `gBattleAnimMove_Tackle` as a safe placeholder until the scripts are manually ported to pokeemerald-expansion battle animation scripts.
- Ability names/descriptions were imported, but custom ability behavior still needs battle-engine C hooks. This matches the extractor note: ability code is not data.
- I could not run a full ROM compile in this environment because `arm-none-eabi-gcc` is not installed.

## Species patch log

```text
{os.linesep.join(patch_log)}
```
''')

print('patched existing species', len([x for x in patch_log if not x.startswith('MISSING')]))
print('missing target species entries', [x for x in patch_log if x.startswith('MISSING')])
print('custom moves', len(missing_custom))
print('custom abilities', len(custom_abs))
print('aliases moves', len(alias_lines))
print('custom species', list(custom_species.values()))
