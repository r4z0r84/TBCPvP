UPDATE `instance_template` SET `script` = 'instance_slave_pens' WHERE `map` = 547;
UPDATE `gameobject_template` SET `flags` = 0x00000004 WHERE `entry` = 182094;
UPDATE `creature_template` SET `ScriptName` = 'npc_naturalist', `AIName` = '' WHERE `entry` = 17893;
