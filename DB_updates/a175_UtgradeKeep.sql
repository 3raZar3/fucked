-- Ingvar the Plunderer
UPDATE creature_template SET lootid = entry WHERE entry = 31673;

UPDATE creature_template SET 
`minhealth` = '240250',
`maxhealth` = '240250'
WHERE `entry` IN (23954);

UPDATE creature_template SET 
`minhealth` = '495254',
`maxhealth` = '495254'
WHERE `entry` IN (31673);

UPDATE `creature_template` SET `ScriptName` = 'shadow_axe' WHERE `entry` IN (23997);

