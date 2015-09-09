-- Make Infernal Relay fly
UPDATE `creature_template` SET `InhabitType`='4' WHERE (`entry`='17645');
-- Remove wrong Infernal Relay NPC
DELETE FROM `creature` WHERE (`guid`='63370');
-- Correct location for Infernal Relay NPC
UPDATE `creature` SET `position_x`='-10923.7', `position_y`='-2045.89', `position_z`='305.293', `orientation`='2', `spawntimesecs`='2000' WHERE (`guid`='63371');
