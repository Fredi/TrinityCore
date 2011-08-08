#include "ScriptPCH.h"

enum Phases
{
    PHASE_ONE           = 1,
    PHASE_TWO           = 2,
    PHASE_THREE         = 3,
    PHASE_FOUR          = 4,
    PHASE_FIVE          = 5,

    PHASE_ONE_MASK      = 1 << PHASE_ONE,
    PHASE_TWO_MASK      = 1 << PHASE_TWO,
    PHASE_THREE_MASK    = 1 << PHASE_THREE,
    PHASE_FOUR_MASK     = 1 << PHASE_FOUR
};

enum Events
{
    EVENT_BERSERK               = 1,
    EVENT_DEATH_AND_DECAY       = 2,
    EVENT_SUMMON_SNOBOLD_VASSAL = 3,
    EVENT_DOMINATE_MIND         = 4,

    // Phase two only
    EVENT_P2_CHILLING_WAVE      = 5,

    // Phase three only
    EVENT_P3_SHADOW_BOLT        = 6
};

enum Spells
{
    SPELL_BERSERK               = 47008,
    SPELL_RISING_ANGER          = 66636,
    SPELL_DEATH_AND_DECAY       = 71001,
    SPELL_DOMINATE_MIND         = 71289,
    SPELL_INCITE_TERROR         = 73070,
    SPELL_CHILLING_WAVE         = 68778,
    SPELL_SHADOW_BOLT           = 71254
};

enum Summons
{
    NPC_SNOBOLD_VASSAL          = 34800
};

enum Models
{
    MODEL_BOY                   = 338,
    MODEL_MONSTER               = 20736
};

#define LM_YELL_AGGRO       "Enviarei todos ao inferno!"
#define LM_YELL_KILL        "Morra!!"
#define LM_YELL_DIE         "Oh nao... eu... voltarei..."
#define LM_YELL_BERSERK     "Provem a minha furia!"

class npc_legion_master : public CreatureScript
{
    public:
        npc_legion_master() : CreatureScript("npc_legion_master") {}

        struct npc_legion_masterAI : public WorldBossAI
        {
            npc_legion_masterAI(Creature* creature) : WorldBossAI(creature) {}

            void Reset()
            {
                _Reset();

                me->RemoveAurasDueToSpell(SPELL_BERSERK);

                me->SetDisplayId(MODEL_BOY);
                me->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);

                me->SetReactState(REACT_DEFENSIVE);

                events.SetPhase(PHASE_ONE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->SetDisplayId(MODEL_MONSTER);
                me->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.2f);

                me->MonsterYell(LM_YELL_AGGRO, LANG_UNIVERSAL, 0);

                events.Reset();
                events.SetPhase(PHASE_ONE);
                // Phase independent events
                events.ScheduleEvent(EVENT_BERSERK, 600000);
                events.ScheduleEvent(EVENT_DEATH_AND_DECAY, 10000);
                events.ScheduleEvent(EVENT_SUMMON_SNOBOLD_VASSAL, 20000);
                events.ScheduleEvent(EVENT_DOMINATE_MIND, 30000);
            }

            void EnterEvadeMode()
            {
                ScriptedAI::EnterEvadeMode();
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    me->MonsterYell(LM_YELL_KILL, LANG_UNIVERSAL, 0);
            }

            void JustDied(Unit* /*killer*/)
            {
                me->MonsterYell(LM_YELL_DIE, LANG_UNIVERSAL, 0);
                _JustDied();
            }

            void CastInciteTerror()
            {
                DoCast(me, SPELL_INCITE_TERROR);
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                if (events.GetPhaseMask() & PHASE_ONE_MASK && !HealthAbovePct(76))
                {
                    CastInciteTerror();
                    events.SetPhase(PHASE_TWO);
                    events.ScheduleEvent(EVENT_P2_CHILLING_WAVE, 5000, 0, PHASE_TWO);
                    return;
                }

                if (events.GetPhaseMask() & PHASE_TWO_MASK && !HealthAbovePct(51))
                {
                    CastInciteTerror();
                    events.SetPhase(PHASE_THREE);
                    events.ScheduleEvent(EVENT_P3_SHADOW_BOLT, 5000, 0, PHASE_THREE);
                    return;
                }

                if (events.GetPhaseMask() & PHASE_THREE_MASK && !HealthAbovePct(26))
                {
                    CastInciteTerror();
                    events.RescheduleEvent(EVENT_SUMMON_SNOBOLD_VASSAL, 5000);
                    events.SetPhase(PHASE_FOUR);
                    return;
                }

                if (events.GetPhaseMask() & PHASE_FOUR_MASK && !HealthAbovePct(11))
                {
                    CastInciteTerror();
                    events.RescheduleEvent(EVENT_SUMMON_SNOBOLD_VASSAL, 5000);
                    events.SetPhase(PHASE_FIVE);
                    return;
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);

                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
                {
                    if (summon->GetEntry() == NPC_SNOBOLD_VASSAL)
                    {
                        summon->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 10.0f, 20.0f);
                        DoCast(me, SPELL_RISING_ANGER);
                    }
                    summon->AI()->AttackStart(target);
                }
            }

            void ExecuteEvent(uint32 const eventId)
            {
                switch (eventId)
                {
                    case EVENT_BERSERK:
                        events.Reset();
                        me->MonsterYell(LM_YELL_BERSERK, LANG_UNIVERSAL, 0);
                        DoCast(me, SPELL_BERSERK);
                        break;
                    case EVENT_DEATH_AND_DECAY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(target, SPELL_DEATH_AND_DECAY);
                        events.ScheduleEvent(EVENT_DEATH_AND_DECAY, urand(10000, 12000));
                        break;
                    case EVENT_SUMMON_SNOBOLD_VASSAL:
                        me->SummonCreature(NPC_SNOBOLD_VASSAL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                        events.ScheduleEvent(EVENT_SUMMON_SNOBOLD_VASSAL, 20000);
                        break;
                    case EVENT_DOMINATE_MIND:
                        for (uint8 i = 0; i < 3; i++)
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_DOMINATE_MIND))
                                DoCast(target, SPELL_DOMINATE_MIND);
                        events.ScheduleEvent(EVENT_DOMINATE_MIND, urand(40000, 45000));
                        break;
                    case EVENT_P2_CHILLING_WAVE:
                        DoCast(me, SPELL_CHILLING_WAVE);
                        events.ScheduleEvent(EVENT_P2_CHILLING_WAVE, 30000, 0, PHASE_TWO);
                        break;
                    case EVENT_P3_SHADOW_BOLT:
                        std::list<Unit*> targets;
                        SelectTargetList(targets, 5, SELECT_TARGET_RANDOM, 100, true);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            DoCast(*itr, SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_P3_SHADOW_BOLT, urand(20000, 30000), 0, PHASE_THREE);
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                    ExecuteEvent(eventId);

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_legion_masterAI(creature);
        }
};

void AddSC_npc_legion_master()
{
    new npc_legion_master();
}