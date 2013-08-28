// Spectator gossip
// Smolderforge 2013

#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "ArenaTeam.h"
#include "ScriptPCH.h"
#include "Chat.h"
#include "GameEventMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"

#define GOSSIP_SENDER   11

std::string StrToInt(int number) // I have NO idea how to do this in another way...
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

bool GossipHello_spectator(Player *player, Creature *_Creature)
{
    if (player->InBattleGroundQueue())
    {
        player->GetSession()->SendNotification("Please leave queue(s) before spectating.");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,  "2v2 Rated"              , ARENA_TYPE_2v2, 0); // start listing at arena 0
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,  "3v3 Rated"              , ARENA_TYPE_3v3, 0);
    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,  "5v5 Rated"              , ARENA_TYPE_5v5, 0);
    player->PlayerTalkClass->SendGossipMenu(66, creature->GetGUID());

    return true;
}

void SendSubMenu_spectator(Player *player, Creature *_Creature, uint32 arenaType, uint32 action)
{
    uint32 totalcount = sBattleGroundMgr->GetBattleGroundsCount();
    uint32 roomLeft = GOSSIP_MAX_MENU_ITEMS-3; // were gonna be cheap and always add a Back, Next and Refresh button, no matter if its needed or not.

    if (action < 0 || action >= totalcount) // reset to start of list if passed end or begin
        action = 0;

    BattleGroundSet::iterator itr = sBattleGroundMgr->GetBattleGroundsBegin();

    for(uint32 i = 0; i < action; i++) // is there any other way to increase a iterator by X amount?
        itr++;

    while(itr != sBattleGroundMgr->GetBattleGroundsEnd() && roomLeft > 0)
    {
        BattleGround * bg = itr->second;
        if (bg->GetArenaType() == arenaType && bg->isRated() && bg->GetStatus() == STATUS_IN_PROGRESS && bg->GetPlayersCountByTeam(ALLIANCE) + bg->GetPlayersCountByTeam(HORDE) > 0)
        {
            ArenaTeam *goldTeam = sObjectMgr->GetArenaTeamById(bg->GetArenaTeamIdForTeam(ALLIANCE));
            ArenaTeam *greenTeam = sObjectMgr->GetArenaTeamById(bg->GetArenaTeamIdForTeam(HORDE));
            if (!greenTeam || !goldTeam)
                continue;

            if (arenaType == 2)
            {
                uint8 prvni = 0;
                uint8 druhy = 0;

                uint8 prvniz = 0;
                uint8 druhyz = 0;
                std::string jmenoprvni = "???";
                std::string jmenodruhy = "???";
                std::string jmenoprvniz = "???";
                std::string jmenodruhyz = "???";
                for (BattleGround::BattleGroundPlayerMap::const_iterator itr2 = bg->GetPlayers().begin(); itr2 != bg->GetPlayers().end(); ++itr2)
                {
                    if (Player *plr = sObjectMgr->GetPlayer(itr2->first))
                        if (plr->GetArenaTeamId(0) == goldTeam->GetId())
                        {
                            if (prvni == 0)
                            {
                                prvni = plr->getClass();
                                jmenoprvni = plr->GetName();
                            }
                            else if (druhy == 0)
                            {
                                druhy = plr->getClass();
                                jmenodruhy = plr->GetName();
                            }
                        }
                        else if (plr->GetArenaTeamId(0) == greenTeam->GetId())
                        {
                            if (prvniz == 0)
                            {
                                prvniz = plr->getClass();
                                jmenoprvniz = plr->GetName();
                            }
                            else if (druhyz == 0)
                            {
                                druhyz = plr->getClass();
                                jmenodruhyz = plr->GetName();
                            }
                        }
                }
                std::string classa1;
                std::string classa2;
                std::string classa3;
                std::string classa4;
                switch(prvni)
                {
                case CLASS_WARRIOR:
                    classa1 = "War";
                    break;
                case CLASS_PALADIN:
                    classa1 = "Pal";
                    break;
                case CLASS_ROGUE:
                    classa1 = "Rog";
                    break;
                case CLASS_PRIEST:
                    classa1 = "Pri";
                    break;
                case CLASS_SHAMAN:
                    classa1 = "Sha";
                    break;
                case CLASS_MAGE:
                    classa1 = "Mag";
                    break;
                case CLASS_WARLOCK:
                    classa1 = "Loc";
                    break;
                case CLASS_DRUID:
                    classa1 = "Dru";
                    break;
                case CLASS_HUNTER:
                    classa1 = "Hun";
                    break;
                default:
                    classa1 = "???";
                    break;
                }
                switch(druhy)
                {
                case CLASS_WARRIOR:
                    classa2 = "War";
                    break;
                case CLASS_PALADIN:
                    classa2 = "Pal";
                    break;
                case CLASS_ROGUE:
                    classa2 = "Rog";
                    break;
                case CLASS_PRIEST:
                    classa2 = "Pri";
                    break;
                case CLASS_SHAMAN:
                    classa2 = "Sha";
                    break;
                case CLASS_MAGE:
                    classa2 = "Mag";
                    break;
                case CLASS_WARLOCK:
                    classa2 = "Loc";
                    break;
                case CLASS_DRUID:
                    classa2 = "Dru";
                    break;
                case CLASS_HUNTER:
                    classa2 = "Hun";
                    break;
                default:
                    classa2 = "???";
                    break;
                }
                switch(prvniz)
                {
                case CLASS_WARRIOR:
                    classa3 = "War";
                    break;
                case CLASS_PALADIN:
                    classa3 = "Pal";
                    break;
                case CLASS_ROGUE:
                    classa3 = "Rog";
                    break;
                case CLASS_PRIEST:
                    classa3 = "Pri";
                    break;
                case CLASS_SHAMAN:
                    classa3 = "Sha";
                    break;
                case CLASS_MAGE:
                    classa3 = "Mag";
                    break;
                case CLASS_WARLOCK:
                    classa3 = "War";
                    break;
                case CLASS_DRUID:
                    classa3 = "Dru";
                    break;
                case CLASS_HUNTER:
                    classa3 = "Hun";
                    break;
                default:
                    classa3 = "???";
                    break;
                }
                switch(druhyz)
                {
                case CLASS_WARRIOR:
                    classa4 = "War";
                    break;
                case CLASS_PALADIN:
                    classa4 = "Pal";
                    break;
                case CLASS_ROGUE:
                    classa4 = "Rog";
                    break;
                case CLASS_PRIEST:
                    classa4 = "Pri";
                    break;
                case CLASS_SHAMAN:
                    classa4 = "Sha";
                    break;
                case CLASS_MAGE:
                    classa4 = "Mag";
                    break;
                case CLASS_WARLOCK:
                    classa4 = "Loc";
                    break;
                case CLASS_DRUID:
                    classa4 = "Dru";
                    break;
                case CLASS_HUNTER:
                    classa4 = "Hun";
                    break;
                default:
                    classa4 = "???";
                    break;
                }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, jmenoprvni + " " + classa1 + " " + jmenodruhy + " " + classa2 + " (" + StrToInt(goldTeam->GetRating()) + ") VS " + 
                    jmenoprvniz + " " + classa3 + " " + jmenodruhyz + " " + classa4 + " (" + StrToInt(greenTeam->GetRating()) + ")",
                    GOSSIP_SENDER, itr->first);
            }
            else
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, goldTeam->GetName() + " (" + StrToInt(goldTeam->GetRating()) + ") VS " + 
                greenTeam->GetName() + " (" + StrToInt(greenTeam->GetRating()) + ")",
                GOSSIP_SENDER, itr->first);
            // Looks like: GoldTeamName (rating) VS GreenTeamName (rating)
            roomLeft--;
        }
        itr++;
    }
    if (totalcount > 0)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reload", arenaType, action);

    player->SEND_GOSSIP_MENU(totalcount > 0 ? DEFAULT_GOSSIP_MESSAGE : 67 ,_Creature->GetGUID());
}

