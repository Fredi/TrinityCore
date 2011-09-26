SET @GOSSIP_MENU = 61001;
SET @NPC_TEXT_ID = 537006;

DELETE FROM `creature_template` WHERE `entry` = 97015;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(97015, 0, 0, 0, 0, 0, 30859, 30987, 30861, 30862, 'Recuperar Anel de Ashen Veredict', '', '', 0, 80, 80, 2, 35, 35, 1, 1, 1.14286, 1, 1, 422, 586, 0, 642, 7.5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 345, 509, 103, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 75, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2354, 0, 2, 'npc_icc_ring_recover', 12340);

UPDATE `creature_template` SET `npcflag` = 1, `gossip_menu_id` = @GOSSIP_MENU WHERE `entry` = 97015;
DELETE FROM `gossip_menu` WHERE `entry` = @GOSSIP_MENU;
INSERT INTO `gossip_menu` VALUES (@GOSSIP_MENU, @NPC_TEXT_ID);
DELETE FROM `npc_text` WHERE id = @NPC_TEXT_ID;
INSERT INTO `npc_text` (`id`, `text0_0`) VALUES (@NPC_TEXT_ID, 'Perdeu seu anel que obteve por reputacao em Ashen Veredict?$B$BAqui podera obte-lo novamente de acordo com sua reputacao atual.$B$BSe depois de recupera-lo voce aumentar sua reputacao e nao puder pegar a nova quest, delete seu anel e fale comigo novamente.');
