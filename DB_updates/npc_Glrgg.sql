DELETE FROM creature WHERE id IN (25203);
INSERT INTO creature VALUES
-- Glrggl
('9000006','25203','571','1','1','0','0','4569.34','6325.88','-47.3439','4.84171','300','20','0','9291','0','0','1');

-- Glrggl
UPDATE creature_template SET
InhabitType = 2,
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 3,
minlevel = 66,
maxlevel = 71,
faction_A = 16,
faction_H = 16,
minhealth = 9200,
maxhealth = 9300
WHERE entry = 25203;
