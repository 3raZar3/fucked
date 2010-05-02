-- Quest :: A Change of Scenery - 12921
-- wrong factions for alliance nad horde
UPDATE `creature_template` SET `faction_A` = '35',
`faction_H` = '35' WHERE `entry` = 29975 LIMIT 1 ;
