
#include "ScriptPCH.h"
#include "slave_pens.h"
#include "ScriptedEscortAI.h"

enum Misc
{
    SPELL_MARK_OF_BITE          = 34906,
    COILFANG_CHAMPION           = 17957,
    COILFANG_SOOTHSAYER         = 17960,
    COILFANG_ENCHANTRESS        = 17961
};

/*######
## npc_naturalist
######*/

struct npc_naturalistAI : public ScriptedAI
{
    npc_naturalistAI(Creature *c) : ScriptedAI(c)
    {
        instance = c->GetInstanceScript();
        HasYelled = false;
        HasSummoned = false;
    }

    ScriptedInstance *instance;

    bool HasYelled;
    bool HasSummoned;
    uint32 GossipTimer;

    void Reset()
    {
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        GossipTimer = 0;
    }

    void EnterCombat(Unit *who)
    {
        me->Say("Uh oh! It would appear that all of the noise you've been making has attracted some unwanted attention!", 0, 0);
    }

    void JustDied(Unit *who) {}

    void MoveInLineOfSight(Unit *who)
    {
        if (!instance)
            return;

        if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 50.0f) && !HasYelled)
        {
            me->Yell("Hey! Over here! Yeah, over here... I'm in the cage!!", 0, 0);
            HasYelled = true;
        }
    }

    void SummonMobs()
    {
        me->SummonCreature(COILFANG_CHAMPION, -138.0847f, -758.946f, 37.892f, 3.699f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 3*MINUTE*IN_MILLISECONDS);
        me->SummonCreature(COILFANG_SOOTHSAYER, -141.585f, -754.85f, 37.892f, 3.762f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 3*MINUTE*IN_MILLISECONDS);
        me->SummonCreature(COILFANG_ENCHANTRESS, -144.608f, -751.4299f, 37.8923f, 3.762f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 3*MINUTE*IN_MILLISECONDS);
        
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        GossipTimer = 45000;
        HasSummoned = true;
    }

    void JustSummoned(Creature* summoned)
    {
        summoned->AI()->AttackStart(me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (GossipTimer <= diff)
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        else
            GossipTimer -= diff;
        
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_npc_naturalist(Player *player, Creature *creature)
{
    ScriptedInstance* instance = creature->GetInstanceScript();

    if (!instance)
        return false;

    if (npc_naturalistAI* naturalist = CAST_AI(npc_naturalistAI, creature->AI()))
        if (!naturalist->HasSummoned)
            player->ADD_GOSSIP_ITEM(0, "Alright, Bite, I'll let you out.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    if (instance->GetData(TYPE_NATURALIST_EVENT) == DONE && !player->HasAura(SPELL_MARK_OF_BITE, 0))
        player->ADD_GOSSIP_ITEM(0, "Naturalist, please grant me your boon.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    
    //TODO: Add correct gossip texts
    player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
    return true;
}

bool GossipSelect_npc_naturalist(Player *player, Creature *creature, uint32 sender, uint32 action)
{
    ScriptedInstance* instance = creature->GetInstanceScript();

    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->CLOSE_GOSSIP_MENU();
            if (instance)
            {
                instance->HandleGameObject(instance->GetData64(DATA_CAGE), true);
                instance->SetData(TYPE_NATURALIST_EVENT, DONE);
                CAST_AI(npc_naturalistAI, creature->AI())->SummonMobs();
            }
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            player->CLOSE_GOSSIP_MENU();
            creature->CastSpell(player, SPELL_MARK_OF_BITE, true);
            break;
    }
    return true;
}

CreatureAI* GetAI_npc_naturalist(Creature* creature)
{
    return new npc_naturalistAI(creature);
}

void AddSC_npc_naturalist()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_naturalist";
    newscript->pGossipHello =  &GossipHello_npc_naturalist;
    newscript->pGossipSelect = &GossipSelect_npc_naturalist;
    newscript->GetAI = &GetAI_npc_naturalist;
    newscript->RegisterSelf();
}
