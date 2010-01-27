-- Koordy Jedogi sumonow do poprawy nie raz ich nie widac
-- Grzyby dispaly i spele do zrobienia


-- AHN KAHET

-- Nadox Taldaram Jedoga Volazi Amanitar
-- 29309,29308,29310,29311,30258
-- 31469,31456,31465,31464,31463


-- Ahn-Kahet::Nadox 29309 31456
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_nadox' WHERE `entry` IN (29309);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31456);
-- Ahn-Kahet::Swarmer
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '250', `maxdmg` = '500', `baseattacktime` = '2000', `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (30178);
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '500', `maxdmg` = '1000', `baseattacktime` = '2000', `minhealth` = '250', `maxhealth` = '250' WHERE `entry` IN (31448);
-- Ahn-Kahet::Guardian
UPDATE creature_template SET `armor` = '6000', `mindmg` = '1000', `maxdmg` = '2000', `baseattacktime` = '2000' WHERE `entry` IN (30176);
UPDATE creature_template SET `armor` = '6000', `mindmg` = '2000', `maxdmg` = '4000', `baseattacktime` = '2000' WHERE `entry` IN (31441);


-- Ahn-Kahet::Taladram
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_taldaram', `minmana` ='71220', `maxmana` ='71220' WHERE `entry` IN (29308);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minmana` = '83380', `maxmana` = '83380' WHERE `entry` IN (31469);
DELETE FROM creature WHERE id = '29308';
INSERT INTO creature VALUES (NULL,29308,619,3,1,0,0,529.114,-848.099,11.3082,1.42479,86400,0,0,458354,0,0,0);
-- Flame Sphere
UPDATE creature_template SET `minlevel` ='80', `maxlevel` = '80', `AIName` = '', `Scriptname` = 'mob_flame_sphere', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (30702);
-- DELETE FROM creature_ai_scripts WHERE creature_id IN (30702);
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '3', '500', '500','3000','3000', '11', '57748', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Normal)');
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '5', '500', '500','3000','3000', '11', '58938', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Heroic)');


-- Ahn-Kahet::Jedoga
DELETE FROM creature WHERE id = '29310';
INSERT INTO creature VALUES (NULL,29310,619,3,1,0,0,371.352,-702.825,-16.1797,2.47565,86400,0,0,431392,0,0,0);

UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = 'boss_jedoga' WHERE `entry` IN (29310);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31465);
-- Volounteer
UPDATE creature_template SET `AIName` = '', `type_flags` = '0', `unit_flags` = '0', `Scriptname` = 'mob_volounteer' WHERE `entry` IN (30385);
UPDATE creature_template SET `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31474);


-- Ahn-Kahet::Amanitar NOT COMPLETE YET
DELETE FROM creature WHERE id = '30258';
-- INSERT INTO creature VALUES (NULL,30258,619,2,1,0,0,345.169,-869.813,-77.6156,6.03587,86400,0,0,431392,0,0,0);
UPDATE creature_template SET `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_amanitar' WHERE `entry` IN (30258);
UPDATE creature_template SET `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287'  WHERE `entry` IN (31463);
-- Ahn-Kahet::Mushrooms
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_healthymushroom' WHERE `entry` IN (30435);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_poisonmushroom' WHERE `entry` IN (30391);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (31461,31462);


-- Ahn-Kahet::Volazj2931131464
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_volazj' WHERE `entry` IN (29311);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31464);
-- Ahn-Kahet::twisted Visage 30625
UPDATE creature_template SET `mindmg` = '500', `maxdmg` = '1000', `baseattacktime` = '2000', `minhealth` = '8000', `maxhealth` = '8000' WHERE `entry` IN (30625);
-- Insert heroic creature?


-- CREATURE_LOOT_TEMPLATE HEROIC

-- Ahn-Kahet::Heroic Boss LOOT
DELETE FROM creature_loot_template WHERE entry IN (31469,31456,31465,31464,31463);

-- Ahn-Kahet::Nadox
UPDATE creature_template SET `lootid` = '31469' WHERE `entry` IN (31469);
INSERT INTO `creature_loot_template` VALUES ('31469', '37592', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31469', '37594', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31469', '37591', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31469', '37593', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31469', '43852', '1.8', '0', '1', '1', '0', '0', '0');

-- Ahn-Kahet::Taladram
UPDATE creature_template SET `lootid` = '31456' WHERE `entry` IN (31456);
INSERT INTO `creature_loot_template` VALUES ('31456', '37612', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31456', '37613', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31456', '37614', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31456', '37595', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31456', '43852', '3', '0', '1', '1', '0', '0', '0');

-- Ahn-Kahet::Jedoga
UPDATE creature_template SET `lootid` = '31465' WHERE `entry` IN (31465);
INSERT INTO `creature_loot_template` VALUES ('31465', '43282', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31465', '43281', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31465', '43280', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31465', '43283', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31465', '43852', '3', '0', '1', '1', '0', '0', '0');

-- Ahn-Kahet::Amanitar
UPDATE creature_template SET `lootid` = '31463' WHERE `entry` IN (31463);
INSERT INTO `creature_loot_template` VALUES ('31463', '43284', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31463', '43285', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31463', '43286', '23', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31463', '43287', '22', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31463', '43852', '3', '0', '1', '1', '0', '0', '0');

-- Ahn-Kahet::Volazj
UPDATE creature_template SET `lootid` = '31464' WHERE `entry` IN (31464);
INSERT INTO `creature_loot_template` VALUES ('31464', '43102', '100', '3', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37620', '20', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37618', '20', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37616', '20', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37617', '20', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37623', '19', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37622', '19', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37619', '19', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '37615', '19', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31464', '41790', '15', '0', '1', '1', '0', '0', '0');