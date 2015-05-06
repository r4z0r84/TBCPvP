/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/>
 * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "Chat.h"
#include <cstring>

//This function is called when the player logs in (every login)
void OnLogin(Player* player)
{
    uint16 maxLevel;
    if (player->HasSkill(SKILL_COOKING) && player->GetBaseSkillValue(SKILL_COOKING) < 375)
    {
        maxLevel = player->GetPureMaxSkillValue(SKILL_COOKING);
        player->SetSkill(SKILL_COOKING, maxLevel, maxLevel);
        player->learnSkillAllSpells(SKILL_COOKING, maxLevel);
    }
    if (player->HasSkill(SKILL_FISHING) && player->GetBaseSkillValue(SKILL_FISHING) < 375)
    {
        maxLevel = player->GetPureMaxSkillValue(SKILL_FISHING);
        player->SetSkill(SKILL_FISHING, maxLevel, maxLevel);
        player->learnSkillAllSpells(SKILL_FISHING, maxLevel);
    }
    if (player->HasSkill(SKILL_FIRST_AID) && player->GetBaseSkillValue(SKILL_FIRST_AID) < 375)
    {
        maxLevel = player->GetPureMaxSkillValue(SKILL_FIRST_AID);
        player->SetSkill(SKILL_FIRST_AID, maxLevel, maxLevel);
        player->learnSkillAllSpells(SKILL_FIRST_AID, maxLevel);
    }

    // Smolderforge arena title modification
    // see if player is an arena finalist with title
    QueryResult_AutoPtr result = CharacterDatabase.PQuery("SELECT * FROM season_titles WHERE guid = '%u' LIMIT 1", player->GetGUIDLow());
    if (result)
    {
        Field *fields = result->Fetch();
        uint32 guid = fields[0].GetUInt32();
        uint8 title = fields[1].GetUInt8();
        uint8 earnedSeason = fields[2].GetUInt8();
        uint8 currentSeason = fields[3].GetUInt8();
        bool awarded = fields[4].GetBool();
        uint8 numKeepSeasons = fields[5].GetUInt8();

        CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(title);

        if (earnedSeason == currentSeason && titleEntry) // we may need to add a title
        {
            if (!awarded)
            {
                if (!player->HasTitle(titleEntry))
                {
                    player->SetTitle(titleEntry);
                    player->GetSession()->SendAreaTriggerMessage("Congratulations! You're an arena finalist! Your title has been added and if you were one of the top 3 teams, your mounts and tabard will be delivered to your mailbox shortly.");
                    ChatHandler(player).PSendSysMessage("Congratulations! You're an arena finalist! Your title has been added and if you were one of the top 3 teams, your mounts and tabard will be delivered to your mailbox shortly.");
                }

                switch (title)
                {
                case 42:
                case 62:
                case 71:
                    CharacterDatabase.PExecute("INSERT INTO `mail_external` (receiver, subject, message, item, item_count) VALUES (%u, 'Arena Rewards', 'You recent efforts in rated arena have placed you at the top 3 for season %u! Attached below are your exclusive mounts to ride upon for the next two seasons, and your tabard which you may keep permanently.', '3910%u', 1)", player->GetGUIDLow(), currentSeason - 1, title);
                    CharacterDatabase.PExecute("UPDATE `season_titles` SET awarded = 1, numKeepSeasons = 1 WHERE guid = %u", player->GetGUIDLow());
                    break;
                default: // non-glads
                    CharacterDatabase.PExecute("UPDATE `season_titles` SET awarded = 1 WHERE guid = %u", player->GetGUIDLow());
                    break;
                }
            }
        }

        if (earnedSeason < currentSeason && titleEntry) // we have a title to remove
        {
            if (player->HasTitle(titleEntry))
            {
                if (!numKeepSeasons) // no seasons left to hold onto title, remove
                {
                    player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
                    player->SetTitle(titleEntry, true);
                    CharacterDatabase.PExecute("DELETE FROM season_titles WHERE guid ='%u'", player->GetGUIDLow());
                    player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
                    player->DestroyItemCount(30609, 1, true, false); // venge drake
                    player->DestroyItemCount(34092, 1, true, false); // merc drake
                    player->DestroyItemCount(37676, 1, true, false); // nether drake
                    player->DestroyItemCount(33225, 1, true, false); // spectral
                }
                else if (numKeepSeasons)
                {
                    switch (title)
                    {
                    case 71: // Vengeful Gladiator
                    case 62: // Merciless Gladiator
                    case 42: // Gladiator
                        CharacterDatabase.PExecute("UPDATE season_titles SET earnedSeason = %u, numKeepSeasons = 0 WHERE guid ='%u'", earnedSeason + 1, player->GetGUIDLow());
                        break;
                    }
                }
            }
        }
    }
    else if (!result) // player has no record, check for titles
    {
        CharTitlesEntry const* vGlad = sCharTitlesStore.LookupEntry(71);
        CharTitlesEntry const* mGlad = sCharTitlesStore.LookupEntry(62);
        CharTitlesEntry const* glad = sCharTitlesStore.LookupEntry(42);
        CharTitlesEntry const* duelist = sCharTitlesStore.LookupEntry(43);
        CharTitlesEntry const* rival = sCharTitlesStore.LookupEntry(44);
        CharTitlesEntry const* challenger = sCharTitlesStore.LookupEntry(45);

        if (player->HasTitle(vGlad))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(vGlad, true);
        }
        if (player->HasTitle(mGlad))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(mGlad, true);
        }
        if (player->HasTitle(glad))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(glad, true);
        }
        if (player->HasTitle(duelist))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(duelist, true);
        }
        if (player->HasTitle(rival))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(rival, true);
        }
        if (player->HasTitle(challenger))
        {
            player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
            player->SetTitle(challenger, true);
        }
    }
}

//This function is called when the player logs out
void OnLogout(Player* player)
{
}

//This function is called when the player kills another player
void OnPVPKill(Player* killer, Player *killed)
{
}

 void AddSC_onevents()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "scripted_on_events";
    newscript->pOnLogin = &OnLogin;
    newscript->pOnLogout = &OnLogout;
    newscript->pOnPVPKill = &OnPVPKill;

    newscript->RegisterSelf();
}
