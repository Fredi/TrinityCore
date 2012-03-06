#include "ScriptPCH.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "ScriptMgr.h"

class spell_oracle_wolvar : public SpellScriptLoader
{
    public:
        spell_oracle_wolvar() : SpellScriptLoader("spell_oracle_wolvar") { }

        class spell_oracle_wolvar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_oracle_wolvar_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* pTarget = GetHitUnit())
                {
                    if (pTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    int32  rep_change = GetSpellInfo()->Effects[EFFECT_1].BasePoints + 1;
                    uint32 faction_id = GetSpellInfo()->Effects[EFFECT_0].BasePoints + 1;

                    FactionEntry const* factionEntry = sFactionStore.LookupEntry(faction_id);

                    if (!factionEntry)
                        return;

                    pTarget->ToPlayer()->GetReputationMgr().SetReputation(factionEntry, rep_change);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_oracle_wolvar_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_oracle_wolvar_SpellScript;
        }
};


class spell_sunreaver_disguise : public SpellScriptLoader
{
    public:
        spell_sunreaver_disguise() : SpellScriptLoader("spell_sunreaver_disguise") { }

        class spell_sunreaver_disguise_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sunreaver_disguise_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                // Change model
                if (Unit *unitTarget = GetHitUnit())
                {
                    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (GetSpellInfo()->Id == 69672)
                        unitTarget->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 70972 : 70971, true, NULL);
                    else
                        unitTarget->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 70974 : 70973, true, NULL);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_sunreaver_disguise_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_sunreaver_disguise_SpellScript;
        }
};


class spell_divine_intervention : public SpellScriptLoader
{
    public:
        spell_divine_intervention() : SpellScriptLoader("spell_divine_intervention") { }

        class spell_divine_interventionSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_divine_interventionSpellScript);

            void HandleBeforeHit()
            {
                if (Unit * target = GetHitUnit())
                {
                   if (target->GetTypeId() != TYPEID_PLAYER)
                   {
                       PreventHitEffect(EFFECT_0);
                       PreventHitEffect(EFFECT_1);
                   }
                }
            }


            void Register()
            {
                BeforeHit += SpellHitFn(spell_divine_interventionSpellScript::HandleBeforeHit);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_divine_interventionSpellScript();
        }
};

enum HalloweenData
{
    NPC_STINKY_BOMB_CREDIT = 15415,

    GO_STINKY_BOMB_FLASK   = 180449,
    GO_STINKY_BOMB_CLOUD   = 180450,

    QUEST_CRASHING_WICKERMAN_FESTIVAL = 1658,

    SPELL_PIRATE_COSTUME_MALE           = 24708,
    SPELL_PIRATE_COSTUME_FEMALE         = 24709,
    SPELL_NINJA_COSTUME_MALE            = 24711,
    SPELL_NINJA_COSTUME_FEMALE          = 24710,
    SPELL_LEPER_GNOME_COSTUME_MALE      = 24712,
    SPELL_LEPER_GNOME_COSTUME_FEMALE    = 24713,
    SPELL_GHOST_COSTUME_MALE            = 24735,
    SPELL_GHOST_COSTUME_FEMALE          = 24736,


    SPELL_HALLOWEEN_WAND_PIRATE         = 24717,
    SPELL_HALLOWEEN_WAND_NINJA          = 24718,
    SPELL_HALLOWEEN_WAND_LEPER_GNOME    = 24719,
    SPELL_HALLOWEEN_WAND_RANDOM         = 24720,
    SPELL_HALLOWEEN_WAND_SKELETON       = 24724,
    SPELL_HALLOWEEN_WAND_WISP           = 24733,
    SPELL_HALLOWEEN_WAND_GHOST          = 24737,
    SPELL_HALLOWEEN_WAND_BAT            = 24741,

    SPELL_GRIM_VISAGE                   = 24705,

    // Headless Horseman fire event
    NPC_HEADLESS_FIRE                   = 23537,
    NPC_FIRE_DUMMY                      = 1,
    GO_FIRE_EFFIGY                      = 186720,


