// Race Changer NPC
// Smolderforge 2013

#include "ScriptPCH.h"

bool GossipHello_racechanger(Player *player, Creature *_Creature)
{
    player->ADD_GOSSIP_ITEM(0, "Alliance", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
    player->ADD_GOSSIP_ITEM(0, "Horde",    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);

    player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
    return true;
}

bool GossipSelect_racechanger(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 101:
        {
            switch (player->getClass())
            {
                case CLASS_WARRIOR:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Dwarf",     GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(0, "Night Elf", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(0, "Gnome",     GOSSIP_SENDER_MAIN, 7);
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_PALADIN:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Dwarf",     GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_HUNTER:
                    player->ADD_GOSSIP_ITEM(0, "Dwarf",     GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(0, "Night Elf", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_ROGUE:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Dwarf",     GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(0, "Night Elf", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(0, "Gnome",     GOSSIP_SENDER_MAIN, 7);
                    break;
                case CLASS_PRIEST:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Dwarf",     GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(0, "Night Elf", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_SHAMAN:
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_MAGE:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Gnome",     GOSSIP_SENDER_MAIN, 7);
                    player->ADD_GOSSIP_ITEM(0, "Draenei",   GOSSIP_SENDER_MAIN, 11);
                    break;
                case CLASS_WARLOCK:
                    player->ADD_GOSSIP_ITEM(0, "Human",     GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(0, "Gnome",     GOSSIP_SENDER_MAIN, 7);
                    break;
                case CLASS_DRUID:
                    player->ADD_GOSSIP_ITEM(0, "Night Elf", GOSSIP_SENDER_MAIN, 4);
                    break;
            }

            player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
            break;
        }

        case GOSSIP_ACTION_INFO_DEF + 202:
        {
            switch (player->getClass())
            {
                case CLASS_WARRIOR:
                    player->ADD_GOSSIP_ITEM(0, "Orc",       GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(0, "Undead",    GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(0, "Tauren",    GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    break;
                case CLASS_PALADIN:
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_HUNTER:
                    player->ADD_GOSSIP_ITEM(0, "Orc",       GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(0, "Tauren",    GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_ROGUE:
                    player->ADD_GOSSIP_ITEM(0, "Orc",       GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(0, "Undead",    GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_PRIEST:
                    player->ADD_GOSSIP_ITEM(0, "Undead",    GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_SHAMAN:
                    player->ADD_GOSSIP_ITEM(0, "Orc",       GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(0, "Tauren",    GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    break;
                case CLASS_MAGE:
                    player->ADD_GOSSIP_ITEM(0, "Undead",    GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(0, "Troll",     GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_WARLOCK:
                    player->ADD_GOSSIP_ITEM(0, "Orc",       GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(0, "Undead",    GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(0, "Blood Elf", GOSSIP_SENDER_MAIN, 10);
                    break;
                case CLASS_DRUID:
                    player->ADD_GOSSIP_ITEM(0, "Tauren",    GOSSIP_SENDER_MAIN, 6);
                    break;
            }

            player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
            break;
        }
        default:
            player->ChangeRace(player, action);
            break;
    }

    return true;
}

void AddSC_racechanger()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="racechanger";
    newscript->pGossipHello =  &GossipHello_racechanger;
    newscript->pGossipSelect = &GossipSelect_racechanger;
    newscript->RegisterSelf();
}
