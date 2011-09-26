-- Temp solution for frostmourn room
DELETE FROM `gameobject` WHERE `id` = 193070 and `map` = 631;
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('2710388', '193070', '631', '15', '1', '520', '-2524', '1038.42', '4.47344', '0', '0', '0.786348', '-0.617784', '300', '255', '1');

DELETE FROM `creature` WHERE `id` in (36823, 36824);
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('250250', '36823', '631', '15', '1', '0', '0', '495', '-2502', '1050', '5.49385', '300', '0', '0', '315000', '59910', '0', '0', '0', '0'),
('250251', '36824', '631', '15', '1', '0', '0', '495', '-2546', '1050.23', '1.72709', '300', '0', '0', '252000', '0', '0', '0', '0', '0');

-- GameObject
-- test platform destruction
UPDATE `gameobject_template` SET `flags` = 32 WHERE `entry` = 202161;
UPDATE `gameobject` SET `state` = '1' WHERE `id` IN (202161);

-- Boss
UPDATE `creature_template` SET `ScriptName`='boss_the_lich_king' WHERE `entry` = 36597;
-- Mobs
UPDATE `creature_template` SET `ScriptName`='npc_tirion_icc' WHERE `entry`= 38995;
UPDATE `creature_template` SET `ScriptName`='npc_valkyr_icc' WHERE `entry` = 36609;
UPDATE `creature_template` SET `ScriptName`='npc_vile_spirit_icc' WHERE `entry`= 37799;
UPDATE `creature_template` SET `ScriptName`='npc_shambling_horror_icc' WHERE `entry` = 37698;
UPDATE `creature_template` SET `ScriptName`='npc_raging_spirit_icc' WHERE `entry` = 36701;
UPDATE `creature_template` SET `ScriptName`='npc_ice_sphere_icc' WHERE `entry` = 36633;
UPDATE `creature_template` SET `ScriptName`='npc_defile_icc' WHERE `entry` = 38757;
UPDATE `creature_template` SET `ScriptName`='npc_terenas_fighter_icc' WHERE `entry` = 36823;
UPDATE `creature_template` SET `ScriptName`='npc_spirit_warden_icc' WHERE `entry` = 36824;
UPDATE `creature_template` SET `ScriptName`='npc_shadow_trap' WHERE `entry` = 39137;

UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 39137;
UPDATE `creature_template` SET `unit_flags` = 0, `vehicleid` = 533 WHERE `entry` IN (36609, 39120, 39121, 39122);
UPDATE `creature_template` SET `modelid1` = 11686 WHERE `entry` IN (15214,36633, 39305, 39306, 39307);
UPDATE `creature_template` SET `mechanic_immune_mask` = 12582928 WHERE `entry` IN (36609, 39120, 39121, 39122);

-- Spell
-- Linked spell

REPLACE INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(-70337,70338,0, 'The Lich King: Necrotic plague initial cast'),
(-70337,72846,0, 'The Lich King: Necrotic plague immun'),
(-70338,70338,0, 'The Lich King: Necrotic jump'),
(-69200,69201,0, 'The Lich King: Raging Spirit'),
(-70338,74074,0, 'The Lich King: Plague Siphon'),
(70860, 39432,2, 'Gravity when Frozen tron teleport - prevent fall down player');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72743,'spell_lich_king_defile'),
(74115,'spell_lich_king_pain_and_suffering'),
(68980,'spell_lich_king_harvest_soul'),
(74325,'spell_lich_king_harvest_soul'),
(74326,'spell_lich_king_harvest_soul'),
(74327,'spell_lich_king_harvest_soul'),
(70541,'spell_lich_king_infection'),
(73779,'spell_lich_king_infection'),
(73780,'spell_lich_king_infection'),
(73781,'spell_lich_king_infection'),
(70337,'spell_lich_king_necrotic_plague'),
(73912,'spell_lich_king_necrotic_plague'),
(73913,'spell_lich_king_necrotic_plague'),
(73914,'spell_lich_king_necrotic_plague'),
(68981,'spell_lich_king_winter'),
(74270,'spell_lich_king_winter'),
(74271,'spell_lich_king_winter'),
(74272,'spell_lich_king_winter'),
(72133,'spell_lich_king_pain_and_suffering_effect'),
(73789,'spell_lich_king_pain_and_suffering_effect'),
(73788,'spell_lich_king_pain_and_suffering_effect'),
(73790,'spell_lich_king_pain_and_suffering_effect'),
(70534,'spell_vile_spirit_distance_check'),
(70501,'spell_vile_spirit_target_search'),
(70498,'spell_lich_king_vile_spirit_summon'),
(70500,'spell_lich_king_vile_spirit_summon_visual'),
(69110,'spell_ice_burst_distance_check'),
(72262,'spell_lich_king_quake'),
(73159,'spell_lich_king_play_movie'),
(74506,'spell_valkyr_carry_can_cast'),
(68576,'spell_valkyr_eject_passenger'),
(69030,'spell_valkyr_target_search'),
(74361,'spell_lich_king_valkyr_summon'),
(72429,'spell_lich_king_tirion_mass_resurrection');

