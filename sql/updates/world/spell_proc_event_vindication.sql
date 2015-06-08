INSERT INTO `spell_proc_event` (`entry`, `procFlags`, `procEx`) VALUES ('9452', '20', '1024');
INSERT INTO `spell_proc_event` (`entry`, `procFlags`, `procEx`) VALUES ('26016', '20', '1024');
INSERT INTO `spell_proc_event` (`entry`, `procFlags`, `procEx`) VALUES ('26021', '20', '1024');

UPDATE `spell_proc_event` SET `procFlags`='20', `procEx`='1024' WHERE (`entry`='9452');
UPDATE `spell_proc_event` SET `procFlags`='20', `procEx`='1024' WHERE (`entry`='26016');
UPDATE `spell_proc_event` SET `procFlags`='20', `procEx`='1024' WHERE (`entry`='26021');
