/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "MapManager.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog->outDebug("WORLD: received CMSG_DUEL_ACCEPTED");
    sLog->outDebug("Player 1 is: %u (%s)", player->GetGUIDLow(), player->GetName());
    sLog->outDebug("Player 2 is: %u (%s)", plTarget->GetGUIDLow(), plTarget->GetName());

    time_t now = time(NULL);
    player->duel->startTimer = now;
    plTarget->duel->startTimer = now;

    if (sWorld->getConfig(CONFIG_DUEL_MOD))
    {
        player->ResetAllPowers();
        plTarget->ResetAllPowers();

        player->ClearDiminishings();
        plTarget->ClearDiminishings();

        player->RemoveAurasDueToSpell(11196);
        player->RemoveAurasDueToSpell(25771);
        player->RemoveAurasDueToSpell(41425);
        plTarget->RemoveAurasDueToSpell(11196);
        plTarget->RemoveAurasDueToSpell(25771);
        plTarget->RemoveAurasDueToSpell(41425);

        if (sWorld->getConfig(CONFIG_DUEL_CD_RESET) && !player->GetMap()->IsDungeon())
            player->RemoveArenaSpellCooldowns();

        if (sWorld->getConfig(CONFIG_DUEL_CD_RESET) && !plTarget->GetMap()->IsDungeon())
            plTarget->RemoveArenaSpellCooldowns();

        if (Pet* pet = player->GetPet())
        {
            pet->ModifyHealth(pet->GetMaxHealth());
            pet->SetPower(pet->getPowerType(), pet->GetMaxPower(pet->getPowerType()));
        }

        if (Pet* pet = plTarget->GetPet())
        {
            pet->ModifyHealth(pet->GetMaxHealth());
            pet->SetPower(pet->getPowerType(), pet->GetMaxPower(pet->getPowerType()));
        }
    }

    player->SendDuelCountdown(3000);
    plTarget->SendDuelCountdown(3000);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug("WORLD: received CMSG_DUEL_CANCELLED");

    uint64 guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    // player either discarded the duel using the "discard button"
    // or used "/forfeit" before countdown reached 0
    GetPlayer()->DuelComplete(DUEL_INTERUPTED);
}

