-- Fix Strength of Earth Totem & Horn of Winter stack
-- By Liberate
DELETE FROM `spell_group` WHERE `id`=1111;
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(1111,57330),
(1111,58680),
(1111,8075);

DELETE FROM `spell_group_stack_rules` WHERE `group_id`=1111;
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(1111,3);

-- Fix Stacks  Earth and Moon & Ebon Plague & Curse of Elements
-- By Retriman
DELETE FROM `spell_group` WHERE `id` = 1114;
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(1114,1490),
(1114,60431),
(1114,60432),
(1114,60433),
(1114,51726),
(1114,51734),
(1114,51735);

DELETE FROM `spell_group_stack_rules` WHERE `group_id` = 1114;
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(1114,1);
