#include "TempEventMgr.h"
#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "Language.h"
#include "MapManager.h"

TempEventMgr::TempEventMgr()
{
    m_EventStatus = EVENT_STATUS_INACTIVE;
    m_PlayerLimit = 0;
    m_EventParticipants.clear();

    DeleteEventLocation();
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
    DeleteEventLocation();
    m_EventParticipants.clear();
}

bool TempEventMgr::AddEventLocation(uint32 mapId, float x, float y, float z, float orientation)
{
    if (!sMapMgr->IsValidMapCoord(mapId, x, y, z))
        return false;

    eventLoc.mapId          = mapId;
    eventLoc.x              = x;
    eventLoc.y              = y;
    eventLoc.z              = z;
    eventLoc.orientation    = orientation;

    return true;
}

void TempEventMgr::AddPlayerToEvent(Player* player)
{
    uint32 eventParticipants = GetEventParticipants();
    uint32 playerLimit = GetPlayerLimit();

    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
    {
        ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_NO_ACTIVE_EVENTS);
        return;
    }

    if (HasPlayerLimit() && (eventParticipants >= playerLimit))
    {
        ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_ENOUGH_PARTICIPANTS);
        return;
    }

    if (m_EventParticipants.find(player) == m_EventParticipants.end())
        m_EventParticipants.insert(player);

    // Announce to the player that he is in queue.
    ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_PLAYER_JOINED);

    // Announce the current queue status if player joins the event.
    // For example: Queue Status for Event: [6 / 12]
    if (HasPlayerLimit())
        ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_QUEUE_STATUS, eventParticipants, playerLimit);
}

void TempEventMgr::RemovePlayerFromEvent(Player* player)
{
    EventParticipants::iterator iter = m_EventParticipants.find(player);
    if (iter == m_EventParticipants.end())
        return;

    m_EventParticipants.erase(iter);

    ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_PLAYER_LEFT);
}

bool TempEventMgr::TeleportPlayersToEvent()
{
    if (!HasEventLocation())
        return false;

    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
        return false;

    for (EventParticipants::const_iterator itr = m_EventParticipants.begin(); itr != m_EventParticipants.end(); ++itr)
        (*itr)->TeleportTo(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z, eventLoc.orientation);

    return true;
}
