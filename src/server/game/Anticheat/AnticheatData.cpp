#include "AnticheatData.h"

AnticheatData::AnticheatData()
{
    lastOpcode = 0;
}

void AnticheatData::SetPosition(float x, float y, float z, float o)
{
    lastMovementInfo.pos.m_positionX = x;
    lastMovementInfo.pos.m_positionY = y;
    lastMovementInfo.pos.m_positionZ = z;
    lastMovementInfo.pos.m_orientation = o;
}