INSERT INTO `command` (`name`, `security`, `help`)
VALUES
	('character mute', 1, 'Syntax is: .character mute\r\nApplies a public-communication mute to the player, disallowing them from speaking in say, yell, whisper, battleground, channels, and emotes.');

INSERT INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
	(818, 'Muted character %s. They will no longer be able to speak in say, yell, whisper, channels, battleground, or emotes. Guild, officer, group, and raid are permitted.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
	(819, 'Unmuted character %s. They will now be able to talk freely.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
