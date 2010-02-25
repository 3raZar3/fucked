--
-- Table structure for table `quest_poi`
--

DROP TABLE IF EXISTS `quest_poi`;
CREATE TABLE IF NOT EXISTS `quest_poi` (
  `questId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `poiId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `objIndex` int(11) NOT NULL DEFAULT '0',
  `mapId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `areaId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `floorId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `unk3` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `unk4` int(11) UNSIGNED NOT NULL DEFAULT '0',
  KEY `questId` (`poiId`,`questId`),
  KEY `poiId` (`poiId`,`questId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Table structure for table `quest_poi_points`
--

DROP TABLE IF EXISTS `quest_poi_points`;
CREATE TABLE IF NOT EXISTS `quest_poi_points` (
  `questId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `poiId` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `x` int(11) NOT NULL DEFAULT '0',
  `y` int(11) NOT NULL DEFAULT '0',
  KEY `questId` (`poiId`,`questId`),
  KEY `poiId` (`poiId`,`questId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
