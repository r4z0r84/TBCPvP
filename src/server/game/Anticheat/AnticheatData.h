#ifndef TRINITY_DEF_ANTICHEATDATA_H
#define TRINITY_DEF_ANTICHEATDATA_H

#include "AnticheatMgr.h"

class AnticheatData
{
public:
    AnticheatData();
    ~AnticheatData() {};

    void SetLastOpcode(uint32 opcode) { lastOpcode = opcode; }
    uint32 GetLastOpcode() const { return lastOpcode; }

    const MovementInfo& GetLastMovementInfo() const { return lastMovementInfo; }
    void SetLastMovementInfo(MovementInfo& moveInfo) { lastMovementInfo = moveInfo; }

    void SetPosition(float x, float y, float z, float o);

private:
    uint32 lastOpcode;
    MovementInfo lastMovementInfo;
};

#endif