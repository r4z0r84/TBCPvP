UPDATE `character_pet` SET `trainpoint`='350' WHERE (`PetType`='1');
UPDATE `character_pet` SET `teachspelldata`='' WHERE (`PetType`='1');
-- DELETE FROM `pet_spell` WHERE ( SELECT GUID FROM character_pet WHERE PetType = 1); -- Don't know SQL 