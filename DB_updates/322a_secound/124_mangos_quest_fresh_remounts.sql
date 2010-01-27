UPDATE ``quest_template` SET `ReqSourceId2` = '37269',`ReqSourceCount2` = '3',`ReqCreatureOrGOId1` = '27213' WHERE `quest_template`.`entry` =12214 LIMIT 1 ;

DELETE FROM creature_loot_template WHERE entry = 27213;
INSERT INTO `creature_loot_template` (`entry` ,`item` ,`ChanceOrQuestChance` ,`groupid` ,`mincountOrRef` ,`maxcount` ,`lootcondition` ,`condition_value1` ,`condition_value2` )VALUES ('27213', '41802', '33', '0', '1', '1', '0', '0', '0'), ('27213', '40199', '33', '0', '1', '1', '0', '0', '0'), ('27213', '37269', '-33', '0', '1', '1', '0', '0', '0');