REPLACE INTO `conditions` VALUES ('13', '0', '71614', '0', '18', '1', '38995', '0', '0', '', 'LichKing - Ice Lock');

UPDATE waypoint_scripts SET delay = 3 WHERE dataint = 38879 AND command = 15;
DELETE FROM `spell_scripts` WHERE id = 72429 AND command = 15;
INSERT INTO `spell_scripts` VALUE ('72429','0','3','15','72423','0','0','0','0','0','0');

-- Achievements
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (12823, 13163, 13164, 13243, 13244, 13245, 13246, 13247);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`)
VALUES
(12823,12,0,0,''),
(12823,18,0,0,''),
(13243,12,1,0,''),
(13243,18,0,0,''),
(13163,12,2,0,''),
(13163,18,0,0,''),
(13164,12,3,0,''),
(13164,18,0,0,''),
(13244,12,1,0,''),
(13244,18,0,0,''),
(13245,12,3,0,''),
(13245,18,0,0,''),
(13246,12,0,0,''),
(13246,18,0,0,''),
(13247,12,2,0,''),
(13247,18,0,0,'');

-- Teleports
DELETE FROM `npc_text` WHERE `id` BETWEEN 800000 AND 800006;
INSERT INTO `npc_text` (`id`, `text0_0`) VALUES
(800000, 'Teleport to the Light\'s Hammer'),
(800001, 'Teleport to the Oratory of the Damned.'),
(800002, 'Teleport to the Rampart of Skulls.'),
(800003, 'Teleport to the Deathbringer\'s Rise.'),
(800004, 'Teleport to the Upper Spire.'),
(800005, 'Teleport to the Sindragosa\'s Lair'),
(800006, 'Teleport to The Frozen Throne');

DELETE FROM script_texts WHERE entry <= -1810001 AND entry >= -1810032;
INSERT INTO script_texts (npc_entry,entry,content_default,content_loc1,content_loc2,content_loc3,content_loc4,content_loc5,content_loc6,content_loc7,content_loc8,sound,type,language,emote,comment)VALUES
(36597,-1810001, 'So...the Light''s vaunted justice has finally arrived. Shall I lay down Frostmourne and throw myself at your mercy, Fordring?',null,null,null,null,null,null,null,null,17349,1,0,0,''),
(38995,-1810002, 'We will grant you a swift death, Arthas. More than can be said for the thousands you''ve tortured and slain.',null,null,null,null,null,null,null,null,17390,1,0,0,''),
(36597,-1810003, 'You will learn of that first hand. When my work is complete, you will beg for mercy -- and I will deny you. Your anguished cries will be testament to my unbridled power.',null,null,null,null,null,null,null,null,17350,1,0,0,''),
(38995,-1810004, 'So be it. Champions, attack!',null,null,null,null,null,null,null,null,17391,1,0,0,''),
(36597,-1810005, 'I''ll keep you alive to witness the end, Fordring. I would not want the Light''s greatest champion to miss seeing this wretched world remade in my image.',null,null,null,null,null,null,null,null,17351,1,0,0,''),
(38995,-1810006, 'Come then champions, feed me your rage!',null,null,null,null,null,null,null,null,17352,1,0,0,''),
(36597,-1810007, 'I will freeze you from within until all that remains is an icy husk!',null,null,null,null,null,null,null,null,17369,1,0,0,''),
(36597,-1810008, 'Apocalypse!',null,null,null,null,null,null,null,null,17371,1,0,0,''),
(36597,-1810009, 'Bow down before your lord and master!',null,null,null,null,null,null,null,null,17372,1,0,0,''),
(36597,-1810010, 'Hope wanes!',null,null,null,null,null,null,null,null,17363,1,0,0,''),
(36597,-1810011, 'The end has come!',null,null,null,null,null,null,null,null,17364,1,0,0,''),
(36597,-1810012, 'Face now your tragic end!',null,null,null,null,null,null,null,null,17365,1,0,0,''),
(36597,-1810013, 'No question remains unanswered. No doubts linger. You are Azeroth''s greatest champions! You overcame every challenge I laid before you. My mightiest servants have fallen before your relentless onslaught, your unbridled fury... Is it truly righteousness that drives you? I wonder.',null,null,null,null,null,null,null,null,17353,1,0,0,''),
(36597,-1810014, 'You trained them well, Fordring. You delivered the greatest fighting force this world has ever known... right into my hands -- exactly as I intended. You shall be rewarded for your unwitting sacrifice.',null,null,null,null,null,null,null,null,17355,1,0,0,''),
(36597,-1810015, 'Watch now as I raise them from the dead to become masters of the Scourge. They will shroud this world in chaos and destruction. Azeroth''s fall will come at their hands -- and you will be the first to die.',null,null,null,null,null,null,null,null,17356,1,0,0,''),
(36597,-1810016, 'I delight in the irony.',null,null,null,null,null,null,null,null,17357,1,0,0,''),
(38995,-1810017, 'LIGHT, GRANT ME ONE FINAL BLESSING. GIVE ME THE STRENGTH... TO SHATTER THESE BONDS!',null,null,null,null,null,null,null,null,17392,1,0,0,''),
(36597,-1810018, 'Impossible...',null,null,null,null,null,null,null,null,17358,1,0,0,''),
(38995,-1810020, 'No more, Arthas! No more lives will be consumed by your hatred!',null,null,null,null,null,null,null,null,17393,1,0,0,''),
(38579,-1810021, 'Free at last! It is over, my son. This is the moment of reckoning.',null,null,null,null,null,null,null,null,17397,1,0,0,''),
(38995,-1810022, 'The Lich King must fall!',null,null,null,null,null,null,null,null,17389,1,0,0,''),
(38579,-1810023, 'Rise up, champions of the Light!',null,null,null,null,null,null,null,null,17398,1,0,0,''),
(36597,-1810024, 'Now I stand, the lion before the lambs... and they do not fear.',null,null,null,null,null,null,null,null,17361,1,0,0,''),
(36597,-1810025, 'They cannot fear.',null,null,null,null,null,null,null,null,17362,1,0,0,''),
(0,-1810026, 'Argh... Frostmourne, obey me!',null,null,null,null,null,null,null,null,17367,1,0,0,''),
(36597,-1810027, 'Frostmourne hungers...',null,null,null,null,null,null,null,null,17366,1,0,0,''),
(0,-1810028, 'Frostmourne feeds on the soul of your fallen ally!',null,null,null,null,null,null,null,null,17368,1,0,0,''),
(36597,-1810029, 'Val''kyr, your master calls!',null,null,null,null,null,null,null,null,17373,1,0,0,''),
(36597,-1810030, 'Watch as the world around you collapses!',null,null,null,null,null,null,null,null,17370,1,0,0,''),
(36597,-1810031, 'You gnats actually hurt me! Perhaps I''ve toyed with you long enough, now taste the vengeance of the grave!',null,null,null,null,null,null,null,null,17359,1,0,0,''),
(36597,-1810032, 'The Lich King begins to cast Defile',null,null,null,null,null,null,null,null,0,3,0,0,'');

DELETE FROM script_texts WHERE entry <= -1810035 AND entry >= -1810037;
INSERT INTO script_texts (npc_entry,entry,content_default,content_loc1,content_loc2,content_loc3,content_loc4,content_loc5,content_loc6,content_loc7,content_loc8,sound,type,language,emote,comment)VALUES
(36823,-1810035, 'You have come to bring Arthas to justice? To see the Lich King destroyed?',null,null,null,null,null,null,null,'Вы пришли, чтобы вершить суд над Артасам, чтобы уничтожить Короля Лича?',17394,1,0,0,''),
(36823,-1810036, 'First, you must escape Frostmourne''s hold or be damned as I am, trapped within this cursed blade for all eternity.',null,null,null,null,null,null,null,'Вы не должны оказаться во власти Ледяной Скорби, иначе как и я будете на век порабощены этим проклятым клинком.',17395,1,0,0,''),
(36823,-1810037, 'Aid me in destroying these tortured souls! Together we will loosen Frostmourne''s hold and weaken the Lich King from within!',null,null,null,null,null,null,null,'Помогите мне уничтожить эти истерзанные души. Вместе мы вытянем силу из Ледяной Скорби и ослабим Короля Лича!',17396,1,0,0,'');
