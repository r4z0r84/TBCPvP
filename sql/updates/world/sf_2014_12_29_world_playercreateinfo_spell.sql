/* Update character ID to bit mask to allow usage of multiclass as well as univeral 0
   Key: http://collab.kpsn.org/display/tc/ChrClasses
        http://collab.kpsn.org/display/tc/ChrRaces
*/

ALTER TABLE playercreateinfo_spell CHANGE class classmask INT(10);
ALTER TABLE playercreateinfo_spell CHANGE race racemask INT(10);
ALTER TABLE playercreateinfo_spell_custom CHANGE class classmask INT(10);
ALTER TABLE playercreateinfo_spell_custom CHANGE race racemask INT(10);

UPDATE `playercreateinfo_spell` SET `classmask`='1024' WHERE (`classmask`='11'); /* Druid */
UPDATE `playercreateinfo_spell` SET `classmask`='256' WHERE (`classmask`='9'); /* Warlock */
UPDATE `playercreateinfo_spell` SET `classmask`='128' WHERE (`classmask`='8'); /* Mage */
UPDATE `playercreateinfo_spell` SET `classmask`='64' WHERE (`classmask`='7'); /* Shaman */
UPDATE `playercreateinfo_spell` SET `classmask`='16' WHERE (`classmask`='5'); /* Priest */
UPDATE `playercreateinfo_spell` SET `classmask`='8' WHERE (`classmask`='4'); /* Rogue */
UPDATE `playercreateinfo_spell` SET `classmask`='4' WHERE (`classmask`='3'); /* Hunter */

UPDATE `playercreateinfo_spell` SET `racemask`='1024' WHERE (`racemask`='11'); /* Draenei */
UPDATE `playercreateinfo_spell` SET `racemask`='512' WHERE (`racemask`='10'); /* Blood Elf */
UPDATE `playercreateinfo_spell` SET `racemask`='128' WHERE (`racemask`='8'); /* Troll */
UPDATE `playercreateinfo_spell` SET `racemask`='64' WHERE (`racemask`='7'); /* Gnome */
UPDATE `playercreateinfo_spell` SET `racemask`='32' WHERE (`racemask`='6'); /* Tauren */
UPDATE `playercreateinfo_spell` SET `racemask`='16' WHERE (`racemask`='5'); /* Undead */
UPDATE `playercreateinfo_spell` SET `racemask`='8' WHERE (`racemask`='4'); /* Night Elf */
UPDATE `playercreateinfo_spell` SET `racemask`='4' WHERE (`racemask`='3'); /* Dwarf */

UPDATE `playercreateinfo_spell_custom` SET `classmask`='1024' WHERE (`classmask`='11'); /* Druid */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='256' WHERE (`classmask`='9'); /* Warlock */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='128' WHERE (`classmask`='8'); /* Mage */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='64' WHERE (`classmask`='7'); /* Shaman */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='16' WHERE (`classmask`='5'); /* Priest */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='8' WHERE (`classmask`='4'); /* Rogue */
UPDATE `playercreateinfo_spell_custom` SET `classmask`='4' WHERE (`classmask`='3'); /* Hunter */

UPDATE `playercreateinfo_spell_custom` SET `racemask`='1024' WHERE (`racemask`='11'); /* Draenei */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='512' WHERE (`racemask`='10'); /* Blood Elf */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='128' WHERE (`racemask`='8'); /* Troll */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='64' WHERE (`racemask`='7'); /* Gnome */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='32' WHERE (`racemask`='6'); /* Tauren */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='16' WHERE (`racemask`='5'); /* Undead */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='8' WHERE (`racemask`='4'); /* Night Elf */
UPDATE `playercreateinfo_spell_custom` SET `racemask`='4' WHERE (`racemask`='3'); /* Dwarf */
