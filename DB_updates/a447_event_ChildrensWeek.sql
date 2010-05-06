#################  human and orcish version   ################################################################
-- All 3 are availeble after finishing Children's Week (alliance)
UPDATE quest_template SET
PrevQuestId = 1468,
ExclusiveGroup = -1479
WHERE entry IN (1479,1558,1687);

-- Both availeble after finishing The Bough of the Eternals, The Stonewrought Dam, Spooky Lighthouse (alliance)
UPDATE quest_template SET
PrevQuestId = 1479,
RequiredRaces = 1101
WHERE entry IN (558,4822);

-- All 3 are availeble after finishing Children's Week (alliance)
UPDATE quest_template SET
PrevQuestId = 172,
ExclusiveGroup = -910
WHERE entry IN (1800,910,911);

-- Both availeble after finishing Lordaeron Throne Room, Down at the Docks, Gateway to the Frontier (alliance)
UPDATE quest_template SET
PrevQuestId = 910,
RequiredRaces = 690
WHERE entry IN (925,915);
   
DELETE FROM gossip_menu_option WHERE menu_id IN (5849,5848,20002,5851);
INSERT INTO gossip_menu_option VALUES
-- alliance version (return whistle of lost)
(5849, 0, 0, 'Well what do you know, this is Children\'s Week! What can I do to help?',1,1,0,0,5849,0,0,'',0,0,0, 0,0,0, 0,0,0),
(5849, 1, 0, 'GOSSIP_OPTION_QUESTGIVER', 2, 2, 0,0,0,0,0,'',0,0,0, 0,0,0, 0,0,0),
-- horde version (return whistle of lost)
(5848, 0, 0, 'Well what do you know, this is Children\'s Week! What can I do to help?',1,1,0,0,5848,0,0,'',0,0,0, 0,0,0, 0,0,0),
(5848, 1, 0, 'GOSSIP_OPTION_QUESTGIVER', 2, 2, 0,0,0,0,0,'',0,0,0, 0,0,0, 0,0,0),
-- jaina proudmore (maybe 5850?)
(20002, 0, 0, 'Lady Jaina, this may sound like an odd request... but I have a young ward who is quite shy. You are a hero to him, and he asked me to get your autograph.',1,1,20003,0,20002,0,0,'',9,558,0, 0,0,0, 0,0,0),
(20002, 1, 0, 'GOSSIP_OPTION_QUESTGIVER', 2, 2, 0,0,0,0,0,'',0,0,0, 0,0,0, 0,0,0),
-- cairne bloodhoof
(5851, 0, 0, 'I know this is rather silly but a young ward who is a bit shy would like your hoofprint.',1,1,20004,0,5851,0,0,'',9,925,0, 0,0,0, 0,0,0),
(5851, 1, 0, 'GOSSIP_OPTION_QUESTGIVER', 2, 2, 0,0,0,0,0,'',0,0,0, 0,0,0, 0,0,0);

DELETE FROM gossip_scripts WHERE id IN (5849,5848,20002);
INSERT INTO gossip_scripts VALUES
-- Orphan Matron Nightingale (alliance)
(5849,0,15,23124,0, 0, 0,0,0,0),
-- Orphan Matron Battlewail (horde)
(5848,0,15,23125,0, 0, 0,0,0,0),
-- Jaina Proudmore (theramoore)
(20002,0,15,23122,0, 0, 0,0,0,0),
-- Cairne Bloodhoof
(5851,0,15,23123,0, 0, 0,0,0,0);

-- Jaina Proudmore (theramoore)
UPDATE creature_template SET
gossip_menu_id = 20002, -- maybe 5850?
ScriptName = ''
WHERE entry = 4968;

DELETE FROM gossip_menu WHERE entry IN (20002,20003,20004,5851,5849,5848);
INSERT INTO gossip_menu VALUES
-- jaina proudmore
(20002, 3157,0,0,0,0,0,0),
(20003, 7012,0,0,0,0,0,0),
-- cairne bloodhoof
(5851, 7013,0,0,0,0,0,0),
(20004, 7014,0,0,0,0,0,0),
-- Orphan Matron Nightingale (alliance)
(5848, 7010,0,0,0,0,0,0),
-- Orphan Matron Nightingale (alliance)
(5849, 7011,0,0,0,0,0,0);

-- jaina proudmore, cairne bloodhoof
DELETE FROM npc_gossip WHERE npc_guid IN (SELECT guid FROM creature WHERE id IN (4968,3057,14450,14451));

DELETE FROM areatrigger_scripts WHERE entry IN (3546, 3547, 3548, 3549, 3550, 3552);
INSERT INTO areatrigger_scripts VALUES
-- Darnassian bank
(3546, 'at_childrens_week_spot'),
-- Undercity - thone room
(3547, 'at_childrens_week_spot'),
-- Stonewrought Dam
(3548, 'at_childrens_week_spot'),
-- The Mor'shan Rampart
(3549, 'at_childrens_week_spot'),
-- Ratchet Docks
(3550, 'at_childrens_week_spot'),
-- Westfall Lighthouse
(3552, 'at_childrens_week_spot');

/* cleanup character db
-- orcish chain
DELETE FROM character_queststatus WHERE quest IN (172,1800,910,911,925,925,5502);
-- human chain
DELETE FROM character_queststatus WHERE quest IN (1468,1687,1558,1479,4822,558,171);
-- whistles
DELETE FROM character_inventory WHERE item_template IN (18598,18597);
*/
