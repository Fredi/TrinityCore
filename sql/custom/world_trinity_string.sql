DELETE FROM `trinity_string` WHERE entry IN (11002, 11003, 11004);
INSERT INTO `trinity_string` (`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`) VALUES
(11002, '|cFFFFFC00[ANTICHEAT]|cFF00FFFF[|cFF60FF00%s|cFF00FFFF] Banned for cheating!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11003, '|cffffff00[|cffff0000%s|cffffff00]:|r %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11004, '|cFFFFFC00[LFG]|cffffff00[|cffff0000%s|cffffff00]:|r %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
