DROP TABLE IF EXISTS `character_talent`;
CREATE TABLE `character_talent` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `spell` int(11) unsigned NOT NULL DEFAULT '0',
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`spell`,`spec`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

ALTER TABLE `character_action`
    ADD COLUMN `spec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `guid`,
    DROP PRIMARY KEY,
    ADD PRIMARY KEY (`guid`, `spec`, `button`);

ALTER TABLE `characters`
    ADD COLUMN `specCount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `latency`,
    ADD COLUMN `activeSpec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `specCount`;

DROP TABLE IF EXISTS `character_talent_name`;
CREATE TABLE `character_talent_name` (
      `guid` int(11) unsigned NOT NULL DEFAULT '0',
      `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
      `name` varchar(255) NOT NULL DEFAULT '',
      PRIMARY KEY (`guid`,`spec`)
    ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