void SendMenu_spectator(Player *player, Creature *_Creature, uint32 action)
{
    if (player->InBattleGroundQueue())
    {
        player->GetSession()->SendNotification("Please leave queue(s) before spectating.");
        return;
    }
    if (player->IsMounted())
    {
        player->GetSession()->SendNotification("You are mounted. You must dismount first.");
        return;
    }
    player->CLOSE_GOSSIP_MENU();
    BattleGround *bg = sBattleGroundMgr->GetBattleGround(action);
    if (bg && bg->isArena() && bg->isRated() && bg->GetStatus() == STATUS_IN_PROGRESS && bg->GetPlayersCountByTeam(ALLIANCE) + bg->GetPlayersCountByTeam(HORDE) > 0)
    {
        bg->AddSpectator(player);
        player->SetBattleGroundId(action);
        player->SetBattleGroundEntryPoint();
        player->setSpectator(true);
        player->SetSpeed(MOVE_RUN, 3, true);
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED);
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        player->RemovePet(NULL, PET_SAVE_NOT_IN_SLOT, true);
        if (player->GetGroup())
            player->RemoveFromGroup();
        bg->HandlePlayerUnderMap(player); // very cheap but awesome working way to teleport the player to the middle of the bg

        WorldPacket data;
        sBattleGroundMgr->BuildBattleGroundStatusPacket(&data, bg, 0, 0, STATUS_IN_PROGRESS, 0, 0, 0, 0);
        player->GetSession()->SendPacket(&data); // make the client generate a PvP icon on the minimap, allowing the player to leave.
    }
    else
    {
        ChatHandler(player).PSendSysMessage("An error occurred while trying to connect to the game (probably just ended).");
    }
}

bool GossipSelect_spectator(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch (sender)
    {
        case ARENA_TYPE_2v2:            SendSubMenu_spectator(player, _Creature, sender, action); break;
        case ARENA_TYPE_3v3:            SendSubMenu_spectator(player, _Creature, sender, action); break;
        //case ARENA_TYPE_5v5:            SendSubMenu_spectator(player, _Creature, sender, action); break;
        case GOSSIP_SENDER:             SendMenu_spectator(player, _Creature, action); break;
    }
    return true;
}

void AddSC_spectator()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="spectator";
    newscript->pGossipHello = &GossipHello_spectator;
    newscript->pGossipSelect = &GossipSelect_spectator;
    newscript->RegisterSelf();
}
