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
    SetEventStatus(EVENT_STATUS_ACTIVE);
}

void TempEventMgr::StartEvent()
{
    SetEventStatus(EVENT_STATUS_IN_PROGRESS);
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

bool TempEventMgr::AddEventLocation(uint32 mapId, uint32 zoneId, float x, float y, float z, float orientation)
{
    if (!sMapMgr->IsValidMapCoord(mapId, x, y, z))
        return false;

    eventLoc.mapId          = mapId;
    eventLoc.zoneId         = zoneId;
    eventLoc.x              = x;
    eventLoc.y              = y;
    eventLoc.z              = z;
    eventLoc.orientation    = orientation;

    return true;
}

void TempEventMgr::AddPlayerToEvent(Player* player)
{
    uint32 playerLimit = GetPlayerLimit();

    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
    {
        ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_NO_ACTIVE_EVENTS);
        return;
    }

    if (HasPlayerLimit() && (GetEventParticipantCount() >= playerLimit))
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
        ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_QUEUE_STATUS, GetEventParticipantCount(), playerLimit);
}

void TempEventMgr::RemovePlayerFromEvent(Player* player)
{
    EventParticipants::iterator iter = m_EventParticipants.find(player);
    if (iter == m_EventParticipants.end())
        return;

    m_EventParticipants.erase(iter);

    ChatHandler(player).PSendSysMessage(LANG_TEMPEVENT_PLAYER_LEFT);
}

bool TempEventMgr::TeleportPlayersToEvent(Player* pInvoker)
{
    if (!HasEventLocation())
        return false;

    if (GetEventStatus() == EVENT_STATUS_INACTIVE)
        return false;

    WorldPacket data(SMSG_SUMMON_REQUEST, 8+4+4);
    data << uint64(pInvoker->GetGUID());
    data << uint32(eventLoc.zoneId);
    data << uint32(MAX_PLAYER_SUMMON_DELAY * 1000);

    for (EventParticipants::const_iterator itr = m_EventParticipants.begin(); itr != m_EventParticipants.end(); ++itr)
    {
        (*itr)->SetSummonPoint(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z);
        (*itr)->GetSession()->SendPacket(&data);
    }

    return true;
}

char *GetStatusString(uint32 eventStatus)
{
    switch (eventStatus)
    {
        case EVENT_STATUS_INACTIVE:
            return "EVENT_STATUS_INACTIVE";
        case EVENT_STATUS_ACTIVE:
            return "EVENT_STATUS_ACTIVE";
        case EVENT_STATUS_IN_PROGRESS:
            return "EVENT_STATUS_IN_PROGRESS";
    }

    return "";
}

void TempEventMgr::SendEventInfoString(Player* pInvoker)
{
    ChatHandler(pInvoker).PSendSysMessage(LANG_TEMPEVENT_INFO);
    ChatHandler(pInvoker).PSendSysMessage(LANG_TEMPEVENT_INFO_STATUS, GetStatusString(GetEventStatus()));
    
    if (HasEventLocation())
    {
        MapEntry const* mapEntry = sMapStore.LookupEntry(eventLoc.mapId);
        AreaTableEntry const* zoneEntry = GetAreaEntryByAreaID(eventLoc.zoneId);

        ChatHandler(pInvoker).PSendSysMessage(LANG_TEMPEVENT_INFO_LOCATION, mapEntry->name[0], zoneEntry->area_name[0], eventLoc.x, eventLoc.y, eventLoc.z);
    }

    if (HasPlayerLimit())
        ChatHandler(pInvoker).PSendSysMessage(LANG_TEMPEVENT_INFO_PLIMIT, GetPlayerLimit());

    ChatHandler(pInvoker).PSendSysMessage(LANG_TEMPEVENT_INFO_PARTICIPANTS, GetEventParticipantCount());
}
