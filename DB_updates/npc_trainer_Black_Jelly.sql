-- Black Jelly
DELETE FROM `npc_trainer` WHERE spell = 64358;
INSERT INTO `npc_trainer` (`entry`,`spell`,`spellcost`,`reqskill`,`reqskillvalue`,`reqlevel`) VALUES
(29631,64358,5000,185,400,0),
(26953,64358,5000,185,400,0),
(26905,64358,5000,185,400,0),
(28705,64358,5000,185,400,0),
(26972,64358,5000,185,400,0),
(26989,64358,5000,185,400,0),
(33587,64358,5000,185,400,0);
