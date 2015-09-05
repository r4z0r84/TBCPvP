-- Delete Kilrek
DELETE FROM `creature` WHERE (`guid`='85371');
-- Correct spawn position from Terestian Illhoof
UPDATE `creature` SET `position_x`='-11241', `position_y`='-1704.54', `position_z`='179.237', `orientation`='0.708644' WHERE (`guid`='56322');

-- Set correct XYZ entry for portals
DELETE FROM `spell_target_position` WHERE `id` IN (30171, 30179);
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`) VALUES ('30171', '532', '-11249.6933', '-1704.61023');
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`) VALUES ('30179', '532', '-11242.116', '-1713.33325');

-- Kilrek emote
DELETE FROM `script_texts` WHERE (`entry`='-1532115');
INSERT INTO `script_texts` (`entry`, `content_default`, `type`, `comment`) VALUES ('-1532115', 'shrieks in pain and points at his master.', '2', 'KILREK_EMOTE_DEATH');