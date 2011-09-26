DELETE FROM `creature_template` WHERE `entry` IN (99020, 99024, 99025);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(99025, 0, 0, 0, 0, 0, 159, 0, 0, 0, 'Teleport', '', '', 0, 82, 82, 0, 35, 35, 1, 1, 1, 1.3, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 8, 0, 0, 0, 0, 0, 1, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_teleport', 12340),
(99024, 0, 0, 0, 0, 0, 159, 0, 0, 0, 'Teleport', '', '', 0, 81, 81, 0, 35, 35, 1, 1, 1, 1.3, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 8, 0, 0, 0, 0, 0, 1, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_teleport', 12340),
(99020, 0, 0, 0, 0, 0, 159, 0, 0, 0, 'Teleport', '', '', 0, 80, 80, 0, 35, 35, 1, 1, 1, 1.3, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 0, 8, 0, 0, 0, 0, 0, 1, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_teleport', 12340);

DELETE FROM `creature` WHERE `id` IN (99020, 99024, 99025);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(NULL, 99020, 0, 1, 1, 0, 0, -13234.1, 217.387, 31.6759, 1.06815, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99020, 0, 1, 1, 0, 0, -7823.8, -477.402, 170.556, 3.03197, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99020, 1, 1, 1, 0, 0, 16222.1, 16252.1, 12.5827, 0.79456, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99020, 571, 1, 1, 0, 0, 5811.79, 453.284, 658.755, 1.29914, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99020, 530, 1, 1, 0, 0, 13000.2, -6907.51, 9.58386, 2.56669, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99020, 530, 1, 1, 0, 0, -1875.89, 5412.71, -12.4277, 3.80094, 300, 0, 0, 26710, 0, 0, 0, 0, 0),
(NULL, 99024, 0, 1, 1, 0, 0, 1568.48, 268.52, -43.1027, 4.82308, 300, 0, 0, 27460, 0, 0, 0, 0, 0),
(NULL, 99024, 530, 1, 1, 0, 0, 9376.68, -7167.33, 9.04634, 2.53396, 300, 0, 0, 27460, 0, 0, 0, 0, 0),
(NULL, 99024, 1, 1, 1, 0, 0, -1193.87, 27.42, 176.949, 2.90063, 300, 0, 0, 27460, 0, 0, 0, 0, 0),
(NULL, 99024, 1, 1, 1, 0, 0, 1679.42, -4314.8, 61.4043, 4.38265, 300, 0, 0, 27460, 0, 0, 0, 0, 0),
(NULL, 99024, 37, 1, 1, 0, 0, -28.6567, 971.069, 347.305, 5.79912, 300, 0, 0, 27460, 0, 0, 0, 0, 0),
(NULL, 99025, 37, 1, 1, 0, 0, 1094.2, 298.032, 338.616, 3.21441, 300, 0, 0, 28235, 0, 0, 0, 0, 0),
(NULL, 99025, 530, 1, 1, 0, 0, -4057.07, -11788.3, 8.87848, 5.12786, 300, 0, 0, 28235, 0, 0, 0, 0, 0),
(NULL, 99025, 1, 1, 1, 0, 0, 9950.95, 2605.76, 1316.19, 3.58211, 300, 0, 0, 28235, 0, 0, 0, 0, 0),
(NULL, 99025, 0, 1, 1, 0, 0, -4819.68, -1153.63, 502.212, 4.0249, 300, 0, 0, 28235, 0, 0, 0, 0, 0),
(NULL, 99025, 0, 1, 1, 0, 0, -8908.96, 556.3, 93.5345, 0.73, 300, 0, 0, 28235, 0, 0, 0, 0, 0);
