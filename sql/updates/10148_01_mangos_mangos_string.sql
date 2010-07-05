ALTER TABLE db_version CHANGE COLUMN required_10131_01_mangos_spell_bonus_data required_10148_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (66, 67);
INSERT INTO mangos_string () VALUES
(66, "Accepts whispers", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(67, "Doesn't accept whispers", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);