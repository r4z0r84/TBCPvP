/*
Script created by Quest Data Compare at 25.03.2015 15:03:32
This script must be executed against @DATABASE on localhost
This script applies changes to @DATABASE to make it the same as skyfire_world on localhost
*/
SET @DATABASE := "";
USE `@DATABASE`;

START TRANSACTION;

DELETE FROM `@DATABASE`.`creature` WHERE `guid` = 78998;
DELETE FROM `@DATABASE`.`creature` WHERE `guid` = 78999;
DELETE FROM `@DATABASE`.`creature` WHERE `guid` = 79000;

UPDATE `@DATABASE`.`creature` SET `position_x` = 2548.55, `position_y` = 7330.01, `position_z` = 373.42, `orientation` = 3.53656 WHERE `guid` = 44255;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2495.07, `position_y` = 7350.35, `position_z` = 380.222, `orientation` = 5.44663 WHERE `guid` = 44256;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2506.61, `position_y` = 7363.08, `position_z` = 380.367, `orientation` = 4.92277 WHERE `guid` = 48166;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2502.59, `position_y` = 7359.17, `position_z` = 380.351, `orientation` = 4.71229 WHERE `guid` = 48167;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3364.91, `position_y` = 3658.65, `position_z` = 284.598, `orientation` = 4.65775, `MovementType` = 2 WHERE `guid` = 79004;
UPDATE `@DATABASE`.`creature` SET `MovementType` = 0 WHERE `guid` = 79005;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3370.88, `position_y` = 3600.54, `position_z` = 277.767, `orientation` = 1.1109, `MovementType` = 0 WHERE `guid` = 79007;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3372.71, `position_y` = 3654.26, `position_z` = 284.624, `orientation` = 5.69292, `MovementType` = 0 WHERE `guid` = 79008;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3368.02, `position_y` = 3658.15, `position_z` = 284.592, `orientation` = 5.1078, `MovementType` = 0 WHERE `guid` = 79009;
UPDATE `@DATABASE`.`creature` SET `MovementType` = 2 WHERE `guid` = 79010;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3408.57, `position_z` = 278.072, `orientation` = 6.2631 WHERE `guid` = 79013;
UPDATE `@DATABASE`.`creature` SET `equipment_id` = 1044 WHERE `guid` = 79021;
UPDATE `@DATABASE`.`creature` SET `equipment_id` = 1044 WHERE `guid` = 79022;
UPDATE `@DATABASE`.`creature` SET `equipment_id` = 1044, `position_x` = -3399.2, `position_y` = 3580.7, `position_z` = 276.644, `orientation` = 4.49596 WHERE `guid` = 79024;
UPDATE `@DATABASE`.`creature` SET `position_x` = -3385.35, `position_y` = 3595.78, `position_z` = 275.999, `orientation` = 3.93833, `MovementType` = 2 WHERE `guid` = 79026;
UPDATE `@DATABASE`.`creature` SET `equipment_id` = 24595, `position_x` = 2516.25, `position_y` = 7354.53, `orientation` = 2.85088, `MovementType` = 2 WHERE `guid` = 1189374;
UPDATE `@DATABASE`.`creature` SET `MovementType` = 2 WHERE `guid` = 1189378;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2544.83, `position_y` = 7335.04, `orientation` = 4.59292 WHERE `guid` = 1189380;

UPDATE `@DATABASE`.`creature_addon` SET `path_id` = 48166 WHERE `guid` = 48166;
UPDATE `@DATABASE`.`creature_addon` SET `path_id` = 79026 WHERE `guid` = 79026;

