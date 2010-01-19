-- Big Roy
UPDATE creature_template SET
InhabitType = 2,
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 3,
minlevel = 71,
maxlevel = 71,
faction_A = 16,
faction_H = 16,
minhealth = 9200,
maxhealth = 9300
WHERE entry = 24785;

-- Abdul The Insane
UPDATE creature_template SET
-- faction Vrykul 
faction_A = 1885,
faction_H = 1885,
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 3,
-- fear/horror/sap/blind
mechanic_immune_mask = mechanic_immune_mask |16 |8388608 |536870912 |67108864
WHERE entry = 24900;
