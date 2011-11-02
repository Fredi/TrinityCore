-- [Q] [A/H] Zuluhed the Whacked
-- Added additions to C++ for Karynaku so it'll summon on quest accept
SET @QUEST := 10866;
UPDATE `quest_template` SET `StartScript`=0,`CompleteScript`=0 WHERE `entry`=@QUEST;
DELETE FROM `quest_start_scripts` WHERE `id`=@QUEST;
