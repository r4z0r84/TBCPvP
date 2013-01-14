-- Set targetable flag for Portals in quest 'Disrupt Their Reinforcements'
UPDATE `gameobject_template` SET `flags` = 32 WHERE `entry` IN (184289, 184290, 184414, 184415);