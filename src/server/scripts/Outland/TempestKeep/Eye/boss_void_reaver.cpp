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
SDName: Boss_Void_Reaver
SD%Complete: 90
SDComment: Should reset if raid are out of room.
SDCategory: Tempest Keep, The Eye
EndScriptData */

#include "ScriptPCH.h"
#include "the_eye.h"

enum
{
    SAY_AGGRO = -1550000,
    SAY_SLAY1 = -1550001,
    SAY_SLAY2 = -1550002,
    SAY_SLAY3 = -1550003,
    SAY_DEATH = -1550004,
    SAY_POUNDING1 = -1550005,
    SAY_POUNDING2 = -1550006,

    SPELL_POUNDING = 34162,
    SPELL_ARCANE_ORB = 34172,
    SPELL_KNOCK_AWAY = 25778,
    SPELL_BERSERK = 27680,

    NPC_TRIGGER_BOMB = 29530
};

struct boss_void_reaverAI : public ScriptedAI
{
    boss_void_reaverAI(Creature *c) : ScriptedAI(c)
    {
        instance = c->GetInstanceScript();
        me->GetPosition(&centerPos);
    }

    ScriptedInstance* instance;

    uint32 Pounding_Timer;
    uint32 ArcaneOrb_Timer;
    uint32 KnockAway_Timer;
    uint32 Berserk_Timer;
    uint32 Check_Timer;

    Position centerPos;

    void Reset()
    {
        Pounding_Timer = 15000;
        ArcaneOrb_Timer = 3000;
        KnockAway_Timer = 30000;
        Berserk_Timer = 600000;
        Check_Timer = 3000;

        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEALTH_LEECH, true);
        me->ApplySpellImmune(0, IMMUNITY_DISPEL, DISPEL_POISON, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_LEECH, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_MANA_LEECH, true);

        if (instance && me->isAlive())
            instance->SetData(DATA_VOIDREAVEREVENT, NOT_STARTED);
    }

    void KilledUnit(Unit *victim)
    {
        switch (rand()%3)
        {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
            case 2: DoScriptText(SAY_SLAY3, me); break;
        }
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEATH, me);

        if (instance)
            instance->SetData(DATA_VOIDREAVEREVENT, DONE);
    }

    void EnterCombat(Unit *who)
    {
        DoScriptText(SAY_AGGRO, me);
        DoZoneInCombat();

        if (instance)
            instance->SetData(DATA_VOIDREAVEREVENT, IN_PROGRESS);
    }

    void SpellHitTarget(Unit *target, SpellEntry *spell)
    {
        if (spell->Id == SPELL_KNOCK_AWAY)
            if (Unit *target = SelectUnit(SELECT_TARGET_TOPAGGRO, 0))
                AttackStart(target);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Check_Timer
        if (Check_Timer < diff)
        {
            if (!me->IsWithinDist3d(&centerPos, 105.0f))
                EnterEvadeMode();

            Check_Timer = 3000;
        }
        else
            Check_Timer -= diff;

        // Pounding
        if (Pounding_Timer <= diff)
        {
            DoCast(me->getVictim(),SPELL_POUNDING);
            DoScriptText(RAND(SAY_POUNDING1, SAY_POUNDING2), me);

             Pounding_Timer = 12000;
        }
        else
            Pounding_Timer -= diff;

        // Arcane Orb
        if (ArcaneOrb_Timer <= diff)
        {
            Unit *pTarget = NULL;
            std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
            std::vector<Unit *> target_list;
            for (std::list<HostileReference *>::iterator itr = t_list.begin(); itr != t_list.end(); ++itr)
            {
                pTarget = Unit::GetUnit(*me, (*itr)->getUnitGuid());
                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER && pTarget->isAlive() && pTarget->GetDistance2d(me) >= 18)
                    target_list.push_back(pTarget);

                pTarget = NULL;
            }
            if (target_list.size())
                pTarget = *(target_list.begin()+rand()%target_list.size());

            if (pTarget)
                if (Creature* trigger = DoSpawnCreature(NPC_TRIGGER_BOMB, 0.0f, 0.0f, 10.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 40000))
                    trigger->CastSpell(pTarget, SPELL_ARCANE_ORB, false, 0, 0, me->GetGUID());

            ArcaneOrb_Timer = urand(3000, 4000);
        }
        else
            ArcaneOrb_Timer -= diff;

        // Single Target knock back, reduces aggro
        if (KnockAway_Timer <= diff)
        {
            DoCast(me->getVictim(),SPELL_KNOCK_AWAY);
            KnockAway_Timer = 30000;
        }
        else
            KnockAway_Timer -= diff;

        //Berserk
        if (Berserk_Timer <= diff)
        {
            DoCast(me, SPELL_BERSERK);
            Berserk_Timer = 600000;
        }
        else
            Berserk_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_void_reaver(Creature* creature)
{
    return new boss_void_reaverAI (creature);
}

void AddSC_boss_void_reaver()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_void_reaver";
    newscript->GetAI = &GetAI_boss_void_reaver;
    newscript->RegisterSelf();
}

