-- Brewfest Coren Direbrew
/* TODO
-- Faltante Loot. Chekear.
*/
DELETE FROM `gameobject` WHERE `id` = 188498; -- Spawn Mole- machine Consola en la entrada de Brd
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(188498, 230, 1, 1, 1133.59, -462.347, -103.659, 5.75403, 0, 0, 0.261501, -0.965203, 300, 0, 1);
DELETE FROM `game_event_gameobject` WHERE `guid` IN (SELECT `guid` FROM `gameobject` WHERE `id` = 188498); -- Añadido al eventlink correspondiente.
INSERT INTO `game_event_gameobject` (`guid`, `eventEntry`) VALUES
((SELECT `guid` FROM `gameobject` WHERE `id` = 188498), 24);
DELETE FROM `creature` WHERE `id` IN (23872); -- Spawn Coren Direbrew
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(23872, 230, 1, 1, 0, 0, 890.38, -135.366, -49.7525, 5.19012, 300, 0, 0, 302400, 0, 0, 0, 0, 0);
DELETE FROM `game_event_creature` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` IN (23872));
INSERT INTO `game_event_creature` (`guid`, `eventEntry`) VALUES
((SELECT `guid` FROM `creature` WHERE `id` = 23872), 24);
-- Spawn de creatures por guid asignadas a correcto evento ID.
DELETE FROM `game_event_creature` WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id` IN (23872,26719,27584,28329)); -- Añadido al eventlink correspondiente.
-- Añadido ScriptNames
UPDATE `creature_template` SET `ScriptName` = 'npc_coren_direbrew', `flags_extra` = 0, `dmg_multiplier` = 20, `lootid` = 23872 WHERE `entry` = 23872;
UPDATE `creature_template` SET `ScriptName` = 'npc_brewmaiden' WHERE `entry` IN (26822,26764);
UPDATE `creature_template` SET `faction_A` = 736, `faction_H` = 736 WHERE `entry` = 26776;
UPDATE `gameobject_template` SET `ScriptName` = 'go_mole_machine_console' WHERE `entry` = 188498;
-- Limite Targets
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN (47344, 47310);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`) VALUES
(13, 47310, 18, 1, 0),-- Cast Disarm AOE
(13, 47344, 18, 1, 26764), 
(13, 47344, 18, 1, 26822);  
-- Spell scripts
DELETE FROM `spell_scripts` WHERE `id`=47344;
INSERT INTO `spell_scripts` (`id`, `effIndex`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`)
VALUES
(47344, 0, 0, 15, 47339, 3, 0, 0, 0, 0, 0); -- cast back "Send Second Mug" on "Request Second Mug" hit
-- Spell Auras Drinking Brew
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 47371;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(47371, -47376, 1, 'Remove Visual Buff'),
(47371, -47331, 1, 'Remove Has Brew Aura');
-- Inmunidades
UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask`|1|2|8|16|32|64|128|256|512|1024|2048|4096|8192|65536|131072|524288|4194304|8388608|33554432|67108864|536870912 WHERE `entry` IN (23872,26822,26764);

UPDATE `quest_template` SET `SpecialFlags`=9 WHERE `entry`=25483;
UPDATE `creature_template` SET `npcflag`=3 WHERE `entry`=23872;

-- Tapper Swindlekeg <Brewfest Organizer>
-- Ipfelkofer Ironkeg <Brewfest Organizer>
-- Tapper Swindlekeg SAI
SET @ENTRY := 24711;
SET @QUEST_DIRE_BREW := 12492;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,@QUEST_DIRE_BREW,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Tapper Swindlekeg - On Quest Complete - Say Line 0 (random)");
-- Text
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Well time's money, and time's wasting! Let's have that drink...",12,0,100,1,0,0,"Tapper Swindlekeg"),
(@ENTRY,0,1,"Wow! This really greases the steamplugs!",12,0,100,1,0,0,"Tapper Swindlekeg"),
(@ENTRY,0,2,"If I were an honest goblin, I'd say this was the best beer of the festival...",12,0,100,1,0,0,"Tapper Swindlekeg"),
(@ENTRY,0,3,"Too bad Coren's dead. If I could buy that brew from him and resell it - watered down and rebottled under my own label, of course - I'd be rich!",12,0,100,1,0,0,"Tapper Swindlekeg"),
-- These two are handled through script
(@ENTRY,1,0,"Hey there, and welcome to Brewfest. Come in and have a drink or three!",12,0,100,1,0,0,"Tapper Swindlekeg"),
(@ENTRY,1,1,"What's up, friend? Welcome to the Brewfest Grounds! Now go buy some drinks!",12,0,100,1,0,0,"Tapper Swindlekeg"),
(@ENTRY,1,2,"Hey hey, it's another $r! Welcome to my annual Brewfest celebration... now go feast and drink some!",12,0,100,1,0,0,"Tapper Swindlekeg");
-- Ipfelkofer Ironkeg SAI
SET @ENTRY := 24710;
SET @QUEST_DIRE_BREW := 12491;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,@QUEST_DIRE_BREW,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Ipfelkofer Ironkeg - On Quest Complete - Say Line 0 (random)");
-- Text
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Right! Let's try this so-called dire brew...",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
(@ENTRY,0,1,"Bronzebeard's beard! What a drink!",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
(@ENTRY,0,2,"$N, this beer... well, it might be the best of Brewfest!",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
(@ENTRY,0,3,"It is a shame Coren's Dire Brew can't quench more thirsting throats! It's blasphemy, I know, but I envy those Dark Iron dwarves!",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
-- These two are handled through script
(@ENTRY,1,0,"Ho there, and welcome to Brewfest!",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
(@ENTRY,1,1,"Hello, friend! Welcome to the Brewfest Grounds!",12,0,100,1,0,0,"Ipfelkofer Ironkeg"),
(@ENTRY,1,2,"Hail, good $c! Welcome to Ironforge's annual Brewfest celebration!",12,0,100,1,0,0,"Ipfelkofer Ironkeg");
-- Areatrigger scriptname
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (4829,4820);
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES
(4829,'at_brewfest'), -- Durotar
(4820,'at_brewfest'); -- Dun Morogh

-- [Q] Catch the Wild Wolpertinger!
-- [Q] [A/H] Catch the Wild Wolpertinger!
-- Conditions already exist with proper ErrorTextId
-- Wild Wolpertinger SAI
SET @ENTRY := 23487;
SET @SPELL_NET := 41621;
SET @SPELL_CREATE_ITEM := 41622;
UPDATE `creature_template` SET `AIName`='SmartAI',`unit_flags`=`unit_flags`|512 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,2,8,0,100,0,@SPELL_NET,0,0,0,11,@SPELL_CREATE_ITEM,2,0,0,0,0,7,0,0,0,0,0,0,0,"Wild Wolpertinger - On Spellhit - Cast Create Stunned Wolpertinger Item"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,4000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wild Wolpertinger - On Spellhit - Forced Despawn");

-- [Q] [A/H] Chug and Chuck
-- The chance of this event to occur is low according to videos!
-- XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
-- Self-Turning and Oscillating Utility Target SAI
SET @ENTRY := 24108;
SET @SPELL_THROW_MUG := 42300;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,8,0,100,0,@SPELL_THROW_MUG,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Self-Turning and Oscillating Utility Target - On Spellhit - Quest Credit");
-- Condition for spell
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (13) AND `SourceEntry` IN (42436,42300);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,0,42436,0,18,1,0,0,0,'',"Spell Drink! targets player"),
(13,0,42300,0,18,24108,0,0,0,'',"Spell Brewfest - Throw Mug targets Self-Turning and Oscillating Utility Target");
-- Spell Drink! should make you throw a mug
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=42436 AND `spell_effect`=42300;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(42436,42300,1,'Drink! will now also cast Brewfest - Throw Mug');
-- [Q] [A/H] Pink Elekks On Parade
-- We were able to kill them for credits.. (faction).
-- Tirisfal Pink Elekk SAI
SET @ENTRY := 23530;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Tirisfal Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tirisfal Pink Elekk - On Spellhit - Forced Despawn");
-- Eversong Pink Elekk SAI
SET @ENTRY := 23531;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Eversong Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eversong Pink Elekk - On Spellhit - Forced Despawn");
-- Mulgore Pink Elekk SAI
SET @ENTRY := 23529;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mulgore Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mulgore Pink Elekk - On Spellhit - Forced Despawn");
-- Elwynn Pink Elekk SAI
SET @ENTRY := 23507;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Elwynn Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elwynn Pink Elekk - On Spellhit - Forced Despawn");
-- Teldrassil Pink Elekk SAI
SET @ENTRY := 23527;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Teldrassil Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Teldrassil Pink Elekk - On Spellhit - Forced Despawn");
-- Azuremyst Pink Elekk SAI
SET @ENTRY := 23528;
SET @SPELL_ELEKK_DISPERSION := 44654;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction_A`=35,`faction_H`=35 WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,@SPELL_ELEKK_DISPERSION,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Azuremyst Pink Elekk - On Spellhit - Quest Credit"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Azuremyst Pink Elekk - On Spellhit - Forced Despawn");
-- Gordok Brew Barker SAI
SET @ENTRY := 23685;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,5000,5000,0,11,@SPELL_DRINK,2,0,0,0,0,7,0,0,0,0,0,0,0,"Gordok Brew Barker - Emote Receive 'Wave' - Cast Create Complimentary Brewfest Sampler"),
(@ENTRY,0,1,0,1,0,100,0,30000,45000,180000,240000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Gordok Brew Barker - Out of Combat - Yell Line 0 (random)");
-- Text
DELETE FROM `script_texts` WHERE `entry` BETWEEN -717 AND -719;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"YOU TRY DA' BEST, NOW TRY DA' REST! OGRE BREW!",14,0,100,1,0,0,"Gordok Brew Barker"),
(@ENTRY,0,1,"HEY YOU! DRINK OGRE BREWS! MAKE YOU BIG AND STRONG!",14,0,100,1,0,0,"Gordok Brew Barker"),
(@ENTRY,0,2,"YOU WANT DRINK? WE GOT DRINK!",14,0,100,1,0,0,"Gordok Brew Barker"),
-- Dark Iron Attack
(@ENTRY,1,0,"SOMEONE TRY THIS SUPER BREW!",14,0,100,1,0,0,"Gordok Brew Barker");
-- Blix Fixwidget SAI
SET @ENTRY := 24495;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,5000,5000,0,11,@SPELL_DRINK,2,0,0,0,0,7,0,0,0,0,0,0,0,"Blix Fixwidget - Emote Receive 'Wave' - Cast Create Complimentary Brewfest Sampler"),
(@ENTRY,0,1,0,1,0,100,0,30000,45000,180000,240000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Blix Fixwidget - Out of Combat - Say Line 0 (random)");
-- Text
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Whoah! Walk by again girl!",12,0,100,1,0,0,"Blix Fixwidget"),
(@ENTRY,0,1,"Hey! Sweet cheeks, over here!",12,0,100,1,0,0,"Blix Fixwidget"),
(@ENTRY,0,2,"Hey, hey sweet thing! Looking good!",12,0,100,1,0,0,"Blix Fixwidget"),
(@ENTRY,0,3,"Hey, hey! Nice build you got there honey!",12,0,100,1,0,0,"Blix Fixwidget"),
(@ENTRY,0,4,"Yo! Big lady! You think you're big enough to handle me?",12,0,100,1,0,0,"Blix Fixwidget");
-- Drohn's Distillery Barker SAI
SET @ENTRY := 24492;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,5000,5000,0,11,@SPELL_DRINK,2,0,0,0,0,7,0,0,0,0,0,0,0,"Drohn's Distillery Barker - Emote Receive 'Wave' - Cast Create Complimentary Brewfest Sampler"),
(@ENTRY,0,1,0,1,0,100,0,30000,45000,180000,240000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Drohn's Distillery Barker - Out of Combat - Say Line 0 (random)");
-- Text
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Drohn's brew is the stuff legends are made of! Come taste the legend!",12,0,100,1,0,0,"Drohn's Distillery Barker"),
(@ENTRY,0,1,"We drink for the Horde! Do you drink for the Horde? Come show us at Drohn's Distillery!",12,0,100,1,0,0,"Drohn's Distillery Barker"),
(@ENTRY,0,2,"Hey you, the tall one... Want to put some hair on your chest? Drohn's Distillery can help you out!",12,0,100,1,0,0,"Drohn's Distillery Barker"),
(@ENTRY,0,3,"Drohn's Distillery has the best brew money can buy! They were voted 'Outstanding Brew' by Monthly Goblin Brew!",12,0,100,1,0,0,"Drohn's Distillery Barker"),
-- Dark Iron Attack
(@ENTRY,1,0,"Chug and chuck! Chug and chuck!",14,0,100,1,0,0,"Drohn's Distillery Barker"),
(@ENTRY,2,0,"Down the free brew and pelt the Guzzlers with your mug!",14,0,100,1,0,0,"Drohn's Distillery Barker"),
(@ENTRY,3,0,"SOMEONE TRY THIS SUPER BREW!",14,0,100,1,0,0,"Drohn's Distillery Barker");
-- T'chali's Voodoo Brewery Barker SAI
SET @ENTRY := 24493;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,5000,5000,0,11,@SPELL_DRINK,2,0,0,0,0,7,0,0,0,0,0,0,0,"T'chali's Voodoo Brewery Barker - Emote Receive 'Wave' - Cast Create Complimentary Brewfest Sampler"),
(@ENTRY,0,1,0,1,0,100,0,30000,45000,180000,240000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T'chali's Voodoo Brewery Barker - Out of Combat - Say Line 0 (random)");
-- Text
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0,"Drohn's brew is the stuff legends are made of! Come taste the legend!",12,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
(@ENTRY,0,1,"We drink for the Horde! Do you drink for the Horde? Come show us at Drohn's Distillery!",12,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
(@ENTRY,0,2,"Hey you, the tall one... Want to put some hair on your chest? Drohn's Distillery can help you out!",12,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
(@ENTRY,0,3,"Drohn's Distillery has the best brew money can buy! They were voted 'Outstanding Brew' by Monthly Goblin Brew!",12,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
-- Dark Iron Attack
(@ENTRY,1,0,"Chug and chuck! Chug and chuck!",14,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
(@ENTRY,2,0,"Down the free brew and pelt the Guzzlers with your mug!",14,0,100,1,0,0,"T'chali's Voodoo Brewery Barker"),
(@ENTRY,3,0,"SOMEONE TRY THIS SUPER BREW!",14,0,100,1,0,0,"T'chali's Voodoo Brewery Barker");
-- Brewfest Reveler SAI
SET @ENTRY := 24484;
SET @SPELL_CREATE_MUG := 42518;
SET @SPELL_TOAST := 41586;
UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry`=@ENTRY;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,5000,5000,0,11,@SPELL_CREATE_MUG,2,0,0,0,0,7,0,0,0,0,0,0,0,"Brewfest Reveler - Emote Receive 'Wave' - Cast Create Complimentary Brewfest Sampler"),
(@ENTRY,0,1,0,22,0,100,0,34,5000,5000,0,11,@SPELL_TOAST,2,0,0,0,0,7,0,0,0,0,0,0,0,"Brewfest Reveler - Emote Receive 'Dance' - Cast Brewfest Toast");
-- Condition for spell
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=42518;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,0,42518,0,18,1,0,0,0,'',"Spell Create Complimentary Brewfest Sampler targets players"),
(13,0,42518,0,26,33096,0,0,0,'',"Spell Create Complimentary Brewfest Sampler targets players");