-- Dual Spec - fixed typos
UPDATE gossip_menu_option SET option_id= 1, action_script_id=6 WHERE menu_id=0 AND id=16;

-- Dual Talent Specialization Achievement 
DELETE FROM achievement_criteria_requirement WHERE criteria_id=9619;
INSERT INTO achievement_criteria_requirement VALUES 
(9619,0,63624,0);
