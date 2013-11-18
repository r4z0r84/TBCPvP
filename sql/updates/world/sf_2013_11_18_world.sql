--1: Fix retribution T6 set bonus
INSERT INTO `spell_proc_event` (`entry`, `ppmRate`) VALUES (38427, 11);

--2: Fix glaive of the pit PPM
UPDATE `item_template` SET `spellppmRate_1`=4.0 WHERE  `entry`=28774 LIMIT 1;

--3: Fix stormherald and deep thunder PPM
UPDATE `item_template` SET `spellppmRate_1`=0.35 WHERE  `entry`=28442 LIMIT 1;
UPDATE `item_template` SET `spellppmRate_1`=0.35 WHERE  `entry`=28441 LIMIT 1;

--4: Re-enable stormherald Stun
DELETE FROM `spell_disabled` WHERE  `entry`=34510 LIMIT 1;

--5: Fix Rod of the Sun King PPM
UPDATE `item_template` SET `spellppmRate_1`=1.5 WHERE  `entry`=29996 LIMIT 1;

--6: Re-enable Rod of the Sun King proc
DELETE FROM `spell_disabled` WHERE  `entry`=36070 LIMIT 1;

--7: Vindication PPM fix
UPDATE `spell_proc_event` SET `ppmRate`=3.0 WHERE  `entry`=26021 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=3.0 WHERE  `entry`=26016 LIMIT 1;
UPDATE `spell_proc_event` SET `ppmRate`=3.0 WHERE  `entry`=9452 LIMIT 1;

--8: Shard of Azzinoth should now have a correct ppm
UPDATE `item_template` SET `spellppmRate_2`=2.5 WHERE  `entry`=32471 LIMIT 1;

--9: Shard of Azzinoth summon should now cause the correct amount of fire damage
UPDATE `creature_template` SET `mindmg`=99, `maxdmg`=156, `dmgschool`=2, `AIName`='CombatAI' WHERE  `entry`=23192 LIMIT 1;

--10: Seal of Vengeance PPM fix
UPDATE `spell_proc_event` SET `ppmRate`=28 WHERE  `entry`=31801 LIMIT 1;

--11: Shiv criticals will now trigger Seal Fate
UPDATE `spell_proc_event` SET `SpellFamilyMask`=27388806408 WHERE  `entry`=14195 LIMIT 1;
UPDATE `spell_proc_event` SET `SpellFamilyMask`=27388806408 WHERE  `entry`=14194 LIMIT 1;
UPDATE `spell_proc_event` SET `SpellFamilyMask`=27388806408 WHERE  `entry`=14193 LIMIT 1;
UPDATE `spell_proc_event` SET `SpellFamilyMask`=27388806408 WHERE  `entry`=14190 LIMIT 1;
UPDATE `spell_proc_event` SET `SpellFamilyMask`=27388806408 WHERE  `entry`=14186 LIMIT 1;

--12: Syphon of the Nathrezim PPM
UPDATE `item_template` SET `spellppmRate_2`=7 WHERE  `entry`=32262 LIMIT 1;

--13: Crusader PPM
INSERT INTO `spell_enchant_proc_data` (`entry`, `PPMChance`) VALUES (1900, 2);

--14: Stonebreaker's totem 
UPDATE `spell_proc_event` SET `CustomChance`=75 WHERE  `entry`=43748 LIMIT 1;

--15: Fixed totem of the Thunderhead mana regeneration proc with Watershield
UPDATE `spell_affect` SET `SpellFamilyMask`=137438953472 WHERE  `entry`=34318 AND `effectId`=0 LIMIT 1;

--16: Updated Fists of Fury ppm
UPDATE `spell_proc_event` SET `ppmRate`=4 WHERE  `entry`=41989 LIMIT 1;

--17: Updated Frostbrand PPM
--(wowhead thread did not take into account offhand misschance in their calculations)
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=2635 LIMIT 1;
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=1668 LIMIT 1;
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=1667 LIMIT 1;
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=524 LIMIT 1;
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=12 LIMIT 1;
UPDATE `spell_enchant_proc_data` SET `PPMChance`=11 WHERE  `entry`=2 LIMIT 1;

--18: Fixed Blackened Naru Silver Proc mechanics
INSERT INTO `spell_proc_event` (`entry`, `Cooldown`) VALUES (45355, 20);
