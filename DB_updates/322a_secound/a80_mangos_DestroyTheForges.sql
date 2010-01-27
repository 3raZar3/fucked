DELETE FROM spell_script_target WHERE entry = 56275;
INSERT INTO spell_script_target VALUES
-- North Lightning Forge
(56275,1,30209),
-- Central Lightning Forge
(56275,1,30211),
-- South Lightning Forge
(56275,1,30212);

-- North Lightning Forge
UPDATE creature SET 
`position_x` = '8023.85',
`position_y` = '-219.937',
`position_z` = '852.457',
`orientation` = '6.15281',
`spawndist` = '0',
`MovementType` = '0'
WHERE guid = 95645;

-- Central Lightning Forge
UPDATE creature SET 
`position_x` = '8021.15',
`position_y` = '-259.449',
`position_z` = '851.782',
`orientation` = '1.29259',
`spawndist` = '0',
`MovementType` = '0'
WHERE guid = 96491;

-- South Lightning Forge
UPDATE creature SET 
`position_x` = '8009.26',
`position_y` = '-309.909',
`position_z` = '852.585',
`orientation` = '5.4316',
`spawndist` = '0',
`MovementType` = '0'
WHERE guid = 96864;

