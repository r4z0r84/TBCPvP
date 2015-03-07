DELETE FROM `creature` WHERE `guid` IN (72693, 86102, 86101);
INSERT INTO `creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `curhealth`) VALUES ('72693', '20563', '530', '-4585.18', '1670.21', '175.736', '0.10472', '300', '0', '369000');
UPDATE `creature` SET `spawndist`='0', `MovementType`='0' WHERE `guid` IN (75469, 75468);
UPDATE `creature_template` SET `ScriptName`='npc_grand_commander_ruusk' WHERE (`entry`='20563');
