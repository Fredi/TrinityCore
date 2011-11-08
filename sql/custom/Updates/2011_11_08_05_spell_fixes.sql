-- -----------------------
-- DRUID
-- -----------------------

-- Druida Spells Fix Stack SP and coeficients.
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 WHERE `entry` IN (779,1822,60089);
DELETE FROM `spell_bonus_data` WHERE `entry` IN (1079,9007,22568);
INSERT INTO `spell_bonus_data` VALUES
(1079,0,0,-1,-1,'Druid - Rip'),
(9007,0,0,-1,-1,'Druid - Pounce Bleed'),
(22568,0,0,-1,-1,'Druid - Ferocious Bite');
-- Lifebloom final bloom fix
UPDATE `spell_bonus_data` SET `direct_bonus`=0.3857 WHERE `entry`=33778 ;
UPDATE `spell_bonus_data` SET `dot_bonus`=0.0653 WHERE `entry` IN (48450, 48451, 48628);

-- -----------------------
-- HUNTER
-- -----------------------
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 WHERE `entry` IN (3044,3674,13812,13797,1978,42243);
UPDATE `spell_bonus_data` SET `ap_dot_bonus` = 0.1 WHERE `entry` = 13812;
DELETE FROM `spell_bonus_data` WHERE `entry` IN (24131,53353,53254,53215,53216,53217,53352,53209);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) 
VALUES
(24131,0,0,-1,-1,'Hunter - Wyvern Sting (triggered)'),
(53353,0,0,-1,-1,'Hunter - Chimera Shot (Serpent)'),
(53209,0,0,-1,-1,'Hunter - Chimera Shot -  Rank 1'),
(53254 ,0,0,0,0,'Hunter - Wild Quiver Auto shot (triggered)'),
(53215,0,0,0,0,'Hunter - Wild Quiver Auto shot Rank1'),
(53216 ,0,0,0,0,'Hunter - Wild Quiver Auto shot Rank2'),
(53217,0,0,0,0,'Hunter - Wild Quiver Auto shot Rank3'),
(53352,0,0,0.14,0,'Hunter - Explosive Shot (triggered)');-- Fix Explosive Shot 

DELETE FROM `spell_ranks` WHERE `first_spell_id` = 24131;
INSERT INTO `spell_ranks` VALUES
(24131,24131,1),
(24131,24134,2),
(24131,24135,3),
(24131,27069,4),
(24131,49009,5),
(24131,49010,6);


-- -----------------------
-- ROGUE
-- -----------------------
-- Fix Rogue - Deadly Poison No stack SP.
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 WHERE `entry` IN (2818,2819,11353,11354,25349,26968,27187,57969,57970);

-- -----------------------
-- DK
-- -----------------------

-- -----------------------
-- Enchants
-- -----------------------
-- Enchants
DELETE FROM `spell_bonus_data` WHERE `entry` IN (6297, 13897, 20004, 28005, 20006, 44525); 
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(6297,0,0,0,0,'Enchant - Fiery Blaze'),
(13897,0,0,0,0,'Enchant - Fiery Weapon'),
(20004,0,0,0,0,'Enchant - Lifestealing'),
(28005,0,0,0,0,'Enchant - Battlemaster'),
(20006,0,0,0,0,'Enchant - Unholy Weapon'),
(44525,0,0,0,0,'Enchant - Icebreaker');

-- --------------------------
-- Items
-- ----------------------------
-- Trinkets - Reign of the Unliving, Reign of the Dead
DELETE FROM spell_bonus_data WHERE entry IN (67760,67714);
INSERT INTO spell_bonus_data (entry,direct_bonus,dot_bonus,ap_bonus,ap_dot_bonus,comments) VALUES
(67760,0,0,0,0, 'Item - Coliseum 25 Heroic Caster Trinket - Pillar of Flame'),
(67714,0,0,0,0, 'Item - Coliseum 25 Normal Caster Trinket - Pillar of Flame');
DELETE FROM spell_proc_event WHERE entry IN (67712,67758);
INSERT INTO spell_proc_event (entry,SchoolMask,SpellFamilyName,SpellFamilyMask0,SpellFamilyMask1,SpellFamilyMask2,procFlags,procEx,ppmRate,CustomChance,Cooldown) VALUES
(67712,0,0,0,0,0,0x00011000,0x0000002,0,0,2),
(67758,0,0,0,0,0,0x00011000,0x0000002,0,0,2);
