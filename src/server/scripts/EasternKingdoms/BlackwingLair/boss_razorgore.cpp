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
SDName: Boss_Razorgore
SD%Complete: 50
SDComment: Needs additional review. Phase 1 NYI (Grethok the Controller)
SDCategory: Blackwing Lair
EndScriptData */

#include "ScriptPCH.h"

//Razorgore Phase 2 Script

enum Texts
{
    SAY_EGGS_BROKEN1    = -1469022,
    SAY_EGGS_BROKEN2    = -1469023,
    SAY_EGGS_BROKEN3    = -1469024,
    SAY_DEATH           = -1469025,
    SAY_GREK_AGGRO      = -1469032,
    SAY_GREK_CONTROL    = -1469033
};

enum Spells
{
    // Razorgore
    SPELL_CLEAVE          = 22540,
    SPELL_WARSTOMP        = 24375,
    SPELL_FIREBALLVOLLEY  = 22425,
    SPELL_CONFLAGRATION   = 23023,

    // Grethok
    SPELL_BLUE_BEAM       = 40225,
    SPELL_MISSILES        = 22273,
    SPELL_DOMINATE        = 14515,
    SPELL_POLYMORPH       = 22274
    
};

struct boss_razorgoreAI : public ScriptedAI
{
    boss_razorgoreAI(Creature *c) : ScriptedAI(c) {}

    uint32 Cleave_Timer;
    uint32 WarStomp_Timer;
    uint32 FireballVolley_Timer;
    uint32 Conflagration_Timer;

    void Reset()
    {
        Cleave_Timer = 15000;                               //These times are probably wrong
        WarStomp_Timer = 35000;
        FireballVolley_Timer = 7000;
        Conflagration_Timer = 12000;
    }

    void EnterCombat(Unit * /*who*/)
    {
        DoZoneInCombat();
    }

    void JustDied(Unit* /*Killer*/)
    {
        DoScriptText(SAY_DEATH, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Cleave_Timer
        if (Cleave_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CLEAVE);
            Cleave_Timer = urand(7000, 10000);
        } else Cleave_Timer -= diff;

        // WarStomp_Timer
        if (WarStomp_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_WARSTOMP);
            WarStomp_Timer = urand(15000, 25000);
        } else WarStomp_Timer -= diff;

        // FireballVolley_Timer
        if (FireballVolley_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_FIREBALLVOLLEY);
            FireballVolley_Timer = urand(12000, 15000);
        } else FireballVolley_Timer -= diff;

        // Conflagration_Timer
        if (Conflagration_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CONFLAGRATION);
            //We will remove this threat reduction and add an aura check.

            //if (DoGetThreat(me->getVictim()))
            //DoModifyThreatPercent(me->getVictim(),-50);

            Conflagration_Timer = 12000;
        } else Conflagration_Timer -= diff;

        // Aura Check. If the gamer is affected by confliguration we attack a random gamer.
        if (me->getVictim() && me->getVictim()->HasAura(SPELL_CONFLAGRATION, 0))
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
                me->TauntApply(pTarget);

        DoMeleeAttackIfReady();
    }
};

struct npc_grethokAI : public ScriptedAI
{
    npc_grethokAI(Creature *c) : ScriptedAI(c) {}

    uint32 Missiles_Timer;
    uint32 Polymorph_Timer;
    uint32 Dominate_Timer;

    void Reset()
    {
        Missiles_Timer = 3*IN_MILLISECONDS;
        Polymorph_Timer = 10*IN_MILLISECONDS;
        Dominate_Timer = 15*IN_MILLISECONDS;

        DoCast(me, SPELL_BLUE_BEAM); // visual until can get to cast to Razorgore
    }

    void EnterCombat(Unit * /*who*/)
    {
        me->InterruptNonMeleeSpells(true);
        DoZoneInCombat();
        DoScriptText(SAY_GREK_AGGRO, me);
    }

    void JustDied(Unit* /*Killer*/)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Missiles_Timer
        if (Missiles_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_MISSILES);
            Missiles_Timer = urand(7000, 10000);
        } else Missiles_Timer -= diff;

        // Polymorph_Timer
        if (Polymorph_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_POLYMORPH);
            Polymorph_Timer = urand(15000, 25000);
        } else Polymorph_Timer -= diff;

        // Dominate_Timer
        if (Dominate_Timer <= diff)
        {
            DoScriptText(SAY_GREK_CONTROL, me);
            DoCast(me->getVictim(), SPELL_DOMINATE);
            Dominate_Timer = urand(15000, 25000);
        } else Dominate_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_razorgore(Creature* creature)
{
    return new boss_razorgoreAI (creature);
}

CreatureAI* GetAI_npc_grethok(Creature* creature)
{
    return new npc_grethokAI (creature);
}

void AddSC_boss_razorgore()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_razorgore";
    newscript->GetAI = &GetAI_boss_razorgore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_grethok";
    newscript->GetAI = &GetAI_npc_grethok;
    newscript->RegisterSelf();
}
