###################################### boss_telestra ######################################################
DELETE FROM creature_ai_scripts WHERE id IN (2692806,2692904,2693006);
INSERT INTO creature_ai_scripts VALUES
(2692806,26928,1,0,100,6,10000,10000,0,0, 41,0,0,0, 0,0,0,0, 0,0,0,0,'Grand Magus Telestra OOC despawn'),
(2692904,26929,1,0,100,6,10000,10000,0,0, 41,0,0,0, 0,0,0,0, 0,0,0,0,'Grand Magus Telestra OOC despawn'),
(2693006,26930,1,0,100,6,10000,10000,0,0, 41,0,0,0, 0,0,0,0, 0,0,0,0,'Grand Magus Telestra OOC despawn'),


/*
-- clearly wrong !! (Guen)
-- IDs Nexus mobs Faction 14
-- 26918,28231,26716,26722,26723,26727,26728,26729,26730,26731,26734,26735,26736,26737,26746,26761,26763,26782,26792,26792,26793,26794,26800,26802,26805,27949,30397,30398
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14' WHERE entry IN (26918,28231,26716,26722,26723,26727,26728,26729,26730,26731,26734,26735,26736,26737,26746,26761,26763,26782,26792,26792,26793,26794,26800,26802,26805,27949,30397,30398);

UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_telestra' WHERE `entry` = 26731;

UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_anomalus' WHERE `entry` = 26763;
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_chaotic_rift' WHERE `entry` = 26918;

UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_ormorok' WHERE `entry` = 26794;
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_crystal_spike' WHERE `entry` = 27099;
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_crystalline_tangler' WHERE `entry` = 32665;

UPDATE creature_template SET `dynamicflags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = 'boss_keristrasza' WHERE `entry` = 26723;
UPDATE creature_template SET `dynamicflags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = '' WHERE `entry` = 30540;

-- Kolurg 26798
-- UPDATE creature_template SET `heroic_entry` = '30397', `AIName` = '', `Scriptname` = 'boss_commander_kolurg' WHERE `entry` = 26798;

-- Stoutbeard 26796
-- UPDATE creature_template SET `heroic_entry` = '30398', `AIName` = '', `Scriptname` = 'boss_commander_stoutbeard' WHERE `entry` = 26796;
*/
