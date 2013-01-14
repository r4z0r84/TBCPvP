 /*
  * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
  * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/>
  * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
  * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
  * Copyright (C) 2012 Hufsa <isak.mortzell@gmail.com>
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
SDName: Boss_Luetenant_Drake
SD%Complete: 95
SDComment: Script for GO (barrels) quest 10283
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

#include "ScriptPCH.h"
#include "old_hillsbrad.h"
#include "ScriptedEscortAI.h"

/*######
## go_barrel_old_hillsbrad
######*/

bool GOHello_go_barrel_old_hillsbrad(Player* player, GameObject* go)
{
    ScriptedInstance* instance = go->GetInstanceScript();

    if (!instance)
        return false;

    if (instance->GetData(TYPE_BARREL_DIVERSION) == DONE)
        return false;

    instance->SetData(TYPE_BARREL_DIVERSION, IN_PROGRESS);
    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);

    return false;
}

/*######
## boss_lieutenant_drake
######*/

#define SAY_ENTER               -1560006
#define SAY_AGGRO               -1560007
#define SAY_SLAY1               -1560008
#define SAY_SLAY2               -1560009
#define SAY_MORTAL              -1560010
#define SAY_SHOUT               -1560011
#define SAY_DEATH               -1560012

#define SPELL_WHIRLWIND         31909
#define SPELL_HAMSTRING         9080
#define SPELL_MORTAL_STRIKE     31911
#define SPELL_FRIGHTENING_SHOUT 33789


struct boss_lieutenant_drakeAI : public ScriptedAI
{
    boss_lieutenant_drakeAI(Creature *c) : ScriptedAI(c)
    {
        instance = c->GetInstanceScript();
    }

    ScriptedInstance* instance;

    uint32 Whirlwind_Timer;
    uint32 Fear_Timer;
    uint32 MortalStrike_Timer;
    uint32 ExplodingShout_Timer;

    void Reset()
    {
        Whirlwind_Timer = 20000;
        Fear_Timer = 30000;
        MortalStrike_Timer = 45000;
        ExplodingShout_Timer = 25000;
        me->GetMotionMaster()->MovePath(70000, true);
    }

    void EnterCombat(Unit *who)
    {
        DoScriptText(SAY_AGGRO, me);
    }

    void KilledUnit(Unit *victim)
    {
        switch (rand()%2)
        {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
        }
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEATH, me);

        if (instance)
            instance->SetData(TYPE_DRAKE_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        //Whirlwind
        if (Whirlwind_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_WHIRLWIND);
            Whirlwind_Timer = 20000+rand()%5000;
        } else Whirlwind_Timer -= diff;

        //Fear
        if (Fear_Timer <= diff)
        {
            DoScriptText(SAY_SHOUT, me);
            DoCast(me->getVictim(), SPELL_FRIGHTENING_SHOUT);
            Fear_Timer = 30000+rand()%10000;
        } else Fear_Timer -= diff;

        //Mortal Strike
        if (MortalStrike_Timer <= diff)
        {
            DoScriptText(SAY_MORTAL, me);
            DoCast(me->getVictim(), SPELL_MORTAL_STRIKE);
            MortalStrike_Timer = 45000+rand()%5000;
        } else MortalStrike_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_lieutenant_drake(Creature* creature)
{
    return new boss_lieutenant_drakeAI (creature);
}

void AddSC_boss_lieutenant_drake()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_barrel_old_hillsbrad";
    newscript->pGOHello = &GOHello_go_barrel_old_hillsbrad;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_lieutenant_drake";
    newscript->GetAI = &GetAI_boss_lieutenant_drake;
    newscript->RegisterSelf();
}

