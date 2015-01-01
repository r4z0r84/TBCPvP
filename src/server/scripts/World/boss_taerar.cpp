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
SDName: Taerar
SD%Complete: 70
SDComment: Mark of Nature & Teleport NYI. Fix the way to be banished.
SDCategory: Bosses
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SAY_AGGRO               = -1000399,
    SAY_SUMMONSHADE         = -1000400,

    // Spells of Taerar
    SPELL_SLEEP             = 24777,
    SPELL_NOXIOUSBREATH     = 24818,
    SPELL_TAILSWEEP         = 15847,
    SPELL_MARKOFNATURE      = 25040,
    SPELL_MARKOFNATUREAURA  = 25041,
    SPELL_ARCANEBLAST       = 24857,
    SPELL_BELLOWINGROAR     = 22686,
    SPELL_SELFSTUN          = 24883,

    SPELL_SUMMONSHADE_1     = 24841,
    SPELL_SUMMONSHADE_2     = 24842,
    SPELL_SUMMONSHADE_3     = 24843,

    // Spells of Shades of Taerar
    SPELL_POSIONCLOUD       = 24840,
    SPELL_POSIONBREATH      = 20667,

    NPC_SHADE_OF_TAERAR     = 15302
};

uint32 m_auiSpellSummonShade[]=
{
    SPELL_SUMMONSHADE_1, SPELL_SUMMONSHADE_2, SPELL_SUMMONSHADE_3
};

struct boss_taerarAI : public ScriptedAI
{
    boss_taerarAI(Creature *c) : ScriptedAI(c), Summons(me) {}

    uint32 m_uiSleep_Timer;
    uint32 m_uiNoxiousBreath_Timer;
    uint32 m_uiTailSweep_Timer;
    uint32 m_uiArcaneBlast_Timer;
    uint32 m_uiBellowingRoar_Timer;
    uint32 m_uiShadesTimeout_Timer;
    uint32 m_uiShadesDead;
    uint32 m_uiEventCounter;

    SummonList Summons;

    void Reset()
    {
        m_uiSleep_Timer         = 15000 + rand()%5000;
        m_uiNoxiousBreath_Timer = 8000;
        m_uiTailSweep_Timer     = 4000;
        m_uiArcaneBlast_Timer   = 12000;
        m_uiBellowingRoar_Timer = 30000;
        m_uiShadesTimeout_Timer = 0; // Banished timer
        m_uiShadesDead          = 0;
        m_uiEventCounter        = 1;

        // Remove unselectable if needed
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        Summons.DespawnAll();
    }

    void EnterCombat(Unit* /*pWho*/)
    {
        DoScriptText(SAY_AGGRO, me);
        DoCast(me, SPELL_MARKOFNATUREAURA, true);
    }

    void JustDied(Unit* /*pKiller*/)
    {
        Summons.DespawnAll();
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
            pSummoned->AI()->AttackStart(pTarget);

        Summons.Summon(pSummoned);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            pVictim->CastSpell(pVictim, SPELL_MARKOFNATURE, true, NULL, NULL, me->GetGUID());
    }

    void DoUnbanishBoss()
    {
        me->RemoveAurasDueToSpell(SPELL_SELFSTUN);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        m_uiShadesTimeout_Timer = 0;
        m_uiShadesDead = 0;
    }

    void DoSpecialDragonAbility()
    {
        me->InterruptNonMeleeSpells(false);
        // Make boss not selectable when banished
        DoCast(me, SPELL_SELFSTUN, true);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        
        // Summon the shades at boss position
        int iSize = sizeof(m_auiSpellSummonShade) / sizeof(uint32);
        for (int i = 0; i < iSize; ++i)
            DoCast(me, m_auiSpellSummonShade[i], true);

        DoScriptText(SAY_SUMMONSHADE, me);
        m_uiShadesTimeout_Timer = 60000;
    }

    void SummonedCreatureDies(Creature* pSummoned, Unit* pSummoner)
    {
        if (pSummoned->GetEntry() == NPC_SHADE_OF_TAERAR)
        {
            ++m_uiShadesDead;

            // If all shades are dead then unbanish the boss
            if (m_uiShadesDead == 3)
                DoUnbanishBoss();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiShadesTimeout_Timer)
        {
            if (m_uiShadesTimeout_Timer <= uiDiff)
                DoUnbanishBoss();
            else
                m_uiShadesTimeout_Timer -= uiDiff;

            // Do nothing while banished
            return;
        }

        // Return since we have no target
        if (!UpdateVictim())
            return;

        // Sleep_Timer
        if (m_uiSleep_Timer <= uiDiff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_SLEEP);

            m_uiSleep_Timer = 8000 + rand()%7000;
        }
        else
            m_uiSleep_Timer -= uiDiff;

        // NoxiousBreath_Timer
        if (m_uiNoxiousBreath_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), SPELL_NOXIOUSBREATH);
            m_uiNoxiousBreath_Timer = 14000 + rand()%6000;
        }
        else
            m_uiNoxiousBreath_Timer -= uiDiff;

        // Tailsweep every 2 seconds
        if (m_uiTailSweep_Timer <= uiDiff)
        {
            DoCast(me, SPELL_TAILSWEEP);
            m_uiTailSweep_Timer = 2000;
        }
        else
            m_uiTailSweep_Timer -= uiDiff;

        // ArcaneBlast_Timer
        if (m_uiArcaneBlast_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), SPELL_ARCANEBLAST);
            m_uiArcaneBlast_Timer = 7000 + rand()%5000;
        }
        else
            m_uiArcaneBlast_Timer -= uiDiff;

        // BellowingRoar_Timer
        if (m_uiBellowingRoar_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), SPELL_BELLOWINGROAR);
            m_uiBellowingRoar_Timer = 20000 + rand()%10000;
        }
        else
            m_uiBellowingRoar_Timer -= uiDiff;

        // Summon 3 Shades at 75%, 50% and 25% (if bShades is true we already left in line 117, no need to check here again)
        if ((me->GetHealth() * 100 / me->GetMaxHealth()) <  100 - m_uiEventCounter * 25 )
        {
            DoSpecialDragonAbility();
            ++m_uiEventCounter;
        }

        DoMeleeAttackIfReady();
    }
};

// Shades of Taerar Script
struct boss_shadeoftaerarAI : public ScriptedAI
{
    boss_shadeoftaerarAI(Creature *c) : ScriptedAI(c) {}

    uint32 m_uiPoisonCloud_Timer;
    uint32 m_uiPosionBreath_Timer;

    void Reset()
    {
        m_uiPoisonCloud_Timer = 8000;
        m_uiPosionBreath_Timer = 12000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        //PoisonCloud_Timer
        if (m_uiPoisonCloud_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), SPELL_POSIONCLOUD);
            m_uiPoisonCloud_Timer = 30000;
        }
        else
            m_uiPoisonCloud_Timer -= uiDiff;

        //PosionBreath_Timer
        if (m_uiPosionBreath_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), SPELL_POSIONBREATH);
            m_uiPosionBreath_Timer = 12000;
        }
        else
            m_uiPosionBreath_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_taerar(Creature* creature)
{
    return new boss_taerarAI (creature);
}

CreatureAI* GetAI_boss_shadeoftaerar(Creature* creature)
{
    return new boss_shadeoftaerarAI (creature);
}

void AddSC_boss_taerar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_taerar";
    newscript->GetAI = &GetAI_boss_taerar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_shade_of_taerar";
    newscript->GetAI = &GetAI_boss_shadeoftaerar;
    newscript->RegisterSelf();
}

