-- Heroic Training Dummy (31146) 

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=31146;

-- No movement and attack
DELETE FROM creature_ai_scripts WHERE id=3114601;
INSERT INTO creature_ai_scripts VALUES
(3114601,31146,4,0,100,0,0,0,0,0,21,0,0,0,20,0,0,0,0,0,0,0,'Heroic Training Dummy - No movement and attack');
