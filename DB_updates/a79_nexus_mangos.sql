-- Telestra after morph
UPDATE creature_template SET modelid_A = 11686, modelid_H = 11686 WHERE entry = 20213;

-- Telestra adds death spells (confirming her that they already died)
INSERT IGNORE INTO spell_script_target VALUES (47711,1,26731);
INSERT IGNORE INTO spell_script_target VALUES (47712,1,26731);
INSERT IGNORE INTO spell_script_target VALUES (47713,1,26731);

-- Summon adds spell target position
DELETE FROM spell_scripts WHERE id=47710;
INSERT INTO spell_scripts (id, delay, command, datalong, datalong2, dataint, X, Y, z, o) VALUES 
(47710, 0, 15, 47707, 1, 0, 0, 0, 0, 0),
(47710, 1, 15, 47708, 1, 0, 0, 0, 0, 0),
(47710, 2, 15, 47709, 1, 0, 0, 0, 0, 0);

-- cast adds death spell
DELETE FROM creature_ai_scripts WHERE id IN (2692805,2692903,2693005);
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT) VALUES
(2692805, 26928, 6, 0, 100, 6, 0, 0, 0, 0, 11, 47711, 6, 18, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Magus Telestra (fire) - Cast death spell'),
(2692903, 26929, 6, 0, 100, 6, 0, 0, 0, 0, 11, 47713, 6, 18, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Magus Telestra (arcane)- Cast death spell'),
(2693005, 26930, 6, 0, 100, 6, 0, 0, 0, 0, 11, 47712, 6, 18, 0, 0, 0, 0, 0, 0, 0, 0, 'Grand Magus Telestra (frost) - Cast death spell');
