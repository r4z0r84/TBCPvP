// Template NPC
// Tournament Realm
// Template by Robin

#include "ScriptPCH.h"
#include "beastmaster.h"

void AddTrinketTabardShirt(Player *player)
{
    // general defines
    uint32 team = player->GetTeam();
    uint32 trinketID_h = 37865;
    uint32 trinketID_a = 37864;
    uint32 guildtabard = 5976;
    uint32 shirt = 4333;

    if (team == HORDE)
        player->StoreNewItemInBestSlots(trinketID_h, 1);
    else
        player->StoreNewItemInBestSlots(trinketID_a, 1);

    player->StoreNewItemInBestSlots(guildtabard, 1);
    player->StoreNewItemInBestSlots(shirt, 1);
}

void AddEnchantment(Player *pPlayer, Item *pItem, uint32 enchantid)
{
    if (!pPlayer || !pItem || !enchantid)
        return;

    // remove old enchanting before applying new if equipped
    pPlayer->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, false);
    pItem->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);

    // add new enchanting if equipped
    pPlayer->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, true);
}

void AddSocket(Player *pPlayer, Item *pItem, uint32 enchantid_1, uint32 enchantid_2, uint32 enchantid_3)
{
    if (!pPlayer || !pItem)
        return;

    //remove ALL enchants
    for (uint32 enchant_slot = SOCK_ENCHANTMENT_SLOT; enchant_slot < SOCK_ENCHANTMENT_SLOT + 3; ++enchant_slot)
        pPlayer->ApplyEnchantment(pItem, EnchantmentSlot(enchant_slot), false);

    pItem->SetEnchantment(EnchantmentSlot(SOCK_ENCHANTMENT_SLOT), enchantid_1, 0, 0);
    pItem->SetEnchantment(EnchantmentSlot(SOCK_ENCHANTMENT_SLOT_2), enchantid_2, 0, 0);
    pItem->SetEnchantment(EnchantmentSlot(SOCK_ENCHANTMENT_SLOT_3), enchantid_3, 0, 0);

    for (uint32 enchant_slot = SOCK_ENCHANTMENT_SLOT; enchant_slot < SOCK_ENCHANTMENT_SLOT + 3; ++enchant_slot)
        pPlayer->ApplyEnchantment(pItem, EnchantmentSlot(enchant_slot), true);
}


