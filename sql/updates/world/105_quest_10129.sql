DELETE FROM `spell_script_target` WHERE `entry` = 33655;
INSERT INTO `spell_script_target` VALUES (33655, 1, 19291), (33655, 1, 19292);
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_q_10129_trigger' WHERE `entry` IN (19291, 19292);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (19291, 19292);
