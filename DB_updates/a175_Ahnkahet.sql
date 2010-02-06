-- Koordy Jedogi sumonow do poprawy nie raz ich nie widac
-- Grzyby dispaly i spele do zrobienia


-- AHN KAHET

-- Nadox Taldaram Jedoga Volazi Amanitar
-- 29309,29308,29310,29311,30258
-- 31469,31456,31465,31464,31463


-- Ahn-Kahet::Nadox 29309 31456
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (29309,31456);
-- Ahn-Kahet::Swarmer
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '125', `maxdmg` = '250', dmg_multiplier = 2, `baseattacktime` = '2000', `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (30178);
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '250', `maxdmg` = '500', dmg_multiplier = 2, `baseattacktime` = '2000', `minhealth` = '250', `maxhealth` = '250' WHERE `entry` IN (31448);

-- Flame Sphere
UPDATE creature_template SET `minlevel` ='80', `maxlevel` = '80', `AIName` = '', `Scriptname` = 'mob_flame_sphere', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (30702);
-- DELETE FROM creature_ai_scripts WHERE creature_id IN (30702);
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '3', '500', '500','3000','3000', '11', '57748', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Normal)');
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '5', '500', '500','3000','3000', '11', '58938', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Heroic)');

-- boss_jedoga
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287, `unit_flags` = '0' WHERE `entry` IN (29310,31465);

-- Volounteer
UPDATE creature_template SET `unit_flags` = '0', `Scriptname` = 'mob_volounteer' WHERE `entry` IN (30385);
UPDATE creature_template SET `unit_flags` = '0' WHERE `entry` IN (31474);


-- Ahn-Kahet::Amanitar NOT COMPLETE YET
DELETE FROM creature WHERE id = '30258';
-- INSERT INTO creature VALUES (NULL,30258,619,2,1,0,0,345.169,-869.813,-77.6156,6.03587,86400,0,0,431392,0,0,0);

UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287, `AIName` = '', `Scriptname` = 'boss_amanitar' WHERE `entry` IN (30258);
UPDATE creature_template SET `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = mechanic_immune_mask|1073463287  WHERE `entry` IN (31463);
-- Ahn-Kahet::Mushrooms
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_healthymushroom' WHERE `entry` IN (30435);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_poisonmushroom' WHERE `entry` IN (30391);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (31461,31462);


-- Ahn-Kahet::Volazj2931131464
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (29311,31464);

-- Ahn-Kahet::twisted Visage 30625
UPDATE creature_template SET `mindmg` = '500', `maxdmg` = '1000', `baseattacktime` = '2000', `minhealth` = '8000', `maxhealth` = '8000' WHERE `entry` IN (30625);
-- Insert heroic creature?