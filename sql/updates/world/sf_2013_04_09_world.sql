/* This should be a more retail like PPM rate for Omen of Clarity Druid Self Buff */

UPDATE `spell_proc_event` SET `ppmRate`=2.5 WHERE  `entry`=16864 LIMIT 1;

/* This will reduce the bonus damage that mangle(cat) gets from two points of savage fury from 380 to (correct) 317 */

DELETE FROM `spell_affect` WHERE  `entry`=16998 AND `effectId`=2 LIMIT 1;
DELETE FROM `spell_affect` WHERE  `entry`=16999 AND `effectId`=2 LIMIT 1;

UPDATE `spell_affect` SET `effectId`=2 WHERE  `entry`=16998 AND `effectId`=0 LIMIT 1;
UPDATE `spell_affect` SET `effectId`=2 WHERE  `entry`=16999 AND `effectId`=0 LIMIT 1;

/* Mace Spec will now use the post patch 2.3 proc chance */

UPDATE `spell_proc_event` SET `ppmRate`=0.28 WHERE  `entry`=12284 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=0.57 WHERE  `entry`=12701 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=0.85 WHERE  `entry`=12702 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=1.14 WHERE  `entry`=12703 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=1.42 WHERE  `entry`=12704 LIMIT 1;
