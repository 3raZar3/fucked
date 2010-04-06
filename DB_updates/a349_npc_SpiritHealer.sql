-- Spirit healer prevent against death
-- unit_flags 4928
UPDATE creature_template SET unit_flags=unit_flags|2 WHERE entry IN (13117,13116);
