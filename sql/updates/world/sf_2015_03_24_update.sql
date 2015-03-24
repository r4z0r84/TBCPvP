/*
Script created by Quest Data Compare at 24.03.2015 13:13:39
This script must be executed against @DATABASE on localhost
This script applies changes to @DATABASE to make it the same as skyfire_world on localhost
*/
SET @DATABASE := "";
USE `@DATABASE`;

START TRANSACTION;

UPDATE `@DATABASE`.`creature` SET `position_x` = 2506.02, `position_y` = 7362.86, `position_z` = 380.363, `orientation` = 2.15189, `MovementType` = 2 WHERE `guid` = 48166;

INSERT INTO `@DATABASE`.`creature_addon` (`guid`, `path_id`, `mount`, `bytes0`, `bytes1`, `bytes2`, `emote`, `moveflags`, `isActive`, `auras`)
VALUES (48166, 23208, 0, 0, 0, 0, 0, 0, 0, NULL);

UPDATE `@DATABASE`.`creature_template` SET `MovementType` = 2 WHERE `entry` = 23208;

INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 1, 2501.73, 7362.45, 380.336, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 2, 2497.85, 7361.48, 380.32, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 3, 2497, 7362.48, 380.32, 60000, 0, 23208, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 4, 2497.85, 7361.48, 380.32, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 5, 2501.73, 7362.45, 380.336, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 6, 2506.11, 7362.21, 380.36, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 7, 2505.62, 7363.14, 380.36, 60000, 0, 23208, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (23208, 8, 2506.11, 7362.21, 380.36, 0, 0, 0, 100, 0);

INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (23208, 0, 2, 169, 69, 0, 0, 0, 0, 0, 0);

COMMIT;
