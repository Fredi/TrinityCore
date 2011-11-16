DROP TABLE IF EXISTS `creature_guild`;
CREATE TABLE `creature_guild` (
`guid` INT(10) UNSIGNED NOT NULL ,
`guild` INT(10) UNSIGNED NOT NULL ,
PRIMARY KEY (`guid`)
);

DROP TABLE IF EXISTS `guild_house`;
CREATE TABLE `guild_house` (
`guild` INT(10) UNSIGNED NOT NULL ,
`mapId` SMALLINT(5) UNSIGNED NOT NULL ,
`zoneId` SMALLINT(5) UNSIGNED NOT NULL ,
`posX` FLOAT NOT NULL ,
`posY` FLOAT NOT NULL ,
`posZ` FLOAT NOT NULL ,
`gm` VARCHAR(12) NOT NULL ,
`date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
PRIMARY KEY (`guild`)
);

DELETE FROM `creature_template` WHERE `entry` = 999130;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('999130','0','0','0','0','0','1126','11686','0','0','Guild House Watcher',NULL,NULL,'0','82','82','0','14','14','0','1','1.14286','1','0','104','138','0','252','1','2000','0','1','33554688','0','0','0','0','0','0','72','106','26','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1.35','1','1','0','0','0','0','0','0','0','0','1','0','0','2','npc_guild_house','12340');
