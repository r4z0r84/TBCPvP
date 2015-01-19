REPLACE INTO `command` (`name`, `security`, `help`)
VALUES
    ('tempevent teleport', 1, 'Usage: .tempevent teleport. Teleports all players in temporary event queue to set location.'),
    ('tempevent reset', 1, 'Usage: .tempevent reset. Resets all variables related to temporary event system so that a new one may be created.'),
    ('tempevent plimit', 1, 'Usage: .tempevent plimit $amount. Sets maximum player limit for temporary event.'),
    ('tempevent location', 1, 'Usage: .tempevent location. Sets the teleport location of the event to summon players to with the .tempevent teleport command.'),
    ('tempevent leave', 0, 'Usage: .tempevent leave. Leaves the temporary event player is apart of.'),
    ('tempevent join', 0, 'Usage: .tempevent join. Enter queue for an active temporary event. A Game Master will issue everyone in queue a summon once the event begins.'),
    ('tempevent info', 0, 'Usage: .tempevent info. Gives information about the current temporary event, if there is one.'),
    ('tempevent gminfo', 1, 'Not yet implemented.'),
    ('tempevent create', 1, 'Not yet implemented.'),
    ('tempevent active', 1, 'Usage: .tempevent active. Makes temporary event GM has prepared active so players may enter queue for it.');