INSERT INTO `@DATABASE`.`creature_addon` (`guid`, `path_id`, `mount`, `bytes0`, `bytes1`, `bytes2`, `emote`, `moveflags`, `isActive`, `auras`)
VALUES (79004, 79004, 0, 0, 0, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`creature_addon` (`guid`, `path_id`, `mount`, `bytes0`, `bytes1`, `bytes2`, `emote`, `moveflags`, `isActive`, `auras`)
VALUES (79010, 79010, 0, 0, 0, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`creature_addon` (`guid`, `path_id`, `mount`, `bytes0`, `bytes1`, `bytes2`, `emote`, `moveflags`, `isActive`, `auras`)
VALUES (1189374, 1189374, 0, 0, 0, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`creature_addon` (`guid`, `path_id`, `mount`, `bytes0`, `bytes1`, `bytes2`, `emote`, `moveflags`, `isActive`, `auras`)
VALUES (1189378, 1189378, 0, 0, 0, 0, 0, 0, 0, NULL);

INSERT INTO `@DATABASE`.`creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`)
VALUES (24595, 24595, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `@DATABASE`.`creature_formations` (`memberGUID`, `leaderGUID`, `dist`, `angle`, `groupAI`)
VALUES (79010, 79010, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature_formations` (`memberGUID`, `leaderGUID`, `dist`, `angle`, `groupAI`)
VALUES (79012, 79010, 3, 360, 0);

UPDATE `@DATABASE`.`creature_template` SET `equipment_id` = 508, `ScriptName` = 'npc_skyguard_handler_irena' WHERE `entry` = 23413;

INSERT INTO `@DATABASE`.`db_script_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES (2000000077, 'spills her beverage.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `@DATABASE`.`db_script_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES (2000000078, 'SKYGUARD SCOUT!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `@DATABASE`.`db_script_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES (2000000079, 'cleans up the mess while muttering curses about the Skyguard hotshot pilots.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO `@DATABASE`.`game_tele` (`id`, `position_x`, `position_y`, `position_z`, `orientation`, `map`, `name`)
VALUES (431, -3364.8, 3649.76, 284.59, 1.70387, 530, 'skyguard2');

DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 1;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 2;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 3;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 4;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 5;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 6;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 7;
DELETE FROM `@DATABASE`.`waypoint_data` WHERE `id` = 23208 AND `point` = 8;

INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 1, 2502.79, 7362.58, 380.347, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 2, 2501.23, 7364.36, 381.055, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 3, 2497.05, 7362.56, 380.321, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 4, 2496.61, 7362.93, 380.321, 30000, 0, 48166, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 5, 2497.48, 7361.14, 380.321, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 6, 2501.03, 7362.75, 380.343, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 7, 2501.87, 7360.96, 380.347, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 8, 2506.22, 7363.67, 380.36, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (48166, 9, 2506.41, 7363.09, 380.367, 300000, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 1, -3365.76, 3641.63, 284.605, 500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 2, -3365.75, 3641.86, 284.605, 9500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 3, -3365.75, 3641.86, 284.605, 10000, 0, 79004, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 4, -3364.91, 3659.01, 284.606, 500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 5, -3364.92, 3658.8, 284.601, 9500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79004, 6, -3364.92, 3658.8, 284.601, 10000, 0, 79004, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 1, -3379.5, 3639.06, 285.339, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 2, -3381.89, 3634, 283.016, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 3, -3380.31, 3624.64, 278.237, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 4, -3385.78, 3620.64, 276.675, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 5, -3392.45, 3618.52, 276.464, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 6, -3393.95, 3611.69, 276.219, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 7, -3389.51, 3605.58, 275.967, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 8, -3391.81, 3597.15, 275.956, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 9, -3397.6, 3597.76, 276.788, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 10, -3391.81, 3597.15, 275.956, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 11, -3389.51, 3605.58, 275.967, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 12, -3393.95, 3611.69, 276.219, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 13, -3392.45, 3618.52, 276.464, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 14, -3385.78, 3620.64, 276.675, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 15, -3380.31, 3624.64, 278.237, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 16, -3381.89, 3634, 283.016, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 17, -3379.5, 3639.06, 285.339, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 18, -3371.3, 3649.34, 284.596, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79010, 19, -3374.52, 3644.16, 284.801, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 1, -3393.66, 3585.7, 276.065, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 2, -3400.52, 3582.78, 276.525, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 3, -3420.03, 3579.38, 276.263, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 4, -3432.99, 3577.56, 276.059, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 5, -3447.99, 3575.98, 275.665, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 6, -3432.99, 3577.56, 276.059, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 7, -3420.03, 3579.38, 276.263, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 8, -3400.52, 3582.78, 276.525, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (79026, 9, -3385.35, 3595.78, 275.999, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 1, 2514.2, 7355.25, 380.734, 30000, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 2, 2514.2, 7355.25, 380.734, 3000, 0, 118937401, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 3, 2514.2, 7355.25, 380.734, 3000, 0, 118937401, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 4, 2514.2, 7355.25, 380.734, 3000, 0, 118937401, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 5, 2514.2, 7355.25, 380.734, 3000, 0, 118937402, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 6, 2514.2, 7355.25, 380.734, 3000, 0, 118937403, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 7, 2512.8, 7350.62, 380.734, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 8, 2516.72, 7346.15, 381.03, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 9, 2518.85, 7344.07, 380.856, 1000, 0, 118937404, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 10, 2518.85, 7344.07, 380.856, 44000, 0, 118937405, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 11, 2516.72, 7346.15, 381.03, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 12, 2512.8, 7350.62, 380.734, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189374, 13, 2516.25, 7354.53, 380.733, 0, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 1, 2522.73, 7322.35, 373.437, 500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 2, 2523.08, 7322.36, 373.437, 9500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 3, 2523.08, 7322.36, 373.437, 10000, 0, 79004, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 4, 2540.21, 7322.78, 373.438, 500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 5, 2539.74, 7322.79, 373.442, 9500, 0, 0, 100, 0);
INSERT INTO `@DATABASE`.`waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`)
VALUES (1189378, 6, 2539.74, 7322.79, 373.442, 10000, 0, 79004, 100, 0);

DELETE FROM `@DATABASE`.`waypoint_scripts` WHERE `id` = 23208 AND `delay` = 0 AND `command` = 2 AND `datalong` = 169 AND `datalong2` = 69 AND `dataint` = 0 AND `x` = 0 AND `y` = 0 AND `z` = 0 AND `o` = 0;

INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (48166, 0, 2, 169, 69, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (79004, 0, 1, 25, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (7900401, 0, 30, 0, 0, 0, 0, 0, 0, 1.48866, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (7900403, 0, 0, 0, 0, 0, 0, 0, 0, 4.68523, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (118937401, 0, 1, 92, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (118937402, 0, 0, 2, 0, 2000000077, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (118937403, 0, 0, 1, 0, 2000000078, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (118937404, 0, 0, 2, 0, 2000000079, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`waypoint_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`, `guid`)
VALUES (118937405, 0, 2, 169, 69, 0, 0, 0, 0, 0, 0);

COMMIT;
