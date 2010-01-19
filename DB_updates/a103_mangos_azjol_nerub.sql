-- AZJOL NERUB

-- Krik Thir norm/hero
UPDATE creature_template SET `mingold` = '4691', `maxgold` = '5691', `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_krikthir', `minmana` ='46854', `maxmana` ='46854' WHERE `entry` IN (28684);
UPDATE creature_template SET `mingold` = '4691', `maxgold` = '5691', `mechanic_immune_mask` = '1073463287', `minmana` = '54960', `maxmana` = '54960' WHERE `entry` IN (31612);

-- Krik Thir mini bosy norm/hero
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_silthik' WHERE `entry` IN (28731);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_gashra' WHERE `entry` IN (28730);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_narjil' WHERE `entry` IN (28729);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31616);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31615);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31617);

-- Swarmer Infector norm/hero
UPDATE creature_template SET `minhealth` ='4000', `maxhealth` ='4000', `minlevel` = '72', `maxlevel` = '72', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '28736';
UPDATE creature_template SET `minhealth` ='6556', `maxhealth` ='6556', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '31613';

-- Swarmer norm/hero no xp at kill
UPDATE creature_template SET `flags_extra` ='64' WHERE `entry` = '28735';
UPDATE creature_template SET `minhealth` ='328', `maxhealth` ='328', `minlevel` = '80', `maxlevel` = '80', `flags_extra` ='64' WHERE `entry` = '31614';


-- Hadronox
UPDATE creature_template SET `mingold` = '4675', `maxgold` = '5675', `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_hadronox' WHERE `entry` IN (28921);
UPDATE creature_template SET `mingold` = '4675', `maxgold` = '5675', `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31611);
-- UPDATE creature SET position_x = '529.157715', position_y = '576.377502', position_z = '733.610474', orientation = '5.295866' WHERE guid = '127401';


-- Anubarak
UPDATE creature_template SET `mingold` = '4684', `maxgold` = '5684', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (29120,31610);
UPDATE creature_template SET `mingold` = '4684', `maxgold` = '5684', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (29120);

-- Trigger Invisible Mode
UPDATE `creature_template` SET `flags_extra` = '128' WHERE `entry` IN (29184);

-- Anub'ar Webspinner Shadowcaster Necromancer venomancer
UPDATE `creature_template` SET `minmana` = '7500', `maxmana` = '7500' WHERE `entry` IN (29335,28733,29098,29064,29217);
UPDATE `creature_template` SET `minmana` = '8979', `maxmana` = '8979' WHERE `entry` IN (31609,31605,31602,31601,31607);
-- Venomncer melee dmg
UPDATE `creature_template` SET `mindmg` = '270', `maxdmg` = '395', `attackpower` = '143' WHERE `entry` IN (29217);
UPDATE `creature_template` SET `mindmg` = '346', `maxdmg` = '499', `attackpower` = '287' WHERE `entry` IN (31607);
-- guardian melee dmg
UPDATE `creature_template` SET `mindmg` = '307', `maxdmg` = '438', `attackpower` = '314', `dmg_multiplier` = '7.5' WHERE `entry` IN (29216);
UPDATE `creature_template` SET `mindmg` = '422', `maxdmg` = '586', `attackpower` = '642', `dmg_multiplier` = '13' WHERE `entry` IN (31599);

-- Heroic Boss Drop
-- Drop withcout badges and quest items need to be added soon

DELETE FROM creature_loot_template WHERE entry IN (31612,31611,31610);

-- Azjol-Nerub::Kirkthir hero loot id 31612
UPDATE creature_template SET `lootid` = '31612' WHERE `entry` IN (31612);
INSERT INTO `creature_loot_template` VALUES ('31612', '43852', '1.4', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31612', '37218', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31612', '37216', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31612', '37219', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31612', '37217', '0', '1', '1', '1', '0', '0', '0');

-- Azjol-Nerub::Hadronox hero loot id 31611
UPDATE creature_template SET `lootid` = '31611' WHERE `entry` IN (31611);
INSERT INTO `creature_loot_template` VALUES ('31611', '43852', '2', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31611', '37221', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31611', '37230', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31611', '37220', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31611', '37222', '0', '1', '1', '1', '0', '0', '0');

-- Azjol-Nerub::Anubarak hero loot id 31610
UPDATE creature_template SET `lootid` = '31610' WHERE `entry` IN (31610);
INSERT INTO `creature_loot_template` VALUES ('31610', '41796', '7', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37232', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37242', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37238', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37241', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37236', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37235', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37237', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '37240', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31610', '43102', '0', '3', '1', '1', '0', '0', '0');