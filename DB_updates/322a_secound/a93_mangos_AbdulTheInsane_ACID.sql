UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 24900;
DELETE FROM creature_ai_scripts WHERE creature_id = 24900;
INSERT INTO creature_ai_scripts VALUES
(2490001,24900, 4,0,100,0, 0,0,0,0, 1,-9996,0,0, 0,0,0,0, 0,0,0,0, 'Abdul the insane - aggro'),
(2490002,24900, 0,0,100,1, 0,0,60000,60000, 1,-9998,-9997,-9998, 0,0,0,0, 0,0,0,0, 'Abdul the insane - random yell'),
(2490003,24900, 0,0,100,1, 30000,30000,60000,60000, 1,-10000,-9999,-10000, 0,0,0,0, 0,0,0,0, 'Abdul the insane - random yell');


DELETE FROM creature_ai_texts WHERE entry BETWEEN -10000 AND -9996;
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-10000,'ABDUL IS STRONG LIKE BULL!',1,'Abdul the insane - random yell'),
(-9999,'ARE YOU CHALLENGING ME? I HAVE THE STRENGTH OF TEN MEN!',1,'Abdul the insane - random yell'),
(-9998,'Its power courses through me! I AM A GOD!',1,'Abdul the insane - random yell'),
(-9997,'HOW DARE YOU! ABDUL WILL PUT YOUR HEAD ON A PIKE!',1,'Abdul the insane - random yell'),
(-9996,'The fury of the Vrykul will consume you!',0,'Abdul the insane - aggro');
