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
SDName: Boss_Mograine_And_Whitemane
SD%Complete: 90
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptPCH.h"
#include "scarlet_monastery.h"

enum Says
{
    // Mograine says
    SAY_MO_AGGRO                 = -1189005,
    SAY_MO_KILL                  = -1189006,
    SAY_MO_RESSURECTED           = -1189007,

    // Whitemane says
    SAY_WH_INTRO                 = -1189008,
    SAY_WH_KILL                  = -1189009,
    SAY_WH_RESSURECT             = -1189010,
};

enum Spells
{
    // Mograine Spells
    SPELL_CRUSADERSTRIKE         = 14518,
    SPELL_HAMMEROFJUSTICE        = 5589,
    SPELL_LAYONHANDS             = 9257,
    SPELL_RETRIBUTIONAURA        = 8990,

    // Whitemanes Spells
    SPELL_DEEPSLEEP              = 9256,
    SPELL_SCARLETRESURRECTION    = 9232,
    SPELL_DOMINATEMIND           = 14515,
    SPELL_HOLYSMITE              = 9481,
    SPELL_HEAL                   = 12039,
    SPELL_POWERWORDSHIELD        = 22187
};

struct boss_scarlet_commander_mograineAI : public ScriptedAI
{
    boss_scarlet_commander_mograineAI(Creature* creature) : ScriptedAI(creature)
    {
        Initialize();
        instance = creature->GetInstanceScript();
    }

    void Initialize()
    {
        CrusaderStrike_Timer = 10000;
        HammerOfJustice_Timer = 10000;
        _bHasDied = false;
        _bHeal = false;
        _bFakeDeath = false;
    }

    ScriptedInstance* instance;

    uint32 CrusaderStrike_Timer;
    uint32 HammerOfJustice_Timer;

    bool _bHasDied;
    bool _bHeal;
    bool _bFakeDeath;

    void Reset()
    {
        Initialize();

        // Incase wipe during phase that mograine fake death
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetStandState(UNIT_STAND_STATE_STAND);

        if (me->isAlive())
            instance->SetBossState(DATA_MOGRAINE_AND_WHITE_EVENT, NOT_STARTED);
    }

    void JustReachedHome()
    {
        if (instance->GetBossState(DATA_MOGRAINE_AND_WHITE_EVENT != NOT_STARTED))
            instance->SetBossState(DATA_MOGRAINE_AND_WHITE_EVENT, FAIL);
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_MO_AGGRO, me);
        DoCast(me, SPELL_RETRIBUTIONAURA);

