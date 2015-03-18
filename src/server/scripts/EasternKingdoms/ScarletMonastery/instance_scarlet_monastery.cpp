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

/* ScriptData
SDName: Instance_Scarlet_Monastery
SD%Complete: 50
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptPCH.h"
#include "scarlet_monastery.h"

DoorData const doorData[] =
{
    { GO_HIGH_INQUISITORS_DOOR, DATA_MOGRAINE_AND_WHITE_EVENT, DOOR_TYPE_ROOM },
    { 0, 0, DOOR_TYPE_ROOM } // END
};

struct instance_scarlet_monastery : public ScriptedInstance
{
    instance_scarlet_monastery(Map* map) : ScriptedInstance(map) { Initialize(); };

    uint64 PumpkinShrineGUID;
    uint64 HorsemanGUID;
    uint64 HeadGUID;
    uint64 MograineGUID;
    uint64 WhitemaneGUID;
    uint64 VorrelGUID;

    std::set<uint64> HorsemanAdds;

    void Initialize()
    {
        SetBossNumber(EncounterCount);
        HorsemanAdds.clear();
    }

    void OnGameObjectCreate(GameObject* pGo, bool /*add*/)
    {
        switch (pGo->GetEntry())
        {
            case GO_PUMPKIN_SHRINE:
                PumpkinShrineGUID = pGo->GetGUID();
                break;
            case GO_HIGH_INQUISITORS_DOOR:
                AddDoor(pGo, true);
                break;
            default:
                break;
        }
    }

    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
            case NPC_HORSEMAN:
                HorsemanGUID = creature->GetGUID();
                break;
            case NPC_HEAD:
                HeadGUID = creature->GetGUID();
                break;
            case NPC_PUMPKIN:
                HorsemanAdds.insert(creature->GetGUID());
                break;
            case NPC_MOGRAINE:
                MograineGUID = creature->GetGUID();
                break;
            case NPC_WHITEMANE:
                WhitemaneGUID = creature->GetGUID();
                break;
            case NPC_VORREL:
                VorrelGUID = creature->GetGUID();
                break;
            default:
                break;
        }
    }

    void SetData(uint32 type, uint32 data)
    {
        switch (type)
        {
            case DATA_PUMPKIN_SHRINE:
                HandleGameObject(PumpkinShrineGUID, false);
                break;
            default:
                break;
        }
    }

    bool SetBossState(uint32 type, EncounterState state)
    {
        if (!InstanceScript::SetBossState(type, state))
            return false;

        switch (type)
        {
            case DATA_HORSEMAN_EVENT:
                if (state == DONE)
                {
                    for (std::set<uint64>::const_iterator itr = HorsemanAdds.begin(); itr != HorsemanAdds.end(); ++itr)
                    {
                        Creature* add = instance->GetCreature(*itr);
                        if (add && add->isAlive())
                            add->Kill(add);
                    }
                    HorsemanAdds.clear();
                    HandleGameObject(PumpkinShrineGUID, false);
                }
                break;
            default:
                break;
        }

        return true;
    }

    uint64 GetData64(uint32 type)
    {
        switch (type)
        {
            case DATA_MOGRAINE:             return MograineGUID;
            case DATA_WHITEMANE:            return WhitemaneGUID;
            case DATA_VORREL:               return VorrelGUID;
        }
        return 0;
    }
};

InstanceScript* GetInstanceData_instance_scarlet_monastery(Map* pMap)
{
    return new instance_scarlet_monastery(pMap);
}

void AddSC_instance_scarlet_monastery()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_scarlet_monastery";
    newscript->GetInstanceScript = &GetInstanceData_instance_scarlet_monastery;
    newscript->RegisterSelf();
}

