-- HALLS OF LIGHTING

-- HallsOfLighting::Bengram
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (31533,28586);

-- HallsOfLighting::Volkano
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (31536,28587);

-- HallsOfLighting::Ionar
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (31537,28546);

-- HallsOfLighting::Spark movement speed
UPDATE creature_template SET `speed` = '0.8' WHERE `entry` IN (28926,31867);

-- HallsOfLighting::Loken
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (31538,28923);

-- HallsOfLighting::Thunderer and Siegebreaker flags remove
UPDATE `creature_template` SET `unit_flags` = '0',`type_flags` = '0' WHERE `entry` IN (28965,28961,30980,30982);