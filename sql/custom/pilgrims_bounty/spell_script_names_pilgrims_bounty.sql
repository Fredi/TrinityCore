-- Achievement: The Turkinator
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_turkey_tracker';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62014, 'spell_gen_turkey_tracker');

-- Feast On Spells
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_feast_on';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(61784, 'spell_gen_feast_on'), -- Feast On Turkey
(61785, 'spell_gen_feast_on'), -- Feast On Cranberries
(61786, 'spell_gen_feast_on'), -- Feast On Sweet Potatoes
(61787, 'spell_gen_feast_on'), -- Feast On Pie
(61788, 'spell_gen_feast_on'); -- Feast On Stuffing
