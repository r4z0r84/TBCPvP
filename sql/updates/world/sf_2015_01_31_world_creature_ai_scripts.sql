NSERT INTO `creature_ai_scripts` VALUES (2141401, 21414, 11, 0, 100, 6, 0, 0, 0, 0, 11, 38833, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Negaton Field - Cast Negaton Field on spawn');
UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16' WHERE (`entry`='21414');
UPDATE `creature_ai_scripts` SET `event_type`='0' WHERE (`id`='2086701');
UPDATE `creature_ai_scripts` SET `event_type`='0' WHERE (`id`='2086702');
UPDATE `creature_ai_scripts` SET `action1_param2`='0' WHERE (`id`='2086705');
UPDATE `creature_ai_scripts` SET `action1_param2`='0' WHERE (`id`='2086706');
