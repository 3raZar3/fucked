-- Utgard-Keep::Heroic Boss Drop
DELETE FROM creature_loot_template WHERE entry IN (30748,31679,31656,31673);

-- Utgard-Keep::Keleseth hero loot id 30748
UPDATE creature_template SET `lootid` = '30748' WHERE `entry` IN (30748);
INSERT INTO `creature_loot_template` VALUES ('30748', '37177', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30748', '37178', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30748', '37179', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30748', '37180', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30748', '43852', '1.8', '0', '1', '1', '0', '0', '0');

-- Utgard-Keep::Skarvald hero loot id 31679
UPDATE creature_template SET `lootid` = '31679' WHERE `entry` IN (31679);
INSERT INTO `creature_loot_template` VALUES ('31679', '37181', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31679', '37182', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31679', '37183', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31679', '37184', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31679', '43852', '1.8', '0', '1', '1', '0', '0', '0');

-- Utgard-Keep::Dalronn 	hero loot id 31656
UPDATE creature_template SET `lootid` = '31656' WHERE `entry` IN (31656);
INSERT INTO `creature_loot_template` VALUES ('31656', '33470', '23', '0', '1', '7', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31656', '43852', '12', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31656', '33454', '6', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31656', '33445', '2', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31656', '33447', '1.7', '0', '1', '1', '0', '0', '0');

-- Utgard-keep::Ingvar		hero loot id 31673
UPDATE creature_template SET `lootid` = '31673' WHERE `entry` IN (31673);
INSERT INTO `creature_loot_template` VALUES ('31673', '43662', '-100', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '43102', '100', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37186', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37188', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37189', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37190', '0', '2', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37191', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37192', '0', '1', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('31673', '37193', '0', '1', '1', '1', '0', '0', '0');