        me->CallForHelp(VISIBLE_RANGE);
    }

    void KilledUnit(Unit* /*pVictim*/)
    {
        DoScriptText(SAY_MO_KILL, me);
    }

    void DamageTaken(Unit* /*pDoneBy*/, uint32 &damage)
    {
        if (damage < me->GetHealth() || _bHasDied || _bFakeDeath)
            return;

        // On first death, fake death and open door, as well as initiate whitemane if exist
        if (Unit* Whitemane = Unit::GetUnit((*me), instance->GetData64(DATA_WHITEMANE)))
        {
            instance->SetBossState(DATA_MOGRAINE_AND_WHITE_EVENT, IN_PROGRESS);

            Whitemane->GetMotionMaster()->MovePoint(1, 1163.113370, 1398.856812, 32.527786);

            me->GetMotionMaster()->MovementExpired();
            me->GetMotionMaster()->MoveIdle();

            me->SetHealth(0);

            if (me->IsNonMeleeSpellCasted(false))
                me->InterruptNonMeleeSpells(false);

            me->ClearComboPointHolders();
            me->RemoveAllAuras();
            me->ClearAllReactives();

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetStandState(UNIT_STAND_STATE_DEAD);

            _bHasDied = true;
            _bFakeDeath = true;

            damage = 0;
        }
    }

    void SpellHit(Unit* /*who*/, const SpellEntry* pSpell)
    {
        // When hit with ressurection say text
        if (pSpell->Id == SPELL_SCARLETRESURRECTION)
        {
            DoScriptText(SAY_MO_RESSURECTED, me);
            _bFakeDeath = false;

            instance->SetBossState(DATA_MOGRAINE_AND_WHITE_EVENT, SPECIAL);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (_bHasDied && !_bHeal && instance->GetBossState(DATA_MOGRAINE_AND_WHITE_EVENT) == SPECIAL)
        {
            // On ressurection, stop fake death and heal whitemane and resume fight
            if (Unit* Whitemane = Unit::GetUnit((*me), instance->GetData64(DATA_WHITEMANE)))
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoCast(Whitemane, SPELL_LAYONHANDS);

                CrusaderStrike_Timer = 10000;
                HammerOfJustice_Timer = 10000;

                if (me->getVictim())
                    me->GetMotionMaster()->MoveChase(me->getVictim());

                _bHeal = true;
            }
        }

        // This if-check to make sure mograine does not attack while fake death
        if (_bFakeDeath)
            return;

        // CrusaderStrike_Timer
        if (CrusaderStrike_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CRUSADERSTRIKE);
            CrusaderStrike_Timer = 10000;
        }
        else CrusaderStrike_Timer -= diff;

        //HammerOfJustice_Timer
        if (HammerOfJustice_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_HAMMEROFJUSTICE);
            HammerOfJustice_Timer = 60000;
        }
        else HammerOfJustice_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct boss_high_inquisitor_whitemaneAI : public ScriptedAI
{
    boss_high_inquisitor_whitemaneAI(Creature* creature) : ScriptedAI(creature)
    {
        Initialize();
        instance = creature->GetInstanceScript();
    }

    void Initialize()
    {
        Wait_Timer = 7000;
        Heal_Timer = 10000;
        PowerWordShield_Timer = 15000;
        HolySmite_Timer = 6000;

        _bCanResurrectCheck = false;
        _bCanResurrect = false;
    }

    ScriptedInstance* instance;

    uint32 Heal_Timer;
    uint32 PowerWordShield_Timer;
    uint32 HolySmite_Timer;
    uint32 Wait_Timer;

    bool _bCanResurrectCheck;
    bool _bCanResurrect;

    void Reset()
    {
        Initialize();

        if (me->isAlive())
            instance->SetBossState(DATA_MOGRAINE_AND_WHITE_EVENT, NOT_STARTED);
    }

    void AttackStart(Unit* who)
    {
        if (instance->GetBossState(DATA_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED)
            return;

        ScriptedAI::AttackStart(who);
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_WH_INTRO, me);
    }

    void KilledUnit(Unit* /*pVictim*/)
    {
        DoScriptText(SAY_WH_KILL, me);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage)
    {
        if (!_bCanResurrectCheck && damage >= me->GetHealth())
            damage = me->GetHealth() - 1;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (_bCanResurrect)
        {
            // When casting resuruction make sure to delay so on rez when reinstate battle deepsleep runs out
            if (Wait_Timer <= diff)
            {
                if (Unit* Mograine = Unit::GetUnit((*me), instance->GetData64(DATA_MOGRAINE)))
                {
                    DoCast(Mograine, SPELL_SCARLETRESURRECTION);
                    DoScriptText(SAY_WH_RESSURECT, me);
                    _bCanResurrect = false;
                }
            }
            else Wait_Timer -= diff;
        }

        // Cast Deep sleep when health is less than 50%
        if (!_bCanResurrectCheck && me->GetHealth()*100 / me->GetMaxHealth() <= 50)
        {
            if (me->IsNonMeleeSpellCasted(false))
                me->InterruptNonMeleeSpells(false);

            DoCast(me->getVictim(), SPELL_DEEPSLEEP);
            _bCanResurrectCheck = true;
            _bCanResurrect = true;
            return;
        }

        // while in "resurrect-mode", don't do anything
        if (_bCanResurrect)
            return;

        // If we are <75% hp cast healing spells at self or Mograine
        if (Heal_Timer <= diff)
        {
            Creature* target = NULL;

            if (HealthBelowPct(75))
                target = me;

            if (Creature* pMograine = Unit::GetCreature((*me), instance->GetData64(DATA_MOGRAINE)))
            {
                // checking _bCanResurrectCheck prevents her healing Mograine while he is "faking death"
                if (_bCanResurrectCheck && pMograine->isAlive() && pMograine->GetHealth() <= pMograine->GetMaxHealth()*0.75f)
                    target = pMograine;
            }

            if (target)
                DoCast(target, SPELL_HEAL);

            Heal_Timer = 13000;
        }
        else Heal_Timer -= diff;

        // PowerWordShield_Timer
        if (PowerWordShield_Timer <= diff)
        {
            DoCast(me, SPELL_POWERWORDSHIELD);
            PowerWordShield_Timer = 15000;
        }
        else PowerWordShield_Timer -= diff;

        // HolySmite_Timer
        if (HolySmite_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_HOLYSMITE);
            HolySmite_Timer = 6000;
        }
        else HolySmite_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_scarlet_commander_mograine(Creature* creature)
{
    return new boss_scarlet_commander_mograineAI (creature);
}

CreatureAI* GetAI_boss_high_inquisitor_whitemane(Creature* creature)
{
    return new boss_high_inquisitor_whitemaneAI (creature);
}

void AddSC_boss_mograine_and_whitemane()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_scarlet_commander_mograine";
    newscript->GetAI = &GetAI_boss_scarlet_commander_mograine;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_high_inquisitor_whitemane";
    newscript->GetAI = &GetAI_boss_high_inquisitor_whitemane;
    newscript->RegisterSelf();
}

