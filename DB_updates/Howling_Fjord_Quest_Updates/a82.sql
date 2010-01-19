-- http://www.wowhead.com/?quest=11434
-- 1.	Forgotten Treasure
-- 2.	The Fragrance of Money
-- 3.	A Traitor Among Us
-- 4.	Zeh'gehn Sez
-- 5.	A Carver and a Croaker

-- Forgotten Treasure
DELETE FROM gameobject WHERE id IN (186885,186886);
INSERT INTO gameobject VALUES
('399999','186885','571','1','1','-331.57','-3642.6','-100.735','5.14871','0','0','0.537306','-0.843387','120','0','1'),
('399998','186886','571','1','1','-299.737','-3682.2','-79.0612','5.03127','0','0','0.585872','-0.810404','25','0','1');
