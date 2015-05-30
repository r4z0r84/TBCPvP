DROP TABLE IF EXISTS `character_talent`;
CREATE TABLE `character_talent` (
    `guid` INT(11) UNSIGNED NULL DEFAULT '0',
    `spell` INT(11) UNSIGNED NULL DEFAULT '0',
    `spec` TINYINT(3) UNSIGNED NULL DEFAULT '0'
)
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;

ALTER TABLE `character_action`
    ADD COLUMN `spec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `guid`,
    DROP PRIMARY KEY,
    ADD PRIMARY KEY (`guid`, `spec`, `button`);

ALTER TABLE `characters`
    ADD COLUMN `specCount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `latency`,
    ADD COLUMN `activeSpec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `specCount`;
