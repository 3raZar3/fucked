-- UDB development part
-- Vault Warder
UPDATE creature_template SET 
unit_flags = unit_flags |2|33554432,
faction_A = 416,
faction_H = 416,
speed = 0.4
WHERE entry IN (4857,10120);

-- Earthen Custodian
-- Earthen Guardian
-- Earthen HallShaper
-- Archedas
UPDATE creature_template SET 
unit_flags = unit_flags |2|33554432,
faction_A = 416,
faction_H = 416
WHERE entry IN (7309,7076,7077);

-- Archaedas
UPDATE creature_template SET 
unit_flags = unit_flags |2|33554432,
faction_A = 416,
faction_H = 416
WHERE entry = 2748;

REPLACE INTO creature_addon VALUES
(33537,0,0,4097,0,0,'10255 0');

DELETE FROM spell_script_target WHERE entry = 10259;
INSERT INTO spell_script_target VALUES 
(10259,1,7309),
(10259,1,7077);
