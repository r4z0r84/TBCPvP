#include "TempEventMgr.h"

TempEventMgr::TempEventMgr()
{
    m_EventStatus = EVENT_STATUS_INACTIVE;
}

void TempEventMgr::AddEvent(uint32 eventEntry)
{
    // Adding Event to database
}

void TempEventMgr::DeleteEvent(uint32 eventEntry)
{
    // Delete Event from database
}

void TempEventMgr::AddEventLocation(uint32 eventEntry, uint32 mapid, float x, float y, float z, float orientation)
{
    // Add teleport location to the event
}

void TempEventMgr::DeleteEventLocation(uint32 eventEntry)
{
    // Delete teleport location from event
}

void TempEventMgr::AddPlayerToEvent(uint32 eventEntry, Player* player)
{
    // ques the player for the event
}

void TempEventMgr::DeletePlayerFromEvent(uint32 eventEntry, Player* player)
{
    // deletes the player from the event
}