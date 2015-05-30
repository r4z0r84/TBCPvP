// TBC Dual Talent Specialization 
// by Itslovelol

#include "ScriptPCH.h"

bool GossipHello_custom_dualspec(Player *player, Creature *_Creature)
{
    uint8 specCount = player->GetSpecsCount();
    if (specCount < MAX_TALENT_SPECS)
    {
        // This fuction add's a menu item,
        // a - Icon Id
        // b - Text
        // c - Sender(this is to identify the current Menu with this item)
        // d - Action (identifys this Menu Item)
        // e - Text to be displayed in pop up box
        // f - Money value in pop up box
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "Purchase Dual Talent Specialization [1,000 Gold]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0, "Are you sure you would like to purchase your second specialization?", 10000000, false);
    }

    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << "[Activate] ";
        if (player->GetSpecName(i) == "NULL")
            specNameString << "(Unnamed)";
        else
            specNameString << player->GetSpecName(i);
        if (i == player->GetActiveSpec())
            specNameString << " <current>";
        else
            specNameString << "";
        player->ADD_GOSSIP_ITEM(0, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (1 + i));
    }

    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << "[Rename] ";
        if (player->GetSpecName(i) == "NULL")
            specNameString << "(Unnamed)";
        else
            specNameString << player->GetSpecName(i);
        if (i == player->GetActiveSpec())
            specNameString << " <current>";
        else
            specNameString << "";
        player->ADD_GOSSIP_ITEM_EXTENDED(0, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (10 + i), "", 0, true);
    }

    player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
    return true;
}

bool GossipSelect_custom_dualspec(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 0:
            if (player->GetMoney() < 10000000)
            {
                _Creature->Whisper("You don't have enough money to buy this!", player->GetGUID());
                break;
            }
            player->SetSpecsCount(player->GetSpecsCount() + 1);
            player->ModifyMoney(-10000000);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->ActivateSpec(0);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            player->ActivateSpec(1);
            break;
        default:
            break;
    }

    return true;
}

bool GossipSelectWithCode_custom_dualspec(Player* player, Creature* creature, uint32 sender, uint32 action, const char* sCode)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 10)
        player->SetSpecName(0, sCode);
    else if (action == GOSSIP_ACTION_INFO_DEF + 11)
        player->SetSpecName(1, sCode);

    player->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_custom_dualspec()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="custom_dualspec";
    newscript->pGossipHello = &GossipHello_custom_dualspec;
    newscript->pGossipSelect = &GossipSelect_custom_dualspec;
    newscript->pGossipSelectWithCode = &GossipSelectWithCode_custom_dualspec;
    newscript->RegisterSelf();
}
