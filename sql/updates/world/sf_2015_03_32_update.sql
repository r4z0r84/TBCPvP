/*
Script created by Quest Data Compare at 23.03.2015 22:56:38
This script must be executed against @DATABASE on localhost
This script applies changes to @DATABASE to make it the same as skyfire_world on localhost
*/

SET @DATABASE := "";
USE `@DATABASE`;

START TRANSACTION;

UPDATE `@DATABASE`.`creature` SET `position_x` = 2495.7, `position_y` = 7353.11, `position_z` = 380.29, `orientation` = 5.374 WHERE `guid` = 74807;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2491.74, `position_y` = 7325.7, `position_z` = 369.262, `orientation` = 3.52005 WHERE `guid` = 79487;
UPDATE `@DATABASE`.`creature` SET `position_x` = 2492.8, `position_y` = 7315.87, `position_z` = 369.465, `orientation` = 2.73072 WHERE `guid` = 79497;

INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189369, 23257, 530, 1, 0, 23257, 2512.55, 7361.78, 380.726, 3.92163, 25, 0, 0, 9955, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189374, 22982, 530, 1, 0, 1687, 2514.56, 7355.03, 380.733, 2.86073, 25, 0, 0, 9250, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189377, 22982, 530, 1, 0, 1687, 2530.88, 7333.29, 373.444, 4.71543, 25, 0, 0, 9250, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189378, 22982, 530, 1, 0, 1687, 2539.7, 7322.77, 373.443, 3.14463, 25, 0, 0, 9250, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189379, 23257, 530, 1, 21184, 23257, 2538.94, 7311.83, 373.637, 2.18095, 25, 0, 0, 9955, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189380, 23257, 530, 1, 0, 23257, 2545.49, 7334.51, 373.423, 4.14444, 25, 0, 0, 9485, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES (1189381, 23257, 530, 1, 21182, 23257, 2501, 7332.49, 376.714, 5.53852, 25, 0, 0, 9720, 0, 0, 0);

INSERT INTO `@DATABASE`.`creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`)
VALUES (23257, 44787, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`)
VALUES (23334, 42555, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`)
VALUES (23392, 7460, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `@DATABASE`.`creature_template` SET `npcflag` = 3 WHERE `entry` = 23120;
UPDATE `@DATABASE`.`creature_template` SET `equipment_id` = 23257, `ScriptName` = 'npc_skyguard_windcharger' WHERE `entry` = 23257;
UPDATE `@DATABASE`.`creature_template` SET `equipment_id` = 23334 WHERE `entry` = 23334;
UPDATE `@DATABASE`.`creature_template` SET `equipment_id` = 23392 WHERE `entry` = 23392;
UPDATE `@DATABASE`.`creature_template` SET `ScriptName` = 'npc_skyhandler_irena' WHERE `entry` = 23413;

UPDATE `@DATABASE`.`gameobject` SET `orientation` = 0.705186, `rotation2` = 0.345332, `rotation3` = 0.93848 WHERE `guid` = 25034;

INSERT INTO `@DATABASE`.`gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`)
VALUES (8622499, 184133, 530, 1, 2511.54, 7346.5, 380.956, 0.0847232, 0, 0, 0.0423489, 0.999103, 25, 0, 1);

UPDATE `@DATABASE`.`npc_gossip` SET `textid` = 11057 WHERE `npc_guid` = 52535;

INSERT INTO `@DATABASE`.`npc_gossip` (`npc_guid`, `textid`)
VALUES (44257, 10842);

INSERT INTO `@DATABASE`.`npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`)
VALUES (10842, NULL, 'Hey, comrade. If you get yourself in good with the Skyguard, I can offer you a direct flight to our base, Blackwind Landing, in the Skethyl Mountains.$B$BDo you like my beautiful nether ray? It is lovely.', 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `@DATABASE`.`npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`)
VALUES (11057, 'Our Skyguard Aether-tech and her escort is studying the Bash''ir crystal forge. She needs help! Go to Bash''ir Landing, find the aether-tech and keep her safe!', NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0);

INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580306, '$N, Do you feel the need...the need for speed?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580305, 'With $N flying, the skies aren''t so friendly', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580304, 'They say that $N has never been shot down.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580303, 'I hear you fly without a parachute cloak,$N.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580302, 'With $N on the job, we have nothing to worry about.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580301, 'The list of Skyguard members is long and distinguished. $N tops that list.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);
INSERT INTO `@DATABASE`.`script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES (-1580300, 'Lady $N, what an unexpected pleasure, ma''am.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);

COMMIT;
