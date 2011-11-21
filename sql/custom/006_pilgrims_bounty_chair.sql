UPDATE `creature_template` SET `VehicleId` = '321' WHERE `entry` IN (34823,34812,34824,34822,34819); -- Temp Fix (not blizz)

DELETE FROM `npc_spellclick_spells` WHERE `spell_id`=46598 AND `npc_entry` IN (34823,34812,34824,34822,34819);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`, `aura_required`, `aura_forbidden`, `user_type`) VALUES
('34823', '46598', '0', '0', '0', '1', '0', '0', '0'),
('34812', '46598', '0', '0', '0', '1', '0', '0', '0'),
('34824', '46598', '0', '0', '0', '1', '0', '0', '0'),
('34822', '46598', '0', '0', '0', '1', '0', '0', '0'),
('34819', '46598', '0', '0', '0', '1', '0', '0', '0');