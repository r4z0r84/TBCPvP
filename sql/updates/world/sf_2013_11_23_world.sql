--Fix fiery weapon PPM
INSERT INTO `spell_enchant_proc_data` (`entry`, `PPMChance`) VALUES (803, 4);
--Romulo's Poison
UPDATE `spell_proc_event` SET `ppmRate`=2.5 WHERE  `entry`=34586 LIMIT 1;
