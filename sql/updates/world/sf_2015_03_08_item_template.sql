-- Revert Query
UPDATE `item_template` SET `spellcooldown_1`='1000' WHERE (`entry`='23576');
-- Greater Ward of Shielding (5min cd)
UPDATE `item_template` SET `spellcooldown_1`='300000' WHERE (`entry`='23576');
