DELETE FROM creature WHERE id IN (32361,32357,32358,32409,32417,32400);
INSERT INTO creature VALUES
-- Icehorn 
('9000026','32361','571','1','1','0','0','3581.44','3710.41','36.848','3.39252','21600','0','0','13936','0','0','0'),
('9000025','32361','571','1','1','0','0','3414.07','3480.7','19.9845','4.9454','21600','0','0','13936','0','0','0'),
('9000024','32361','571','1','1','0','0','3087.49','3663.33','3.0895','3.75945','21600','0','0','13936','0','0','0'),
('9000023','32361','571','1','1','0','0','3176.67','3899.6','29.969','0.566814','21600','0','0','13936','0','0','0'),
('9000027','32361','571','1','1','0','0','3710.51','3878.38','26.3822','2.21835','21600','0','0','13936','0','0','0'),
('9000028','32361','571','1','1','0','0','3686.25','3330.26','52.6504','3.98707','21600','0','0','13936','0','0','0'),
-- Old Crystalbark
('9000029','32357','571','1','1','0','0','3570.66','7162.35','221.938','4.43065','21600','0','0','14415','3309','0','2'),
('9000030','32357','571','1','1','0','0','3678.43','6801.48','165.755','0.0885324','21600','0','0','14415','3309','0','2'),
-- Fumblub Gearwind
('9000031','32358','571','1','1','0','782','3788.3','4343.45','57.0656','3.0916','21600','0','0','13936','0','0','2'),
-- Crazed Indu'le Survivor
('9000032','32409','571','1','1','0','996','3896.86','2809.55','150.463','3.91722','21600','0','0','14910','0','0','0'),
('9000033','32409','571','1','1','0','996','3406.35','2782.14','52.1033','6.09672','21600','0','0','14910','0','0','0'),
('9000034','32409','571','1','1','0','996','3516.84','2472.2','68.6881','3.22609','21600','0','0','14910','0','0','0'),
('9000035','32409','571','1','1','0','996','3601.77','2310.58','59.152','3.35961','21600','0','0','14910','0','0','0'),
('9000036','32409','571','1','1','0','996','3414.53','2107.74','53.1617','0.261212','21600','0','0','14910','0','0','0'),
('9000037','32409','571','1','1','0','996','3268.54','2044.89','93.5158','0.909177','21600','0','0','14910','0','0','0'),
('9000038','32409','571','1','1','0','996','3348.49','1932.19','92.553','0.233733','21600','0','0','14910','0','0','0'),
('9000039','32409','571','1','1','0','996','3471.41','1817.96','73.1616','4.70265','21600','0','0','14910','0','0','0'),
-- Scarlet Highlord Daion
('9000042','32417','571','1','1','0','0','4676.58','-369.459','213.86','2.63934','21600','0','0','14910','0','0','0'),
('9000041','32417','571','1','1','0','0','4565.11','-526.463','190.097','0.750455','21600','0','0','14910','0','0','0'),
('9000040','32417','571','1','1','0','0','4677.56','-493.124','174.392','3.75069','21600','0','0','14910','0','0','0'),
-- Tukemuth
('9000043','32400','571','1','1','0','0','3509.07','547.143','68.0937','5.25001','21600','40','0','39760','0','0','1'),
('9000044','32400','571','1','1','0','0','3403.82','176.957','59.1881','5.79428','21600','0','0','39760','0','0','2'),
('9000045','32400','571','1','1','0','0','3405.93','-274.802','87.5405','0.145224','21600','0','0','39760','0','0','2'),
('9000046','32400','571','1','1','0','0','4182.69','-81.7875','65.7902','0.051816','21600','40','0','39760','0','0','1');


DELETE FROM pool_template WHERE entry IN (10018,10019,10020,10021,10022);
INSERT INTO pool_template VALUES
(10018, 1, 'Icehorn (32361)'),
(10019, 1, 'Old Crystalbark (32357)'),
(10020, 1, 'Crazed Indu\'le Survivor (32409)'),
(10021, 1, 'Scarlet Highlord Daion (32417)'),
(10022, 1, 'Tukemuth (32400)');


DELETE FROM pool_creature WHERE pool_entry IN (10018,10019,10020,10021,10022);
INSERT INTO pool_creature VALUES
(9000023, 10018, 0, 'Icehorn (32361) Spawn 1'),
(9000024, 10018, 0, 'Icehorn (32361) Spawn 2'),
(9000025, 10018, 0, 'Icehorn (32361) Spawn 3'),
(9000026, 10018, 0, 'Icehorn (32361) Spawn 4'),
(9000027, 10018, 0, 'Icehorn (32361) Spawn 5'),
(9000028, 10018, 0, 'Icehorn (32361) Spawn 6'),

