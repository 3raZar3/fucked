-- NAXXRAMAS
###################   boss_anubrekhan   ########################################################
-- crypt guard (summon) based on ACID 3.0.4
DELETE FROM creature_ai_scripts WHERE creature_id = 16573;
INSERT INTO creature_ai_scripts VALUES
('1657301','16573','0','0','100','2','0','0','0','0','11','28969','4','32','0','0','0','0','0','0','0','0','Crypt Guard (Normal) - Cast Acid Spit on Aggro'),
('1657302','16573','0','0','100','4','0','0','0','0','11','56098','4','32','0','0','0','0','0','0','0','0','Crypt Guard (Heroic) - Cast Acid Spit on Aggro'),
('1657303','16573','0','0','100','3','4000','6000','4000','7000','11','28969','1','0','0','0','0','0','0','0','0','0','Crypt Guard (Normal) - Cast Acid Spit'),
('1657304','16573','0','0','100','5','4000','6000','4000','7000','11','56098','1','0','0','0','0','0','0','0','0','0','Crypt Guard (Heroic) - Cast Acid Spit'),
('1657305','16573','0','0','100','7','7000','9000','7000','9000','11','40504','1','0','0','0','0','0','0','0','0','0','Crypt Guard - Cast Cleave'),
('1657306','16573','2','0','100','7','30','0','120000','120000','11','8269','0','1','0','0','0','0','0','0','0','0','Crypt Guard - Cast Frenzy at 30% HP'),
('1657307','16573','5','0','100','7','1000','1000','0','0','11','29105','0','1','0','0','0','0','0','0','0','0','Crypt Guard - Summon Corpse Scarabs (5) at player kill'),
('1657308','16573','6','0','100','6','0','0','0','0','11','28864','6','17','0','0','0','0','0','0','0','0','Crypt Guard - Summon Corpse Scarabs (10) at death');

-- Corpse Scarab Force Despaw After Wipe (Anub'Rekhan encounter)
UPDATE creature_template SET AIName='EventAI' WHERE entry=16698;
DELETE FROM creature_ai_scripts WHERE id IN (1669801,1669802);
INSERT INTO creature_ai_scripts VALUES
(1669801,16698,1,0,100,6,30000,30000,30000,30000,41,0,0,0,0,0,0,0,0,0,0,0,'Corpse Scarab - Force Despawn');

###################   boss_faerlina   ##########################################################

###################   boss_gluth  ##############################################################

DELETE FROM script_texts WHERE entry IN (-1999781,-1999780,-1999779,-1533119);
INSERT INTO script_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-1999781, '%s deciamtes all nearby flesh',3,'Gluth - Decimated Players'),
(-1999780, '%s devours all nearby zombies',2,'Gluth - Decimated Zombie'),
(-1999779, '%s becomes enraged',3,'Gluth - Periodic Enrage'),
(-1533119, '%s spots zombie to devour!',2,'Gluth - Spoted Zombie');

UPDATE creature_template SET ScriptName = 'mob_zombie_chow' WHERE entry = 16360;

################################################################################################

/*
-- Arachnid Quarter::Worshippers and folowers
DELETE FROM `creature` WHERE `id` IN (16506);
UPDATE creature_template SET `minmana` ='58750', `maxmana` = '58750' WHERE `entry` IN (29273);
*/
