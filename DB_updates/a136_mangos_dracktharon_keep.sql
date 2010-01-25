-- Crystal Channel Target
UPDATE creature_template SET 
InhabitType = 4,
scale = 0.1,
flags_extra = 2,
faction_A = 35,
faction_H = 35,
unit_flags = unit_flags|2|33554432
WHERE entry = 26712;

-- Novos Summon Target
UPDATE creature_template SET 
InhabitType = 4,
scale = 0.1,
flags_extra = 130,
faction_A = 35,
faction_H = 35,
unit_flags = unit_flags|2|33554432
WHERE entry = 27583;

--  Crystal Handler
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '21700',
`maxhealth` = '22000',
`minmana` = '7800',
`maxmana` = '8100',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '450',
`maxdmg` = '600',
`AIName` = 'EventAI',
`dmg_multiplier` = '2' WHERE `entry` =26627;

-- Risen Shadowcaster
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '1645',
`maxhealth` = '1645',
`minmana` = '7800',
`maxmana` = '7800',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '450',
`maxdmg` = '600',
`AIName` = 'EventAI',
`dmg_multiplier` = '2' WHERE `entry` =27600;

-- Fetid Troll Corpse
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '2050',
`maxhealth` = '2100',
`minmana` = '0',
`maxmana` = '0',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2' WHERE `entry` =27598;

-- Hulking Corpse
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '12500',
`maxhealth` = '13000',
`minmana` = '0',
`maxmana` = '0',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2' WHERE `entry` =27597;

-- Delete all Crystal Target creature addon befor replacing triggers
DELETE FROM creature_addon WHERE guid IN (SELECT guid FROM creature WHERE id = 26712);

DELETE FROM creature WHERE id IN (26712,27583);
INSERT INTO creature VALUES
-- Crystal Channel Target
('127498','26712','600','3','1','15468','0','-392.416','-724.865','33','3.14159','86400','0','0','4050','0','0','0'),
('127499','26712','600','3','1','15468','0','-365.279','-751.087','33','3.14159','86400','0','0','4050','0','0','0'),
('127500','26712','600','3','1','15468','0','-365.410','-724.865','33','3.14159','86400','0','0','4050','0','0','0'),
('127501','26712','600','3','1','15468','0','-392.286','-751.087','33','3.14159','86400','0','0','4050','0','0','0'),
-- Novos Summon Target
('127502','27583','600','1','1','0','0','-379.329','-813.393','62.2485','0','86400','2','0','1','0','0','1');

-- Delete crystals from crystal handler loot_template. Since 3.0.3 they are not neccessary
DELETE FROM creature_loot_template WHERE item = 38555;

-- Crystals
UPDATE gameobject SET animprogress = 100 WHERE id IN (189299,189300,189301,189302);

/* Boss damage */
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26630;
-- Novos The Summoner
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26631;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 27483;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26632;

UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (26627,27600);
DELETE FROM `creature_ai_scripts` WHERE creature_id IN (26627,27600);
INSERT INTO `creature_ai_scripts` VALUES
-- Crystal Handler 
(2662701,26627, 0,0,100,7, 5000,10000,5000,10000, 11,49668,1,0, 0,0,0,0, 0,0,0,0, 'Crystal Handler - Flash of Darkness'),
(2662702,26627, 6,0,100,6, 0,0,0,0, 34,9,4,0, 0,0,0,0, 0,0,0,0, 'Crystal Handler - Update Crystal Event at death'),

-- Risen Shadowcaster
(2760001,27600, 1,0,100,6, 2000,2000,0,0, 21,0,0,0, 22,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(2760002,27600, 4,0,100,2, 2000,2000,0,0, 11,51363,1,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster (Normal) - Cast Fireball and Set Phase 1 on Aggro'),
(2760003,27600, 9,5,100,3, 0,40,5400,6800, 11,51363,1,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster (Normal) - Cast Fireball (Phase 1)'),
(2760004,27600, 4,0,100,4, 2000,2000,0,0, 11,59016,1,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster (Heroic) - Cast Fireball and Set Phase 1 on Aggro'),
(2760005,27600, 9,5,100,5, 0,40,5400,6800, 11,59016,1,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster (Heroic) - Cast Fireball (Phase 1)'),
(2760006,27600, 3,5,100,6, 15,0,0,0, 21,1,0,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement and Set Phase 2 when Mana is at 15% (Phase 1)'),
(2760007,27600, 9,5,100,6, 35,80,0,0, 21,1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement at 35 Yards (Phase 1)'),
(2760008,27600, 9,5,100,6, 5,15,0,0, 21,0,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Prevent Combat Movement at 15 Yards (Phase 1)'),
(2760009,27600, 9,5,100,6, 0,5,0,0, 21,1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement Below 5 Yards'),
(2760010,27600, 3,3,100,7, 100,15,100,100, 23,-1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Set Phase 1 when Mana is above 15% (Phase 2)'),
(2760011,27600, 7,0,100,6, 0,0,0,0, 22,0,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Set Phase to 0 on Evade');

-- Beam channel
-- ATTENTION: HACK COMMING! - this should work in reverse mode (from Novos to crystal targets) 
-- but in case that core does not support multiple SCRIPT_TARGET targets should i could'nt find any other way
DELETE FROM spell_script_target WHERE entry = 52106;
INSERT INTO spell_script_target VALUES
(52106,1,26631);