(9000029, 10019, 0, 'Old Crystalbark (32357) Spawn 1'),
(9000030, 10019, 0, 'Old Crystalbark (32357) Spawn 2'),

(9000032, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 1'),
(9000033, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 2'),
(9000034, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 3'),
(9000035, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 4'),
(9000036, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 5'),
(9000037, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 6'),
(9000038, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 7'),
(9000039, 10020, 0, 'Crazed Indu\'le Survivor (32409) Spawn 8'),

(9000040, 10021, 0, 'Scarlet Highlord Daion (32417) Spawn 1'),
(9000041, 10021, 0, 'Scarlet Highlord Daion (32417) Spawn 2'),
(9000042, 10021, 0, 'Scarlet Highlord Daion (32417) Spawn 3'),

(9000043, 10022, 0, 'Tukemuth (32400) Spawn 1'),
(9000044, 10022, 0, 'Tukemuth (32400) Spawn 2'),
(9000045, 10022, 0, 'Tukemuth (32400) Spawn 3'),
(9000046, 10022, 0, 'Tukemuth (32400) Spawn 3');

DELETE FROM creature_movement WHERE id IN (9000029,9000030,9000031,9000044,9000045);
INSERT INTO creature_movement (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Old Crystalbark (1)
(9000029, 1, '3562.27','7085.85','211.075'),
(9000029, 2, '3564.14','7122.36','215.08'),
(9000029, 3, '3573.37','7153.44','220.607'),
(9000029, 4, '3577.77','7190.69','225.243'),
(9000029, 5, '3598.54','7213.43','221.18'),
(9000029, 6, '3606.76','7247.41','221.748'),
(9000029, 7, '3590.11','7280.11','232.626'),
(9000029, 8, '3600.47','7299.41','235.034'),
(9000029, 9, '3622.84','7319.82','230.135'),
(9000029, 10, '3632.97','7337.1','233.348'),
(9000029, 11, '3648.73','7338.25','232.828'),
(9000029, 12, '3673.74','7335.06','228.598'),
(9000029, 13, '3705.45','7320.24','216.068'),
(9000029, 14, '3729.86','7328.01','211.687'),
(9000029, 15, '3753.67','7323.23','206.672'),
(9000029, 16, '3729.86','7328.01','211.687'),
(9000029, 17, '3705.45','7320.24','216.068'),
(9000029, 18, '3673.74','7335.06','228.598'),
(9000029, 19, '3648.73','7338.25','232.828'),
(9000029, 20, '3632.97','7337.1','233.348'),
(9000029, 21, '3622.84','7319.82','230.135'),
(9000029, 22, '3600.47','7299.41','235.034'),
(9000029, 23, '3590.11','7280.11','232.626'),
(9000029, 24, '3606.76','7247.41','221.748'),
(9000029, 25, '3598.54','7213.43','221.18'),
(9000029, 26, '3577.77','7190.69','225.243'),
(9000029, 27, '3573.37','7153.44','220.607'),
(9000029, 28, '3564.14','7122.36','215.08'),
-- Old Crystalbark (2)
(9000030, 1, '3721.14','6616.78','170.715'),
(9000030, 2, '3712.48','6655.71','168.507'),
(9000030, 3, '3701.7','6635.56','172.634'),
(9000030, 4, '3723.77','6671.04','161.879'),
(9000030, 5, '3718.44','6691.83','161.536'),
(9000030, 6, '3699.21','6708.8','160.739'),
(9000030, 7, '3694.39','6729.21','162.499'),
(9000030, 8, '3688.61','6757.57','166.978'),
(9000030, 9, '3676.76','6771.93','169.999'),
(9000030, 10, '3677.08','6800.38','166.153'),
(9000030, 11, '3746.55','6599.49','170.139'),
(9000030, 12, '3765.28','6582.69','170.906'),
(9000030, 13, '3796.89','6584.55','166.093'),
(9000030, 14, '3765.28','6582.69','170.906'),
(9000030, 15, '3746.55','6599.49','170.139'),
(9000030, 16, '3677.08','6800.38','166.153'),
(9000030, 17, '3676.76','6771.93','169.999'),
(9000030, 18, '3688.61','6757.57','166.978'),
(9000030, 19, '3694.39','6729.21','162.499'),
(9000030, 20, '3699.21','6708.8','160.739'),
(9000030, 21, '3718.44','6691.83','161.536'),
(9000030, 22, '3723.77','6671.04','161.879'),
(9000030, 23, '3701.7','6635.56','172.634'),
(9000030, 24, '3712.48','6655.71','168.507'),

-- Fumblub Gearwind
(9000031, 1, '3466.38','4284.19','34.105'),
(9000031, 2, '3439.92','4275.17','34.5257'),
(9000031, 3, '3411.29','4268.95','36.3769'),
(9000031, 4, '3495.2','4297.3','33.8686'),
(9000031, 5, '3522.62','4307.84','34.2797'),
(9000031, 6, '3556.14','4317.12','36.8059'),
(9000031, 7, '3593.16','4326.48','36.6168'),
(9000031, 8, '3643.81','4330.51','36.766'),
(9000031, 9, '3694.38','4333.95','40.0929'),
(9000031, 10, '3734.23','4337.01','46.9885'),
(9000031, 11, '3788.3','4343.45','57.0656'),
(9000031, 12, '3383.62','4262.43','37.5074'),
(9000031, 13, '3355.19','4254.95','38.0229'),
(9000031, 14, '3326.57','4246.45','38.078'),
(9000031, 15, '3310.8','4266.39','39.252'),
(9000031, 16, '3298.7','4291.06','38.9065'),
(9000031, 17, '3290.38','4316.24','38.7146'),
(9000031, 18, '3284.3','4347.79','39.2216'),
(9000031, 19, '3281.2','4371.75','37.0792'),
(9000031, 20, '3283.83','4400.69','37.9302'),
(9000031, 21, '3298.76','4430.67','37.7613'),
(9000031, 22, '3311.74','4447.11','37.6776'),
(9000031, 23, '3329.68','4465.49','37.4878'),
(9000031, 24, '3354.82','4486.26','37.4942'),
(9000031, 25, '3376.55','4505.79','34.734'),
(9000031, 26, '3399.46','4526.95','33.4767'),
(9000031, 27, '3425.11','4554.2','30.8348'),
(9000031, 28, '3431.01','4577.62','30.5375'),
(9000031, 29, '3427.64','4607.11','37.1853'),
(9000031, 30, '3427.03','4635.62','41.5008'),
(9000031, 31, '3429.03','4667.63','43.9177'),
(9000031, 32, '3432.71','4701.95','45.1908'),
(9000031, 33, '3446.44','4719.02','44.9894'),
(9000031, 34, '3467.45','4724.14','40.5816'),
(9000031, 35, '3489.15','4735.99','30.2991'),
(9000031, 36, '3514','4756.21','23.3081'),
(9000031, 37, '3535.06','4777.98','22.6625'),
(9000031, 38, '3554.37','4804.11','22.4445'),
(9000031, 39, '3567.51','4833.89','21.9452'),
(9000031, 40, '3575.15','4868.38','20.6851'),
(9000031, 41, '3580.85','4904.26','19.1482'),
(9000031, 42, '3599.69','4931.7','16.6297'),
(9000031, 43, '3634.44','4943.94','14.6274'),
(9000031, 44, '3666.19','4954.58','15.8502'),
(9000031, 45, '3688.14','4966.71','16.3076'),
(9000031, 46, '3708.63','4976.69','20.6347'),
(9000031, 47, '3731.53','4965.75','17.1442'),
(9000031, 48, '3759.8','4960.27','16.112'),
(9000031, 49, '3789.44','4957.1','15.9076'),
(9000031, 50, '3824.36','4962.02','13.9456'),
(9000031, 51, '3843.66','4987.65','15.8375'),
(9000031, 52, '3861.57','5018.13','17.7006'),
(9000031, 53, '3883.42','5045.14','16.7864'),
(9000031, 54, '3912.65','5064.77','17.5382'),
(9000031, 55, '3945.31','5083.72','18.4133'),
(9000031, 56, '3974.56','5090.28','19.2579'),
(9000031, 57, '4000.22','5074.4','18.5718'),
(9000031, 58, '4026.92','5071.26','20.2866'),
(9000031, 59, '4044.29','5069.33','21.0127'),
(9000031, 60, '4085.73','5070.28','20.8439'),
(9000031, 61, '4113.6','5085.66','22.0717'),
(9000031, 62, '4126.34','5086.13','24.618'),
(9000031, 63, '4143.6','5084.23','29.0719'),
(9000031, 64, '4159.08','5091.56','32.5983'),
(9000031, 65, '4172.51','5096.87','35.1407'),
(9000031, 66, '4201.07','5105.67','40.0594'),
(9000031, 67, '4228.38','5108.5','41.6494'),
(9000031, 68, '4257.12','5111.16','40.0134'),
(9000031, 69, '4284.02','5109.67','37.598'),
(9000031, 70, '4308.91','5098.14','35.2626'),
(9000031, 71, '4329.53','5071.15','32.8624'),
(9000031, 72, '4336.13','5043.56','32.1165'),
(9000031, 73, '4335.77','5014.01','31.1091'),
(9000031, 74, '4325.61','4989.59','32.1951'),
(9000031, 75, '4313.28','4966.59','32.9452'),
(9000031, 76, '4297.47','4944.12','33.7597'),
(9000031, 77, '4266.2','4933.81','30.2677'),
(9000031, 78, '4237.8','4918.86','19.0899'),
(9000031, 79, '4211.17','4900.21','12.6526'),
(9000031, 80, '4199.33','4873.4','10.2666'),
(9000031, 81, '4189.51','4852.77','10.9159'),
(9000031, 82, '4156.46','4837.11','12.8153'),
(9000031, 83, '4134.24','4826.57','14.3729'),
(9000031, 84, '4108.4','4817.05','15.0112'),
(9000031, 85, '4079.59','4801.66','16.0679'),
(9000031, 86, '4052.06','4786.82','17.0386'),
(9000031, 87, '4020.08','4768.67','16.7369'),
(9000031, 88, '3995.63','4754.14','17.0184'),
(9000031, 89, '4010.06','4731.47','15.5577'),
(9000031, 90, '4027.13','4711.52','15.9832'),
(9000031, 91, '4052.33','4695.78','18.2276'),
(9000031, 92, '4080.9','4682.15','29.5668'),
(9000031, 93, '4058.26','4684.2','21.1677'),
(9000031, 94, '4036.27','4669.65','17.7693'),
(9000031, 95, '4008.7','4653.12','17.8495'),
(9000031, 96, '3989.66','4637.43','18.6497'),
(9000031, 97, '3957.71','4633.45','19.0588'),
(9000031, 98, '3929.95','4630.1','19.0564'),
(9000031, 99, '3900.31','4626.61','18.1852'),
(9000031, 100, '3870.67','4623.12','17.314'),
(9000031, 101, '3845.25','4609.32','16.9693'),
(9000031, 102, '3817.93','4595.14','15.7482'),
(9000031, 103, '3796.84','4584.13','15.1856'),
(9000031, 104, '3782.16','4567.87','15.1342'),
(9000031, 105, '3764.97','4549.44','15.1905'),
(9000031, 106, '3743.3','4529.66','14.871'),
(9000031, 107, '3726.04','4515.39','14.4519'),
(9000031, 108, '3703.35','4506.04','14.0456'),
(9000031, 109, '3676.6','4497.79','14.1313'),
(9000031, 110, '3653.19','4489.88','14.146'),
(9000031, 111, '3628.01','4473.96','15.0236'),
(9000031, 112, '3607.86','4454.54','13.3355'),
(9000031, 113, '3597.32','4424.71','14.7505'),
(9000031, 114, '3591.89','4395.13','17.3799'),
(9000031, 115, '3587.64','4363.51','21.1676'),
(9000031, 116, '3590.47','4331.23','33.2'),
(9000031, 117, '3615.55','4330.93','34.2288'),
(9000031, 118, '3644.28','4332.61','36.4913'),
(9000031, 119, '3667.5','4333.78','38.197'),
(9000031, 120, '3696.77','4336','39.6938'),
(9000031, 121, '3716.32','4337.89','43.8977'),
(9000031, 122, '3742.72','4341.78','47.8309'),
(9000031, 123, '3770.58','4344.24','52.9228'),

-- Tukemuth (1)
(9000044, 1, '3611.9','111.483','44.2918'),
(9000044, 2, '3624.38','113.119','44.7585'),
(9000044, 3, '3605.21','109.557','44.2844'),
(9000044, 4, '3592.46','108.936','46.6237'),
(9000044, 5, '3532.77','101.113','52.6528'),
(9000044, 6, '3555.43','104.083','52.8676'),
(9000044, 7, '3574.87','106.63','51.1815'),
(9000044, 8, '3498.59','96.6331','52.0986'),
(9000044, 9, '3482.03','106.237','50.2453'),
(9000044, 10, '3465.1','116.052','50.6755'),
(9000044, 11, '3440.83','141.959','55.117'),
(9000044, 12, '3448.32','120.404','54.8926'),
(9000044, 13, '3465.22','112.419','50.9703'),
(9000044, 14, '3469.04','94.1231','51.5424'),
(9000044, 15, '3471.9','80.4183','53.7016'),
(9000044, 16, '3471.9','80.4183','53.7016'),
(9000044, 17, '3486.87','70.0026','53.8135'),
(9000044, 18, '3500.63','60.4265','55.0688'),
(9000044, 19, '3514.38','68.3566','53.7812'),
(9000044, 20, '3533.33','79.283','53.1254'),
(9000044, 21, '3544.64','85.8039','53.7827'),
(9000044, 22, '3555.38','88.6305','53.7466'),
(9000044, 23, '3576.04','92.3696','51.345'),
(9000044, 24, '3593.35','94.907','48.8681'),
(9000044, 25, '3604.59','108.841','44.3782'),
(9000044, 26, '3449.49','126.746','54.8414'),
(9000044, 27, '3445.85','128.845','55.7416'),
(9000044, 28, '3433.06','142.642','56.035'),
(9000044, 29, '3421.77','156.016','57.1374'),
(9000044, 30, '3403.21','179.371','58.9317'),

-- Tukemuth (2)
(9000045, 1, '3712.79','-280.774','72.2173'),
(9000045, 2, '3692.91','-285.792','72.8976'),
(9000045, 3, '3670.12','-279.461','69.8087'),
(9000045, 4, '3650.37','-275.772','69.9728'),
(9000045, 5, '3629.76','-271.923','67.323'),
(9000045, 6, '3611.9','-268.587','68.5729'),
(9000045, 7, '3593.98','-265.239','70.9491'),
(9000045, 8, '3577.46','-262.155','73.1534'),
(9000045, 9, '3558.68','-258.646','74.3677'),
(9000045, 10, '3538.06','-254.796','74.9153'),
(9000045, 11, '3521.51','-252.149','75.1799'),
(9000045, 12, '3504.64','-257.537','72.3854'),
(9000045, 13, '3486.85','-263.154','71.0343'),
(9000045, 14, '3465.96','-269.671','73.2614'),
(9000045, 15, '3446.81','-275.642','77.6404'),
(9000045, 16, '3429.08','-269.955','79.7542'),
(9000045, 17, '3733.28','-269.861','74.4622'),
(9000045, 18, '3752.21','-252.878','76.6949'),
(9000045, 19, '3769.53','-236.997','77.6692'),
(9000045, 20, '3786.02','-214.446','73.9372'),
(9000045, 21, '3769.32','-236.878','77.6868'),
(9000045, 22, '3752.67','-243.96','76.4544'),
(9000045, 23, '3729.17','-247.654','73.7805'),
(9000045, 24, '3709.86','-250.668','71.6087'),
(9000045, 25, '3689.46','-261.79','70.5633'),
(9000045, 26, '3670.08','-277.818','69.7831'),
(9000045, 27, '3648.92','-295.401','71.4218'),
(9000045, 28, '3627.99','-295.653','69.4194'),
(9000045, 29, '3603.65','-286.131','70.1983'),
(9000045, 30, '3583.31','-277.984','72.5388'),
(9000045, 31, '3565.99','-271.047','72.6149'),
(9000045, 32, '3545.55','-264.811','74.0617'),
(9000045, 33, '3525.07','-259.999','74.2423'),
(9000045, 34, '3504.28','-265.168','71.6909'),
(9000045, 35, '3482.96','-255.741','71.3816'),
(9000045, 36, '3405.93','-274.802','87.5405'),
(9000045, 37, '3424.52','-270.948','80.6977'),
(9000045, 38, '3444.13','-263.527','77.954'),
(9000045, 39, '3460.51','-259.918','73.2668');


-- Fumblub Gearwind
UPDATE creature_template SET inhabittype = 4 WHERE entry = 32358;
-- Flying Machine
DELETE FROM creature_addon WHERE guid IN (9000031);
INSERT INTO creature_addon VALUES
(9000031, 0,0,0,0,0,'44153 0');