    SPELL_WATER_SPOUT_VISUAL            = 42348,
    SPELL_FIRE_VISUAL_BUFF              = 42074,
    SPELL_FIRE_SIZE_STACK               = 42091,
};

enum HalloweenFireEvents
{
    EVENT_FIRE_NONE,
    EVENT_FIRE_HIT_BY_BUCKET,
    EVENT_FIRE_VISUAL_WATER,
    EVENT_FIRE_GROW_FIRE,
};
class spell_halloween_wand : public SpellScriptLoader
{
public:
    spell_halloween_wand() : SpellScriptLoader("spell_halloween_wand") {}

    class spell_halloween_wand_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_halloween_wand_SpellScript)

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PIRATE_COSTUME_MALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_PIRATE_COSTUME_FEMALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_NINJA_COSTUME_MALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_NINJA_COSTUME_FEMALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_LEPER_GNOME_COSTUME_MALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_LEPER_GNOME_COSTUME_FEMALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_GHOST_COSTUME_MALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_GHOST_COSTUME_FEMALE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_PIRATE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_NINJA))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_LEPER_GNOME))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_RANDOM))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_SKELETON))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_WISP))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_GHOST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_HALLOWEEN_WAND_BAT))
                return false;
            return true;
        }

        void HandleScriptEffect()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitPlayer();

            if (!caster || !target)
                return;

            uint32 spellId = 0;
            uint8 gender = target->getGender();

            switch (GetSpellInfo()->Id)
            {
                case SPELL_HALLOWEEN_WAND_LEPER_GNOME:
                    spellId = gender ? SPELL_LEPER_GNOME_COSTUME_FEMALE : SPELL_LEPER_GNOME_COSTUME_MALE;
                    break;
                case SPELL_HALLOWEEN_WAND_PIRATE:
                    spellId = gender ? SPELL_PIRATE_COSTUME_FEMALE : SPELL_PIRATE_COSTUME_MALE;
                    break;
                case SPELL_HALLOWEEN_WAND_GHOST:
                    spellId = gender ? SPELL_GHOST_COSTUME_FEMALE : SPELL_GHOST_COSTUME_MALE;
                    break;
                case SPELL_HALLOWEEN_WAND_NINJA:
                    spellId = gender ? SPELL_NINJA_COSTUME_FEMALE : SPELL_NINJA_COSTUME_MALE;
                    break;
                case SPELL_HALLOWEEN_WAND_RANDOM:
                    spellId = RAND(SPELL_HALLOWEEN_WAND_PIRATE, SPELL_HALLOWEEN_WAND_NINJA, SPELL_HALLOWEEN_WAND_LEPER_GNOME, SPELL_HALLOWEEN_WAND_SKELETON, SPELL_HALLOWEEN_WAND_WISP, SPELL_HALLOWEEN_WAND_GHOST, SPELL_HALLOWEEN_WAND_BAT);
                    break;
            }
            caster->CastSpell(target, spellId, true);
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_halloween_wand_SpellScript::HandleScriptEffect);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_halloween_wand_SpellScript();
    }
};

class spell_toss_stinky_bomb : public SpellScriptLoader
{
public:
    spell_toss_stinky_bomb() : SpellScriptLoader("spell_toss_stinky_bomb") {}

    class spell_toss_stinky_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_toss_stinky_bomb_SpellScript)

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                caster->ToPlayer()->KilledMonsterCredit(NPC_STINKY_BOMB_CREDIT, 0);
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_toss_stinky_bomb_SpellScript::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SEND_EVENT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_toss_stinky_bomb_SpellScript();
    }
};

class spell_clean_stinky_bomb : public SpellScriptLoader
{
public:
    spell_clean_stinky_bomb() : SpellScriptLoader("spell_clean_stinky_bomb") {}