bool GossipHello_npc_gossipgear(Player *player, Creature *_Creature)
{
    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
    {
        Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);

        if (itemTarget)
        {
            if (player->GetZoneId() == 721)
            {
                player->TeleportTo(530, -1837.1394, 5419.9858, -12.428, 2.789);
                return true;
            }

            player->GetSession()->SendNotification("Please unequip ALL items before you try to talk to me.");
            return true;
        }
    }

    // check if already in queue
    if (player->InBattleGroundQueue())
    {
        player->GetSession()->SendNotification("Please leave ALL queues before try to talk to me.");
        return true;
    }

    switch (player->getClass())
    {
    case CLASS_WARRIOR:
        player->ADD_GOSSIP_ITEM(0, "Arms (with Sweeping Strikes)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
        player->ADD_GOSSIP_ITEM(0, "Arms (with Endless Rage)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
        player->ADD_GOSSIP_ITEM(0, "Arms (with Flurry)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);
        //player->ADD_GOSSIP_ITEM(0, "Fury", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
        //player->ADD_GOSSIP_ITEM(0, "Protection", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);
        break;
    case CLASS_PALADIN:
        player->ADD_GOSSIP_ITEM(0, "Holy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 201);
        //player->ADD_GOSSIP_ITEM(0, "Protection", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);
        player->ADD_GOSSIP_ITEM(0, "Retribution", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 203);
        break;
    case CLASS_HUNTER:
        player->ADD_GOSSIP_ITEM(0, "Marksmanship", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 301);
        player->ADD_GOSSIP_ITEM(0, "Beast Mastery", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 302);
        player->ADD_GOSSIP_ITEM(0, "Survival", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 303);
        break;
    case CLASS_ROGUE:
        player->ADD_GOSSIP_ITEM(0, "Mutilate", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 401);
        player->ADD_GOSSIP_ITEM(0, "Combat (Deep)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 402);
        player->ADD_GOSSIP_ITEM(0, "Combat (with Hemorrhage)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 404);
        player->ADD_GOSSIP_ITEM(0, "Shadowstep", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 403);
        break;
    case CLASS_PRIEST:
        player->ADD_GOSSIP_ITEM(0, "Discipline (defensiv)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 501);
        player->ADD_GOSSIP_ITEM(0, "Discipline (agressiv)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 503);
        player->ADD_GOSSIP_ITEM(0, "Shadow", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 502);
        break;
    case CLASS_SHAMAN:
        player->ADD_GOSSIP_ITEM(0, "Elemental", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 601);
        player->ADD_GOSSIP_ITEM(0, "Enhancement", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 602);
        player->ADD_GOSSIP_ITEM(0, "Restoration (with Mana Tide Totem)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 603);
        player->ADD_GOSSIP_ITEM(0, "Restoration (with Improved Healing Wave", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 604);
        break;
    case CLASS_MAGE:
        player->ADD_GOSSIP_ITEM(0, "Frost", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 701);
        player->ADD_GOSSIP_ITEM(0, "Fire (with Improved Counterspell", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 702);
        player->ADD_GOSSIP_ITEM(0, "Fire (with Icy Veins)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 703);
        break;
    case CLASS_WARLOCK:
        player->ADD_GOSSIP_ITEM(0, "Affliction", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 801);
        player->ADD_GOSSIP_ITEM(0, "Siphon Life / Soul Link", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 803);
        player->ADD_GOSSIP_ITEM(0, "Destruction", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 802);
        break;
    case CLASS_DRUID:
        player->ADD_GOSSIP_ITEM(0, "Balance (with Nature's Swiftness)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 901);
        player->ADD_GOSSIP_ITEM(0, "Balance (with Treants)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 902);
        player->ADD_GOSSIP_ITEM(0, "Feral Combat (Cat)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 903);
        player->ADD_GOSSIP_ITEM(0, "Restoration (Deep)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 904);
        player->ADD_GOSSIP_ITEM(0, "Restoration (Dreamstate)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 905);
        break;
    }

    player->ADD_GOSSIP_ITEM(0, "[Continue to mall]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1000);

    player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
    return true;
}


bool GossipSelect_npc_gossipgear(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    bool isVip = player->GetSession()->GetSecurity() >= 1;
    switch (action)
    {
    case GOSSIP_ACTION_INFO_DEF + 101: // Warrior - Arms
    case GOSSIP_ACTION_INFO_DEF + 102:
    case GOSSIP_ACTION_INFO_DEF + 103:
    {
        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 arrayWar_arms_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3012, 2658, 2647, 684, 2931, 2931, 0, 0, 368, 2667, 0, 0, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 arrayWar_arms_sockets[19][3] = {
            { 2829, 3139, 0 },
            { 3139, 0, 0 },
            { 3115, 3139, 0 },
            { 0, 0, 0 },
            { 3115, 3115, 3139 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3139, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        if (action == GOSSIP_ACTION_INFO_DEF + 101) // Sweeping Strikes
        {
            // Add all talents spells (max rank wich should be learned) here, dont care wich first
            uint32 arrayWar_arms_talents[] = { 16466, 12962, 12296, 12290, 12867, 12712, 16494, 12292, 12704, 23695, 29889, 12294, 29836, 29838, 12856, 12837, 12322, 16492, 12318, 12323, 13048, 20505, 12328, 12677 };
            uint32 countWar_arms_talents = 24; // talent spell count from above

            // wipe talents
            player->resetTalents(true);
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < countWar_arms_talents; talent_i++)
            {
                player->learnSpell(arrayWar_arms_talents[talent_i]);
                player->addTalent(arrayWar_arms_talents[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }
        else if (action == GOSSIP_ACTION_INFO_DEF + 102) // Endless Rage
        {
            // Add all talents spells (max rank wich should be learned) here, dont care wich first
            uint32 arrayWar_arms_talents[] = { 16466, 12962, 12296, 12963, 12867, 12713, 16494, 12292, 12704, 29889, 12294, 29859, 29838, 35448, 23695, 29623, 12856, 12837, 12322, 16492, 12323, 12318, 13045, 12677 };
            uint32 countWar_arms_talents = 24; // talent spell count from above

            // wipe talents
            player->resetTalents(true);
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < countWar_arms_talents; talent_i++)
            {
                player->learnSpell(arrayWar_arms_talents[talent_i]);
                player->addTalent(arrayWar_arms_talents[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }
        else if (action == GOSSIP_ACTION_INFO_DEF + 103) // Flurry
        {
            // Add all talents spells (max rank wich should be learned) here, dont care wich first
            uint32 arrayWar_arms_talents[] = { 16466, 12962, 12867, 12296, 12290, 16494, 12712, 12292, 12704, 29899, 12668, 12294, 12856, 12837, 12322, 16492, 12323, 12318, 13048, 20503, 12328, 20505, 12974, 29889 };
            uint32 countWar_arms_talents = 24; // talent spell count from above

            // wipe talents
            player->resetTalents(true);
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < countWar_arms_talents; talent_i++)
            {
                player->learnSpell(arrayWar_arms_talents[talent_i]);
                player->addTalent(arrayWar_arms_talents[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }

        if (isVip)
        {
            // ITEM TEMPLATE; just fill in item ids, dont care wich slot first
            uint32 arrayWar_arms[] = { 35068, 35070, 35066, 35176, 35067, 35161, 35069, 35146, 35135, 33484, 34189, 32335, 33831, 34989, 35108 }; // item ids
            uint32 countWar_arms_items = 15; // item count above

            for (uint32 i = 0; i < countWar_arms_items; i++)
                player->StoreNewItemInBestSlots(arrayWar_arms[i], 1);
        }
        else
        {
            uint32 arrayWar_arms[] = { 33730, 33732, 33728, 33813, 33729, 33811, 33731, 33812, 33923, 33484, 34189, 32335, 33831, 33663, 33765 }; // item ids
            uint32 countWar_arms_items = 15; // item count above

            for (uint32 i = 0; i < countWar_arms_items; i++)
                player->StoreNewItemInBestSlots(arrayWar_arms[i], 1);
        }

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);
            AddSocket(player, itemTarget, arrayWar_arms_sockets[i_slot][0], arrayWar_arms_sockets[i_slot][1], arrayWar_arms_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, arrayWar_arms_enchants[i_slot]);

            if (i_slot >= INVENTORY_SLOT_BAG_END || !itemTarget)
                continue;

            ItemPrototype const *proto = itemTarget->GetProto();

            player->ApplyEnchantment(itemTarget, BONUS_ENCHANTMENT_SLOT, false);
            itemTarget->SetEnchantment(BONUS_ENCHANTMENT_SLOT, proto->socketBonus, 0, 0);
            player->ApplyEnchantment(itemTarget, BONUS_ENCHANTMENT_SLOT, true);
        }

        player->ToggleMetaGemsActive(23, true);

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 201: // Paladin - Holy
    {
        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 arrayPaladin_holy_enchants[] = { 3001, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2664, 2343, 2654, 0, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 arrayPaladin_holy_sockets[19][3] = {
            { 2828, 3138, 0 },
            { 0, 0, 0 },
            { 3138, 3141, 0 },
            { 0, 0, 0 },
            { 3138, 3138, 3141 },
            { 3138, 0, 0 },
            { 3141, 0, 0 },
            { 3138, 0, 0 },
            { 3138, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };
        // Add all talents spells (max rank wich should be learned) here, dont care wich first
        uint32 arrayPaladin_holy_talents[] = { 20261, 20330, 20209, 20239, 25836, 20215, 20216, 20361, 25829, 20473, 31836, 31841, 31842, 20137, 20175, 20193, 20148, 20470, 20256, 31845, 20217 };
        uint32 countPaladin_holy_talents = 21; // talent spell count from above


        if (isVip)
        {
            uint32 arrayPaladin_holy_items[] = { 35061, 35063, 35059, 34432, 35060, 34487, 30994, 34559, 32500, 35073, 33502, 34184, 33333, 29309, 32528, 34471 }; // Item IDs
            uint32 countPaladin_holy_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPaladin_holy_items; i++)
                player->StoreNewItemInBestSlots(arrayPaladin_holy_items[i], 1);
        }
        else
        {
            uint32 arrayPaladin_holy_items[] = { 33724, 33726, 33722, 34432, 33723, 34487, 30994, 34559, 32500, 33735, 33502, 34184, 33333, 29309, 32528, 34471 }; // Item IDs
            uint32 countPaladin_holy_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPaladin_holy_items; i++)
                player->StoreNewItemInBestSlots(arrayPaladin_holy_items[i], 1);
        }

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, arrayPaladin_holy_sockets[i_slot][0], arrayPaladin_holy_sockets[i_slot][1], arrayPaladin_holy_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, arrayPaladin_holy_enchants[i_slot]);
        }

        // wipe talents
        player->resetTalents(true);

        // learn talents from array
        for (uint32 talent_i = 0; talent_i < countPaladin_holy_talents; talent_i++)
        {
            player->learnSpell(arrayPaladin_holy_talents[talent_i]);
            player->addTalent(arrayPaladin_holy_talents[talent_i], player->GetActiveSpec(), true);
        }

        // remove all talents points
        player->SetFreeTalentPoints(0);

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 202: // Paladin - Protection
        break;
    case GOSSIP_ACTION_INFO_DEF + 203: // Paladin - Retribution
    {
        uint32 array_talent[] = { 20217, 20137, 20193, 20175, 20143, 20470, 20489, 31845, 20105, 20337, 25957, 20121, 20375, 44414, 31870, 26021, 20113, 20218, 31878, 20059, 20066, 35397, 35395 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayPaladin_ret[] = { 35090, 35092, 35088, 34431, 35089, 35163, 30993, 35148, 33503, 35015, 35135, 33484, 32335, 34189, 33831 }; // Item IDs
            uint32 countPaladin_ret = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPaladin_ret; i++)
                player->StoreNewItemInBestSlots(arrayPaladin_ret[i], 1);
        }
        else
        {
            uint32 arrayPaladin_ret[] = { 33751, 33753, 33749, 34431, 33750, 33909, 30993, 33911, 33503, 33688, 33923, 33484, 32335, 34189, 33831 }; // Item IDs
            uint32 countPaladin_ret = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPaladin_ret; i++)
                player->StoreNewItemInBestSlots(arrayPaladin_ret[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3012, 2658, 2647, 684, 2931, 2931, 0, 0, 368, 2667 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2830, 3115, 0 },
            { 3139, 0, 0 },
            { 3115, 3139, 0 },
            { 0, 0, 0 },
            { 3115, 3115, 3139 },
            { 0, 0, 0 },
            { 3115, 0, 0 },
            { 0, 0, 0 },
            { 3139, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 301: // Hunter - mm
    {
        uint32 array_talent[] = { 19587, 19575, 19415, 19431, 19417, 19434, 34949, 19490, 19464, 19468, 19503, 24691, 34476, 19506, 34484, 34489, 34490, 19500, 19152, 19232, 19388, 19245, 19263 };
        uint32 count_talent = 23; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayHunter_mm[] = { 34992, 34994, 34990, 35166, 34991, 35151, 34993, 35136, 35110, 36737, player->getRace() == RACE_DWARF ? 35075 : 35047, 33484, 35131, 34189, 33832, 35135 }; // Item IDs
            uint32 countHunter_mm = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_mm; i++)
                player->StoreNewItemInBestSlots(arrayHunter_mm[i], 1);
        }
        else
        {
            uint32 arrayHunter_mm[] = { 33666, 33668, 33664, 33876, 33665, 33877, 33667, 33878, 33762, 33734, player->getRace() == RACE_DWARF ? 34530 : 34529, 33484, 33919, 34189, 33832, 33923 }; // Item IDs
            uint32 countHunter_mm = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_mm; i++)
                player->StoreNewItemInBestSlots(arrayHunter_mm[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2986, 0, 2933, 0, 3012, 2658, 1593, 2564, 2931, 2931, 0, 0, 368, 2666, 2666, 2724, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2829, 3119, 0 },
            { 3144, 0, 0 },
            { 3119, 3144, 0 },
            { 0, 0, 0 },
            { 3119, 3119, 3144 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3144, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 302: // Hunter - bm
    {
        uint32 array_talent[] = { 19587, 19610, 19575, 35030, 19596, 19620, 19573, 19602, 19577, 19592, 19624, 19574, 34460, 34470, 34692, 19415, 19431, 19434, 34954, 34949, 19490 };
        uint32 count_talent = 21; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayHunter_bm[] = { 34992, 34994, 34990, 35166, 34991, 35151, 34993, 35136, 35110, 36737, player->getRace() == RACE_DWARF ? 35075 : 35047, 33484, 29301, 34189, 33831, 35135 }; // Item IDs
            uint32 countHunter_bm = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_bm; i++)
                player->StoreNewItemInBestSlots(arrayHunter_bm[i], 1);
        }
        else
        {
            uint32 arrayHunter_bm[] = { 33666, 33668, 33664, 33876, 33665, 33877, 33667, 33878, 33762, 33734, player->getRace() == RACE_DWARF ? 34530 : 34529, 33484, 29301, 34189, 33831, 33923 }; // Item IDs
            uint32 countHunter_bm = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_bm; i++)
                player->StoreNewItemInBestSlots(arrayHunter_bm[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2997, 0, 2933, 0, 3012, 2658, 1593, 2564, 2931, 2931, 0, 0, 368, 2666, 2666, 2724, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2829, 3116, 0 },
            { 3144, 0, 0 },
            { 3116, 3144, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3144 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3144, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 303: // Hunter - sv
    {
        uint32 array_talent[] = { 19587, 19575, 19415, 19431, 19417, 19434, 34949, 19464, 19468, 19503, 19500, 19152, 19233, 19388, 19263, 19245, 19255, 24283, 19377, 19373, 19306, 34494, 24297, 19386, 34502 };
        uint32 count_talent = 25; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayHunter_sv[] = { 34992, 34994, 34990, 35166, 34991, 35151, 34993, 35136, 35110, 36737, player->getRace() == RACE_DWARF ? 35075 : 35047, 33484, 35131, 34189, 33832, 35135 }; // Item IDs
            uint32 countHunter_sv = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_sv; i++)
                player->StoreNewItemInBestSlots(arrayHunter_sv[i], 1);
        }
        else
        {
            uint32 arrayHunter_sv[] = { 33666, 33668, 33664, 33876, 33665, 33877, 33667, 33878, 33762, 33734, player->getRace() == RACE_DWARF ? 34530 : 34529, 33484, 33919, 34189, 34163, 33923 }; // Item IDs
            uint32 countHunter_sv = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countHunter_sv; i++)
                player->StoreNewItemInBestSlots(arrayHunter_sv[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2997, 0, 2933, 0, 3013, 2658, 1593, 2564, 2931, 2931, 0, 0, 368, 2666, 2666, 2724, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2829, 3116, 0 },
            { 3144, 0, 0 },
            { 3116, 3144, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3144 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3144, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 401: // Rogue - Assassination (Mutilate)
    {
        uint32 array_talent[] = { 14142, 14161, 13866, 14137, 14169, 14179, 14117, 16720, 14177, 31209, 14176, 31245, 14195, 14983, 1329, 31242, 31227, 14075, 14094, 14063 };
        uint32 count_talent = 20; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayRogue_muti[] = { 35033, 35035, 35036, 35167, 35032, 35156, 35034, 35141, 35093, 35058, 35108, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_muti = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countRogue_muti; i++)
                player->StoreNewItemInBestSlots(arrayRogue_muti[i], 1);
        }
        else
        {
            uint32 arrayRogue_muti[] = { 33701, 33702, 33704, 33881, 33700, 33891, 33703, 33892, 33754, 33801, 33765, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_muti = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countRogue_muti; i++)
                player->StoreNewItemInBestSlots(arrayRogue_muti[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 arrayRogue_shs_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3012, 2657, 1593, 2564, 2931, 2931, 0, 0, 368, 2673, 2673, 0, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 arrayRogue_shs_sockets[19][3] = {
            { 2830, 3116, 0 },
            { 0, 0, 0 },
            { 3116, 3142, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3142 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3142, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, arrayRogue_shs_sockets[i_slot][0], arrayRogue_shs_sockets[i_slot][1], arrayRogue_shs_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, arrayRogue_shs_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 402: // Rogue - Combat
    case GOSSIP_ACTION_INFO_DEF + 404: // Rogue - Combat
    {
        if (action == GOSSIP_ACTION_INFO_DEF + 402) // Deep
        {
            uint32 array_talent[] = { 13863, 13792, 13845, 14166, 13875, 13852, 13877, 13803, 30920, 31126, 18429, 13750, 31131, 35552, 32601, 14142, 14159, 14161, 14179, 14169, 14132, 16720 };
            uint32 count_talent = 22; // talent spell count from above

            // wipe talents
            player->resetTalents();
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
            {
                player->learnSpell(array_talent[talent_i]);
                player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }
        else if (action == GOSSIP_ACTION_INFO_DEF + 404) // Hemo
        {
            uint32 array_talent[] = { 13973, 14094, 14064, 13980, 14278, 14066, 14173, 14185, 14083, 16511, 13792, 13790, 13843, 13856, 14251, 13872, 13867, 13803, 13877, 13875, 30920, 31126, 31131, 13750, 35550 };
            uint32 count_talent = 25; // talent spell count from above

            // wipe talents
            player->resetTalents();
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
            {
                player->learnSpell(array_talent[talent_i]);
                player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }

        if (isVip)
        {
            uint32 arrayRogue_combat[] = { 35033, 35035, 35036, 35167, 35032, 35156, 35034, 35141, 35071, 34988, 35108, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_combat = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countRogue_combat; i++)
                player->StoreNewItemInBestSlots(arrayRogue_combat[i], 1);
        }
        else
        {
            uint32 arrayRogue_combat[] = { 33701, 33702, 33704, 33881, 33700, 33891, 33703, 33892, 33733, 33662, 33765, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_combat = 16; // Wie viele Items im array drübe
            for (uint32 i = 0; i < countRogue_combat; i++)
                player->StoreNewItemInBestSlots(arrayRogue_combat[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 arrayRogue_shs_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3012, 2657, 1593, 2564, 2931, 2931, 0, 0, 368, 2673, 2673, 0, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 arrayRogue_shs_sockets[19][3] = {
            { 2829, 3116, 0 },
            { 0, 0, 0 },
            { 3116, 3142, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3142 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3142, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, arrayRogue_shs_sockets[i_slot][0], arrayRogue_shs_sockets[i_slot][1], arrayRogue_shs_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, arrayRogue_shs_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 403: // Rogue - Subtlety
    {
        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 arrayRogue_shs_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3012, 2657, 1593, 2564, 2931, 2931, 0, 0, 368, 2673, 2673, 0, 0 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 arrayRogue_shs_sockets[19][3] = {
            { 2829, 3116, 0 },
            { 0, 0, 0 },
            { 3116, 3142, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3142 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3142, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        // Add all talents spells (max rank wich should be learned) here, dont care wich first
        if (isVip)
        {
            uint32 arrayRogue_shs[] = { 35033, 35035, 35036, 35167, 35032, 35156, 35034, 35141, player->getRace() == RACE_HUMAN ? 35101 : 35076, 35095, 35108, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_shs = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countRogue_shs; i++)
                player->StoreNewItemInBestSlots(arrayRogue_shs[i], 1);
        }
        else
        {
            uint32 arrayRogue_shs[] = { 33701, 33702, 33704, 33881, 33700, 33891, 33703, 33892, player->getRace() == RACE_HUMAN ? 33762 : 33737, 33756, 33765, 34177, 29994, 29301, 34887, 33831 }; // Item IDs
            uint32 countRogue_shs = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countRogue_shs; i++)
                player->StoreNewItemInBestSlots(arrayRogue_shs[i], 1);
        }

        uint32 arrayRogue_shs_talents[] = { 14142, 14161, 14163, 14179, 14137, 16719, 14278, 13973, 14064, 14094, 13980, 142798, 14173, 14066, 16511, 14185, 14083, 30895, 14183, 30906, 31230, 31220, 36554 };
        uint32 countRogue_shs_talents = 23; // talent spell count from above

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, arrayRogue_shs_sockets[i_slot][0], arrayRogue_shs_sockets[i_slot][1], arrayRogue_shs_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, arrayRogue_shs_enchants[i_slot]);
        }

        player->resetTalents(true);
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < countRogue_shs_talents; talent_i++)
        {
            player->learnSpell(arrayRogue_shs_talents[talent_i]);
            player->addTalent(arrayRogue_shs_talents[talent_i], player->GetActiveSpec(), true);
        }

        // remove all talents points
        player->SetFreeTalentPoints(0);

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 501: // Priest - Discipline / Holy
    {
        uint32 array_talent[] = { 14791, 14769, 14774, 14787, 14767, 14777, 14751, 33172, 14783, 14772, 18555, 14752, 33190, 10060, 33205, 45244, 33206, 15012, 17191, 18535, 15237, 27811 };
        uint32 count_talent = 22; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayPriest_disc[] = { 35054, 35056, 35057, 35174, 35053, 35159, 35055, 35144, 35082, 35074, 34985, 35291, 32337, 35733, 35733, 30665 }; // Item IDs
            uint32 countPriest_disc = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_disc; i++)
                player->StoreNewItemInBestSlots(arrayPriest_disc[i], 1);
        }
        else
        {
            uint32 arrayPriest_disc[] = { 33718, 33720, 33721, 33902, 33717, 33900, 33719, 33743, 33736, 34059, 33922, 32337, 35733, 35733, 30665, 33901 }; // Item IDs
            uint32 countPriest_disc = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_disc; i++)
                player->StoreNewItemInBestSlots(arrayPriest_disc[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3001, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2938, 2343 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2835, 3318, 0 },
            { isVip ? 3318 : 3131, 0, 0 },
            { 3318, 3132, 0 },
            { 0, 0, 0 },
            { 3318, 3132, 3132 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3132, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 503: // Priest - Discipline / Holy
    {
        uint32 array_talent[] = { 14791, 14787, 14777, 14751, 33172, 14783, 18555, 14752, 33190, 45244, 10060, 14772, 14769, 14749, 33206, 15012, 17191, 18535, 15237, 27816, 27903, 15017 };
        uint32 count_talent = 22; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayPriest_disc[] = { 35054, 35056, 35057, 35174, 35053, 35159, 35055, 35144, 35082, 35074, 34985, 35291, 32337, 35733, 35733, 30665 }; // Item IDs
            uint32 countPriest_disc = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_disc; i++)
                player->StoreNewItemInBestSlots(arrayPriest_disc[i], 1);
        }
        else
        {
            uint32 arrayPriest_disc[] = { 33718, 33720, 33721, 33902, 33717, 33900, 33719, 33743, 33736, 34059, 33922, 32337, 35733, 35733, 30665, 33901 }; // Item IDs
            uint32 countPriest_disc = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_disc; i++)
                player->StoreNewItemInBestSlots(arrayPriest_disc[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3001, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2938, 2343 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2835, 3318, 0 },
            { isVip ? 3318 : 3131, 0, 0 },
            { 3318, 3132, 0 },
            { 0, 0, 0 },
            { 3318, 3132, 3132 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3132, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 502: // Priest - Shadow
    {
        uint32 arrayPriest_shadow_talent[] = { 14791, 14769, 14774, 14751, 14777, 33167, 15326, 15317, 15328, 15312, 15448, 15407, 17323, 15334, 15487, 15286, 27840, 15310, 33195, 15473, 34914, 33215, 14783 };
        uint32 countPriest_shadow_talent = 23; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < countPriest_shadow_talent; talent_i++)
            player->learnSpell(arrayPriest_shadow_talent[talent_i]);
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayPriest_shadow[] = { 35084, 35086, 35087, 35168, 35083, 35153, 35085, 35138, 35014, 35016, 35107, 35133, 35321, 35129, 32483, 33853 }; // Item IDs
            uint32 countPriest_shadow = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_shadow; i++)
                player->StoreNewItemInBestSlots(arrayPriest_shadow[i], 1);
        }
        else
        {
            uint32 arrayPriest_shadow[] = { 33745, 33747, 33748, 33883, 33744, 33882, 33746, 33884, 33763, 34033, 34066, 35319, 35321, 33853, 32483, 33056 }; // Item IDs
            uint32 countPriest_shadow = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countPriest_shadow; i++)
                player->StoreNewItemInBestSlots(arrayPriest_shadow[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2672 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3163, 3118, 0 },
            { 3118, 0, 0 },
            { 3118, 3118, 0 },
            { 0, 0, 0 },
            { 3118, 3131, 3131 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3131, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 601: // Shaman - Elemental
    {
        uint32 array_talent[] = { 16112, 16120, 16116, 16164, 29065, 16089, 29000, 16582, 16166, 30673, 30681, 16217, 16225, 16234, 16221, 16188, 16108 };
        uint32 count_talent = 17; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayShaman_resto[] = { 35050, 35052, 35048, 35173, 35049, 35158, 35051, 35143, 35102, 34986, 33506, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countShaman_resto = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_resto; i++)
                player->StoreNewItemInBestSlots(arrayShaman_resto[i], 1);
        }
        else
        {
            uint32 arrayShaman_ele[] = { 33713, 33715, 33711, 33897, 33712, 33898, 33714, 33899, 33687, 33661, 33506, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countShaman_ele = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_ele; i++)
                player->StoreNewItemInBestSlots(arrayShaman_ele[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2669, 3229 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 0, 0, 0 },
            { 3286, 3285, 0 },
            { 0, 0, 0 },
            { 3286, 3287, 3287 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3285, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 602: // Shaman - Enhancement
    {
        uint32 array_talent[] = { 16301, 16287, 16305, 16293, 43338, 16284, 16309, 16268, 29080, 29193, 29088, 17364, 30798, 30816, 30811, 30823, 16112, 16130, 28998, 16116, 16164 };
        uint32 count_talent = 21; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayShaman_enh[] = { 35044, 35046, 35042, 35172, 35043, 35157, 35045, 35142, 35135, 33484, 29301, 34189, 33831, 34996, 34995, 33507 }; // Item IDs
            uint32 countShaman_enh = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_enh; i++)
                player->StoreNewItemInBestSlots(arrayShaman_enh[i], 1);
        }
        else
        {
            uint32 arrayShaman_enh[] = { 33708, 33710, 33706, 33894, 33707, 33895, 33709, 33896, 33923, 33484, 29301, 34189, 33831, 34015, 33669, 33507 }; // Item IDs
            uint32 countShaman_enh = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_enh; i++)
                player->StoreNewItemInBestSlots(arrayShaman_enh[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2986, 0, 2933, 0, 3012, 2658, 2647, 684, 2931, 2931, 0, 0, 2938, 2668, 3225 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2829, 3115, 0 },
            { 3139, 0, 0 },
            { 3115, 3139, 0 },
            { 0, 0, 0 },
            { 3115, 3115, 3139 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3139, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 603: // Shaman - Restoration
    case GOSSIP_ACTION_INFO_DEF + 604: // Shaman - Restoration
    {
        if (action == GOSSIP_ACTION_INFO_DEF + 603)
        {
            uint32 array_talent[] = { 17489, 16253, 16287, 16293, 16274, 16309, 16217, 16222, 16240, 16234, 16196, 16189, 16208, 16188, 30866, 16213, 16190, 30885, 30869, 974 };
            uint32 count_talent = 20; // talent spell count from above

            // wipe talents
            player->resetTalents();
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
            {
                player->learnSpell(array_talent[talent_i]);
                player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }
        else if (action == GOSSIP_ACTION_INFO_DEF + 604)
        {
            uint32 array_talent[] = { 17489, 16253, 16287, 16293, 16274, 16309, 16229, 16222, 16240, 16189, 16234, 16196, 16221, 16188, 30866, 16213, 30886, 30869, 974 };
            uint32 count_talent = 19; // talent spell count from above

            // wipe talents
            player->resetTalents();
            // learn talents from array
            for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
            {
                player->learnSpell(array_talent[talent_i]);
                player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
            }
            // remove all talents points
            player->SetFreeTalentPoints(0);
        }

        if (isVip)
        {
            uint32 arrayShaman_resto[] = { 35079, 35081, 35077, 35177, 35078, 35162, 35080, 35147, 32500, 35073, 35106, 35134, 33333, 35130, 35283, 34471 }; // Item IDs
            uint32 countShaman_resto = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_resto; i++)
                player->StoreNewItemInBestSlots(arrayShaman_resto[i], 1);
        }
        else
        {
            uint32 arrayShaman_resto[] = { 33740, 33742, 33738, 33906, 33739, 33907, 33741, 33908, 32500, 33735, 33843, 33922, 33333, 33918, 35283, 34471 }; // Item IDs
            uint32 countShaman_resto = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countShaman_resto; i++)
                player->StoreNewItemInBestSlots(arrayShaman_resto[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2938, 2343, 2654, 3229 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2835, 3138, 0 },
            { 3131, 0, 0 },
            { 3138, 3131, 0 },
            { 0, 0, 0 },
            { 3138, 3141, 3141 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3131, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 701: // Mage - frost
    {
        uint32 array_talent[] = { 12592, 16770, 12577, 12606, 28574, 12598, 16766, 12475, 12571, 12497, 15053, 12472, 12953, 16758, 12985, 12488, 11160, 11958, 11426, 31672, 28593, 31676, 31687 };
        uint32 count_talent = 23; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayMage_frost[] = { 35097, 35096, 35099, 35179, 35098, 35164, 35100, 35149, 35102, 35008, 35107, 34204, 35321, 32527, 32527, 33829 }; // Item IDs
            uint32 countMage_frost = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_frost; i++)
                player->StoreNewItemInBestSlots(arrayMage_frost[i], 1);
        }
        else
        {
            uint32 arrayMage_frost[] = { 33758, 33757, 33760, 33913, 33759, 33912, 33761, 33914, 33763, 33681, 33764, 34204, 35321, 32527, 32527, 33829 }; // Item IDs
            uint32 countMage_frost = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_frost; i++)
                player->StoreNewItemInBestSlots(arrayMage_frost[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2669 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 0, 0, 0 },
            { 3285, 3287, 0 },
            { 0, 0, 0 },
            { 3286, 3287, 3287 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3285, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 702: // Mage - fire imp cs
    {
        uint32 array_talent[] = { 16770, 12341, 12360, 12847, 12353, 11366, 12351, 18460, 12873, 11113, 11115, 11368, 31639, 12400, 31642, 34296, 11129, 31661, 31680, 12577, 29446, 28574, 11255, 12598 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayMage_fire[] = { 35097, 35096, 35099, 35179, 35098, 35164, 35100, 35149, 34987, 35107, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countMage_fire = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_fire; i++)
                player->StoreNewItemInBestSlots(arrayMage_fire[i], 1);
        }
        else
        {
            uint32 arrayMage_fire[] = { 33758, 33757, 33760, 33913, 33759, 33912, 33761, 33914, 34540, 33764, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countMage_fire = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_fire; i++)
                player->StoreNewItemInBestSlots(arrayMage_fire[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2671 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 0, 0, 0 },
            { 3285, 3287, 0 },
            { 0, 0, 0 },
            { 3286, 3287, 3287 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3285, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 703: // Mage - fire icy veins
    {
        uint32 array_talent[] = { 12341, 12360, 12847, 12353, 11366, 12351, 18460, 12873, 11113, 11115, 11368, 31639, 12400, 31642, 34296, 11129, 31661, 31680, 16766, 12497, 12475, 12571, 12488, 12472 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayMage_fire[] = { 35097, 35096, 35099, 35179, 35098, 35164, 35100, 35149, 34987, 35107, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countMage_fire = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_fire; i++)
                player->StoreNewItemInBestSlots(arrayMage_fire[i], 1);
        }
        else
        {
            uint32 arrayMage_fire[] = { 33758, 33757, 33760, 33913, 33759, 33912, 33761, 33914, 34540, 33764, 34204, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countMage_fire = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countMage_fire; i++)
                player->StoreNewItemInBestSlots(arrayMage_fire[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2671 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 0, 0, 0 },
            { 3285, 3287, 0 },
            { 0, 0, 0 },
            { 3286, 3287, 3287 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3285, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 801: // Warlock - Affliction / Demonology
    {
        uint32 array_talent[] = { 17814, 18179, 17805, 18183, 18288, 18829, 17784, 32383, 18095, 18219, 18223, 18265, 32385, 18275, 30064, 18220, 30057, 32484, 30108, 18693, 18701, 17803, 17792, 17877, 18119 };
        uint32 count_talent = 25; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 array_items[] = { 35010, 35006, 35007, 35168, 35003, 35153, 35005, 35138, 35102, 35016, 35065, 37928, 35321, 32527, 35129, 33829 }; // Item IDs
            uint32 count_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < count_items; i++)
                player->StoreNewItemInBestSlots(array_items[i], 1);
        }
        else
        {
            uint32 array_items[] = { 33683, 33679, 33680, 33883, 33676, 33882, 33678, 33884, 33763, 34033, 34066, 35319, 35321, 32527, 33853, 33829 }; // Item IDs
            uint32 count_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < count_items; i++)
                player->StoreNewItemInBestSlots(array_items[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2672 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3163, 3118, 0 },
            { 3131, 0, 0 },
            { 3118, 3118, 0 },
            { 0, 0, 0 },
            { 3118, 3131, 3131 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3131, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 802: // Warlock - Destruction
    {
        uint32 array_talent[] = { 17814, 18701, 18693, 17782, 17792, 18134, 17877, 17918, 18136, 18073, 17836, 17959, 30302, 17958, 17962, 34939, 30292, 30283, 30296 };
        uint32 count_talent = 19; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayWarlock_destro[] = { 35010, 35009, 35012, 35179, 35011, 35164, 35013, 35149, 37928, 35321, 32527, 32527, 32483, 34987, 35107 }; // Item IDs
            uint32 countWarlock_destro = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countWarlock_destro; i++)
                player->StoreNewItemInBestSlots(arrayWarlock_destro[i], 1);
        }
        else
        {
            uint32 arrayWarlock_destro[] = { 33683, 33682, 33685, 33913, 33684, 33912, 33686, 33914, 34540, 33764, 35319, 35321, 32527, 32527, 32483 }; // Item IDs
            uint32 countWarlock_destro = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countWarlock_destro; i++)
                player->StoreNewItemInBestSlots(arrayWarlock_destro[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2671 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 3287, 0, 0 },
            { 3285, 3287, 0 },
            { 0, 0, 0 },
            { 3286, 3287, 3287 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3285, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 803: // Warlock - SL
    {
        uint32 array_talent[] = { 18701, 18744, 30145, 18750, 18708, 18710, 18773, 30326, 23824, 19028, 30320, 35693, 17814, 18179, 18183, 17805, 18288, 17784, 18829, 18095, 32383, 18219, 18265, 18223, 32385, 18788, 18693 };
        uint32 count_talent = 27; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 array_items[] = { 35010, 35006, 35007, 35168, 35003, 35153, 35005, 35138, 35102, 35016, 35065, 37928, 35321, 32527, 35129, 33829 }; // Item IDs
            uint32 count_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < count_items; i++)
                player->StoreNewItemInBestSlots(array_items[i], 1);
        }
        else
        {
            uint32 array_items[] = { 33683, 33679, 33680, 33883, 33676, 33882, 33678, 33884, 33763, 34033, 34066, 35319, 35321, 32527, 33853, 33829 }; // Item IDs
            uint32 count_items = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < count_items; i++)
                player->StoreNewItemInBestSlots(array_items[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2672 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3163, 3118, 0 },
            { 3131, 0, 0 },
            { 3118, 3118, 0 },
            { 0, 0, 0 },
            { 3118, 3131, 3131 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3131, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }

    case GOSSIP_ACTION_INFO_DEF + 901: // Druid - Balance
    {
        uint32 array_talent[] = { 16818, 16689, 17245, 16920, 35364, 5570, 16820, 16912, 16924, 16880, 33591, 33596, 16897, 24858, 33956, 16845, 33607, 17051, 17061, 16835, 17108, 17121, 17113, 17116 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayDruid_balance[] = { 35112, 35114, 35115, 35180, 35111, 35165, 35113, 35150, 37928, 35321, 32527, 32527, 33829, 34987, 33510 }; // Item IDs
            uint32 countDruid_balance = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_balance; i++)
                player->StoreNewItemInBestSlots(arrayDruid_balance[i], 1);
        }
        else
        {
            uint32 arrayDruid_balance[] = { 33768, 33770, 33771, 33917, 33767, 33915, 33769, 33916, 35319, 35321, 32527, 32527, 33829, 34540, 33510 }; // Item IDs
            uint32 countDruid_balance = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_balance; i++)
                player->StoreNewItemInBestSlots(arrayDruid_balance[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2669 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 3286, 0, 0 },
            { 3286, 3285, 0 },
            { 0, 0, 0 },
            { 3286, 3286, 3285 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3286, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 902: // Druid - Balance (with Treants)
    {
        uint32 array_talent[] = { 16818, 16689, 17248, 35364, 16920, 5570, 16820, 16924, 16913, 16880, 33591, 16901, 24858, 33956, 33607, 33831, 33596, 17061, 17051, 16835, 17122 };
        uint32 count_talent = 21; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayDruid_balance[] = { 35112, 35114, 35115, 35180, 35111, 35165, 35113, 35150, 37928, 35321, 32527, 32527, 33829, 34987, 33510 }; // Item IDs
            uint32 countDruid_balance = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_balance; i++)
                player->StoreNewItemInBestSlots(arrayDruid_balance[i], 1);
        }
        else
        {
            uint32 arrayDruid_balance[] = { 33768, 33770, 33771, 33917, 33767, 33915, 33769, 33916, 33920, 35321, 32527, 32527, 33829, 34540, 33510 }; // Item IDs
            uint32 countDruid_balance = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_balance; i++)
                player->StoreNewItemInBestSlots(arrayDruid_balance[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3002, 0, 2982, 0, 2933, 0, 2748, 2940, 2650, 2937, 2928, 2928, 0, 0, 2938, 2669 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 3261, 3286, 0 },
            { 3286, 0, 0 },
            { 3286, 3285, 0 },
            { 0, 0, 0 },
            { 3286, 3286, 3285 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3286, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 903: // Druid - Feral Combat (Cat)
    {
        uint32 array_talent[] = { 16689, 16938, 16941, 16949, 24866, 16979, 16944, 37117, 16975, 16968, 16999, 16857, 33873, 24894, 33853, 17007, 34300, 33957, 33869, 33917, 17061, 16835, 17073, 16864 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayDruid_feralcat[] = { 34999, 35001, 35002, 34444, 34998, 34556, 31044, 34573, 34177, 29994, 29301, 34837, 33831, 35103, 33509 }; // Item IDs
            uint32 countDruid_feralcat = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_feralcat; i++)
                player->StoreNewItemInBestSlots(arrayDruid_feralcat[i], 1);
        }
        else
        {
            uint32 arrayDruid_feralcat[] = { 33672, 33674, 33675, 34444, 33671, 34573, 31044, 34556, 34177, 29994, 29301, 34837, 33831, 33716, 33509 }; // Item IDs
            uint32 countDruid_feralcat = 15; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_feralcat; i++)
                player->StoreNewItemInBestSlots(arrayDruid_feralcat[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3003, 0, 2986, 0, 2661, 0, 3013, 2657, 1891, 2564, 2931, 2931, 0, 0, 368, 2670 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2829, 3127, 0 },
            { 0, 0, 0 },
            { 3116, 3127, 0 },
            { 0, 0, 0 },
            { 3116, 3116, 3127 },
            { 3116, 0, 0 },
            { 3135, 0, 0 },
            { 3116, 0, 0 },
            { 3116, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 904: // Druid - Restoration (Deep)
    {
        uint32 array_talent[] = { 17061, 17051, 16835, 17122, 17108, 17113, 24946, 17116, 17076, 18562, 33882, 34152, 33887, 16689, 16818, 17245, 16920, 5570, 16820, 16862, 16941, 16929, 16931, 16979 };
        uint32 count_talent = 24; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayDruid_restoration[] = { 35023, 35291, 35025, 32337, 35026, 35169, 35022, 35154, 35024, 35139, 35733, 35733, 34580, 35082, 35074, 27886 }; // Item IDs
            uint32 countDruid_restoration = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_restoration; i++)
                player->StoreNewItemInBestSlots(arrayDruid_restoration[i], 1);
        }
        else
        {
            uint32 arrayDruid_restoration[] = { 33691, 33922, 33693, 32337, 33694, 33887, 33690, 33885, 33886, 35733, 35733, 34580, 33743, 33736, 27886, 33692 }; // Item 
            uint32 countDruid_restoration = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_restoration; i++)
                player->StoreNewItemInBestSlots(arrayDruid_restoration[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3001, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2938, 2343 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2835, 3132, 0 },
            { isVip ? 3318 : 3131, 0, 0 },
            { 3318, 3131, 0 },
            { 0, 0, 0 },
            { 3318, 3318, 3132 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3318, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 905: // Druid - Restoration (Dreamstate)
    {
        uint32 array_talent[] = { 17061, 17051, 16835, 17122, 17108, 17113, 24946, 17116, 16818, 16689, 17249, 16920, 16822, 5570, 16820, 16924, 16880, 16847, 33591, 33596, 24858, 33956 };
        uint32 count_talent = 28; // talent spell count from above

        // wipe talents
        player->resetTalents();
        // learn talents from array
        for (uint32 talent_i = 0; talent_i < count_talent; talent_i++)
        {
            player->learnSpell(array_talent[talent_i]);
            player->addTalent(array_talent[talent_i], player->GetActiveSpec(), true);
        }
        // remove all talents points
        player->SetFreeTalentPoints(0);

        if (isVip)
        {
            uint32 arrayDruid_restoration[] = { 35023, 35291, 35025, 32337, 35026, 35169, 35022, 35154, 35024, 35139, 35733, 35733, 34580, 35082, 35074, 27886 }; // Item IDs
            uint32 countDruid_restoration = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_restoration; i++)
                player->StoreNewItemInBestSlots(arrayDruid_restoration[i], 1);
        }
        else
        {
            uint32 arrayDruid_restoration[] = { 33691, 33922, 33693, 32337, 33694, 33887, 33690, 33885, 33886, 35733, 35733, 34580, 33743, 33736, 27886, 33692 }; // Item 
            uint32 countDruid_restoration = 16; // Wie viele Items im array drüber
            for (uint32 i = 0; i < countDruid_restoration; i++)
                player->StoreNewItemInBestSlots(arrayDruid_restoration[i], 1);
        }

        // ENCHANT TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        uint32 array_enchants[] = { 3001, 0, 2980, 0, 2933, 0, 2746, 2940, 2617, 2322, 2930, 2930, 0, 0, 2938, 2343 }; // enchant ids
        // GEM TEMPLATE -> HEAD, NECK, SHOULDER, BODY(SHIRT), CHEST, WAIST, LEGS, FEET, WRISTS, HANDS, FINGER1, FINGER2, TRINKET1, TRINKET2, BACK, MAINHAND, OFFHAND, RANGE, TABARD
        // If Item has 1 gem slot { ENCHANTID, 0 , 0},
        // If Item has 2 gem slot { ENCHANTID, ENCHANTID, 0},
        // If Item has 3 gem slot { ENCHANTID, ENCHANTID, ENCHANTID},
        uint32 array_sockets[19][3] = {
            { 2835, 3141, 0 },
            { isVip ? 3318 : 3131, 0, 0 },
            { 3318, 3141, 0 },
            { 0, 0, 0 },
            { 3318, 3318, 3141 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 3318, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        for (int i_slot = EQUIPMENT_SLOT_START; i_slot < EQUIPMENT_SLOT_END; i_slot++)
        {
            Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i_slot);

            AddSocket(player, itemTarget, array_sockets[i_slot][0], array_sockets[i_slot][1], array_sockets[i_slot][2]);
            AddEnchantment(player, itemTarget, array_enchants[i_slot]);
        }

        AddTrinketTabardShirt(player);

        player->CLOSE_GOSSIP_MENU();
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 1000:
    {
        player->TeleportTo(530, -1837.1394, 5419.9858, -12.428, 2.789);
        return true;
    }
    }

    if (player->GetZoneId() == 721)
    {
        /*
        if (player->GetTeam() == ALLIANCE)
        {
        if (roll_chance_i(50))
        player->TeleportTo(0, -8962.090820f, 514.734863f, 96.355431f, 0.649875f);
        else
        player->TeleportTo(0, -4918.725586f, -958.222046f, 501.503937f, 5.384710f);
        }
        else
        {
        if (roll_chance_i(50))
        player->TeleportTo(1, 1528.450562f, -4392.451660f, 14.888202f, 1.395065f);
        else
        player->TeleportTo(0, 1805.482666f, 278.784515f, 70.399658f, 1.573302f);
        }
        */

        player->TeleportTo(530, -1837.1394, 5419.9858, -12.428, 2.789);
    }

    return true;
}

void AddSC_npc_gossipgear()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_gossipgear";
    newscript->pGossipHello = &GossipHello_npc_gossipgear;
    newscript->pGossipSelect = &GossipSelect_npc_gossipgear;
    newscript->RegisterSelf();
}