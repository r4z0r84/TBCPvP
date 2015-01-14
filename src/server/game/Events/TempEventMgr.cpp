#include "TempEventMgr.h"
#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "MapManager.h"

TempEventMgr::TempEventMgr()
{
    m_EventStatus = EVENT_STATUS_INACTIVE;
    m_PlayerLimit = 0;
    m_EventParticipants.clear();
}

void TempEventMgr::ActiveEvent()
{
    sLog->outError("ActiveEvent");
    sWorld->SendGlobalText("Event: uint32 eventEntry, std::string name is active! Type .tempevent join to participate.", NULL);

    // Clear participants list on initialize
    SetEventStatus(EVENT_STATUS_ACTIVE);
}

void TempEventMgr::DisableEvent()
{
    sLog->outError("DisableEvent");
    sWorld->SendGlobalText("Event: uint32 eventEntry, std::string name has ende! Winner is std::string name", NULL);

    // Clear participants list on delete
    SetEventStatus(EVENT_STATUS_INACTIVE);
    m_EventParticipants.clear();
}

bool TempEventMgr::AddEventLocation(uint32 mapId, float x, float y, float z, float orientation)
{
    eventLoc.mapId          = mapId;
    eventLoc.x              = x;
    eventLoc.y              = y;
    eventLoc.z              = z;
    eventLoc.orientation    = orientation;

    if (!sMapMgr->IsValidMapCoord(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z))
    {
        sLog->outError("AddEventLocation - !IsValidMapCoord");
        return false;
    }

    sLog->outError("AddEventLocation - Successful");
    return true;
}

void TempEventMgr::DeleteEventLocation()
{
    eventLoc.mapId          = 0;
    eventLoc.x              = 0;
    eventLoc.y              = 0;
    eventLoc.z              = 0;
    eventLoc.orientation    = 0;

    sLog->outError("DeleteEventLocation - Successful");
}

void TempEventMgr::AddPlayerToEvent(Player* player)
{
    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
    {
        sLog->outError("AddPlayerToEvent - Event Inactive");
        ChatHandler(player).PSendSysMessage("There is no active event as this time." /*LANG_TEMPEVENT_NOT_ACTIVE*/);
        return;
    }

    if (HasPlayerLimit() && (GetEventParticipants() >= GetPlayerLimit()))
    {
        sLog->outError("AddPlayerToEvent - Event Player limit reached");
        ChatHandler(player).PSendSysMessage("This event has enough participants." /*LANG_TEMPEVENT_ENOUGH_PARTICIPANTS*/);
        return;
    }

    if (m_EventParticipants.find(player) == m_EventParticipants.end())
        m_EventParticipants.insert(player);
}

void TempEventMgr::RemovePlayerFromEvent(Player* player)
{
    EventParticipants::iterator iter = m_EventParticipants.find(player);
    if (iter == m_EventParticipants.end())
        return;

    m_EventParticipants.erase(iter);
}

void TempEventMgr::TeleportPlayersToEvent()
{
    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
    {
        // GM needs to activate event before starting it
        sLog->outError("TeleportPlayersToEvent - Event Inactive");
        return;
    }

    for (EventParticipants::const_iterator itr = m_EventParticipants.begin(); itr != m_EventParticipants.end(); ++itr)
    {
        (*itr)->TeleportTo(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z, eventLoc.orientation);
    }
}
