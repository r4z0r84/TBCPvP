-- ----------------------------
-- Table structure for `spell_delays`
-- ----------------------------
DROP TABLE IF EXISTS `spell_delays`;
CREATE TABLE `spell_delays` (
  `entry` smallint(5) unsigned NOT NULL DEFAULT '0',
  `triggerDelay` smallint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of spell_delays
-- ----------------------------
INSERT INTO `spell_delays` VALUES ('37506', '1');
INSERT INTO `spell_delays` VALUES ('25504', '500');
INSERT INTO `spell_delays` VALUES ('33750', '500');
INSERT INTO `spell_delays` VALUES ('20424', '500');
INSERT INTO `spell_delays` VALUES ('31616', '100');
INSERT INTO `spell_delays` VALUES ('12798', '250');
INSERT INTO `spell_delays` VALUES ('14157', '250');
INSERT INTO `spell_delays` VALUES ('14189', '250');
