#ifndef TRINITY_DEF_ANTICHEATDATA_H
#define TRINITY_DEF_ANTICHEATDATA_H

#include "AnticheatMgr.h"

#define MAX_REPORT_TYPES 2

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

    void SetTempReports(uint32 amount, uint8 type) { tempReports[type] = amount; }
    uint32 GetTempReports(uint8 type) { return tempReports[type]; }

    void SetTempReportsTimer(uint32 time, uint8 type) { tempReportsTimer[type] = time; }
    uint32 GetTempReportsTimer(uint8 type) { return tempReportsTimer[type]; }

private:
    uint32 lastOpcode;
    MovementInfo lastMovementInfo;

    uint32 tempReports[MAX_REPORT_TYPES];
    uint32 tempReportsTimer[MAX_REPORT_TYPES];
};

#endif