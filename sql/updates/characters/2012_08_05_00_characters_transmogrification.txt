-- ----------------------------
-- Table structure for `custom_transmogrification`
-- ----------------------------
DROP TABLE IF EXISTS `custom_transmogrification`;
CREATE TABLE `custom_transmogrification` (
  `GUID` int(10) unsigned NOT NULL DEFAULT '0',
  `FakeEntry` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `custom_transmogrification`
--

LOCK TABLES `custom_transmogrification` WRITE;
/*!40000 ALTER TABLE `custom_transmogrification` DISABLE KEYS */;
/*!40000 ALTER TABLE `custom_transmogrification` ENABLE KEYS */;
UNLOCK TABLES;