    class spell_clean_stinky_bomb_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_clean_stinky_bomb_SpellScript)

        SpellCastResult CheckIfNearBomb()
        {
            Unit* caster = GetCaster();

            if(GameObject* stinky = GetClosestGameObjectWithEntry(caster, GO_STINKY_BOMB_CLOUD, 15.0f))
                return SPELL_CAST_OK;
            else
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        }

        void HandleCleanBombEffect(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (GameObject* stinky = GetClosestGameObjectWithEntry(caster, GO_STINKY_BOMB_CLOUD, 15.0f))
                stinky->RemoveFromWorld();
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_clean_stinky_bomb_SpellScript::CheckIfNearBomb);
            OnEffectHit += SpellEffectFn(spell_clean_stinky_bomb_SpellScript::HandleCleanBombEffect, EFFECT_1, SPELL_EFFECT_ACTIVATE_OBJECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_clean_stinky_bomb_SpellScript();
    }
};

class at_wickerman_festival : public AreaTriggerScript
{
    public:
        at_wickerman_festival() : AreaTriggerScript("at_wickerman_festival") {}

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            player->GroupEventHappens(QUEST_CRASHING_WICKERMAN_FESTIVAL, player);
            return true;
        }
};

#define GOSSIP_WICKERMAN_EMBER "Usar las cenizas como pintura de guerra para la cara" //"Smear the ash on my face like war paint!" 

class go_wickerman_ember : public GameObjectScript
{
public:
    go_wickerman_ember() : GameObjectScript("go_wickerman_ember") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (!player->HasAura(SPELL_GRIM_VISAGE))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WICKERMAN_EMBER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
    {
        if (action == GOSSIP_ACTION_INFO_DEF)
            go->CastSpell(player, SPELL_GRIM_VISAGE);

        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

class npc_halloween_fire : public CreatureScript
{
public:
    npc_halloween_fire() : CreatureScript("npc_halloween_fire") { }


    struct npc_halloween_fireAI : public ScriptedAI
    {
        npc_halloween_fireAI(Creature* c) : ScriptedAI(c) {}

        bool fireEffigy;
        EventMap events;
        uint64 _playerGUID;

        void Reset()
        {
            fireEffigy = false;
            _playerGUID = 0;
            events.Reset();
            // Mark the npc if is for handling effigy instead of horseman fires
            if(GameObject* effigy = me->FindNearestGameObject(GO_FIRE_EFFIGY, 0.5f))
                fireEffigy = true;
            events.ScheduleEvent(EVENT_FIRE_GROW_FIRE, 1000);
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            switch(events.ExecuteEvent())
            {
                case EVENT_FIRE_VISUAL_WATER:
                    me->CastSpell(me, SPELL_WATER_SPOUT_VISUAL, true);
                    if (fireEffigy)
                    {
                        if (GameObject* effigy = me->FindNearestGameObject(GO_FIRE_EFFIGY, 0.5f))
                        {
                            effigy->SetGoState(GO_STATE_READY);
                            if (Player* player = me->GetPlayer(*me, _playerGUID))
                                player->KilledMonsterCredit(me->GetEntry(),0);
                            events.ScheduleEvent(EVENT_FIRE_GROW_FIRE, 22000);
                        }
                    }
                    break;
                case EVENT_FIRE_GROW_FIRE:
                    if (fireEffigy)
                    {
                        if(GameObject* effigy = me->FindNearestGameObject(GO_FIRE_EFFIGY, 0.5f))
                            effigy->SetGoState(GO_STATE_ACTIVE);
                    }
                    break;

            }
        }

        void SetGUID(uint64 guid, int32 id)
        {
            if (id == EVENT_FIRE_HIT_BY_BUCKET)
            {
                _playerGUID = guid;
                if (fireEffigy)
                {
                    if (GameObject* effigy = me->FindNearestGameObject(GO_FIRE_EFFIGY, 0.5f))
                        if (effigy->GetGoState() == GO_STATE_ACTIVE)
                            events.ScheduleEvent(EVENT_FIRE_VISUAL_WATER, 1000);
                } else
                    events.ScheduleEvent(EVENT_FIRE_VISUAL_WATER, 1000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_halloween_fireAI(creature);
    }
};

void AddSC_custom_fixes()
{
    new spell_oracle_wolvar;
    new spell_sunreaver_disguise;
    new spell_divine_intervention;
    new spell_toss_stinky_bomb();
    new spell_clean_stinky_bomb();
    new at_wickerman_festival();
    new spell_halloween_wand();
    new go_wickerman_ember();
    new npc_halloween_fire();
}
