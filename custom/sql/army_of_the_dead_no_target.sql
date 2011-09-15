-- Army of the Dead Ghoul
SET @ENTRY := 24207;
SET @SPELL1 := 7398; -- Birth
SET @SPELL2 := 43264; -- Periodic Taunt
SET @SPELL3 := 47468; -- Claw ~5 sec cd
SET @SPELL4 := 47482; -- Leap 30 sec spell cooldown
UPDATE `creature_template` SET `faction_A`=35,`faction_H`=35,`dynamicflags`=0,`mindmg`=198,`maxdmg`=273,`attackpower`=587,`AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,0,0,0,0,11,@SPELL1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Army of the Dead Ghoul - On spawn - Cast Birth on self'), -- This is the visual effect for ghouls coming up from the ground
(@ENTRY,0,1,0,1,0,100,1,0,0,0,0,11,@SPELL2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Army of the Dead Ghoul - On spawn - Cast Periodic Taunt on self'),
(@ENTRY,0,2,0,0,0,100,0,2000,2000,30000,30000,11,@SPELL4,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Army of the Dead Ghoul - Combat - Cast Leap'),
(@ENTRY,0,3,0,0,0,100,0,1000,1000,4000,5000,11,@SPELL3,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Army of the Dead Ghoul - Combat - Cast Claw');