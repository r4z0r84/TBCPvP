/*
Script created by Quest Data Compare at 25.03.2015 21:33:31
This script must be executed against @DATABASE on localhost
This script applies changes to @DATABASE to make it the same as skyfire_world on localhost
*/

SET @DATABASE := "";
USE `@DATABASE`;

START TRANSACTION;

UPDATE `@DATABASE`.`creature_template` SET `ScriptName` = 'npc_severin' WHERE `entry` = 23042;

UPDATE `@DATABASE`.`quest_template` SET `RewRepFaction1` = 1031, `RewRepValue1` = 350 WHERE `entry` = 11008;

DELETE FROM `@DATABASE`.`spell_script_target` WHERE `entry` = 39844 AND `type` = 0 AND `targetEntry` = 185549;

INSERT INTO `@DATABASE`.`spell_script_target` (`entry`, `type`, `targetEntry`)
VALUES (39844, 1, 22991);

COMMIT;
