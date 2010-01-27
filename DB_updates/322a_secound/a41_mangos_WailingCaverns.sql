DELETE FROM creature_ai_scripts WHERE creature_id IN (3673,3670,3669,3671) AND action1_type = 34;
INSERT INTO creature_ai_scripts (`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('3673', '6','0','100','2', '0','0','0','0', '34','3','3','0', '0','0','0','0', '0','0','0','0', 'Lord Serpentis - Encounter Done'),
('3670', '6','0','100','2', '0','0','0','0', '34','2','3','0', '0','0','0','0', '0','0','0','0', 'Lord Pythas - Encounter Done'),
('3669', '6','0','100','2', '0','0','0','0', '34','1','3','0', '0','0','0','0', '0','0','0','0', 'Lord Cobrahn - Encounter Done'),
('3671', '6','0','100','2', '0','0','0','0', '34','0','3','0', '0','0','0','0', '0','0','0','0', 'Lord Anacondra - Encounter Done');
