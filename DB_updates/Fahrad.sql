
UPDATE creature_template SET 
npcflag = npcflag|2|16, 
trainer_class=4,
trainer_type=0,
faction_A=471,
faction_H=471 
WHERE entry = 6707;
DELETE FROM creature_questrelation WHERE quest=8249;
INSERT INTO creature_questrelation (id,quest) VALUES
(6707,8249);