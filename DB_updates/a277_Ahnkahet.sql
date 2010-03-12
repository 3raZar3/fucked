-- AHN KAHET
######################  Elder Nadox   ##################################################################

-- Ahn-Kahet::Nadox 29309 31456
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (29309,31456);
-- limit XP gained on Elder Nadox Adds
UPDATE creature_template SET flags_extra = flags_extra | 2048 WHERE entry IN (30176,30178,31441,31448);

-- Ahn'kahar Swarmer (H)
UPDATE creature_template SET
minlevel = 80,
maxlevel = 82 WHERE entry = 31448;

######################  Prince Taldaram ################################################################
-- Flame Sphere
UPDATE creature_template SET 
`minlevel` = 80, 
`maxlevel` = 80,
`AIName` = '',
`Scriptname` = 'mob_flame_sphere',
WHERE `entry` IN (30106,31686,31687);

-- Taldaram - delete blue beam aura
DELETE FROM creature_addon WHERE guid IN (SELECT guid FROM creature WHERE id IN (29308,31469));


#####################   Jedoga Shadowseeker   ##########################################################
-- Jedoga Controller, Jedoga, Volunteer, Initiate
DELETE FROM creature WHERE id IN (30181,30385,29310,30114);
INSERT INTO creature VALUES
-- Jedoga Shadowseeker
('131953','29310','619','3','1','26777','0','373.54','-704.44','-1.7','5.61646','86400','0','0','212700','0','0','0'),
-- Jedoga Contoller
('132064','30181','619','3','1','11686','0','376.743','-707.103','-16.1797','5.58952','3600','0','0','10282','0','0','0');
DELETE FROM creature_addon WHERE guid = 131953;

-- Volunteer
UPDATE creature_template SET 
flags_extra = flags_extra | 2,
equipment_id = 93
WHERE entry IN (30385,31474);

-- Jedoga Controller
UPDATE creature_template SET
unit_flags = unit_flags |2|33554432,
faction_A = 35,
faction_H = 35
WHERE entry = 30181;

-- Sacrifice Beam
DELETE FROM spell_script_target WHERE entry IN (56312,56150,56219);
INSERT INTO spell_script_target VALUES
(56150, 1, 30385),
(56150, 1, 31474);

UPDATE creature_template SET
ScriptName = 'mob_jedoga_add'
WHERE entry IN (30385,30114);

/*
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
-- Insert heroic creature? */
