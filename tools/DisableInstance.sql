UPDATE areatrigger_teleport SET
required_quest_done = 30000,
required_quest_done_heroic = 30000,
required_failed_text = 'Ta instancja jest w tej chwili niedostepna na Andeerii'
WHERE target_map IN (
574, -- Utgarde Keep
575, -- Utgarde Pinnacle
576, -- The Nexus
578, -- The Oculus 
599, -- Halls of Stone
600, -- Drak\'Tharon Keep
601, -- Azjol-Nerub 
602, -- Halls of Lightning 
603, -- Ulduar 
604, -- Gundrak 
608, -- Violet Hold 
609, -- Ebon Hold 
615, -- The Obsidian Sanctum 
616, -- The Eye of Eternity 
624, -- Vault of Archavon 
631, -- Icecrown Citadel Raid
632, -- Forge of Souls
619, -- Ahn'Kahet
595, -- Culling Stratholme
533); -- Naxxramas  

DELETE FROM quest_template WHERE entry = 30000;
INSERT INTO quest_template VALUES('30000','0','-22','0','1','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','3','0','0','0','Disable Map Quest','','',NULL,NULL,'',NULL,'','','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','37586','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','11100','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');
