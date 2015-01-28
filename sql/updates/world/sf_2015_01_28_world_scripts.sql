DELETE FROM `spell_target_position` WHERE `id`=26448;
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(26448,1,7581.01,-2225.35,473.64,1.80);

DELETE FROM spell_scripts WHERE id=26373;
DELETE FROM spell_linked_spell WHERE spell_trigger=26373;
INSERT INTO spell_linked_spell VALUES (26373,26448,0,'Lunar Festival Invitation - Teleport Moonglade');

-- Lunar festival: Rocket Clusters placed near Omen's summon place (Moonglade)
SET @CLUSTER := 180874;
SET @LUNARFESTIVAL := 7;

DELETE FROM `gameobject` WHERE `id`=@CLUSTER AND `guid` IN (101000,101001);
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`position_x`,`position_y`,`position_z`) VALUES
(101000,@CLUSTER,1,1,7531.662,-2851.228,458.9172),
(101001,@CLUSTER,1,1,7561.145,-2872.45,461.0998);

DELETE FROM `game_event_gameobject` WHERE `guid` IN (101000,101001) AND `event`=@LUNARFESTIVAL;
INSERT INTO `game_event_gameobject` (`event`,`guid`) VALUES
(@LUNARFESTIVAL,101000),
(@LUNARFESTIVAL,101001);

-- Update all targeting stuff for Fireworks and Rocket clusters
DELETE FROM  `spell_script_target` WHERE `entry` IN (26294,26295,26333,26334,26336,26337,26338,26488,26490,26517,26521,26344,26347,26345,26348,26349,26351,26352,26354,26355,26356);
INSERT INTO  `spell_script_target`(`entry`,`type`,`targetEntry`) VALUES
(26294,0,180771),
(26294,0,180850),
(26294,0,180868),
(26295,0,180771),
(26295,0,180850),
(26295,0,180868),
(26333,0,180771),
(26333,0,180850),
(26333,0,180868),
(26334,0,180771),
(26334,0,180850),
(26334,0,180868),
(26336,0,180771),
(26336,0,180850),
(26336,0,180868),
(26337,0,180771),
(26337,0,180850),
(26337,0,180868),
(26338,0,180771),
(26338,0,180850),
(26338,0,180868),
(26488,0,180772),
(26488,0,180859),
(26488,0,180869),
(26488,0,180874),
(26490,0,180772),
(26490,0,180859),
(26490,0,180869),
(26490,0,180874),
(26517,0,180772),
(26517,0,180859),
(26517,0,180869),
(26517,0,180874),
(26521,0,180772),
(26521,0,180859),
(26521,0,180869),
(26521,0,180874),
(26347,0,180771),
(26347,0,180850),
(26347,0,180868),
(26344,0,180771),
(26344,0,180850),
(26344,0,180868),
(26345,0,180771),
(26345,0,180850),
(26345,0,180868),
(26348,0,180771),
(26348,0,180850),
(26348,0,180868),
(26349,0,180771),
(26349,0,180850),
(26349,0,180868),
(26351,0,180771),
(26351,0,180850),
(26351,0,180868),
(26352,0,180771),
(26352,0,180850),
(26352,0,180868),
(26354,0,180771),
(26354,0,180850),
(26354,0,180868),
(26355,0,180771),
(26355,0,180850),
(26355,0,180868),
(26356,0,180771),
(26356,0,180850),
(26356,0,180868);

UPDATE `creature_template` SET `ScriptName`='npc_firework' WHERE `entry` IN (
15882,
15883,
15918,
15872,
15873,
15874,
15875,
15876,
15877,
15879,
15880,
15881,
15884,
15885,
15886,
15887,
15888,
15889,
15890,
15911,
15912,
15913,
15914,
15915,
15916);

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26304', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26304', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26304', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26304', '180874');

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26325', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26325', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26325', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26325', '180874');

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26327', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26327', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26327', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26327', '180874');

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26490', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26490', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26490', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26490', '180874');

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26517', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26517', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26517', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26517', '180874');

REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26521', '180772');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26521', '180859');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26521', '180869');
REPLACE INTO `spell_script_target` (`entry`, `targetEntry`) VALUES ('26521', '180874');


REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `size`, `data1`, `data2`, `data3`, `data5`, `data11`, `data14`) VALUES ('180877', '6', '327', 'Elune\'s Blessing TRAP QUESTCREDIT', '14', '0.01', '255', '8', '26394', '1', '1', '1');

DELETE FROM `creature_template_addon` WHERE (`entry`IN(15902,15466));
INSERT INTO `creature_template_addon`(`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(15466,0,0,0,0,0,17327), -- Add spirit particles to Omen minions
(15902,0,0,0,0,0,50236); -- Add Spotlight aura to Giant Spotlight (summoned by 26392 on Omen's death)